#pragma once

#include <strix/net/object/Object.h>
#include <strix/net/object/PredefinedClassId.h>
#include <strix/net/util/NumberComparator.h>

#include <utility>

namespace strix { namespace net { namespace object {

class Number : public Object
{
public:
	STRIX_ABSTRACT_CLASS(Number, Object)
	(
	)

	enum class Type
	{
		Byte,
		UByte,
		Short,
		UShort,
		Int,
		UInt,
		Long,
		ULong,
		LongLong,
		ULongLong,
		Float,
		Double,
	};

	virtual const void * GetRaw() const = 0;

	virtual Type GetType() const = 0;

	virtual int8_t ByteValue() const = 0;

	virtual uint8_t UByteValue() const = 0;
	
	virtual short ShortValue() const = 0;

	virtual unsigned short UShortValue() const = 0;

	virtual int IntValue() const = 0;

	virtual unsigned int UIntValue() const = 0;

	virtual long LongValue() const = 0;

	virtual unsigned long ULongValue() const = 0;

	virtual long long LongLongValue() const = 0;

	virtual unsigned long long ULongLongValue() const = 0;

	virtual float FloatValue() const = 0;

	virtual double DoubleValue() const = 0;
	
	virtual int CompareNumber(const Number &number) const = 0;

	bool operator<(const Number &rhs) const {
		return CompareNumber(rhs) < 0;
	}

	bool operator>(const Number &rhs) const {
		return CompareNumber(rhs) > 0;
	}

	bool operator>=(const Number &rhs) const {
		return !operator<(rhs);
	}

	bool operator<=(const Number &rhs) const {
		return !operator>(rhs);
	}

	bool operator==(const Number &rhs) const {
		return CompareNumber(rhs) == 0;
	}

	bool operator!=(const Number &rhs) const {
		return CompareNumber(rhs) != 0;
	}
};

template <typename T>
class NumberT : public Number
{
public:
	STRIX_ABSTRACT_CLASS(NumberT, Number)
	(
		STRIX_PROPERTY(m_value)
	)
		
	NumberT() : m_value() {} 
	NumberT(const T &value) : m_value(value) {};
	NumberT(T &&value) : m_value(std::move(value)) {};
	virtual ~NumberT() = default;

	const T &Get() const {
		return m_value;
	}

	void Set(const T &value) {
		m_value = value;
	}

	operator T() const {
		return m_value;
	}

	T &operator*() {
		return m_value;
	}

	const T &operator*() const {
		return m_value;
	}

	T *operator->() {
		return &m_value;
	}

	const T *operator->() const {
		return &m_value;
	}

	const void * GetRaw() const override
	{
		return &m_value;
	}

public:
	T m_value;
};

template <typename T, int _Type, int _ClassId>
class NumberImpl : public NumberT<T>
{
public:
	STRIX_CLASS(NumberImpl, NumberT<T>)
	(
		STRIX_CLASS_ID(_ClassId)
	)

	typedef T ValueType;
	
	NumberImpl() : NumberT<T>() {}
	NumberImpl(const T &value) : NumberT<T>(value) {}
	NumberImpl(T &&value) : NumberT<T>(std::move(value)) {}

	NumberImpl<T, _Type, _ClassId> &operator=(const T &value) {
		NumberT<T>::m_value = value;
		return *this;
	}
	
	NumberImpl<T, _Type, _ClassId> &operator=(T &&value) {
		NumberT<T>::m_value = std::move(value);
		return *this;
	}

	bool operator<(const NumberImpl<T, _Type, _ClassId> &rhs) const {
		return NumberT<T>::m_value < rhs.m_value;
	}

	bool operator<=(const NumberImpl<T, _Type, _ClassId> &rhs) const {
		return NumberT<T>::m_value <= rhs.m_value;
	}

	bool operator>(const NumberImpl<T, _Type, _ClassId> &rhs) const {
		return NumberT<T>::m_value > rhs.m_value;
	}

	bool operator>=(const NumberImpl<T, _Type, _ClassId> &rhs) const {
		return NumberT<T>::m_value >= rhs.m_value;
	}

	bool operator==(const NumberImpl<T, _Type, _ClassId> &rhs) const {
		return NumberT<T>::m_value == rhs.m_value;
	}

	bool operator!=(const NumberImpl<T, _Type, _ClassId> &rhs) const {
		return NumberT<T>::m_value != rhs.m_value;
	}

	Number::Type GetType() const override {
		return static_cast<Number::Type>(_Type);
	}

	/**
	 * 値を比較した結果を返します
	 * 
	 * 別のNumberクラスの値とは比較しません。
	 * 別のNumberクラスの値と比較したい場合はCompareNumberを使用してください。
	 */
	int Compare(const Object &rhs) const override {
		const MetaClass &metaClass = GetMetaClass();
		const MetaClass &metaClass2 = rhs.GetMetaClass();
		
		if (&metaClass > &metaClass2)
			return 1;
		if (&metaClass < &metaClass2)
			return -1;

		const NumberImpl<T, _Type, _ClassId> &v = static_cast<const NumberImpl<T, _Type, _ClassId> &>(rhs);
		
		if (NumberT<T>::m_value > v.m_value)
			return 1;
		if (NumberT<T>::m_value < v.m_value)
			return -1;

		return 0;
	}

	int8_t ByteValue() const override {
		return static_cast<int8_t>(NumberT<T>::m_value);
	}
	
