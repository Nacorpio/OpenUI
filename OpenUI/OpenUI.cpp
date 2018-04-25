// OpenUI.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "Managers/ResourceMgr.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include "ClientWindow.h"

int main()
{
	sf::Image& myImage = sResourceMgr->CreateImage(100, 100, sf::Color::White);
	sf::Sprite& mySprite = sResourceMgr->CreateSprite(myImage);
	sf::Font& font = sResourceMgr->CreateFont("AlegreyaSansSC-Regular.ttf");

	const OpenUI::RenderWindowSettings mySetting;
	sf::RenderWindow *const myRenderWindow = new sf::RenderWindow (
																   mySetting.Size,
																   mySetting.Title,
																   mySetting.Style,
																   mySetting.ContextSettings );
	OpenUI::ClientWindow * clientWindow = new OpenUI::ClientWindow ( myRenderWindow );
	clientWindow->Start();
	std::cin.get ();

    return 0;
}


