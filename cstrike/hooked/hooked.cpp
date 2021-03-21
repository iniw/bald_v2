#include "hooked.h"

bool hooks::setup( ) {

	g_detour.setup( XOR( "CHLClient::LevelInitPreEntity" ), g_utils.get_v_func( g_interfaces.m_client, 5 ), &level_init_pre_entity );

	g_detour.setup( XOR( "CHLClient::LevelShutdown" ), g_utils.get_v_func( g_interfaces.m_client, 7 ), &level_shutdown );

	g_detour.setup( XOR( "CHLClient::FrameStageNotify" ), g_utils.get_v_func( g_interfaces.m_client, 37 ), &frame_stage_notify );

	g_detour.setup( XOR( "C_CSPlayer::CreateMove" ), g_signatures.m_create_move, &create_move );

	g_detour.setup( XOR( "C_BasePlayer::GlowEffectSpectator" ), g_signatures.m_glow_effect_spectator, &glow_effect_spectators );
	
	g_detour.setup( XOR( "CEngineVGui::Paint" ), g_signatures.m_paint, &paint );

	g_detour.setup( XOR( "CEngineClient::IsHLTV" ), g_utils.get_v_func( g_interfaces.m_engine, 193 ), &is_hltv );

	g_detour.setup( XOR( "ClientModeShared::GetViewModelFOV" ), g_signatures.m_get_view_model_fov, &get_view_model_fov );

	g_detour.setup( XOR( "C_WeaponCSBase::DrawCrosshair" ), g_signatures.m_draw_crosshair, &draw_crosshair );

	g_detour.setup( XOR( "CCSGOPlayerAnimState::Update" ), g_signatures.m_update, &update );

	g_detour.setup( XOR( "CCSGOPlayerAnimState::ModifyEyePosition" ), g_signatures.m_modify_eye_position, &modify_eye_position );

	g_detour.setup( XOR( "CCSGOPlayerAnimState::DoProceduralFootPlant" ), g_signatures.m_do_procedural_foot_plant, &do_procedural_foot_plant );

	g_detour.setup( XOR( "CCSGOPlayerAnimState::SetUpVelocity" ), g_signatures.m_setup_velocity, &set_up_velocity );

	g_detour.setup( XOR( "CCSGOPlayerAnimState::SetUpMovement" ), g_signatures.m_setup_movement, &set_up_movement );

	g_detour.setup( XOR( "C_BaseAnimating::ShouldSkipAnimationFrame" ), g_signatures.m_should_skip_animation_frame, &should_skip_animation_frame );

	g_detour.setup( XOR( "CInput::CAM_Think" ), g_signatures.m_cam_think, &cam_think );

	g_detour.setup( XOR( "CInput::CAM_ToThirdPerson" ), g_signatures.m_cam_to_third_person, &cam_to_third_person );

	g_detour.setup( XOR( "CSchemeManager::ReloadSchemes" ), g_signatures.m_reload_schemes, &reload_schemes );

	g_detour.setup( XOR( "CStudioRenderContext::DrawModel" ), g_signatures.m_draw_model, &draw_model );

	g_detour.setup( XOR( "CEngineBSPTree::ListLeavesInBox" ), g_signatures.m_list_leaves_in_box, &list_leaves_in_box );

	g_detour.setup( XOR( "CMaterialSystem::OverrideConfig" ), g_utils.get_v_func( g_interfaces.m_material_system, 21 ), &override_config );

	g_console.log( XOR( "finished hooking" ) );

	return true;

}

void hooks::unload( ) {

	g_detour.unload( );

}