	uint8_t UByteValue() const override {
		return static_cast<uint8_t>(NumberT<T>::m_value);
	}

	short ShortValue() const override {
		return static_cast<short>(NumberT<T>::m_value);
	}

	unsigned short UShortValue() const override {
		return static_cast<unsigned short>(NumberT<T>::m_value);
	}
	
	int IntValue() const override {
		return static_cast<int>(NumberT<T>::m_value);
	}

	unsigned int UIntValue() const override {
		return static_cast<unsigned int>(NumberT<T>::m_value);
	}
	
	long LongValue() const override {
		return static_cast<long>(NumberT<T>::m_value);
	}

	unsigned long ULongValue() const override {
		return static_cast<unsigned long>(NumberT<T>::m_value);
	}

	long long LongLongValue() const override {
		return static_cast<long long>(NumberT<T>::m_value);
	}

	unsigned long long ULongLongValue() const override {
		return static_cast<unsigned long long>(NumberT<T>::m_value);
	}

	float FloatValue() const override {
		return static_cast<float>(NumberT<T>::m_value);
	}

	double DoubleValue() const override {
		return static_cast<double>(NumberT<T>::m_value);
	}

	int CompareNumber(const Number &number) const override;
};

template <typename T, int _Type, int _ClassId>
int NumberImpl<T, _Type, _ClassId>::CompareNumber(const Number &number) const
{
	Number::Type type = number.GetType();

	switch(type)
	{
	case Number::Type::Byte:
		return util::NumberComparator::Compare<T, int8_t>(NumberT<T>::m_value, number.ByteValue());
	case Number::Type::UByte:
		return util::NumberComparator::Compare<T, uint8_t>(NumberT<T>::m_value, number.UByteValue());
	case Number::Type::Short:
		return util::NumberComparator::Compare<T, short>(NumberT<T>::m_value, number.ShortValue());
	case Number::Type::UShort:
		return util::NumberComparator::Compare<T, unsigned short>(NumberT<T>::m_value, number.UShortValue());
	case Number::Type::Int:
		return util::NumberComparator::Compare<T, int>(NumberT<T>::m_value, number.IntValue());
	case Number::Type::UInt:
		return util::NumberComparator::Compare<T, unsigned int>(NumberT<T>::m_value, number.UIntValue());
	case Number::Type::Long:
		return util::NumberComparator::Compare<T, long>(NumberT<T>::m_value, number.LongValue());
	case Number::Type::ULong:
		return util::NumberComparator::Compare<T, unsigned long>(NumberT<T>::m_value, number.ULongValue());
	case Number::Type::LongLong:
		return util::NumberComparator::Compare<T, long long>(NumberT<T>::m_value, number.LongLongValue());
	case Number::Type::ULongLong:
		return util::NumberComparator::Compare<T, unsigned long long>(NumberT<T>::m_value, number.ULongLongValue());
	case Number::Type::Float:
		return util::NumberComparator::Compare<T, float>(NumberT<T>::m_value, number.FloatValue());
	case Number::Type::Double:
		return util::NumberComparator::Compare<T, double>(NumberT<T>::m_value, number.DoubleValue());
	default:
		return -1;
	}
}

typedef NumberImpl<int8_t, static_cast<int>(Number::Type::Byte), static_cast<int>(PredefinedClassId::Byte)> ByteObject;
typedef NumberImpl<uint8_t, static_cast<int>(Number::Type::UByte), static_cast<int>(PredefinedClassId::UByte)> UByteObject;
typedef NumberImpl<short, static_cast<int>(Number::Type::Short), static_cast<int>(PredefinedClassId::Short)> ShortObject;
typedef NumberImpl<unsigned short, static_cast<int>(Number::Type::UShort), static_cast<int>(PredefinedClassId::UShort)> UShortObject;
typedef NumberImpl<int, static_cast<int>(Number::Type::Int), static_cast<int>(PredefinedClassId::Integer)> IntegerObject;
typedef NumberImpl<unsigned int, static_cast<int>(Number::Type::UInt), static_cast<int>(PredefinedClassId::UInteger)> UIntegerObject;
typedef NumberImpl<long, static_cast<int>(Number::Type::Long), static_cast<int>(PredefinedClassId::Long)> LongObject;
typedef NumberImpl<unsigned long, static_cast<int>(Number::Type::ULong), static_cast<int>(PredefinedClassId::ULong)> ULongObject;
typedef NumberImpl<long long, static_cast<int>(Number::Type::LongLong), static_cast<int>(PredefinedClassId::LongLong)> LongLongObject;
typedef NumberImpl<unsigned long long, static_cast<int>(Number::Type::ULongLong), static_cast<int>(PredefinedClassId::ULongLong)> ULongLongObject;
typedef NumberImpl<float, static_cast<int>(Number::Type::Float), static_cast<int>(PredefinedClassId::Float)> FloatObject;
typedef NumberImpl<double, static_cast<int>(Number::Type::Double), static_cast<int>(PredefinedClassId::Double)> DoubleObject;

template <>
class TypeNameFactory<Number>
{
public:
	static std::string GetTypeName(bool)
	{
		return "strix::net::object::Number";
	}
};

template <typename T>
class TypeNameFactory<NumberT<T>>
{
public:
	static std::string GetTypeName(bool)
	{
		return "strix::net::object::NumberT<"
			+ TypeNameFactory<T>::GetTypeName(true) + ">";
	}
};

} } }

