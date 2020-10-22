#pragma once

#include <strix/net/util/concurrent/detail/FutureTaskContext.h>

#include <cstddef>
#include <functional>
#include <future>
#include <memory>

namespace strix { namespace net { namespace util { namespace concurrent {

template <typename ResultType>
class FutureTaskBase
{
public:
	typedef std::function<ResultType()> FunctionType;
	typedef std::future<ResultType> FutureType;
	typedef std::promise<ResultType> PromiseType;

	FutureTaskBase() {}

	template <typename Fn>
	FutureTaskBase(const Fn &command)
		: m_pContext(std::make_shared<detail::FutureTaskContext<ResultType> >(command)) {}

	FutureType &GetFuture() {
		return m_pContext->GetFuture();
	}

	bool IsDone() const {
		if(!m_pContext)
			return false;

		return m_pContext->IsDone();
	}

	bool IsCancelled() const {
		if(!m_pContext)
			return false;

		return m_pContext->IsCancelled();
	}

	void Cancel() {
		if(!m_pContext)
			return;

		return m_pContext->Cancel();
	}

	operator bool() const {
		if(!m_pContext)
			return false;

		return static_cast<bool>(*m_pContext);
	}

protected:
	std::shared_ptr<detail::FutureTaskContext<ResultType> > m_pContext;
};

template <typename ResultType>
class FutureTask : public FutureTaskBase<ResultType>
{
public:
	typedef FutureTaskBase<ResultType> BaseType;
	using typename BaseType::FunctionType;
	using typename BaseType::FutureType;
	using typename BaseType::PromiseType;

	FutureTask() {}

	template <typename Fn>
	explicit FutureTask(const Fn &command) : BaseType::FutureTaskBase(command) {}

	void operator()() {
		BaseType::m_pContext->Invoke();
	}

	ResultType Get() {
		return BaseType::m_pContext->Get();
	}

	FutureTask& operator=(std::nullptr_t) {
		BaseType::operator=(nullptr);
		return *this;
	}
};

template <>
class FutureTask<void> : public FutureTaskBase<void>
{
public:
	typedef FutureTaskBase<void> BaseType;
	using typename BaseType::FunctionType;
	using typename BaseType::FutureType;
	using typename BaseType::PromiseType;

	FutureTask() {}

	template <typename Fn>
	explicit FutureTask(const Fn &command) : FutureTaskBase(command) {}

	void operator()() {
		BaseType::m_pContext->Invoke();
	}

	void Get() {
		BaseType::m_pContext->Get();
	}

	FutureTask& operator=(std::nullptr_t) {
		BaseType::operator=(nullptr);
		return *this;
	}
};

} } } }
