#pragma once

#include "../other/math/math.h"

#pragma region definitions

enum max_studio_defs {

	MAXSTUDIOBONECTRLS	= 4,
	MAXSTUDIOPOSEPARAM	= 24,
	MAXSTUDIOSKINS		= 32,	
	MAXSTUDIOFLEXCTRL	= 96,	
	MAXSTUDIOBONES		= 256,	
	MAXSTUDIOANIMBLOCKS	= 256,
	MAXSTUDIOFLEXDESC	= 1024

};

enum setup_bones_masks {

	BONE_USED_MASK				= 0x0007FF00,
	BONE_USED_BY_ANYTHING		= 0x0007FF00,
	BONE_USED_BY_HITBOX			= 0x00000100,
	BONE_USED_BY_ATTACHMENT		= 0x00000200,
	BONE_USED_BY_VERTEX_MASK	= 0x0003FC00,
	BONE_USED_BY_VERTEX_LOD0	= 0x00000400,
	BONE_USED_BY_VERTEX_LOD1	= 0x00000800,
	BONE_USED_BY_VERTEX_LOD2	= 0x00001000,
	BONE_USED_BY_VERTEX_LOD3	= 0x00002000,
	BONE_USED_BY_VERTEX_LOD4	= 0x00004000,
	BONE_USED_BY_VERTEX_LOD5	= 0x00008000,
	BONE_USED_BY_VERTEX_LOD6	= 0x00010000,
	BONE_USED_BY_VERTEX_LOD7	= 0x00020000,
	BONE_USED_BY_BONE_MERGE		= 0x00040000,
	BONE_ALWAYS_SETUP			= 0x00080000

};

enum hitbox {

	hitbox_invalid = -1,
	hitbox_head,
	hitbox_neck,
	hitbox_pelvis,
	hitbox_stomach,
	hitbox_thorax,
	hitbox_chest,
	hitbox_upper_chest,
	hitbox_right_thigh,
	hitbox_left_thigh,
	hitbox_right_calf,
	hitbox_left_calf,
	hitbox_right_foot,
	hitbox_left_foot,
	hitbox_right_hand,
	hitbox_left_hand,
	hitbox_right_upper_arm,
	hitbox_right_forearm,
	hitbox_left_upper_arm,
	hitbox_left_forearm,
	hitbox_max

};

enum hitgroup {

	hitgroup_generic = 0,
	hitgroup_head,
	hitgroup_chest,
	hitgroup_stomach,
	hitgroup_leftarm,
	hitgroup_rightarm,
	hitgroup_leftleg,
	hitgroup_rightleg,
	hitgroup_neck,
	hitgroup_gear = 10
	
};

#pragma endregion

struct model;
struct studio_hdr;

struct studio_seq_desc {
	int m_base_studio;
	inline studio_hdr* get_studio_hdr( ) const {

		return ( studio_hdr* )( ( std::uint8_t* )this + m_base_studio );

	}

	int	m_label_index;
	inline const char* get_label( ) const {

		return ( char* )this + m_label_index;

	}

	int	m_activity_name_index;
	inline const char* get_activity_name( ) const {

		return ( char* )this + m_activity_name_index;

	}

	int	m_flags;

	int	m_activity;
	int	m_activity_weight;

	int m_events;
	int m_event_index;
	inline void* get_event( int event ) const {

		if ( event < 0 || event >= m_events )
			return nullptr;

		return ( ( std::uint8_t* )this + m_event_index ) + event;

	}

	vec_3 m_bb_min;
	vec_3 m_bb_max;

	int	m_blends;
	int	m_blend_index;

	inline int get_anim_value( int x, int y ) const {

		if ( x >= m_group_size[ 0 ] )
			x = m_group_size[ 0 ] - 1;

		if ( y >= m_group_size[ 1 ] )
			y = m_group_size[ 1 ] - 1;

		int offset = y * m_group_size[ 0 ] + x;
		short* blends = ( short* )( ( std::uint8_t* )this + m_blend_index );
		return ( int )blends[ offset ];

	}

