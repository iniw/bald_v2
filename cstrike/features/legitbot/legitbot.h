#pragma once

#include "../../cstrike.h"
#include "autowall.h"

struct aimbot_data {

	aimbot_data( ) : m_ent( nullptr ), m_fov ( 0.f ), m_dmg( -1.f ) { }

	aimbot_data init( cs_player* player );

private:

	// closest record to the crosshair
	void setup_record( );

	// closest hitbox to the crosshair
	void setup_hitbox( );

public:

	// the entity
	cs_player* m_ent;
	// bone matrix
	matrix_3x4 m_matrix[ MAXSTUDIOBONES ];
	// position we are going to shoot
	vec_3 m_pos;
	// angle of the position and our eye position
	q_ang m_ang;
	// fov of that angle
	float m_fov;
	// damage we will deal
	float m_dmg;
	// closest record for that player
	lag_record* m_record;

};

struct legitbot {

	void run( user_cmd* cmd );

	void paint( );

	bool setup( );

	std::unique_ptr< aimbot_data > m_data;


private:

	void init( );

	vec_3 get_best_hitbox( cs_player* player, lag_record* record = nullptr );

	void finalize( );

	// list of our possible targets
	std::vector< aimbot_data > m_possible_targets;

	vec_3 m_eye_pos;

	struct {

		convar* weapon_recoil_scale;

	} m_convars;


};

inline legitbot g_legitbot;