#include "cstrike.h"

#include "hooked/hooked.h"
#include "render/render.h"

DWORD WINAPI cstrike::setup( void* parameter ) {

	HMODULE handle = static_cast< HMODULE >( parameter );

	g_console.setup( "cstrike-hack" );

	while ( !( g_cstrike.m_window = FindWindowA( "Valve001", nullptr ) ) )
		g_utils.sleep( 100 );

	if ( !g_interfaces.setup( ) || !g_netvars.setup( ) || !g_input.setup( ) || !g_render.setup( ) || !g_hooked.setup( ) ) {

		FreeLibraryAndExitThread( handle, EXIT_FAILURE );

		return EXIT_FAILURE;

	}

	while ( !g_input.is_key_down( VK_DELETE  ) )
		g_utils.sleep( 100 );

	g_console.log( "unloading" );

	unload( );

	FreeLibraryAndExitThread( handle, EXIT_SUCCESS );

	return EXIT_SUCCESS;

}

void cstrike::unload( ) {

	g_input.unload( );

	g_hooked.unload( );

	g_console.unload( );

	Beep( 400, 400 );

}

void cstrike::iterate_players( std::function< void( cs_player* ) > function, int flags ) {

	if ( !m_local_player )
		return;

	for ( int i = 1; i <= g_interfaces.m_globals->m_max_clients; i++ ) {

		cs_player* player = g_interfaces.m_entity_list->get< cs_player* >( i );
		if ( !player )
			continue;

		if ( !( flags & iterate_dead ) )
			if ( !player->is_alive( ) )
				continue;

		if ( !( flags & iterate_dormant ) )
			if ( player->is_dormant( ) )
				continue;

		if ( !( flags & iterate_teammates ) )
			if ( !player->is_enemy( m_local_player ) )
				continue;

		function( player );

	}

}