	int	  m_movement_index;
	int   m_group_size[ 2 ];
	int   m_param_index[ 2 ];
	float m_param_start[ 2 ];
	float m_param_end[ 2 ];
	int	  m_param_parent;

	float m_fade_in_time;
	float m_fade_out_time;

	int	m_entry_node;
	int	m_exit_node;
	int	m_node_flags;

	float m_entry_phase;
	float m_exit_phase;

	float m_last_frame;

	int	m_next_sequence;
	int	m_pose;

	int	m_ik_rules;

	int	m_auto_layers;
	int	m_auto_layer_index;
	inline void* get_auto_layer( int auto_layer ) const {

		if ( auto_layer < 0 || auto_layer >= m_auto_layers )
			return nullptr;

		return ( ( std::uint8_t* )this + m_auto_layer_index ) + auto_layer;

	}

	int	m_weight_list_index;
	inline float* get_bone_weight( int bone ) const {

		return ( ( float* )( ( std::uint8_t* )this + m_weight_list_index ) + bone );

	}

	int	m_pose_key_index;
	inline float* get_pose_key( int parameter, int animation ) const {

		return ( float* )( ( std::uint8_t* )this + m_pose_key_index ) + parameter * m_group_size[ 0 ] + animation;

	}

	int	m_ik_locks;
	int	m_ik_lock_index;
	inline void* get_ik_lock( int ik ) const {

		if ( ik < 0 || ik >= m_ik_locks )
			return nullptr;

		return ( ( std::uint8_t* )this + m_ik_lock_index ) + ik;

	}

	int	m_key_value_index;
	int	m_key_value_size;
	inline const char* key_value_text( ) const {

		if ( !m_key_value_size )
			return nullptr;

		return ( char* )this + m_key_value_index;

	}

	int	m_cycle_pose_index;

	int m_activity_modifier_index;
	int	m_activity_modifiers;

	int	m_anim_tag_index;
	int	m_anim_tags;

	int	m_root_driver_index;
	char pad0[ 0x8 ];
};

struct studio_bbox {

	int			m_bone;
	int			m_group;
	vec_3		m_bb_min;
	vec_3		m_bb_max;
	int			m_hitbox_name_index;
	q_ang		m_offset_orientation;
	float		m_radius;
	char		pad0[ 0x10 ];

	inline const char* get_hitbox_name( ) const {

		if ( !m_hitbox_name_index )
			return nullptr;

		return ( const char* )this + m_hitbox_name_index;

	}
};

struct studio_hitbox_set {

	int m_name_index;
	int m_hitboxes;
	int m_hitbox_index;

	inline const char* get_name( ) const {

		if ( !m_name_index )
			return nullptr;

		return ( char* )this + m_name_index;

	}

	inline studio_bbox* get_hitbox( int hitbox ) const {

		if ( hitbox < 0 || hitbox >= m_hitboxes )
			return nullptr;

		return ( studio_bbox* )( ( std::uint8_t* )this + m_hitbox_index ) + hitbox;
	}

};

struct studio_bone {

	int			m_name_index;
	int			m_parent;
	int			m_bone_controller[ 6 ];

	vec_3		m_position;
	char		pad0[ 0x1C ];

	vec_3		m_position_scale;
	vec_3		m_euler_scale;

	matrix_3x4  m_pose_to_bone;
	char		pad1[ 0x10 ];
	int			m_flags;
	int			m_procedure_type;
	int			m_procedure_index;
	mutable int m_physics_bone;
	int			m_surface_prop_index;
	int			m_contents;
	int			m_surface_prop;
	char		pad2[ 0x1C ];

	inline const char* get_name( ) {

		if ( !m_name_index )
			return nullptr;

		return ( char* )this + m_name_index;

	}

	inline void* get_procedure( ) const {

		if ( !m_procedure_index )
			return nullptr;

		return ( void* )( ( std::uint8_t* )this + m_procedure_index );

	}

