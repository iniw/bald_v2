#pragma once
#include "../../../../other/math/math.h"

struct ray;

struct model;
struct base_handle;

struct i_handle_entity {

	virtual ~i_handle_entity( ) { }
	virtual void set_handle( const base_handle& handle ) = 0;
	virtual const base_handle& get_handle( ) const = 0;

};

struct i_client_networkable;
struct i_client_renderable;
struct i_client_entity;
struct base_entity;
struct i_client_thinkable;
struct i_client_alpha_property;
struct i_client_unknown;

struct i_collideable {

	virtual i_handle_entity*        get_entity_handle( ) = 0;
	virtual vec_3&					obb_mins( ) const = 0;
	virtual vec_3&					obb_maxs( ) const = 0;
	virtual void					world_space_trigger_bounds( vec_3* world_mins, vec_3* world_maxs ) const = 0;
	virtual bool					test_collision( const ray& ray, unsigned int contents_mask, void* tr ) = 0;
	virtual bool					test_hitboxes( const ray& ray, unsigned int contents_mask, void* tr ) = 0;
	virtual int						get_collision_model_index( ) = 0;
	virtual const model*            get_collision_model( ) = 0;
	virtual vec_3&                  get_collision_origin( ) const = 0;
	virtual q_ang&                  get_collision_angles( ) const = 0;
	virtual const matrix_3x4&       collision_to_world_transform( ) const = 0;
	virtual int				        get_solid( ) const = 0;
	virtual int						get_solid_flags( ) const = 0;
	virtual i_client_unknown*       get_i_client_unknown( ) = 0;
	virtual int						get_collision_group( ) const = 0;
	virtual void					world_space_surrounding_bounds( vec_3* mins, vec_3* maxs ) = 0;
	virtual unsigned int			get_required_trigger_flags( ) const = 0;
	virtual const matrix_3x4*       get_root_parent_to_world_transform( ) const = 0;
	virtual void*                   get_v_physics_object( ) const = 0;

};

struct i_client_unknown : public i_handle_entity {

	virtual i_collideable*           get_collideable( ) = 0;
	virtual i_client_networkable*    get_client_networkable( ) = 0;
	virtual i_client_renderable*     get_client_renderable( ) = 0;
	virtual i_client_entity*         get_client_entity( ) = 0;
	virtual base_entity*             get_base_entity( ) = 0;
	virtual i_client_thinkable*      get_client_thinkable( ) = 0;
	virtual i_client_alpha_property* get_client_alpha_property( ) = 0;

};