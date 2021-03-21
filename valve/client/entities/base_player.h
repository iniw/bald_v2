#pragma once

#include "base_combat_character.h"
#include "../../shared/user_cmd.h"

enum move_types {

	move_type_none = 0,
	move_type_isometric,
	move_type_walk,
	move_type_step,
	move_type_fly,
	move_type_flygravity,
	move_type_vphysics,
	move_type_push,
	move_type_noclip,
	move_type_ladder,
	move_type_observer,
	move_type_custom,
	move_type_last = move_type_custom,
	move_type_max_bits = 4

};

enum flags {

	fl_onground              = ( 1 << 0 ),
	fl_ducking               = ( 1 << 1 ),
	fl_animducking           = ( 1 << 2 ),
	fl_waterjump             = ( 1 << 3 ),
	fl_ontrain               = ( 1 << 4 ),
	fl_inrain                = ( 1 << 5 ),
	fl_frozen                = ( 1 << 6 ),
	fl_atcontrols            = ( 1 << 7 ),
	fl_client                = ( 1 << 8 ),
	fl_fakeclient            = ( 1 << 9 ),
	fl_inwater               = ( 1 << 10 ),
	fl_fly                   = ( 1 << 11 ),
	fl_swim                  = ( 1 << 12 ),
	fl_conveyor              = ( 1 << 13 ),
	fl_npc                   = ( 1 << 14 ),
	fl_godmode               = ( 1 << 15 ),
	fl_notarget              = ( 1 << 16 ),
	fl_aimtarget             = ( 1 << 17 ),
	fl_partialground         = ( 1 << 18 ),
	fl_staticprop            = ( 1 << 19 ),
	fl_graphed               = ( 1 << 20 ),
	fl_grenade               = ( 1 << 21 ),
	fl_stepmovement          = ( 1 << 22 ),
	fl_donttouch             = ( 1 << 23 ),
	fl_basevelocity          = ( 1 << 24 ),
	fl_worldbrush            = ( 1 << 25 ),
	fl_object                = ( 1 << 26 ),
	fl_killme                = ( 1 << 27 ),
	fl_onfire                = ( 1 << 28 ),
	fl_dissolving            = ( 1 << 29 ),
	fl_transragdoll          = ( 1 << 30 ),
	fl_unblockable_by_player = ( 1 << 31 )

};

struct base_player : base_combat_character {

	inline auto update_collision_bounds( ) {

		return g_utils.call_v_func< void >( this, 339 );

	}

	inline auto is_max_health( ) {

		return g_utils.call_v_func< int >( this, 122 );

	}

	inline auto util_player_by_index( int entindex ) {

		auto function = g_signatures.m_util_player_by_index.as< base_player* ( __thiscall* )( int ) >( );

		return function( entindex );

	}

	inline auto get_buttons( ) {

		static auto offset = g_netvars.find_in_datamap( get_prediction_desc_map( ), g_hash.const_hash( XOR( "m_nButtons" ) ) );

		return reinterpret_cast< int* >( reinterpret_cast< size_t >( this ) + offset );

	}

	inline auto& get_button_last( ) {

		static auto offset = g_netvars.find_in_datamap( get_prediction_desc_map( ), g_hash.const_hash( XOR( "m_afButtonLast" ) ) );

		return *reinterpret_cast< int* >( reinterpret_cast< size_t >( this ) + offset );

	}

	inline auto& get_button_pressed( ) {

		static auto offset = g_netvars.find_in_datamap( get_prediction_desc_map( ), g_hash.const_hash( XOR( "m_afButtonPressed" ) ) );

		return *reinterpret_cast< int* >( reinterpret_cast< size_t >( this ) + offset );

	}

	inline auto& get_button_released( ) {

		static auto offset = g_netvars.find_in_datamap( get_prediction_desc_map( ), g_hash.const_hash( XOR( "m_afButtonReleased" ) ) );

		return *reinterpret_cast< int* >( reinterpret_cast< size_t >( this ) + offset );

	}

