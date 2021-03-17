#include "legitbot.h"

#include "../../render/render.h"

void legitbot::run( user_cmd* cmd ) {

	m_data = get_data( cmd );
	if ( !m_data )
		return;

	if ( cmd->m_buttons & in_attack && g_cstrike.m_local->can_shoot( ) ) {

		cmd->m_view_angles = m_data->m_ang;
		g_interfaces.m_engine->set_view_angles( m_data->m_ang );

	}

}

std::unique_ptr< aimbot_data > legitbot::get_data( user_cmd* cmd ) {

	cs_player* best_player = nullptr;
	float best_fov = FLT_MAX;

	for ( int i = 1; i <= g_interfaces.m_globals->m_max_clients; i++ ) {

		cs_player* player = g_interfaces.m_entity_list->get< cs_player* >( i );

		if ( !g_cstrike.validate_player( player ) )
			continue;

		aimbot_data data( player );

		if ( data.m_fov < best_fov && data.m_dmg > 0.f ) {

			best_fov = data.m_fov;
			best_player = data.m_ent;

		}

	}

	return best_player ? std::make_unique< aimbot_data >( best_player ) : nullptr;

}

void legitbot::finalize_angle( ) {



}

void legitbot::apply_angle( ) {



}

void legitbot::paint( ) {

	if ( !m_data )
		return;
	/*
	vec_3 screen_head_pos;
	int w, h;

	g_interfaces.m_engine->get_screen_size( w, h );

	if ( g_interfaces.m_debug_overlay->screen_position( m_data->m_pos, screen_head_pos ) == -1 )
		return;

	g_render.draw_line( w / 2, h / 2, 
		screen_head_pos.x, screen_head_pos.y, 
		color( 255, 255, 255 ) );

	g_render.draw_text( g_render.m_fonts.primary, 
		w / 2, h / 2 - 5, 
		g_render.format_text( XOR( "dmg = %.2f" ), m_data->m_dmg ), 
		color( 255, 255, 255 ), 
		x_centre | y_centre );
		*/

}
