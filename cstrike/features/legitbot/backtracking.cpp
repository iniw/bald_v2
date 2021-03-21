#include "backtracking.h"

#include "../../render/render.h"
#include "legitbot.h"

void backtracking::update( ) {

	for ( int i = 1; i <= g_interfaces.m_globals->m_max_clients; i++ ) {

		auto& player_records = m_records[ i - 1 ];

		cs_player* player = g_interfaces.m_entity_list->get< cs_player* >( i );

		if ( !g_cstrike.validate_player( player ) ) {
			
			if ( player_records.size( ) )
				player_records.clear( );

			continue;

		}

		if ( player->get_old_sim_time( ) == player->get_sim_time( ) )
			continue;

		if ( validate_sim_time( player->get_sim_time( ) ) )
			player_records.emplace_front( lag_record( player ) );

		while ( player_records.size( ) > g_cstrike.time_to_ticks( 0.2f ) )
			player_records.pop_back( );

	}

}

void backtracking::run( user_cmd* cmd ) {

	if ( g_legitbot.m_data )
		return;

	lag_record best_record;
	float best_fov = FLT_MAX;

	for ( int i = 1; i <= g_interfaces.m_globals->m_max_clients; i++ ) {

		cs_player* player = g_interfaces.m_entity_list->get< cs_player* >( i );

		if ( !g_cstrike.validate_player( player ) )
			continue;

		auto& player_records = g_backtracking.m_records[ player->get_index( ) - 1 ];
		if ( player_records.empty( ) )
			continue;

		for ( auto& record : player_records ) {

			if ( !g_backtracking.validate_sim_time( record.m_sim_time ) )
				continue;

			const float fov = g_math.calc_fov( g_cstrike.m_cmd->m_view_angles, g_cstrike.m_eye_pos, record.m_eye_pos );

			if ( fov < best_fov ) {

				best_record = record;

			}

		}

	}

	if ( best_fov == FLT_MAX )
		return;

	if ( cmd->m_buttons & in_attack && g_cstrike.m_local->can_shoot( ) ) {

		apply_tick_count( cmd, &best_record, m_player.ptr, true );

	}

}

void backtracking::apply_tick_count( user_cmd* cmd, lag_record* record, cs_player* player, const bool should_draw_matrix ) {

	if ( !record )
		return;

	apply( record, player );

	cmd->m_tick_count = g_cstrike.time_to_ticks( record->m_sim_time + get_lerp( ) );

	restore( player );

	if ( should_draw_matrix )
		draw_matrix( record->m_matrix, player );

}

void backtracking::apply( lag_record* record, cs_player* player ) {

	if ( !record )
		return;

	m_backup.init( player );

	record->apply( player );

}

void backtracking::restore( cs_player* player ) {

	m_backup.apply( player );

}

void backtracking::paint( ) {

	vec_3 screen_pos;

	for ( const auto& player_records : m_records ) {

		if ( !player_records.size( ) )
			continue;

		for ( const auto& record : player_records ) {

			if ( g_interfaces.m_debug_overlay->screen_position( record.m_eye_pos, screen_pos ) == -1 )
				continue;

			g_render.draw_filled_rect( screen_pos.x, screen_pos.y,
				2, 2,
				color( 255, 255, 255 ),
				x_centre | y_centre );
		}

	}

}

void backtracking::draw_matrix( matrix_3x4* matrix, cs_player* player ) {

	const auto player_model = player->get_model( );
	if ( !player_model )
		return;

	const auto studio_model = g_interfaces.m_model_info->get_studio_model( player_model );
	if ( !studio_model )
		return;

	const auto set = studio_model->get_hitbox_set( 0 );
	if ( !set )
		return;

	studio_bbox* hitbox = nullptr;
	vec_3 min, max;

	for ( int i = 0; i < set->m_hitboxes; i++ ) {

		hitbox = set->get_hitbox( i );
		if ( !hitbox )
			continue;

		min = g_math.vector_transform( hitbox->m_bb_min, matrix[ hitbox->m_bone ] );
		max = g_math.vector_transform( hitbox->m_bb_max, matrix[ hitbox->m_bone ] );

		g_interfaces.m_debug_overlay->draw_pill( min, max, hitbox->m_radius, color( 255, 255, 255 ), m_convars.sv_showlagcompensation_duration->get_float( ) );

	}

}

bool backtracking::setup( ) {

	if ( m_convars.cl_updaterate = g_interfaces.m_convar->find_var( XOR( "cl_updaterate" ) ); !m_convars.cl_updaterate )
		return false;

	if ( m_convars.sv_minupdaterate = g_interfaces.m_convar->find_var( XOR( "sv_minupdaterate" ) ); !m_convars.sv_minupdaterate )
		return false;

	if ( m_convars.sv_maxupdaterate = g_interfaces.m_convar->find_var( XOR( "sv_maxupdaterate" ) ); !m_convars.sv_maxupdaterate )
		return false;

	if ( m_convars.cl_interp = g_interfaces.m_convar->find_var( XOR( "cl_interp" ) ); !m_convars.cl_interp )
		return false;

	if ( m_convars.cl_interp_ratio = g_interfaces.m_convar->find_var( XOR( "cl_interp_ratio" ) ); !m_convars.cl_interp_ratio )
		return false;

	if ( m_convars.sv_client_min_interp_ratio = g_interfaces.m_convar->find_var( XOR( "sv_client_min_interp_ratio" ) ); !m_convars.sv_client_min_interp_ratio )
		return false;

	if ( m_convars.sv_client_max_interp_ratio = g_interfaces.m_convar->find_var( XOR( "sv_client_max_interp_ratio" ) ); !m_convars.sv_client_max_interp_ratio )
		return false;

	if ( m_convars.sv_maxunlag = g_interfaces.m_convar->find_var( XOR( "sv_maxunlag" ) ); !m_convars.sv_maxunlag )
		return false;

	if ( m_convars.sv_showlagcompensation_duration = g_interfaces.m_convar->find_var( XOR( "sv_showlagcompensation_duration" ) ); !m_convars.sv_showlagcompensation_duration )
		return false;

	return true;

}