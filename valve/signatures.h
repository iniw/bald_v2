#pragma once

#include "../other/pattern/pattern.h"
#include "../other/memory/pe.h"
#include "../other/xor/xor.h"

struct signatures {

	// modules
	
	struct {

		address client;
		address engine;
		address server;
		address gameoverlayrenderer;
		address vgui2;
		address vguimatsurface;
		address studiorender;
		address localize;
		address datacache;
		address materialsystem;
		address vstdlib;
		address vphysics;

	} m_dlls;

	// offsets

	address m_anim_overlay;
	address m_abs_velocity;

	// functions

	address m_create_move;
	address m_level_shutdown;
	address m_get_view_model_fov;
	address m_draw_crosshair;
	address m_update;
	address m_modify_eye_position;
	address m_do_procedural_foot_plant;
	address m_setup_velocity;
	address m_setup_movement;
	address m_setup_aim_matrix;
	address m_set_up_weapon_action;
	address m_set_up_movement;
	address m_set_up_alive_loop;
	address m_set_up_whole_body_action;
	address m_set_up_flinch;
	address m_set_up_lean;
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
	address m_prediction_random_seed;
	address m_prediction_entity;
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

		bool setup( ) {

			m_dlls.client              = g_pe.get( XOR( "client.dll" ) );
			m_dlls.engine              = g_pe.get( XOR( "engine.dll" ) );
			m_dlls.server              = g_pe.get( XOR( "server.dll" ) );
			m_dlls.gameoverlayrenderer = g_pe.get( XOR( "gameoverlayrenderer.dll" ) );
			m_dlls.vgui2               = g_pe.get( XOR( "vgui2.dll" ) );
			m_dlls.vguimatsurface      = g_pe.get( XOR( "vguimatsurface.dll" ) );
			m_dlls.studiorender	       = g_pe.get( XOR( "studiorender.dll" ) );
			m_dlls.localize            = g_pe.get( XOR( "localize.dll" ) );
			m_dlls.datacache           = g_pe.get( XOR( "datacache.dll" ) );
			m_dlls.materialsystem	   = g_pe.get( XOR( "materialsystem.dll" ) );
			m_dlls.vstdlib			   = g_pe.get( XOR( "vstdlib.dll" ) );
			m_dlls.vphysics			   = g_pe.get( XOR( "vphysics.dll" ) );

			m_anim_overlay = g_pattern.find( m_dlls.client, XOR( "8B 80 ? ? ? ? 03 C1 74 15" ) );
			m_abs_velocity = g_pattern.find( m_dlls.client, XOR( "F3 0F 10 A6 ? ? ? ? F3 0F 11 64 24 ?" ) );

			m_create_move                        = g_pattern.find( m_dlls.client, XOR( "E8 ? ? ? ? FF 15 ? ? ? ? 84 C0 74 29" ) ).absolute( );
			m_level_shutdown                     = g_pattern.find( m_dlls.client, XOR( "55 8B EC 83 E4 F8 83 EC 30 C6 05 ? ? ? ? ?" ) );
			m_get_view_model_fov                 = g_pattern.find( m_dlls.client, XOR( "55 8B EC 8B 0D ? ? ? ? 83 EC 08 57" ) );
			m_draw_crosshair                     = g_pattern.find( m_dlls.client, XOR( "55 8B EC 83 E4 F0 83 EC 78 56 8B F1 8B 0D ? ? ? ?" ) );
			m_update                             = g_pattern.find( m_dlls.client, XOR( "E8 ? ? ? ? E9 ? ? ? ? 83 BE ? ? ? ? ?" ) ).absolute( );
			m_modify_eye_position                = g_pattern.find( m_dlls.client, XOR( "E8 ? ? ? ? 8B 06 8B CE FF 90 ? ? ? ? 85 C0 74 50" ) ).absolute( );
			m_do_procedural_foot_plant           = g_pattern.find( m_dlls.client, XOR( "E8 ? ? ? ? F6 86 ? ? ? ? ? 0F 84 ? ? ? ?" ) ).absolute( );
			m_setup_velocity                     = g_pattern.find( m_dlls.client, XOR( "55 8B EC 83 E4 F8 83 EC 30 56 57 8B 3D ? ? ? ?" ) );
			m_setup_movement                     = g_pattern.find( m_dlls.client, XOR( "E8 ? ? ? ? 8B CF E8 ? ? ? ? 8B CF E8 ? ? ? ? 8B 47 60" ) ).absolute( );
			m_setup_aim_matrix                   = g_pattern.find( m_dlls.client, XOR( "55 8B EC 81 EC ? ? ? ? 53 56 57 8B 3D ? ? ? ?" ) );
			m_set_up_weapon_action               = g_pattern.find( m_dlls.client, XOR( "55 8B EC 51 53 56 57 8B F9 8B 77 60" ) );
			m_set_up_movement                    = g_pattern.find( m_dlls.client, XOR( "E8 ? ? ? ? 8B CF E8 ? ? ? ? 8B CF E8 ? ? ? ? 8B 47 60" ) ).absolute( );
			m_set_up_alive_loop                  = g_pattern.find( m_dlls.client, XOR( "E8 ? ? ? ? 8B CF E8 ? ? ? ? 8B 47 60" ) ).absolute( );
			m_set_up_whole_body_action           = g_pattern.find( m_dlls.client, XOR( "E8 ? ? ? ? 8B 47 60 83 B8 ? ? ? ? ?" ) ).absolute( );
			m_set_up_flinch                      = g_pattern.find( m_dlls.client, XOR( "E8 ? ? ? ? 8B CF E8 ? ? ? ? 33 C0" ) ).absolute( );
			m_set_up_lean                        = g_pattern.find( m_dlls.client, XOR( "E8 ? ? ? ? 33 C0 89 44 24 0C" ) ).absolute( );
			m_cache_sequences                    = g_pattern.find( m_dlls.client, XOR( "E8 ? ? ? ? 84 C0 0F 84 ? ? ? ? 8B 77 60" ) ).absolute( );
			m_get_ground_entity                  = g_pattern.find( m_dlls.client, XOR( "E8 ? ? ? ? 8B 4C 24 14 85 C0" ) ).absolute( );
			m_invalidate_physics_recursive       = g_pattern.find( m_dlls.client, XOR( "E8 ? ? ? ? 89 5E 18" ) ).absolute( );
			m_set_abs_angles                     = g_pattern.find( m_dlls.client, XOR( "E8 ? ? ? ? 53 8D 45 F0" ) ).absolute( );
			m_set_abs_origin                     = g_pattern.find( m_dlls.client, XOR( "55 8B EC 83 E4 F8 51 53 56 57 8B F1 E8" ) );
			m_lookup_bone                        = g_pattern.find( m_dlls.client, XOR( "E8 ? ? ? ? 89 44 24 5C" ) ).absolute( );
			m_get_bone_position                  = g_pattern.find( m_dlls.client, XOR( "E8 ? ? ? ? 8D 14 24" ) ).absolute( );
			m_calc_absolute_velocity             = g_pattern.find( m_dlls.client, XOR( "E8 ? ? ? ? 83 7B 30 00" ) ).absolute( );
			m_increment_layer_cycle              = g_pattern.find( m_dlls.client, XOR( "E8 ? ? ? ? FF 76 60 F3 0F 10 54 24 ?" ) ).absolute( );
			m_increment_layer_weight             = g_pattern.find( m_dlls.client, XOR( "E8 ? ? ? ? 8B 5F 60 83 BB ? ? ? ? ?" ) ).absolute( );
			m_get_model_ptr                      = g_pattern.find( m_dlls.client, XOR( "E8 ? ? ? ? 8B 55 38" ) ).absolute( );
			m_get_first_sequence_anim_tag        = g_pattern.find( m_dlls.client, XOR( "E8 ? ? ? ? F3 0F 11 86 ? ? ? ? 0F 57 DB" ) ).absolute( );
			m_seqdesc                            = g_pattern.find( m_dlls.client, XOR( "E8 ? ? ? ? 03 40 04" ) ).absolute( );
			m_lookup_pose_parameter              = g_pattern.find( m_dlls.client, XOR( "E8 ? ? ? ? 85 C0 79 08" ) ).absolute( );
			m_studio_set_pose_parameter          = g_pattern.find( m_dlls.client, XOR( "E8 ? ? ? ? 0F 28 D8 83 C4 04" ) ).absolute( );
			m_cam_think                          = g_pattern.find( m_dlls.client, XOR( "55 8B EC 83 E4 F8 81 EC ? ? ? ? 56 8B F1 8B 0D ? ? ? ? 57 85 C9" ) );
			m_cam_to_third_person                = g_pattern.find( m_dlls.client, XOR( "55 8B EC 83 EC 0C 8D 55 F4" ) );
			m_physics_run_think                  = g_pattern.find( m_dlls.client, XOR( "55 8B EC 83 EC 10 53 56 57 8B F9 8B 87" ) );
			m_post_think_vphysics                = g_pattern.find( m_dlls.client, XOR( "55 8B EC 83 E4 F8 81 EC ? ? ? ? 53 8B D9 56 57 83 BB" ) );
			m_simulate_player_simulated_entities = g_pattern.find( m_dlls.client, XOR( "56 8B F1 57 8B BE ? ? ? ? 83 EF 01 78 72" ) );
			m_prediction_random_seed             = g_pattern.find( m_dlls.client, XOR( "8B 0D ? ? ? ? BA ? ? ? ? E8 ? ? ? ? 83 C4 04" ) );
			m_prediction_entity                  = g_pattern.find( m_dlls.client, XOR( "89 35 ? ? ? ? F3 0F 10 48 20" ) );
			m_glow_effect_spectator              = g_pattern.find( m_dlls.client, XOR( "55 8B EC 83 EC 14 53 8B 5D 0C 56 57 85 DB 74" ) );
			m_move_helper                        = g_pattern.find( m_dlls.client, XOR( "8B 0D ? ? ? ? 8B 46 08 68" ) );
			m_insert_into_tree                   = g_pattern.find( m_dlls.client, XOR( "56 52 FF 50 18" ) );
			m_net_graph_panel                    = g_pattern.find( m_dlls.client, XOR( "89 1D ? ? ? ? 8B C3" ) );
			m_accumulate_layers                  = g_pattern.find( m_dlls.client, XOR( "84 C0 75 0D F6 87" ) );
			m_invalidate_bone_cache              = g_pattern.find( m_dlls.client, XOR( "80 3D ? ? ? ? ? 74 16 A1 ? ? ? ? 48 C7 81" ) );
			m_set_collision_bounds				 = g_pattern.find( m_dlls.client, XOR( "53 8B DC 83 EC 08 83 E4 F8 83 C4 04 55 8B 6B 04 89 6C 24 04 8B EC 83 EC 10 56 57 8B 7B" ) );
			m_should_interpolate				 = g_pattern.find( m_dlls.client, XOR( "A1 ? ? ? ? 56 57 8B F9 8B 30 8D 4F 08" ) );
			m_should_skip_animation_frame		 = g_pattern.find( m_dlls.client, XOR( "57 8B F9 8B 07 8B 80 ? ? ? ? FF D0 84 C0 75 02" ) );

			m_client_state       = g_pattern.find( m_dlls.engine , XOR( "A1 ? ? ? ? 8B 80 ? ? ? ? C3" ) );
			m_paint              = g_pattern.find( m_dlls.engine , XOR( "55 8B EC 83 EC 40 53 8B D9 8B 0D ? ? ? ? 89 5D F8" ) );
			m_list_leaves_in_box = g_pattern.find( m_dlls.engine , XOR( "55 8B EC 83 EC 18 8B 4D 0C" ) );

			m_start_drawing  = g_pattern.find( m_dlls.vguimatsurface , XOR( "55 8B EC 83 E4 C0 83 EC 38" ) );
			m_finish_drawing = g_pattern.find( m_dlls.vguimatsurface , XOR( "8B 0D ? ? ? ? 56 C6 05 ? ? ? ? ?" ) );

			m_reload_schemes = g_pattern.find( m_dlls.vgui2, XOR( "55 8B EC 83 EC 08 53 56 8B F1 6A 00" ) );

			m_draw_model = g_pattern.find( m_dlls.studiorender, XOR( "55 8B EC 83 E4 F8 83 EC 54" ) );

			m_hook    = g_pattern.find( m_dlls.gameoverlayrenderer, XOR( "55 8B EC 51 8B 45 10 C7" ) );
			m_restore = g_pattern.find( m_dlls.gameoverlayrenderer, XOR( "E8 ? ? ? ? 83 C4 08 FF 15 ? ? ? ?" ) ).absolute( );

			m_draw_server_hitboxes = g_pattern.find( m_dlls.server, XOR( "E8 ? ? ? ? F6 83 ? ? ? ? ? 0F 84 ? ? ? ? 33 FF" ) ).absolute( );
			m_util_player_by_index = g_pattern.find( m_dlls.server, XOR( "85 C9 7E 2A A1 ? ? ? ?" ) );

			return true;

		}

};

inline signatures g_signatures;