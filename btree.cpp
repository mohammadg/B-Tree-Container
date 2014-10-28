/*
 *  B-Tree implementation
 *
 * Author: Mohammad Ghasembeigi
*/

//TEMP!!!!! remove after
#include "btree.h"

/*
* Copy Semantics
*/
template <typename T>
btree<T>::btree(const btree<T>& original) {
  maxElements = original.maxElements;
  root = original.root;

  //Recursively copy binary tree
  copyBTree(original.root, root);
}

//Helper Function: Copy nodes in btree recursively
template <typename T>
void btree<T>::copyBTree(Node *source, Node *dest) {
  //Iterate over node
  for(std::map<T, Element>::iterator it = source.elements.begin(); it != source.elements.end(); ++it) {
    //Copy values from this node

  }
}

/*
* Move Semantics
*/
template <typename T>
btree<T>::btree(btree<T>&& original) {

}

/*
 * Operater= Copy Semantics 
*/
template <typename T>
btree<T>& btree<T>::operator=(const btree<T>& rhs) {
  btree<T> *b = new btree<T>(rhs);
  return *b;
}

/*
* Operater= Move Semantics
*/
template <typename T>
btree<T>& btree<T>::operator=(btree<T>&& rhs) {
  btree<T> b = std::move(rhs);
  return b;
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const btree<T>& tree) {

}

template <typename T>
typename btree<T>::iterator btree<T>::find(const T& elem) {
  
}

template <typename T>
typename btree<T>::const_iterator btree<T>::find(const T& elem) const {
  
}

/*
* Insert elements into the BTree
*
* Returns: A pair consisting of an iterator positioned at the element inserted and a boolean indicating the 
* success of insertion.
*/
template <typename T>
std::pair<typename btree<T>::iterator, bool> btree<T>::insert(const T& elem) {
  return recursiveInsert(&root, &root, elem);
}

template <typename T>
std::pair<typename btree<T>::iterator, bool> btree<T>::recursiveInsert(Node *node, Node *parent, const T& elem) {

  //Iterate over node elements
  for (auto it = node->elements.begin(); it != node->elements.end(); ++it) {
    //Create boolean for final iteration special case
    bool finalIteration = false;

    if (it == --node->elements.end())
      finalIteration = true;

    //cout << &node.elements.begin() << " | " << &node.elements.end() << endl;

    //Keep traversing while elem < it's element and not equal to it
    if (elem == it->first) {
      //Exact match found, return pair
      return pair<typename btree<T>::iterator, bool>(btree<T>::iterator(), false);
    }
    //If elem is less than element or this is the last element, we must insert or expand here
    else if (elem < it->first || finalIteration) {

      //We can insert the element at this location in this node if there is space
      if (node->elements.size() < maxElements) {
        //Create new element
        Element e;
        e.value = elem;
        e.leftChild = nullptr;
        e.rightChild = nullptr;
        node->elements.insert(pair<T, Element>(elem, e));

        return pair<typename btree<T>::iterator, bool>(btree<T>::iterator(), true);
      }
      //Otherwise, recursively analyse the left or right child
      else {
        Node *child = it->second.leftChild;
        
        //Select right child for the last element if elem is bigger
        if (finalIteration && elem > it->first)
          child = it->second.rightChild;

        //If child is empty node
        if (child == nullptr) {
          //Create new node
          child = new Node(parent);

          //Set pointers to child node
          if (finalIteration && elem > it->first)
            it->second.rightChild = child;
          else
            it->second.leftChild = child;
        }
        
        return recursiveInsert(child, node, elem);
      }
    }
  }

  //No elements in the node, we must add the new element
  //Create new element
  Element e;
  e.value = elem;
  e.leftChild = nullptr;
  e.rightChild = nullptr;
  node->elements.insert(pair<T, Element>(elem, e));

  return pair<typename btree<T>::iterator, bool>(btree<T>::iterator(), true);

}

template <typename T>
btree<T>::~btree() {

}

