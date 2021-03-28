#include "utils.h"

#include <sstream>
#include <iomanip>
#include "../pattern/pattern.h"

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

std::string_view utils::format_text( std::string_view format, ... ) {

	if ( std::strlen( format.data( ) ) >= sizeof( m_buffer ) )
		return std::string_view( );

	va_list arguments;

	va_start( arguments, format );

	std::memset( m_buffer, '\0', sizeof( m_buffer ) );
	vsprintf_s( m_buffer, format.data( ), arguments );

	va_end( arguments );

	return m_buffer;

}

address utils::get_v_table( address module_base, std::string_view name ) {

	std::string type_descriptor_name = XOR( ".?AV" ) + std::string( name ) + XOR( "@@" );

	std::string pattern = bytes_to_pattern( reinterpret_cast< byte* >( type_descriptor_name.data( ) ), type_descriptor_name.size( ) );

	address rtti_type_descriptor = g_pattern.find( module_base, pattern );
	if ( !rtti_type_descriptor )
		return address( );

	rtti_type_descriptor = rtti_type_descriptor.sub( 0x8 );

	section_info section_rdata = get_section_info( module_base, XOR( ".rdata" ) );
	if ( !section_rdata )
		return address( );

	const auto xrefs = get_xrefs( rtti_type_descriptor, section_rdata );

	for ( const auto& xref : xrefs ) {

		const int offset_from_class =  xref.sub( 0x8 ).to< int >( );
		if ( offset_from_class != 0 )
			continue;
			
		address object_locator = xref.sub( 0xC );

		pattern = bytes_to_pattern( reinterpret_cast< byte* >( &object_locator ) );

		address vtable_address = g_pattern.find( section_rdata, pattern.data( ) ).add( 0x4 );
		if ( vtable_address.as< size_t >( ) <= 4 ) 
			return address( );

		section_info section_text = get_section_info( module_base, XOR( ".text" ) );
		if ( !section_text )
			return address( );

		pattern = bytes_to_pattern( reinterpret_cast< byte* >( &vtable_address ) );

		return g_pattern.find( section_text, pattern.data( ) );

	}

	return address( );

}

inline std::string utils::bytes_to_pattern( byte* bytes, size_t size ) {

	std::stringstream ida_pattern;
	ida_pattern << std::hex << std::setfill( '0' );

	for ( size_t i = 0; i < size; i++ ) {

		const int current_byte = bytes[ i ];

		if ( current_byte != 255 )
			ida_pattern << std::setw( 2 ) << current_byte;
		else
			ida_pattern << std::setw( 1 ) << XOR( "?" );

		if ( i != size - 1 )
			ida_pattern << XOR( " " );

	}

	return ida_pattern.str( );

}

inline std::vector< address > utils::get_xrefs( address module_base, section_info info ) {

	std::vector< address > xrefs;

	const std::string ida_pattern = bytes_to_pattern( reinterpret_cast< byte* >( &module_base ) );

	const size_t end = info.start.add( info.size );

	while ( info.start && info.start < end ) {

		address xref = g_pattern.find( info, ida_pattern );
		if ( !xref )
			break;

		xrefs.push_back( xref );
		info.start = xref.add( 0x4 );

	}

	return xrefs;

}

inline section_info utils::get_section_info( address module_base, std::string_view section_name ) {

	const PIMAGE_DOS_HEADER dos_header = module_base.as< PIMAGE_DOS_HEADER >( );
	if ( dos_header->e_magic != IMAGE_DOS_SIGNATURE )
		return section_info( );

	const PIMAGE_NT_HEADERS32 nt_headers = module_base.add( dos_header->e_lfanew ).as< PIMAGE_NT_HEADERS32 >( );
	if ( nt_headers->Signature != IMAGE_NT_SIGNATURE )
		return section_info( );

	PIMAGE_SECTION_HEADER section_header = IMAGE_FIRST_SECTION( nt_headers );
	uint16_t number_of_sections = nt_headers->FileHeader.NumberOfSections;

	const size_t hash = g_hash.get( section_name );

	while ( number_of_sections > 0 ) {

		if ( g_hash.get( reinterpret_cast< const char* >( section_header->Name ) ) == hash ) 
			return section_info( module_base.add( section_header->VirtualAddress ), section_header->SizeOfRawData );

		section_header++;
		number_of_sections--;

	}

	return section_info( );

}
