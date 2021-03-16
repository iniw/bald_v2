#include "hooked.h"

bool hooked::setup( ) {

	g_console.log( XOR( "hooking functions..." ) );

	g_detour.setup( XOR( "C_BasePlayer::CreateMove" ), g_signatures.m_create_move, &create_move );

	g_detour.setup( XOR( "CHLClient::FrameStageNotify" ), g_utils.get_v_func( g_interfaces.m_client, 37 ), &frame_stage_notify );
	
	g_detour.setup( XOR( "CEngineVGui::Paint" ), g_signatures.m_paint, &paint );

	g_detour.setup( XOR( "ClientModeShared::GetViewModelFOV" ), g_signatures.m_get_view_model_fov, &get_view_model_fov );

	g_detour.setup( XOR( "C_WeaponCSBase::DrawCrosshair" ), g_signatures.m_draw_crosshair, &draw_crosshair );

	g_detour.setup( XOR( "CCSGOPlayerAnimState::Update" ), g_signatures.m_update, &update );

	g_detour.setup( XOR( "CCSGOPlayerAnimState::ModifyEyePosition" ), g_signatures.m_modify_eye_position, &modify_eye_position );

	g_detour.setup( XOR( "CCSGOPlayerAnimState::DoProceduralFootPlant" ), g_signatures.m_do_procedural_foot_plant, &do_procedural_foot_plant );

	g_detour.setup( XOR( "CCSGOPlayerAnimState::SetUpVelocity" ), g_signatures.m_setup_velocity, &set_up_velocity );

	g_detour.setup( XOR( "CCSGOPlayerAnimState::SetUpMovement" ), g_signatures.m_setup_movement, &set_up_movement );

	g_detour.setup( XOR( "CInput::CAM_Think" ), g_signatures.m_cam_think, &cam_think );

	g_detour.setup( XOR( "CInput::CAM_ToThirdPerson" ), g_signatures.m_cam_to_third_person, &cam_to_third_person );

	g_detour.setup( XOR( "CSchemeManager::ReloadSchemes" ), g_signatures.m_reload_schemes, &reload_schemes );

	g_detour.setup( XOR( "CStudioRenderContext::DrawModel" ), g_signatures.m_draw_model, &draw_model );

	g_detour.setup( XOR( "C_CSPlayer::GlowEffectSpectator" ), g_signatures.m_glow_effect_spectator, &glow_effect_spectators );

	g_detour.setup( XOR( "CEngineBSPTree::ListLeavesInBox" ), g_signatures.m_list_leaves_in_box, &list_leaves_in_box );

	g_console.log( XOR( "hooked functions" ) );

	return true;

}

void hooked::unload( ) {

	g_detour.unload( );

}