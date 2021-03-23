#include "console.h"

#include <iostream>

bool console::setup( ) {

	if ( !AllocConsole( ) )
		return false;

	freopen_s( reinterpret_cast< _iobuf** >( stdin ), XOR( "CONIN$" ), XOR( "r" ), stdin );
	freopen_s( reinterpret_cast< _iobuf** >( stdout ), XOR( "CONOUT$" ), XOR( "w" ), stdout );
	freopen_s( reinterpret_cast< _iobuf** >( stderr ), XOR( "CONOUT$" ), XOR( "w" ), stderr );

	m_handle = GetStdHandle( STD_OUTPUT_HANDLE );

	bool result = SetConsoleTitleA( XOR( "bald_v2" ) );

	std::memset( m_buffer, '\0', sizeof( m_buffer ) );

	m_file.open( XOR( "bald_logs.txt" ), std::ios::out | std::ios::trunc );

	return result;
}

void console::unload( ) {

	fclose( static_cast< _iobuf* >( stdin ) );
	fclose( static_cast< _iobuf* >( stdout ) );
	fclose( static_cast< _iobuf* >( stderr ) );

	FreeConsole( );

	m_file.close( );

}

void console::log( int type, std::string_view format, ... ) {

	if ( std::strlen( format.data( ) ) >= sizeof( m_buffer ) )
		return;

	if ( type < log_normal || type > log_max - 1 )
		return;

	va_list arguments;

	va_start( arguments, format );

	vsprintf_s( m_buffer, format.data( ), arguments );

	SetConsoleTextAttribute( m_handle, m_type_lookup[ type ] );

	if ( type == log_warning || type == log_error ) 
		m_file << m_buffer << std::endl;

	std::printf( XOR( "%s \n" ), m_buffer );

	// clear the buffer for the next call
	std::memset( m_buffer, '\0', sizeof( m_buffer ) );

	va_end( arguments );

}
