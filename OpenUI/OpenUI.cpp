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

	OpenUI::ClientWindow* myClientWindow = sElementMgr->CreateClientWindow ( 0, "clientWindow" );
	OpenUI::Button* myButton = sElementMgr->CreateButton ( 1, "button0" );

	myClientWindow->AddChild ( myButton );
	myClientWindow->RemoveChild ( myButton );

	std::cin.get ();
	return 0;
}
