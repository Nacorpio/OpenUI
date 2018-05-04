#pragma once
#include "Entities/Elements/Element.h"
#include "Common/Global.h"


namespace OpenUI
{
	class GraphicsContext;
	class WindowElement;

	class WindowHeaderElement : public Element
	{
	public:

		WindowHeaderElement(const std::string& p_name);
		~WindowHeaderElement();

		WindowElement& GetWindowContainer () const;

		void SetWindowContainer ( WindowElement * element );

		void ContainerAddChild ( Element * element ) const;

		void OnMouseDown () override;

		void Update () override;

	private:
		WindowElement * m_windowElement = nullptr;
		IntVector m_mousePressedPosition;
		bool m_isMousePressed = false;

		void SetMousePressedPosition ();

		void DragWindow ();
	};


	class WindowElement : public Element
	{
	public:
		WindowElement(const std::string& p_name);
		~WindowElement();
	};

	
}
