#include "interfaces.h"

bool interfaces::setup( ) {

	m_client = get< base_client_dll* >( g_pe.m_dlls.client, XOR( "VClient" ) );
	if ( !m_client )
		return false;

	m_entity_list = get< client_entity_list* >( g_pe.m_dlls.client, XOR( "VClientEntityList" ) );
	if ( !m_entity_list )
		return false;

	m_game_movement = get< game_movement* >( g_pe.m_dlls.client, XOR( "GameMovement" ) );
	if ( !m_game_movement )
		return false;

	m_prediction = get< prediction* >( g_pe.m_dlls.client, XOR( "VClientPrediction" ) );
	if ( !m_prediction )
		return false;

	m_debug_overlay = get< debug_overlay* >( g_pe.m_dlls.engine, XOR( "VDebugOverlay" ) );
	if ( !m_debug_overlay )
		return false;

	m_engine = get< engine_client* >( g_pe.m_dlls.engine, XOR( "VEngineClient" ) );
	if ( !m_engine )
		return false;

	m_model_info = get< model_info* >( g_pe.m_dlls.engine, XOR( "VModelInfoClient" ) );
	if ( !m_model_info )
		return false;

	m_trace = get< engine_trace* >( g_pe.m_dlls.engine, XOR( "EngineTraceClient" ) );
	if ( !m_trace )
		return false;

	m_surface = get< surface* >( g_pe.m_dlls.vguimatsurface, XOR( "VGUI_Surface" ) );
	if ( !m_surface )
		return false;

	m_material_system = get< material_system* >( g_pe.m_dlls.materialsystem, XOR( "VMaterialSystem" ) );
	if ( !m_material_system )
		return false;

	m_localize = get< localize* >( g_pe.m_dlls.localize, XOR( "Localize_" ) );
	if ( !m_localize )
		return false;

	m_mdl_cache = get< mdl_cache* >( g_pe.m_dlls.datacache, XOR( "MDLCache" ) );
	if ( !m_mdl_cache )
		return false;

	m_convar = get< con_var* >( g_pe.m_dlls.vstdlib, XOR( "VEngineCvar" ) );
	if ( !m_convar )
		return false;

	m_physics_props = get< physics_surface_props* >( g_pe.m_dlls.vphysics, XOR( "VPhysicsSurfaceProps" ) );
	if ( !m_physics_props )
		return false;

	m_move_helper = g_signatures.m_move_helper.add( 0x2 ).get< move_helper* >( 2 );
	if ( !m_move_helper ) {

		g_console.log( log_error, XOR( "error grabbing move_helper" ) );
		return false;

	}

	m_client_state = g_signatures.m_client_state.add( 0x1 ).get< client_state* >( 2 );
	if ( !m_client_state ) {
		
		g_console.log( log_error, XOR( "error grabbing client_state" ) );
		return false;

	}

	m_globals = g_utils.get_v_func( m_client, 11 ).add( 0xa ).get< global_vars_base* >( 2 );
	if ( !m_globals ) {

		g_console.log( log_error, XOR( "error grabbing globals" ) );
		return false;

	}

	m_net_graph_panel = g_signatures.m_net_graph_panel.add( 0x2 ).get< net_graph_panel* >( 2 );
	if ( !m_net_graph_panel ) {

		g_console.log( log_error, XOR( "error grabbing net_graph_panel" ) );
		return false;

	}

	g_console.log( log_completion, XOR( "setup interfaces" ) );

	return true;

}