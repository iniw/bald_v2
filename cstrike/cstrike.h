#pragma once

#include <functional>

#include "config.h"

#include "../other/other.h"
#include "../valve/valve.h"

enum iterate_player_flags {

	valid_dead      = 1 << 0,
	valid_dormant   = 1 << 1,
	valid_teammates = 1 << 2,
	valid_immune	= 1 << 2,

};

enum search_type {

	search_crosshair = 0,  // nearest eye to the crosshair
	search_distance        // nearest origin to local origin

};

struct cstrike {

	static DWORD WINAPI setup( void* parameter );

	static void unload( );

	void iterate_players( std::function< void( cs_player* ) > function, int flags = { } );

	cs_player* get_nearest_player( search_type type, int flags = { } );

	inline bool validate_player( cs_player* player, int flags = { } ) {

		if ( !player )
			return false;

		if ( player == m_local )
			return false;

		if ( !player->is_player( ) )
			return false;

		if ( !( flags & valid_dead ) )
			if ( !player->is_alive( ) )
				return false;

		if ( !( flags & valid_dormant ) )
			if ( player->is_dormant( ) )
				return false;

		if ( !( flags & valid_teammates ) )
			if ( !player->is_enemy( m_local ) )
				return false;

		if ( !( flags & valid_immune ) )
			if ( player->is_immune( ) )
				return false;

		return true;

	}

	inline size_t time_to_ticks( float time ) {

		return static_cast< size_t >( 0.5f + static_cast< float >( time ) / g_interfaces.m_globals->m_interval_per_tick );

	}

	inline float ticks_to_time( size_t ticks ) {

		return g_interfaces.m_globals->m_interval_per_tick * static_cast< float >( ticks );

	}

	HWND m_window;

	cs_player* m_local;

	user_cmd*  m_cmd;

};

inline cstrike g_cstrike;