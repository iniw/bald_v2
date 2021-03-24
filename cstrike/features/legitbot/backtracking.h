#pragma once

#include <array>
#include <deque>

#include "../../cstrike.h"

struct lag_record {

	lag_record( ) : m_sim_time( 0.f ), m_studio_model( nullptr ) { }

	lag_record( cs_player* player ) { 

		player->fixed_setup_bones( m_matrix, BONE_USED_BY_HITBOX, g_interfaces.m_globals->m_curtime );

		const auto model = player->get_model( );
		if ( model )
			m_studio_model = g_interfaces.m_model_info->get_studio_model( model );

		m_sim_time   = player->get_sim_time( );
		m_head_pos	 = player->get_hitbox_position( hitbox_head, this );
		m_origin     = player->get_origin( );
		m_abs_origin = player->get_abs_origin( );
		m_mins		 = player->get_mins( );
		m_maxs	     = player->get_maxs( );
		
	}


	inline void init( cs_player* player ) {

		m_origin = player->get_origin( );
		m_abs_origin = player->get_abs_origin( );
			
		std::memcpy( m_matrix, player->get_bone_cache( ).base( ), player->get_bone_count( ) * sizeof( matrix_3x4 ) );

		m_mins = player->get_mins( );
		m_maxs = player->get_maxs( );

	}

	inline void apply( cs_player* player ) {

		player->get_origin( ) = m_origin;
		player->set_abs_origin( m_abs_origin );

		std::memcpy( player->get_bone_cache( ).base( ), m_matrix, player->get_bone_count( ) * sizeof( matrix_3x4 ) );

		player->set_collision_bounds( m_mins, m_maxs );

	}

	float m_sim_time;
	vec_3 m_head_pos;
	vec_3 m_origin;
	vec_3 m_abs_origin;
	vec_3 m_mins;
	vec_3 m_maxs;
	studio_hdr* m_studio_model;
	matrix_3x4 m_matrix[ MAXSTUDIOBONES ];

};

struct backtracking {

	void update( );

	void run( user_cmd* cmd );

	void paint( );

	void apply_tick_count( user_cmd* cmd, lag_record* record, cs_player* player, const bool should_draw_matrix = false );

	void apply( lag_record* record, cs_player* player );

	void restore( cs_player* player );

	bool setup( );

	bool validate_sim_time( float sim_time ) {

		const float curtime = g_interfaces.m_globals->m_curtime;

		if ( sim_time < std::floorf( curtime - m_convars.sv_maxunlag->get_float( ) ) )
			return false;

		const auto net_channel_info = g_interfaces.m_engine->get_net_channel_info( );

		float correct = 0.f;

		correct += net_channel_info->get_avg_latency( 0 ); // outgoing

		correct += net_channel_info->get_avg_latency( 1 ); // incoming

		correct += get_lerp( );

		correct = std::clamp( correct, 0.f, m_convars.sv_maxunlag->get_float( ) );

		const float delta = correct - ( curtime - sim_time );

		return std::fabs( delta ) <= 0.2f;

	}

	std::array< std::deque< lag_record >, 64 > m_records;

private:

	void draw_matrix( matrix_3x4* matrix, cs_player* player );

	inline float get_lerp( ) {

		const auto ratio = std::clamp( m_convars.cl_interp_ratio->get_float( ), m_convars.sv_client_min_interp_ratio->get_float( ), m_convars.sv_client_max_interp_ratio->get_float( ) );

		return ( std::max )( m_convars.cl_interp->get_float( ), ( ratio / ( ( m_convars.sv_maxupdaterate ) ? m_convars.sv_maxupdaterate->get_float( ) : m_convars.cl_updaterate->get_float( ) ) ) );

	}


	struct {

		convar* cl_updaterate;
		convar* sv_minupdaterate;
		convar* sv_maxupdaterate;

		convar* cl_interp;
		convar* cl_interp_ratio;
		convar* sv_client_min_interp_ratio;
		convar* sv_client_max_interp_ratio;

		convar* sv_maxunlag;

		convar* sv_showlagcompensation_duration;

	} m_convars;

	struct {

		cs_player* ptr;

		int idx;

	} m_player;

	lag_record m_backup;

};

inline backtracking g_backtracking;