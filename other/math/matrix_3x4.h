#pragma once

#include "vec_3.h"
#include <limits>

struct matrix_3x4 {

	matrix_3x4( ) = default;

	matrix_3x4(
		float m00, float m01, float m02, float m03,
		float m10, float m11, float m12, float m13,
		float m20, float m21, float m22, float m23 ) {

		data[ 0 ][ 0 ] = m00; data[ 0 ][ 1 ] = m01; data[ 0 ][ 2 ] = m02; data[ 0 ][ 3 ] = m03;
		data[ 1 ][ 0 ] = m10; data[ 1 ][ 1 ] = m11; data[ 1 ][ 2 ] = m12; data[ 1 ][ 3 ] = m13;
		data[ 2 ][ 0 ] = m20; data[ 2 ][ 1 ] = m21; data[ 2 ][ 2 ] = m22; data[ 2 ][ 3 ] = m23;

	}

	matrix_3x4( const vec_3& x_axis, const vec_3& y_axis, const vec_3& z_axis, const vec_3& origin ) {

		init( x_axis, y_axis, z_axis, origin );

	}

	// create matrix where the X axis = forward, the Y axis = left, the Z axis = up
	void init( const vec_3& x, const vec_3& y, const vec_3& z, const vec_3& origin ) {

		this->at( 0 ) = x;
		this->at( 1 ) = y;
		this->at( 2 ) = z;
		this->at( 3 ) = origin;

	}

	void set_origin( const vec_3& origin ) {

		this->at( 3 ) = origin;

	}

	constexpr void invalidate( ) {

		for ( int i = 0; i < 3; i++ ) {
			for ( int k = 0; k < 4; k++ )
				data[ i ][ k ] = std::numeric_limits<float>::infinity( );
		}

	}

	float* operator[]( int i ) {

		return data[ i ];

	}

	const float* operator[]( int i ) const {

		return data[ i ];

	}

	vec_3 at( int i ) const {

		return vec_3( data[ 0 ][ i ], data[ 1 ][ i ], data[ 2 ][ i ] );

	}

	float* base( ) {

		return &data[ 0 ][ 0 ];

	}

	const float* base( ) const {

		return &data[ 0 ][ 0 ];

	}

	float data[ 3 ][ 4 ] = { };
};