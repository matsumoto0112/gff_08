#pragma once

#include <strix/net/object/_MetaClassT.h>
#include <strix/net/io/Encoder.h>
#include <strix/net/io/Decoder.h>

#include <set>
#include <list>
#include <memory>
#include <chrono>
#include <assert.h>

namespace strix { namespace net { namespace serialization { namespace serializer {

template <typename T, bool IsObject = std::is_same<object::Object, T>::value || std::is_base_of<object::Object, T>::value>
class SerializerImpl {};

template <>
class SerializerImpl<bool, false>
{
public:
	bool Serialize(io::Encoder &encoder, const bool &value) {
		return encoder.WriteBool(value);
	}
	bool Deserialize(io::Decoder &decoder, bool &value) {
		return decoder.ReadBool(value);
	}
};

template <>
class SerializerImpl<char, false>
{
public:
	bool Serialize(io::Encoder &encoder, const char &value) {
		return encoder.WriteByte(value);
	}
	bool Deserialize(io::Decoder &decoder, char &value) {
		return decoder.ReadByte((uint8_t&)value);
	}
};

template <>
class SerializerImpl<wchar_t, false>
{
public:
	bool Serialize(io::Encoder &encoder, const wchar_t &value) {
		return encoder.WriteInt(value);
	}
	bool Deserialize(io::Decoder &decoder, wchar_t &value) {
		int v;
		if (!decoder.ReadInt(v))
			return false;

		value = (wchar_t)v;
		return true;
	}
};

template <>
class SerializerImpl<char16_t, false>
{
public:
	bool Serialize(io::Encoder &encoder, const char16_t &value) {
		return encoder.WriteInt(value);
	}
	bool Deserialize(io::Decoder &decoder, char16_t &value) {
		int v;
		if (!decoder.ReadInt(v))
			return false;

		value = (char16_t)v;
		return true;
	}
};

template <>
class SerializerImpl<signed char, false>
{
public:
	bool Serialize(io::Encoder &encoder, const signed char &value) {
		return encoder.WriteByte(value);
	}
	bool Deserialize(io::Decoder &decoder, signed char &value) {
		return decoder.ReadByte((uint8_t&)value);
	}
};

template <>
class SerializerImpl<unsigned char, false>
{
public:
	bool Serialize(io::Encoder &encoder, const unsigned char &value) {
		return encoder.WriteByte(value);
	}
	bool Deserialize(io::Decoder &decoder, unsigned char &value) {
		return decoder.ReadByte(value);
	}
};

template <>
class SerializerImpl<short, false>
{
public:
	bool Serialize(io::Encoder &encoder, const short &value) {
		return encoder.WriteShort(value);
	}
	bool Deserialize(io::Decoder &decoder, short &value) {
		return decoder.ReadShort(value);
	}
};

template <>
class SerializerImpl<unsigned short, false>
{
public:
	bool Serialize(io::Encoder &encoder, const unsigned short &value) {
		return encoder.WriteShort(value);
	}
	bool Deserialize(io::Decoder &decoder, unsigned short &value) {
		return decoder.ReadShort((short&)value);
	}
};

template <>
class SerializerImpl<int, false>
{
public:
	bool Serialize(io::Encoder &encoder, const int &value) {
		return encoder.WriteInt(value);
	}
	bool Deserialize(io::Decoder &decoder, int &value) {
		return decoder.ReadInt(value);
	}
};

template <>
class SerializerImpl<unsigned int, false>
{
public:
	bool Serialize(io::Encoder &encoder, const unsigned int &value) {
		return encoder.WriteInt(value);
	}
	bool Deserialize(io::Decoder &decoder, unsigned int &value) {
		return decoder.ReadInt((int&)value);
	}
};

template <>
class SerializerImpl<long, false>
{
public:
	bool Serialize(io::Encoder &encoder, const long &value) {
		return encoder.WriteLong(value);
	}
	bool Deserialize(io::Decoder &decoder, long &value) {
		return decoder.ReadLong(value);
	}
};

template <>
class SerializerImpl<unsigned long, false>
{
public:
	bool Serialize(io::Encoder &encoder, const unsigned long &value) {
		return encoder.WriteLong(value);
	}
	bool Deserialize(io::Decoder &decoder, unsigned long &value) {
		return decoder.ReadLong((long&)value);
	}
};

template <>
class SerializerImpl<long long, false>
{
public:
	bool Serialize(io::Encoder &encoder, const long long &value) {
		return encoder.WriteLongLong(value);
	}
	bool Deserialize(io::Decoder &decoder, long long &value) {
		return decoder.ReadLongLong(value);
	}
};

template <>
class SerializerImpl<unsigned long long, false>
{
public:
	bool Serialize(io::Encoder &encoder, const unsigned long long &value) {
		return encoder.WriteLongLong(value);
	}
	bool Deserialize(io::Decoder &decoder, unsigned long long &value) {
		return decoder.ReadLongLong((long long&)value);
	}
};



template <>
class SerializerImpl<float, false>
{
public:
	bool Serialize(io::Encoder &encoder, const float &value) {
		return encoder.WriteFloat(value);
	}
	bool Deserialize(io::Decoder &decoder, float &value) {
		return decoder.ReadFloat(value);
	}
};

template <>
class SerializerImpl<double, false>
{
public:
	bool Serialize(io::Encoder &encoder, const double &value) {
		return encoder.WriteDouble(value);
	}
	bool Deserialize(io::Decoder &decoder, double &value) {
		return decoder.ReadDouble(value);
	}
};

class StringSerializerImpl
{
protected:
	bool SerializeString(io::Encoder &encoder, const std::string &value) const;

