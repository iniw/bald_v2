#pragma once

#include "../other/utils/utils.h"
#include "../other/math/datatypes/q_ang.h"
#include "net_channel.h"

struct client_class;

enum frame_stage {

	stage_undefined = -1,
	stage_frame_start,
	stage_net_update_start,
	stage_net_update_postdataupdate_start,
	stage_net_update_postdataupdate_end,
	stage_net_update_end,
	stage_render_start,
	stage_render_end

};

struct player_info {

	char pad0[ 0x8 ];
	int  m_xuid_low;
	char pad1[ 0x4 ];
	char m_name[ 256 ];
	char pad2[ 0x13C ];

};

struct engine_client {

	inline auto get_screen_size( int& w, int& h ) {

		return g_utils.call_v_func< void, int&, int& >( this, 5, w, h );

	}

	inline auto get_player_info( int ent_num, player_info* info ) {

		return g_utils.call_v_func< bool >( this, 8, ent_num, info );

	}

	inline auto get_local_index( ) {

		return g_utils.call_v_func< int >( this, 12 );

	}

	inline auto get_view_angles( q_ang& angle ) {

		g_utils.call_v_func< void, q_ang& >( this, 18, angle );

	}

	inline auto get_view_angles( ) {

		q_ang angle_out = { };

		get_view_angles( angle_out );

		return angle_out;

	}

	inline auto set_view_angles( q_ang& angle ) {

		g_utils.call_v_func< void, q_ang& >( this, 19, angle );

	}


	inline auto in_game( ) {

		return g_utils.call_v_func< bool >( this, 26 );

	}

	inline auto get_net_channel_info( ) {

		return g_utils.call_v_func< net_channel_info* >( this, 78 );

	}

	inline auto playing_demo( ) {

		return g_utils.call_v_func< bool >( this, 82 );

	}

	inline auto recording_demo( ) {

		return g_utils.call_v_func< bool >( this, 83 );

	}

};

struct base_client_dll {

	inline auto get_all_classes( ) {

		return g_utils.call_v_func< client_class* >( this, 8 );

	}

};