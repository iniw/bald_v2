#include "pattern.h"

#include <psapi.h>
#include <vector>

address pattern::find( address module_base, std::string_view pattern ) {

	auto dos_header = module_base.as< PIMAGE_DOS_HEADER >( );
	if ( dos_header->e_magic != IMAGE_DOS_SIGNATURE )
		return address( );

	auto nt_header = module_base.add( dos_header->e_lfanew ).as< PIMAGE_NT_HEADERS >( );
	if ( nt_header->Signature != IMAGE_NT_SIGNATURE )
		return address( );

	auto image_bytes = reinterpret_cast< unsigned char* >( nt_header->OptionalHeader.ImageBase );
	if ( !image_bytes )
		return address( );

	auto image_size = nt_header->OptionalHeader.SizeOfImage;
	if ( !image_size )
		return address( );

	auto pattern_bytes = pattern_to_byte( pattern.data( ) );
	auto signature_size = pattern_bytes.size( );
	auto signature_bytes = pattern_bytes.data( );

	for ( unsigned long i = 0; i < image_size - signature_size; ++i ) {

		bool byte_sequence_found = true;

		for ( unsigned long j = 0; j < signature_size; ++j ) {

			if ( image_bytes[ i + j ] != signature_bytes[ j ] && signature_bytes[ j ] != -1 ) {

				byte_sequence_found = false;

				break;

			}
		}

		if ( byte_sequence_found )
			return &image_bytes[ i ];

	}

	return address( );

}

address pattern::find( section_info section, std::string_view pattern ) {

	auto image_bytes = section.start.as< unsigned char* >( );
	if ( !image_bytes ) {

		g_console.log( log_error, "invalid image_bytes" );
		return address( );

	}

	if ( !section.size ) {

		g_console.log( log_error, "invalid size" );
		return address( );

	}

	auto pattern_bytes = pattern_to_byte( pattern );
	auto signature_size = pattern_bytes.size( );
	auto signature_bytes = pattern_bytes.data( );

	for ( unsigned long i = 0; i < section.size - signature_size; ++i ) {

		bool byte_sequence_found = true;

		for ( unsigned long j = 0; j < signature_size; ++j ) {

			if ( image_bytes[ i + j ] != signature_bytes[ j ] && signature_bytes[ j ] != -1 ) {

				byte_sequence_found = false;

				break;

			}
		}

		if ( byte_sequence_found )
			return address( &image_bytes[ i ] );

	}

	return address( );

}

bool pattern::find( address module_base, std::string_view pattern, address result ) {
	
	result = find( module_base, pattern );
	return result;

}

std::vector<size_t> pattern::pattern_to_byte( std::string_view pattern ) {

	std::vector< size_t > bytes;

	auto start = const_cast< char* >( pattern.data( ) );
	auto end = const_cast< char* >( pattern.data( ) ) + pattern.size( );

	for ( auto current = start; current < end; ++current ) {

		if ( *current == '?' ) {

			++current;

			if ( *current == '?' )
				++current;

			bytes.push_back( -1 );

		} else {

			bytes.push_back( std::strtoul( current, &current, 16 ) );

		}
	}

	return bytes;

};