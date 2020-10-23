#pragma once

#include <strix/net/object/WrapperObject.h>
#include <strix/net/object/ObjectAdapter.h>

#include <map>
#include <memory>
#include <string>

namespace strix {namespace net {namespace object {
class ObjectAdapter;
} } }

namespace strix { namespace client { namespace ingame { namespace sync {

class PropertyMap
{
public:
	PropertyMap() = default;

	PropertyMap(std::map<int, net::object::ObjectPtr> properties)
		: m_properties(std::move(properties)) {}

	bool TryGet(const std::string &key, net::object::ObjectPtr &outValue) const;
	bool TryGet(int key, net::object::ObjectPtr &outValue) const;

	net::object::ObjectPtr Get(const std::string &key) const;
	net::object::ObjectPtr Get(int key) const;

	void Set(const std::string &key, net::object::ObjectAdapter value);
	void Set(int key, net::object::ObjectAdapter value);

	const std::map<int, net::object::ObjectPtr> &GetMap() const;

	void RemoveCommonEntries(std::map<int, net::object::ObjectPtr> other);

	static void RegisterIndexOfProperty(const std::string &propertyName, int code);
	static int GetIndexOfProperty(const std::string &propertyName);

private:
	std::map<int, net::object::ObjectPtr> m_properties;
	static std::map<std::string, int> m_propertyHashCodes;
};

} } } }
