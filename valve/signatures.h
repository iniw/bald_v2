#pragma once

#include "../other/pattern/pattern.h"

struct signatures {

	// offsets

	address m_anim_overlay = g_pattern.find( "client.dll", "8B 80 ? ? ? ? 03 C1 74 15" );
	address m_abs_velocity = g_pattern.find( "client.dll", "F3 0F 10 A6 ? ? ? ? F3 0F 11 64 24 ?" );

	// functions

	address m_create_move                        = g_pattern.find( "client.dll", "E8 ? ? ? ? FF 15 ? ? ? ? 84 C0 74 29" ).absolute( );
	address m_paint                              = g_pattern.find( "engine.dll", "55 8B EC 83 EC 40 53 8B D9 8B 0D ? ? ? ? 89 5D F8" );
	address m_get_view_model_fov                 = g_pattern.find( "client.dll", "55 8B EC 8B 0D ? ? ? ? 83 EC 08 57" );
	address m_draw_crosshair                     = g_pattern.find( "client.dll", "55 8B EC 83 E4 F0 83 EC 78 56 8B F1 8B 0D ? ? ? ?" );
	address m_update                             = g_pattern.find( "client.dll", "E8 ? ? ? ? E9 ? ? ? ? 83 BE ? ? ? ? ?" ).absolute( );
	address m_modify_eye_position                = g_pattern.find( "client.dll", "E8 ? ? ? ? 8B 06 8B CE FF 90 ? ? ? ? 85 C0 74 50" ).absolute( );
	address m_do_procedural_foot_plant           = g_pattern.find( "client.dll", "E8 ? ? ? ? F6 86 ? ? ? ? ? 0F 84 ? ? ? ?" ).absolute( );
	address m_setup_velocity                     = g_pattern.find( "client.dll", "55 8B EC 83 E4 F8 83 EC 30 56 57 8B 3D ? ? ? ?" );
	address m_setup_movement                     = g_pattern.find( "client.dll", "E8 ? ? ? ? 8B CF E8 ? ? ? ? 8B CF E8 ? ? ? ? 8B 47 60" ).absolute( );
	address m_setup_aim_matrix                   = g_pattern.find( "client.dll", "55 8B EC 81 EC ? ? ? ? 53 56 57 8B 3D ? ? ? ?" );
	address m_set_up_weapon_action               = g_pattern.find( "client.dll", "55 8B EC 51 53 56 57 8B F9 8B 77 60" );
	address m_set_up_movement                    = g_pattern.find( "client.dll", "E8 ? ? ? ? 8B CF E8 ? ? ? ? 8B CF E8 ? ? ? ? 8B 47 60" ).absolute( );
	address m_set_up_alive_loop                  = g_pattern.find( "client.dll", "E8 ? ? ? ? 8B CF E8 ? ? ? ? 8B 47 60" ).absolute( );
	address m_set_up_whole_body_action           = g_pattern.find( "client.dll", "E8 ? ? ? ? 8B 47 60 83 B8 ? ? ? ? ?" ).absolute( );
	address m_set_up_flinch                      = g_pattern.find( "client.dll", "E8 ? ? ? ? 8B CF E8 ? ? ? ? 33 C0" ).absolute( );
	address m_set_up_lean                        = g_pattern.find( "client.dll", "E8 ? ? ? ? 33 C0 89 44 24 0C" ).absolute( );
	address m_cache_sequences                    = g_pattern.find( "client.dll", "E8 ? ? ? ? 84 C0 0F 84 ? ? ? ? 8B 77 60" ).absolute( );
	address m_get_ground_entity                  = g_pattern.find( "client.dll", "E8 ? ? ? ? 8B 4C 24 14 85 C0" ).absolute( );
	address m_invalidate_physics_recursive       = g_pattern.find( "client.dll", "E8 ? ? ? ? 89 5E 18" ).absolute( );
	address m_set_abs_angles                     = g_pattern.find( "client.dll", "E8 ? ? ? ? 53 8D 45 F0" ).absolute( );
	address m_set_abs_origin                     = g_pattern.find( "client.dll", "55 8B EC 83 E4 F8 51 53 56 57 8B F1 E8" );
	address m_lookup_bone                        = g_pattern.find( "client.dll", "E8 ? ? ? ? 89 44 24 5C" ).absolute( );
	address m_get_bone_position                  = g_pattern.find( "client.dll", "E8 ? ? ? ? 8D 14 24" ).absolute( );
	address m_calc_absolute_velocity             = g_pattern.find( "client.dll", "E8 ? ? ? ? 83 7B 30 00" ).absolute( );
	address m_increment_layer_cycle              = g_pattern.find( "client.dll", "E8 ? ? ? ? FF 76 60 F3 0F 10 54 24 ?" ).absolute( );
	address m_increment_layer_weight             = g_pattern.find( "client.dll", "E8 ? ? ? ? 8B 5F 60 83 BB ? ? ? ? ?" ).absolute( );
	address m_get_model_ptr                      = g_pattern.find( "client.dll", "E8 ? ? ? ? 8B 55 38" ).absolute( );
	address m_get_first_sequence_anim_tag        = g_pattern.find( "client.dll", "E8 ? ? ? ? F3 0F 11 86 ? ? ? ? 0F 57 DB" ).absolute( );
	address m_seqdesc                            = g_pattern.find( "client.dll", "E8 ? ? ? ? 03 40 04" ).absolute( );
	address m_lookup_pose_parameter              = g_pattern.find( "client.dll", "E8 ? ? ? ? 85 C0 79 08" ).absolute( );
	address m_studio_set_pose_parameter          = g_pattern.find( "client.dll", "E8 ? ? ? ? 0F 28 D8 83 C4 04" ).absolute( );
	address m_cam_think                          = g_pattern.find( "client.dll", "55 8B EC 83 E4 F8 81 EC ? ? ? ? 56 8B F1 8B 0D ? ? ? ? 57 85 C9" );
	address m_cam_to_third_person                = g_pattern.find( "client.dll", "55 8B EC 83 EC 0C 8D 55 F4" );
	address m_physics_run_think                  = g_pattern.find( "client.dll", "55 8B EC 83 EC 10 53 56 57 8B F9 8B 87" );
	address m_post_think_vphysics		         = g_pattern.find( "client.dll", "55 8B EC 83 E4 F8 81 EC ? ? ? ? 53 8B D9 56 57 83 BB" );
	address m_simulate_player_simulated_entities = g_pattern.find( "client.dll", "56 8B F1 57 8B BE ? ? ? ? 83 EF 01 78 72" );
	address m_prediction_random_seed			 = g_pattern.find( "client.dll", "8B 0D ? ? ? ? BA ? ? ? ? E8 ? ? ? ? 83 C4 04" );
	address m_prediction_entity					 = g_pattern.find( "client.dll", "89 35 ? ? ? ? F3 0F 10 48 20" );

	address m_start_drawing  = g_pattern.find( "vguimatsurface.dll", "55 8B EC 83 E4 C0 83 EC 38" );
	address m_finish_drawing = g_pattern.find( "vguimatsurface.dll", "8B 0D ? ? ? ? 56 C6 05 ? ? ? ? ?" );

	address m_reload_schemes = g_pattern.find( "vgui2.dll", "55 8B EC 83 EC 08 53 56 8B F1 6A 00" );

	address m_draw_model = g_pattern.find( "studiorender.dll", "55 8B EC 83 E4 F8 83 EC 54" );

	address m_hook    = g_pattern.find( "gameoverlayrenderer.dll", "55 8B EC 51 8B 45 10 C7" );
	address m_restore = g_pattern.find( "gameoverlayrenderer.dll", "E8 ? ? ? ? 83 C4 08 FF 15 ? ? ? ?" ).absolute( );

	address m_draw_server_hitboxes = g_pattern.find( "server.dll", "E8 ? ? ? ? F6 83 ? ? ? ? ? 0F 84 ? ? ? ? 33 FF" ).absolute( );
	address m_util_player_by_index = g_pattern.find( "server.dll", "85 C9 7E 2A A1 ? ? ? ?" );

};

inline signatures g_signatures;