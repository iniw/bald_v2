#pragma once

struct studio_render_context {

	char      pad0[ 0x240 ];
	float     m_color_mod[ 3 ];
	float     m_alpha_mod;
	material* m_forced_material[ 4 ];
	int       m_forced_material_type;
	int       m_forced_material_index[ 4 ];
	int       m_forced_material_index_count;

	inline auto set_color( const color& color ) {

		m_color_mod[ 0 ] = static_cast< float >( color.r ) / 255.f;
		m_color_mod[ 1 ] = static_cast< float >( color.g ) / 255.f;
		m_color_mod[ 2 ] = static_cast< float >( color.b ) / 255.f;

	}

	inline auto set_alpha( float alpha ) {

		m_alpha_mod = alpha;

	}

	inline auto set_material( material* material, int var = 0, bool value = false ) {

		if ( material && var )
			material->set_material_var_flag( var, value );

		m_forced_material_type = 0;
		m_forced_material[ 0 ] = material;
		m_forced_material_index[ 0 ] = -1;
		m_forced_material_index_count = 0;

	}

};