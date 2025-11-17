#ifndef BST_H_INCLUDED
#define BST_H_INCLUDED

#include <iostream>
using std::cout;
using std::endl;

/**
 * @class Bst
 * @brief A templated Binary Search Tree (BST) class.
 *
 * This class provides functionality for storing elements in a binary search tree
 * structure. Supported operations include insertion, searching, deletion,
 * and depth-first traversals (in-order, pre-order, post-order).
 *
 * The type T must support <, >, and == comparison operators.
 *
 * @tparam T Data type stored inside the BST.
 */
template <class T>
class Bst
{
public:
    /**
     * @brief Constructs an empty BST.
     */
    Bst();

    /**
     * @brief Destructor. Recursively frees all nodes.
     */
    ~Bst();

    /**
     * @brief Copy constructor. Performs a deep copy.
     * @param other The BST to copy.
     */
    Bst(const Bst& other);

    /**
     * @brief Copy assignment operator. Performs deep copy with cleanup.
     * @param other The BST to assign from.
     * @return Reference to *this.
     */
    Bst& operator=(const Bst& other);

    /**
     * @brief Inserts a new value into the BST.
     *
     * Duplicate values are ignored.
     *
     * @param value The value to insert.
     */
    void Insert(const T& value);

    /**
     * @brief Searches for a value in the BST.
     * @param value The value to locate.
     * @return True if found, false otherwise.
     */
    bool Search(const T& value) const;

    /**
     * @brief Removes all nodes and resets the tree to empty.
     */
    void DeleteTree();

    /**
     * @brief Deletes a node containing the specified value.
     * @param value Value to remove.
     */
    void DeleteNode(const T& value);

    /**
     * @brief Performs in-order traversal.
     *
     * Order: Left → Root → Right
     *
     * @param func A function pointer applied to each visited value.
     */
    void InOrder(void (*func)(const T&)) const;

    /**
     * @brief Performs pre-order traversal.
     *
     * Order: Root → Left → Right
     *
     * @param func A function pointer applied to each visited value.
     */
    void PreOrder(void (*func)(const T&)) const;

    /**
     * @brief Performs post-order traversal.
     *
     * Order: Left → Right → Root
     *
     * @param func A function pointer applied to each visited value.
     */
    void PostOrder(void (*func)(const T&)) const;

    /**
     * @brief Ensures the BST invariant holds for all nodes.
     *
     * BST property checked:
     * - Left subtree values < node value
     * - Right subtree values > node value
     *
     * @return True if invariant is satisfied.
     */
    bool DebugCheckInvariant() const;

private:

    /**
     * @struct Node
     * @brief Represents a single node in the BST.
     */
    struct Node
    {
        T data;        ///< Value stored at this node.
        Node* left;    ///< Pointer to left subtree.
        Node* right;   ///< Pointer to right subtree.
    };

    Node* root;  ///< Pointer to the root of the tree.

    // ====================== Helper Functions ======================

    /**
     * @brief Recursive insert helper.
     * @param node Current subtree root.
     * @param value Value to insert.
     * @return Updated subtree root.
     */
    Node* insert(Node* node, const T& value);

    /**
     * @brief Recursive search helper.
     * @param node Current subtree root.
     * @param value Value to find.
     * @return True if found.
     */
    bool search(Node* node, const T& value) const;

    /**
     * @brief Recursive in-order traversal helper.
     * @param node Current subtree root.
     * @param func Function applied to each node value.
     */
    void inOrder(Node* node, void (*func)(const T&)) const;

    /**
     * @brief Recursive pre-order traversal helper.
     * @param node Current subtree root.
     * @param func Function applied to each node value.
     */
    void preOrder(Node* node, void (*func)(const T&)) const;

    /**
     * @brief Recursive post-order traversal helper.
     * @param node Current subtree root.
     * @param func Function applied to each node value.
     */
    void postOrder(Node* node, void (*func)(const T&)) const;

    /**
     * @brief Recursive destroy helper.
     * @param node Current subtree root.
     */
    void deleteTree(Node* node);

    /**
     * @brief Recursive node deletion helper.
     * @param node Current subtree root.
     * @param value Value to remove.
     * @return Updated subtree root.
     */
    Node* deleteNode(Node* node, const T& value);

    /**
     * @brief Recursively clones a subtree.
     * @param node Subtree root to copy.
     * @return Pointer to new cloned subtree.
     */
    Node* copyTree(Node* node);

    /**
     * @brief Recursive helper to validate BST ordering.
     * @param node Current subtree root.
     * @return True if subtree satisfies BST rules.
     */
    bool checkInvariant(Node* node) const;
};

// --- Implementation ---

