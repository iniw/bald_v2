#pragma once

#include "../../cstrike.h"
#include "autowall.h"

struct aimbot_data {

	aimbot_data( ) : m_ent( nullptr ), m_fov ( 0.f ), m_dmg( -1.f ) { };

	inline void init( cs_player* player, lag_record* record = nullptr ) {

		m_ent = player;

		m_pos = m_ent->get_hitbox_position( hitbox_head );
		m_ang = g_math.calc_angle( g_cstrike.m_local->get_eye_position( ), m_pos ).sanitize( );
		m_fov = g_math.calc_fov( g_cstrike.m_cmd->m_view_angles, m_ang );

		m_dmg = g_autowall.get_damage( m_pos, record, m_ent );

	}

	inline void clear( ) {

		m_ent = nullptr;
		m_pos = { 0.f, 0.f, 0.f };
		m_ang = { 0.f, 0.f, 0.f };
		m_fov = 0.f;
		m_dmg = -1.f;

	}

	inline operator bool( ) {

		return m_ent;

	}

	cs_player* m_ent;
	vec_3 m_pos;
	q_ang m_ang;
	float m_fov;
	float m_dmg;
	lag_record m_record;

};

struct legitbot {

	void run( user_cmd* cmd );

	std::unique_ptr< aimbot_data > get_data( user_cmd* cmd );

	void finalize_angle( );

	void apply_angle( );

	void paint( );

	std::unique_ptr< aimbot_data > m_data;

};

inline legitbot g_legitbot;