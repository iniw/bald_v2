#include "../hooked.h"

void __fastcall hooked::draw_model( studio_render_context* ecx, void* edx, void* results, const draw_model_info& info, void* bone_to_world, float* flex_weights, float* flex_delayed_rates, const vec_3& origin, int flags ) {

	static auto o_draw_model = g_detour.get< decltype( &draw_model ) >( XOR( "CStudioRenderContext::DrawModel" ) );

	if ( !g_cstrike.m_local || !info.m_client_entity )
		return o_draw_model( ecx, edx, results, info, bone_to_world, flex_weights, flex_delayed_rates, origin, flags );

	base_entity* entity = reinterpret_cast< base_entity* >( info.m_client_entity - 0x4 );
	if ( entity && entity->is_player( ) && g_cstrike.m_local->is_enemy( entity ) ) {

		static auto material = g_interfaces.m_material_system->find_material( XOR( "debug/debugdrawflat" ), XOR( "Model textures" ) );

		ecx->set_color( color( 109, 114, 195 ) );

		ecx->set_material( material, material_var_ignorez, true );

		o_draw_model( ecx, edx, results, info, bone_to_world, flex_weights, flex_delayed_rates, origin, flags );

		ecx->set_color( color( 221, 115, 115 ) );

		ecx->set_material( material, material_var_ignorez, false );

		o_draw_model( ecx, edx, results, info, bone_to_world, flex_weights, flex_delayed_rates, origin, flags );

		ecx->set_material( nullptr );

		return;
	}

	return o_draw_model( ecx, edx, results, info, bone_to_world, flex_weights, flex_delayed_rates, origin, flags );

}