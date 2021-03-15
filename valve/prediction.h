#pragma once

#include "../other/math/vec_3.h"
#include "../other/math/q_ang.h"

struct user_cmd;

struct move_data {

	bool	  m_first_run_of_functions : 1;
	bool	  m_game_code_moved_player : 1;
	bool	  m_no_air_control : 1;
	uintptr_t m_player_handle;
	int		  m_impulse_command;
	q_ang	  m_view_angles;
	q_ang	  m_abs_view_angles;
	int		  m_buttons;
	int		  m_old_buttons;
	float	  m_forward_move;
	float	  m_side_move;
	float	  m_up_move;
	float	  m_max_speed;
	float	  m_client_max_speed;
	vec_3	  m_velocity;
	vec_3	  m_trailing_velocity;
	float	  m_trailing_velocity_time;
	vec_3	  m_angles;
	vec_3	  m_old_angles;
	float	  m_out_step_height;
	vec_3	  m_out_wish_vel;
	vec_3	  m_out_jump_vel;
	vec_3	  m_constraint_center;
	float	  m_constraint_radius;
	float	  m_constraint_width;
	float	  m_constraint_speed_factor;
	bool	  m_constraint_past_radius;
	vec_3	  m_abs_origin;

};

struct base_entity;

struct move_helper {

	inline void set_host( base_entity* entity ) {

		g_utils.call_v_func< void >( this, 1, entity );

	}

	inline void process_impacts( ) {

		g_utils.call_v_func< void >( this, 4 );

	}

};

struct game_movement {

	inline void process_movement( base_entity* entity, move_data* move ) {

		g_utils.call_v_func< void >( this, 1, entity, move );

	}

	inline void reset( ) {

		g_utils.call_v_func< void >( this, 2 );

	}

	inline void start_track_prediction_errors( base_entity* entity ) {

		g_utils.call_v_func< void >( this, 3, entity );

	}

	inline void finish_track_prediction_errors( base_entity* entity ) {

		g_utils.call_v_func< void >( this, 4, entity );

	}

};

struct prediction {

	byte	  pad0[ 0x4 ];
	uintptr_t m_last_ground;
	bool	  m_in_prediction;
	bool	  m_old_cl_predict_value;
	bool	  m_engine_paused;
	byte	  pad2[ 0xD ];
	bool	  m_is_first_time_predicted;

	inline void update( int start_frame, bool valid_frame, int incoming_acknowledged, int outgoing_command ) {

		g_utils.call_v_func< void >( this, 3, start_frame, valid_frame, incoming_acknowledged, outgoing_command );

	}

	inline void get_local_view_angles( q_ang& ang_view ) {

		g_utils.call_v_func< void, q_ang& >( this, 12, ang_view );

	}

	inline void set_local_view_angles( q_ang& ang_view ) {

		g_utils.call_v_func< void, q_ang& >( this, 13, ang_view );

	}

	inline void check_moving_ground( base_entity* entity, double frametime ) {

		g_utils.call_v_func< void >( this, 18, entity, frametime );

	}

	inline void setup_move( base_entity* entity, user_cmd* cmd, move_helper* helper, move_data* move_data ) {

		g_utils.call_v_func< void >( this, 20, entity, cmd, helper, move_data );

	}

	inline void finish_move( base_entity* entity, user_cmd* cmd, move_data* move_data ) {

		g_utils.call_v_func< void >( this, 21, entity, cmd, move_data );

	}

};