#include "interfaces.h"

bool interfaces::setup( ) {

	g_console.log( XOR( "grabbing interfaces..." ) );

	m_client = get< base_client_dll* >( CLIENT_DLL, XOR( "VClient" ) );
	if ( !m_client )
		return false;

	m_entity_list = get< client_entity_list* >( CLIENT_DLL, XOR( "VClientEntityList" ) );
	if ( !m_entity_list )
		return false;

	m_game_movement = get< game_movement* >( CLIENT_DLL, XOR( "GameMovement" ) );
	if ( !m_game_movement )
		return false;

	m_prediction = get< prediction* >( CLIENT_DLL, XOR( "VClientPrediction" ) );
	if ( !m_prediction )
		return false;

	m_debug_overlay = get< debug_overlay* >( ENGINE_DLL, XOR( "VDebugOverlay" ) );
	if ( !m_debug_overlay )
		return false;

	m_engine = get< engine_client* >( ENGINE_DLL, XOR( "VEngineClient" ) );
	if ( !m_engine )
		return false;

	m_model_info = get< model_info* >( ENGINE_DLL, XOR( "VModelInfoClient" ) );
	if ( !m_model_info )
		return false;

	m_trace = get< engine_trace* >( ENGINE_DLL, XOR( "EngineTraceClient" ) );
	if ( !m_trace )
		return false;

	m_surface = get< surface* >( VGUIMATSURFACE_DLL, XOR( "VGUI_Surface" ) );
	if ( !m_surface )
		return false;

	m_material_system = get< material_system* >( MATERIALSYSTEM_DLL, XOR( "VMaterialSystem" ) );
	if ( !m_material_system )
		return false;

	m_localize = get< localize* >( LOCALIZE_DLL, XOR( "Localize_" ) );
	if ( !m_localize )
		return false;

	m_mdl_cache = get< mdl_cache* >( DATACACHE_DLL, XOR( "MDLCache" ) );
	if ( !m_mdl_cache )
		return false;

	m_convar = get< con_var* >( VSTDLIB_DLL, XOR( "VEngineCvar" ) );
	if ( !m_convar )
		return false;

	m_physics_props = get< physics_surface_props* >( VPHYSICS_DLL, XOR( "VPhysicsSurfaceProps" ) );
	if ( !m_physics_props )
		return false;

	m_move_helper = g_signatures.m_move_helper.add( 0x2 ).get< move_helper* >( 2 );
	if ( !m_move_helper )
		return false;

	g_console.log( XOR( "m_move_helper -> 0x%x" ), m_move_helper );

	m_client_state = g_signatures.m_client_state.add( 0x1 ).get< client_state* >( 2 );
	if ( !m_client_state )
		return false;

	g_console.log( XOR( "m_client_state -> 0x%x" ), m_client_state );

	m_globals = g_utils.get_v_func( m_client, 11 ).add( 0xa ).get< global_vars_base* >( 2 );
	if ( !m_globals )
		return false;

	g_console.log( XOR( "m_globals -> 0x%x" ), m_globals );

	g_console.log( XOR( "grabbed interfaces" ) );

	return true;

}