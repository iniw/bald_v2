#pragma once

#include <cstring>
#include <assert.h>

#define md5_digest_length 16  
#define md5_bit_length ( md5_digest_length * sizeof( unsigned char ) )

typedef struct {

	unsigned int	buf[ 4 ];
	unsigned int	bits[ 2 ];
	unsigned char	in[ 64 ];

} md5_context;

struct md5_value;

struct md5 {

	void init( md5_context* context );

	void update( md5_context* context, unsigned char const* buf, unsigned int len );

	void final( unsigned char digest[ md5_digest_length ], md5_context* context );

	unsigned int pseudo_random( unsigned int nSeed );

	void process_single_buffer( const void* p, int len, md5_value& md5Result );

	void transform( unsigned int buf[ 4 ], unsigned int const in[ 16 ] );

	static bool compare( const md5_value& data, const md5_value& compare );

};

struct md5_value {

	void zero( ) {

		memset( bits, 0, sizeof( bits ) );

	};

	bool is_zero( ) const {

		for ( int i = 0; i < ( sizeof( bits ) / sizeof( bits[ 0 ] ) ); ++i ) {
			if ( bits[ i ] != 0 )
				return false;
		}

		return true;

	};

	inline bool operator==( const md5_value& src ) const {

		return md5::compare( *this, src );

	};

	inline bool operator!=( const md5_value& src ) const {

		return !md5::compare( *this, src );

	};

	unsigned char bits[ md5_digest_length ];
};

inline md5 g_md5;