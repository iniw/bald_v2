#include "legitbot.h"

#include "../../render/render.h"

void legitbot::run( user_cmd* cmd ) {

	m_data = get_data( cmd );

	if ( !m_data )
		return;

	if ( cmd->m_buttons & in_attack && g_cstrike.m_local_player->can_shoot( ) ) {

		cmd->m_view_angles = m_data.ang;
		g_interfaces.m_engine->set_view_angles( m_data.ang );

	}

}

aimbot_data legitbot::get_data( user_cmd* cmd ) {

	cs_player* best_player = nullptr;
	float best_fov = FLT_MAX;

	for ( int i = 1; i <= g_interfaces.m_globals->m_max_clients; i++ ) {

		cs_player* player = g_interfaces.m_entity_list->get< cs_player* >( i );

		if ( !g_cstrike.validate_player( player ) )
			continue;

		aimbot_data data( player );

		if ( data.fov < best_fov ) {

			best_fov = data.fov;
			best_player = data.ent;

		}

	}

	return aimbot_data( best_player );

}

void legitbot::finalize_angle( ) {



}

void legitbot::apply_angle( ) {



}

void legitbot::paint( ) {

	vec_3 screen_head_pos;
	int w, h;

	g_interfaces.m_engine->get_screen_size( w, h );

	if ( g_interfaces.m_debug_overlay->screen_position( m_data.pos, screen_head_pos ) == -1 )
		return;

	g_render.draw_line( w / 2, h / 2, screen_head_pos.x, screen_head_pos.y, color( 255, 255, 255 ) );

	char buffer[ 25 ];
	sprintf_s( buffer, "dmg = %.2f", m_data.dmg );

	g_render.draw_text( g_render.m_fonts.primary, w / 2, h / 2 - 5, buffer, color( 255, 255, 255 ), x_centre | y_centre );

}
