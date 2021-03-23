#pragma once

#include <windows.h>
#include <string>
#include <fstream>

#include "../xor/xor.h"

#define FOREGROUND_WHITE	( FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN )
#define FOREGROUND_MAGENTA	( FOREGROUND_RED | FOREGROUND_BLUE )
#define FOREGROUND_YELLOW   ( FOREGROUND_RED | FOREGROUND_GREEN )
#define FOREGROUND_CYAN		( FOREGROUND_BLUE | FOREGROUND_GREEN )
#define FOREGROUND_BLACK	0

enum log_types {

	log_normal     = 0,
	log_completion = 1,
	log_warning    = 2,
	log_error      = 3,
	log_max		   = 4

};

struct console {

	bool setup( );

	void unload( );

	void log( int type, std::string_view format, ... );

private:

	HANDLE m_handle;

	std::ofstream m_file;

	char m_buffer[ 256 ];

	int m_type_lookup[ log_max ] = { FOREGROUND_WHITE, FOREGROUND_CYAN, FOREGROUND_YELLOW, FOREGROUND_RED };

};

inline console g_console;