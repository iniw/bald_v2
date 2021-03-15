#pragma once

struct event_info {

	short				class_id;
	float				fire_delay;
	const void*         send_table;
	const client_class* client_class;
	void*				data;
	intptr_t		    packed_bits;
	int					flags;
	byte			    pad0[ 0x16 ];

};