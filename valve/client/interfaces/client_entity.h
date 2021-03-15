#pragma once

#include "client_unknown.h"
#include "client_renderable.h"
#include "client_networkable.h"
#include "client_thinkable.h"
#include "../signatures.h"
#include "../../other/utils/utils.h"
#include "../../data_map.h"

struct i_client_entity : public i_client_unknown, public i_client_renderable, public i_client_networkable, public i_client_thinkable {

	virtual void			release( ) override = 0;
	virtual const vec_3&	get_abs_origin( ) const = 0;
	virtual const q_angle&	get_abs_angles( ) const = 0;
	virtual void*			get_mouth( ) = 0;
	virtual bool			get_sound_spatialization( void* info ) = 0;
	virtual bool			is_blurred( ) = 0;

	inline void set_abs_origin( const vec_3& vector ) {

		auto function = g_signatures.m_set_abs_origin.as< void( __thiscall* )( void*, const vec_3& ) >( );

		return function( this, vector );

	}

	inline auto set_abs_angles( const q_angle& angles ) {

		auto function = g_signatures.m_set_abs_angles.as< void( __thiscall* )( void*, const q_angle& ) >( );

		return function( this, angles );

	}

	inline data_map* get_data_desc_map( ) {

		return g_utils.call_v_func< data_map* >( this, 15 );

	}

	inline data_map* get_prediction_desc_map( ) {

		return g_utils.call_v_func< data_map* >( this, 17 );

	}

};