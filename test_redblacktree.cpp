#include <deepstate/DeepState.hpp>
#include "RedBlackTree.h"
#include <algorithm> // Include this for std::min_element
#include <vector>    // Include this for std::vector

using namespace deepstate;

TEST(RedBlackTree, InsertAndRemove)
{
    RedBlackTree tree;

    // Generate a random number of insertions
    int num_operations = DeepState_IntInRange(1, 100);
    std::vector<int> inserted_values;

    // Insert random integers into the tree
    for (int i = 0; i < num_operations; ++i)
    {
        int value = DeepState_Int();
        tree.insert(value);
        inserted_values.push_back(value);
    }

    // Check if the tree remains valid after each operation
    for (int val : inserted_values)
    {
        tree.insert(val); // Re-insert duplicates to test tree stability
    }

    // Randomly remove some elements
    int num_removals = DeepState_IntInRange(0, num_operations);
    for (int i = 0; i < num_removals; ++i)
    {
        int index = DeepState_IntInRange(0, inserted_values.size() - 1);
        tree.remove(inserted_values[index]);
        inserted_values.erase(inserted_values.begin() + index);
    }
}

TEST(RedBlackTree, MinimumValidation)
{
    RedBlackTree tree;

    // Insert nodes and validate the minimum function
    std::vector<int> values;
    for (int i = 0; i < 10; ++i)
    {
        int value = DeepState_IntInRange(1, 100);
        tree.insert(value);
        values.push_back(value);
    }

    // Ensure that the minimum node matches the smallest value in the vector
    Node *min_node = tree.getMinimum();
    ASSERT(min_node != nullptr) << "Minimum node should not be null.";
    ASSERT(min_node->data == *std::min_element(values.begin(), values.end()))
        << "Tree minimum doesn't match the smallest inserted value.";
}

TEST(RedBlackTree, StressTest)
{
    RedBlackTree tree;

    // Perform a large number of operations to stress-test the tree
    int num_operations = DeepState_IntInRange(1000, 5000);
    for (int i = 0; i < num_operations; ++i)
    {
        int op = DeepState_IntInRange(0, 1); // 0 for insert, 1 for remove
        int value = DeepState_Int();
        if (op == 0)
        {
            tree.insert(value);
        }
        else
        {
            tree.remove(value);
        }
    }
}
