#pragma once

#include "../../cstrike.h"
#include "backtracking.h"

struct awall_data {

	awall_data( ) : m_dmg( 0.f ), m_pen_count( 0 ) { }

	awall_data( const vec_3& pos, const vec_3& point ) : m_dmg( 0.f ), m_pen_count( 0 ), m_pos( pos ) {

		m_dir = ( point - m_pos ).normalized( );

	}

	vec_3 m_pos;
	vec_3 m_dir;
	trace m_trace;
	float m_dmg;
	int	  m_pen_count;

};

struct autowall {

	float get_damage( const vec_3& point,lag_record* record = nullptr, cs_player* player = nullptr );

private:

	bool simulate_shot( weapon_cs_base* weapon, awall_data& data );

	void clip_trace_to_players( const vec_3& start, const vec_3& end, unsigned int mask, trace_filter* filter, trace* ray_trace );

	void scale_damage( int hitgroup, cs_player* player, float weapon_armor_ratio, float& damage );

	bool handle_bullet_penetration( cs_weapon_info* weapon_info, surface_data* result_surface_data, awall_data& data );

	bool trace_to_exit( trace& enter_trace, trace& exit_trace, vec_3 position, vec_3 direction );

	bool is_breakable_entity( base_player* entity );

};

inline autowall g_autowall;