#pragma once

#include "base_attributable_item.h"

enum class weapon_type {

	knife = 0,
	pistol = 1,
	submachinegun = 2,
	rifle = 3,
	shotgun = 4,
	sniper = 5,
	machinegun = 6,
	c4 = 7,
	placeholder = 8,
	grenade = 9,
	healthshot = 11,
	fists = 12,
	breachcharge = 13,
	bumpmine = 14,
	tablet = 15,
	melee = 16

};

struct cs_weapon_info {

	byte	    pad0[ 0x14 ];				
	int			m_max_clip1;				
	int			m_max_clip2;				
	int			m_default_clip1;			
	int			m_default_clip2;			
	int			m_primary_max_reserve_ammo; 
	int			m_secondary_max_reserve_ammo;
	char*       m_world_model;		
	char*       m_view_model;		
	char*       m_dropped_model;	
	byte	    pad1[ 0x50 ];		
	char*       m_hud_name;			
	char*       m_weapon_name;		
	byte	    pad2[ 0x2 ];		
	bool		m_is_melee_weapon;	
	byte	    pad3[ 0x9 ];		
	float		m_weapon_weight;	
	byte	    pad4[ 0x28 ];		
	int			m_weapon_type;		
	byte	    pad5[ 0x4 ];		
	int			m_weapon_price;		
	int			m_kill_award;		
	byte	    pad6[ 0x4 ];		
	float		m_cycle_time;		
	float		m_cycle_time_alt;	
	byte	    pad7[ 0x8 ];		
	bool		m_full_auto;		
	byte	    pad8[ 0x3 ];		
	int			m_damage;			
	float		m_armor_ratio;		
	int			m_bullets;			
	float		m_penetration;		
	byte	    pad9[ 0x8 ];		
	float		m_range;			
	float		m_range_modifier;	
	float		m_throw_velocity;	
	byte	    pad10[ 0xC ];		
	bool		b_has_silencer;		
	byte	    pad11[ 0xB ];		
	char*       m_bullet_type;		
	float		m_max_speed;		
	float		m_max_speed_alt;	
	float		m_spread;			
	float		m_spread_alt;		
	byte	    pad12[ 0x44 ];		
	int			m_recoil_seed;		
	byte	    pad13[ 0x20 ];		

};

struct weapon_cs_base : public base_attributable_item {

	inline auto get_max_speed( ) {

		return g_utils.call_v_func< float >( this, 441 );

	}

	inline auto get_cs_wpn_data( ) {

		return g_utils.call_v_func< cs_weapon_info* >( this, 460 ); // 8B 81 ? ? ? ? 85 C0 0F 84 ? ? ? ? C3

	}

	inline auto& is_burst_mode( ) {

		static auto offset = g_netvars.m_offsets[ g_hash.get( XOR( "DT_WeaponCSBase->m_bBurstMode" ) ) ];

		return *reinterpret_cast< bool* >( reinterpret_cast< size_t >( this ) + offset );

	}

	inline auto& get_burst_shots_remaining( ) {

		static auto offset = g_netvars.m_offsets[ g_hash.get( XOR( "DT_WeaponCSBaseGun->m_iBurstShotsRemaining" ) ) ];

		return *reinterpret_cast< int* >( reinterpret_cast< size_t >( this ) + offset );

	}

	inline auto& get_ammo( ) {

		static auto offset = g_netvars.m_offsets[ g_hash.get( XOR( "DT_BaseCombatWeapon->m_iClip1" ) ) ];

		return *reinterpret_cast< int* >( reinterpret_cast< size_t >( this ) + offset );

	}

	inline auto& get_next_primary_attack( ) {

		static auto offset = g_netvars.m_offsets[ g_hash.get( XOR( "DT_BaseCombatWeapon->m_flNextPrimaryAttack" ) ) ];

		return *reinterpret_cast< float* >( reinterpret_cast< size_t >( this ) + offset );

	}

};