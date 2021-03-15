#pragma once

#include <windows.h>
#include <thread>
#include <cstddef>

#include "../memory/address.h"

struct utils {

	bool create_thread( DWORD WINAPI function( void* ), void* parameter );

	inline void sleep( std::size_t milliseconds ) {

		std::this_thread::sleep_for( std::chrono::milliseconds( milliseconds ) );

	}

	inline std::size_t get_ebp( void* address_of_return_address ) {

		return reinterpret_cast< std::size_t >( address_of_return_address ) - sizeof( std::size_t );

	}

	template< typename t = address > inline t get_v_func( address pointer, std::size_t index ) {

		return ( t )( pointer.to< t* >( )[ index ] );

	}

	template< typename t = address, typename ... args_t > constexpr inline t call_v_func( address pointer, std::size_t index, args_t... args_list ) {

		using fn = t( __thiscall* )( void*, decltype( args_list )... );
		return pointer.to< fn* >( )[ index ]( pointer, args_list... );

	}

};

inline utils g_utils;