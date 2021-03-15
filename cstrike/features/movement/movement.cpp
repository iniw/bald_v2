#include "movement.h"

#include <algorithm>

void movement::correct( user_cmd* cmd, q_ang& old_view_angles ) {

	if ( !g_cstrike.m_local->is_alive( ) )
		return;

	static convar* cl_forwardspeed = g_interfaces.m_convar->find_var( "cl_forwardspeed" );
	if ( !cl_forwardspeed )
		return;

	static convar* cl_sidespeed = g_interfaces.m_convar->find_var( "cl_sidespeed" );
	if ( !cl_sidespeed )
		return;

	static convar* cl_upspeed = g_interfaces.m_convar->find_var( "cl_upspeed" );
	if ( !cl_upspeed )
		return;

	const float max_forward_speed = cl_forwardspeed->get_float( );
	const float max_side_speed = cl_sidespeed->get_float( );
	const float max_up_speed = cl_upspeed->get_float( );

	vec_3 forward = { }, right = { }, up = { };
	g_math.angle_vectors( old_view_angles, &forward, &right, &up );

	forward.z = right.z = up.x = up.y = 0.f;

	forward.normalize( );
	right.normalize( );
	up.normalize( );

	vec_3 old_forward = { }, old_right = { }, old_up = { };
	g_math.angle_vectors( cmd->m_view_angles, &old_forward, &old_right, &old_up );

	old_forward.z = old_right.z = old_up.x = old_up.y = 0.f;

	old_forward.normalize( );
	old_right.normalize( );
	old_up.normalize( );

	const float pitch_forward = forward.x * cmd->m_forward_move;
	const float yaw_forward = forward.y * cmd->m_forward_move;
	const float pitch_side = right.x * cmd->m_side_move;
	const float yaw_side = right.y * cmd->m_side_move;
	const float roll_up = up.z * cmd->m_up_move;

	const float x = old_forward.x * pitch_side + old_forward.y * yaw_side + old_forward.x * pitch_forward + old_forward.y * yaw_forward + old_forward.z * roll_up;
	const float y = old_right.x * pitch_side + old_right.y * yaw_side + old_right.x * pitch_forward + old_right.y * yaw_forward + old_right.z * roll_up;
	const float z = old_up.x * yaw_side + old_up.y * pitch_side + old_up.x * yaw_forward + old_up.y * pitch_forward + old_up.z * roll_up;

	cmd->m_forward_move = std::clamp( x, -max_forward_speed, max_forward_speed );
	cmd->m_side_move = std::clamp( y, -max_side_speed, max_side_speed );
	cmd->m_up_move = std::clamp( z, -max_up_speed, max_up_speed );

}
