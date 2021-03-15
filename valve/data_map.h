#pragma once

#include <cstddef>

enum field_types {

	FIELD_VOID = 0,			
	FIELD_FLOAT,			
	FIELD_STRING,			
	FIELD_VECTOR,			
	FIELD_QUATERNION,		
	FIELD_INTEGER,			
	FIELD_BOOLEAN,			
	FIELD_SHORT,			
	FIELD_CHARACTER,		
	FIELD_COLOR32,			
	FIELD_EMBEDDED,			
	FIELD_CUSTOM,			
	FIELD_CLASSPTR,			
	FIELD_EHANDLE,			
	FIELD_EDICT,			
	FIELD_POSITION_VECTOR,	
	FIELD_TIME,				
	FIELD_TICK,				
	FIELD_MODELNAME,		
	FIELD_SOUNDNAME,		
	FIELD_INPUT,			
	FIELD_FUNCTION,			
	FIELD_VMATRIX,			
	FIELD_VMATRIX_WORLDSPACE,
	FIELD_MATRIX3X4_WORLDSPACE,
	FIELD_INTERVAL,	
	FIELD_MODELINDEX,		
	FIELD_MATERIALINDEX,	
	FIELD_VECTOR2D,			
	FIELD_INTEGER64,		
	FIELD_VECTOR4D,			
	FIELD_TYPECOUNT
};

enum {

	TD_OFFSET_NORMAL = 0,
	TD_OFFSET_PACKED = 1,
	TD_OFFSET_COUNT

};

struct data_map;

struct type_description {

	field_types			field_type;
	const char*         field_name;
	int					field_offset[ TD_OFFSET_COUNT ];
	unsigned short		field_size;
	short				flags;
	std::byte			pad0[ 0xC ];
	data_map*           type_description;
	std::byte			pad1[ 0x18 ];

};

struct data_map {

	type_description*   data_desc;
	int					data_fields;
	const char*         data_class_name;
	data_map*           base_map;
	bool				chains_validated;
	bool				packed_offsets_computed;
	int					packed_size;

};