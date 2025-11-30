#pragma once
#include "Stack_and_Quene.hpp"

#define BinNodePosi(T) BinNode<T>*          //  节点位置
#define stature(p) ((p) ? (p)->height : -1) //  节点高度（空树高度为-1）
#define IsRoot(x) (!((x).parent))
#define IsLChild(x) (!IsRoot(x) && (&(x) == (x).parent->lchild))
#define IsRChild(x) (!IsRoot(x) && (&(x) == (x).parent->rchild))
#define HasParent(x) (!IsRoot(x))
#define HasLChild(x) ((x).lchild)   //  左孩子
#define HasRChild(x) ((x).rchild)   //  右孩子
#define HasChild(x) (HasLChild(x) || HasRChild(x))        //  至少拥有一个孩子
#define HasBothChild(x) (HasLChild(x) && HasRChild(x))    //  同时拥有两个孩子
#define IsLeaf(x) (!HasChild(x))
#define sibling(p) (IsLChild(*(p)) ? (p)->parent->rchild : (p)->parent->lchild) //  兄弟
#define uncle(x) (IsLChild(* ((x)->parent)) ? (x)->parent->parent->rchild : (x)->parent->parent->lchild)
#define FromParentTo(x) (IsRoot(x) ? _root : (IsLChild(x) ? (x).parent->lchild : (x).parent->rchild))

typedef enum {RB_RED, RB_BLACK} RBColor;    //节点颜色

template<typename T> struct BinNode{
    T data; //  数值
    BinNode* lchild;    //  左孩子
    BinNode* rchild;    //  右孩子
    BinNode* parent;    //  父节点
    int npl             //  左式堆，也可直接用height代替
    int height;         //  节点高度
    RBColor color;      //  节点颜色

    BinNode() : parent(NULL), lc(NULL), rc(NULL), height(0), npl(1), color(RB_RED){}
    BinNode(T e, BinNodePosi(T) p = NULL, BinNodePosi(T) lc = NULL, BinNodePosi(T) rc = NULL, int h = 0, int l = 1, RBColor c = RB_RED) 
            :data(e), parent(p), lchild(lc), rchild(rc), height(h), npl(l), color(c){}
    
    int size();
    BinNodePosi(T) succ();
    BinNodePosi(T) insertAsLC(T const&); 
    BinNodePosi(T) insertAsRC(T const&);

    template <typename VST> void travLevel(VST&);    //  子树层次遍历
    template <typename VST> void travPre(VST&);      //  子树先序遍历
    template <typename VST> void travIn(VST&);       //  子树中序遍历
    template <typename VST> void travPost(VST&);     //  子树后序遍历
    
    bool operator< (BinNode const& bn) {return data < bn.data;}     //  小于
    bool operator> (BinNode const& bn) {return data > bn.data;}     //  大于
    bool operator== (BinNode const& bn) {return data == bn.data;}   //  等于
    bool operator!= (BinNode const& bn) {return data != bn.data;}   //  不等于
    bool operator>= (BinNode const& bn) {return data >= bn.data;}   //  大于等于
    bool operator<= (BinNode const& bn) {return data <= bn.data;}   //  小于等于    
};

template<class T>
BinNodePosi(T) BinNode<T>::insertAsLC(T const& e){
    return this->lchild = new BinNode(e, this);
}

template<class T>
BinNodePosi(T) BinNode<T>::insertAsRC(T const& e){
    return this->rchild = new BinNode(e, this);
}

template <typename T, typename VST>
void travPre_R(BinNodePosi(T) x, VST& visit){
    if(!x) return;
    visit(x->data);
    travPre_R(x->lchild, visit);
    travPre_R(x->rchild, visit);
}

template <typename T, typename VST>
void travPost_R(BinNodePosi(T) x, VST& visit){
    if(!x) return;
    travPost_R(x->lchild, visit);
    travPost_R(x->rchild, visit);
    visit(x->data);
}

template <typename T, typename VST>
void travIn_R(BinNodePosi(T) x, VST& visit){
    if(!x) return;
    travIn_R(x->lchild, visit);
    visit(x->data);
    travIn_R(x->rchild, visit);
}

template <typename T, typename VST> 
static void visitAlongLeftBranch(BinNodePosi(T) x, VST& visit, Stack<BinNodePosi(T)>& S){
    while(x) {
        visit(x->data);
        S.push(x->rchild);
        x = x->lchild;
    }
}

