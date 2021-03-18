#include "detour.h"

#include "../signatures.h"
#include "../../other/console/console.h"
#include "../../other/pattern/pattern.h"

bool detour::setup( std::string_view name, void* function, void* custom_function ) {

	if ( !function || !custom_function )
		return false;

	auto& info = m_detours[ g_hash.get( name.data( ) ) ];
	info = { function, nullptr };

	const auto hook = g_signatures.m_hook.as< bool( __cdecl* )( void*, void*, void*, int ) >( );
	if ( !hook( info.m_function, custom_function, &info.m_original, 0 ) )
		return false;

	g_console.log( XOR( "hooked %s -> 0x%x" ), name.data( ), function );

	return true;

}

void detour::unload( ) {

	auto restore = g_signatures.m_restore.as< void( __cdecl* )( void*, bool ) >( );

	for ( auto& detour : m_detours )
		restore( detour.second.m_function, false );

}