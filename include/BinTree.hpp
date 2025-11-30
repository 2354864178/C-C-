#pragma once
#include "BinNode.hpp"
#include "Stack_and_Quene.hpp"

template <typename T> 
class BinTree{
protected:
    int _size;              //  规模
    BinNodePosi(T) _root;   //    根节点
    virtual int updateHeight(BinNodePosi(T) x); //  更新节点x的高度
    void updateHeightAbove(BinNodePosi(T) x);   //  更新节点x及其祖先的高度

public:
    BinNodePosi(T) insertAsRoot(T const& e);    //  根节点插入
    BinNodePosi(T) insertAsLC(BinNodePosi(T) x, T const& e);    //  左孩子插入
    BinNodePosi(T) insertAsRC(BinNodePosi(T) x, T const& e);    //  右孩子插入
    BinNodePosi(T) attachAsLC(BinNodePosi(T) x, BinTree<T>* &S);    //  左子树插入
    BinNodePosi(T) attachAsRC(BinNodePosi(T) x, BinTree<T>* &S);    //  右子树插入
    int remove(BinNodePosi(T) x);   //  子树删除
    BinTree<T>* BinTree<T>::secede(BinNodePosi(T) x);   //  子树分离
    template <typename VST> 
    void travPre(VST& visit) {if(_root) _root->travPre(visit);}     //  先序遍历
    template <typename VST> 
    void travIn(VST& visit) {if(_root) _root->travIn(visit);}       //  中序遍历
    template <typename VST>
    void travPost(VST& visit) {if(_root) _root->travPost(visit);}   //  后序遍历
    bool operator== (BinTree<T> const& t)
    {return _root && t._root && ( _root == t._root );}
};

template <typename T> 
int BinTree<T>::updateHeight(BinNodePosi(T) x){
    return x->height = 1 + max (stature(x->lc), stature(x->rc));
}

template <typename T> 
void BinTree<T>::updateHeightAbove(BinNodePosi(T) x){
    while(x){
        this->updateHeight(x);
        x = x->parent;
    }
}

template <typename T>
BinNodePosi(T) BinTree<T>::insertAsRoot(T const& e){
    BinNodePosi(T) x = new BinNode<T>(e);
    this->_root = x;
    this->_size = 1;
    this->updateHeightAbove(x);
    return x;
}

template <typename T>
BinNodePosi(T) BinTree<T>::insertAsLC(BinNodePosi(T) x, T const& e){
    this->_size++;
    x->insertAsLC(e);
    this->updateHeightAbove(x);
    return x->lchild;
}

template <typename T>
BinNodePosi(T) BinTree<T>::insertAsRC(BinNodePosi(T) x, T const& e){
    this->_size++;
    x->insertAsRC(e);
    this->updateHeightAbove(x);
    return x->rchild;
}

template <typename T>
BinNodePosi(T) BinTree<T>::attachAsLC(BinNodePosi(T) x, BinTree<T>* &S){
    x->lchild = S->_root;
    if(x->lchild) x->lchild->parent = x;
    this->_size += S->_size;
    this->updateHeightAbove(x);
    S->_root = NULL; 
    S->_size = 0; 
    release(S); 
    S = NULL; 
    return x;
}

template <typename T>
BinNodePosi(T) BinTree<T>::attachAsRC(BinNodePosi(T) x, BinTree<T>* &S){
    x->rchild = S->_root;
    if(x->rchild) x->rchild->parent = x;
    this->_size += S->_size;
    this->updateHeightAbove(x);
    S->_root = NULL; 
    S->_size = 0; 
    release(S); 
    S = NULL; 
    return x;
}

template <typename T>
int BinTree<T>::remove(BinNodePosi(T) x){
    FromParentTo(*x) = NULL;
    this->updateHeightAbove(x->parent);
    int n = removeAt (x);
     _size -= n; 
     return n; 
}

template <typename T> 
static int removeAt(BinNodePosi(T) x){ 
    if(!x) return 0; 
    int n = 1 + removeAt(x->lc) + removeAt(x->rc); 
    release(x->data);
    release (x); 
    return n; 
}

template <typename T> 
BinTree<T>* BinTree<T>::secede(BinNodePosi(T) x){
    FromParentTo(*x) = NULL; 
    updateHeightAbove(x->parent);
    BinTree<T>* S = new BinTree<T>();
    S->_root = x;
    x->parent = NULL;
    S->_size = x->size(); 
    this->_size -= S->_size; 
    return S;
}
