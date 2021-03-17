#pragma once

enum data_update_type {

	data_update_created = 0,
	data_update_datatable_changed,

};

struct client_class;

struct i_client_networkable {

	virtual i_client_unknown* get_client_unknown( ) = 0;
	virtual void              release( ) = 0;
	virtual client_class*     get_client_class( ) = 0;
	virtual void              notify_should_transmit( data_update_type state ) = 0;
	virtual void              on_pre_data_changed( data_update_type update_type ) = 0;
	virtual void              on_data_changed( data_update_type update_type ) = 0;
	virtual void              pre_data_update( data_update_type update_type ) = 0;
	virtual void              post_data_update( data_update_type update_type ) = 0;
	virtual void              on_data_unchanged_in_pvs( ) = 0;
	virtual bool              is_dormant( ) = 0;
	virtual int               get_index( ) const = 0;
	virtual void              receive_message( int class_id, void* msg ) = 0;
	virtual void*			  get_data_table_base_ptr( ) = 0;
	virtual void              set_destroyed_on_recreate_entities( ) = 0;

};