	bool DeserializeString(io::Decoder &decoder, std::string &value) const;
};

class WStringSerializerImpl
{
protected:
	bool SerializeString(io::Encoder &encoder, const std::wstring &value) const;

	bool DeserializeString(io::Decoder &decoder, std::wstring &value) const;
};

template <>
class SerializerImpl<std::string, false> : public StringSerializerImpl
{
public:
	bool Serialize(io::Encoder &encoder, const std::string &value) {
		return SerializeString(encoder, value);
	}
	bool Deserialize(io::Decoder &decoder, std::string &value) {
		return DeserializeString(decoder, value);
	}
};

template <>
class SerializerImpl<std::wstring, false> : public WStringSerializerImpl
{
public:
	bool Serialize(io::Encoder &encoder, const std::wstring &value) {
		return SerializeString(encoder, value);
	}
	bool Deserialize(io::Decoder &decoder, std::wstring &value) {
		return DeserializeString(decoder, value);
	}
};


template <typename T, size_t Size>
class SerializerImpl<T(&)[Size], false>
{
	bool Serialize(io::Encoder &encoder, const T value[Size]) {
		if(!encoder.WriteArrayBegin(Size))
			return false;

		for(size_t i=0; i<Size; i++)
		{
			if(!encoder.WriteArrayItemBegin(i))
				return false;

			if(!SerializerImpl<T>().Serialize(encoder, value[i]))
				return false;

			if(!encoder.WriteArrayItemEnd(i))
				return false;
		}

		if(!encoder.WriteArrayEnd())
			return false;

		return true;
	}
	bool Deserialize(io::Decoder &decoder, T value[Size]) {
		int len;
		if(!decoder.ReadArrayBegin(len))
			return false;

		assert(len < Size);

		for(int i=0; i<len; i++)
		{
			if(!SerializerImpl<T>().Deserialize(decoder, value[i]))
				return false;
		}

		if(!decoder.ReadArrayEnd())
			return false;

		return true;
	}
};

template <typename T, typename Allocator>
class SerializerImpl<std::vector<T, Allocator>, false>
{
public:
	typedef std::vector<T, Allocator> ArgType;

	bool Serialize(io::Encoder &encoder, const ArgType &value) {
		if(!encoder.WriteArrayBegin((int)value.size()))
			return false;

		int index = 0;
		for(typename ArgType::const_iterator it = value.begin(); it != value.end(); ++it)
		{
			if(!encoder.WriteArrayItemBegin(index))
				return false;

			if(!SerializerImpl<T>().Serialize(encoder, *it))
				return false;

			if(!encoder.WriteArrayItemEnd(index))
				return false;

			++index;
		}

		if(!encoder.WriteArrayEnd())
			return false;

		return true;
	}
	bool Deserialize(io::Decoder &decoder, ArgType &value) {
		int len;
		if(!decoder.ReadArrayBegin(len))
			return false;

		value.resize(len);

		for(int i=0; i<len; i++)
		{
			if(!SerializerImpl<T>().Deserialize(decoder, value[i]))
				return false;
		}

		if(!decoder.ReadArrayEnd())
			return false;

		return true;
	}
};

template <typename T, typename Allocator>
class SerializerImpl<std::list<T, Allocator>, false>
{
public:
	typedef std::list<T, Allocator> ArgType;

