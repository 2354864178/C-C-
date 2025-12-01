// Minimal, correct binary tree implementation for tests
#pragma once
#include "BinNode.hpp"
#include <algorithm>

void run_bintree_test();
template <typename T>
class BinTree {
protected:
    int _size = 0;
    BinNodePosi(T) _root = nullptr;

    virtual int updateHeight(BinNodePosi(T) x) {
        if (!x) return -1;
        x->height = 1 + std::max((x->lchild ? x->lchild->height : -1), (x->rchild ? x->rchild->height : -1));
        return x->height;
    }

    void updateHeightAbove(BinNodePosi(T) x) {
        while (x) {
            updateHeight(x);
            x = x->parent;
        }
    }

public:
    BinTree() = default;
    ~BinTree() { remove(_root); }

    int size() const { return _size; }
    bool empty() const { return _size == 0; }

    BinNodePosi(T) root() const { return _root; }

    BinNodePosi(T) insertAsRoot(const T& e) {
        if (_root) return nullptr; // already has root
        _root = new BinNode<T>(e);
        _size = 1;
        updateHeightAbove(_root);
        return _root;
    }

    BinNodePosi(T) insertAsLC(BinNodePosi(T) x, const T& e) {
        ++_size;
        return x->insertAsLC(e);
    }

    BinNodePosi(T) insertAsRC(BinNodePosi(T) x, const T& e) {
        ++_size;
        return x->insertAsRC(e);
    }

    template <typename VST>
    void travPre(const VST& visit) { if (_root) _root->travPre(visit); }
    template <typename VST>
    void travIn(const VST& visit) { if (_root) _root->travIn(visit); }
    template <typename VST>
    void travPost(const VST& visit) { if (_root) _root->travPost(visit); }

    // remove subtree rooted at x, return number of removed nodes
    int remove(BinNodePosi(T) x) {
        if (!x) return 0;
        // detach from parent
        if (x->parent) {
            if (x->parent->lchild == x) x->parent->lchild = nullptr;
            else if (x->parent->rchild == x) x->parent->rchild = nullptr;
            updateHeightAbove(x->parent);
        } else {
            _root = nullptr;
        }
        int n = removeAt(x);
        _size -= n;
        return n;
    }

    BinTree<T>* secede(BinNodePosi(T) x) {
        if (!x) return nullptr;
        // detach
        if (x->parent) {
            if (x->parent->lchild == x) x->parent->lchild = nullptr;
            else if (x->parent->rchild == x) x->parent->rchild = nullptr;
            updateHeightAbove(x->parent);
        } else {
            _root = nullptr;
        }
        BinTree<T>* S = new BinTree<T>();
        S->_root = x;
        x->parent = nullptr;
        S->_size = x->size();
        _size -= S->_size;
        return S;
    }

private:
    static int removeAt(BinNodePosi(T) x) {
        if (!x) return 0;
        int n = 1;
        n += removeAt(x->lchild);
        n += removeAt(x->rchild);
        delete x;
        return n;
    }
};
