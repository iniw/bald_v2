#pragma once

struct client_think_handle;
struct i_client_unknown;
using client_think_handle_t = client_think_handle*;

struct i_client_thinkable {

	virtual i_client_unknown*           get_i_client_unknown( ) = 0;
	virtual void					    client_think( ) = 0;
	virtual client_think_handle_t		get_think_handle( ) = 0;
	virtual void					    set_think_handle( client_think_handle_t think ) = 0;
	virtual void					    release( ) = 0;

};