	bool Serialize(io::Encoder &encoder, const ArgType &value) {
		if(!encoder.WriteArrayBegin((int)value.size()))
			return false;

		int index = 0;
		for(typename ArgType::const_iterator it = value.begin(); it != value.end(); ++it)
		{
			if(!encoder.WriteArrayItemBegin(index))
				return false;

			if(!SerializerImpl<T>().Serialize(encoder, *it))
				return false;
			
			if(!encoder.WriteArrayItemEnd(index))
				return false;

			++index;
		}

		if(!encoder.WriteArrayEnd())
			return false;

		return true;
	}
	bool Deserialize(io::Decoder &decoder, ArgType &value) {
		int len;
		value.clear();

		if (!decoder.ReadArrayBegin(len))
		{
			if (decoder.ReadNull())
				return true;
			else
				return false;
		}

		value.clear();

		for(int i=0; i<len; i++) {
			T v;
			if(!SerializerImpl<T>().Deserialize(decoder, v))
				return false;
			value.push_back(v);
		}

		if(!decoder.ReadArrayEnd())
			return false;

		return true;
	}
};

template <typename T, typename Pred, typename Allocator>
class SerializerImpl<std::set<T, Pred, Allocator>, false>
{
public:
	typedef std::set<T, Pred, Allocator> ArgType;

	bool Serialize(io::Encoder &encoder, const ArgType &value) {
		if(!encoder.WriteArrayBegin((int)value.size()))
			return false;

		int index = 0;
		for(typename ArgType::const_iterator it = value.begin(); it != value.end(); ++it)
		{
			if(!encoder.WriteArrayItemBegin(index))
				return false;

			if(!SerializerImpl<T>().Serialize(encoder, *it))
				return false;

			if(!encoder.WriteArrayItemEnd(index))
				return false;

			++index;
		}

		if(!encoder.WriteArrayEnd())
			return false;

		return true;
	}
	bool Deserialize(io::Decoder &decoder, ArgType &value) {
		int len;
		value.clear();

		if (!decoder.ReadArrayBegin(len))
		{
			if (decoder.ReadNull())
				return true;
			else
				return false;
		}

		for(int i=0; i<len; i++) {
			T v;
			if(!SerializerImpl<T>().Deserialize(decoder, v))
				return false;

			value.insert(v);
		}

		if(!decoder.ReadArrayEnd())
			return false;

		return true;
	}
};

template <typename KeyType, typename ValueType, typename Pred, typename Allocator>
class SerializerImpl<std::map<KeyType, ValueType, Pred, Allocator>, false>
{
public:
	typedef std::map<KeyType, ValueType, Pred, Allocator> ArgType;

	bool Serialize(io::Encoder &encoder, const ArgType &value) {
		if(!encoder.WriteMapBegin((int)value.size()))
			return false;

		int index = 0;
		for(typename ArgType::const_iterator it = value.begin(); it != value.end(); ++it)
		{
			if(!encoder.WriteMapKeyBegin(index))
				return false;

			if(!SerializerImpl<KeyType>().Serialize(encoder, it->first))
				return false;

			if(!encoder.WriteMapKeyEnd(index))
				return false;

			if(!encoder.WriteMapValueBegin(index))
				return false;

			if(!SerializerImpl<ValueType>().Serialize(encoder, it->second))
				return false;

			if(!encoder.WriteMapValueEnd(index))
				return false;

			++index;
		}

		if(!encoder.WriteMapEnd())
			return false;

		return true;
	}
	bool Deserialize(io::Decoder &decoder, ArgType &value) {
		int len;
		value.clear();

		if (!decoder.ReadMapBegin(len))
		{
			if (decoder.ReadNull())
				return true;
			else
				return false;
		}
		
		int index = 0;
		for(int i=0; i<len; i++)
		{
			KeyType k;
			ValueType v;

			if (!decoder.ReadMapKeyBegin(index))
				return false;

			if(!SerializerImpl<KeyType>().Deserialize(decoder, k))
				return false;

			if(!decoder.ReadMapKeyEnd(index))
				return false;

			if(!decoder.ReadMapValueBegin(index))
				return false;

			if(!SerializerImpl<ValueType>().Deserialize(decoder, v))
				return false;

			if(!decoder.ReadMapValueEnd(index))
				return false;

			++index;

			value.insert(typename ArgType::value_type(k, v));
		}

		if(!decoder.ReadMapEnd())
			return false;

		return true;
	}
};

class ObjectSerializerImpl
{
protected:
	bool SerializeObject(io::Encoder &encoder, const object::Object &value) {
		return SerializeObject(encoder, value.GetMetaClass(), &value);
	}

	bool SerializeObject(io::Encoder &encoder, const object::MetaClass &metaClass, const object::Object *value);

