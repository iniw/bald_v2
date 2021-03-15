#pragma once

#include "../../cstrike.h"
#include "autowall.h"

struct aimbot_data {

	aimbot_data( ) {

		ent = nullptr;
		pos = { 0.f, 0.f, 0.f };
		ang = { 0.f, 0.f, 0.f };
		fov = 0.f;
		dmg = -1.f;

	};

	aimbot_data( cs_player* player ) {

		ent = player;

		if ( ent ) {

			pos = ent->get_hitbox_position( hitbox::head );
			ang = g_math.calc_angle( g_cstrike.m_local_player->get_eye_position( ), pos ).sanitize( );
			fov = g_math.calc_fov( g_interfaces.m_engine->get_view_angles( ), ang );
			dmg = g_autowall.get_damage( pos );

		} else {

			pos = { 0.f, 0.f, 0.f };
			ang = { 0.f, 0.f, 0.f };
			fov = 0.f;
			dmg = -1.f;

		}

	}

	void clear( ) {

		ent = nullptr;
		pos = { 0.f, 0.f, 0.f };
		ang = { 0.f, 0.f, 0.f };
		fov = 0.f;
		dmg = -1.f;

	}

	bool operator!( ) {

		return ent == nullptr;

	}

	cs_player* ent;
	vec_3      pos;
	q_angle    ang;
	float      fov;
	float	   dmg;

};

struct legitbot {

	void run( user_cmd* cmd );

	aimbot_data get_data( user_cmd* cmd );

	void finalize_angle( );

	void apply_angle( );

	void paint( );

	aimbot_data m_data;

};

inline legitbot g_legitbot;