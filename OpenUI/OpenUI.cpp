// OpenUI.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "Managers/ResourceMgr.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include "Entities/Elements/Windows/ClientWindow.h"

int main ()
{
	sf::Image& myImage = sResourceMgr->CreateImage ( 100, 100, sf::Color::White );
	sf::Sprite& mySprite = sResourceMgr->CreateSprite ( myImage );
	sf::Font& font = sResourceMgr->CreateFont ( "AlegreyaSansSC-Regular.ttf" );

	//Button * myButton = sElementMgr->CreateButton(0, "Hello");
	//auto x = myButton->GetName();
	OpenUI::RenderWindowSettings mySetting;
	sf::RenderWindow*const myRenderWindow = new sf::RenderWindow (
																  mySetting.VideoMode,
																  mySetting.Title,
																  mySetting.Style,
																  mySetting.ContextSettings );
	OpenUI::ClientWindow* clientWindow = new OpenUI::ClientWindow ( "", mySetting );
	clientWindow->Start ();

	std::cin.get ();
	return 0;
}
