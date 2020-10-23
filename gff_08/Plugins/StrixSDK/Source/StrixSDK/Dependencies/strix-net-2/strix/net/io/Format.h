#pragma once

namespace strix { namespace net { namespace io {

enum class Format
{
	Invalid = -1,
	Null = 0,
	Boolean = 1,
	Byte = 2,
	Short = 3,
	Int = 4,
	Int64 = 5,
	UByte = 6,
	UShort = 7,
	UInt = 8,
	UInt64 = 9,
	Float = 10,
	Double = 11,
	Char = 12,
	String = 13,
	Binary = 14,
	Object = 15,
	Array = 16,
	List = 17,
	Set = 18,
	Map = 19,
	Date = 20,
	GenericObject = 21
};


} } }
