#include "Bst.h"
#include <iostream>
using namespace std;

// -----------------------------------------------------
// Simple print function for traversal (function pointer)
// -----------------------------------------------------
void PrintValue(const int& val)
{
    cout << val << " ";
}

// -----------------------------------------------------
// Tests passing by const reference
// -----------------------------------------------------
void PrintTreeConstRef(const Bst<int>& t)
{
    cout << "Const-ref inorder: ";
    t.InOrder(PrintValue);
    cout << endl;
}

// -----------------------------------------------------
// Tests passing by reference (modifies tree)
// -----------------------------------------------------
void InsertIntoTreeRef(Bst<int>& t)
{
    t.Insert(999);
    t.Insert(-50);
}

// -----------------------------------------------------
// Tests pass-by-value (copy constructor usage)
// -----------------------------------------------------
void PrintTreeByValue(Bst<int> t)
{
    cout << "Pass-by-value inorder (copy): ";
    t.InOrder(PrintValue);
    cout << endl;
}

// -----------------------------------------------------
// Main Tester
// -----------------------------------------------------
int main()
{
    // =====================================================
    // 1. Basic Insertion
    // =====================================================
    Bst<int> tree;
    tree.Insert(10);
    tree.Insert(5);
    tree.Insert(15);
    tree.Insert(3);
    tree.Insert(7);
    tree.Insert(13);
    tree.Insert(20);

    cout << "--- BASIC TREE CONTENTS ---\n";
    cout << "InOrder:   ";
    tree.InOrder(PrintValue);
    cout << "\nPreOrder:  ";
    tree.PreOrder(PrintValue);
    cout << "\nPostOrder: ";
    tree.PostOrder(PrintValue);
    cout << "\n\n";

    // =====================================================
    // 2. Debug invariant check
    // =====================================================
    cout << "Check invariant: "
         << (tree.DebugCheckInvariant() ? "OK" : "BROKEN") << "\n\n";

    // =====================================================
    // 3. Test Search()
    // =====================================================
    cout << "--- SEARCH TEST ---\n";
    cout << "Search 7:  " << (tree.Search(7) ? "Found" : "Not Found") << endl;
    cout << "Search 99: " << (tree.Search(99) ? "Found" : "Not Found") << endl;
    cout << endl;

    // =====================================================
    // 4. Test DeleteNode()
    // =====================================================
    cout << "--- DELETE TEST ---\n";

    tree.DeleteNode(5);  // delete a node with 2 children
    tree.DeleteNode(20); // delete a leaf
    tree.DeleteNode(13); // delete node with 1 child

    cout << "Tree after deletions (inorder): ";
    tree.InOrder(PrintValue);
    cout << endl;

    cout << "Invariant after deletions: "
         << (tree.DebugCheckInvariant() ? "OK" : "BROKEN") << "\n\n";

    // =====================================================
    // 5. Test Copy Constructor
    // =====================================================
    cout << "--- COPY CONSTRUCTOR TEST ---\n";
    Bst<int> copyTree(tree);        // deep copy
    cout << "Original inorder: ";
    tree.InOrder(PrintValue);
    cout << "\nCopy inorder:     ";
    copyTree.InOrder(PrintValue);
    cout << "\n\n";

    // modify copyTree and ensure original remains unchanged
    copyTree.Insert(777);

    cout << "After modifying copy:\n";
    cout << "Original inorder: ";
    tree.InOrder(PrintValue);
    cout << "\nCopy inorder:     ";
    copyTree.InOrder(PrintValue);
    cout << "\n\n";

    // =====================================================
    // 6. Test Copy Assignment Operator
    // =====================================================
    cout << "--- COPY ASSIGNMENT TEST ---\n";
    Bst<int> assigned;
    assigned = tree; // operator=

    cout << "Assigned inorder: ";
    assigned.InOrder(PrintValue);
    cout << "\n\n";

    assigned.Insert(-123);

    cout << "After modifying assigned:\n";
    cout << "Original inorder: ";
    tree.InOrder(PrintValue);
    cout << "\nAssigned inorder: ";
    assigned.InOrder(PrintValue);
    cout << "\n\n";

    // =====================================================
    // 7. Pass-by-const-reference test
    // =====================================================
    cout << "--- PASS BY CONST REF TEST ---\n";
    PrintTreeConstRef(tree);
    cout << endl;

    // =====================================================
    // 8. Pass-by-reference test (modification)
    // =====================================================
    cout << "--- PASS BY REF TEST ---\n";
    InsertIntoTreeRef(tree); // modifies the original
    cout << "Tree after ref function: ";
    tree.InOrder(PrintValue);
    cout << "\n\n";

    // =====================================================
    // 9. Pass-by-value test (copy constructor again)
    // =====================================================
    cout << "--- PASS BY VALUE TEST ---\n";
    PrintTreeByValue(tree);
    cout << endl;

    // =====================================================
    // 10. Delete entire tree
    // =====================================================
    cout << "--- DELETE ENTIRE TREE ---\n";
    tree.DeleteTree();

    cout << "Tree after DeleteTree(): ";
    tree.InOrder(PrintValue); // should print nothing
    cout << endl;

    cout << "Invariant after full delete: "
         << (tree.DebugCheckInvariant() ? "OK" : "BROKEN") << endl;

    cout << "\n===== FULL BST TEST COMPLETE =====\n";

    return 0;
}
