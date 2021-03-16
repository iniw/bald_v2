#include "visuals.h"

#include <algorithm>

#include "../../render/render.h"

void visuals::paint( ) {

	g_cstrike.iterate_players( [ this ]( cs_player* player ) -> void {

		m_player = {

			player,
			player->get_index( ) - 1,
			player->is_dormant( ),

		};

		if ( !calculate_box( ) )
			return;

		calculate_alpha( );

		draw_box( );

		draw_health( );

		draw_name( );

		draw_weapon( );

		}, { iterate_dormant } );

}

void visuals::draw_box( ) {

	g_render.draw_outlined_rect( m_box.x - 1, m_box.y - 1, 
		m_box.width + 2, m_box.height + 2, 
		color( 0, 0, 0, m_alpha[ m_player.idx ] ) );

	g_render.draw_outlined_rect( m_box.x + 1, m_box.y + 1, 
		m_box.width - 2, m_box.height - 2, 
		color( 0, 0, 0, m_alpha[ m_player.idx ] ) );

	g_render.draw_outlined_rect( m_box.x, m_box.y,
		m_box.width, m_box.height, 
		color( 255, 255, 255, m_alpha[ m_player.idx ] ) );

}

void visuals::draw_health( ) {

	int health = m_player.pointer->get_health( ), 
		scaler = static_cast< int >( 2.55 * health );

	g_render.draw_filled_rect( m_box.x - 2, m_box.y - 1, 
		4, m_box.height + 2, 
		color( 0, 0, 0, m_alpha[ m_player.idx ] ), 
		x_right );

	g_render.draw_filled_rect( m_box.x - 3, m_box.y, 
		2, health * m_box.height / 100, 
		color( 255 - scaler, scaler, 0, m_alpha[ m_player.idx ] ),
		x_right );

	if ( health == 100 )
		return;

	g_render.draw_text( g_render.m_fonts.secondary, 
		m_box.x - 5, m_box.y + health * m_box.height / 100, 
		std::to_wstring( health ), 
		color( 255, 255, 255, m_alpha[ m_player.idx ] ), 
		x_centre | y_centre );

}

void visuals::draw_name( ) {

	player_info info;
	if ( !g_interfaces.m_engine->get_player_info( m_player.idx + 1, &info ) )
		return;

	std::string name = info.m_name;

	if ( !info.m_xuid_low )
		name.append( XOR( " - bot" ) );

	g_render.draw_text( g_render.m_fonts.primary,
		m_box.x + m_box.width / 2, m_box.y - 1, 
		name, 
		color( 255, 255, 255, m_alpha[ m_player.idx ] ), 
		x_centre | y_bottom );

}

void visuals::draw_weapon( ) {

	weapon_cs_base* weapon = g_interfaces.m_entity_list->get< weapon_cs_base* >( m_player.pointer->get_active_weapon( ) );
	if ( !weapon )
		return;

	cs_weapon_info* weapon_info = weapon->get_cs_wpn_data( );
	if ( !weapon_info )
		return;

	std::wstring weapon_name = g_interfaces.m_localize->find( weapon_info->m_hud_name );
	std::transform( weapon_name.begin( ), weapon_name.end( ), weapon_name.begin( ), std::toupper );

	g_render.draw_text( g_render.m_fonts.secondary,
		m_box.x + m_box.width / 2, m_box.y + m_box.height + 1,
		weapon_name,
		color( 255, 255, 255, m_alpha[ m_player.idx ] ),
		x_centre );

}

void visuals::calculate_alpha( ) {

	float delta_time = g_interfaces.m_globals->m_curtime - m_player.pointer->get_simulation_time( );

	float opacity = m_player.is_dormant ? g_easing.out_quint( 1.f - std::clamp( delta_time, 0.f, 0.8f ) ) : 0.8f;

	m_alpha[ m_player.idx ] = static_cast< int >( 255 * opacity );

}

bool visuals::calculate_box( ) {

	vec_3 mins, maxs;
	m_player.pointer->get_render_bounds( mins, maxs );

	vec_3 origin = m_player.pointer->get_origin( ), screen_origin;
	origin.z -= 5.f;

	vec_3 top = m_player.pointer->get_origin( ), screen_top;
	top.z += maxs.z;

	if ( g_interfaces.m_debug_overlay->screen_position( origin, screen_origin ) == -1
		|| g_interfaces.m_debug_overlay->screen_position( top, screen_top ) == -1 )
		return false;

	float height = screen_origin.y - screen_top.y;
	float width = height / 2;

	m_box = {

		static_cast< int >( screen_origin.x - width / 2 ),
		static_cast< int >( screen_top.y ),
		static_cast< int >( width ),
		static_cast< int >( height )

	};

	return true;

}