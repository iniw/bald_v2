#include "autowall.h"

float autowall::get_damage( const vec_3& point ) {

	bulet_data data = { };

	vec_3 position = g_cstrike.m_local->get_eye_position( );

	data.m_position = position;
	data.m_direction = ( point - position ).normalized( );

	weapon_cs_base* weapon = g_interfaces.m_entity_list->get< weapon_cs_base* >( g_cstrike.m_local->get_active_weapon( ) );

	if ( !weapon )
		return -1.0f;

	if ( !simulate_fire_bullet( weapon, data ) )
		return -1.0f;

	return data.m_current_damage;

}

bool autowall::simulate_fire_bullet( weapon_cs_base* weapon, bulet_data& data ) {

	cs_weapon_info* weapon_data = weapon->get_cs_wpn_data( );

	if ( !weapon_data )
		return false;

	float max_range = weapon_data->m_range;

	data.m_penetration_count = 4;

	data.m_current_damage = static_cast< float >( weapon_data->m_damage );

	float trace_length = 0.f;

	trace_filter filter( g_cstrike.m_local );

	while ( data.m_penetration_count > 0 && data.m_current_damage >= 1.f ) {

		max_range -= trace_length;

		const vec_3 pos_end = data.m_position + data.m_direction * max_range;

		ray ray( data.m_position, pos_end );
		g_interfaces.m_trace->trace_ray( ray, MASK_SHOT_HULL | CONTENTS_HITBOX, &filter, &data.m_trace );

		clip_trace_to_players( data.m_position, pos_end + data.m_direction * 40.f, MASK_SHOT_HULL | CONTENTS_HITBOX, &filter, &data.m_trace );

		surface_data* surface_data = g_interfaces.m_physics_props->get_surface_data( data.m_trace.m_surface.m_surface_props );
		const float penetration_modifier = surface_data->m_game.m_penetration_modifier;

		if ( data.m_trace.m_fraction == 1.0f )
			break;

		trace_length += data.m_trace.m_fraction * max_range;
		data.m_current_damage *= std::powf( weapon_data->m_range_modifier, trace_length / 500.f );

		if ( trace_length > 3000.0f || penetration_modifier < 0.1f )
			break;

		if ( data.m_trace.m_hitgroup != generic && data.m_trace.m_hitgroup != gear && g_cstrike.m_local->is_enemy( data.m_trace.m_hit_entity ) ) {

			scale_damage( data.m_trace.m_hitgroup, data.m_trace.m_hit_entity, weapon_data->m_armor_ratio, data.m_current_damage );
			return true;

		}

		if ( !handle_bullet_penetration( weapon_data, surface_data, data ) )
			break;
	}

	return false;

}

void autowall::clip_trace_to_players( const vec_3& start, const vec_3& end, unsigned int mask, base_trace_filter* filter, trace* ray_trace ) {

	trace trace = { };
	float smallest_fraction = ray_trace->m_fraction;

	const ray ray( start, end );

	for ( int i = 1; i <= g_interfaces.m_globals->m_max_clients; i++ ) {

		cs_player* player = g_interfaces.m_entity_list->get< cs_player* >( i );

		if ( !player || !player->is_alive( ) || player->is_dormant( ) )
			continue;

		if ( filter && !filter->should_hit_entity( player, mask ) )
			continue;

		const i_collideable* collideable = player->get_collideable( );
		if ( collideable == nullptr )
			continue;

		const vec_3 min = collideable->obb_mins( );
		const vec_3 max = collideable->obb_maxs( );

		const vec_3 center = ( max + min ) * 0.5f;
		const vec_3 position = center + player->get_origin( );

		const float range = player->dist_to_ray( position, start, end );

		if ( range < 0.f || range > 60.f )
			continue;

		g_interfaces.m_trace->clip_ray_to_entity( ray, mask | CONTENTS_HITBOX, player, &trace );

		if ( trace.m_fraction < smallest_fraction ) {

			*ray_trace = trace;
			smallest_fraction = trace.m_fraction;

		}
	}

}

