#include "hooked.h"

bool hooked::setup( ) {

	g_console.log( "hooking functions..." );

	g_detour.setup( "C_BasePlayer::CreateMove", g_signatures.m_create_move, &create_move );

	g_detour.setup( "CHLClient::FrameStageNotify", g_utils.get_v_func( g_interfaces.m_client, 37 ), &frame_stage_notify );

	g_detour.setup( "CEngineVGui::Paint", g_signatures.m_paint, &paint );

	g_detour.setup( "ClientModeShared::GetViewModelFOV", g_signatures.m_get_view_model_fov, &get_view_model_fov );

	g_detour.setup( "C_WeaponCSBase::DrawCrosshair", g_signatures.m_draw_crosshair, &draw_crosshair );

	g_detour.setup( "CCSGOPlayerAnimState::Update", g_signatures.m_update, &update );

	g_detour.setup( "CCSGOPlayerAnimState::ModifyEyePosition", g_signatures.m_modify_eye_position, &modify_eye_position );

	g_detour.setup( "CCSGOPlayerAnimState::DoProceduralFootPlant", g_signatures.m_do_procedural_foot_plant, &do_procedural_foot_plant );

	g_detour.setup( "CCSGOPlayerAnimState::SetUpVelocity", g_signatures.m_setup_velocity, &set_up_velocity );

	g_detour.setup( "CCSGOPlayerAnimState::SetUpMovement", g_signatures.m_setup_movement, &set_up_movement );

	g_detour.setup( "CInput::CAM_Think", g_signatures.m_cam_think, &cam_think );

	g_detour.setup( "CInput::CAM_ToThirdPerson", g_signatures.m_cam_to_third_person, &cam_to_third_person );

	g_detour.setup( "CSchemeManager::ReloadSchemes", g_signatures.m_reload_schemes, &reload_schemes );

	g_detour.setup( "CStudioRenderContext::DrawModel", g_signatures.m_draw_model, &draw_model );

	g_detour.setup( "C_CSPlayer::GlowEffectSpectator", g_pattern.find( "client.dll", "55 8B EC 83 EC 14 53 8B 5D 0C 56 57 85 DB 74" ), &glow_effect_spectators );

	g_console.log( "hooked functions" );

	return true;

}

void hooked::unload( ) {

	g_detour.unload( );

}