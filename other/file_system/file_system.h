#pragma once

#include <filesystem>
#include "../console/console.h"

struct file_system {

	bool setup( );

	std::string m_main_path;
	std::string m_fonts_path;
	std::string m_configs_path;

};

inline file_system g_file_system;