void autowall::scale_damage( int hit_group, cs_player* player, float weapon_armor_ratio, float& damage ) {

	const bool has_heavy_armor = player->has_heavy_armor( );
	const int armor = player->get_armor( );

	switch ( hit_group ) {

	case head:
		damage *= has_heavy_armor ? 2.0f : 4.0f;
		break;

	case stomach:
		damage *= 1.25f;
		break;

	case leftleg:
	case rightleg:
		damage *= 0.75f;
		break;

	}

	if ( armor > 0 && ( ( hit_group == head && player->has_helmet( ) ) || ( hit_group >= generic && hit_group <= rightarm ) ) ) {

		float modifier = 1.0f, armor_bonus_ratio = 0.5f, armor_ratio = weapon_armor_ratio * 0.5f;

		if ( has_heavy_armor ) {

			armor_bonus_ratio = 0.33f;
			armor_ratio *= 0.5f;
			modifier = 0.33f;

		}

		float new_damage = damage * armor_ratio;

		if ( has_heavy_armor )
			new_damage *= 0.85f;

		if ( ( ( damage - damage * armor_ratio ) * ( modifier * armor_bonus_ratio ) ) > armor )
			new_damage = damage - armor / armor_bonus_ratio;

		damage = new_damage;

	}

}

bool autowall::handle_bullet_penetration( cs_weapon_info* weapon_info, surface_data* result_surface_data, bulet_data& data ) {

	g_console.log( "called hbp" );

	static convar* ff_damage_reduction_bullets = g_interfaces.m_convar->find_var( "ff_damage_reduction_bullets" );
	static convar* ff_damage_bullet_penetration = g_interfaces.m_convar->find_var( "ff_damage_bullet_penetration" );

	const float reduction_damage = ff_damage_reduction_bullets->get_float( );
	const float penetrate_damage = ff_damage_bullet_penetration->get_float( );

	const uint16_t enter_material = result_surface_data->m_game.m_material;
	const float enter_penetration_modifier = result_surface_data->m_game.m_penetration_modifier;

	const bool is_solid_surf = ( ( data.m_trace.m_contents >> 3 ) & CONTENTS_SOLID );
	const bool is_light_surf = ( ( data.m_trace.m_surface.m_flags >> 7 ) & SURF_LIGHT );

	trace exit_trace = { };

	if ( data.m_penetration_count <= 0 || ( !data.m_penetration_count && !is_light_surf && !is_solid_surf && enter_material != 'G' && enter_material != 'Y' ) ||
		 ( weapon_info->m_penetration <= 0.f ) ||
		 ( !trace_to_exit( data.m_trace, exit_trace, data.m_trace.m_end, data.m_direction ) && !( g_interfaces.m_trace->get_point_contents( data.m_trace.m_end, MASK_SHOT_HULL, nullptr ) & MASK_SHOT_HULL ) ) )
		return false;

	const surface_data* exit_surface_data = g_interfaces.m_physics_props->get_surface_data( exit_trace.m_surface.m_surface_props );

	const uint16_t exit_material = exit_surface_data->m_game.m_material;

	const float exit_penetration_modifier = exit_surface_data->m_game.m_penetration_modifier;

	float damage_lost_modifier = 0.16f;
	float penetration_modifier = 0.f;

	if ( enter_material == 'G' || enter_material == 'Y' ) {

		damage_lost_modifier = 0.05f;
		penetration_modifier = 3.f;

	} else if ( is_solid_surf || is_light_surf ) {

		damage_lost_modifier = 0.16f;
		penetration_modifier = 1.f;

	} else if ( enter_material == 'F' && ( g_cstrike.m_local->get_team( ) == data.m_trace.m_hit_entity->get_team( ) && reduction_damage == 0.f ) ) {

		if ( penetrate_damage == 0.f )
			return false;

		damage_lost_modifier = 0.16f;
		penetration_modifier = penetrate_damage;

	} else {

		damage_lost_modifier = 0.16f;
		penetration_modifier = ( enter_penetration_modifier + exit_penetration_modifier ) * 0.5f;

	}

	if ( enter_material == exit_material ) {

		if ( exit_material == 'U' || exit_material == 'W' )
			penetration_modifier = 3.f;

		else if ( exit_material == 'L' )
			penetration_modifier = 2.f;

	}

	const float trace_distance = ( exit_trace.m_end - data.m_trace.m_end ).length_sqr( );

	const float modifier = ( std::max )( 0.0f, 1.0f / penetration_modifier );

	const float lost_damage = ( data.m_current_damage * damage_lost_modifier + ( std::max )( 0.f, 3.75f / weapon_info->m_penetration ) * ( modifier * 3.0f ) ) + ( ( modifier * trace_distance ) / 24.0f );

	if ( lost_damage > data.m_current_damage )
		return false;

	if ( lost_damage > 0.0f )
		data.m_current_damage -= lost_damage;

	if ( data.m_current_damage < 1.0f )
		return false;

	data.m_position = exit_trace.m_end;
	--data.m_penetration_count;
	return true;

}

