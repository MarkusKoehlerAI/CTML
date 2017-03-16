#pragma once

namespace CTML
{
	class Node;

	/**
	 A container representing a list of Node instances.
	 
	 Implemented similarly to a std::vector, but with
	 key differences in usability on a representation
	 of a CTML/HTML document.
	 */
	class NodeList
	{
	public:


	private:
		/**
		 The underlying fixed array of Nodes.
		 
		 When an item is added, and the array
		 is too small, the array is resized
		 by the current amount of nodes
		 multiplied by two.
		 */
		Node* m_nodes = nullptr;

		/**
		 The current amount of actual Node
		 instances within the array.
		 */
		size_t m_count = 0;

		/**
		 The current amount of Node instances
		 that can be placed in the array.
		 
		 Can be user-sized as to fit and use
		 less memory in the list.
		 */
		size_t m_capacity = 0;

	};
}