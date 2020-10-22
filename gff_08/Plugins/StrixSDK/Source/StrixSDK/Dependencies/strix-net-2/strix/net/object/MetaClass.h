#pragma once

#include <strix/net/object/_Object.h>
#include <strix/net/util/SuperFastHash.h>

#include <map>
#include <vector>
#include <string>
#include <sstream>
#include <memory>
#include <algorithm>

namespace strix { namespace net { namespace io {
	class Decoder;
	class Encoder;
} } }

namespace strix { namespace net { namespace object {

class PropertyAccessor;
typedef std::shared_ptr<PropertyAccessor> PropertyAccessorPtr;

class MetaClass : public Object
{
public:
	typedef MetaClassT<MetaClass, true> MetaClassType;
	friend MetaClassType;

	class PropertyInfo
	{
	public:
		const std::string &GetName() const {
			return m_name;
		}

		void SetName(const std::string &name) {
			m_name = name;
		}

		const MetaClass *GetMetaClass() const {
			return m_pMetaClass;
		}

		void SetMetaClass(const MetaClass *pMetaClass) {
			m_pMetaClass = pMetaClass;
		}

		PropertyAccessorPtr GetAccessor() const {
			return m_pAccessor;
		}

		void SetAccessor(PropertyAccessorPtr pAccessor) {
			m_pAccessor = pAccessor;
		}

	private:
		std::string m_name;
		const MetaClass *m_pMetaClass;
		PropertyAccessorPtr m_pAccessor;
	};

	class SuperClassInfo
	{
	public:
		SuperClassInfo() : m_class(NULL), m_offset(0) {}

		const MetaClass *GetMetaClass() const {
			return m_class;
		}

		void SetMetaClass(const MetaClass *metaClass) {
			m_class = metaClass;
		}

		size_t GetOffset() const {
			return m_offset;
		}

		void SetOffset(size_t offset) {
			m_offset = offset;
		}

	private:
		const MetaClass *m_class;
		size_t m_offset;
	};

	typedef int ClassId;
	typedef std::map<std::string, int> PropertyIndexMap;
	typedef std::vector<PropertyInfo*> PropertyInfoList;
	typedef std::vector<SuperClassInfo> SuperClassInfoList;

	static const MetaClass &s_GetMetaClass();

	const MetaClass &GetMetaClass() const override;

	virtual void *Create() const = 0;

	const std::string &GetName() const {
		return m_name;
	}

	void SetName(const std::string &name) {
		m_name = name;
	}

	const std::string &GetDisplayName() const {
		return m_displayName;
	}

	void SetDisplayName(const std::string &name) {
		m_displayName = name;
	}

	ClassId GetClassId() const {
		return m_classId;
	}

	void SetClassId(ClassId classId) {
		if (m_name.empty())
		{
			std::stringstream ss;
			(ss << classId);
			m_name = ss.str();
		}
		m_classId = classId;
	}

	void SetClassId(const std::string &name) {
		m_name = name;
		m_classId = util::SuperFastHash::Fast(name.c_str());
	}

	void AddSuperClass(const MetaClass *super, size_t offset) {
		SuperClassInfo info;
		info.SetMetaClass(super);
		info.SetOffset(offset);
		m_super.push_back(info);
	}

	void AddPropertyAccessor(const std::string &name, const MetaClass &metaClass, PropertyAccessorPtr pAccessor) {
		PropertyInfo *pPropertyInfo = new PropertyInfo();
		pPropertyInfo->SetName(name);
		pPropertyInfo->SetMetaClass(&metaClass);
		pPropertyInfo->SetAccessor(pAccessor);
		m_propertyInfoList.push_back(pPropertyInfo);
		m_propertyIndexMap.insert(PropertyIndexMap::value_type(name, static_cast<int>(m_propertyInfoList.size() - 1)));
	}

	void SortPropertyAccessors()
	{
		std::sort(m_propertyInfoList.begin(), m_propertyInfoList.end(), [](PropertyInfo* & a, PropertyInfo* & b) -> bool
		{
			return a->GetName() < b->GetName();
		});

		for (unsigned int i = 0; i < m_propertyInfoList.size(); i++)
		{
			const std::string propertyName = m_propertyInfoList[i]->GetName();
			m_propertyIndexMap[propertyName] = i;
		}
	}

	const PropertyInfoList &GetProperties() const {
		return m_propertyInfoList;
	}

	const SuperClassInfoList &GetSuperClass() const {
		return m_super;
	}

	const PropertyInfo *GetPropertyInfo(const std::string &name) const;

	void *GetProperty(const std::string &name, void *obj) const;

	bool SetProperty(const std::string &name, void *obj, const void *arg) const;
	
	bool IsSubclassOf(const MetaClass &baseClass) const;

	static const MetaClass *Find(const std::string &className);

	static const MetaClass *Find(ClassId classId);

	static bool Register(const MetaClass &metaClass, ClassId classId = 0);

	template <typename T>
	static bool Register(ClassId classId = 0);
	
	bool operator<(const MetaClass &rhs) const {
		return this < &rhs;
	}

	bool operator<=(const MetaClass &rhs) const {
		return this <= &rhs;
	}

	bool operator>(const MetaClass &rhs) const {
		return this > &rhs;
	}

	bool operator>=(const MetaClass &rhs) const {
		return this >= &rhs;
	}

	bool operator==(const MetaClass &rhs) const {
		return this == &rhs;
	}

	bool operator!=(const MetaClass &rhs) const {
		return this != &rhs;
	}

protected:
	MetaClass();
	virtual ~MetaClass();

	const PropertyInfo *GetPropertyInfo_(const std::string &name) const;

	void *GetProperty_(const std::string &name, void *obj) const;

	bool SetProperty_(const std::string &name, void *obj, const void *arg) const;
	
private: 
	friend struct detail::MetaClassHelper;
	
	static Object *_Create() {
		return NULL;
	}
	
	static void _InitMetaClass(MetaClassType &metaClass);
	
	std::string m_name;
	std::string m_displayName;
	ClassId m_classId;
	PropertyInfoList m_propertyInfoList;
	PropertyIndexMap m_propertyIndexMap;
	SuperClassInfoList m_super;
};

} } }
