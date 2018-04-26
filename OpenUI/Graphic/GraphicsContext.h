#pragma once

namespace OpenUI
{
	class ClientWindow;

	class GraphicsContext final
	{
	public:
		explicit GraphicsContext ( const ClientWindow& clientWindow );

		const ClientWindow& GetClientWindow () const;

	private:
		const ClientWindow& m_clientWindow;
	};
}
