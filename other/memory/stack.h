#pragma once

#include "address.h"

struct stack : address {

	stack( void* address_of_return_address ) : address( g_utils.get_ebp( address_of_return_address ) ) {



	}

	inline stack& next( ) {

		return *reinterpret_cast< stack* >( m_address );

	}

	template< typename t = address > inline t local( size_t offset ) {

		return ( t )( m_address - offset );

	}

	template< typename t = address > inline t argument( size_t offset ) {

		return ( t )( m_address + offset );

	}

	inline address return_address( ) {

		if ( !m_address )
			return address( );

		return *reinterpret_cast< size_t* >( m_address + sizeof( size_t ) );

	}

	inline address address_of_return_address( ) {

		if ( !m_address )
			return address( );

		return m_address + sizeof( size_t );

	}

};