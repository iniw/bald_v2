#pragma once

struct client_input {

	byte pad0[ 0xAD ];
	bool m_camera_in_third_person;
	byte pad1[ 0x2 ];
	vec_3 m_camera_offset;
	byte pad2[ 0x48 ];
	int m_cam_command;

};