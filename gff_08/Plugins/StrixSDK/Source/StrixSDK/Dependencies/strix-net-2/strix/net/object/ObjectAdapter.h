#pragma once

#include <chrono>
#include <memory>
#include <string>
#include <vector>

namespace strix { namespace net { namespace object {

class Object;
typedef std::shared_ptr<Object> ObjectPtr;

class ObjectAdapter
{
public:
	ObjectAdapter(bool value);
	ObjectAdapter(char value);
	ObjectAdapter(const char *value);
	ObjectAdapter(const std::string &value);
	ObjectAdapter(const std::vector<uint8_t> &value);
	ObjectAdapter(const std::chrono::system_clock::time_point &value);
	ObjectAdapter(int8_t value);
	ObjectAdapter(uint8_t value);
	ObjectAdapter(short value);
	ObjectAdapter(unsigned short value);
	ObjectAdapter(int value);
	ObjectAdapter(unsigned int value);
	ObjectAdapter(long value);
	ObjectAdapter(unsigned long value);
	ObjectAdapter(long long value);
	ObjectAdapter(unsigned long long value);
	ObjectAdapter(float value);
	ObjectAdapter(double value);
	ObjectAdapter(ObjectPtr value);

	template <class T>
	ObjectAdapter(std::shared_ptr<T> value)
	{
		static_assert(std::is_base_of<Object, T>::value, "Must be an Object type");
		m_value = std::move(value);
	}

	ObjectPtr &Get();

	const ObjectPtr &Get() const;

	ObjectPtr &operator*();

	const ObjectPtr &operator*() const;

	operator ObjectPtr() const;

	operator Object *() const;

	operator Object() const;

private:
	ObjectPtr m_value;
};

} } }
