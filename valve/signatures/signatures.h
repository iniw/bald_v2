#pragma once

#include "../../other/pattern/pattern.h"
#include "../../other/utils/utils.h"

#define FIND( var, dll, pattern ) \
	if ( var = g_pattern.find( dll, pattern ); !var ) { \
		g_console.log( log_error, XOR( "failed to scan pattern for %s" ), XOR( #var ) ); \
		return false; \
	}

#define FIND_ABS( var, dll, pattern ) \
	if ( var = g_pattern.find( dll, XOR( pattern ) ).absolute( ); !var ) { \
		g_console.log( log_error, XOR( "failed to scan pattern for %s" ), XOR( #var ) ); \
		return false; \
	}

struct signatures {

	// offsets

	address m_anim_overlay;
	address m_abs_velocity;

	// functions

	address m_create_move;
	address m_get_view_model_fov;
	address m_draw_crosshair;
	address m_update;
	address m_modify_eye_position;
	address m_do_procedural_foot_plant;
	address m_setup_velocity;
	address m_setup_movement;
	address m_setup_aim_matrix;
	address m_setup_weapon_action;
	address m_setup_alive_loop;
	address m_setup_whole_body_action;
	address m_setup_flinch;
	address m_setup_lean;
	address m_cache_sequences;
	address m_get_ground_entity;
	address m_invalidate_physics_recursive;
	address m_set_abs_angles;
	address m_set_abs_origin;
	address m_lookup_bone;
	address m_get_bone_position;
	address m_calc_absolute_velocity;
	address m_increment_layer_cycle;
	address m_increment_layer_weight;
	address m_get_model_ptr;
	address m_get_first_sequence_anim_tag;
	address m_seqdesc;
	address m_lookup_pose_parameter;
	address m_studio_set_pose_parameter;
	address m_cam_think;
	address m_cam_to_third_person;
	address m_physics_run_think;
	address m_post_think_vphysics;
	address m_simulate_player_simulated_entities;
	address m_glow_effect_spectator;
	address m_move_helper;
	address m_insert_into_tree;
	address m_net_graph_panel;
	address m_accumulate_layers;
	address m_invalidate_bone_cache;
	address m_set_collision_bounds;
	address m_should_interpolate;
	address m_should_skip_animation_frame;

	address m_client_state;
	address m_paint;
	address m_list_leaves_in_box;
	
	address m_start_drawing;
	address m_finish_drawing;

	address m_reload_schemes;

	address m_draw_model;

	address m_hook;
	address m_restore;
																	  
	address m_draw_server_hitboxes;
	address m_util_player_by_index;

	bool setup( );

};

inline signatures g_signatures;