#pragma once

struct model;
struct studio_hdr;

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