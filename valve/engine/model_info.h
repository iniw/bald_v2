#pragma once

struct model;
struct studio_hdr;

enum rendereable_info_flags {

	rendereable_flags_disable_rendering       = 0x01,
	rendereable_flags_haschanged              = 0x02,
	rendereable_flags_alternate_sorting       = 0x04,
	rendereable_flags_render_with_viewmodels  = 0x08,
	rendereable_flags_bloat_bounds            = 0x10,
	rendereable_flags_bounds_valid            = 0x20,
	rendereable_flags_bounds_always_recompute = 0x40,
	rendereable_flags_is_sprite               = 0x80,
	rendereable_flags_force_opaque_pass       = 0x100

};

struct model_info {

	inline auto get_model( int modelindex ) {

		return g_utils.call_v_func< model* >( this, 1, modelindex );

	}
	inline auto  get_model_index( const char* name ) {

		return g_utils.call_v_func< int >( this, 2, name );

	}

	inline auto  get_model_name( const model* model ) {

		return g_utils.call_v_func< char* >( this, 3, model );

	}

	inline auto get_studio_model( const model* model ) {

		return g_utils.call_v_func< studio_hdr* >( this, 32, model );

	}

};