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
#include "Graphic/Scheme.h"

int main ()
{
	//const sf::Image& myImage = sResourceMgr->CreateImage ( 100, 100, sf::Color::White );
	//const sf::Sprite& mySprite = sResourceMgr->CreateSprite ( myImage );
	//const sf::Font& myFont = sResourceMgr->CreateFont ( "AlegreyaSansSC-Regular.ttf" );

	OpenUI::ClientWindow* myClientWindow = sElementMgr->CreateClientWindow ( 0, "clientWindow" );
	OpenUI::Button* myButton = sElementMgr->CreateButton (1, "button0" );
	OpenUI::Button* myButton1 = sElementMgr->CreateButton (2, "button1" );
	OpenUI::WindowHeaderElement* myWindowHeaderElement = sElementMgr->CreateWindowHeaderElement(3, "windowHeaderElement0");
	OpenUI::WindowElement* myWindowElement = sElementMgr->CreateWindowElement(4, "WindowElement0");
	OpenUI::ScrollBar* myScrollBar = sElementMgr->CreateScrollBar(5, "scrollBar0");

	myWindowHeaderElement->SetBounds({ 10,10,200,30 });
	myWindowElement->SetBounds({ 10,10,200,300 });
	myScrollBar->SetBounds({ 180,0,30,200 });
	myButton->SetBounds({ 0,300,100,100 });
	myButton1->SetBounds({ 50,50,100,100 });

	OpenUI::Scheme* myButtonScheme = new OpenUI::Scheme ();
	OpenUI::Scheme* myWindowScheme = new OpenUI::Scheme();
	OpenUI::Scheme* myWindowHeaderScheme = new OpenUI::Scheme();
	OpenUI::Scheme* myClientWindowScheme = new OpenUI::Scheme();
	OpenUI::Scheme* myScrollBarScheme = new OpenUI::Scheme();

	myScrollBarScheme->Colors.BackColor = sf::Color(65, 65, 65);
	myScrollBarScheme->Colors.BackColor.Entered = sf::Color(70, 70, 70);
	myScrollBarScheme->Colors.BackColor.Pressed = sf::Color(75, 75, 75);
	myScrollBarScheme->Colors.OutlineColor = sf::Color(75, 75, 75);
	myScrollBarScheme->Colors.OutlineColor.Entered = sf::Color(80, 80, 80);
	myScrollBarScheme->Colors.OutlineColor.Pressed = sf::Color(95, 95, 95);

	myButtonScheme->Colors.BackColor = sf::Color(80,80,80);
	myButtonScheme->Colors.BackColor.Entered = sf::Color(100, 100, 100);
	myButtonScheme->Colors.BackColor.Pressed = sf::Color(130, 130, 130);

	myWindowHeaderScheme->Colors.BackColor = sf::Color(120, 120, 120);
	myWindowScheme->Colors.BackColor = sf::Color(60, 60, 60);
	myClientWindowScheme->Colors.BackColor = sf::Color(33, 33, 33);

	myWindowHeaderElement->SetScheme(myWindowHeaderScheme);
	myWindowElement->SetScheme(myWindowScheme);
	myScrollBar->SetScheme(myScrollBarScheme);

	myClientWindow->SetScheme(myClientWindowScheme);
	myButton->SetScheme ( myButtonScheme );
	myButton1->SetScheme (myClientWindowScheme);

	myClientWindow->AddChild(myWindowHeaderElement);
	myWindowHeaderElement->SetWindowContainer(myWindowElement);
	myWindowHeaderElement->ContainerAddChild (myScrollBar);
	myWindowHeaderElement->ContainerAddChild(myButton);
	myButton->AddChild(myButton1);

	sController->Start();

	std::cin.get ();
	return 0;
}
