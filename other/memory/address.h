#pragma once

#include <intrin.h>

struct address {

	address( ) : m_address{ } {



	}

	address( size_t address ) : m_address{ address } {



	}

	address( void* address ) : m_address{ reinterpret_cast< size_t >( address ) } {



	}

	inline operator size_t( ) {

		return m_address;

	}

	inline operator void* ( ) {

		return reinterpret_cast< void* >( m_address );

	}


	inline bool operator==( address address ) {

		return as< size_t >( ) == address.as< size_t >( );

	}

	inline bool operator!=( address address ) {

		return as< size_t >( ) != address.as< size_t >( );

	}

	template< typename t = address > inline t to( ) {

		return *( t* )m_address;

	}

	template< typename t = address > inline t as( ) {

		return m_address ? ( t )m_address : t( );

	}

	template< typename t = address > inline t at( size_t offset ) {

		return m_address ? *( t* )( m_address + offset ) : t( );

	}

	template< typename t = address > inline t add( size_t offset ) {

		return m_address ? ( t )( m_address + offset ) : t( );

	}

	template< typename t = address > inline t sub( size_t offset ) {

		return m_address ? ( t )( m_address - offset ) : t( );

	}

	template< typename t = address > inline t get( size_t dereferences = 1 ) {

		if ( !m_address )
			return t( );

		size_t object = m_address;

		while ( dereferences-- )
			if ( object )
				object = *reinterpret_cast< size_t* >( object );

		return ( t )object;

	}

	template< typename t = size_t > inline void set( const t& value ) {

		if ( !m_address )
			return;

		*( t* )m_address = value;

	}

	template< typename t = address > inline t absolute( size_t offset = 0x1 ) {

		if ( !m_address )
			return t( );

		size_t new_address = m_address + offset;

		// boris will gutter stomp you

		std::int32_t relative_offset = *reinterpret_cast< std::int32_t* >( new_address );

		if ( !relative_offset )
			return t( );

		return ( t )( new_address + sizeof( size_t ) + relative_offset );

	}

protected:

	size_t m_address;

};