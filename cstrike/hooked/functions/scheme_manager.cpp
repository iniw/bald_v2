#include "../hooked.h"

#include "../../render/render.h"

void __fastcall hooks::reload_schemes( void* ecx, void* edx ) {

	static auto o_reload_schemes = g_detour.get< decltype( &reload_schemes ) >( XOR( "CSchemeManager::ReloadSchemes" ) );

	o_reload_schemes( ecx, edx );

	g_render.setup( );

}