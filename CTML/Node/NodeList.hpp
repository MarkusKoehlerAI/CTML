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
		/**
		 Construct a NodeList of the specified size.
		 */
		NodeList(const size_t capacity=1);

		~NodeList();

		/**
		 Simply add a new Node to the list.

		 May or may not resize the underlying
		 array. To avoid an unnecessary resize,
		 try creating the list with a default
		 capacity in mind.

		 Since the array might be resized by a
		 the count multiplied by two, it could
		 reserve a large amount of memory.
		 
		 To mitigate that, resize to the count
		 when done manipulating the list using
		 the Capacity method.

		 Returns the NodeList for chainability.
		 */
		NodeList& Add(const Node& node);

		/**
		 Simply remove a Node from the list
		 using its index in the list.

		 This method does not resize the
		 underlying array. To unreserve
		 the memory after removal, resize
		 to the count of the NodeList.

		 Returns the NodeList for chainability.
		 */
		NodeList& Remove(const size_t item);

		/**
		 Iterates through the whole NodeList, running
		 the callback method passed in until there are
		 no more nodes to iterate through.
		 */
		void ForEach(const std::function<void(const size_t, const Node&)> callback);

		/**
		 Grab the amount of Nodes in the NodeList.
		 */
		inline size_t Count()
		{
			return m_count;
		}

		/**
		 Grab the amount of reserved nodes in the
		 NodeList currently.
		 */
		inline size_t Capacity()
		{
			return m_capacity;
		}

		/**
		 Reserve an array of nodes up to the passed
		 in capacity value.

		 Do not run this continuously, this copies
		 memory! Therefore, wait until you are done
		 manipulating the list, then resize to what
		 you want.

		 Returns the NodeList for chainability.
		 */
		inline NodeList& Capacity(size_t capacity)
		{
			this->m_capacity = capacity;

			_ResizeArray(capacity);

			return *this;
		}

	private:
		/**
		 The underlying fixed array of Nodes.
		 
		 When an item is added, and the array
		 is too small, the array is resized
		 by the current amount of nodes
		 multiplied by two.

		 This array defaults to a size that will
		 hold a single node within.
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

		 Defaults to one, as the array defaults
		 to holding one node.
		 */
		size_t m_capacity = 0;

		/**
		 Resize the array for placing elements
		 within continuously.

		 The resizedCapacity parameter defaults
		 to negative one, which, any default
		 number will resize the array by the
		 capacity multiplied by two.
		 */
		void _ResizeArray(const ptrdiff_t resizedCapacity = -1);

	};
}