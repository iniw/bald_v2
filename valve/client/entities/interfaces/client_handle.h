#pragma once

#include "client_unknown.h"

#define NUM_ENT_ENTRY_BITS         ( 11 + 2 )
#define NUM_ENT_ENTRIES            ( 1 << NUM_ENT_ENTRY_BITS )
#define INVALID_EHANDLE_INDEX      0xFFFFFFFF
#define NUM_SERIAL_NUM_BITS        16
#define NUM_SERIAL_NUM_SHIFT_BITS  ( 32 - NUM_SERIAL_NUM_BITS )
#define ENT_ENTRY_MASK             ( ( 1 << NUM_SERIAL_NUM_BITS ) - 1)

struct base_handle {

	base_handle( ) {

		idx = INVALID_EHANDLE_INDEX;

	}

	base_handle( const base_handle& other ) {

		idx = other.idx;

	}

	base_handle( unsigned long value ) {

		idx = value;

	}

	base_handle( int entry, int serial_number ) {

		init( entry, serial_number );

	}

	void init( int entry, int serial_number ) {

		idx = static_cast< unsigned long >( entry | ( serial_number << NUM_SERIAL_NUM_SHIFT_BITS ) );

	}

	void term( ) {

		idx = INVALID_EHANDLE_INDEX;

	}

	bool is_valid( ) const {

		return idx != INVALID_EHANDLE_INDEX;

	}

	int get_entry_index( ) const {

		if ( !is_valid( ) )
			return NUM_ENT_ENTRIES - 1;

		return idx & ENT_ENTRY_MASK;

	}
	int get_serial_number( ) const {

		return idx >> NUM_SERIAL_NUM_SHIFT_BITS;

	}

	int to_int( ) const {

		static_cast< int >( idx );

	}

	bool operator !=( const base_handle& other ) const {

		return idx != other.idx;

	}

	bool operator ==( const base_handle& other ) const {

		return idx == other.idx;

	}

	bool operator ==( const i_handle_entity* ent ) const {

		return get( ) == ent;

	}

	bool operator !=( const i_handle_entity* ent ) const {

		return get( ) != ent;

	}

	bool operator <( const base_handle& other ) const {

		return idx < other.idx;

	}

	bool operator <( const i_handle_entity* ent ) const {

		unsigned long otherIndex = ( ent ) ? ent->get_handle( ).idx : INVALID_EHANDLE_INDEX;
		return idx < otherIndex;

	}

	const base_handle& operator=( const i_handle_entity* entity ) {

		return set( entity );

	}

	const base_handle& set( const i_handle_entity* entity ) {

		if ( entity )
			*this = entity->get_handle( );
		else
			idx = INVALID_EHANDLE_INDEX;

		return *this;

	}

	i_handle_entity* get( ) const;

protected:
	unsigned long idx;

};

template< class t >
struct client_handle : public base_handle {

	client_handle( ) { };
	client_handle( int entry, int serial_number ) {

		init( entry, serial_number );

	}

	client_handle( const base_handle& handle ) : base_handle( handle ) { };

	client_handle( t* val ) {

		term( );
		set( obj );

	}

	static client_handle< t > from_index( int index ) {

		client_handle< t > ret;
		ret.idx = index;
		return ret;

	}

	t* get( ) const {

		return reinterpret_cast< t* >( base_handle::get( ) );

	}
	void set( const t* val ) {

		base_handle::set( reinterpret_cast< const i_handle_entity* >( val ) );

	}

	operator t* ( ) {

		return get( );

	}
	operator t* ( ) const {

		return get( );

	}

	bool operator!( ) const {

		return !get( );

	}

	bool operator==( t* val ) const {

		return get( ) == val;

	}

	bool operator!=( t* val ) const {

		return get( ) != val;

	}
	const base_handle& operator=( const t* val ) {

		set( val );
		return *this;

	}

	t* operator->( ) const {

		return get( );

	}

};