/*======================================================================
** You can use this file to test if your code is working
** properly by designing your own test case and test code.
** 
** You are allowed to modify this file as much as you would like.
** For grading, we will use our own filled version.
**======================================================================*/

#include <iostream>
#include <queue>
#include <sstream>
#include <string>

#include "binary-search-tree.h"

using namespace std;

// Assert Macros for test cases.
#define ASSERT_TRUE(T) \
    if (!(T))          \
        return false;
#define ASSERT_FALSE(T) \
    if ((T))            \
        return false;

string get_status_str(bool status) {
    return status ? "PASSED" : "FAILED";
}

// Function for getting the tree as a string
std::string breadthFirstTraversal(BinarySearchTree::Node* root) {

    // If no nodes, return an empty string.
    if (root == nullptr) {
        return "";
    }

    // Init a string buffer, and queue for traversal.
    stringstream ss;
    queue<BinarySearchTree::Node*> queue;

    // Seed the traversal.
    queue.push(root);

    // Walk through the tree, looking at each level inorder.
    bool first = true;
    while (!queue.empty()) {

        // Get the node.
        BinarySearchTree::Node* cur = queue.front();
        queue.pop();

        // Push this value into the string buffer.
        ss << (first ? "" : " ") << cur->val;
        first = false;

        // Add the left and right children if they exist.
        if (cur->left) {
            queue.push(cur->left);
        }
        if (cur->right) {
            queue.push(cur->right);
        }
    }

    string level_order_str = ss.str();
    return level_order_str;
}

// Define the test suites (implementation below).
class BinarySearchTreeTest {
private:
    bool test_result[8] = {0,0,0,0,0,0,0,0};
    string test_description[8] = {
        "Test1: New tree is valid",
        "Test2: Test a tree with one node",
        "Test3: Insert, remove, and size on linear list formation with three elements",
        "Test4: Test removal of a node with one child",
        "Test5: Insert multiple elements and remove till nothing remains",
        "Test6: Test removal of root node when both children of root have two children",
        "Test7: Test depth with many inserts and some removes",
        "Test8: Lots of inserts and removes"
    };
    
public:
    string getTestDescription(int test_num);
    void runAllTests();
    void printReport();

    bool test1();
    bool test2();
    bool test3();
    bool test4();
    bool test5();
    bool test6();
    bool test7();
    bool test8();
};


//======================================================================
//================================ MAIN ================================
//======================================================================
int main() {

    // The test suite has some tests implemented for you,
    // and place holders for where you can put your own.
    BinarySearchTreeTest bst_test;

    // You can check the description for each test to see 
    // what we will be testing for with the following method.
    // Alternatively, you can also navigate to the line above 
    // where the test description is stored to read it.
    cout << bst_test.getTestDescription(1) << endl;

    // Tests can be run one at a time to get their result
    bool result = bst_test.test1();
    cout << "Test1: " << get_status_str(result) << endl;

    // Or you can run all of the tests at once and generate a report.
    bst_test.runAllTests();
    bst_test.printReport();

    return 0;
}


//======================================================================
//====================== Binary Search Tree Test =======================
//======================================================================
string BinarySearchTreeTest::getTestDescription(int test_num) {
    if (test_num < 1 || test_num > 8) { // check range.
        return "";
    }
    return test_description[test_num-1];
}

void BinarySearchTreeTest::runAllTests() {
    test_result[0] = test1();
    test_result[1] = test2();
    test_result[2] = test3();
    test_result[3] = test4();
    test_result[4] = test5();
    test_result[5] = test6();
    test_result[6] = test7();
    test_result[7] = test8();
}

void BinarySearchTreeTest::printReport() {
    cout << "  BINARY SEARCH TREE TEST RESULTS  \n"
         << " ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ \n";
    for (int idx = 0; idx < 8; ++idx) {
        cout << test_description[idx] << "\n  " << get_status_str(test_result[idx]) << endl << endl;
    }
    cout << endl;
}

// Test 1: New tree is valid
bool BinarySearchTreeTest::test1() {

    // Test set up.
    BinarySearchTree bst;

    // Check that the internal state is set correctly.
    ASSERT_TRUE(bst.getRootNode() == nullptr)
    ASSERT_TRUE(bst.root_ == nullptr)
    ASSERT_TRUE(bst.size_ == 0 && bst.size() == 0)

    // Try some allowed function on the empty tree to ensure they handle this case.
    ASSERT_FALSE(bst.exists(0))

    // Compare the tree's representation to the expected tree.
    string expected_level_order = "";
    string tree_level_order = breadthFirstTraversal(bst.root_);
    ASSERT_TRUE(tree_level_order.compare(expected_level_order) == 0)

    // Return true to signal all tests passed.
    return true;
}

// Test 2: Test a tree with one node
bool BinarySearchTreeTest::test2() {

    // Test set up.
    BinarySearchTree bst;

    // Try to add data to the bst.
    ASSERT_TRUE(bst.insert(5))

    // Check that the root has changed.
    ASSERT_FALSE(bst.root_ == nullptr)

    // Try to remove an element that isn't present.
    ASSERT_FALSE(bst.remove(4))

    // Check to see if 5 is in the tree.
    ASSERT_TRUE(bst.exists(5))

    // What is the max value of the tree.
    ASSERT_TRUE(bst.max() == bst.min() && bst.max() == 5)

    // Check that size is expected.
    ASSERT_TRUE(bst.size() == 1)

    // Compare the tree's representation to the expected tree.
    string expected_level_order = "5";
    string tree_level_order = breadthFirstTraversal(bst.root_);
    ASSERT_TRUE(tree_level_order.compare(expected_level_order) == 0)

    // Return true to signal all tests passed.
    return true;
}

