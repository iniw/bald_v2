#pragma once

#include <windows.h>
#include <thread>
#include <cstddef>

#include "../memory/address.h"
#include "../winapi/winapi.h"

struct section_info {

	section_info( ) : size( 0 ) { }

	section_info( size_t start, size_t size ) : start( start ), size( size ) { }

	inline operator bool( ) {

		return start && size;

	}

	address start;
	size_t size;

};

struct utils {

	bool create_thread( DWORD WINAPI function( void* ), void* parameter );

	std::string wide_to_multi_byte( const std::wstring_view str );

	std::wstring multi_byte_to_wide( const std::string_view str );

	std::string_view format_text( std::string_view format, ... );

	address get_v_table( address module_base, std::string_view name );

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

private:

	inline std::string bytes_to_pattern( byte* bytes, size_t size = 4 );

	inline std::vector< address > get_xrefs( address module_base, section_info info );

	inline section_info get_section_info( address module_base, std::string_view section_name );

	char m_buffer[ 256 ];

};

inline utils g_utils;