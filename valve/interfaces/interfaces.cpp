#include "interfaces.h"

bool interfaces::setup( ) {

	g_console.log( "grabbing interfaces..." );

	m_client = get< base_client_dll* >( "client.dll", "VClient018" );
	if ( !m_client )
		return false;

	m_surface = get< surface* >( "vguimatsurface.dll", "VGUI_Surface031" );
	if ( !m_surface )
		return false;

	m_entity_list = get< client_entity_list* >( "client.dll", "VClientEntityList003" );
	if ( !m_entity_list )
		return false;

	m_debug_overlay = get< debug_overlay* >( "engine.dll", "VDebugOverlay004" );
	if ( !m_debug_overlay )
		return false;

	m_engine = get< engine_client* >( "engine.dll", "VEngineClient014" );
	if ( !m_engine )
		return false;

	m_localize = get< localize* >( "localize.dll", "Localize_001" );
	if ( !m_localize )
		return false;

	m_mdl_cache = get< mdl_cache* >( "datacache.dll", "MDLCache004" );
	if ( !m_mdl_cache )
		return false;

	m_model_info = get< model_info* >( "engine.dll", "VModelInfoClient004" );
	if ( !m_model_info )
		return false;

	m_trace = get< engine_trace* >( "engine.dll", "EngineTraceClient004" );
	if ( !m_trace )
		return false;

	m_convar = get< con_var* >( "vstdlib.dll", "VEngineCvar007" );
	if ( !m_convar )
		return false;

	m_game_movement = get< game_movement* >( "client.dll", "GameMovement001" );
	if ( !m_game_movement )
		return false;

	m_prediction = get< prediction* >( "client.dll", "VClientPrediction001" );
	if ( !m_prediction )
		return false;

	m_physics_props = get< physics_surface_props* >( "vphysics.dll", "VPhysicsSurfaceProps001" );
	if ( !m_physics_props )
		return false;

	m_move_helper = g_pattern.find( "client.dll", "8B 0D ? ? ? ? 8B 46 08 68" ).add( 0x2 ).get< move_helper* >( 2 );
	if ( !m_move_helper )
		return false;

	g_console.log( "m_move_helper -> 0x%x", m_move_helper );

	m_client_state = g_pattern.find( "engine.dll", "A1 ? ? ? ? 8B 88 ? ? ? ? 85 C9 75 07" ).add( 0x1 ).get< client_state* >( 2 );
	if ( !m_client_state )
		return false;

	g_console.log( "m_client_state -> 0x%x", m_client_state );

	m_globals = g_utils.get_v_func( m_client, 11 ).add( 0xa ).get< global_vars_base* >( 2 );
	if ( !m_globals )
		return false;

	g_console.log( "m_globals -> 0x%x", m_globals );

	g_console.log( "grabbed interfaces" );

	return true;

}