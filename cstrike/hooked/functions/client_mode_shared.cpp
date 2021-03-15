#include "../hooked.h"

float __fastcall hooked::get_view_model_fov( void* ecx, void* edx ) {

	static auto o_get_view_model_fov = g_detour.get< decltype( &get_view_model_fov ) >( "ClientModeShared::GetViewModelFOV" );

	return o_get_view_model_fov( ecx, edx );

}