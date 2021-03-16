#pragma once

#include "../cstrike.h"

#include "../features/features.h"
#include "../input/input.h"

struct hooked {

	bool setup( );

	void unload( );

private:

	static bool __fastcall   create_move( cs_player* ecx, void* edx, float input_sample_time, user_cmd* cmd );
	static void __fastcall   frame_stage_notify( void* ecx, void* edx, frame_stage stage );
	static void __fastcall   paint( void* ecx, void* edx, paint_mode mode );
	static float __fastcall  get_view_model_fov( void* ecx, void* edx );
	static void __fastcall   draw_crosshair( weapon_cs_base* ecx, void* edx );
	static void __vectorcall update( csgo_player_anim_state* ecx, void* unk0, float z, float y, float x, void* unk1 );
	static void __fastcall   modify_eye_position( csgo_player_anim_state* ecx, void* edx, vec_3& input_eye_pos );
	static void __fastcall   do_procedural_foot_plant( csgo_player_anim_state* ecx, void* edx, void* bone_to_world, void* left_foot_chain, void* right_foot_chain, void* pos );
	static void __fastcall   set_up_movement( csgo_player_anim_state* ecx, void* edx );
	static void __fastcall   set_up_velocity( csgo_player_anim_state* ecx, void* edx );
	static void __fastcall   cam_think( client_input* ecx, void* edx );
	static void __fastcall   cam_to_third_person( client_input* ecx, void* edx );
	static void __fastcall   reload_schemes( void* ecx, void* edx );
	static void __fastcall   draw_model( studio_render_context* ecx, void* edx, void* results, const draw_model_info& info, void* bone_to_world, float* flex_weights, float* flex_delayed_rates, const vec_3& origin, int flags );
	static int __fastcall	 list_leaves_in_box( void* ecx, void* edx, const vec_3& mins, const vec_3& maxs, unsigned short* list, int list_max );
	static bool __cdecl      glow_effect_spectators( base_player* this_player, base_player* local_player, glow_styles& glow_style, vec_3& color, float& alpha_start, float& alpha, float& time_start, float& time_target, bool& animate );

};

inline hooked g_hooked;