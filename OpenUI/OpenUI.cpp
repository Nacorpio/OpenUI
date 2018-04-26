// OpenUI.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <Managers/ResourceMgr.h>
#include <SFML/Graphics/RenderWindow.hpp>
#include <Entities/Elements/Windows/ClientWindow.h>
#include <Entities/Controls/Button.h>
#include "Managers/ElementMgr.h"

int main ()
{
	const sf::Image& myImage = sResourceMgr->CreateImage ( 100, 100, sf::Color::White );
	const sf::Sprite& mySprite = sResourceMgr->CreateSprite ( myImage );
	const sf::Font& myFont = sResourceMgr->CreateFont ( "AlegreyaSansSC-Regular.ttf" );

	const OpenUI::ClientWindow* myClientWindow = sElementMgr->CreateClientWindow ( 0, "clientWindow" );
	const OpenUI::Button* myButton = sElementMgr->CreateButton ( 0, "button0" );

	std::cin.get ();
	return 0;
}
