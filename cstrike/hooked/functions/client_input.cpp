#include "../hooked.h"

void __fastcall hooked::cam_think( client_input* ecx, void* edx ) {

	static auto o_cam_think = g_detour.get< decltype( &cam_think ) >( XOR( "CInput::CAM_Think" ) );

	//ecx->m_camera_in_third_person = !g_input.is_key_toggled( 0x56, g_config.m_third_person );

	//ecx->m_cam_command = 1;

	return o_cam_think( ecx, edx );

}

void __fastcall hooked::cam_to_third_person( client_input* ecx, void* edx ) {

	static auto o_cam_to_third_person = g_detour.get< decltype( &cam_to_third_person ) >( XOR( "CInput::CAM_ToThirdPerson" ) );

	o_cam_to_third_person( ecx, edx );

	//ecx->m_camera_offset.z = 150.f;

}