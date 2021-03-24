#include "detour.h"

#include "../../other/console/console.h"

bool detour::setup( std::string_view name, void* function, void* custom_function ) {

	if ( !function || !custom_function ) {

		g_console.log( log_error, XOR( "nullptrs passed to %s" ), name );
		return false;

	}

	const size_t hash = g_hash.get( name );

	m_detours[ hash ] = detour_hook( function, custom_function );

	bool result = m_detours[ hash ].init( );
	if ( !result )
		g_console.log( log_error, XOR( "failed to hook %s" ), name );

	return result;

}

void detour::unload( ) {

	// this may be called before we ever hook something 
	if ( m_detours.empty( ) )
		return;

	// this calls the deconstructor of detour_hook 
	m_detours.clear( );

}