template <class T>
Bst<T>::Bst()
{
    root = nullptr;
}

template <class T>
Bst<T>::~Bst()
{
    deleteTree(root);
    root = nullptr;
}
template <class T>
Bst<T>::Bst(const Bst& other)
{
    root = copyTree(other.root);
}

template <class T>
typename Bst<T>::Node* Bst<T>::copyTree(Node* node)
{
    if (!node)
    {
        return nullptr;
    }
    Node* newNode = new Node{node->data, nullptr, nullptr};
    newNode->left = copyTree(node->left);
    newNode->right = copyTree(node->right);
    return newNode;
}

template <class T>
Bst<T>& Bst<T>::operator=(const Bst& other)
{
    if (this != &other)  // protect against self-assignment
    {
        deleteTree(root);
        root = copyTree(other.root);
    }
    return *this;
}

template <class T>
void Bst<T>::Insert(const T& value)
{
    root = insert(root, value);
}

template <class T>
typename Bst<T>::Node* Bst<T>::insert(Node* node, const T& value)
{
    if (node == nullptr)
    {
        node = new Node{value, nullptr, nullptr};
    }
    else if (value < node->data)
    {
        node->left = insert(node->left, value);
    }
    else if (value > node->data)
    {
        node->right = insert(node->right, value);
    }
    return node;
}

template <class T>
bool Bst<T>::Search(const T& value) const
{
    return search(root, value);
}

template <class T>
bool Bst<T>::search(Node* node, const T& value) const
{
    if (node == nullptr)
    {
        return false;
    }
    else if (value == node->data)
    {
        return true;
    }
    else if (value < node->data)
    {
        return search(node->left, value);
    }
    else
    {
        return search(node->right, value);
    }
}

template <class T>
void Bst<T>::DeleteTree()
{
    deleteTree(root);
    root = nullptr;
}

template <class T>
void Bst<T>::deleteTree(Node* node)
{
    if (node)
    {
        deleteTree(node->left);
        deleteTree(node->right);
        delete node;
    }
}

template <class T>
void Bst<T>::DeleteNode(const T& value)
{
    root = deleteNode(root, value);
}

template <class T>
typename Bst<T>::Node* Bst<T>::deleteNode(Node* node, const T& value)
{
    if (node == nullptr)
    {
        return nullptr;
    }

    if (value < node->data)
    {
        node->left = deleteNode(node->left, value);
    }
    else if (value > node->data)
    {
        node->right = deleteNode(node->right, value);
    }
    else
    {
        // Case 1: Leaf
        if (node->left == nullptr && node->right == nullptr)
        {
            delete node;
            node = nullptr;
        }
        // Case 2: One child
        else if (node->left == nullptr)
        {
            Node* temp = node->right;
            delete node;
            node = temp;
        }
        else if (node->right == nullptr)
        {
            Node* temp = node->left;
            delete node;
            node = temp;
        }
        // Case 3: Two children
        else
        {
            Node* successor = node->right;
            while (successor->left != nullptr)
            {
                successor = successor->left;
            }
            node->data = successor->data;
            node->right = deleteNode(node->right, successor->data);
        }
    }
    return node;
}

template <class T>
void Bst<T>::InOrder(void (*func)(const T&)) const
{
    inOrder(root, func);
    cout << endl;
}

template <class T>
void Bst<T>::inOrder(Node* node,void (*func)(const T&)) const
{
    if (node)
    {
        inOrder(node->left, func);
        func(node->data);
        inOrder(node->right, func);
    }
}

template <class T>
void Bst<T>::PreOrder(void (*func)(const T&)) const
{
    preOrder(root, func);
    cout << endl;
}

template <class T>
void Bst<T>::preOrder(Node* node,void (*func)(const T&)) const
{
    if (node)
    {
        func(node->data);
        preOrder(node->left, func);
        preOrder(node->right, func);
    }
}

template <class T>
void Bst<T>::PostOrder(void (*func)(const T&)) const
{
    postOrder(root, func);
    cout << endl;
}

template <class T>
void Bst<T>::postOrder(Node* node,void (*func)(const T&)) const
{
    if (node)
    {
        postOrder(node->left, func);
        postOrder(node->right, func);
        func(node->data);
    }
}

template <class T>
bool Bst<T>::DebugCheckInvariant() const
{
    return checkInvariant(root);
}

template <class T>
bool Bst<T>::checkInvariant(Node* node) const
{
    if (node == nullptr)
    {
        return true;
    }

    if (node->left && node->left->data >= node->data)
    {
        return false;
    }
    if (node->right && node->right->data <= node->data)
    {
        return false;
    }

    return checkInvariant(node->left) && checkInvariant(node->right);
}


#endif // BST_H_INCLUDED
