#pragma once

#include <strix/net/object/Object.h>

namespace strix { namespace client { namespace core { namespace message {

/**
 *  Base parameter message class
 *  
 *  Parameter classes can take a number of MetaClasses representing the Objects they can operate on
 */
class ParameterMessage : public strix::net::object::Object
{
public:
	STRIX_CLASS(ParameterMessage, Object)
	(
		STRIX_CLASS_ID("jp.co.soft_gear.strix.server.core.message.ParameterMessage")
		STRIX_PROPERTY(m_parameterClasses)
	)

    typedef strix::net::object::MetaClass MetaClass;

	ParameterMessage() : m_parameterClasses(1) {
	}

	/**
	 *  Construct a ParameterMessage that can operate on the given number of classes
	 *  @param	numClasses	The number of MetaClasses
	 */
	ParameterMessage(int numClasses) : m_parameterClasses(numClasses) {
	}

	/**
	 *  Construct a ParameterMessage that can operate on the given class
	 *  @param	parameterClass	The MetaClass that can be operated on
	 */
	ParameterMessage(const MetaClass &parameterClass) : m_parameterClasses(1) {
	    m_parameterClasses[0] = &parameterClass;
	}

	/**
	 *  Construct a ParameterMessage that can operate on the given classes
	 *  @param	parameterClasses	The MetaClasses that can be operated on
	 */
	ParameterMessage(const std::vector<const MetaClass *> &parameterClasses) : m_parameterClasses(parameterClasses) {
	}

	/**
	 *  Get the first parameter class of this message 
	 *  @returns	The parameter class
	 */
	const MetaClass &GetParameterClass() const {
		return *m_parameterClasses[0];
	}

	/**
	 *  Get the parameter class of this message at the given index
	 *  @param	index	The index into the list of parameter classes
	 *  @returns	The parameter class
	 */
	const MetaClass &GetParameterClass(const size_t index) const {
		return *m_parameterClasses[index];
	}

	/**
	 *  Get the list of parameter classes of this message
	 *  @returns	The list of parameter classes
	 */
	std::vector<const MetaClass *> &GetParameterClasses() {
		return m_parameterClasses;
	}

	/**
	 *  Set the first parameter class of this message
	 *  @param	parameterClass	The class to set
	 */
	void SetParameterClass(const MetaClass& parameterClass)
	{
		if (m_parameterClasses.empty())
		{
			m_parameterClasses.push_back(&parameterClass);
		}
		else
		{
			m_parameterClasses[0] = &parameterClass;
		}
	}

	/**
	 *  Set the parameter class of this message at the given index
	 *  @param	index	The index to set at
	 *  @param	parameterClass	The class to set
	 */
	void SetParameterClass(const size_t index, const MetaClass &parameterClass) {
		if (m_parameterClasses.size() == index)
		{
			m_parameterClasses.push_back(&parameterClass);
		}
		else {
			m_parameterClasses[index] = &parameterClass;
		}
	}

private:
	std::vector<const MetaClass *> m_parameterClasses;
};

} } } }

