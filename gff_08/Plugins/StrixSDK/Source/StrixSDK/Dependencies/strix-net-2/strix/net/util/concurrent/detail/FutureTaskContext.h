#pragma once

#include <atomic>
#include <chrono>
#include <cstddef>
#include <functional>
#include <future>
#include <utility>

namespace strix { namespace net { namespace util { namespace concurrent { namespace detail {

template <typename T>
class FutureTaskContextBase
{
public:
	typedef T ResultType;
	typedef std::function<ResultType()> FunctionType;
	typedef std::future<ResultType> FutureType;
	typedef std::promise<ResultType> PromiseType;
	
	FutureTaskContextBase() {}
	FutureTaskContextBase(std::nullptr_t) {}
	FutureTaskContextBase(const FutureTaskContextBase &rhs) = default;

	template <typename Fn>
	FutureTaskContextBase(Fn &&command)
		:	m_command(std::move(command)),
			m_future(m_promise.get_future()),
			m_cancelled(false) {
	}
		
	FutureType &GetFuture() {
		return m_future;
	}

	bool IsDone() const {
		return (m_future.wait_for(std::chrono::nanoseconds(0)) == std::future_status::ready);
	}

	bool IsCancelled() const {
		return m_cancelled;
	}

	void Cancel() {
		m_cancelled = true;
	}

	operator bool() const {
		return static_cast<bool>(m_command);
	}

protected:
	FunctionType m_command;
	PromiseType m_promise;
	FutureType m_future;
	std::atomic<bool> m_cancelled;
};

template <typename T>
class FutureTaskContext : public FutureTaskContextBase<T>
{
public:
	typedef FutureTaskContextBase<T> BaseType;
	using typename BaseType::ResultType;
	using typename BaseType::FutureType;
	using typename BaseType::PromiseType;
	
	FutureTaskContext() {}
	FutureTaskContext(std::nullptr_t) {}
	FutureTaskContext(const FutureTaskContext &rhs) = default;

	template <typename Fn>
	FutureTaskContext(Fn &&command) : BaseType(std::forward<Fn>(command)) {}

	void Invoke() {
		if(BaseType::IsCancelled())
			return;

		ResultType ret = BaseType::m_command();
		Set(ret);
	}

	ResultType Get() {
		if(BaseType::IsCancelled())
			return ResultType();

		return BaseType::m_future.get();
	}

	void Set(const ResultType &value) {
		BaseType::m_promise.set_value(value);
	}
};

template <>
class FutureTaskContext<void> : public FutureTaskContextBase<void>
{
public:
	typedef FutureTaskContextBase<void> BaseType;
	using typename BaseType::ResultType;
	using typename BaseType::FutureType;
	using typename BaseType::PromiseType;
		
	FutureTaskContext() {}
	FutureTaskContext(std::nullptr_t) {}
	FutureTaskContext(const FutureTaskContext &rhs) = default;

	template <typename Fn>
	FutureTaskContext(Fn &&command) : BaseType(std::forward<Fn>(command)) {}
	
	void Invoke() {
		if(BaseType::IsCancelled())
			return;

		BaseType::m_command();
		Set();
	}

	void Get() {
		if(BaseType::IsCancelled())
			return;

		BaseType::m_future.get();
	}

	void Set() {
		BaseType::m_promise.set_value();
	}
};

} } } } }
