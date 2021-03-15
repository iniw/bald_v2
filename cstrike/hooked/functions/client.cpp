#include "../hooked.h"

void __fastcall hooked::frame_stage_notify( void* ecx, void* edx, frame_stage stage ) {
	static auto o_frame_stage_notify = g_detour.get< decltype( &frame_stage_notify ) >( "CHLClient::FrameStageNotify" );

	if ( !g_interfaces.m_engine->in_game( ) )
		return o_frame_stage_notify( ecx, edx, stage );

	g_cstrike.m_local = g_interfaces.m_entity_list->get< cs_player* >( g_interfaces.m_engine->get_local_player( ) );

	return o_frame_stage_notify( ecx, edx, stage );

}