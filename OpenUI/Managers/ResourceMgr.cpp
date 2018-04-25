#include "stdafx.h"
#include "ResourceMgr.h"

ResourceMgr::~ResourceMgr ()
{
	for ( auto it = m_sprites.begin () ; it != m_sprites.end () ; ++it )
	{
		delete it._Ptr->_Myval;
	}

	for ( auto it = m_fonts.begin () ; it != m_fonts.end () ; ++it )
	{
		delete it._Ptr->_Myval;
	}

	for ( auto it = m_images.begin () ; it != m_images.end () ; ++it )
	{
		delete it._Ptr->_Myval;
	}

	for ( auto it = m_shaders.begin () ; it != m_shaders.end () ; ++it )
	{
		delete it._Ptr->_Myval;
	}
}

sf::Shader& ResourceMgr::CreateShader ( const std::string& fileName, const sf::Shader::Type type )
{
	auto* shader = new sf::Shader ();
	shader->loadFromFile ( fileName, type );

	m_shaders.insert ( shader );

	return *shader;
}

sf::Font& ResourceMgr::CreateFont ( const std::string& fileName )
{
	auto* font = new sf::Font;
	font->loadFromFile ( fileName );

	m_fonts.insert ( font );

	return *font;
}

sf::Image& ResourceMgr::CreateImage ( const unsigned width, const unsigned height, const sf::Color& color )
{
	auto* image = new sf::Image;
	image->create ( width, height, color );

	m_images.insert ( image );

	return *image;
}

sf::Image& ResourceMgr::CreateImage ( const std::string& fileName )
{
	auto* image = new sf::Image;
	image->loadFromFile ( fileName );

	m_images.insert ( image );
	return *image;
}

sf::Sprite& ResourceMgr::CreateSprite ( const std::string& fileName, const sf::IntRect& area )
{
	auto* texture = new sf::Texture;
	texture->loadFromFile ( fileName, area );

	return CreateSprite ( texture );
}

sf::Sprite& ResourceMgr::CreateSprite ( sf::Texture* texture )
{
	auto* sprite = new sf::Sprite ( *texture );
	m_sprites.insert ( sprite );

	return *sprite;
}
