#pragma once

#include "../net_channel.h"
#include "../engine/event_info.h"

struct client_state {

	char		    pad0[ 0x9C ];
	net_channel*    m_net_channel;
	int				m_challenge_nr;
	char		    pad1[ 0x64 ];
	int				m_signon_state;
	char		    pad2[ 0x8 ];
	float			m_next_cmd_time;
	int				m_server_count;
	int				m_current_sequence;
	char		    pad3[ 0x54 ];
	int				m_delta_tick;
	bool			m_paused;
	char		    pad4[ 0x7 ];
	int				m_view_entity;
	int				m_player_slot;
	char			m_level_name[ 260 ];
	char			m_level_name_short[ 80 ];
	char			m_map_group_name[ 80 ];
	char			m_last_level_name_short[ 80 ];
	char		    pad5[ 0xC ];
	int				m_max_clients;
	char		    pad6[ 0x498C ];
	float			m_last_server_tick_time;
	bool			m_in_simulation;
	char		    pad7[ 0x3 ];
	int				m_old_tickcount;
	float			m_tick_remainder;
	float			m_frame_time;
	int				m_last_outgoing_command;
	int				m_choked_commands;
	int				m_last_command_ack;
	int				m_command_ack;
	int				m_sound_sequence;
	char		    pad8[ 0x50 ];
	q_ang			m_view_point;
	char		    pad9[ 0xD0 ];
	event_info*		m_events;

};