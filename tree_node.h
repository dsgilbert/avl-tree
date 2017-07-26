
#ifndef TREE_NODE_H
#define TREE_NODE_H

#include <iostream>
#include <memory>
#include <utility>
using namespace std;

/**
 * A tree node class.
 * Author: Daniel Gilbert
 */
template <class T>
class tree_node {
    private:
        T key; /**< key. */
        tree_node<T>* parent; /**< parent. */
        unique_ptr<tree_node<T>>
            leftChild, /**< left child. */
            rightChild; /**< right child. */
    public:
        
        /**
         * Constructs a tree node with key keyP.
         * @param keyP the key
         */
        tree_node(T keyP) : key(keyP) {}
        
        /**
         * Returns the key.
         * @return the key
         */
        T getKey() { return key; }
        
        /**
         * Sets the parent.
         * @param parentP the parent
         * @see getParent()
         */
        void setParent(tree_node<T>* parentP) { parent = parentP; }
        
        /**
         * Returns the parent.
         * Returns nullptr if there is no parent.
         * @return the parent or nullptr if there is no parent.
         * @see setParent()
         */
        tree_node<T>* getParent() const { return parent; }
        
        /**
         * Sets the left child.
         * @param leftChildP the left child
         * @see getLeftChild()
         * @see getRightChild()
         * @see setRightChild()
         */
        void setLeftChild(unique_ptr<tree_node<T>> leftChildP)
            { leftChild = move(leftChildP); }
        
        /**
         * Sets the right child.
         * @param rightChildP the right child
         * @see getRightChild()
         * @see getLeftChild()
         * @see setLeftChild()
         */
        void setRightChild(unique_ptr<tree_node<T>> rightChildP)
            { rightChild = move(rightChildP); }
        
        /**
         * Returns the left child.
         * Returns nullptr if there is no left child.
         * @return the left child or nullptr if there is no left child
         * @see setLeftChild()
         * @see setRightChild()
         * @see getRightChild()
         */
        unique_ptr<tree_node<T>>& getLeftChild() { return leftChild; }
        
        /**
         * Returns the right child.
         * Returns nullptr if there is no right child. 
         * @return the right child or nullptr if there is no right child
         * @see setRightChild()
         * @see setLeftChild()
         * @see getLeftChild()
         */
        unique_ptr<tree_node<T>>& getRightChild() { return rightChild; }
        
        /**
         * Prints the values of all the tree nodes in the tree rooted at the
         * tree node in in-order.
         * @see printTreePreOrder()
         * @see printTreePostOrder()
         */
        void printTreeInOrder();
        
        /**
         * Prints the values of all the tree nodes in the tree rooted at the
         * tree node in pre-order.
         * @see printTreeInOrder()
         * @see printTreePostOrder()
         */
        void printTreePreOrder();
        
        /**
         * Prints the values of all the tree nodes in the tree rooted at the
         * tree node in post-order.
         * @see printTreeInOrder()
         * @see printTreePreOrder()
         */
        void printTreePostOrder();
        
        /**
         * Prints a visual representation of the tree.
         * @param depth the depth of the tree node which defaults to 0
         * @see printTreeInOrder()
         * @see printTreePreOrder()
         * @see printTreePostOrder()
         */
        void printTree(int depth = 0);
        
        /**
         * Returns the first tree node found with key keyP from the tree rooted
         * at the tree node.
         * Returns nullptr if a tree node with key keyP does not exist in the
         * tree rooted at the tree node.
         * @param keyP the key of the tree node to search for
         * @return the first tree node found with key keyP, or nullptr if such a
         * tree node does not exist
         */
        tree_node<T>* getNodeWithKey(T keyP);
        
        /**
         * Returns the minimum tree node from the tree rooted at the tree node.
         * @return the minimum tree node from the tree rooted at the tree node
         * @see getMaximumNode()
         */
        tree_node<T>* getMinimumNode();
        
