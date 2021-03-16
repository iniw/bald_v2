#pragma once

struct client_entity_list {

	inline auto get_client_entity( int entity_number ) {

		return g_utils.call_v_func< void* >( this, 3, entity_number );

	}

	inline auto get_client_entity_from_handle( size_t entity ) {

		return g_utils.call_v_func< void* >( this, 4, entity );

	}

	template< class t > inline t get( int entity_number ) {

		return ( t )get_client_entity( entity_number );

	}

	template< class t > inline t get( size_t entity ) {

		return ( t )get_client_entity_from_handle( entity );

	}

};