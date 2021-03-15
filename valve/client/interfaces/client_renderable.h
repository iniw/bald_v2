#pragma once

#include <cstdint>

struct i_client_unknown;
struct matrix_3x4;

using client_shadow_handle_t = uint16_t;
using client_render_handle_t = uint16_t;
using model_instance_handle_t = uint16_t;

struct i_client_renderable {

	virtual i_client_unknown*               get_client_unknown( ) = 0;
	virtual vec_3&                          get_render_origin( void ) = 0;
	virtual vec_3&                          get_render_angles( void ) = 0;
	virtual bool                            should_draw( void ) = 0;
	virtual int                             get_render_flags( void ) = 0;
	virtual void                            unused( void ) const { }
	virtual client_shadow_handle_t          get_shadow_handle( ) const = 0;
	virtual client_render_handle_t&         render_handle( ) = 0;
	virtual const model*                    get_model( ) const = 0;
	virtual int                             draw_model( int flags, const uint8_t& instance ) = 0;
	virtual int                             get_body( ) = 0;
	virtual void                            get_color_modulation( float* color ) = 0;
	virtual bool                            lod_test( ) = 0;
	virtual bool                            setup_bones( matrix_3x4* bone_to_world_out, int max_bones, int bone_mask, float current_time ) = 0;
	virtual void                            setup_weights( const matrix_3x4* bone_to_world_out, int flex_weight_count, float* flex_weights, float* flex_delayed_weights ) = 0;
	virtual void                            do_animation_events( void ) = 0;
	virtual void*                           get_pvs_notify_interface( ) = 0;
	virtual void                            get_render_bounds( vec_3& mins, vec_3& maxs ) = 0;
	virtual void                            get_render_bounds_worldspace( vec_3& mins, vec_3& maxs ) = 0;
	virtual void                            get_shadow_render_bounds( vec_3& mins, vec_3& maxs, int shadow_type ) = 0;
	virtual bool                            should_receive_projected_textures( int flags ) = 0;
	virtual bool                            get_shadow_cast_distance( float* dist, int shadow_type ) const = 0;
	virtual bool                            get_shadow_cast_direction( vec_3* m_direction, int shadow_type ) const = 0;
	virtual bool                            is_shadow_dirty( ) = 0;
	virtual void                            mark_shadow_dirty( bool dirty ) = 0;
	virtual i_client_renderable*            get_shadow_parent( ) = 0;
	virtual i_client_renderable*            first_shadow_child( ) = 0;
	virtual i_client_renderable*            next_shadow_peer( ) = 0;
	virtual int                             shadow_cast_type( ) = 0;
	virtual void                            create_model_instance( ) = 0;
	virtual model_instance_handle_t         get_model_instance( ) = 0;
	virtual const matrix_3x4&               renderable_to_world_transform( ) = 0;
	virtual int                             lookup_attachment( const char* attachment_name ) = 0;
	virtual bool                            get_attachment( int number, vec_3& origin, vec_3& angles ) = 0;
	virtual bool                            get_attachment( int number, matrix_3x4& matrix ) = 0;
	virtual float*                          get_render_clip_plane( void ) = 0;
	virtual int                             get_skin( ) = 0;
	virtual void                            on_threaded_draw_setup( ) = 0;
	virtual bool                            uses_flex_delayed_weights( ) = 0;
	virtual void                            record_tool_message( ) = 0;
	virtual bool                            should_draw_for_split_screen_user( int slot ) = 0;
	virtual uint8_t                         override_alpha_modulation( uint8_t alpha ) = 0;
	virtual uint8_t                         override_shadow_alpha_modulation( uint8_t alpha ) = 0;

};