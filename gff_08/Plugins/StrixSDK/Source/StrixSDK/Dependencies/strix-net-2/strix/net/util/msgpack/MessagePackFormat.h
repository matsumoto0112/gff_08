#pragma once

namespace strix { namespace net { namespace util { namespace msgpack {

enum class MessagePackFormat
{
	Invalid = -1,
	Nil = 0,
	//Unused = 1,
	False = 2,
	True,
	Bin8,
	Bin16,
	Bin32,
	Ext8,
	Ext16,
	Ext32,
	Float32,
	Float64,
	Uint8,
	Uint16,
	Uint32,
	Uint64,
	Int8,
	Int16,
	Int32,
	Int64,
	FixExt1,
	FixExt2,
	FixExt4,
	FixExt8,
	FixExt16,
	Str8,
	Str16,
	Str32,
	Array16,
	Array32,
	Map16,
	Map32,
	PositiveFixInt,
	NegativeFixInt,
	FixMap,
	FixArray,
	FixStr,
};

} } } }
