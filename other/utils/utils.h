#pragma once

#include <windows.h>
#include <thread>
#include <cstddef>

#include "../memory/address.h"
#include "../winapi/winapi.h"

struct utils {

	bool create_thread( DWORD WINAPI function( void* ), void* parameter );

	inline std::string wide_to_multi_byte( const std::wstring_view str ) {

		if ( str.empty( ) )
			return { };

		std::string result;
		int lenght;

		lenght = g_winapi.wide_char_to_multi_byte( CP_UTF8, 0, str.data( ), ( int )str.size( ), 0, 0, 0, 0 );

		result = std::string( lenght, 0 );

		g_winapi.wide_char_to_multi_byte( CP_UTF8, 0, str.data( ), ( int )str.size( ), &result[ 0 ], lenght, 0, 0 );

		return result;

	}

	inline std::wstring multi_byte_to_wide( const std::string_view str ) {

		if ( str.empty( ) )
			return { };

		std::wstring result;
		int lenght;
		lenght = g_winapi.multi_byte_to_wide_char( CP_UTF8, 0, str.data( ), ( int )str.size( ), nullptr, 0 );

		result = std::wstring( lenght, 0 );

		g_winapi.multi_byte_to_wide_char( CP_UTF8, 0, str.data( ), ( int )str.size( ), &result[ 0 ], lenght );

		return result;
	}

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