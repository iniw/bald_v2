#pragma once

#include <unordered_map>
#include <polyhook2/Detour/x86Detour.hpp>
#include <polyhook2/CapstoneDisassembler.hpp>

#include "../../other/hash/hash.h"

// this should be an inherinted class from x86Detour but Fvck It
struct detour_hook {

	detour_hook( ) : m_target( 0 ), m_tramp( 0 ), m_org( 0 ), m_dis( nullptr ), m_detour( nullptr ) { }

	detour_hook( void* target, void* tramp ) : m_target( ( uint64_t )target ), m_tramp( ( uint64_t )tramp ), m_org( 0 ), m_dis( nullptr ), m_detour( nullptr ) { }

	~detour_hook( ) {

		// goodbye my children :sob: sob:

		delete m_dis;
		delete m_detour;

	}

	inline bool init( ) {

		m_dis = new PLH::CapstoneDisassembler( PLH::Mode::x86 );
		m_detour = new PLH::x86Detour( m_target, m_tramp, &m_org, *m_dis );

		return m_detour->hook( );

	}

	uint64_t m_target;
	uint64_t m_tramp;
	uint64_t m_org;

	PLH::CapstoneDisassembler* m_dis;
	PLH::x86Detour* m_detour;

};

struct detour {

	bool setup( std::string_view name, void* function, void* custom_function );

	void unload( );

	template< typename t > inline t get( std::string_view name ) {

		auto& obj = m_detours[ g_hash.get( name ) ];

		return PLH::FnCast( obj.m_org, reinterpret_cast< t >( obj.m_target ) );

	}

private:

	std::unordered_map< size_t, detour_hook > m_detours;

};

inline detour g_detour;