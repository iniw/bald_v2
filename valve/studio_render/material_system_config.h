#pragma once

struct material_video_mode {

	int m_width;
	int m_height;
	int m_format;
	int m_refresh_rate;

};

struct material_system_config {

	char  pad0[ 0x10 ];
	float m_monitor_gamma;
	float m_gamma_tv_range_min;
	float m_gamma_tv_range_max;
	float m_gamma_tv_exponent;
	bool  m_gamma_tv_enabled;
	bool  m_triple_buffered;
	int   m_aa_samples;
	int   m_force_anisotropic_level;
	int   m_skip_mip_levels;
	int   m_dx_support_level;
	int   m_flags;
	bool  m_edit_mode;
	char  m_proxies_test_mode;
	bool  m_compressed_textures;
	bool  m_filter_lightmaps;
	bool  m_filter_textures;
	bool  m_reverse_depth;
	bool  m_buffer_primitives;
	bool  m_draw_flat;
	bool  m_measure_fill_rate;
	bool  m_visualize_fill_rate;
	bool  m_no_transparency;
	bool  m_software_lighting;
	bool  m_allow_cheats;
	char  m_show_mip_levels;
	bool  m_show_low_res_image;
	bool  m_show_normal_map;
	bool  m_mip_map_textures;
	char  m_fullbright;
	bool  m_fast_no_bump;
	bool  m_suppress_rendering;
	bool  m_draw_gray;
	bool  m_show_specular;
	bool  m_show_diffuse;
	int   m_windowed_size_limit_width;
	int   m_windowed_size_limit_height;
	int   m_aa_quality;
	bool  m_shadow_depth_texture;
	bool  m_motion_blur;
	bool  m_support_flashlight;
	bool  m_paint_enabled;
	char  pad1[ 0xC ];

};