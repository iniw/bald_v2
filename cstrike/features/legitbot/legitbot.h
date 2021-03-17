#pragma once

#include "../../cstrike.h"
#include "autowall.h"

struct aimbot_data {

	aimbot_data( ) : m_ent( nullptr ), m_fov ( 0.f ), m_dmg( -1.f ) { }

	inline void init( cs_player* player, lag_record* record = nullptr ) {

		m_ent = player;

		record ? m_record = *record : m_record = lag_record( );

		m_pos = m_ent->get_hitbox_position( hitbox_head, record );
		m_ang = g_math.calc_angle( g_cstrike.m_local->get_eye_position( ), m_pos ).sanitize( );
		m_fov = g_math.calc_fov( g_cstrike.m_cmd->m_view_angles, m_ang );
		m_dmg = g_autowall.get_damage( m_pos, record, m_ent );

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

	void finalize( );

	void paint( );

	bool setup( );

	bool m_ative;

	std::unique_ptr< aimbot_data > m_data;

	struct {

		convar* weapon_recoil_scale;

	} m_convars;

};

inline legitbot g_legitbot;