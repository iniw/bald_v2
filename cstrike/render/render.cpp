#include "render.h"

#include <filesystem>

bool render::setup( ) {

	if ( !download_font( XOR( "https://drive.google.com/uc?export=download&id=1Z-Ft-FYkOP4Q93dujBhr7V8rIJ_Fwzbw" ), XOR( "04b03.ttf" ) ) )
		return false;

	if ( !download_font( XOR( "https://drive.google.com/uc?export=download&id=147HCXZljiUg2vRa7jza9kNGx31KTY6Ww" ), XOR( "04b25.ttf" ) ) )
		return false;

	create_font( m_fonts.primary, XOR( "Verdana" ), 12, 500,  fontflag_dropshadow );

	create_font( m_fonts.secondary, XOR( "04b03" ), 8, 500, fontflag_outline );

	create_font( m_fonts.tertiary, XOR( "04b25" ), 12, 500, fontflag_outline );	

	g_interfaces.m_surface->get_screen_size( m_screen.w, m_screen.h );

	g_console.log( log_completion, XOR( "setup renderer" ) );

	return true;

}

void render::draw_line( int x0, int y0, int x1, int y1, const color& color ) {

	g_interfaces.m_surface->draw_set_color( color.r, color.g, color.b, color.a );

	g_interfaces.m_surface->draw_line( x0, y0, x1, y1 );

}

void render::draw_filled_rect( int x, int y, int width, int height, const color& color, int flags ) {

	g_interfaces.m_surface->draw_set_color( color.r, color.g, color.b, color.a );

	handle_flags( x, y, width, height, flags );

	g_interfaces.m_surface->draw_filled_rect( x, y, x + width, y + height );

}

void render::draw_outlined_rect( int x, int y, int width, int height, const color& color, int flags ) {

	g_interfaces.m_surface->draw_set_color( color.r, color.g, color.b, color.a );

	handle_flags( x, y, width, height, flags );

	g_interfaces.m_surface->draw_outlined_rect( x, y, x + width, y + height );

}

void render::draw_text( h_font& font, int x, int y, std::wstring_view text, const color& color, int flags ) {

	int width, height;
	g_interfaces.m_surface->get_text_size( font, text.data( ), width, height );

	handle_flags( x, y, width, height, flags );

	g_interfaces.m_surface->draw_set_text_color( color.r, color.g, color.b, color.a );
	g_interfaces.m_surface->draw_set_text_font( font );
	g_interfaces.m_surface->draw_set_text_pos( x, y );
	g_interfaces.m_surface->draw_print_text( text.data( ), text.size( ) );

}

void render::draw_text( h_font& font, int x, int y, std::string_view text, const color& color, int flags ) {

	draw_text( font, x, y, g_utils.multi_byte_to_wide( text ), color, flags );

}

void render::create_font( h_font& font, std::string_view name, int tall, int weight, int flags ) {

	font = g_interfaces.m_surface->create_font( );
		
	g_interfaces.m_surface->set_font_glyph( font, name.data( ), tall, weight, 0, 0, flags );

}

bool render::download_font( std::string_view link, std::string_view name ) {

	std::string font_path = g_file_system.m_fonts_path;
	g_winapi.path_append( font_path.data( ), name.data( ) );

	if ( !std::filesystem::exists( font_path ) ) {

		if ( !SUCCEEDED( g_winapi.url_download_to_file( NULL, link.data( ), font_path.data( ), 0, NULL ) ) ) {

			g_console.log( log_error, XOR( "failed to download font %s" ), name);

			return false;

		}

	}

	g_winapi.add_font_resource( font_path.data( ) );

	return true;

}

void render::handle_flags( int& x, int& y, int width, int height, int flags ) {

	if ( !flags )
		return;

	if ( flags & x_right )
		x -= width;
	else if ( flags & x_centre )
		x -= width / 2;

	if ( flags & y_bottom )
		y -= height;
	else if ( flags & y_centre )
		y -= height / 2;

}