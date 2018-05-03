// OpenUI.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <SFML/Graphics/RenderWindow.hpp>
#include <Entities/Elements/Windows/ClientWindow.h>
#include <Entities/Controls/Button.h>
#include "Managers/ElementMgr.h"
#include "Managers/Controller.h"
#include "Entities/Elements/Windows/WindowElement.h"

int main ()
{
	//const sf::Image& myImage = sResourceMgr->CreateImage ( 100, 100, sf::Color::White );
	//const sf::Sprite& mySprite = sResourceMgr->CreateSprite ( myImage );
	//const sf::Font& myFont = sResourceMgr->CreateFont ( "AlegreyaSansSC-Regular.ttf" );

	OpenUI::ClientWindow* myClientWindow = sElementMgr->CreateClientWindow ( 0, "clientWindow" );
	OpenUI::Button* myButton = sElementMgr->CreateButton ( 2, "button0" );
	OpenUI::Button* myButton1 = sElementMgr->CreateButton ( 3, "button1" );
	OpenUI::WindowElement* myWindowElement = sElementMgr->CreateWindowElement(4, "windowElement0",30);
	
	myWindowElement->SetBounds({ 0,0,200,200 });
	myButton->SetBounds({ 0,0,100,100 });
	myButton1->SetBounds({ 0,100,100,100 });

	OpenUI::Scheme* myButtonScheme = new OpenUI::Scheme ();
	OpenUI::Scheme* myWindowScheme = new OpenUI::Scheme();
	OpenUI::Scheme* myClientWindowScheme = new OpenUI::Scheme();

	myButtonScheme->Colors.BackColor = sf::Color(80,80,80);
	myButtonScheme->Colors.BackColor.Entered = sf::Color(100, 100, 100);
	myButtonScheme->Colors.BackColor.Pressed = sf::Color(130, 130, 130);

	myWindowScheme->Colors.BackColor = sf::Color(60, 60, 60);
	myClientWindowScheme->Colors.BackColor = sf::Color(33, 33, 33);

	myWindowElement->SetScheme(myWindowScheme);
	myClientWindow->SetScheme(myClientWindowScheme);
	myButton->SetScheme ( myButtonScheme );
	myButton1->SetScheme (myClientWindowScheme);


	myClientWindow->AddChild(myWindowElement);

	myWindowElement->AddChild(myButton);
	myButton->AddChild(myButton1);

	myWindowElement->SetPosition(OpenUI::IntVector(100, 100));
	sController->Start();

	std::cin.get ();
	return 0;
}
