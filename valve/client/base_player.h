#pragma once

#include "base_combat_character.h"
#include "../shared/user_cmd.h"

struct base_player : base_combat_character {

	inline auto update_collision_bounds( ) {

		return g_utils.call_v_func< void >( this, 339 );

	}

	inline auto is_max_health( ) {

		return g_utils.call_v_func< int >( this, 122 );

	}

	inline auto get_eye_position( ) {

		vec_3 vec_out;

		g_utils.call_v_func< void, vec_3& >( this, 168, vec_out );

		return vec_out;

	}

	inline auto get_take_damage( ) {

		static auto offset = 0x280;

		return *reinterpret_cast< int* >( reinterpret_cast< std::size_t >( this ) + offset );
	}

	inline auto get_current_command( ) {

		static auto offset = g_netvars.m_offsets[ g_hash.get( "DT_BasePlayer->m_hConstraintEntity" ) ];

		return reinterpret_cast< user_cmd** >( reinterpret_cast< std::size_t >( this ) + offset - 0xC );
	}

	inline auto& get_last_command( ) {

		return *reinterpret_cast< user_cmd* >( reinterpret_cast< std::size_t >( this ) + 0x3288 );

	}

	inline auto& get_tickbase( ) {

		static auto offset = g_netvars.m_offsets[ g_hash.get( "DT_BasePlayer->m_nTickBase" ) ];

		return *reinterpret_cast< int* >( reinterpret_cast< std::size_t >( this ) + offset );

	}

	inline auto get_buttons( ) {

		static auto offset = g_netvars.find_in_datamap( this->get_prediction_desc_map( ), g_hash.get( "m_nButtons" ) );

		return reinterpret_cast< int* >( reinterpret_cast< std::size_t >( this ) + offset );

	}

	inline auto& get_button_disabled( ) {

		return *reinterpret_cast< int* >( reinterpret_cast< std::size_t >( this ) + 0x3330 );

	}

	inline auto& get_button_forced( ) {

		return *reinterpret_cast< int* >( reinterpret_cast< std::size_t >( this ) + 0x3334 );

	}

	inline auto& get_button_last( ) {

		static auto offset = g_netvars.find_in_datamap( this->get_prediction_desc_map( ), g_hash.get( "m_afButtonLast" ) );

		return *reinterpret_cast< int* >( reinterpret_cast< std::size_t >( this ) + offset );

	}

	inline auto& get_button_pressed( ) {

		static auto offset = g_netvars.find_in_datamap( this->get_prediction_desc_map( ), g_hash.get( "m_afButtonPressed" ) );

		return *reinterpret_cast< int* >( reinterpret_cast< std::size_t >( this ) + offset );

	}

	inline auto& get_button_released( ) {

		static auto offset = g_netvars.find_in_datamap( this->get_prediction_desc_map( ), g_hash.get( "m_afButtonReleased" ) );

		return *reinterpret_cast< int* >( reinterpret_cast< std::size_t >( this ) + offset );

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

	inline auto get_impulse( ) {

		static auto offset = g_netvars.find_in_datamap( this->get_prediction_desc_map( ), g_hash.get( "m_nImpulse" ) );

		return reinterpret_cast< int* >( reinterpret_cast< std::size_t >( this ) + offset );

	}

	inline auto& get_health( ) {

		static auto offset = g_netvars.m_offsets[ g_hash.get( "DT_BasePlayer->m_iHealth" ) ];

		return *reinterpret_cast< int* >( reinterpret_cast< std::size_t >( this ) + offset );

	}

	inline auto& get_flags( ) {

		static auto offset = g_netvars.m_offsets[ g_hash.get( "DT_BasePlayer->m_fFlags" ) ];

		return *reinterpret_cast< int* >( reinterpret_cast< std::size_t >( this ) + offset );

	}

	inline auto get_fall_velocity( ) {

		static auto offset = g_netvars.m_offsets[ g_hash.get( "DT_BasePlayer->m_flFallVelocity" ) ];

		return reinterpret_cast< float* >( reinterpret_cast< std::size_t >( this ) + offset );

	}

	inline auto get_next_think_tick( ) {

		static auto offset = g_netvars.m_offsets[ g_hash.get( "DT_BasePlayer->m_nNextThinkTick" ) ];

		return reinterpret_cast< int* >( reinterpret_cast< std::size_t >( this ) + offset );

	}

	inline auto* get_pose_parameter( ) {

		static auto offset = g_netvars.m_offsets[ g_hash.get( "DT_CSPlayer->m_flPoseParameter" ) ];

		return reinterpret_cast< float* >( reinterpret_cast< std::size_t >( this ) + offset );

	}

	inline auto util_player_by_index( int entindex ) {

		auto function = g_signatures.m_util_player_by_index.as< base_player* ( __thiscall* )( int ) >( );

		return function( entindex );

	}

	inline auto is_enemy( base_player* player ) {

		int this_team = this->get_team( );
		int player_team = player->get_team( );

		return this_team != player_team;

	}

};