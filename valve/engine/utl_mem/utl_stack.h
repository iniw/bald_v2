#pragma once

#include "utl_memory.h"

template < class t, class m = utl_memory< t > >
struct utl_stack {

	inline t& operator[]( int i ) {

		return memory[ i ];

	}

	inline const t& operator[]( int i ) const {

		return memory[ i ];

	}

	inline t& element( int i ) {

		return memory[ i ];

	}

	inline const t& element( int i ) const {

		return memory[ i ];

	}

	inline t* base( ) {

		return memory.base( );

	}

	inline const t* base( ) const {

		return memory.base( );

	}

	inline t& top( ) {

		return element( size - 1 );

	}

	inline const t& top( ) const {

		return element( size - 1 );

	}

	inline int count( ) const {

		return size;

	}

private:

	m	memory;
	int	size;
	t* elements;

};