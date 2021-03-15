#pragma once

template < class t >
inline void destruct( t* memory ) {

	memory->~t( );

}

template < class t >
inline t* construct( t* memory ) {

	return new( memory ) t;

}

template< class t >
inline t* copy( t* memory, t const& src ) {

	return new( memory ) t( src );

}

template < class t, class a = utl_memory< t > >
struct utl_vector {

	using allocator = a;

	t& operator[]( int i ) {

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

	inline int count( ) const {

		return size;

	}

	inline int& get_size( ) {

		return size;

	}

	inline void grow_vector( int num = 1 ) {

		if ( size + num > memory.num_allocated( ) )
			memory.grow( size + num - memory.num_allocated( ) );

		size += num;

	}

	inline void shift_elements_right( int num_element, int num = 1 ) {

		int to_move = size - num_element - num;
		if ( to_move > 0 && num > 0 )
			memmove( &element( num_element + num ), &element( num_element ), to_move * sizeof( t ) );

	}

	inline void shift_elements_left( int num_element, int num = 1 ) {

		int to_move = size - num_element - num;
		if ( to_move > 0 && num > 0 )
			memmove( &element( num_element ), &element( num_element + num ), to_move * sizeof( t ) );

	}

	inline int insert_before( int num_element ) {

		grow_vector( );
		shift_elements_right( num_element );
		construct( &element( num_element ) );

		return num_element;

	}

	inline int insert_before( int num_element, const t& src ) {

		grow_vector( );
		shift_elements_right( num_element );
		copy( &element( num_element ), src );

		return num_element;

	}

	inline int add_to_tail( ) {

		return insert_before( size );

	}

	inline int add_to_tail( const t& src ) {

		return insert_before( size, src );

	}

	inline int find( const t& src ) const {

		for ( int i = 0; i < count( ); ++i ) {

			if ( element( i ) == src )
				return i;

		}

		return -1;
	}

	inline void remove( int num_element ) {

		destruct( &element( num_element ) );
		shift_elements_left( num_element );
		--size;

	}

	inline void remove_all( ) {

		for ( int i = size; --i >= 0;)
			destruct( &element( i ) );

		size = 0;

	}

	inline bool find_and_remove( const t& src ) {

		int num_element = find( src );
		if ( num_element != -1 ) {

			remove( num_element );
			return true;

		}

		return false;

	}

protected:
	allocator memory;
	int size;
	t* elements;

};
