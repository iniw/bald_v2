#pragma once

#include "../../cstrike.h"

struct bulet_data {

	bulet_data( ) : m_current_damage( 0.f ), m_penetration_count( 0 ) { }

	vec_3 m_position;
	vec_3 m_direction;
	trace m_trace;
	float m_current_damage;
	int	  m_penetration_count;

};

struct autowall {

	float get_damage( const vec_3& point );

private:

	bool simulate_fire_bullet( weapon_cs_base* weapon, bulet_data& data );

	void clip_trace_to_players( const vec_3& start, const vec_3& end, unsigned int mask, base_trace_filter* filter, trace* ray_trace );

	void scale_damage( int hit_group, cs_player* player, float weapon_armor_ratio, float& damage );

	bool handle_bullet_penetration( cs_weapon_info* weapon_info, surface_data* result_surface_data, bulet_data& data );

	bool trace_to_exit( trace& enter_trace, trace& exit_trace, vec_3 position, vec_3 direction );

	bool is_breakable_entity( base_player* entity );

};

inline autowall g_autowall;