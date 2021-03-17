#pragma once

class vec_2 {
public:

	vec_2( float x = 0, float y = 0 ) : x( x ), y( y ) { }

	vec_2( float* v ) : x( v[ 0 ] ), y( v[ 1 ] ) { }

	inline vec_2& operator+=( const vec_2& v ) {

		x += v.x; y += v.y;

		return *this;

	}

	inline vec_2& operator-=( const vec_2& v ) {

		x -= v.x; y -= v.y;

		return *this;

	}

	inline vec_2& operator*=( const vec_2& v ) {

		x *= v.x; y *= v.y;

		return *this;

	}

	inline vec_2& operator/=( const vec_2& v ) {

		x /= v.x; y /= v.y;

		return *this;

	}

	inline vec_2& operator+=( const float& fl ) {

		x += fl; y += fl;

		return *this;

	}

	inline vec_2& operator-=( const float& fl ) {

		x -= fl; y -= fl;

		return *this;

	}


	inline vec_2& operator*=( const float& fl ) {

		x *= fl; y *= fl;

		return *this;

	}

	inline vec_2& operator/=( const float& fl ) {

		x /= fl; y /= fl;

		return *this;

	}

	inline vec_2 operator+( const vec_2& v ) const {

		return vec_2( x + v.x, y + v.y );

	}

	inline vec_2 operator-( const vec_2& v ) const {

		return vec_2( x - v.x, y - v.y );

	}

	inline vec_2 operator*( const vec_2& v ) const {

		return vec_2( x * v.x, y * v.y );

	}

	inline vec_2 operator/( const vec_2& v ) const {

		return vec_2( x / v.x, y / v.y );

	}

	inline vec_2 operator+( const float& fl ) const {

		return vec_2( x + fl, y + fl );

	}

	inline vec_2 operator-( const float& fl ) const {

		return vec_2( x - fl, y - fl );

	}

	inline vec_2 operator*( const float& fl ) const {

		return vec_2( x * fl, y * fl );

	}

	inline vec_2 operator/( const float& fl ) const {

		return vec_2( x / fl, y / fl );

	}

	float x, y;

};