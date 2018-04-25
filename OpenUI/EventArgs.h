#pragma once
#include <memory>
#include <SFML/Graphics/RenderWindow.hpp>
class GraphicContext
{
public:
	std::shared_ptr <sf::RenderWindow> RenderWindow;
	explicit GraphicContext(std::shared_ptr<sf::RenderWindow> p_renderWindow)
		: RenderWindow(p_renderWindow)
	{
	}
};