	bool DeserializeObject(io::Decoder &decoder, const object::MetaClass &metaClass, object::Object *&value);
};

template <typename T>
class SerializerImpl<T, true> : public ObjectSerializerImpl
{
public:
	bool Serialize(io::Encoder &encoder, const T &value) {
		return SerializeObject(encoder, value);
	}

	bool Deserialize(io::Decoder &decoder, T &value) {
		object::Object *pValue = &value;
		return DeserializeObject(decoder, object::MetaClassT<T>::Get(), pValue);
	}
};

template <typename T, bool IsObject = std::is_same<object::Object, T>::value || std::is_base_of<object::Object, T>::value>
class PointerSerializerImpl {};

template <typename T>
class PointerSerializerImpl<T, false>
{
public:
	bool Serialize(io::Encoder &encoder, const T *value) {
		return SerializerImpl<T>().Serialize(encoder, *value);
	}

	bool Deserialize(io::Decoder &decoder, T *&value) {
		if(!value)
			value = static_cast<T*>(object::MetaClassT<T>::Get().Create());
		return SerializerImpl<T>().Deserialize(decoder, *value);
	}
};

template <typename T>
class PointerSerializerImpl<T, true> : public ObjectSerializerImpl
{
public:
	bool Serialize(io::Encoder &encoder, const T *value) {
		const object::MetaClass &metaClass = (value != nullptr ? value->GetMetaClass() : object::MetaClassT<T>::Get());
		return SerializeObject(encoder, metaClass, value);
	}

	bool Deserialize(io::Decoder &decoder, T *&value) {
		object::Object *pObject = static_cast<object::Object*>(value);
		
		if (!DeserializeObject(decoder, object::MetaClassT<T>::Get(), pObject))
			return false;

		value = static_cast<T*>(pObject);

		return true;
	}
};

template <typename T>
class SerializerImpl<T*, false> : public PointerSerializerImpl<T> {};

template <typename T>
class SerializerImpl<const T*, false>
{
public:
	bool Serialize(io::Encoder &encoder, const T *value) {
		return SerializerImpl<T*, false>().Serialize(encoder, value);
	}
	
	bool Deserialize(io::Decoder &decoder, const T *&value) {
		return SerializerImpl<T*, false>().Deserialize(decoder, const_cast<T*&>(value));
	}
};

template <typename T>
class BinarySerializerImpl
{
public:
	bool Serialize(io::Encoder &encoder, const T &value) {
		return encoder.WriteBinary(reinterpret_cast<const uint8_t*>(&value[0]), value.size());
	}
	bool Deserialize(io::Decoder &decoder, T &value) {
		size_t size;
		if(!decoder.ReadBinaryBegin(size))
			return false;
		value.resize(size);
		if(size > 0)
		{
			if(!decoder.ReadBinary(reinterpret_cast<unsigned char*>(&value[0]), size))
				return false;
		}
		return decoder.ReadBinaryEnd();
	}
};

template <> class SerializerImpl<std::vector<char>, false> : public BinarySerializerImpl<std::vector<char> > {};
template <> class SerializerImpl<std::vector<int8_t>, false> : public BinarySerializerImpl<std::vector<int8_t> > {};
template <> class SerializerImpl<std::vector<uint8_t>, false> : public BinarySerializerImpl<std::vector<uint8_t> > {};

template <typename T>
class SmartPointerSerializerImpl
{
public:
	bool Serialize(io::Encoder &encoder, const T &value) {
		return SerializerImpl<typename T::element_type*>().Serialize(encoder, value.get());
	}

	bool Deserialize(io::Decoder &decoder, T &value) {
		typename T::element_type *p = nullptr;

		if(!SerializerImpl<typename T::element_type*>().Deserialize(decoder, p))
			return false;

		value.reset(p);

		return true;
	}
};

template <typename T>
class SerializerImpl<std::shared_ptr<T>, false> : public SmartPointerSerializerImpl<std::shared_ptr<T> > {};

template <typename T>
class SerializerImpl<std::unique_ptr<T>, false> : public SmartPointerSerializerImpl<std::unique_ptr<T> > {};

template <>
class SerializerImpl<std::chrono::system_clock::time_point, false>
{
public:
	bool Serialize(io::Encoder &encoder, const std::chrono::system_clock::time_point &value) {
		long long milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(value.time_since_epoch()).count();
		return encoder.WriteLongLong(milliseconds);
	}
	bool Deserialize(io::Decoder &decoder, std::chrono::system_clock::time_point &value) {
		long long milliseconds;

		if (!decoder.ReadLongLong(milliseconds))
			return false;

		value = std::chrono::system_clock::time_point(std::chrono::milliseconds(milliseconds));
		return true;
	}
};

} } } }
