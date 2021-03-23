#include "signatures.h"

#include "../../other/memory/pe.h"
#include "../../other/xor/xor.h"

bool signatures::setup( ) {

	FIND( m_anim_overlay, g_pe.m_dlls.client, "8B 80 ? ? ? ? 03 C1 74 15" );
	FIND( m_abs_velocity, g_pe.m_dlls.client, "F3 0F 10 A6 ? ? ? ? F3 0F 11 64 24 ?" );

	FIND( m_get_view_model_fov, g_pe.m_dlls.client, "55 8B EC 8B 0D ? ? ? ? 83 EC 08 57" );
	FIND( m_draw_crosshair, g_pe.m_dlls.client, "55 8B EC 83 E4 F0 83 EC 78 56 8B F1 8B 0D ? ? ? ?" );
	FIND_ABS( m_update, g_pe.m_dlls.client, "E8 ? ? ? ? E9 ? ? ? ? 83 BE ? ? ? ? ?" );
	FIND_ABS( m_modify_eye_position, g_pe.m_dlls.client, "E8 ? ? ? ? 8B 06 8B CE FF 90 ? ? ? ? 85 C0 74 50" );
	FIND_ABS( m_do_procedural_foot_plant, g_pe.m_dlls.client, "E8 ? ? ? ? F6 86 ? ? ? ? ? 0F 84 ? ? ? ?" );
	FIND( m_setup_velocity, g_pe.m_dlls.client, "55 8B EC 83 E4 F8 83 EC 30 56 57 8B 3D ? ? ? ?" );
	FIND_ABS( m_setup_movement, g_pe.m_dlls.client, "E8 ? ? ? ? 8B CF E8 ? ? ? ? 8B CF E8 ? ? ? ? 8B 47 60" );
	FIND( m_setup_aim_matrix, g_pe.m_dlls.client, "55 8B EC 81 EC ? ? ? ? 53 56 57 8B 3D ? ? ? ?" );
	FIND( m_setup_weapon_action, g_pe.m_dlls.client, "55 8B EC 51 53 56 57 8B F9 8B 77 60" );
	FIND_ABS( m_setup_alive_loop, g_pe.m_dlls.client, "E8 ? ? ? ? 8B CF E8 ? ? ? ? 8B 47 60" );
	FIND_ABS( m_setup_whole_body_action, g_pe.m_dlls.client, "E8 ? ? ? ? 8B 47 60 83 B8 ? ? ? ? ?" );
	FIND_ABS( m_setup_flinch, g_pe.m_dlls.client, "E8 ? ? ? ? 8B CF E8 ? ? ? ? 33 C0" );
	FIND_ABS( m_setup_lean, g_pe.m_dlls.client, "E8 ? ? ? ? 33 C0 89 44 24 0C" );
	FIND_ABS( m_cache_sequences, g_pe.m_dlls.client, "E8 ? ? ? ? 84 C0 0F 84 ? ? ? ? 8B 77 60" );
	FIND_ABS( m_get_ground_entity, g_pe.m_dlls.client, "E8 ? ? ? ? 8B 4C 24 14 85 C0" );
	FIND_ABS( m_invalidate_physics_recursive, g_pe.m_dlls.client, "E8 ? ? ? ? 89 5E 18" );
	FIND_ABS( m_set_abs_angles, g_pe.m_dlls.client, "E8 ? ? ? ? 53 8D 45 F0" );
	FIND( m_set_abs_origin, g_pe.m_dlls.client, "55 8B EC 83 E4 F8 51 53 56 57 8B F1 E8" );
	FIND_ABS( m_lookup_bone, g_pe.m_dlls.client, "E8 ? ? ? ? 89 44 24 5C" );
	FIND_ABS( m_get_bone_position, g_pe.m_dlls.client, "E8 ? ? ? ? 8D 14 24" );
	FIND_ABS( m_calc_absolute_velocity, g_pe.m_dlls.client, "E8 ? ? ? ? 83 7B 30 00" );
	FIND_ABS( m_increment_layer_cycle, g_pe.m_dlls.client, "E8 ? ? ? ? FF 76 60 F3 0F 10 54 24 ?" );
	FIND_ABS( m_increment_layer_weight, g_pe.m_dlls.client, "E8 ? ? ? ? 8B 5F 60 83 BB ? ? ? ? ?" );
	FIND_ABS( m_get_model_ptr, g_pe.m_dlls.client, "E8 ? ? ? ? 8B 55 38" );
	FIND_ABS( m_get_first_sequence_anim_tag, g_pe.m_dlls.client, "E8 ? ? ? ? F3 0F 11 86 ? ? ? ? 0F 57 DB" );
	FIND_ABS( m_seqdesc, g_pe.m_dlls.client, "E8 ? ? ? ? 03 40 04" );
	FIND_ABS( m_lookup_pose_parameter, g_pe.m_dlls.client, "E8 ? ? ? ? 85 C0 79 08" );
	FIND_ABS( m_studio_set_pose_parameter, g_pe.m_dlls.client, "E8 ? ? ? ? 0F 28 D8 83 C4 04" );
	FIND( m_cam_think, g_pe.m_dlls.client, "55 8B EC 83 E4 F8 81 EC ? ? ? ? 56 8B F1 8B 0D ? ? ? ? 57 85 C9" );
	FIND( m_cam_to_third_person, g_pe.m_dlls.client, "55 8B EC 83 EC 0C 8D 55 F4" );
	FIND( m_physics_run_think, g_pe.m_dlls.client, "55 8B EC 83 EC 10 53 56 57 8B F9 8B 87" );
	FIND( m_post_think_vphysics, g_pe.m_dlls.client,  "55 8B EC 83 E4 F8 81 EC ? ? ? ? 53 8B D9 56 57 83 BB" );
	FIND( m_simulate_player_simulated_entities, g_pe.m_dlls.client, "56 8B F1 57 8B BE ? ? ? ? 83 EF 01 78 72" );
	FIND( m_glow_effect_spectator, g_pe.m_dlls.client, "55 8B EC 83 EC 14 53 8B 5D 0C 56 57 85 DB 74" );
	FIND( m_move_helper, g_pe.m_dlls.client, "8B 0D ? ? ? ? 8B 46 08 68" );
	FIND( m_insert_into_tree, g_pe.m_dlls.client, "56 52 FF 50 18" );
	FIND( m_net_graph_panel, g_pe.m_dlls.client, "89 1D ? ? ? ? 8B C3" );
	FIND( m_accumulate_layers, g_pe.m_dlls.client, "84 C0 75 0D F6 87" );
	FIND( m_set_collision_bounds, g_pe.m_dlls.client, "53 8B DC 83 EC 08 83 E4 F8 83 C4 04 55 8B 6B 04 89 6C 24 04 8B EC 83 EC 10 56 57 8B 7B" );
	FIND( m_should_interpolate, g_pe.m_dlls.client, "A1 ? ? ? ? 56 57 8B F9 8B 30 8D 4F 08" );
	FIND( m_should_skip_animation_frame, g_pe.m_dlls.client, "57 8B F9 8B 07 8B 80 ? ? ? ? FF D0 84 C0 75 02" );

	FIND( m_client_state, g_pe.m_dlls.engine, "A1 ? ? ? ? 8B 80 ? ? ? ? C3" );
	FIND( m_paint, g_pe.m_dlls.engine, "55 8B EC 83 EC 40 53 8B D9 8B 0D ? ? ? ? 89 5D F8" );
	FIND( m_list_leaves_in_box, g_pe.m_dlls.engine, "55 8B EC 83 EC 18 8B 4D 0C" );

	FIND( m_start_drawing, g_pe.m_dlls.vguimatsurface, "55 8B EC 83 E4 C0 83 EC 38" );
	FIND( m_finish_drawing, g_pe.m_dlls.vguimatsurface, "8B 0D ? ? ? ? 56 C6 05 ? ? ? ? ?" );

	FIND( m_reload_schemes, g_pe.m_dlls.vgui2, "55 8B EC 83 EC 08 53 56 8B F1 6A 00" );

	FIND( m_draw_model, g_pe.m_dlls.studiorender, "55 8B EC 83 E4 F8 83 EC 54" );

	FIND( m_hook, g_pe.m_dlls.gameoverlayrenderer, "55 8B EC 51 8B 45 10 C7" );
	FIND_ABS( m_restore, g_pe.m_dlls.gameoverlayrenderer, "E8 ? ? ? ? 83 C4 08 FF 15 ? ? ? ?" );

	FIND_ABS( m_draw_server_hitboxes, g_pe.m_dlls.server, "E8 ? ? ? ? F6 83 ? ? ? ? ? 0F 84 ? ? ? ? 33 FF"  );
	FIND( m_util_player_by_index, g_pe.m_dlls.server, "85 C9 7E 2A A1 ? ? ? ?" );

	g_console.log( log_completion, XOR( "setup scanning" ) );

	return true;

}