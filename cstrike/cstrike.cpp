#include "cstrike.h"

#include "hooked/hooked.h"
#include "render/render.h"

DWORD WINAPI cstrike::setup( void* parameter ) {

	g_cstrike.m_handle = static_cast< HMODULE >( parameter );
	
	g_console.setup( ); g_pe.setup( ); g_winapi.setup( );

	while ( !( g_cstrike.m_window = g_winapi.find_window( XOR( "Valve001" ), nullptr ) ) )
		g_utils.sleep( 100 );

	if ( !g_signatures.setup( ) || !g_interfaces.setup( ) || !g_file_system.setup( ) ||
		!g_backtracking.setup( ) || !g_engine_prediction.setup( ) || !g_legitbot.setup( ) ||
		!g_netvars.setup( ) || !g_input.setup( ) || !g_render.setup( ) || !g_hooks.setup( ) ) {

		g_utils.sleep( 1000 );

		FreeLibraryAndExitThread( g_cstrike.m_handle, EXIT_FAILURE );

		return EXIT_FAILURE;

	}

	while ( !g_input.is_key_down( VK_DELETE  ) )
		g_utils.sleep( 100 );

	g_console.log( XOR( "unloading" ) );

	return unload( EXIT_SUCCESS );

}

int cstrike::unload( int exit ) {

	g_input.unload( );

	g_hooks.unload( );

	g_console.unload( );

	FreeLibraryAndExitThread( g_cstrike.m_handle, exit );

	return exit;


}

void cstrike::iterate_players( std::function< void( cs_player* ) > function, int flags ) {

	if ( !m_local )
		return;

	for ( int i = 1; i <= g_interfaces.m_globals->m_max_clients; i++ ) {

		cs_player* player = g_interfaces.m_entity_list->get< cs_player* >( i );

		if ( !validate_player( player, flags ) )
			continue;

		function( player );

	}

}

cs_player* cstrike::get_nearest_player( search_type type, int flags ) {

	if ( !m_local )
		return nullptr;

	cs_player* best_player = nullptr;
	float best_distance = FLT_MAX;	

	for ( int i = 1; i <= g_interfaces.m_globals->m_max_clients; i++ ) {

		cs_player* player = g_interfaces.m_entity_list->get< cs_player* >( i );

		if ( !validate_player( player, flags ) )
			continue;

		const float fov = g_math.calc_fov( m_cmd->m_view_angles, m_eye_pos, player->get_eye_position( ) );

		if ( fov < best_distance ) {

			best_distance = fov;
			best_player = player;

		}

	}

	return best_player;

}
