#pragma once

#include <strix/net/object/WrapperObject.h>

#include <functional>

namespace strix { namespace net { namespace object {

template<typename T>
struct EqualsExists
{
private:
	template<typename U> static auto Test(bool) -> decltype(std::declval<U>() == std::declval<U>(), std::true_type());

	template<typename> static std::false_type Test(...);

public:

	static constexpr bool value = std::is_same<decltype(Test<T>(0)), std::true_type>::value;
};

template <typename T, int _ClassId>
class ComparableWrapperObjectImpl : public WrapperObjectT<T>
{
public:
	STRIX_CLASS(ComparableWrapperObjectImpl, WrapperObjectT<T>)
	(
		STRIX_CLASS_ID(_ClassId)
	)

	ComparableWrapperObjectImpl() = default;
	ComparableWrapperObjectImpl(const ComparableWrapperObjectImpl<T, _ClassId> &other) : WrapperObjectT<T>(other), m_comparator(other->GetComparator()) {};
	ComparableWrapperObjectImpl(const T &value) : WrapperObjectT<T>(value) {};
	ComparableWrapperObjectImpl(T &&value) : WrapperObjectT<T>(std::move(value)) {};
	ComparableWrapperObjectImpl(const T &value, std::function<int(const T &)> comparator) : WrapperObjectT<T>(value), m_comparator(comparator) {};
	ComparableWrapperObjectImpl(T &&value, std::function<int(const T &)> comparator) : WrapperObjectT<T>(std::move(value)), m_comparator(comparator) {};

	virtual ~ComparableWrapperObjectImpl() = default;

	ComparableWrapperObjectImpl<T, _ClassId> &operator=(const T &value) {
		WrapperObjectT<T>::m_value = value;
		return *this;
	}

	ComparableWrapperObjectImpl<T, _ClassId> &operator=(T &&value) {
		WrapperObjectT<T>::m_value = std::move(value);
		return *this;
	}

	ComparableWrapperObjectImpl<T, _ClassId> &operator=(const ComparableWrapperObjectImpl<T, _ClassId> &other) {
		WrapperObjectT<T>::m_value = other.m_value;
		return *this;
	}

	ComparableWrapperObjectImpl<T, _ClassId> &operator=(ComparableWrapperObjectImpl<T, _ClassId> &&other) = default;

	bool operator==(const ComparableWrapperObjectImpl<T, _ClassId> &rhs) const {
		return WrapperObjectT<T>::m_value == rhs.m_value;
	}

	bool operator!=(const ComparableWrapperObjectImpl<T, _ClassId> &rhs) const {
		return WrapperObjectT<T>::m_value != rhs.m_value;
	}

	template <typename Type>
	std::enable_if_t<EqualsExists<Type>::value, int>
	CompareT(const Type &rhs) const {
		if (WrapperObjectT<Type>::m_value == rhs)
		{
			return 0;
		}

		if (&(WrapperObjectT<Type>::m_value) > &rhs)
			return 1;
		if (&(WrapperObjectT<Type>::m_value) < &rhs)
			return -1;

		return 0;
	}

	template <typename Type>
	std::enable_if_t<!EqualsExists<Type>::value, int>
	CompareT(const Type &rhs) const {
		if (&(WrapperObjectT<Type>::m_value) > &rhs)
			return 1;
		if (&(WrapperObjectT<Type>::m_value) < &rhs)
			return -1;

		return 0;
	}

	int Compare(const Object &rhs) const override {
		const MetaClass &metaClass = GetMetaClass();
		const MetaClass &metaClass2 = rhs.GetMetaClass();

		if (&metaClass > &metaClass2)
			return 1;
		if (&metaClass < &metaClass2)
			return -1;

		const ComparableWrapperObjectImpl<T, _ClassId> &v = static_cast<const ComparableWrapperObjectImpl<T, _ClassId> &>(rhs);

		if (m_comparator)
		{
			return m_comparator(v);
		}

		return CompareT<T>(v.m_value);
	}

	std::function<int(const T &)> GetComparator()
	{
		return m_comparator;
	}

private:
	std::function<int(const T &)> m_comparator;
};

} } }
