#pragma once

#include <strix/client/core/model/manager/filter/TextFilterType.h>
#include <strix/net/object/Object.h>

namespace strix { namespace client { namespace core { namespace model { namespace manager { namespace filter {

class TextFilter : public strix::net::object::Object {
public:
	STRIX_CLASS(TextFilter, Object)
	(
		STRIX_CLASS_ID("jp.co.soft_gear.strix.server.core.model.manager.filter.TextFilter")
		STRIX_PROPERTY_TYPED(m_type, int)
		STRIX_PROPERTY(m_value)
	)

	TextFilter() {}

	TextFilter(TextFilterType type) : m_type(type) {}

	TextFilter(TextFilterType type, const std::string &value) {
		m_type = type;
		m_value = value;
	}

	static std::shared_ptr<TextFilter> Text(std::string value)
	{
		return std::make_shared<TextFilter>(TextFilterType::Text, value);
	}

	static std::shared_ptr<TextFilter> SingleCharacterWildcard()
	{
		return std::make_shared<TextFilter>(TextFilterType::SingleCharacterWildcard);
	}

	static std::shared_ptr<TextFilter> MultipleCharacterWildcard()
	{
		return std::make_shared<TextFilter>(TextFilterType::MultipleCharacterWildcard);
	}
	
	virtual ~TextFilter() {}
	
	TextFilterType GetType() {
		return m_type;
	}
	
	void SetType(const TextFilterType type) {
		m_type = type;
	}
	
	std::string &GetValue() {
		return m_value;
	}

	void SetValue(const std::string &value) {
		m_value = value;
	}

	int Compare(const Object &rhs) const override
	{
		const net::object::MetaClass &metaClass = GetMetaClass();
		const net::object::MetaClass &metaClass2 = rhs.GetMetaClass();
	
		if (&metaClass > &metaClass2)
			return 1;
		if (&metaClass < &metaClass2)
			return -1;

		const TextFilter & other = static_cast<const TextFilter &>(rhs);

		if (m_type > other.m_type)
			return 1;
		if (m_type < other.m_type)
			return -1;
		
		if (m_value > other.m_value)
			return 1;
		if (m_value < other.m_value)
			return -1;

		return 0;
	}

private:
	TextFilterType m_type;
	std::string m_value;
};

typedef std::shared_ptr<TextFilter> TextFilterPtr;
typedef std::list<TextFilterPtr> TextFilterList;

} } } } } }