        /**
         * Returns the maximum tree node from the tree rooted at the tree node.
         * @return the maximum tree node from the tree rooted at the tree node
         * @see getMinimumNode()
         */
        tree_node<T>* getMaximumNode();
        
        /**
         * Returns the in-order predecessor tree node of the tree node from the
         * whole tree.
         * Returns nullptr if the in-order predecessor tree node of the tree
         * node from the whole tree does not exist.
         * @return the in-order predecessor tree node, or nullptr if it does not
         * exist
         * @see getSuccessorNode()
         */
        tree_node<T>* getPredecessorNode();
        
        /**
         * Returns the in-order successor tree node of the tree node from the
         * whole tree.
         * Returns nullptr if the in-order successor tree node of the tree node
         * from the whole tree does not exist.
         * @return the in-order successor tree node, or nullptr if it does not
         * exist
         * @see getPredecessorNode()
         */
        tree_node<T>* getSuccessorNode();
};

template <class T>
void tree_node<T>::printTreeInOrder() {
    if (getLeftChild()) getLeftChild()->printTreeInOrder();
    cout << getKey() << " ";
    if (getRightChild()) getRightChild()->printTreeInOrder();
}

template <class T>
void tree_node<T>::printTreePreOrder() {
    cout << getKey() << " ";
    if (getLeftChild()) getLeftChild()->printTreeInOrder();
    if (getRightChild()) getRightChild()->printTreeInOrder();
}

template <class T>
void tree_node<T>::printTreePostOrder() {
    if (getLeftChild()) getLeftChild()->printTreeInOrder();
    if (getRightChild()) getRightChild()->printTreeInOrder();
    cout << getKey() << " ";
}

template <class T>
void tree_node<T>::printTree(int depth) {
    if (getRightChild()) getRightChild()->printTree(depth + 1);
    cout << string(depth, '\t') << getKey() << endl;
    if (getLeftChild()) getLeftChild()->printTree(depth + 1);
}

template <class T>
tree_node<T>* tree_node<T>::getNodeWithKey(T keyP) {
    tree_node<T>* currentNode = this;
    while (currentNode && keyP != currentNode->getKey()) {
        if (keyP < currentNode->getKey()) {
            currentNode = currentNode->getLeftChild().get();
        } else {
            currentNode = currentNode->getRightChild().get();
        }
    }
    return currentNode;
}

template <class T>
tree_node<T>* tree_node<T>::getMinimumNode() {
    tree_node<T>* currentNode = this;
    while (currentNode->getLeftChild()) {
        currentNode = currentNode->getLeftChild().get();
    }
    return currentNode;
}

template <class T>
tree_node<T>* tree_node<T>::getMaximumNode() {
    tree_node<T>* currentNode = this;
    while (currentNode->getRightChild()) {
        currentNode = currentNode->getRightChild().get();
    }
    return currentNode;
}

template <class T>
tree_node<T>* tree_node<T>::getPredecessorNode() {
    tree_node<T>* currentNode = this;
    if (currentNode->getLeftChild()) {
        return currentNode->getLeftChild()->getMaximumNode();
    }
    tree_node<T>* currentNodesParent = currentNode->getParent();
    while (currentNodesParent && 
           currentNode == currentNodesParent->getLeftChild().get()) {
        currentNode = currentNodesParent;
        currentNodesParent = currentNodesParent->getParent();
    }
    return currentNodesParent;
}

template <class T>
tree_node<T>* tree_node<T>::getSuccessorNode() {
    tree_node<T>* currentNode = this;
    if (currentNode->getRightChild()) {
        return currentNode->getRightChild()->getMinimumNode();
    }
    tree_node<T>* currentNodesParent = currentNode->getParent();
    while (currentNodesParent && 
           currentNode == currentNodesParent->getRightChild().get()) {
        currentNode = currentNodesParent;
        currentNodesParent = currentNodesParent->getParent();
    }
    return currentNodesParent;
}

#endif /* TREE_NODE_H */