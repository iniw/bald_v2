#pragma once

enum paint_mode {

	paint_uipanels = ( 1 << 0 ),
	paint_ingamepanels = ( 1 << 1 ),

};

struct engine_vgui {

	char  pad0[ 0x48 ];
	void* m_static_transition_panel;

};