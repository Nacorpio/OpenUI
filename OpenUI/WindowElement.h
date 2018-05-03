#pragma once
#include "Entities/Elements/Element.h"
#include <iostream>
#include "Global.h"

namespace OpenUI
{
	class GraphicsContext;
	class WindowElement : public Element
	{
	public:
		WindowElement(const std::string& p_name, const uint16_t & p_headerSize);
		~WindowElement();

		void Start() const override;
		void Initialize() override;

		void Update (  ) override;
		void Draw(const GraphicsContext & gContext) override;

		void OnMouseEnter() override;
		void OnMouseLeave() override;
		void OnMouseMove () override;
		void OnMouseHover() override;
		void OnMouseUp () override;
		void OnMouseDown () override;
		void OnMouseClick () override;
		void OnDrop(const InputHandler::MouseDropEvent& event) override;
		void OnDragBegin() override;

		void OnBoundsChanged ( const IntRect & delta ) override;

	private:
		uint16_t m_headerHeight = 30;
		IntVector m_mousePressedPosition;
		bool m_isMousePressedHeader = false;
		sf::RectangleShape * m_headerBar = nullptr;

		void UpdateHeaderBarBounds()
		{
			m_headerBar->setSize(sf::Vector2f(GetBounds().Size.sfVector.x, m_headerHeight));
			m_headerBar->setPosition(sf::Vector2f(GetBounds().Position.sfVector));
		}

		bool CheckMouseDownHeader()
		{
			if(sInputInformation->MousePosition.Y < GetPosition().Y + m_headerHeight)
			{
				const auto currentLocation = GetBounds().Position;
				m_mousePressedPosition.X = sInputInformation->MousePosition.X - currentLocation.X;
				m_mousePressedPosition.Y = sInputInformation->MousePosition.Y - currentLocation.Y;
				return true;
			}
			return false;
		}

		void DragWindow()
		{
			SetPosition(sInputInformation->MousePosition - m_mousePressedPosition);
		}
	};

	
}