	inline auto get_impulse( ) {

		static auto offset = g_netvars.find_in_datamap( get_prediction_desc_map( ), g_hash.const_hash( XOR( "m_nImpulse" ) ) );

		return reinterpret_cast< int* >( reinterpret_cast< size_t >( this ) + offset );

	}

	inline auto& get_move_type( ) {

		static auto offset = g_netvars.find_in_datamap( get_prediction_desc_map( ), g_hash.const_hash( XOR( "m_MoveType" ) ) );

		return *reinterpret_cast< int* >( reinterpret_cast< size_t >( this ) + offset );

	}

	inline auto get_current_command( ) {

		static auto offset = g_netvars.m_offsets[ g_hash.get( XOR( "DT_BasePlayer->m_hConstraintEntity" ) ) ] - 0xC;

		return reinterpret_cast< user_cmd** >( reinterpret_cast< size_t >( this ) + offset );
	}

	inline auto& get_tickbase( ) {

		static auto offset = g_netvars.m_offsets[ g_hash.get( XOR( "DT_BasePlayer->m_nTickBase" ) ) ];

		return *reinterpret_cast< int* >( reinterpret_cast< size_t >( this ) + offset );

	}

	inline auto& get_punch( ) {

		static auto offset = g_netvars.m_offsets[ g_hash.get( XOR( "DT_BasePlayer->m_aimPunchAngle" ) ) ];

		return *reinterpret_cast< q_ang* >( reinterpret_cast< size_t >( this ) + offset );

	}

	inline auto& get_health( ) {

		static auto offset = g_netvars.m_offsets[ g_hash.get( XOR( "DT_BasePlayer->m_iHealth" ) ) ];

		return *reinterpret_cast< int* >( reinterpret_cast< size_t >( this ) + offset );

	}

	inline auto& get_flags( ) {

		static auto offset = g_netvars.m_offsets[ g_hash.get( XOR( "DT_BasePlayer->m_fFlags" ) ) ];

		return *reinterpret_cast< int* >( reinterpret_cast< size_t >( this ) + offset );

	}

	inline auto get_fall_velocity( ) {

		static auto offset = g_netvars.m_offsets[ g_hash.get( XOR( "DT_BasePlayer->m_flFallVelocity" ) ) ];

		return reinterpret_cast< float* >( reinterpret_cast< size_t >( this ) + offset );

	}

	inline auto get_next_think_tick( ) {

		static auto offset = g_netvars.m_offsets[ g_hash.get( XOR( "DT_BasePlayer->m_nNextThinkTick" ) ) ];

		return reinterpret_cast< int* >( reinterpret_cast< size_t >( this ) + offset );

	}

	inline auto* get_pose_parameter( ) {

		static auto offset = g_netvars.m_offsets[ g_hash.get( XOR( "DT_CSPlayer->m_flPoseParameter" ) ) ];

		return reinterpret_cast< float* >( reinterpret_cast< size_t >( this ) + offset );

	}

	inline auto& get_button_disabled( ) {

		return *reinterpret_cast< int* >( reinterpret_cast< size_t >( this ) + 0x3330 );

	}

	inline auto& get_button_forced( ) {

		return *reinterpret_cast< int* >( reinterpret_cast< size_t >( this ) + 0x3334 );

	}

	inline auto get_take_damage( ) {

		return *reinterpret_cast< int* >( reinterpret_cast< size_t >( this ) + 0x280 );
	}

	inline auto& get_last_command( ) {

		return *reinterpret_cast< user_cmd* >( reinterpret_cast< size_t >( this ) + 0x3288 );

	}

	inline auto update_buttons( user_cmd* cmd ) {

		cmd->m_buttons |= get_button_forced( );
		cmd->m_buttons &= ~( get_button_disabled( ) );

		const int buttons = cmd->m_buttons;
		int* player_buttons = get_buttons( );
		const int buttons_changed = buttons ^ *player_buttons;

		get_button_last( ) = *player_buttons;

		*get_buttons( ) = buttons;

		get_button_pressed( ) = buttons & buttons_changed;

		get_button_released( ) = buttons_changed & ~buttons;

	}

	inline auto is_enemy( base_entity* player ) {

		int this_team = get_team( );
		int player_team = player->get_team( );

		return this_team != player_team;

	}

};