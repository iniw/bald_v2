#pragma once

#include <assert.h>
#include <functional>
#include "../../other/math/math.h"

enum disp_surf_flags {

	dispsurf_flag_surface = ( 1 << 0 ),
	dispsurf_flag_walkable = ( 1 << 1 ),
	dispsurf_flag_buildable = ( 1 << 2 ),
	dispsurf_flag_surfprop1 = ( 1 << 3 ),
	dispsurf_flag_surfprop2 = ( 1 << 4 )

};

enum trace_type {

	trace_everything = 0,
	trace_world_only,
	trace_entities_only,
	trace_everything_filter_props,
	trace_filtersky

};

enum debug_trace_counter_behavior {

	trace_counter_set = 0,
	trace_counter_inc,

};

struct brush_side_info {

	vec_3a			m_plane;
	uint16_t	    m_bevel;
	uint16_t	    m_thin;

};

struct plane {

	vec_3		m_normal;
	float		m_distance;
	byte	    m_type;
	byte	    m_sign_bits;
	byte	    pad[ 0x2 ];

};

struct trace_surface {

	const char* m_name;
	short		m_surface_props;
	uint16_t	m_flags;

};

struct base_trace {

	base_trace( ) { }

	vec_3			m_start;	
	vec_3			m_end;	
	plane			m_plane;	
	float			m_fraction;
	int				m_contents;
	uint16_t	    m_disp_flags;
	bool			m_all_solid;
	bool			m_start_solid;

};

struct cs_player;
struct game_trace : public base_trace {

	game_trace( ) : m_hit_entity( nullptr ), m_hitgroup( 0 ) { }

	float				m_fraction_left_solid;	
	trace_surface		m_surface;
	int					m_hitgroup;				
	short				m_physics_bone;			
	uint16_t		    m_world_surface_index;	
	cs_player*          m_hit_entity;
	int					m_hitbox;					

	inline bool did_hit( ) const {

		return ( m_fraction < 1.0f || m_all_solid || m_start_solid );

	}

	inline bool is_visible( ) const {

		return ( m_fraction > 0.97f );

	}

private:
	game_trace( const game_trace& other ) {

		*this = other;

	}

};

using trace = game_trace;

struct ray {

	ray( const vec_3& start, const vec_3& end ) : m_start( start ), m_delta( end - start ), m_world_axis_transform( nullptr ), m_is_ray( true ) {

		m_is_swept = this->m_delta.length_sqr( ) != 0.f;

	}

	ray( const vec_3& start, const vec_3& end, const vec_3& mins, const vec_3& maxs ) {

		m_delta = end - start;

		m_world_axis_transform = nullptr;
		m_is_swept = m_delta.length_sqr( ) != 0.f;
		
		m_extents = maxs - mins;
		m_extents *= 0.5f;
		m_is_ray = m_extents.length_sqr( ) < 1e-6;

		m_start_offset = mins + maxs;
		m_start_offset *= 0.5f;
		m_start = start + m_start_offset;
		m_start_offset *= -1.0f;

	}

	vec_3a				m_start;
	vec_3a				m_delta;
	vec_3a				m_start_offset;
	vec_3a				m_extents;
	const matrix_3x4*   m_world_axis_transform;
	bool				m_is_ray;
	bool				m_is_swept;

};

struct i_handle_entity;
struct base_trace_filter {

	virtual bool should_hit_entity( i_handle_entity* entity, int contentsMask ) = 0;
	virtual trace_type get_trace_type( ) const = 0;

};

struct trace_filter : public base_trace_filter {

	using filter_callback_fn = std::function<bool( i_handle_entity*, int )>;

	trace_filter( const i_handle_entity* skip_entity, trace_type trace_type = trace_everything ) : m_skip( skip_entity ), m_trace_type( trace_type ) { }

	trace_filter( filter_callback_fn&& check_callback, trace_type trace_type = trace_everything ) : m_check_callback( check_callback ), m_trace_type( trace_type ) { }

	inline bool should_hit_entity( i_handle_entity* handle_entity, int contents_mask ) override {

		// if given user defined callback - check it
		if ( m_check_callback != nullptr )
			return m_check_callback( handle_entity, contents_mask );

		assert( m_skip );	

		// else skip given entity
		return !( handle_entity == m_skip );

	}

	inline trace_type get_trace_type( ) const override {

		return m_trace_type;

	}

private:
	const i_handle_entity* m_skip = nullptr;
	filter_callback_fn     m_check_callback = nullptr;
	trace_type             m_trace_type = trace_everything;

};

struct engine_trace {

	inline auto get_point_contents( const vec_3& pos, int mask = 0xFFFFFFFF, i_handle_entity** entity = nullptr ) {

		return g_utils.get_v_func< int( __thiscall* )( void*, const vec_3&, int, i_handle_entity**) >( this, 0 )( this, pos, mask, entity );

	}

	inline auto clip_ray_to_entity( const ray& r, unsigned int mask, i_handle_entity* handle, trace* tr ) {

		return g_utils.get_v_func< void( __thiscall* )( void*, const ray&, unsigned int, i_handle_entity*, trace* ) >( this, 3 )( this, r, mask, handle, tr );

	}

	inline auto trace_ray( const ray& r, unsigned int mask, base_trace_filter* filter, trace* tr ) {

		return g_utils.get_v_func< void( __thiscall* )( void*, const ray&, unsigned int, base_trace_filter*, trace* ) >( this, 5 )( this, r, mask, filter, tr );

	}

};