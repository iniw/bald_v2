#pragma once

#include <cstddef>

inline int utl_memory_calc_new_allocation_count( int allocation_count, int grow_size, int new_size, int bytes_item ) {

	if ( grow_size )
		allocation_count = ( ( 1 + ( ( new_size - 1 ) / grow_size ) ) * grow_size );

	else {

		if ( !allocation_count )
			allocation_count = ( 31 + bytes_item ) / bytes_item;

		while ( allocation_count < new_size )
			allocation_count *= 2;

	}

	return allocation_count;

}

template <class t, class n = int>
struct utl_memory {

	inline t& operator[]( n i ) {

		return memory[ i ];

	}

	inline const t& operator[]( n i ) const {

		return memory[ i ];

	}

	inline t* base( ) {

		return memory;

	}

	inline int num_allocated( ) const {

		return allocation_count;

	}

	inline void grow( int num = 1 ) {

		if ( is_externally_allocated( ) )
			return;

		int old_allocation_count = allocation_count;
		int allocation_requested = allocation_count + num;
		int new_allocation_count = utl_memory_calc_new_allocation_count( allocation_count, grow_size, allocation_requested, sizeof( t ) );

		if ( static_cast< int >( static_cast< n >( new_allocation_count ) ) < allocation_requested ) {

			if ( static_cast< int >( static_cast< n >( new_allocation_count ) ) == 0 && static_cast< int >( static_cast< n >( new_allocation_count - 1 ) ) >= allocation_requested )
				--new_allocation_count;

			else {

				if ( static_cast< int >( static_cast< n >( allocation_requested ) ) != allocation_requested )
					return;

				while ( static_cast< int >( static_cast< n >( new_allocation_count ) ) < allocation_requested )
					new_allocation_count = ( new_allocation_count + allocation_requested ) / 2;

			}

		}

		allocation_count = new_allocation_count;

		if ( memory != nullptr ) {

			char* data = new char[ allocation_count * sizeof( t ) ];
			memcpy( data, memory, allocation_count * sizeof( t ) );
			memory = reinterpret_cast< t* >( data );

		} else
			memory = reinterpret_cast< t* >( new std::byte[ allocation_count * sizeof( t ) ] );

	}

	inline bool is_externally_allocated( ) const {

		return grow_size < 0;

	}

protected:
	t* memory;
	int allocation_count;
	int grow_size;

};