// Test 3: Insert, remove, and size on linear list formation with three elements
bool BinarySearchTreeTest::test3() {

    BinarySearchTree bst;

    ASSERT_TRUE(bst.insert(5))
    ASSERT_TRUE(bst.insert(6))
    ASSERT_TRUE(bst.insert(7))

    ASSERT_FALSE(bst.root_ == nullptr)

    ASSERT_TRUE(bst.exists(6))

    ASSERT_TRUE(bst.remove(6))
    ASSERT_TRUE(bst.insert(9))

    ASSERT_TRUE(bst.min() == 5 && bst.max() == 9)

    ASSERT_TRUE(bst.size() == 3)

    string expected_level_order = "5 7 9";
    string tree_level_order = breadthFirstTraversal(bst.root_);
    ASSERT_TRUE(tree_level_order.compare(expected_level_order) == 0)

    return true;
}

// Test 4: Test removal of a node with one child
bool BinarySearchTreeTest::test4() {

    BinarySearchTree bst;

    ASSERT_TRUE(bst.insert(6))
    ASSERT_TRUE(bst.insert(8))
    ASSERT_TRUE(bst.insert(3))
    ASSERT_TRUE(bst.insert(5))

    ASSERT_FALSE(bst.root_ == nullptr)
    ASSERT_TRUE(bst.size() == 4 && bst.height() == 2)

    ASSERT_TRUE(bst.remove(3))
    ASSERT_TRUE(bst.size() == 3 && bst.height() == 1)

    string expected_level_order = "6 5 8";
    string tree_level_order = breadthFirstTraversal(bst.root_);
    ASSERT_TRUE(tree_level_order.compare(expected_level_order) == 0)

    return true;
}

// Test 5: Insert multiple elements and remove till nothing remains
bool BinarySearchTreeTest::test5() {

    BinarySearchTree bst;

    BinarySearchTree::DataType in[6] = {21, 15, 25, 13, 22, 30};
    for (auto val : in) {
        ASSERT_TRUE(bst.insert(val))
    }

    ASSERT_TRUE(bst.root_ != nullptr && bst.size() == 6)
    ASSERT_TRUE(bst.max() == 30 && bst.min() == 13)

    for (auto val : in) {
        ASSERT_TRUE(bst.remove(val))
    }

    ASSERT_TRUE(bst.root_ == nullptr && bst.size() == 0)
    ASSERT_TRUE(bst.height() == -1)

    return true;
}

// Test 6: Test removal of root node when both children of root have two children
bool BinarySearchTreeTest::test6() {

    // Test set up.
    BinarySearchTree bst;

    // Insert a bunch of nodes into the tree in the following order.
    BinarySearchTree::DataType in[7] = {8, 3, 10, 1, 6, 9, 15};
    for (auto val : in) {
        ASSERT_TRUE(bst.insert(val))
    }

    // Remove the root.
    ASSERT_TRUE(bst.remove(8));

    // Check the resulting tree.
    string expected_tree1 = "6 3 10 1 9 15";
    string expected_tree2 = "9 3 10 1 6 15";
    string tree_level_order = breadthFirstTraversal(bst.root_);

    // Depending on implementation, resulting tree should be one of the above.
    ASSERT_TRUE(tree_level_order.compare(expected_tree1) == 0 ||
                tree_level_order.compare(expected_tree2) == 0)

    // Return true to signal all tests passed.
    return true;
}

// Test 7: Test depth with many inserts and some removes
bool BinarySearchTreeTest::test7() {
    BinarySearchTree bst;

    BinarySearchTree::DataType in[6] = {6, 3, 8, 5, 7, 10};
    for (auto val : in) {
        ASSERT_TRUE(bst.insert(val))
    }

    ASSERT_TRUE(bst.root_ != nullptr && bst.size() == 6)
    ASSERT_TRUE(bst.height() == 2)

    ASSERT_TRUE(bst.remove(3))
    ASSERT_TRUE(bst.height() == 2)

    ASSERT_TRUE(bst.remove(8))
    ASSERT_TRUE(bst.height() == 2)

    ASSERT_TRUE(bst.remove(10))
    ASSERT_TRUE(bst.height() == 1)

    ASSERT_TRUE(bst.insert(4))
    ASSERT_TRUE(bst.height() == 2)

    ASSERT_TRUE(bst.root_ != nullptr && bst.size() == 4)

    string expected_level_order = "6 5 7 4";
    string tree_level_order = breadthFirstTraversal(bst.root_);
    ASSERT_TRUE(tree_level_order.compare(expected_level_order) == 0)

    ASSERT_TRUE(bst.remove(5))
    ASSERT_TRUE(bst.height() == 1)

    ASSERT_TRUE(bst.remove(7))
    ASSERT_TRUE(bst.height() == 1)

    ASSERT_TRUE(bst.remove(4))
    ASSERT_TRUE(bst.height() == 0)

    ASSERT_TRUE(bst.root_ != nullptr && bst.size() == 1)

    return true;
}

// Test 8: Lots of inserts and removes
bool BinarySearchTreeTest::test8() {

    BinarySearchTree bst;

    for(int i = 1; i < 11; i++){
        ASSERT_TRUE(bst.insert(i))
    }

    ASSERT_TRUE(bst.size() == 10)

    for(int i = 1; i < 6; i++){
        ASSERT_TRUE(bst.remove(i))
    }

    ASSERT_TRUE(bst.size() == 5)

    string expected_level_order = "6 7 8 9 10";
    string tree_level_order = breadthFirstTraversal(bst.root_);
    ASSERT_TRUE(tree_level_order.compare(expected_level_order) == 0)

    return true;
}