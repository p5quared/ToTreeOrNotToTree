#pragma once

#include <string>
#include <iostream>
#include <stack>


namespace psv {

template<typename T>
struct Node {
    Node() : _count(), _left(nullptr), _right(nullptr), _parent(nullptr) {}

    ~Node() = default;

    explicit Node(T data) : _data(std::move(data)), _count(1), _left(nullptr), _right(nullptr), _parent(nullptr) {}

    T _data;
    int _count;
    Node *_left;
    Node *_right;
    Node *_parent;
};

template<typename T>
class Tree {
public:
    Tree() = default;
    virtual ~Tree();
    virtual void print() const;

    void insert(const T &data);
    void remove(const T &data);

    struct Iterator {
        using iterator_category = std::forward_iterator_tag;
        using value_type = Node<T>;
        using pointer = Node<T>*;
        using reference = Node<T>&;
        explicit Iterator(Node<T>* start) : _curr(start) {}

        reference operator*() const { return *_curr; }
        pointer operator->() { return _curr; }

        Iterator& operator++();

        friend bool operator==(const Iterator &a, const Iterator &b) {return a._curr == b._curr;}
        friend bool operator!=(const Iterator &a, const Iterator &b) {return a._curr != b._curr;}
    private:
        pointer _curr{};
    };
    Iterator begin() const {return Iterator(this->_leftMost(_root));}
    Iterator end() const {return Iterator(nullptr);}

protected:
    Node<T> *_root;


private:
    void _delete(Node<T> *&node);
    virtual void _insert(Node<T> *&node,Node<T> *parent, const T &data);
    void _print(Node<T> *node) const;
    void _remove(Node<T> *&node, const T &data);
    Node<T>* _leftMost(Node<T> *node) const;
};

template<typename T>
Node<T>* Tree<T>::_leftMost(Node<T> *node) const {
    if (node == nullptr) {
        return nullptr;
    }
    while (node->_left != nullptr) {
        node = node->_left;
    }
    return node;
}


template<typename T>
void Tree<T>::insert(const T &data) {
    _insert(_root,nullptr, data);
}

template<typename T>
void Tree<T>::_insert(Node<T> *&node, Node<T> *parent, const T &data) {
    if (node == nullptr) {
        node = new Node(data);
        node->_parent = parent;
        return;
    }
    if (node->_data == data) {
        node->_count++;
        return;
    }
    if (node->_data > data) {
        _insert(node->_left, node, data);
    } else {
        _insert(node->_right,node, data);
    }
}


template<typename T>
void Tree<T>::remove(const T &data) {
    _remove(_root, data);
}

template<typename T>
void Tree<T>::_remove(Node<T> *&node, const T &data) {
    if (node == nullptr) { // not found
        return;
    }
    if (node->_data > data) {
        _remove(node->_left, data);
        return;
    }
    if (node->_data < data) {
        _remove(node->_right, data);
        return;
    }
    // found
    if (node->_count > 1) {
        node->_count--;
        return;
    }
    // node->_count == 1
    if (node->_left == nullptr && node->_right == nullptr) {
        delete node;
        node = nullptr;
        return;
    }
    if (node->_left == nullptr) {
        Node<T> *temp = node;
        node = node->_right;
        delete temp;
        return;
    } else if (node->_right == nullptr) {
        Node<T> *temp = node;
        node = node->_left;
        delete temp;
        return;
    }
    // node has two children
    Node<T> *temp = node->_right;
    while (temp->_left != nullptr) {
        temp = temp->_left;
    }
    node->_data = temp->_data;
    node->_count = temp->_count;
    _remove(node->_right, temp->_data);
}


template<typename T>
void Tree<T>::print() const {
    _print(_root);
}

template<typename T>
void Tree<T>::_print(Node<T> *node) const {
    if (node == nullptr) {
        return;
    }
    _print(node->_left);
    std::cout << node->_data << std::endl;
    _print(node->_right);
}


template<typename T>
Tree<T>::~Tree() {
    _delete(_root);
}

template<typename T>
void Tree<T>::_delete(Node<T> *&node) {
    if (node == nullptr) {
        return;
    }
    _delete(node->_left);
    _delete(node->_right);
    delete node;
}

template<typename T>
typename Tree<T>::Iterator& Tree<T>::Iterator::operator++() {
    if (_curr->_right != nullptr) {
        _curr = _curr->_right;
        while (_curr->_left != nullptr) {
            _curr = _curr->_left;
        }
        return *this;
    }
    Node<T> *temp = _curr->_parent;
    while (temp != nullptr && _curr == temp->_right) {
        _curr = temp;
        temp = temp->_parent;
    }
    _curr = temp;
    return *this;
}

} // namespace psv

