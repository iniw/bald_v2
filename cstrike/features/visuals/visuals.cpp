#include "visuals.h"

#include <algorithm>

#include "../../render/render.h"

void visuals::paint( ) {

	draw_watermark( );

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

		}, { valid_dormant } );

}

void visuals::draw_watermark( ) {

	const int fps = static_cast< int >( 1.f / g_interfaces.m_net_graph_panel->m_frame_rate );

	g_render.draw_text( g_render.m_fonts.secondary,
		g_render.m_screen.w - 5, 5,
		g_render.format_text( XOR( "bald_v2 | local: 0x%x | fps: %d" ), g_cstrike.m_local, fps ),
		color( 255, 255, 255 ),
		x_right );

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

	int health = m_player.ptr->get_health( ), 
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
		g_render.format_text( XOR( "%d" ), health ),
		color( 255, 255, 255, m_alpha[ m_player.idx ] ), 
		x_centre | y_centre );

}

void visuals::draw_name( ) {

	player_info info;
	if ( !g_interfaces.m_engine->get_player_info( m_player.idx + 1, &info ) )
		return;

	std::string name = info.m_name;

	if ( !info.m_xuid_low )
		name.append( XOR( " [BOT]" ) );

	std::transform( name.begin( ), name.end( ), name.begin( ), std::tolower );

	g_render.draw_text( g_render.m_fonts.primary,
		m_box.x + m_box.width / 2, m_box.y - 1, 
		name, 
		color( 255, 255, 255, m_alpha[ m_player.idx ] ), 
		x_centre | y_bottom );

}

void visuals::draw_weapon( ) {

	weapon_cs_base* weapon = g_interfaces.m_entity_list->get< weapon_cs_base* >( m_player.ptr->get_active_weapon( ) );
	if ( !weapon )
		return;

	cs_weapon_info* weapon_info = weapon->get_cs_wpn_data( );
	if ( !weapon_info )
		return;

	std::wstring weapon_name = g_interfaces.m_localize->find( weapon_info->m_hud_name );
	std::transform( weapon_name.begin( ), weapon_name.end( ), weapon_name.begin( ), std::toupper );

	g_render.draw_text( g_render.m_fonts.secondary,
		m_box.x + m_box.width / 2, m_box.y + m_box.height + 2,
		weapon_name,
		color( 255, 255, 255, m_alpha[ m_player.idx ] ),
		x_centre );

}

void visuals::calculate_alpha( ) {

	float delta_time = g_interfaces.m_globals->m_curtime - m_player.ptr->get_sim_time( );

	float opacity = m_player.is_dormant ? g_easing.in_quint( 1.f - std::clamp( delta_time, 0.f, 1.f ) ) : 1.f;

	m_alpha[ m_player.idx ] = static_cast< int >( 255 * ( opacity * 0.8f ) );

}

bool visuals::calculate_box( ) {

	vec_3 mins = m_player.ptr->get_mins( ), maxs = m_player.ptr->get_maxs( );

	std::array< vec_3, 8 > world_points = {

		vec_3( mins.x, mins.y, mins.z ),
		vec_3( mins.x, maxs.y, mins.z ),
		vec_3( maxs.x, maxs.y, mins.z ),
		vec_3( maxs.x, mins.y, mins.z ),
		vec_3( maxs.x, maxs.y, maxs.z ),
		vec_3( mins.x, maxs.y, maxs.z ),
		vec_3( mins.x, mins.y, maxs.z ),
		vec_3( maxs.x, mins.y, maxs.z )

	};

	float left = FLT_MAX, top = FLT_MAX, right = FLT_MIN, bottom = FLT_MIN;

	matrix_3x4& transformed_matrix = m_player.ptr->get_coordinated_frame( );

	std::array< vec_3, 8 > screen_points;

	for ( int i = 0; i < 8; i++ ) {

		if ( g_interfaces.m_debug_overlay->screen_position( g_math.vector_transform( world_points[ i ], transformed_matrix ), screen_points[ i ] ) == -1 )
			return false;

		left   = ( std::min )( left, screen_points[ i ].x );
		top    = ( std::min )( top, screen_points[ i ].y );
		right  = ( std::max )( right, screen_points[ i ].x );
		bottom = ( std::max )( bottom, screen_points[ i ].y );

	}

	m_box = {

		static_cast< int >( left ),
		static_cast< int >( top ),
		static_cast< int >( right - left ),
		static_cast< int >( bottom - top )

	};

	return true;

}