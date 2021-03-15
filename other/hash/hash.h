#pragma once

#include <cstddef>
#include <string>

struct hash {

	size_t get( std::string_view string );

	constexpr size_t const_hash( const char* string, const size_t uValue = 0x8ADF9ED5 ) noexcept {

		return ( string[ 0 ] == '\0' ) ? uValue : const_hash( &string[ 1 ], ( uValue ^ size_t( string[ 0 ] ) ) * m_prime );

	}

private:

	size_t m_basis = 0x8ADF9ED5;
	size_t m_prime = 0x60561129;

};

inline hash g_hash;