#pragma once

struct surface_physics_params {

	float m_friction;
	float m_elasticity;
	float m_density;
	float m_thickness;
	float m_dampening;

};

struct surface_audio_params {

	float m_reflectivity;
	float m_hardness_factor;
	float m_roughness_factor;
	float m_rough_threshold;
	float m_hard_threshold;
	float m_hard_velocity_threshold;
	float m_high_pitch_occlusion;
	float m_mid_pitch_occlusion;
	float m_low_pitch_occlusion;

};

struct surface_sound_names {

	uint16_t m_walk_step_left;
	uint16_t m_walk_step_right;
	uint16_t m_run_step_left;
	uint16_t m_run_step_right;
	uint16_t m_impact_soft;
	uint16_t m_impact_hard;
	uint16_t m_scrape_smooth;
	uint16_t m_scrape_rough;
	uint16_t m_bullet_impact;
	uint16_t m_rolling;
	uint16_t m_break_sound;
	uint16_t m_strain_sound;
};

struct surface_sound_handles {

	uint16_t m_walk_step_left;
	uint16_t m_walk_step_right;
	uint16_t m_run_step_left;
	uint16_t m_run_step_right;
	uint16_t m_impact_soft;
	uint16_t m_impact_hard;
	uint16_t m_scrape_smooth;
	uint16_t m_scrape_rough;
	uint16_t m_bullet_impact;
	uint16_t m_rolling;
	uint16_t m_break_sound;
	uint16_t m_strain_sound;

};

struct surface_game_props {

	float    m_max_speed_factor;
	float    m_jump_factor;
	float    m_penetration_modifier;
	float    m_damage_modifier;
	uint16_t m_material;
	byte     m_climbable;
	byte     pad0[ 0x4 ];

};

struct surface_data {

	surface_physics_params	m_physics;
	surface_audio_params	m_audio;
	surface_sound_names		m_sounds;
	surface_game_props		m_game;
	surface_sound_handles	m_soundhandles;

};

struct physics_surface_props {

	inline auto get_surface_data( int idx ) {

		return g_utils.call_v_func< surface_data* >( this, 5, idx );

	}
};