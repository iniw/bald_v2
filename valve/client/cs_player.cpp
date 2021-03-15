#include "cs_player.h"

#include <array>
#include "../../cstrike/cstrike.h"

void cs_player::post_think( ) {

	static auto post_think_vphysics = g_signatures.m_post_think_vphysics.as< bool( __thiscall* )( base_entity* ) >( );

	static auto simulate_player_simulated_entities = g_signatures.m_simulate_player_simulated_entities.as< void( __thiscall* )( base_entity* ) >( );

	g_interfaces.m_mdl_cache->begin_lock( );

	if ( this->is_alive( ) ) {

		this->update_collision_bounds( );

		if ( this->get_flags( ) & 1 )
			*this->get_fall_velocity( ) = 0.f;

		if ( this->get_sequence( ) == -1 )
			this->set_sequence( 0 );

		this->studio_frame_advance( );

		post_think_vphysics( this );

	}

	simulate_player_simulated_entities( this );

	g_interfaces.m_mdl_cache->end_lock( );

}

bool cs_player::can_shoot( ) {

	const float server_time = g_cstrike.ticks_to_time( this->get_tickbase( ) );

	if ( this->get_next_attack( ) > server_time )
		return false;

	const auto weapon = g_interfaces.m_entity_list->get< weapon_cs_base* >( this->get_active_weapon( ) );

	if ( !weapon )
		return false;

	const auto def_index = static_cast< definition_index >( weapon->get_item_definition_index( ) );

	if ( ( def_index == definition_index::famas || def_index == definition_index::glock ) && weapon->is_burst_mode( ) && weapon->get_burst_shots_remaining( ) > 0 )
		return true;

	if ( weapon->get_ammo( ) <= 0 )
		return false;

	if ( weapon->get_next_primary_attack( ) > server_time )
		return false;

	return true;

}

vec_3 cs_player::get_hitbox_position( hitbox hitbox ) {

	std::array< matrix_3x4, MAXSTUDIOBONES > out_bones = { };

	auto model = this->get_model( );

	if ( !model )
		return vec_3( );

	auto studio_model = g_interfaces.m_model_info->get_studio_model( model );

	if ( !studio_model )
		return vec_3( );

	auto studio_hitbox = studio_model->get_hitbox( static_cast< int >( hitbox ), 0 );

	if ( !studio_hitbox )
		return vec_3( );

	if ( !this->setup_bones( out_bones.data( ), MAXSTUDIOBONES, BONE_USED_BY_HITBOX, 0.f ) )
		return vec_3( );

	vec_3 min = g_math.vector_transform( studio_hitbox->m_bb_min, out_bones[ studio_hitbox->m_bone ] );
	vec_3 max = g_math.vector_transform( studio_hitbox->m_bb_max, out_bones[ studio_hitbox->m_bone ] );

	return ( min + max ) * 0.5f;

}