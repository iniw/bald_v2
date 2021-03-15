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
	
	/*
	virtual void		set_dmg_mod_bullet( float flDmgMod ) = 0;
	virtual void		set_dmg_mod_club( float flDmgMod ) = 0;
	virtual void		set_dmg_mod_explosive( float flDmgMod ) = 0;
	virtual float		get_dmg_mod_bullet( ) = 0;
	virtual float		get_dmg_mod_club( ) = 0;
	virtual float		get_dmg_mod_explosive( ) = 0;
	virtual float		get_dmg_mod_fire( ) = 0;

	virtual void		set_explosive_radius( float flRadius ) = 0;
	virtual void		set_explosive_damage( float flDamage ) = 0;
	virtual float		get_explosive_radius( ) = 0;
	virtual float		get_explosive_damage( ) = 0;

	virtual void		set_physics_damage_table( void* iszTableName ) = 0;
	virtual void*		get_physics_damage_table( ) = 0;

	virtual void		set_breakable_model( void* iszModel ) = 0;
	virtual void*		get_breakable_model( ) = 0;
	virtual void		set_breakable_skin( int iSkin ) = 0;
	virtual int			get_breakable_skin( ) = 0;
	virtual void		set_breakable_count( int iCount ) = 0;
	virtual int			get_breakable_count( ) = 0;
	virtual void		set_max_breakable_size( int iSize ) = 0;
	virtual int			get_max_breakable_size( ) = 0;

	virtual void		set_prop_data_blocks_los( bool bBlocksLOS ) = 0;
	virtual void		set_prop_data_is_ai_walkable( bool bBlocksLOS ) = 0;

	virtual void		set_interaction( int Interaction ) = 0;
	virtual bool		has_interaction( int Interaction ) = 0;

	virtual void		set_physics_mode( int iMode ) = 0;
	virtual int			get_physics_mode( ) = 0;

	virtual void		set_multiplayer_break_mode( int mode ) = 0;
	virtual int			get_multiplayer_break_mode( ) const = 0;

	virtual void		set_base_prop_data( void* iszBase ) = 0;
	virtual void*		get_base_prop_data( ) = 0;
	*/
};
