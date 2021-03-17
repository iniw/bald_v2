#pragma once

#include "interfaces/client_entity.h"
#include "../../netvars/netvars.h"
#include "../../../other/hash/hash.h"

enum effects_flags {

	ef_bonemerge                  = 0x001,		
	ef_brightlight                = 0x002,		
	ef_dimlight                   = 0x004,		
	ef_nointerp                   = 0x008,		
	ef_noshadow                   = 0x010,		
	ef_nodraw                     = 0x020,			
	ef_noreceiveshadow            = 0x040,	
	ef_bonemerge_fastcull         = 0x080,												
	ef_item_blink                 = 0x100,				
	ef_parent_animates            = 0x200,			
	ef_marked_for_fast_reflection = 0x400,
	ef_noshadowdepth              = 0x800,			
	ef_shadowdepth_nocache        = 0x1000,	
	ef_noflashlight               = 0x2000,
	ef_nocsm                      = 0x4000,					
	ef_max_bits                   = 15

};

struct animation_layer;

struct base_entity : public i_client_entity {

	inline auto get_class_name( ) {

		return g_utils.call_v_func< const char* >( this, 142 );

	}

	inline auto physics_solid_mask_for_entity( ) {

		return g_utils.call_v_func< unsigned int >( this, 151 );

	}

	inline auto is_alive( ) {

		return g_utils.call_v_func< bool >( this, 155 );

	}

	inline auto is_player( ) {

		return g_utils.call_v_func< bool >( this, 157 );

	}

	inline auto& get_effects( ) {

		static auto offset = 0xF0;

		return *reinterpret_cast< int* >( reinterpret_cast< size_t >( this ) + offset );
	}

	inline auto& get_coordinated_frame( ) {

		static auto offset = g_netvars.find_in_datamap( this->get_data_desc_map( ), g_hash.get( XOR( "m_rgflCoordinateFrame" ) ) );

		return *reinterpret_cast< matrix_3x4* >( reinterpret_cast< size_t >( this ) + offset );

	}

	inline auto& get_origin( ) {

		static auto offset = g_netvars.m_offsets[ g_hash.get( XOR( "DT_BaseEntity->m_vecOrigin" ) ) ];

		return *reinterpret_cast< vec_3* >( reinterpret_cast< size_t >( this ) + offset );

	}

	inline auto& get_collision_group( ) {

		static auto offset = g_netvars.m_offsets[ g_hash.get( XOR( "DT_BaseEntity->m_CollisionGroup" ) ) ];

		return *reinterpret_cast< int* >( reinterpret_cast< size_t >( this ) + offset );

	}

	inline auto& get_sim_time( ) {

		static auto offset = g_netvars.m_offsets[ g_hash.get( XOR( "DT_BaseEntity->m_flSimulationTime" ) ) ];

		return *reinterpret_cast< float* >( reinterpret_cast< size_t >( this ) + offset );

	}

	inline auto& get_old_sim_time( ) {

		static auto offset = g_netvars.m_offsets[ g_hash.get( XOR( "DT_BaseEntity->m_flSimulationTime" ) ) ] + 0x4;

		return *reinterpret_cast< float* >( reinterpret_cast< size_t >( this ) + offset );

	}

	inline auto& get_mins( ) {

		static auto offset = g_netvars.m_offsets[ g_hash.get( XOR( "DT_BaseEntity->m_vecMins" ) ) ];

		return *reinterpret_cast< vec_3* >( reinterpret_cast< size_t >( this ) + offset );

	}

	inline auto& get_maxs( ) {

		static auto offset = g_netvars.m_offsets[ g_hash.get( XOR( "DT_BaseEntity->m_vecMaxs" ) ) ];

		return *reinterpret_cast< vec_3* >( reinterpret_cast< size_t >( this ) + offset );

	}

	inline auto& get_team( ) {

		static auto offset = g_netvars.m_offsets[ g_hash.get( XOR( "DT_BaseEntity->m_iTeamNum" ) ) ];

		return *reinterpret_cast< int* >( reinterpret_cast< size_t >( this ) + offset );

	}

	inline auto calc_absolute_velocity( ) { // grr

		auto function = g_signatures.m_calc_absolute_velocity.as< void( __thiscall* )( void* ) >( );

		return function( this );

	}

	inline auto& get_abs_velocity( ) {

		auto offset = g_signatures.m_abs_velocity.add( 0x4 ).to< size_t >( );

		calc_absolute_velocity( );

		return *reinterpret_cast< vec_3* >( reinterpret_cast< size_t >( this ) + offset );

	}

	inline auto get_anim_overlay( int i ) {

		auto offset = g_signatures.m_anim_overlay.add( 0x2 ).to< size_t >( );

		return reinterpret_cast< animation_layer* >( i * 0x38 + *reinterpret_cast< size_t* >( reinterpret_cast< size_t >( this ) + offset ) );

	}

	inline auto get_ground_entity( ) {

		auto function = g_signatures.m_get_ground_entity.as< base_entity* ( __thiscall* )( void* ) >( );

		return function( this );

	}

	inline auto invalidate_physics_recursive( int change_flags ) {

		auto function = g_signatures.m_invalidate_physics_recursive.as< void( __thiscall* )( void*, int ) >( );

		return function( this, change_flags );

	}

};