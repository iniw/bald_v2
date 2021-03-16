#pragma once

#include <windows.h>
#include <thread>
#include <cstddef>

#include "../memory/address.h"

struct utils {

	bool create_thread( DWORD WINAPI function( void* ), void* parameter );

	inline void sleep( size_t milliseconds ) {

		std::this_thread::sleep_for( std::chrono::milliseconds( milliseconds ) );

	}

	inline size_t get_ebp( void* address_of_return_address ) {

		return reinterpret_cast< size_t >( address_of_return_address ) - sizeof( size_t );

	}

	template< typename t = address > inline t get_v_func( address pointer, size_t idx ) {

		return ( t )( pointer.to< t* >( )[ idx ] );

	}

	template< typename t, typename ... args_t > constexpr inline t call_v_func( address pointer, size_t idx, args_t... args_list ) {

		using fn = t( __thiscall* )( void*, decltype( args_list )... );
		return pointer.to< fn* >( )[ idx ]( pointer, args_list... );

	}

};

inline utils g_utils;