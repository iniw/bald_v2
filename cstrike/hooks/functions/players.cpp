#include "../hooks.h"

bool __fastcall hooks::create_move( cs_player* ecx, void* edx, float input_sample_time, user_cmd* cmd ) {

	static auto o_create_move = g_detour.get< decltype( &create_move ) >( XOR( "C_CSPlayer::CreateMove" ) );

	if ( !cmd->m_command_number )
		return o_create_move( ecx, edx, input_sample_time, cmd );

	if ( o_create_move( ecx, edx, input_sample_time, cmd ) ) {

		g_interfaces.m_prediction->set_local_view_angles( cmd->m_view_angles );
		g_interfaces.m_engine->set_view_angles( cmd->m_view_angles );

	}

	q_ang old_view_angles = cmd->m_view_angles;

	g_cstrike.m_local = ecx; g_cstrike.m_cmd = cmd; g_cstrike.m_eye_pos = g_cstrike.m_local->get_eye_position( );

	g_movement.bhop( cmd );
	
	g_engine_prediction.update( );

	g_engine_prediction.start( cmd ); {

		//g_legitbot.run( cmd );

		g_backtracking.run( cmd );

	}
	g_engine_prediction.end( cmd );

	g_movement.correct( cmd, old_view_angles );

	cmd->m_view_angles.sanitize( );

	return false;

}

bool __fastcall hooks::should_skip_animation_frame( void* ecx, void* edx ) {

	return false;

}

bool __cdecl hooks::glow_effect_spectators( base_player* this_player, base_player* local_player, glow_styles& glow_style, vec_3& color, float& alpha_start, float& alpha, float& time_start, float& time_target, bool& animate ) {

	if ( !this_player->is_enemy( local_player ) )
		return false;

	glow_style = glow_style_default;

	color.x = 1.f;
	color.y = 1.f;
	color.z = 1.f;

	alpha = 0.4f;

	return true;

}