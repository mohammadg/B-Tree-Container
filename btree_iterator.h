#ifndef BTREE_ITERATOR_H
#define BTREE_ITERATOR_H

#include <iterator>

/**
 * You MUST implement the btree iterators as (an) external class(es) in this file.
 * Failure to do so will result in a total mark of 0 for this deliverable.
 **/

// iterator related interface stuff here; would be nice if you called your
// iterator class btree_iterator (and possibly const_btree_iterator)


template <typename T> class btree;
template <typename T> class const_btree_iterator;

template <typename T>
class btree_iterator {
public:
  friend class const_btree_iterator<T>;

  typedef ptrdiff_t difference_type;
  typedef std::bidirectional_iterator_tag	iterator_category;
  typedef T value_type;
  typedef T* pointer;
  typedef T& reference;

  bool operator==(const btree_iterator<T>&) const;
  bool operator!=(const btree_iterator<T>& other) const { return !operator==(other); }

  reference operator*() const;
  pointer operator->() const { return &(operator*()); }
  btree_iterator<T>& operator=(const btree_iterator<T>&);
  btree_iterator<T>& operator++();
  btree_iterator<T>& operator++(int);
  btree_iterator<T>& operator--();
  btree_iterator<T>& operator--(int);

  btree_iterator() {};

  btree_iterator(typename btree<T>::Node *n,
    typename std::map<T, typename btree<T>::Element>::iterator it)
    : node(n), it(it) {}

private:
  //Store a current node as well as a map iterator
  //This will be the underlying implementation of our iterator
  typename btree<T>::Node *node;
  typename std::map<T, typename btree<T>::Element>::iterator it;
  bool didTraverse = false; //boolean true if last iteration traversed upwards (in the btree)

  //Helper functions
  void forward_traverse_down(typename btree<T>::Node*,
    typename std::map<T, typename btree<T>::Element>::iterator&);
  void forward_traverse_up(typename btree<T>::Node*,
    typename std::map<T, typename btree<T>::Element>::iterator&);
  
  void reverse_traverse_down(typename btree<T>::Node*,
    typename std::map<T, typename btree<T>::Element>::iterator&);
  void reverse_traverse_up(typename btree<T>::Node*,
    typename std::map<T, typename btree<T>::Element>::iterator&);
};

template <typename T>
class const_btree_iterator {
public:
  typedef ptrdiff_t difference_type;
  typedef std::bidirectional_iterator_tag iterator_category;
  typedef T value_type;
  typedef const T* pointer;
  typedef const T& reference;

  bool operator==(const const_btree_iterator&) const;
  bool operator!=(const const_btree_iterator& other) const { return !operator==(other); }

  bool operator==(const btree_iterator<T>&) const;
  bool operator!=(const btree_iterator<T>& other) const { return !operator==(other);}

  reference operator*() const;
  pointer operator->() const { return &(operator*()); }
  const_btree_iterator& operator=(const const_btree_iterator<T>&);
  const_btree_iterator& operator++();
  const_btree_iterator& operator++(int);
  const_btree_iterator& operator--();
  const_btree_iterator& operator--(int);
  
  const_btree_iterator() {};

  //Allow seemless conversion of btree_iterator to const_btree_iterator
  const_btree_iterator(const btree_iterator<T>& it) : const_btree_iterator(it.node, it.it) {};

  const_btree_iterator(const typename btree<T>::Node *n,
    typename std::map<T, typename btree<T>::Element>::const_iterator it)
    : node(n), it(it) {}

private:
  //Store a current node as well as a map iterator
  //This will be the underlying implementation of our iterator
  const typename btree<T>::Node *node;
  typename std::map<T, typename btree<T>::Element>::const_iterator it;
  bool didTraverse = false; //boolean true if last iteration traversed upwards (in the btree)

  //Helper functions
  void forward_traverse_down(const typename btree<T>::Node*,
    typename std::map<T, typename btree<T>::Element>::const_iterator&);
  void forward_traverse_up(const typename btree<T>::Node*,
    typename std::map<T, typename btree<T>::Element>::const_iterator&);

  void reverse_traverse_down(const typename btree<T>::Node*,
    typename std::map<T, typename btree<T>::Element>::const_iterator&);
  void reverse_traverse_up(const typename btree<T>::Node*,
    typename std::map<T, typename btree<T>::Element>::const_iterator&);
};

#include "btree_iterator.cpp"

#endif