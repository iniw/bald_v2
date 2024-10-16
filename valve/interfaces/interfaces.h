#pragma once

#include <string>

#include "../cdll_int.h"
#include "../prediction.h"
#include "../vgui/surface.h"
#include "../client_entity_list.h"
#include "../engine/debug_overlay.h"
#include "../engine/trace.h"
#include "../engine/model_info.h"
#include "../engine/convar.h"
#include "../global_vars_base.h"
#include "../tier1/localize.h"
#include "../tier1/interface.h"
#include "../data_cache/mdl_cache.h"
#include "../client/client_state.h"
#include "../client/net_graph_panel.h"
#include "../physics/physics_surface_props.h"
#include "../material_system/material_system.h"

#include "../../other/console/console.h"

#include <fstream>

struct interfaces {

	bool setup( );

	base_client_dll*       m_client;
	surface*               m_surface;
	client_entity_list*    m_entity_list;
	debug_overlay*         m_debug_overlay;
	global_vars_base*      m_globals;
	engine_client*         m_engine;
	localize*              m_localize;
	mdl_cache*             m_mdl_cache;
	model_info*            m_model_info;
	engine_trace*          m_trace;
	con_var*               m_convar;
	game_movement*         m_game_movement;
	move_helper*           m_move_helper;
	prediction*			   m_prediction;
	client_state*		   m_client_state;
	physics_surface_props* m_physics_props;
	material_system*       m_material_system;
	net_graph_panel*	   m_net_graph_panel;

private:

	template< class t > inline t get( address module_base, std::string_view interface_name ) {

		static const auto fn_hash = g_hash.get( XOR( "CreateInterface" ) );

		auto create_interface = g_pe.export_fn( module_base, fn_hash );
		if ( !create_interface ) {

			g_console.log( log_error, XOR( "failed to import create_interface from the module" ) );
			return t( );

		}

		auto create_interface_fn = create_interface.add( 0x4 ).absolute( );
		if ( !create_interface_fn ) {

			g_console.log( log_error, XOR( "failed to find create_interface_fn" ) );
			return t( );

		}
		auto interface_node = create_interface_fn.add( 0x6 ).get< interface_reg* >( 2 );

		while ( interface_node != nullptr ) {

			std::string name = interface_node->m_name;

			if ( !name.compare( 0u, interface_name.length( ), interface_name )
				&& std::atoi( interface_node->m_name + interface_name.length( ) ) > 0 ) {	

				auto interface_address = interface_node->m_create_fn( );
				if ( !interface_address )
					return t( );

				return ( t )interface_address;

			}

			interface_node = interface_node->m_next;

		}

		g_console.log( log_error, XOR( "failed to find %s interface" ), interface_name );

		return t( );

	}

};

inline interfaces g_interfaces;