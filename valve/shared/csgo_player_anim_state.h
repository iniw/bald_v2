#pragma once

struct animstate_pose_param_cache {

	bool m_initialized; // 0
	byte pad0[ 0x3 ]; // 1
	int m_index; // 4
	const char* m_name; // 8

	inline bool init( base_animating* player, const char* pose_param_name ) {

		g_interfaces.m_mdl_cache->begin_lock( );

		m_name = pose_param_name;
		m_index = player->lookup_pose_parameter( pose_param_name );

		if ( m_index != 1 )
			m_initialized = true;

		g_interfaces.m_mdl_cache->end_lock( );

		return m_initialized;

	}

	inline void set_value( base_animating* player, float value ) {

		if ( !m_initialized )
			init( player, m_name );

		if ( m_initialized && player ) {

			g_interfaces.m_mdl_cache->begin_lock( );

			player->set_pose_parameter( m_index, value );

			g_interfaces.m_mdl_cache->end_lock( );

		}

	}

}; // size: 12

struct csgo_player_anim_state {

	inline auto setup_velocity( ) {

		auto function = g_signatures.m_setup_velocity.as< void( __thiscall* )( void* ) >( );

		return function( this );

	}

	inline auto setup_aim_matrix( ) {

		auto function = g_signatures.m_setup_aim_matrix.as< void( __thiscall* )( void* ) >( );

		return function( this );

	}

	inline auto setup_weapon_action( ) {

		auto function = g_signatures.m_setup_weapon_action.as< void( __thiscall* )( void* ) >( );

		return function( this );

	}

	inline auto setup_movement( ) {

		auto function = g_signatures.m_setup_movement.as< void( __thiscall* )( void* ) >( );

		return function( this );

	}

	inline auto setup_alive_loop( ) {

		auto function = g_signatures.m_setup_alive_loop.as< void( __thiscall* )( void* ) >( );

		return function( this );

	}

	inline auto setup_whole_body_action( ) {

		auto function = g_signatures.m_setup_whole_body_action.as< void( __thiscall* )( void* ) >( );

		return function( this );

	}

	inline auto setup_flashed_reaction( ) {

		// to do

	}

	inline auto setup_flinch( ) {

		auto function = g_signatures.m_setup_flinch.as< void( __thiscall* )( void* ) >( );

		return function( this );

	}

	inline auto setup_lean( ) {

		auto function = g_signatures.m_setup_lean.as< void( __thiscall* )( void* ) >( );

		return function( this );

	}

	inline auto cache_sequences( ) {

		auto function = g_signatures.m_cache_sequences.as< bool( __thiscall* )( void* ) >( );

		return function( this );

	}

	inline auto increment_layer_cycle( int layer_index, bool allow_loop ) {

		auto function = g_signatures.m_increment_layer_cycle.as< void( __thiscall* )( void*, int, bool ) >( );

		return function( this, layer_index, allow_loop );

	}

	inline auto increment_layer_weight( int layer_index ) {

		auto function = g_signatures.m_increment_layer_weight.as< void( __thiscall* )( void*, int ) >( );

		return function( this, layer_index );

	}

	char pad0[ 0x4 ]; // 0
	bool m_first_run_since_init; // 4
	char pad1[ 0x5b ]; // 5
	cs_player* m_player; // 96
	weapon_cs_base* m_weapon; // 100
	weapon_cs_base* m_weapon_last; // 104
	float m_last_update_time; // 108
	int   m_last_update_frame; // 112
	float m_last_update_increment; // 116
	float m_eye_yaw; // 120
	float m_eye_pitch; // 124
	float m_foot_yaw; // 128
	float m_foot_yaw_last; // 132
	float m_move_yaw; // 136
	float m_move_yaw_ideal; // 140
	float m_move_yaw_current_to_ideal; // 144
	float m_time_to_align_lower_body; // 148
	float m_primary_cycle; // 152
	float m_move_weight; // 156
	float m_move_weight_smoothed; // 160
	float m_anim_duck_amount; // 164
	float m_duck_additional; // 168
	float m_recrouch_weight; // 172
	vec_3 m_position_current; // 176
	vec_3 m_position_last; // 188
	vec_3 m_velocity; // 200
	vec_3 m_velocity_normalized; // 212
	vec_3 m_velocity_normalized_non_zero; // 224
	float m_velocity_length_xy; // 236
	float m_velocity_length_z; // 240
	float m_speed_as_portion_of_run_top_speed; // 244
	float m_speed_as_portion_of_walk_top_speed; // 248
	float m_speed_as_portion_of_crouch_top_speed; // 252
	float m_duration_moving; // 256
	float m_duration_still; // 260
	bool  m_on_ground; // 264
	bool  m_landing; // 265
	char  pad2[ 0x12 ]; // 266
	float m_walk_to_run_transition; // 284
	char  pad3[ 0x4 ]; // 288
	float m_in_air_smooth_value; // 292
	bool  m_on_ladder; // 296
	char  pad4[ 0x3 ]; // 297
	float m_ladder_weight; // 300
	char  pad5[ 0x2c ]; // 304
	vec_3 m_velocity_last; // 348
	char  pad6[ 0x45 ]; // 360
	bool  m_player_is_accelerating; // 429
	char  pad7[ 0x2 ]; // 430
	animstate_pose_param_cache m_pose_param_mappings[ 20 ]; // 432
	float m_duration_move_weight_is_too_high; // 672
	float m_static_approach_speed; // 676
	int   m_previous_move_state; // 680
	float m_stutter_step; // 684
	char  pad8[ 0x80 ]; // 688
	float m_aim_yaw_min; // 816
	float m_aim_yaw_max; // 820
	float m_aim_pitch_min; // 824
	float m_aim_pitch_max; // 828

};