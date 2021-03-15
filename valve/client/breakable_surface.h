#pragma once

#include "base_entity.h"
#include "../../valve/physics/multiplayer_physics.h"

struct breakable_surface : public base_entity, public breakable_with_prop_data {

	inline auto& is_broken( ) {

		static auto offset = g_netvars.m_offsets[ g_hash.get( "DT_BreakableSurface->m_bIsBroken" ) ];

		return *reinterpret_cast< bool* >( reinterpret_cast< std::size_t >( this ) + offset );

	}

};