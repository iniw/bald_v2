#include "backtracking.h"

#include "../../render/render.h"

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
			player_records.emplace_front( record( player ) );

		while ( player_records.size( ) > g_cstrike.time_to_ticks( 0.2f ) )
			player_records.pop_back( );

	}

}

void backtracking::think( user_cmd* cmd ) {

	const q_ang view_angles = cmd->m_view_angles;

	cs_player* player = g_cstrike.get_nearest_player( search_crosshair );
	if ( !player )
		return;

	m_player = {

		player,
		player->get_index( ) - 1

	};

	const auto player_records = m_records[ m_player.idx ];
	if ( player_records.empty( ) )
		return;

    record best_record;
	float best_fov = FLT_MAX;

	for ( const auto& record : player_records ) {

		if ( !validate_sim_time( record.m_sim_time ) )
			continue;

		const q_ang angle = g_math.calc_angle( g_cstrike.m_local->get_eye_position( ), record.m_head_pos ).sanitize( );

		const float fov = g_math.calc_fov( view_angles, angle );

		if ( fov < best_fov ) {

			best_fov = fov;
			best_record = record;

		}

	}

	if ( best_fov == FLT_MAX )
		return;

	if ( cmd->m_buttons & in_attack && g_cstrike.m_local->can_shoot( ) ) {

		apply_tick_count( cmd, best_record, m_player.ptr, true );

	}

}

void backtracking::apply_tick_count( user_cmd* cmd, record& record, cs_player* player, const bool should_draw_matrix ) {

	apply( record, player );

	cmd->m_tick_count = g_cstrike.time_to_ticks( record.m_sim_time + get_lerp( ) );

	restore( record, player );

	if ( should_draw_matrix )
		draw_matrix( record.m_matrix.data( ), player );

}

void backtracking::apply( record& record, cs_player* player ) {

	m_backup.init( player );

	record.apply( player );

}

void backtracking::restore( record& record, cs_player* player ) {

	m_backup.restore( player );

}

void backtracking::paint( ) {

	if ( !m_player.ptr )
		return;

	const auto player_records = m_records[ m_player.idx ];
	if ( player_records.empty( ) )
		return;

	vec_3 screen_pos;

	for ( const auto& record : player_records ) {

		if ( g_interfaces.m_debug_overlay->screen_position( record.m_head_pos, screen_pos ) == -1 )
			continue;

		g_render.draw_filled_rect( screen_pos.x, screen_pos.y,
			2, 2,
			color( 255, 255, 255 ),
			x_centre | y_centre );

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