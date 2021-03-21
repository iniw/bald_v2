#pragma once

#include "datatypes/datatypes.h"

#define HPI	  1.570796327f
#define QPI	  0.785398163f
#define PI	  3.141592654f
#define PI2	  6.283185307f
#define GPI	  1.6180339887498f
#define RADPI 57.295779513082f

struct math {

	vec_3 vector_transform( vec_3& transform, matrix_3x4& matrix );

	q_ang calc_angle( const vec_3& m_start, const vec_3& end );

	float calc_fov( const q_ang& view_angles, const vec_3& start, const vec_3& end );

	void vector_angles( const vec_3& vector, q_ang& angle );

	void angle_vectors( const q_ang& angle, vec_3* foward, vec_3* right = nullptr, vec_3* up = nullptr );

	__forceinline float rad_to_deg( const float rad ) const {

		return rad * ( 180.f / PI );

	}

	__forceinline float deg_to_rad( const float deg ) const {

		return deg * ( PI / 180.f );

	}

};

inline math g_math;