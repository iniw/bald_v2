#pragma once

struct bf_write {

	bf_write( ) = default;
	unsigned long*  m_data;
	int				m_data_bytes;
	int				m_data_bits;
	int				m_current_bit;

};

struct bf_read {

	uintptr_t m_base_address;
	uintptr_t m_current_offset;

	bf_read( uintptr_t address ) : m_base_address( address ), m_current_offset( 0U ) { }

	inline void set_offset( uintptr_t offset ) {

		m_current_offset = offset;

	}

	inline void skip( uintptr_t length ) {

		m_current_offset += length;

	}

	inline int read_byte( ) {

		char value = *reinterpret_cast< char* >( m_base_address + m_current_offset );
		++m_current_offset;
		return value;

	}

	inline bool read_bool( ) {

		bool bValue = *reinterpret_cast< bool* >( m_base_address + m_current_offset );
		++m_current_offset;
		return bValue;

	}

	inline const char* read_string( ) {

		char buffer[ 256 ];
		char length = *reinterpret_cast< char* >( m_base_address + m_current_offset );

		++m_current_offset;

		std::memcpy( buffer, reinterpret_cast< void* >( m_base_address + m_current_offset ), length > 255 ? 255 : length );

		buffer[ length > 255 ? 255 : length ] = '\0';

		m_current_offset += length + 1;

		return buffer;

	}

};