#ifndef BST_H_INCLUDED
#define BST_H_INCLUDED

#include <iostream>
using std::cout;
using std::endl;

/**
 * @class Bst
 * @brief A templated Binary Search Tree (BST) implementation.
 *
 * This class stores elements in a binary search tree structure, allowing
 * fast insertion, lookup, deletion, and depth-first traversals. Values
 * stored in the tree must support the <, >, and == comparison operators.
 *
 * Supported operations:
 * - Insert a new value
 * - Search for a value
 * - Delete a specific value
 * - Clear the entire tree
 * - In-order, pre-order, and post-order traversal
 *
 * @tparam T Type of elements stored in the BST.
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
     * @brief Destructor.
     *
     * Recursively deallocates all nodes in the tree.
     */
    ~Bst();

    /**
     * @brief Copy constructor.
     *
     * Creates a deep copy of another BST.
     *
     * @param other Tree to copy.
     */
    Bst(const Bst& other);

    /**
     * @brief Copy assignment operator.
     *
     * Replaces the contents of this BST with a deep copy of @p other.
     *
     * @param other Tree to copy from.
     * @return Reference to this instance.
     */
    Bst& operator=(const Bst& other);

    /**
     * @brief Inserts a value into the BST.
     *
     * Duplicate values are ignored and not inserted.
     *
     * @param value The value to insert.
     */
    void Insert(const T& value);

    /**
     * @brief Searches for a value in the BST.
     *
     * @param value The value to locate.
     * @return True if the value exists, false otherwise.
     */
    bool Search(const T& value) const;

    /**
     * @brief Removes all nodes in the tree and resets it to empty.
     */
    void DeleteTree();

    /**
     * @brief Deletes a node containing the specified value.
     *
     * If the value does not exist, no changes are made.
     *
     * @param value The value to remove.
     */
    void DeleteNode(const T& value);

    /**
     * @brief Performs an in-order traversal.
     *
     * Order: **Left → Root → Right**
     * Produces sorted output if the BST contains no duplicates.
     *
     * @param func Function applied to each visited node's value.
     */
    void InOrder(void (*func)(const T&)) const;

    /**
     * @brief Performs a pre-order traversal.
     *
     * Order: **Root → Left → Right**
     *
     * @param func Function applied to each visited node's value.
     */
    void PreOrder(void (*func)(const T&)) const;

    /**
     * @brief Performs a post-order traversal.
     *
     * Order: **Left → Right → Root**
     *
     * @param func Function applied to each visited node's value.
     */
    void PostOrder(void (*func)(const T&)) const;

private:

    /**
     * @struct Node
     * @brief Represents a single BST node.
     */
    struct Node
    {
        T data;        ///< Value stored at this node.
        Node* left;    ///< Pointer to the left child.
        Node* right;   ///< Pointer to the right child.
    };

    Node* root; ///< Pointer to the root of the BST.

    /**
     * @brief Recursive insert helper.
     * @param node Current subtree root.
     * @param value Value to insert.
     * @return Updated subtree root pointer.
     */
    Node* insert(Node* node, const T& value);

    /**
     * @brief Recursive search helper.
     * @param node Current subtree root.
     * @param value Value to locate.
     * @return True if the value is found.
     */
    bool search(Node* node, const T& value) const;

    /**
     * @brief Recursive in-order traversal helper.
     */
    void inOrder(const Node* node, void (*func)(const T&)) const;

    /**
     * @brief Recursive pre-order traversal helper.
     */
    void preOrder(const Node* node, void (*func)(const T&)) const;

    /**
     * @brief Recursive post-order traversal helper.
     */
    void postOrder(const Node* node, void (*func)(const T&)) const;

    /**
     * @brief Recursive destroy helper.
     * @param node Subtree root to delete.
     */
    void deleteTree(Node* node);

    /**
     * @brief Recursive delete-node helper.
     * @param node Current subtree root.
     * @param value Value to remove.
     * @return Updated subtree root pointer.
     */
    Node* deleteNode(Node* node, const T& value);

    /**
     * @brief Recursively clones a subtree.
     * @param node Root of the subtree to clone.
     * @return New subtree root.
     */
    Node* copyTree(Node* node);
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
}

template <class T>
void Bst<T>::inOrder(const Node* node,void (*func)(const T&)) const
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
}

template <class T>
void Bst<T>::preOrder(const Node* node,void (*func)(const T&)) const
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
}

template <class T>
void Bst<T>::postOrder(const Node* node,void (*func)(const T&)) const
{
    if (node)
    {
        postOrder(node->left, func);
        postOrder(node->right, func);
        func(node->data);
    }
}

#endif // BST_H_INCLUDED
