#include "../hooked.h"

void __fastcall hooked::frame_stage_notify( void* ecx, void* edx, frame_stage stage ) {
	static auto o_frame_stage_notify = g_detour.get< decltype( &frame_stage_notify ) >( XOR( "CHLClient::FrameStageNotify" ) );

	if ( !g_interfaces.m_engine->in_game( ) )
		return o_frame_stage_notify( ecx, edx, stage );

	return o_frame_stage_notify( ecx, edx, stage );

}