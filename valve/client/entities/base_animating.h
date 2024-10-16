#pragma once

#include "base_player.h"

#include "../../studio.h"
#include "../../engine/utl_mem/utl_mem.h"

struct csgo_player_anim_state;

struct base_animating : base_player {

	inline void set_sequence( int sequence ) {

		g_utils.call_v_func< void >( this, 218, sequence );

	}

	inline auto lookup_bone( const char* name ) {

		auto function = g_signatures.m_lookup_bone.as< int( __thiscall* )( void*, const char* ) >( );

		return function( this, name );

	}

	inline auto get_bone_position( int bone_id, vec_3& origin ) {

		auto function = g_signatures.m_get_bone_position.as< void( __thiscall* )( void*, int, vec_3* ) >( );

		vec_3 vectors[ 4 ];
		function( this, bone_id, vectors );
		origin = { vectors[ 1 ].x, vectors[ 2 ].y, vectors[ 3 ].z };

	}

	inline auto get_model_ptr( ) {

		auto function = g_signatures.m_get_model_ptr.as< studio_hdr* ( __thiscall* )( void* ) >( );

		return function( this );

	}

	inline auto get_first_sequence_anim_tag( int sequence, int desired_tag ) {

		auto function = g_signatures.m_get_first_sequence_anim_tag.as< float( __thiscall* )( void*, int, int, int ) >( );

		return function( this, sequence, desired_tag, 0 );

	}

	inline auto lookup_pose_parameter( const char* name ) {

		auto function = g_signatures.m_lookup_pose_parameter.as< int( __thiscall* )( void*, studio_hdr*, const char* name ) >( );

		return function( this, get_model_ptr( ), name );

	}

	inline auto& get_sequence( ) {

		static auto offset = g_netvars.m_offsets[ g_hash.get( XOR( "DT_BaseAnimating->m_nSequence" ) ) ];

		return *reinterpret_cast< int* >( reinterpret_cast< size_t >( this ) + offset );

	}

	inline auto& occlusion_framecount( ) {

		return *reinterpret_cast< int* >( reinterpret_cast< size_t >( this ) + 0xA30 );
	}

	inline auto& occlusion_flags( ) {

		return *reinterpret_cast< int* >( reinterpret_cast< size_t >( this ) + 0xA68 );
	}

	inline auto& readable_bones( ) {

		return *reinterpret_cast< int* >( reinterpret_cast< size_t >( this ) + 0x26B0 );
	}

	inline auto& writeable_bones( ) {

		return *reinterpret_cast< int* >( reinterpret_cast< size_t >( this ) + 0x26AC );
	}

	inline auto& last_bone_setup_time( ) {

		return *reinterpret_cast< size_t* >( reinterpret_cast< size_t >( this ) + 0x2924 );
	}

	inline auto& last_bone_setup_frame( ) {

		return *reinterpret_cast< int* >( reinterpret_cast< size_t >( this ) + 0xA68 );
	}

	inline auto& most_recent_model_bone_counter( ) {

		return *reinterpret_cast< size_t* >( reinterpret_cast< size_t >( this ) + 0x2690 );
	}

	inline auto& get_anim_state( ) {

		return *reinterpret_cast< csgo_player_anim_state** >( reinterpret_cast< size_t >( this ) + 0x3914 );

	}

	inline auto& get_bone_count( ) {

		return *reinterpret_cast< int* >( reinterpret_cast< size_t >( this ) + 0x291C );

	}

	inline auto& get_bone_cache( ) {

		return *reinterpret_cast< utl_vector< matrix_3x4 >* >( reinterpret_cast< size_t >( this ) + 0x2910 );

	}

	inline auto set_pose_parameter( int parameter, float value ) {

		studio_hdr* studio_hdr = get_model_ptr( );
		if ( !studio_hdr )
			return value;

		if ( parameter >= 0.f ) {

			float new_value;
			
			__asm {

				pushad

				movss xmm2, [ value ]
				lea ecx, [ new_value ]
				push ecx
				mov edx, parameter
				mov ecx, studio_hdr
				call g_signatures.m_studio_set_pose_parameter
				pop ecx

				popad

			}

			get_pose_parameter( )[ parameter ] = new_value;

		}

		return value;

	}

	inline auto draw_server_hitboxes( float duration = 0.f, int /*bool*/ monocolor = 0 ) {

		base_player* player = base_player::util_player_by_index( get_index( ) );
		if ( !player )
			return;

		__asm {

			pushad

			movss xmm1, duration
			push monocolor
			mov ecx, player
			call g_signatures.m_draw_server_hitboxes

			popad
		}

	}

	inline void invalidate_bone_cache( ) {

		most_recent_model_bone_counter( ) = g_signatures.m_invalidate_bone_cache.add( 0xA ).get< unsigned long >( 2 ) - 1;

		last_bone_setup_time( ) = -FLT_MAX;

	}

};