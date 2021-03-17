#pragma once

#include "utl_mem/utl_mem.h"
#include "../app_system.h"

using fn_change_callback = void( __cdecl* )( void*, const char*, float );

struct color;
struct convar {

	inline const char* get_name( ) {

		return g_utils.call_v_func<const char*>( this, 5 );

	}

	inline float get_float( ) {

		uint32_t xored = *reinterpret_cast< uint32_t* >( &m_parent->m_value_f ) ^ reinterpret_cast< uint32_t >( this );
		return *reinterpret_cast< float* >( &xored );

	}

	inline int get_int( ) {

		return static_cast< int >( m_parent->m_value_i ^ reinterpret_cast< int >( this ) );

	}

	inline bool get_bool( ) {

		return !!get_int( );

	}

	inline const char* get_string( ) {

		char const* value = m_parent->m_string;
		return value ? value : "";

	}

	inline void set_value( const char* value ) {

		return g_utils.call_v_func< void >( this, 14, value );

	}

	inline void set_value( float value ) {

		return g_utils.call_v_func< void >( this, 15, value );

	}

	inline void set_value( int value ) {

		return g_utils.call_v_func< void >( this, 16, value );

	}

	char							    pad0[ 0x4 ];
	convar*                             m_next;
	bool								m_registered;
	const char*                         m_name;
	const char*                         m_help_string;
	int									m_flags;
	char							    pad1[ 0x4 ];
	convar*                             m_parent;
	const char*                         m_default_value;
	char*                               m_string;
	int									m_string_length;
	float								m_value_f;
	int									m_value_i;
	bool								m_has_min;
	float								m_min_value;
	bool								m_has_max;
	float								m_max_value;
	utl_vector< fn_change_callback >	m_change_callbacks;

};

struct con_var : public app_system {

	virtual int	            allocate_dll_identifier( ) = 0;
	virtual void			register_con_command( convar* command_base ) = 0;
	virtual void			unregister_con_command( convar* command_base ) = 0;
	virtual void			unregister_con_commands( int id ) = 0;
	virtual const char*     get_command_line_value( const char* variable_name ) = 0;
	virtual void*           find_command_base( const char* name ) = 0;
	virtual const void*     find_command_base( const char* name ) const = 0;
	virtual convar*         find_var( const char* variable_name ) = 0;
	virtual const convar*   find_var( const char* variable_name ) const = 0;
	virtual void*           find_command( const char* name ) = 0;
	virtual const void*     find_command( const char* name ) const = 0;
	virtual void			install_global_change_callback( fn_change_callback callback ) = 0;
	virtual void			remove_global_change_callback( fn_change_callback callback ) = 0;
	virtual void			call_global_change_callbacks( convar* var, const char* old_string, float old_value ) = 0;
	virtual void			install_console_display_func( void* display_func ) = 0;
	virtual void			remove_console_display_func( void* display_func ) = 0;
	virtual void			console_color_printf( const color& color, const char* format, ... ) const = 0;
	virtual void			console_printf( const char* format, ... ) const = 0;
	virtual void			console_d_printf( const char* format, ... ) const = 0;
	virtual void			revert_f_lagged_con_vars( int flag ) = 0;

};