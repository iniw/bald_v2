#include "../hooked.h"

bool __fastcall hooked::create_move( cs_player* ecx, void* edx, float input_sample_time, user_cmd* cmd ) {

	static auto o_create_move = g_detour.get< decltype( &create_move ) >( XOR( "C_BasePlayer::CreateMove" ) );

	if ( cmd->m_command_number == 0 )
		return o_create_move( ecx, edx, input_sample_time, cmd );

	if ( o_create_move( ecx, edx, input_sample_time, cmd ) )
		g_interfaces.m_prediction->set_local_view_angles( cmd->m_view_angles );

	q_ang old_view_angles = cmd->m_view_angles;

	g_cstrike.m_cmd = cmd;

	g_movement.bhop( cmd );
		
	g_engine_prediction.start( cmd ); {

		g_legitbot.run( cmd );
		/*
		trace trace;

		q_ang view_angles = cmd->m_view_angles;

		vec_3 start, end, foward;
		g_math.angle_vectors( view_angles, &foward );

		weapon_cs_base* weapon = g_interfaces.m_entity_list->get< weapon_cs_base* >( g_cstrike.m_local->get_active_weapon( ) );

		if ( weapon ) {

			cs_weapon_info* weapon_data = weapon->get_cs_wpn_data( );

			if ( weapon_data ) {

				start = g_cstrike.m_local->get_eye_position( );
				foward *= weapon_data->m_range;
				end = start + foward;

				ray ray( start, end );
				trace_filter filter( g_cstrike.m_local );
				g_interfaces.m_trace->trace_ray( ray, MASK_SHOT | CONTENTS_HITBOX, &filter, &trace );

				if ( trace.m_hit_entity ) {
					
					g_console.log( trace.m_hit_entity->get_class_name( ) );

				} 

				if ( trace.m_hit_entity && trace.m_hitbox ) {

					g_console.log( "hit hitbox number %d", trace.m_hitbox );

				} 
				
				if ( trace.m_hit_entity && trace.m_hitgroup ) {

					g_console.log( "hit hitgroup number %d", trace.m_hitgroup );

				}

			}
			

		}	
		*/

	}
	g_engine_prediction.end( cmd );

	g_movement.correct( cmd, old_view_angles );

	cmd->m_view_angles.sanitize( );

	return false;

}

bool __cdecl hooked::glow_effect_spectators( base_player* this_player, base_player* local_player, glow_styles& glow_style, vec_3& color, float& alpha_start, float& alpha, float& time_start, float& time_target, bool& animate ) {

	if ( !this_player->is_enemy( local_player ) )
		return false;

	glow_style = glow_style_default;

	color.x = 1.f;
	color.y = 1.f;
	color.z = 1.f;

	alpha = 0.3f;

	return true;

}