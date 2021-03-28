#include "../hooks.h"

bool __fastcall hooks::override_config( void* ecx, void* edx, material_system_config* cfg, bool update ) {

	static auto o_override_config = g_detour.get< decltype( &override_config ) >( XOR( "CMaterialSystem::OverrideConfig" ) );

	return o_override_config( ecx, edx, cfg, update );

}