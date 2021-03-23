#pragma once

#include <filesystem>
#include "../console/console.h"

struct file_system {

	char m_main_path[ MAX_PATH + 1 ];
	char m_fonts_path[ MAX_PATH + 1 ];
	char m_configs_path[ MAX_PATH + 1 ];
	char m_logs_path[ MAX_PATH + 1 ];

	bool setup( );

};

inline file_system g_file_system;