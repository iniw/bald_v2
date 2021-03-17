#include "cs_player.h"

#include <array>
#include "../../../cstrike/cstrike.h"

void cs_player::post_think( ) {

	static auto post_think_vphysics = g_signatures.m_post_think_vphysics.as< bool( __thiscall* )( base_entity* ) >( );

	static auto simulate_player_simulated_entities = g_signatures.m_simulate_player_simulated_entities.as< void( __thiscall* )( base_entity* ) >( );

	g_interfaces.m_mdl_cache->begin_lock( );

	if ( is_alive( ) ) {

		update_collision_bounds( );

		if ( get_flags( ) & 1 )
			*get_fall_velocity( ) = 0.f;

		if ( get_sequence( ) == -1 )
			set_sequence( 0 );

		studio_frame_advance( );

		post_think_vphysics( this );

	}

	simulate_player_simulated_entities( this );

	g_interfaces.m_mdl_cache->end_lock( );

}

bool cs_player::can_shoot( ) {

	const float server_time = g_cstrike.ticks_to_time( get_tickbase( ) );

	if ( get_next_attack( ) > server_time )
		return false;

	const auto weapon = g_interfaces.m_entity_list->get< weapon_cs_base* >( get_active_weapon( ) );

	if ( !weapon )
		return false;

	const auto idx = static_cast< def_idx >( weapon->get_item_definition_index( ) );

	if ( ( idx == def_idx::famas || idx == def_idx::glock ) && weapon->is_burst_mode( ) && weapon->get_burst_shots_remaining( ) > 0 )
		return true;

	if ( weapon->get_ammo( ) <= 0 )
		return false;

	if ( weapon->get_next_primary_attack( ) > server_time )
		return false;

	return true;

}

vec_3 cs_player::get_hitbox_position( int hitbox ) {

	const auto model = get_model( );
	if ( !model )
		return vec_3( );

	const auto studio_model = g_interfaces.m_model_info->get_studio_model( model );
	if ( !studio_model )
		return vec_3( );

	const auto studio_hitbox = studio_model->get_hitbox( hitbox, 0 );
	if ( !studio_hitbox )
		return vec_3( );

	std::array< matrix_3x4, MAXSTUDIOBONES > bones;
	if ( !setup_bones( bones.data( ), MAXSTUDIOBONES, BONE_USED_BY_HITBOX, 0.f ) )
		return vec_3( );

	vec_3 min = g_math.vector_transform( studio_hitbox->m_bb_min, bones[ studio_hitbox->m_bone ] );
	vec_3 max = g_math.vector_transform( studio_hitbox->m_bb_max, bones[ studio_hitbox->m_bone ] );

	return ( min + max ) * 0.5f;

}

vec_3 cs_player::get_hitbox_position( int hitbox, std::array< matrix_3x4, MAXSTUDIOBONES > matrix ) {

	const auto player_model = get_model( );
	if ( !player_model )
		return vec_3( );

	const auto studio_model = g_interfaces.m_model_info->get_studio_model( player_model );
	if ( !studio_model )
		return vec_3( );

	const auto studio_hitbox = studio_model->get_hitbox( hitbox, 0 );
	if ( !studio_hitbox )
		return vec_3( );

	const vec_3 min = g_math.vector_transform( studio_hitbox->m_bb_min, matrix[ studio_hitbox->m_bone ] );
	const vec_3 max = g_math.vector_transform( studio_hitbox->m_bb_max, matrix[ studio_hitbox->m_bone ] );

	return ( min + max ) * 0.5f;

}

bool cs_player::fixed_setup_bones( matrix_3x4* matrix, const int bone_mask, const float curtime ) {

	const auto backup5 = get_abs_origin( );

	invalidate_bone_cache( );

	set_abs_origin( get_origin( ) );

	get_effects( ) |= ef_nointerp;
	
	last_bone_setup_frame( ) = 0;

	const auto result = setup_bones( matrix, MAXSTUDIOBONES, bone_mask, curtime );

	set_abs_origin( backup5 );

	get_effects( ) &= ~ef_nointerp;

	return result;

}

float cs_player::dist_to_ray( const vec_3& start, const vec_3& end ) {

	const i_collideable* collideable = get_collideable( );
	if ( !collideable )
		return -1.f;

	const vec_3 center = ( collideable->obb_mins( ) + collideable->obb_maxs( ) ) * 0.5f;
	const vec_3 pos = center + get_origin( );	

	const vec_3 to = pos - start;
	vec_3 direction = end - start;
	float length = direction.normalize( );

	const float range_along = direction.dot( to );
	float range = 0.f;

	if ( range_along < 0.f )
		range = -to.length( );
	else if ( range_along > length )
		range = -( pos - end ).length( );
	else
		range = ( pos - ( direction * range_along + start ) ).length( );

	return range;

}
