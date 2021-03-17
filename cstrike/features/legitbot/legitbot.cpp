#include "legitbot.h"

#include "../../render/render.h"

void legitbot::run( user_cmd* cmd ) {

	m_ative = false;

	m_data = get_data( cmd );
	if ( !m_data )
		return;

	finalize( );

	if ( cmd->m_buttons & in_attack && g_cstrike.m_local->can_shoot( ) ) {

		m_ative = true;

		cmd->m_view_angles = m_data->m_ang;

		if ( m_data->m_record.m_sim_time )
			g_backtracking.apply_tick_count( cmd, m_data->m_record, m_data->m_ent );

		//g_interfaces.m_engine->set_view_angles( m_data->m_ang );

	}

}

std::unique_ptr< aimbot_data > legitbot::get_data( user_cmd* cmd ) {

	aimbot_data best_data;
	best_data.m_fov = FLT_MAX;

	aimbot_data* temp_data = new aimbot_data; // no allocation on the stack around here.

	for ( int i = 1; i <= g_interfaces.m_globals->m_max_clients; i++ ) {

		cs_player* player = g_interfaces.m_entity_list->get< cs_player* >( i );

		if ( !g_cstrike.validate_player( player ) )
			continue;

		temp_data->init( player );

		if ( temp_data->m_fov < best_data.m_fov && temp_data->m_dmg > 0.f ) {

			best_data = *temp_data;

		}

		auto& player_records = g_backtracking.m_records[ player->get_index( ) - 1 ];
		if ( player_records.empty( ) )
			continue;

		for ( auto& record : player_records ) {

			if ( !g_backtracking.validate_sim_time( record.m_sim_time ) )
				continue;

			temp_data->init( player, &record );

			if ( temp_data->m_fov < best_data.m_fov && temp_data->m_dmg > 0.f ) {

				best_data = *temp_data;

			}

		}

	}

	delete temp_data;

	return best_data.m_ent ? std::make_unique< aimbot_data >( best_data ) : nullptr;

}

void legitbot::finalize( ) {

	m_data->m_ang -= g_cstrike.m_local->get_punch( ) * m_convars.weapon_recoil_scale->get_float( );
	m_data->m_ang.sanitize( );

}

void legitbot::paint( ) {

	if ( !m_data )
		return;
	
	vec_3 screen_head_pos;
	int w, h;

	g_interfaces.m_engine->get_screen_size( w, h );

	if ( g_interfaces.m_debug_overlay->screen_position( m_data->m_pos, screen_head_pos ) == -1 )
		return;

	g_render.draw_line( w / 2, h / 2, 
		screen_head_pos.x, screen_head_pos.y, 
		color( 255, 255, 255 ) );

	g_render.draw_text( g_render.m_fonts.primary, 
		w / 2, h / 2 - 5, 
		g_render.format_text( XOR( "dmg = %.2f" ), m_data->m_dmg ), 
		color( 255, 255, 255 ), 
		x_centre | y_centre );

}

bool legitbot::setup( ) {

	if ( m_convars.weapon_recoil_scale = g_interfaces.m_convar->find_var( XOR( "weapon_recoil_scale" ) ); !m_convars.weapon_recoil_scale )
		return false;

	return true;

}
