#include "utils.h"

bool utils::create_thread( DWORD WINAPI function( void* ), void* parameter ) {

	HANDLE handle = CreateThread( NULL, 0, function, parameter, 0, NULL );

	if ( !handle )
		return false;

	CloseHandle( handle );

	return true;

}

std::string utils::wide_to_multi_byte( const std::wstring_view str ) {

	if ( str.empty( ) )
		return { };

	int lenght = g_winapi.wide_char_to_multi_byte( CP_UTF8, 0, str.data( ), ( int )str.size( ), 0, 0, 0, 0 );

	std::string result = std::string( lenght, 0 );

	g_winapi.wide_char_to_multi_byte( CP_UTF8, 0, str.data( ), ( int )str.size( ), &result[ 0 ], lenght, 0, 0 );

	return result;

}

std::wstring utils::multi_byte_to_wide( const std::string_view str ) {

	if ( str.empty( ) )
		return { };

	int lenght = g_winapi.multi_byte_to_wide_char( CP_UTF8, 0, str.data( ), ( int )str.size( ), nullptr, 0 );

	std::wstring result = std::wstring( lenght, 0 );

	g_winapi.multi_byte_to_wide_char( CP_UTF8, 0, str.data( ), ( int )str.size( ), &result[ 0 ], lenght );

	return result;

}