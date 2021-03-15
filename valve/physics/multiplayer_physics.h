#pragma once

struct multiplayer_physics {

	inline auto get_multiplayer_physics_mode( ) {

		return g_utils.call_v_func< int >( this, 0 );

	}

};

struct breakable_with_prop_data {
	
	inline auto get_dmg_mod_bullet( ) {

		return g_utils.call_v_func< float >( this, 3 );

	}
	
};
