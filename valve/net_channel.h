#pragma once

#include "bitbuf.h"

struct net_channel_info {

	inline auto get_avg_latency( int flow ) {

		return g_utils.call_v_func< float >( this, 10, flow );

	}

};

struct net_channel {

	char pad0[ 0x14 ];
	bool m_processing_messages;
	bool m_should_delete;
	bool m_stop_processing;
	char pad1[ 0x1 ];
	int	 m_out_sequence_nr;
	int	 m_in_sequence_nr;
	int	 m_out_sequence_nr_ack;
	int	 m_out_reliable_state;
	int	 m_in_reliable_state;
	int	 m_choked_packets;
	char pad2[ 0x414 ];

	inline int send_datagram( bf_write* datagram ) {

		return g_utils.call_v_func<int>( this, 46, datagram );

	}

	inline bool transmit( bool only_reliable = false ) {

		return g_utils.call_v_func<bool>( this, 49, only_reliable );

	}

};