#include "hooked.h"

bool hooks::setup( ) {

	if ( !g_detour.setup( XOR( "CHLClient::LevelInitPreEntity" ), g_utils.get_v_func( g_interfaces.m_client, 5 ), &level_init_pre_entity ) )
		return false;

	if ( !g_detour.setup( XOR( "CHLClient::LevelShutdown" ), g_utils.get_v_func( g_interfaces.m_client, 7 ), &level_shutdown ) )
		return false;

	if ( !g_detour.setup( XOR( "CHLClient::FrameStageNotify" ), g_utils.get_v_func( g_interfaces.m_client, 37 ), &frame_stage_notify ) )
		return false;

	const auto player_vtable = g_utils.get_v_table( g_pe.m_dlls.client, XOR( "C_CSPlayer" ) );

	if ( !g_detour.setup( XOR( "C_CSPlayer::CreateMove" ), g_utils.get_v_func( player_vtable, 288 ), &create_move ) )
		return false;

	if ( !g_detour.setup( XOR( "C_BasePlayer::GlowEffectSpectator" ), g_signatures.m_glow_effect_spectator, &glow_effect_spectators ) )
		return false;
	
	if ( !g_detour.setup( XOR( "CEngineVGui::Paint" ), g_signatures.m_paint, &paint ) )
		return false;

	if ( !g_detour.setup( XOR( "CEngineClient::IsHLTV" ), g_utils.get_v_func( g_interfaces.m_engine, 193 ), &is_hltv ) )
		return false;

	if ( !g_detour.setup( XOR( "ClientModeShared::GetViewModelFOV" ), g_signatures.m_get_view_model_fov, &get_view_model_fov ) )
		return false;

	if ( !g_detour.setup( XOR( "C_WeaponCSBase::DrawCrosshair" ), g_signatures.m_draw_crosshair, &draw_crosshair ) )
		return false;

	if ( !g_detour.setup( XOR( "CCSGOPlayerAnimState::Update" ), g_signatures.m_update, &update ) )
		return false;

	if ( !g_detour.setup( XOR( "CCSGOPlayerAnimState::ModifyEyePosition" ), g_signatures.m_modify_eye_position, &modify_eye_position ) )
		return false;

	if ( !g_detour.setup( XOR( "CCSGOPlayerAnimState::DoProceduralFootPlant" ), g_signatures.m_do_procedural_foot_plant, &do_procedural_foot_plant ) )
		return false;

	if ( !g_detour.setup( XOR( "CCSGOPlayerAnimState::SetUpVelocity" ), g_signatures.m_setup_velocity, &setup_velocity ) )
		return false;

	if ( !g_detour.setup( XOR( "CCSGOPlayerAnimState::SetUpMovement" ), g_signatures.m_setup_movement, &setup_movement ) )
		return false;

	if ( !g_detour.setup( XOR( "C_BaseAnimating::ShouldSkipAnimationFrame" ), g_signatures.m_should_skip_animation_frame, &should_skip_animation_frame ) )
		return false;

	if ( !g_detour.setup( XOR( "CInput::CAM_Think" ), g_signatures.m_cam_think, &cam_think ) )
		return false;

	if ( !g_detour.setup( XOR( "CInput::CAM_ToThirdPerson" ), g_signatures.m_cam_to_third_person, &cam_to_third_person ) )
		return false;

	if ( !g_detour.setup( XOR( "CSchemeManager::ReloadSchemes" ), g_signatures.m_reload_schemes, &reload_schemes ) )
		return false;

	if ( !g_detour.setup( XOR( "CStudioRenderContext::DrawModel" ), g_signatures.m_draw_model, &draw_model ) )
		return false;

	if ( !g_detour.setup( XOR( "CEngineBSPTree::ListLeavesInBox" ), g_signatures.m_list_leaves_in_box, &list_leaves_in_box ) )
		return false;

	if ( !g_detour.setup( XOR( "CMaterialSystem::OverrideConfig" ), g_utils.get_v_func( g_interfaces.m_material_system, 21 ), &override_config ) )
		return false;

	g_console.log( log_completion, XOR( "setup hooks" ) );

	return true;

}

void hooks::unload( ) {

	g_detour.unload( );

}