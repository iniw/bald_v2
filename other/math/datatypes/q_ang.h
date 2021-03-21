#pragma once

#include <cmath>
#include <algorithm>

struct q_ang {

	q_ang( float pitch = 0.f, float yaw = 0.f, float roll = 0.f ) : pitch( pitch ), yaw( yaw ), roll( roll ) { }

	q_ang( const float* arr ) : pitch( arr[ 0 ] ), yaw( arr[ 1 ] ), roll( arr[ 2 ] ) { }

	inline void init( float pitch = 0.f, float yaw = 0.f, float roll = 0.f ) {

		this->pitch = pitch; this->yaw = yaw; this->roll = roll;

	}

	inline void init( const q_ang& a ) {

		this->pitch = a.pitch; this->yaw = a.yaw; this->roll = a.roll;

	}

	inline q_ang operator+=( const q_ang& a ) {

		pitch += a.pitch; yaw += a.yaw; roll += a.roll;

		return *this;

	}

	inline q_ang operator-=( const q_ang& a ) {

		pitch -= a.pitch; yaw -= a.yaw; roll -= a.roll;

		return *this;

	}

	inline q_ang operator*=( const q_ang& a ) {

		pitch *= a.pitch; yaw *= a.yaw; roll *= a.roll;

		return *this;

	}

	inline q_ang operator/=( const q_ang& a ) {

		pitch /= a.pitch; yaw /= a.yaw; roll /= a.roll;

		return *this;

	}

	inline q_ang operator+=( const float& fl ) {

		pitch += fl; yaw += fl; roll += fl;

		return *this;

	}

	inline q_ang operator-=( const float& fl ) {

		pitch -= fl; yaw -= fl; roll -= fl;

		return *this;

	}

	inline q_ang operator*=( const float& fl ) {

		pitch *= fl; yaw *= fl; roll *= fl;

		return *this;

	}

	inline q_ang operator/=( const float& fl ) {

		pitch /= fl; yaw /= fl; roll /= fl;

		return *this;

	}

	inline q_ang operator+( const q_ang& a ) const {

		return q_ang( pitch + a.pitch, yaw + a.yaw, roll + a.roll );

	}

	inline q_ang operator-( const q_ang& a ) const {

		return q_ang( pitch - a.pitch, yaw - a.yaw, roll - a.roll );

	}

	inline q_ang operator*( const q_ang& a ) const {

		return q_ang( pitch * a.pitch, yaw * a.yaw, roll * a.roll );

	}

	inline q_ang operator/( const q_ang& a ) const {

		return q_ang( pitch / a.pitch, yaw / a.yaw, roll / a.roll );

	}

	inline q_ang operator+( const float& fl ) const {

		return q_ang( pitch + fl, yaw + fl, roll + fl );

	}

	inline q_ang operator-( const float& fl ) const {

		return q_ang( pitch - fl, yaw - fl, roll - fl );

	}

	inline q_ang operator*( const float& fl ) const {

		return q_ang( pitch * fl, yaw * fl, roll * fl );

	}

	inline q_ang operator/( const float& fl ) const {

		return q_ang( pitch * fl, yaw * fl, roll * fl );

	}

	inline q_ang normalize( ) {

		pitch = std::isfinite( pitch ) ? std::remainderf( pitch, 360.f ) : 0.f;
		yaw   = std::isfinite( yaw ) ? std::remainderf( yaw, 360.f ) : 0.f;
		roll  = std::clamp( roll, -50.f, 50.f );

		return *this;

	}

	inline q_ang clamp( ) {

		pitch = std::clamp( pitch, -89.f, 89.f );
		yaw   = std::clamp( yaw, -180.f, 180.f );
		roll  = std::clamp( roll, -50.f, 50.f );

		return *this;

	}

	inline q_ang sanitize( ) {

		this->normalize( );
		this->clamp( );

		return *this;
	}

	float pitch, yaw, roll;

};