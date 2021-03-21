#include "legitbot.h"

#include "../../render/render.h"

aimbot_data aimbot_data::init( cs_player* player ) {

	m_ent = player;

	m_ent->fixed_setup_bones( m_matrix, BONE_USED_BY_HITBOX, g_interfaces.m_globals->m_curtime );
	
	setup_record( );

	setup_hitbox( );
	/*
	const vec_3 eye_pos = g_cstrike.m_local->get_eye_position( );

	m_ang = g_math.calc_angle( eye_pos, m_pos ).sanitize( );

	m_fov = g_math.calc_fov( g_cstrike.m_cmd->m_view_angles, eye_pos, m_pos );

	m_dmg = g_autowall.get_damage( m_pos, m_record, m_ent );
	*/

	return *this;

}

void aimbot_data::setup_record( ) {

	auto& records = g_backtracking.m_records[ m_ent->get_index( ) - 1 ];
	if ( records.empty( ) )
		return;

	float best_fov = FLT_MAX;

	for ( auto& record : records ) {

		const float fov = g_math.calc_fov( g_cstrike.m_cmd->m_view_angles, g_cstrike.m_eye_pos, record.m_head_pos );

		if ( fov < best_fov ) {

			m_record = &record;
			best_fov = fov;

		}

	}

}

void aimbot_data::setup_hitbox( ) {

	static constexpr std::array< int, 5 > hitboxes = { hitbox_head, hitbox_upper_chest, hitbox_chest, hitbox_stomach, hitbox_thorax };

	float best_fov = FLT_MAX;

	for ( int i = 0; i < hitboxes.size( ); i++ ) {

		vec_3 pos = m_ent->get_hitbox_position( hitboxes[ i ], m_matrix );

		float fov = g_math.calc_fov( g_cstrike.m_cmd->m_view_angles, g_cstrike.m_eye_pos, pos );

		float dmg = g_autowall.get_damage( pos );

		if ( fov < best_fov && dmg > 0.f ) {

			m_pos = pos;
			best_fov = fov;

		}
		
		pos = m_ent->get_hitbox_position( hitboxes[ i ], m_record );

		fov = g_math.calc_fov( g_cstrike.m_cmd->m_view_angles, g_cstrike.m_eye_pos, pos );

		dmg = g_autowall.get_damage( pos );

		if ( fov < best_fov && dmg > 0.f ) {

			m_pos = pos;
			best_fov = fov;

		}


	}

}

void legitbot::run( user_cmd* cmd ) {

	m_eye_pos = g_cstrike.m_local->get_eye_position( );

	if ( !( cmd->m_buttons & in_attack ) ) {

		m_data.reset( );
		return;

	}

	// setup all of our possible targets
	init( );

	finalize( );

	if ( cmd->m_buttons & in_attack && g_cstrike.m_local->can_shoot( ) ) {

		cmd->m_view_angles = m_data->m_ang;

		if ( m_data->m_record )
			g_backtracking.apply_tick_count( cmd, m_data->m_record, m_data->m_ent, true );

		//g_interfaces.m_engine->set_view_angles( m_data->m_ang );

	}

}

void legitbot::init( ) {

	aimbot_data temp;

	for ( int i = 1; i <= g_interfaces.m_globals->m_max_clients; i++ ) {

		cs_player* player = g_interfaces.m_entity_list->get< cs_player* >( i );

		if ( !g_cstrike.validate_player( player ) )
			continue;
		
		m_possible_targets.emplace_back( temp.init( player ) );

	}

}

vec_3 legitbot::get_best_hitbox( cs_player* player, lag_record* record ) {

	return vec_3( );

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

	g_console.log( XOR( "setup legitbot convars" ) );

	return true;

}
