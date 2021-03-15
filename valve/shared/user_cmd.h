#pragma once

#include <cstdint>

struct user_cmd {

    char    pad0[ 0x4 ];
    int     m_command_number;
    int     m_tick_count;
    q_ang   m_view_angles;
    vec_3   m_aim_direction;
    float   m_forward_move;
    float   m_side_move;
    float   m_up_move;
    int	    m_buttons;
    int	    m_impulse;
    int	    m_weapon_select;
    int	    m_weapon_sub_type;
    int	    m_random_seed;
    short   m_moused_x;
    short   m_moused_y;
    bool    m_has_been_predicted;

};