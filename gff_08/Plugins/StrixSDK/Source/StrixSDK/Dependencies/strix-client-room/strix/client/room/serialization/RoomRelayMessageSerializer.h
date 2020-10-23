#pragma once

#include <strix/net/object/MetaClass.h>
#include <strix/net/io/Encoder.h>
#include <strix/net/io/Decoder.h>
#include <strix/net/serialization/serializer/GenericObjectSerializer.h>

namespace strix { namespace client { namespace room { namespace serialization {

/**
 *  Performs serialization and deserialization of objects for standard relay messages
 */
class RoomRelayMessageSerializer : public strix::net::serialization::serializer::GenericObjectSerializer
{
public:

	/**
	 *  Serialize the properties of the object into the encoder
	 *  @param	encoder	The encoder to write to
	 *  @param	metaClass	The class of the object
	 *  @param	value	The object to serialize
	 *  @returns	Whether the serialization was successful
	 */
	bool SerializeProperties(strix::net::io::Encoder &encoder, const strix::net::object::MetaClass &metaClass, const strix::net::object::Object *value) override;

	/**
	 *  Deserialize the properties from the decoder into the object
	 *  @param	decoder	The decoder to write from
	 *  @param	metaClass	The class of the object
	 *  @param	value	The object to deserialize to
	 *  @returns	Whether the deserialization was successful
	 */
	bool DeserializeProperties(strix::net::io::Decoder &decoder, const strix::net::object::MetaClass &metaClass, strix::net::object::Object *&value) override;
};

} } } }
