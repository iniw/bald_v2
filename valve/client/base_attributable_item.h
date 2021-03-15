#pragma once

#include "base_entity.h"

enum class definition_index {

	none = 0,
	deagle = 1,
	elite = 2,
	fiveseven = 3,
	glock = 4,
	ak47 = 7,
	aug = 8,
	awp = 9,
	famas = 10,
	g3sg1 = 11,
	galilar = 13,
	m249 = 14,
	m4a1 = 16,
	mac10 = 17,
	p90 = 19,
	zone_repulsor = 20,
	mp5sd = 23,
	ump45 = 24,
	xm1014 = 25,
	bizon = 26,
	mag7 = 27,
	negev = 28,
	sawedoff = 29,
	tec9 = 30,
	taser = 31,
	hkp2000 = 32,
	mp7 = 33,
	mp9 = 34,
	nova = 35,
	p250 = 36,
	shield = 37,
	scar20 = 38,
	sg556 = 39,
	ssg08 = 40,
	knife_gg = 41,
	knife = 42,
	flashbang = 43,
	hegrenade = 44,
	smokegrenade = 45,
	molotov = 46,
	decoy = 47,
	incgrenade = 48,
	c4 = 49,
	healthshot = 57,
	knife_t = 59,
	m4a1_silencer = 60,
	usp_silencer = 61,
	cz75a = 63,
	revolver = 64,
	tagrenade = 68,
	fists = 69,
	breachcharge = 70,
	tablet = 72,
	melee = 74,
	axe = 75,
	hammer = 76,
	spanner = 78,
	knife_ghost = 80,
	firebomb = 81,
	diversion = 82,
	frag_grenade = 83,
	snowball = 84,
	bumpmine = 85,
	knife_bayonet = 500,
	knife_css = 503,
	knife_flip = 505,
	knife_gut = 506,
	knife_karambit = 507,
	knife_m9_bayonet = 508,
	knife_tactical = 509,
	knife_falchion = 512,
	knife_survival_bowie = 514,
	knife_butterfly = 515,
	knife_push = 516,
	knife_cord = 517,
	knife_canis = 518,
	knife_ursus = 519,
	knife_gypsy_jackknife = 520,
	knife_outdoor = 521,
	knifeStiletto = 522,
	knife_widowmaker = 523,
	knife_skeleton = 525,
	glove_studded_bloodhound = 5027,
	glove_t = 5028,
	glove_ct = 5029,
	glove_sporty = 5030,
	glove_slick = 5031,
	glove_leather_handwraps = 5032,
	glove_motorcycle = 5033,
	glove_specialist = 5034,
	glove_hydra = 5035

};

struct base_attributable_item : base_entity {

	inline auto& get_item_definition_index( ) {

		static auto offset = g_netvars.m_offsets[ g_hash.get( "DT_BaseAttributableItem->m_iItemDefinitionIndex" ) ];

		return *reinterpret_cast< short* >( reinterpret_cast< std::size_t >( this ) + offset );

	}

	inline auto& get_item_id_high( ) {

		static auto offset = g_netvars.m_offsets[ g_hash.get( "DT_BaseAttributableItem->m_iItemIDHigh" ) ];

		return *reinterpret_cast< int* >( reinterpret_cast< std::size_t >( this ) + offset );

	}

	inline auto& get_item_id_low( ) {

		static auto offset = g_netvars.m_offsets[ g_hash.get( "DT_BaseAttributableItem->m_iItemIDLow" ) ];

		return *reinterpret_cast< int* >( reinterpret_cast< std::size_t >( this ) + offset );

	}

	inline auto& get_entity_quality( ) {

		static auto offset = g_netvars.m_offsets[ g_hash.get( "DT_BaseAttributableItem->m_iEntityQuality" ) ];

		return *reinterpret_cast< int* >( reinterpret_cast< std::size_t >( this ) + offset );

	}

	inline auto& get_custom_name( ) {

		static auto offset = g_netvars.m_offsets[ g_hash.get( "DT_BaseAttributableItem->m_szCustomName" ) ];

		return *reinterpret_cast< char* >( reinterpret_cast< std::size_t >( this ) + offset );

	}

	inline auto& get_fallback_paint_kit( ) {

		static auto offset = g_netvars.m_offsets[ g_hash.get( "DT_BaseAttributableItem->m_nFallbackPaintKit" ) ];

		return *reinterpret_cast< int* >( reinterpret_cast< std::size_t >( this ) + offset );

	}

	inline auto& get_fallback_seed( ) {

		static auto offset = g_netvars.m_offsets[ g_hash.get( "DT_BaseAttributableItem->m_nFallbackSeed" ) ];

		return *reinterpret_cast< int* >( reinterpret_cast< std::size_t >( this ) + offset );

	}

	inline auto& get_fallback_wear( ) {

		static auto offset = g_netvars.m_offsets[ g_hash.get( "DT_BaseAttributableItem->m_flFallbackWear" ) ];

		return *reinterpret_cast< float* >( reinterpret_cast< std::size_t >( this ) + offset );

	}

	inline auto& get_fallback_stat_trak( ) {

		static auto offset = g_netvars.m_offsets[ g_hash.get( "DT_BaseAttributableItem->m_nFallbackStatTrak" ) ];

		return *reinterpret_cast< int* >( reinterpret_cast< std::size_t >( this ) + offset );

	}

};