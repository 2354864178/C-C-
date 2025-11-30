#pragma once

using Rank=int; //同(typedef int Rank;)
#define ListNodePosi(T) ListNode<T>* // 列表节点位置

//节点的模板类
template <class T> 
struct ListNode{
    T data;                 //  值
    ListNodePosi(T) pred;   //  前节点
    ListNodePosi(T) succ;   //  后继节点
    ListNodePosi(T) insertAsPred (T const& e);  //紧靠当前节点之前插入新节点
    ListNodePosi(T) insertAsSucc (T const& e);  //紧靠当前节点之后插入新节点
    ListNode(){};   //  针对header和trailer构造
    ListNode(T e, ListNodePosi(T) p = NULL, ListNodePosi(T) s = NULL):data(e), pred(p), succ(s){}   // 默认构造器
};

template <class T>
ListNodePosi(T) ListNode<T>::insertAsPred(T const& e){
    ListNodePosi(T) x = new ListNode(e, pred, this);
    pred->succ = x;
    pred = x;
    return x;
}

template <class T>
ListNodePosi(T) ListNode<T>::insertAsSucc(T const& e){
    ListNodePosi(T) x = new ListNode(e, this, succ);
    succ->pred = x;
    succ = x;
    return x;
}


