#pragma once

struct client_input {

	char pad0[ 0xAD ];
	bool m_camera_in_third_person;
	char pad1[ 0x2 ];
	vec_3 m_camera_offset;
	char pad2[ 0x48 ];
	int m_cam_command;

};