#include "math.h"

#include <cmath>
#include <DirectXMath.h>

vec_3 math::vector_transform( vec_3& transform, matrix_3x4& matrix ) {

	return vec_3( transform.dot( matrix[ 0 ] ) + matrix[ 0 ][ 3 ],
				  transform.dot( matrix[ 1 ] ) + matrix[ 1 ][ 3 ],
				  transform.dot( matrix[ 2 ] ) + matrix[ 2 ][ 3 ] );

}

q_ang math::calc_angle( const vec_3& m_start, const vec_3& end ) {

	q_ang view_point;

	vector_angles( end - m_start, view_point );

	view_point.normalize( );

	return view_point;
}

float math::calc_fov( const q_ang& view_angles, const vec_3& start, const vec_3& end ) {

	vec_3 dir, fw;
	dir = ( end - start ).normalized( );

	angle_vectors( view_angles, &fw );

	return ( std::max )( rad_to_deg( std::acos( fw.dot( dir ) ) ), 0.f );

}

void math::vector_angles( const vec_3& vector, q_ang& angle ) {

	float pitch, yaw;

	if ( vector.x == 0.f && vector.y == 0.f ) {

		pitch = ( vector.z > 0.f ) ? 270.f : 90.f;
		yaw = 0.f;

	} else {

		pitch = std::atan2f( -vector.z, vector.length_2d( ) ) * 180.f / PI;

		if ( pitch < 0.f )
			pitch += 360.f;

		yaw = std::atan2f( vector.y, vector.x ) * 180.f / PI;

		if ( yaw < 0.f )
			yaw += 360.f;

	}

	angle.pitch = pitch;
	angle.yaw = yaw;
	angle.roll = 0.f;

}

void math::angle_vectors( const q_ang& angle, vec_3* foward, vec_3* right, vec_3* up ) {

	float sp, sy, sr, cp, cy, cr;

	DirectX::XMScalarSinCos( &sp, &cp, deg_to_rad( angle.pitch ) );
	DirectX::XMScalarSinCos( &sy, &cy, deg_to_rad( angle.yaw ) );
	DirectX::XMScalarSinCos( &sr, &cr, deg_to_rad( angle.roll ) );

	if ( foward != nullptr ) {

		foward->x = cp * cy;
		foward->y = cp * sy;
		foward->z = -sp;

	}

	if ( right != nullptr ) {

		right->x = -1 * sr * sp * cy + -1 * cr * -sy;
		right->y = -1 * sr * sp * sy + -1 * cr * cy;
		right->z = -1 * sr * cp;

	}

	if ( up != nullptr ) {

		up->x = cr * sp * cy + -sr * -sy;
		up->y = cr * sp * sy + -sr * cy;
		up->z = cr * cp;

	}

}