bool autowall::trace_to_exit( trace& enter_trace, trace& exit_trace, vec_3 position, vec_3 direction ) {

	float distance = 0.0f;
	int start_contents = 0;

	while ( distance <= 90.0f ) {

		distance += 4.0f;

		vec_3 start = position + direction * distance;

		if ( !start_contents )
			start_contents = g_interfaces.m_trace->get_point_contents( start, MASK_SHOT_HULL | CONTENTS_HITBOX, nullptr );

		const int current_contents = g_interfaces.m_trace->get_point_contents( start, MASK_SHOT_HULL | CONTENTS_HITBOX, nullptr );

		if ( !( current_contents & MASK_SHOT_HULL ) || ( current_contents & CONTENTS_HITBOX && current_contents != start_contents ) ) {

			const vec_3 end = start - ( direction * 4.0f );

			ray ray_world( start, end );
			g_interfaces.m_trace->trace_ray( ray_world, MASK_SHOT_HULL | CONTENTS_HITBOX, nullptr, &exit_trace );

			if ( exit_trace.m_start_solid && exit_trace.m_surface.m_flags & SURF_HITBOX ) {

				ray ray( start, position );
				trace_filter filter( exit_trace.m_hit_entity );

				g_interfaces.m_trace->trace_ray( ray, MASK_SHOT_HULL, &filter, &exit_trace );

				if ( exit_trace.did_hit( ) && !exit_trace.m_start_solid ) {

					start = exit_trace.m_end;
					return true;

				}

				continue;

			}

			if ( exit_trace.did_hit( ) && !exit_trace.m_start_solid ) {

				if ( is_breakable_entity( enter_trace.m_hit_entity ) && is_breakable_entity( exit_trace.m_hit_entity ) )
					return true;

				if ( enter_trace.m_surface.m_flags & SURF_NODRAW || ( !( exit_trace.m_surface.m_flags & SURF_NODRAW ) && exit_trace.m_plane.m_normal.dot( direction ) <= 1.0f ) ) {

					const float multiplier = exit_trace.m_fraction * 4.0f;
					start -= direction * multiplier;
					return true;

				}

				continue;

			}

			if ( !exit_trace.did_hit( ) || exit_trace.m_start_solid ) {

				if ( enter_trace.m_hit_entity && enter_trace.m_hit_entity->get_index( ) != 0 && is_breakable_entity( enter_trace.m_hit_entity ) ) {

					exit_trace = enter_trace;
					exit_trace.m_end = start + direction;
					return true;

				}

				continue;

			}

		}

	}

	return false;

}


bool autowall::is_breakable_entity( base_player* entity ) {

	if ( !entity )
		return false;

	const int health = entity->get_health( );

	if ( health < 0 && entity->is_max_health( ) > 0 )
		return true;

	if ( entity->get_take_damage( ) != 2 ) {

		const class_index player_class = entity->get_client_class( )->m_class_id;

		if ( player_class != class_index::func_brush )
			return false;

	}

	const int collision_group = entity->get_collision_group( );

	if ( collision_group != 17 && collision_group != 6 && collision_group != 0 )
		return false;

	if ( health > 200 )
		return false;

	multiplayer_physics* physics_interface = dynamic_cast< multiplayer_physics* >( entity );
	if ( physics_interface ) {

		if ( physics_interface->get_multiplayer_physics_mode( ) != 1 )
			return false;

	} else {

		size_t class_name = g_hash.get( entity->get_class_name( ) );

		if ( class_name == g_hash.const_hash( "func_breakable" ) || class_name == g_hash.const_hash( "func_breakable_surf" ) ) {

			if ( class_name == g_hash.const_hash( "func_breakable_surf" ) ) {

				breakable_surface* surface = reinterpret_cast< breakable_surface* >( entity );

				if ( surface->is_broken( ) )
					return false;

			}

		} else if ( entity->physics_solid_mask_for_entity( ) & CONTENTS_PLAYERCLIP ) {

			return false;

		}
	}

	breakable_with_prop_data* breakable_interface = dynamic_cast< breakable_with_prop_data* >( entity );
	if ( breakable_interface ) {

		if ( breakable_interface->get_dmg_mod_bullet( ) <= 0.0f )
			return false;

	}

	return true;

}