	inline const char* get_surface_prop_name( ) const {

		if ( !m_surface_prop_index )
			return nullptr;

		return ( char* )this + m_surface_prop_index;

	}

};

struct studio_bone_controller {

	int		m_bone;
	int		m_type;
	float	m_start;
	float	m_end;
	int		m_rest;
	int		m_inputfield;
	int		unused[ 8 ];

};

struct studio_hdr {
	int	m_id;
	int	m_version;
	int m_checksum;

	char m_name[ 64 ];
	int	 m_length;

	vec_3 m_eye_position;
	vec_3 m_illum_position;
	vec_3 m_hull_min;
	vec_3 m_hull_max;
	vec_3 m_view_bb_min;
	vec_3 m_view_bb_max;

	int	m_flags;

	int	m_bones;
	int	m_bone_index;
	inline studio_bone* get_bone( int bone ) const {

		if ( bone < 0 || bone >= bone )
			return nullptr;

		return ( studio_bone* )( ( std::uint8_t* )this + m_bone_index ) + bone;

	}

	int	m_bone_controllers;
	int	m_bone_controller_index;
	inline void* get_bone_controller( int bone_controller ) const {

		if ( bone_controller < 0 || bone_controller >= m_bone_controllers )
			return nullptr;

		return ( ( std::uint8_t* )this + m_bone_controller_index ) + bone_controller;

	}

	int	m_hitbox_sets;
	int	m_hitbox_set_index;
	inline studio_hitbox_set* get_hitbox_set( int set ) const {

		if ( set < 0 || set >= m_hitbox_sets )
			return nullptr;

		return ( studio_hitbox_set* )( ( std::uint8_t* )this + m_hitbox_set_index ) + set;

	}

	inline studio_bbox* get_hitbox( int hitbox, int set ) const {

		const studio_hitbox_set* hitbox_set = get_hitbox_set( set );

		if ( hitbox_set == nullptr )
			return nullptr;

		return hitbox_set->get_hitbox( hitbox );

	}

	inline int get_hitbox_count( int set ) const {

		const studio_hitbox_set* hitbox_set = get_hitbox_set( set );

		if ( hitbox_set == nullptr )
			return 0;

		return hitbox_set->m_hitboxes;

	}

	int	m_local_animations;
	int	m_local_animation_index;
	inline void* get_anim_description( int animation ) const {

		if ( animation < 0 || animation >= m_local_animations )
			animation = 0;

		return ( ( std::uint8_t* )this + m_local_animation_index ) + animation;

	}

	int m_local_sequences;
	int m_local_sequence_index;
	inline studio_seq_desc* get_sequence_description( int sequence ) const {

		if ( sequence < 0 || sequence >= m_local_sequences )
			sequence = 0;

		return ( studio_seq_desc* )( ( std::uint8_t* )this + m_local_sequence_index ) + sequence;

	}

	inline auto seq_desc( int seq ) {

		auto function = g_signatures.m_seqdesc.as< studio_seq_desc&( __thiscall* )( void*, int ) >( );

		return function( this, seq );

	}

	mutable int m_activity_list_version;
	mutable int m_events_indexed;

	int	m_textures;
	int	m_texture_index;
	inline void* get_texture( int index ) const {

		if ( index < 0 || index >= m_textures )
			return nullptr;

		return ( ( std::uint8_t* )this + m_texture_index ) + index;

	}

	int	m_cd_textures;
	int	m_cd_texture_index;
	inline char* get_cd_texture( int index ) const {

		if ( index < 0 || index >= m_cd_textures )
			return nullptr;

		return ( ( ( char* )this ) + *( ( int* )( ( std::uint8_t* )this + m_cd_texture_index ) + index ) );

	}

	int	m_skin_refs;
	int m_skin_families;
	int m_skin_index;
	inline short* get_skin_ref( int index ) const {

		if ( index < 0 || index >= m_skin_refs )
			return nullptr;

		return ( short* )( ( std::uint8_t* )this + m_skin_index ) + index;

	}