template <typename T, typename VST> 
void travPre_I1 ( BinNodePosi(T) x, VST& visit ) { 
    Stack<BinNodePosi(T)> S; 
    if(x) S.push (x); 
    while (!S.empty()) { 
        x = S.pop(); visit ( x->data ); 
        if(HasRChild(*x )) S.push (x->rchild); 
        if HasLChild(*x )) S.push (x->lchild);
    }
}


template <typename T, typename VST>
void travPre_I2(BinNodePosi(T) x, VST& visit){
    Stack<BinNodePosi(T)> S;
    while(true){
        visitAlongLeftBranch(x, visit, S);
        if(S.empty()) break;
        x = S.pop();

    }
}

template <typename T>
static void goAlongLeftBranch(BinNodePosi(T) x, Stack<BinNodePosi(T)>& S) {
    while(x){
        S.push(x); 
        x = x->lchild;
    }
}

template <typename T, typename VST>
void travIn_I1(BinNodePosi(T) x, VST& visit){
    Stack<BinNodePosi(T)> S;
    while(true) {
        goAlongLeftBranch(x, S);
        if(S.empty()) break; 
        x = S.pop();
        visit(x->data); 
        x = x->rchild; //转向右子树
    }
}

template <typename T> 
BinNodePosi(T) BinNode<T>::succ(){ 
    BinNodePosi(T) s = this;
    if(rc){ 
        s = rchild; 
        while(HasLChild(*s)) s = s->lchild; 
    }else{
        while(IsRChild(*s)) s = s->parent; 
        s = s->parent; 
    }
    return s;
}

template <typename T, typename VST>
void travIn_I2(BinNodePosi(T) x, VST& visit){
    Stack(BinNodePosi(T)) S;
    while(true){
        if(x){
            S.push(x);
            x = x->lchild;
        }
        else if(!S.empty()){
            x = S.pop();
            visit(x->data);
            x = x->rchild; 
        }
        else break;
    }
}

template <typename T, typename VST>
void travIn_I3(BinNodePosi(T) x, VST& visit){
    bool backtrack = false;
    while(true){
        if(!backtrack && HasLChild(*x)) x = x->lchild;
        else visit(x->data); 
        if(HasRChild(*x)){
            x = x->rchild;
            backtrack = false;
        }
        else{
            if(!(x = x->succ())) break;
            backtrack = true;
        }
    }
}

template <typename T> //在以S栈顶节点为根癿子树中，找刡最高左侧可见叶节点
static void gotoHLVFL ( Stack<BinNodePosi(T)>& S ) { //沿递所遇节点依次入栈
    while ( BinNodePosi(T) x = S.top() ) //自顶而下，反复检查弼前节点（即栈顶）
    if ( HasLChild ( *x ) ) { //尽可能向左
        if ( HasRChild ( *x ) ) S.push ( x->rc ); //若有右孩子，优先入栈
        S.push ( x->lc ); //然后才转至左孩子
    } 
    else S.push ( x->rc ); //才向右
    S.pop(); //迒回乀前，弹出栈顶癿空节点
}

template <typename T, typename VST>
void travPost_I ( BinNodePosi(T) x, VST& visit ) { 
    Stack<BinNodePosi(T)> S;
    if ( x ) S.push ( x );
    while ( !S.empty() ) {
        if ( S.top() != x->parent ) 
        gotoHLVFL ( S ); 
        x = S.pop(); visit ( x->data ); 
    }
}

template <typename T> template <typename VST> //元素类型、操作器
void BinNode<T>::travIn(VST& visit){ //二叉树中序遍历算法统一入口
        switch (rand() % 4) { //此处暂随机选择以做测试，共五种选择
            case 1: travIn_I1 ( this, visit ); break; //迭代版#1
            case 2: travIn_I2 ( this, visit ); break; //迭代版#2
            case 3: travIn_I3 ( this, visit ); break; //迭代版#3
            default: travIn_R ( this, visit ); break; //递归版
    }
}

template <typename T> template <typename VST> //元素类型、操作器
void BinNode<T>::travPre(VST& visit){ //二叉树先序遍历算法统一入口
        switch (rand() % 3) {
            case 1: travPre_I1 ( this, visit ); break; //迭代版#1
            case 2: travPre_I2 ( this, visit ); break; //迭代版#2
            default: travPre_R ( this, visit ); break; //递归版
    }
}

template <typename T> template <typename VST> //元素类型、操作器
void BinNode<T>::travPost(VST& visit){ //二叉树先序遍历算法统一入口
        switch (rand() % 2) {
            case 1: travPost_I ( this, visit ); break; //迭代版#1
            default: travPodt_R ( this, visit ); break; //递归版
    }
}


