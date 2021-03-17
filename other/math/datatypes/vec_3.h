#pragma once

#include <cmath>
#include <cfloat>
#include <limits>

#include "vec_2.h"

struct vec_3 {

	vec_3( float x = 0.f, float y = 0.f, float z = 0.f ) : x{ x }, y{ y }, z{ z } { }

	vec_3( const float* f ) : x( f[ 0 ] ), y( f[ 1 ] ), z( f[ 2 ] ) { }

	inline void init( float x = 0.f, float y = 0.f, float z = 0.f ) {

		this->x = x; this->y = y; this->z = z;

	}

	inline void init( const vec_3& v ) {

		x = v.x; y = v.y; z = v.z;

	}

	inline vec_3& operator+=( const vec_3& v ) {

		x += v.x; y += v.y; z += v.z; 
		
		return *this;

	}

	inline vec_3& operator-=( const vec_3& v ) {

		x -= v.x; y -= v.y; z -= v.z; 
		
		return *this;

	}

	inline vec_3& operator*=( const vec_3& v ) {

		x *= v.x; y *= v.y; z *= v.z; 
		
		return *this;

	}

	inline vec_3& operator/=( const vec_3& v ) {

		x /= v.x; y /= v.y; z /= v.z; 
		
		return *this;

	}

	inline vec_3& operator+=( const float& fl ) {

		x += fl; y += fl; z += fl; 
		
		return *this;

	}

	inline vec_3& operator-=( const float& fl ) {

		x -= fl; y -= fl; z -= fl; 
		
		return *this;

	}


	inline vec_3& operator*=( const float& fl ) {

		x *= fl; y *= fl; z *= fl; 
		
		return *this;

	}

	inline vec_3& operator/=( const float& fl ) {

		x /= fl; y /= fl; z /= fl; 
		
		return *this;

	}

	inline vec_3 operator+( const vec_3& v ) const {

		return vec_3( x + v.x, y + v.y, z + v.z );

	}

	inline vec_3 operator-( const vec_3& v ) const {

		return vec_3( x - v.x, y - v.y, z - v.z );

	}

	inline vec_3 operator*( const vec_3& v ) const {

		return vec_3( x * v.x, y * v.y, z * v.z );

	}

	inline vec_3 operator/( const vec_3& v ) const {

		return vec_3( x / v.x, y / v.y, z / v.z );

	}

	inline vec_3 operator+( const float& fl )  const {

		return vec_3( x + fl, y + fl, z + fl );

	}

	inline vec_3 operator-( const float& fl ) const {

		return vec_3( x - fl, y - fl, z - fl );

	}

	inline vec_3 operator*( const float& fl ) const {

		return vec_3( x * fl, y * fl, z * fl );

	}

	inline vec_3 operator/( const float& fl ) const {

		return vec_3( x / fl, y / fl, z / fl );

	}

	inline float dot( const vec_3& dot ) const {

		return ( x * dot.x + y * dot.y + z * dot.z );

	}

	inline float length( ) const {

		return std::sqrtf( length_sqr( ) );

	}

	inline float length_sqr( ) const {

		return dot( *this );

	}

	inline vec_2 to_2d( ) const {

		return vec_2( x, y );

	}

	inline float length_2d( ) const {

		return std::sqrtf( x * x + y * y );

	}

	inline float normalize( ) {

		const float length = this->length( );
		const float radius = 1.f / ( length + std::numeric_limits<float>::epsilon( ) );

		x *= radius;
		y *= radius;
		z *= radius;

		return length;

	}

	inline float vector_normalize( vec_3& v )  const {

		float length = v.length( );
		float radius = 1.f / ( length + FLT_EPSILON );

		v *= radius;

		return length;

	}

	inline vec_3 normalized( ) const {

		vec_3 v = *this;
		vector_normalize( v );
		return v;

	}

	float x, y, z;

};

struct __declspec( align( 16 ) ) vec_3a : public vec_3 {

	vec_3a( ) = default;

	explicit vec_3a( const vec_3& v ) {

		this->x = v.x, this->y = v.y, this->z = v.z; this->w = 0.f;

	}

	inline vec_3a& operator=( const vec_3& v ) {

		this->x = v.x, this->y = v.y, this->z = v.z; this->w = 0.f;

		return *this;
	}

	float w;
};