	int	m_body_parts;
	int	m_body_part_index;
	inline void* get_body_part( int index ) const {

		if ( index < 0 || index >= m_body_parts )
			return nullptr;

		return ( ( std::uint8_t* )this + m_body_part_index ) + index;

	}

	int	m_attachments;
	int	m_attachment_index;
	inline void* get_attachment( int index ) const {

		if ( index < 0 || index >= m_attachments )
			return nullptr;

		return ( ( std::uint8_t* )this + m_attachment_index ) + index;

	}

	int	m_transitions;
	int	m_transition_index;
	int	m_transition_name_index;
	inline std::uint8_t* get_transition( int index ) const {

		if ( index < 0 || index >= ( m_transitions * m_transitions ) )
			return nullptr;

		return ( std::uint8_t* )( ( std::uint8_t* )this + m_transition_index ) + index;

	}

	int	m_flex_descs;
	int	m_flex_desc_index;
	inline void* get_flex_description( int index ) const {

		if ( index < 0 || index >= m_flex_descs )
			return nullptr;

		return ( ( std::uint8_t* )this + m_flex_desc_index ) + index;

	}

	int	m_flex_controllers;
	int	m_flex_controller_index;
	inline void* get_flex_controller( int index ) const {

		if ( index < 0 || index >= m_flex_controllers )
			return nullptr;

		return ( ( std::uint8_t* )this + m_flex_controller_index ) + index;

	}

	int	m_flex_rules;
	int	m_flex_rule_index;
	inline void* get_flex_rule( int index ) const {

		if ( index < 0 || index >= m_flex_rules )
			return nullptr;

		return ( ( std::uint8_t* )this + m_flex_rule_index ) + index;

	}

	int	m_ik_chains;
	int	m_ik_chain_index;
	inline void* get_ik_chain( int index ) const {

		if ( index < 0 || index >= m_ik_chains )
			return nullptr;

		return ( ( std::uint8_t* )this + m_ik_chain_index ) + index;

	}

	int	m_mouths;
	int	m_mouth_index;
	inline void* get_mouth( int index ) const {

		if ( index < 0 || index >= m_mouths )
			return nullptr;

		return ( ( std::uint8_t* )this + m_mouth_index ) + index;

	}

	int	m_pose_parameters;
	int	m_pose_parameter_index;
	inline void* get_pose_parameter( int index ) const {

		if ( index < 0 || index >= m_pose_parameters )
			return nullptr;

		return ( ( std::uint8_t* )this + m_pose_parameter_index ) + index;

	}

	int	m_surface_prop_index;
	inline const char* get_surface_prop( ) const {

		if ( !m_surface_prop_index )
			return nullptr;

		return ( ( char* )this ) + m_surface_prop_index;

	}

	int m_key_value_index;
	int m_key_value_size;
	inline const char* key_value_text( ) const {

		if ( !m_key_value_size )
			return nullptr;

		return ( ( char* )this ) + m_key_value_index;

	}

	int	m_ik_autoplay_locks;
	int	m_ik_autoplay_lock_index;
	inline void* get_ik_autoplay_lock( int index ) const {

		if ( index < 0 || index >= m_ik_autoplay_locks )
			return nullptr;

		return ( ( std::uint8_t* )this + m_ik_autoplay_lock_index ) + index;

	}

	float m_mass;
	int	m_contents;

	int	m_include_models;
	int	m_include_model_index;

	int	m_virtual_model;

	int	m_anim_block_name_index;
	int	m_anim_blocks;
	int	m_anim_block_index;
	int	m_animblock_model;

	int	m_bone_table_by_name_index;

	int m_vertex_base;
	int m_index_base;

	uint8_t m_directional_light_dot;
	uint8_t m_root_lod;
	uint8_t m_allowed_root_lo_ds;

	char pad0[ 0x5 ];

	int	m_flex_controller_ui;
	int	m_flexcontroller_ui_index;

	float m_vert_anim_fixed_point_scale;
	mutable int m_surface_prop_lookup;
	int	m_studio_hdr2_index;

	char pad1[ 0x4 ];
};