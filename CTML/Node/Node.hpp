#pragma once

namespace CTML
{
	/**
	 Generic HTML Node class for CTML.
	 */
	class Node
	{
	public:
		Node()
		{
		}

		~Node()
		{
		}

	private:
		/**
		 Determines whether the node is
		 essentially a container or "root"
		 node.
		 
		 For example, an HTML document would
		 use a empty root node, then add all
		 of the children such as DOCTYPE and
		 others within.
		 
		 Defaults to true unless otherwise set.
		 */
		bool m_empty = true;

	};
}