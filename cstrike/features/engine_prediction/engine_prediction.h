#pragma once

#include "../../cstrike.h"

struct engine_prediction {

	engine_prediction( ) {

		m_prediction_random_seed = g_signatures.m_prediction_random_seed.add( 0x2 ).get< int* >( );
		m_prediction_entity      = g_signatures.m_prediction_entity.add( 0x2 ).get< base_player* >( );

	}

	void start( user_cmd* cmd );
	void end( user_cmd* cmd );
	void update( );

	int get_tickbase( user_cmd* cmd );

private:

	int* m_prediction_random_seed = nullptr;

	base_player* m_prediction_entity = nullptr;

	move_data m_move_data = { };

	float m_old_curtime = 0.f;
	float m_old_frametime = 0.f;
	int   m_old_tick_count = 0;

};

inline engine_prediction g_engine_prediction;