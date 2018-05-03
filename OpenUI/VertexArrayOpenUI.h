#pragma once
#include <vector>
#include <SFML/Graphics/PrimitiveType.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include "Math/Rectangle.h"

class VertexArrayOpenUI
{
public:
	VertexArrayOpenUI()
		: m_vertices(0), m_primitive(sf::Points)
	{}

	~VertexArrayOpenUI();

	explicit VertexArrayOpenUI(sf::PrimitiveType p_type, size_t p_vertexCount = 0)
		: m_vertices ( p_vertexCount ),m_primitive ( p_type )
	{}

	sf::Vertex & operator[] (size_t p_index)
	{
		return *m_vertices[p_index];
	}

	const sf::Vertex & operator[] (size_t p_index) const
	{
		return *m_vertices[p_index];
	}

	void Clear()
	{
		m_vertices.clear();
	}

	void Resize(size_t p_vertexCount)
	{
		m_vertices.resize(p_vertexCount);
	}

	void Append(sf::Vertex & p_vertex)
	{
		m_vertices.push_back(&p_vertex);
	}



	size_t GetVertexCount() const
	{
		return m_vertices.size();
	}

	sf::PrimitiveType GetPrimitiveType() const
	{
		return m_primitive;
	}

	void SetPrimitiveType(sf::PrimitiveType p_type)
	{
		m_primitive = p_type;
	}

	void Draw( sf::RenderTarget& target, sf::RenderStates states) const
	{
		if (!m_vertices.empty())
		{
			target.draw(m_vertices[0], m_vertices.size(), m_primitive, states);
		}
	}

private:
	std::vector<sf::Vertex*> m_vertices;
	sf::PrimitiveType m_primitive;
};

