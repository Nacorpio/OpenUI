#pragma once

#include <set>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Shader.hpp>

namespace OpenUI
{
	typedef std::set <sf::Drawable*> DrawableSet;
	typedef std::set <sf::Image*> ImageSet;
	typedef std::set <sf::Font*> FontSet;
	typedef std::set <sf::Shader*> ShaderSet;
	typedef std::set <sf::Texture*> TextureSet;

	class ResourceMgr
	{
	public:
		static ResourceMgr* instance ()
		{
			static ResourceMgr instance;
			return &instance;
		}

		~ResourceMgr ();

		sf::Shader& CreateShader ( const std::string& fileName, sf::Shader::Type type );
		sf::Font& CreateFont ( const std::string& fileName );

		sf::Image& CreateImage(const std::string& fileName);
		sf::Image& CreateImage ( unsigned int width, unsigned int height, const sf::Color& color );

		sf::Sprite& CreateSprite ( const std::string& fileName, const sf::IntRect& area );
		sf::Sprite& CreateSprite ( const sf::Texture& texture );
		sf::Sprite& CreateSprite ( const sf::Image& image );
		sf::Sprite& CreateSprite ( const sf::Image& image, const sf::IntRect& area );

		sf::Texture& CreateTexture ( const std::string& fileName );
		sf::Texture& CreateTexture ( const sf::Image& image, const sf::IntRect& area );
		sf::Texture& CreateTexture ( const sf::Image& image );

	private:
		DrawableSet m_drawables;
		ImageSet m_images;
		FontSet m_fonts;
		ShaderSet m_shaders;
		TextureSet m_textures;
	};
}

#define sResourceMgr OpenUI::ResourceMgr::instance()
