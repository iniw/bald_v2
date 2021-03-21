#include "console.h"

#include <iostream>

bool console::setup( ) {

	if ( !AllocConsole( ) )
		return false;

	freopen_s( reinterpret_cast< _iobuf** >( stdin ), XOR( "CONIN$" ), XOR( "r" ), stdin );
	freopen_s( reinterpret_cast< _iobuf** >( stdout ), XOR( "CONOUT$" ), XOR( "w" ), stdout );
	freopen_s( reinterpret_cast< _iobuf** >( stderr ), XOR( "CONOUT$" ), XOR( "w" ), stderr );

	m_handle = GetStdHandle( STD_OUTPUT_HANDLE );

	return SetConsoleTitleA( XOR( "bald_v2" ) );

}

void console::unload( ) {

	fclose( static_cast< _iobuf* >( stdin ) );
	fclose( static_cast< _iobuf* >( stdout ) );
	fclose( static_cast< _iobuf* >( stderr ) );

	FreeConsole( );

}

void console::log( std::string_view format, ... ) {

	if ( std::strlen( format.data( ) ) >= sizeof( m_buffer ) )
		return;

	va_list arguments;

	va_start( arguments, format );

	std::memset( m_buffer, '\0', sizeof( m_buffer ) );
	vsprintf_s( m_buffer, format.data( ), arguments );

	SetConsoleTextAttribute( m_handle, 7 );

	// pretty ugly !
	std::printf( XOR( "%s \n" ), m_buffer );

	va_end( arguments );

}