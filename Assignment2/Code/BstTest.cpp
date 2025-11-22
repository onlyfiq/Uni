#include <iostream>
#include <vector>
#include <string>
#include "Bst.h"
using namespace std;

// Global container used to collect traversal output
vector<int> visited;

// Callback function used by traversals to store visited values
void Collect(const int& x)
{
    visited.push_back(x);
}

// Clears the global visited vector before a traversal test
void ResetVisited()
{
    visited.clear();
}

// Converts a vector<int> to a human-readable string
// Used to display traversal results in test output
string VecToStr(const vector<int>& v)
{
    string out = "{ ";
    for (size_t i = 0; i < v.size(); ++i)
    {
        out += to_string(v[i]);
        if (i + 1 < v.size())
        {
            out += ", ";
        }
    }
    out += " }";
    return out;
}

// Small wrapper to display [OK] / [FAIL] for each test condition
void Assert(bool condition, const string& message)
{
    if (!condition)
    {
        cout << "[FAIL] " << message << endl;
    }
    else
    {
        cout << "[OK] " << message << endl;
    }
}

// Verifies basic insertion and search functionality
void TestInsertAndSearch()
{
    cout << "\n=== TestInsertAndSearch ===\n";
    Bst<int> tree;

    tree.Insert(5);
    tree.Insert(3);
    tree.Insert(7);
    tree.Insert(1);
    tree.Insert(9);

    Assert(tree.Search(5), "Search root");
    Assert(tree.Search(1), "Search leftmost");
    Assert(tree.Search(9), "Search rightmost");
    Assert(!tree.Search(4), "Search missing value");
}

// Verifies that duplicate insertions are ignored
void TestDuplicateInsert()
{
    cout << "\n=== TestDuplicateInsert ===\n";
    Bst<int> tree;

    tree.Insert(5);
    tree.Insert(5); // duplicate should be ignored

    ResetVisited();
    tree.InOrder(Collect);

    Assert(visited.size() == 1, "Duplicate insertion ignored");
}

// Verifies that InOrder traversal outputs sorted order
void TestInOrderTraversal()
{
    cout << "\n=== TestInOrderTraversal ===\n";
    Bst<int> tree;

    int vals[] = {5, 3, 7, 1, 9, 8};
    for (int x : vals)
    {
        tree.Insert(x);
    }

    ResetVisited();
    tree.InOrder(Collect);

    vector<int> expected = {1, 3, 5, 7, 8, 9};
    Assert(visited == expected,
           string("InOrder = ") + VecToStr(visited));
}

// Verifies that PreOrder traversal matches expected sequence
void TestPreOrderTraversal()
{
    cout << "\n=== TestPreOrderTraversal ===\n";
    Bst<int> tree;

    int vals[] = {5, 3, 7, 1, 9, 8};
    for (int x : vals)
    {
        tree.Insert(x);
    }

    ResetVisited();
    tree.PreOrder(Collect);

    vector<int> expected = {5, 3, 1, 7, 9, 8};
    Assert(visited == expected,
           string("PreOrder = ") + VecToStr(visited));
}

// Verifies PostOrder traversal correctness
void TestPostOrderTraversal()
{
    cout << "\n=== TestPostOrderTraversal ===\n";
    Bst<int> tree;

    int vals[] = {5, 3, 7, 1, 9, 8};
    for (int x : vals)
    {
        tree.Insert(x);
    }

    ResetVisited();
    tree.PostOrder(Collect);

    vector<int> expected = {1, 3, 8, 9, 7, 5};
    Assert(visited == expected,
           string("PostOrder = ") + VecToStr(visited));
}

// Tests deletion of a leaf node
void TestDeleteLeaf()
{
    cout << "\n=== TestDeleteLeaf ===\n";
    Bst<int> tree;

    tree.Insert(5);
    tree.Insert(3);
    tree.Insert(7);

    tree.DeleteNode(3);

    Assert(!tree.Search(3), "Leaf deletion removes node");
}

// Tests deletion of a node with exactly one child
void TestDeleteOneChild()
{
    cout << "\n=== TestDeleteOneChild ===\n";
    Bst<int> tree;

    tree.Insert(5);
    tree.Insert(7);
    tree.Insert(9);  // child of 7

    tree.DeleteNode(7);

    Assert(!tree.Search(7), "Node with one child deleted");
    Assert(tree.Search(9), "Child promoted correctly");
}

// Tests deletion of a node with two children (uses successor replacement)
void TestDeleteTwoChildren()
{
    cout << "\n=== TestDeleteTwoChildren ===\n";
    Bst<int> tree;

    int vals[] = {50, 30, 70, 20, 40, 60, 80};
    for (int x : vals)
    {
        tree.Insert(x);
    }

    tree.DeleteNode(50);  // root with two children

    Assert(!tree.Search(50), "Node with two children deleted");
}

// Special case: deleting the root of the tree
void TestDeleteRoot()
{
    cout << "\n=== TestDeleteRoot ===\n";
    Bst<int> tree;

    tree.Insert(10);
    tree.Insert(5);
    tree.Insert(15);

    tree.DeleteNode(10);

    Assert(!tree.Search(10), "Root deleted");
}

// Ensures DeleteTree removes every node
void TestDeleteTree()
{
    cout << "\n=== TestDeleteTree ===\n";
    Bst<int> tree;

    for (int i = 0; i < 10; i++)
    {
        tree.Insert(i);
    }

    tree.DeleteTree();

    for (int i = 0; i < 10; i++)
    {
        Assert(!tree.Search(i), "Tree empty after DeleteTree");
    }
}

// Ensures deep copying works and copies remain independent
void TestCopyConstructor()
{
    cout << "\n=== TestCopyConstructor ===\n";
    Bst<int> tree;

    for (int i :
            {
                5, 3, 7, 1, 9
            })
    {
        tree.Insert(i);
    }

    Bst<int> copy(tree);

    Assert(copy.Search(3), "Copy contains same values");
    Assert(copy.Search(9), "Copy contains same values");

    // Modify original, ensure copy unchanged
    tree.DeleteNode(3);
    Assert(copy.Search(3), "Deep copy unaffected by original's changes");
}

// Ensures operator= performs deep copying correctly
void TestAssignmentOperator()
{
    cout << "\n=== TestAssignmentOperator ===\n";
    Bst<int> a, b;

    for (int x :
            {
                1, 2, 3
            })
    {
        a.Insert(x);
    }
    for (int x :
            {
                10, 20, 30
            })
    {
        b.Insert(x);
    }

    b = a;  // assignment

    Assert(b.Search(1) && b.Search(3), "Assigned tree has copied values");

    a.DeleteNode(1);
    Assert(b.Search(1), "Deep copy unaffected by modifications");
}

// Ensures BST invariant is valid after standard insertions
void TestInvariantChecker()
{
    cout << "\n=== TestInvariantChecker ===\n";
    Bst<int> tree;

    for (int x :
            {
                10, 5, 15, 2, 7
            })
    {
        tree.Insert(x);
    }
}

int main()
{
    TestInsertAndSearch();
    TestDuplicateInsert();
    TestInOrderTraversal();
    TestPreOrderTraversal();
    TestPostOrderTraversal();
    TestDeleteLeaf();
    TestDeleteOneChild();
    TestDeleteTwoChildren();
    TestDeleteRoot();
    TestDeleteTree();
    TestCopyConstructor();
    TestAssignmentOperator();
    TestInvariantChecker();

    cout << "\n=== ALL TESTS COMPLETE ===\n";
    return 0;
}
