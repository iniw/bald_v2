#include "../hooks.h"

void __fastcall hooks::level_init_pre_entity( void* ecx, void* edx, char* map ) {

	static auto o_level_init_pre_entity = g_detour.get< decltype( &level_init_pre_entity ) >( XOR( "CHLClient::LevelInitPreEntity" ) );

	return o_level_init_pre_entity( ecx, edx, map );

}

void __fastcall hooks::frame_stage_notify( void* ecx, void* edx, frame_stage stage ) {

	static auto o_frame_stage_notify = g_detour.get< decltype( &frame_stage_notify ) >( XOR( "CHLClient::FrameStageNotify" ) );

	g_cstrike.m_local = g_interfaces.m_entity_list->get< cs_player* >( g_interfaces.m_engine->get_local_index( ) );

	if ( !g_cstrike.m_local || !g_interfaces.m_engine->in_game( ) )
		return o_frame_stage_notify( ecx, edx, stage );

	switch ( stage ) {

	case stage_net_update_end: {

		g_backtracking.update( );

		break;

	}
	default:
		break;

	}

	return o_frame_stage_notify( ecx, edx, stage );

}

void __fastcall hooks::level_shutdown( void* ecx, void* edx ) {

	static auto o_level_shutdown = g_detour.get< decltype( &level_shutdown ) >( XOR( "CHLClient::LevelShutdown" ) );

	g_cstrike.m_local = nullptr;

	return o_level_shutdown( ecx, edx );

}