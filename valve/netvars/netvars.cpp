#include "netvars.h"

#include "../interfaces/interfaces.h"

#include "../../other/console/console.h"
#include "../../other/hash/hash.h"
#include "../../other/file_system/file_system.h"

bool netvars::setup( ) {

	auto list = g_interfaces.m_client->get_all_classes( );	
	if ( !list )
		return false;
	/*
	char path[ MAX_PATH + 1 ]; strcpy_s( path, g_file_system.m_logs_path );
	g_winapi.path_append( path, XOR( "netvars.txt" ) );

	m_file.open( path, std::ios::out | std::ios::trunc );
	*/

	while ( list != nullptr ) {

		store( list->m_recv_table->m_net_table_name, list->m_recv_table );

		list = list->m_next;

	}

	//m_file.close( );

	g_console.log( log_completion, XOR( "setup netvars" ) );

	return true;

}

void netvars::store( std::string_view name, recv_table* table, size_t offset ) {

	// s/o Rimes big dawg da man ..
	recv_prop* prop; recv_table* child;
	std::string netvar; size_t hash;

	for ( auto i = 0; i < table->m_props; ++i ) {

		prop = &table->m_props_pointer[ i ];
		child = prop->m_data_table;

		if ( child && child->m_props > 0 )
			store( name, child, prop->m_offset + offset );

		auto variable = prop->m_var_name;

		netvar = std::string( name.data( ) ) + "->" + variable;
		hash = g_hash.get( netvar.c_str( ) );

		if ( !m_offsets[ hash ] ) {

			m_offsets[ hash ] = prop->m_offset + offset;

			//m_file << netvar << XOR( " = 0x" ) << std::hex << m_offsets[ hash ] << std::endl;

		}

	}

}

size_t netvars::find_in_datamap( data_map* map, const size_t hash ) {

	while ( map != nullptr ) {

		for ( auto i = 0; i < map->data_fields; ++i ) {

			const char* field_name = map->data_desc[ i ].field_name;
			if ( !field_name )
				continue;

			if ( g_hash.get( field_name ) == hash )
				return map->data_desc[ i ].field_offset[ TD_OFFSET_NORMAL ];

			if ( map->data_desc[ i ].field_type == FIELD_EMBEDDED )
				if ( map->data_desc[ i ].type_description != nullptr )
					if ( const auto offset = find_in_datamap( map->data_desc[ i ].type_description, hash ); offset )
						return offset;

		}

		map = map->base_map;
	}

	return 0U;

}
