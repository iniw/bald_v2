#include "engine_prediction.h"
#include "../../../other/hash/md5.h"

void engine_prediction::start( user_cmd* cmd ) {

	if ( !g_cstrike.m_local->is_alive( ) )
		return;

	*g_cstrike.m_local->get_current_command( ) = cmd;
	g_cstrike.m_local->get_last_command( ) = *cmd;

	*m_prediction_random_seed = g_md5.pseudo_random( cmd->m_command_number ) & 0x7FFFFFFF;

	m_prediction_entity = g_cstrike.m_local;

	m_old_curtime    = g_interfaces.m_globals->m_curtime;
	m_old_frametime  = g_interfaces.m_globals->m_frametime;
	m_old_tick_count = g_interfaces.m_globals->m_tickcount;

	const bool old_is_first_prediction = g_interfaces.m_prediction->m_is_first_time_predicted;
	const bool old_in_prediction = g_interfaces.m_prediction->m_in_prediction;

	g_interfaces.m_globals->m_curtime   = g_cstrike.ticks_to_time( get_tickbase( cmd ) );
	g_interfaces.m_globals->m_frametime = g_interfaces.m_prediction->m_engine_paused ? 0.f : g_interfaces.m_globals->m_interval_per_tick;
	g_interfaces.m_globals->m_tickcount = get_tickbase( cmd );

	g_interfaces.m_prediction->m_is_first_time_predicted = false;
	g_interfaces.m_prediction->m_in_prediction = true;

	if ( cmd->m_impulse )
		*g_cstrike.m_local->get_impulse( ) = cmd->m_impulse;

	g_cstrike.m_local->update_buttons( cmd );

	g_interfaces.m_prediction->set_local_view_angles( cmd->m_view_angles );

	if ( g_cstrike.m_local->physics_run_think( 0 ) )
		g_cstrike.m_local->pre_think( );

	int* next_think_tick = g_cstrike.m_local->get_next_think_tick( );

	if ( *next_think_tick > 0 && *next_think_tick <= get_tickbase( cmd ) ) {

		*next_think_tick = -1;
		g_cstrike.m_local->think( );

	}

	g_interfaces.m_move_helper->set_host( g_cstrike.m_local );

	g_interfaces.m_game_movement->start_track_prediction_errors( g_cstrike.m_local );

	g_interfaces.m_prediction->check_moving_ground( g_cstrike.m_local, g_interfaces.m_globals->m_frametime );

	g_interfaces.m_prediction->setup_move( g_cstrike.m_local, cmd, g_interfaces.m_move_helper, &m_move_data );

	g_interfaces.m_game_movement->process_movement( g_cstrike.m_local, &m_move_data );

	g_interfaces.m_prediction->finish_move( g_cstrike.m_local, cmd, &m_move_data );

	g_interfaces.m_move_helper->process_impacts( );

	g_interfaces.m_game_movement->finish_track_prediction_errors( g_cstrike.m_local );

	g_cstrike.m_local->post_think( );

	g_interfaces.m_prediction->m_in_prediction = old_in_prediction;
	g_interfaces.m_prediction->m_is_first_time_predicted = old_is_first_prediction;
							   
}

void engine_prediction::end( user_cmd* cmd ) {

	if ( !g_cstrike.m_local->is_alive( ) )
		return;

	g_interfaces.m_move_helper->set_host( nullptr );

	g_interfaces.m_globals->m_curtime   = m_old_curtime;
	g_interfaces.m_globals->m_frametime = m_old_frametime;
	g_interfaces.m_globals->m_tickcount = m_old_tick_count;

	*g_cstrike.m_local->get_current_command( ) = nullptr;

	*m_prediction_random_seed = -1;

	m_prediction_entity = nullptr;

	g_interfaces.m_game_movement->reset( );

}

void engine_prediction::update( ) {

	if ( !g_cstrike.m_local->is_alive( ) )
		return;

	if ( g_interfaces.m_client_state->m_delta_tick > 0 ) {

		g_interfaces.m_prediction->update( g_interfaces.m_client_state->m_delta_tick,
										 g_interfaces.m_client_state->m_delta_tick > 0,
										 g_interfaces.m_client_state->m_last_command_ack,
										 g_interfaces.m_client_state->m_last_outgoing_command + g_interfaces.m_client_state->m_choked_commands );
	}

}

int engine_prediction::get_tickbase( user_cmd* cmd ) {

	static int tick = 0;
	static user_cmd* last_cmd = nullptr;

	if ( cmd != nullptr ) {

		if ( last_cmd == nullptr || last_cmd->m_has_been_predicted )
			tick = g_cstrike.m_local->get_tickbase( );
		else
			tick++;

		last_cmd = cmd;
	}

	return tick;

}

bool engine_prediction::setup( ) {

	m_prediction_random_seed = g_utils.get_v_func( g_interfaces.m_prediction, 19).add( 0x30 ).get< int* >( );
	m_prediction_entity = g_utils.get_v_func( g_interfaces.m_prediction, 19 ).add( 0x54 ).get< base_player* >( );

	return m_prediction_entity && m_prediction_random_seed;

}
