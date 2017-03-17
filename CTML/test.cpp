/**
 A collection of test methods for CTML.
 
 Cases should be seperate methods that
 compares a desired output with the one
 returned by the library.
 
 Once a method is added, add it to the
 main method for running a sweep of tests.
 */
#include "stdafx.hpp"

#include "Node/Node.hpp"
#include "Node/NodeList.hpp"

using namespace CTML;

const std::string boolean_to_string(bool value)
{
	return ((value) ? "true" : "false");
}

/**
 Test the ability to add a node to the
 NodeList.

 Fails if the NodeList's Count method
 returns zero.
 */
void run_node_list_add_test()
{
	std::cout << "Running NodeList Add Test..." << std::endl;

	const size_t expectedCount = 1;

	Node node;
	NodeList list;

	list.Add(node);

	const size_t count = list.Count();

	std::cout << "Add Test Passed: " << boolean_to_string(count == expectedCount) << std::endl;
	std::cout << "Expected Count: " << expectedCount << std::endl;
	std::cout << "Actual Count: " << count << std::endl << std::endl;
}

/**
 Test the ability to remove a single
 node from the NodeList.

 Fails if the NodeList's Count method
 returns anything but zero.
 */
void run_node_list_remove_test()
{
	std::cout << "Running NodeList Remove Test..." << std::endl;

	NodeList list;

	list.Add(Node()).Add(Node()).Add(Node());

	const size_t expectedCount = list.Count() - 1;

	list.Remove(1);

	const size_t count = list.Count();

	std::cout << "Remove Test Passed: " << boolean_to_string(count == expectedCount) << std::endl;
	std::cout << "Expected Count: " << expectedCount << std::endl;
	std::cout << "Actual Count: " << count << std::endl << std::endl;
}

/**
 Test the ability to run through each
 node within the NodeList with the
 ForEach method.

 Fails if the iterations through the
 NodeList are less than the elements
 within said list.
 */
void run_node_for_each()
{
	std::cout << "Running NodeList ForEach Test..." << std::endl;

	NodeList list;

	list.Add(Node()).Add(Node()).Add(Node());

	const size_t expectedCount = list.Count();
	size_t       count         = 0;

	list.ForEach([&](const size_t, const Node&) {
		count++;
	});

	std::cout << "ForEach Test Passed: " << boolean_to_string(count == expectedCount) << std::endl;
	std::cout << "Expected Count: " << expectedCount << std::endl;
	std::cout << "Actual Count: " << count << std::endl << std::endl;
}

int main()
{
	run_node_list_add_test();
	run_node_list_remove_test();
	run_node_for_each();

	return 0;
}