#pragma once

#include "base_animating.h"

enum glow_styles {

	glow_style_default = 0,
	glow_style_rim_3d,
	glow_style_edge_hightlight,
	glow_style_edge_hightlight_pulse,
	glow_style_count,

};

struct lag_record;

struct cs_player : base_animating {

	inline auto think( ) {

		g_utils.call_v_func< void >( this, 138 );

	}

	inline auto pre_think( ) {

		g_utils.call_v_func< void >( this, 339 );

	}

	inline auto studio_frame_advance( ) {

		g_utils.call_v_func< void >( this, 219 );

	}

	inline auto& is_scoped( ) {

		static auto offset = g_netvars.m_offsets[ g_hash.get( XOR( "DT_CSPlayer->m_bIsScoped" ) ) ];

		return *reinterpret_cast< bool* >( reinterpret_cast< size_t >( this ) + offset );

	}

	inline auto& is_player_ghost( ) {

		static auto offset = g_netvars.m_offsets[ g_hash.get( XOR( "DT_CSPlayer->m_bIsPlayerGhost" ) ) ];

		return *reinterpret_cast< bool* >( reinterpret_cast< size_t >( this ) + offset );

	}

	inline auto& get_third_person_recoil( ) {

		static auto offset = g_netvars.m_offsets[ g_hash.get( XOR( "DT_CSPlayer->m_flThirdpersonRecoil" ) ) ];

		return *reinterpret_cast< float* >( reinterpret_cast< size_t >( this ) + offset );

	}

	inline auto& get_duck_amount( ) {

		static auto offset = g_netvars.m_offsets[ g_hash.get( XOR( "DT_CSPlayer->m_flDuckAmount" ) ) ];

		return *reinterpret_cast< float* >( reinterpret_cast< size_t >( this ) + offset );

	}

	inline auto& get_playback_rate( ) {

		static auto offset = g_netvars.m_offsets[ g_hash.get( XOR( "DT_CSPlayer->m_flPlaybackRate" ) ) ];

		return *reinterpret_cast< float* >( reinterpret_cast< size_t >( this ) + offset );

	}

	inline auto& get_cycle( ) {

		static auto offset = g_netvars.m_offsets[ g_hash.get( XOR( "DT_CSPlayer->m_flCycle" ) ) ];

		return *reinterpret_cast< float* >( reinterpret_cast< size_t >( this ) + offset );

	}

	inline auto& get_lower_body_yaw_target( ) {

		static auto offset = g_netvars.m_offsets[ g_hash.get( XOR( "DT_CSPlayer->m_flLowerBodyYawTarget" ) ) ];

		return *reinterpret_cast< float* >( reinterpret_cast< size_t >( this ) + offset );

	}

	inline auto& is_immune( ) {

		static auto offset = g_netvars.m_offsets[ g_hash.get( XOR( "DT_CSPlayer->m_bGunGameImmunity" ) ) ];

		return *reinterpret_cast< bool* >( reinterpret_cast< size_t >( this ) + offset );

	}


	inline auto& has_heavy_armor( ) {

		static auto offset = g_netvars.m_offsets[ g_hash.get( XOR( "DT_CSPlayer->m_bHasHeavyArmor" ) ) ];

		return *reinterpret_cast< bool* >( reinterpret_cast< size_t >( this ) + offset );

	}

	inline auto& get_armor( ) {

		static auto offset = g_netvars.m_offsets[ g_hash.get( XOR( "DT_CSPlayer->m_ArmorValue" ) ) ];

		return *reinterpret_cast< int* >( reinterpret_cast< size_t >( this ) + offset );

	}

	inline auto& has_helmet( ) {

		static auto offset = g_netvars.m_offsets[ g_hash.get( XOR( "DT_CSPlayer->m_bHasHelmet" ) ) ];

		return *reinterpret_cast< bool* >( reinterpret_cast< size_t >( this ) + offset );

	}

	inline auto& is_using_new_anim_state( ) {

		static auto offset = g_netvars.m_offsets[ g_hash.get( XOR( "DT_CSPlayer->m_flLastExoJumpTime" ) ) ] + 0x8;

		return *reinterpret_cast< int* >( reinterpret_cast< size_t >( this ) + offset );

	}

	inline auto physics_run_think( int method ) {

		static auto function = g_signatures.m_physics_run_think.as< bool( __thiscall* )( void*, int ) >( );

		return function( this, method );

	}

	inline auto set_collision_bounds( const vec_3& mins, const vec_3& maxs ) {

		static auto function = g_signatures.m_set_collision_bounds.as< void( __thiscall* )( i_collideable*, const vec_3&, const vec_3& ) >( );

		return function( this->get_collideable( ), mins, maxs );

	}

	vec_3 get_eye_position( );

	void post_think( );

	bool can_shoot( );

	vec_3 get_hitbox_position( int hitbox, lag_record* record = nullptr );

	vec_3 get_hitbox_position( int hitbox, matrix_3x4* matrix = nullptr );

	bool fixed_setup_bones( matrix_3x4* matrix, const int bone_mask, const float curtime );

	float dist_to_ray( const vec_3& start, const vec_3& end );

};