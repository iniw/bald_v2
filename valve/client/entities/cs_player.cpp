#include "cs_player.h"

#include <array>
#include "../../../cstrike/cstrike.h"
#include "../../../cstrike/features/legitbot/backtracking.h"

vec_3 cs_player::get_eye_position( ) {

	vec_3 eye_pos;
	g_utils.call_v_func< void, vec_3& >( this, 168, eye_pos );

	if ( is_using_new_anim_state( ) && this == g_cstrike.m_local ) {

		auto anim_state = get_anim_state( );

		if ( anim_state ) {

			// we have modify eye position hooked so we can just call it directly
			g_signatures.m_modify_eye_position.as< void( __thiscall* )( csgo_player_anim_state*, const vec_3& ) >( )( anim_state, eye_pos );

		}

	}

	return eye_pos;

}

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

vec_3 cs_player::get_hitbox_position( int hitbox, lag_record* record ) {

	const auto model = get_model( );
	if ( !model )
		return vec_3( );

	const auto studio_model = record ? record->m_studio_model : g_interfaces.m_model_info->get_studio_model( model );
	if ( !studio_model )
		return vec_3( );

	const auto studio_hitbox = studio_model->get_hitbox( hitbox, 0 );
	if ( !studio_hitbox )
		return vec_3( );

	std::array< matrix_3x4, MAXSTUDIOBONES > bones;

	if ( !record ) 
		if ( !setup_bones( bones.data( ), MAXSTUDIOBONES, BONE_USED_BY_HITBOX, 0.f ) )
			return vec_3( );

	vec_3 min = g_math.vector_transform( studio_hitbox->m_bb_min, record ? record->m_matrix[ studio_hitbox->m_bone ] : bones[ studio_hitbox->m_bone ] );
	vec_3 max = g_math.vector_transform( studio_hitbox->m_bb_max, record ? record->m_matrix[ studio_hitbox->m_bone ] : bones[ studio_hitbox->m_bone ] );

	return ( min + max ) * 0.5f;

}

vec_3 cs_player::get_hitbox_position( int hitbox, matrix_3x4* matrix ) {

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

	if ( !matrix )
		if ( !setup_bones( bones.data( ), MAXSTUDIOBONES, BONE_USED_BY_HITBOX, 0.f ) )
			return vec_3( );

	vec_3 min = g_math.vector_transform( studio_hitbox->m_bb_min, matrix ? matrix[ studio_hitbox->m_bone ] : bones[ studio_hitbox->m_bone ] );
	vec_3 max = g_math.vector_transform( studio_hitbox->m_bb_max, matrix ? matrix[ studio_hitbox->m_bone ] : bones[ studio_hitbox->m_bone ] );

	return ( min + max ) * 0.5f;

}

bool cs_player::fixed_setup_bones( matrix_3x4* matrix, const int bone_mask, const float curtime ) {

	const auto backup_abs_origin = get_abs_origin( );

	set_abs_origin( get_origin( ) );

	invalidate_bone_cache( );

	last_bone_setup_frame( ) = 0;

	const auto result = setup_bones( matrix, MAXSTUDIOBONES, bone_mask, curtime );

	set_abs_origin( backup_abs_origin );

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
