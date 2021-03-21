#include "hash.h"

size_t hash::get( std::string_view string ) {

    size_t ret = m_basis;

    size_t length = string.size( );
    for ( size_t i = 0; i < length; ++i ) {

        ret ^= string[ i ];
        ret *= m_prime;

    }

    return ret;

}