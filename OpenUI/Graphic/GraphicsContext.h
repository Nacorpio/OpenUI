#pragma once

namespace OpenUI
{
	class ClientWindow;

	class GraphicsContext final
	{
	public:
		explicit GraphicsContext ();

		ClientWindow& GetClientWindow () const;

	private:
		ClientWindow* m_clientWindow = nullptr;
	};
}
