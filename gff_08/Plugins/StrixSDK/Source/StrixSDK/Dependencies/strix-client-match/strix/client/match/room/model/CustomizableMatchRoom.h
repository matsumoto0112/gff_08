#pragma once

#include <strix/client/match/room/model/MatchRoom.h>

namespace strix { namespace client { namespace match { namespace room { namespace model {

/**
 *  An implementation of MatchRoom with customizable properties and keys
 */
class CustomizableMatchRoom : public MatchRoom
{
public:
	STRIX_CLASS(CustomizableMatchRoom, MatchRoom)
	(
		STRIX_CLASS_ID("jp.co.soft_gear.strix.server.match.room.model.CustomizableMatchRoom")
		STRIX_PROPERTY(m_key1)
		STRIX_PROPERTY(m_key2)
		STRIX_PROPERTY(m_key3)
		STRIX_PROPERTY(m_key4)
		STRIX_PROPERTY(m_key5)
		STRIX_PROPERTY(m_key6)
		STRIX_PROPERTY(m_key7)
		STRIX_PROPERTY(m_key8)
		STRIX_PROPERTY(m_stringKey)
		STRIX_PROPERTY(m_properties)
	)
	
	CustomizableMatchRoom() {}

	virtual ~CustomizableMatchRoom() {}

	/**
	 *  Get customizable key
	 *  @returns	key
	 */
	double GetKey1() {
		return m_key1;
	}

	/**
	 *  Set customizable key
	 *  @param	key1	key
	 */
	void SetKey1(double key1) {
		m_key1 = key1;
	}

	/**
	 *  Get customizable key
	 *  @returns	key
	 */
	double GetKey2() {
		return m_key2;
	}

	/**
	 *  Set customizable key
	 *  @param	key2	key
	 */
	void SetKey2(double key2) {
		m_key2 = key2;
	}

	/**
	 *  Get customizable key
	 *  @returns	key
	 */
	double GetKey3() {
		return m_key3;
	}

	/**
	 *  Set customizable key
	 *  @param	key3	key
	 */
	void SetKey3(double key3) {
		m_key3 = key3;
	}

	/**
	 *  Get customizable key
	 *  @returns	key
	 */
	double GetKey4() {
		return m_key4;
	}
	
	/**
	 *  Set customizable key
	 *  @param	key4	key
	 */
	void SetKey4(double key4) {
		m_key4 = key4;
	}

	/**
	 *  Get customizable key
	 *  @returns	key
	 */
	double GetKey5() {
		return m_key5;
	}

	/**
	 *  Set customizable key
	 *  @param	key5	key
	 */
	void SetKey5(double key5) {
		m_key5 = key5;
	}

	/**
	 *  Get customizable key
	 *  @returns	key
	 */
	double GetKey6() {
		return m_key6;
	}

	/**
	 *  Set customizable key
	 *  @param	key6	key
	 */
	void SetKey6(double key6) {
		m_key6 = key6;
	}

	/**
	 *  Get customizable key
	 *  @returns	key
	 */
	double GetKey7() {
		return m_key7;
	}

	/**
	 *  Set customizable key
	 *  @param	key7	key
	 */
	void SetKey7(double key7) {
		m_key7 = key7;
	}

	/**
	 *  Get customizable key
	 *  @returns	key
	 */
	double GetKey8() {
		return m_key8;
	}

	/**
	 *  Set customizable key
	 *  @param	key8	key
	 */
	void SetKey8(double key8) {
		m_key8 = key8;
	}

	/**
	 *  Get string key
	 *  @returns	key
	 */
	const std::string &GetStringKey() {
		return m_stringKey;
	}

	/**
	 *  Set string key
	 *  @param	stringKey	key
	 */
	void SetStringKey(const std::string &stringKey) {
		m_stringKey = stringKey;
	}

	/**
	 *  Get this room's customizable properties
	 *  @returns	Map of strings (property names) to objects (values)
	 */
	std::map<std::string, strix::net::object::ObjectPtr> &GetProperties() {
		return m_properties;
	}

	/**
	 *  Set this room's customizable properties
	 *  @param	properties	Map of strings (property names) to objects (values)
	 */
	void SetProperties(std::map<std::string, strix::net::object::ObjectPtr> properties) {
		m_properties = std::move(properties);
	}

private:
	double m_key1;
	double m_key2;
	double m_key3;
	double m_key4;
	double m_key5;
	double m_key6;
	double m_key7;
	double m_key8;
	std::string m_stringKey;
	std::map<std::string, strix::net::object::ObjectPtr> m_properties;
};

typedef std::shared_ptr<CustomizableMatchRoom> CustomizableMatchRoomPtr;

} } } } }
