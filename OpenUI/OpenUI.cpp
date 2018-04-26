// OpenUI.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <Managers/ResourceMgr.h>
#include <SFML/Graphics/RenderWindow.hpp>
#include <Entities/Elements/Windows/ClientWindow.h>
#include <Entities/Controls/Button.h>
#include "Managers/ElementMgr.h"
#include "Managers/MouseStateManager.h"

int main ()
{
	const sf::Image& myImage = sResourceMgr->CreateImage ( 100, 100, sf::Color::White );
	const sf::Sprite& mySprite = sResourceMgr->CreateSprite ( myImage );
	const sf::Font& myFont = sResourceMgr->CreateFont ( "AlegreyaSansSC-Regular.ttf" );

	OpenUI::ClientWindow* myClientWindow = sElementMgr->CreateClientWindow ( 0, "clientWindow" );
	OpenUI::Button* myButton = sElementMgr->CreateButton ( 0, "button0" );
	OpenUI::Button* myButton1 = sElementMgr->CreateButton(1, "button1");

	myButton->SetSize(IntVector(100,100));
	myButton->SetPosition(IntVector(10, 10));
	myButton1->SetSize(IntVector(50, 50));
	myButton1->SetPosition(IntVector(10, 10));

	myButton->AddChild(myButton1);
	myClientWindow->AddChild(myButton);

	OpenUI::MouseStateManager myMSM;
	myMSM.CheckMouseIntersection(myClientWindow);

	std::cin.get ();
	return 0;
}
