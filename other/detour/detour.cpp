#include "detour.h"

#include "../../other/console/console.h"

bool detour::setup( std::string_view name, void* function, void* custom_function ) {

	if ( !function || !custom_function ) {

		g_console.log( log_error, XOR( "nullptrs passed to %s" ), name );
		return false;

	}

	const size_t hash = g_hash.get( name );

	m_detours[ hash ] = detour_hook( function, custom_function );

	if ( !m_detours[ hash ].init( ) ) {

		g_console.log( log_error, XOR( "failed to hook %s" ), name );
		return false;

	}

	return true;

}

void detour::unload( ) {

	m_detours.clear( );

}