#pragma once

#include <set>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Shader.hpp>

typedef std::set <sf::Sprite*> SpriteSet;
typedef std::set <sf::Image*> ImageSet;
typedef std::set <sf::Font*> FontSet;
typedef std::set <sf::Shader*> ShaderSet;

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
	sf::Image& CreateImage ( unsigned int width, unsigned int height, const sf::Color& color );
	sf::Image& CreateImage ( const std::string& fileName );
	sf::Sprite& CreateSprite ( const std::string& fileName, const sf::IntRect& area );
	sf::Sprite& CreateSprite ( const sf::Texture& texture );

private:
	SpriteSet m_sprites;
	ImageSet m_images;
	FontSet m_fonts;
	ShaderSet m_shaders;
};

#define sResourceMgr ResourceMgr::instance()
