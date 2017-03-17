#include "../stdafx.hpp"
#include "NodeList.hpp"

#include "Node.hpp"

using namespace CTML;

/**
Construct a NodeList of the specified size.
*/
NodeList::NodeList(const size_t capacity)
	:
	m_capacity(capacity)
{
	m_nodes = new Node[capacity];
}

NodeList::~NodeList()
{
	delete[] m_nodes;

	m_count    = 0;
	m_capacity = 0;
}

NodeList& NodeList::Add(const Node& node)
{
	// Resize if we are at or over capacity
	if (m_count >= m_capacity)
		_ResizeArray();

	m_nodes[m_count] = node;

	m_count++;

	return *this;
}

NodeList& NodeList::Remove(const size_t item)
{
	// Do not try and delete something out of bounds
	if (item < 0 || item > m_count)
		return *this;

	// To remove, shift left each item until the end
	for (size_t index = item; index < m_count; index++)
		m_nodes[index] = m_nodes[index + 1];

	m_count--;

	_ResizeArray(m_count);

	return *this;
}

void NodeList::ForEach(const std::function<void(const size_t, const Node&)> callback)
{
	if (m_count == 0)
		return;

	for (size_t index = 0; index < m_count; index++)
		callback(index, m_nodes[index]);
}

void NodeList::_ResizeArray(const ptrdiff_t resizedCapacity)
{
	// Calculate the size for the new array
	size_t capacity = 0;

	if (resizedCapacity < 0)
		capacity = m_capacity * 2;
	else
		capacity = static_cast<size_t>(resizedCapacity);

	// Create a new array of nodes, copy the
	// current contents over to the new
	Node* resized = new Node[capacity];
	memcpy(resized, m_nodes, m_count * sizeof(Node));

	m_capacity = capacity;

	// Clean-up and reset
	delete[] m_nodes;
	m_nodes = resized;
}