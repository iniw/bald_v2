#pragma once

#include "base_entity.h"

struct base_combat_character : base_entity {

	inline auto& get_active_weapon( ) {

		static auto offset = g_netvars.m_offsets[ g_hash.get( XOR( "DT_BaseCombatCharacter->m_hActiveWeapon" ) ) ];

		return *reinterpret_cast< size_t* >( reinterpret_cast< size_t >( this ) + offset );

	}

	inline auto& get_next_attack( ) {

		static auto offset = g_netvars.m_offsets[ g_hash.get( XOR( "DT_BaseCombatCharacter->m_flNextAttack" ) ) ];

		return *reinterpret_cast< float* >( reinterpret_cast< size_t >( this ) + offset );

	}

};