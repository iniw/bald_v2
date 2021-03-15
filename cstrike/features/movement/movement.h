#pragma once

#include "../../cstrike.h"

struct movement {

	void correct( user_cmd* cmd, q_ang& old_view_angles );

};

inline movement g_movement;