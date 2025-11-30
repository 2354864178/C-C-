#pragma once
#include "ListNode.hpp"

void run_list_test();

template<typename T>
class List{
private:
    int _size;
    ListNodePosi(T) header;
    ListNodePosi(T) trailer;

protected:
    void init();
    void copyNodes(ListNodePosi(T) p, int n);   //  复制列表自p其的n项

public:
    //   构造与析构函数
    List(){this->init();}
    List(List<T> const& L); 
    List(ListNodePosi(T) p, int n);
    List(List<T> const& L, Rank r, int n);
    ~List();

    int clear();
    int uniquify();     //  有序列表唯一化
    int deduplicate();  //  无序列表唯一化
    
    T remove(ListNodePosi(T) p);                //  节点删除，返回被删节点
    bool valid (ListNodePosi(T) p);             //  判断节点是否合法
    T& operator[](Rank index) const;            //  重载[]，支持[]访问
    Rank size() const {return _size;}           //  获取列表大小
    bool empty() const {return _size <= 0;}     //  判空

    ListNodePosi(T) first() const {return this->header->succ;}  //  返回第一个元素的位置
    ListNodePosi(T) last() const {return this->trailer->pred;}  //  返回最后一个元素的位置

    ListNodePosi(T) find(const T& e) const;                                 //  无序列表查找元素    
    ListNodePosi(T) find(const T& e, int n, ListNodePosi(T) p) const;       //  无序列表区间查找（p的前n个元素内）  
    ListNodePosi(T) search(T const& e) const;                               //  有序列表查找不大于e的最后者
    ListNodePosi(T) search (T const& e, int n, ListNodePosi(T) p) const;    //  有序列表区间查找不大于e的最后者
    ListNodePosi(T) selectMax();                                            //  最大元素查找
    ListNodePosi(T) selectMax(ListNodePosi(T) p, int n);                    //  在p及其n-1个后继中选出最大者
    
    ListNodePosi(T) insertAsFirst(const T& e);                      //  作为第一个节点插入
    ListNodePosi(T) insertAsLast(const T& e);                       //  作为最后一个节点插入
    ListNodePosi(T) insertAfter(ListNodePosi(T) p, const T& e);     //  在p之后插入
    ListNodePosi(T) insertBefore(ListNodePosi(T) p, const T& e);    //  在p之前插入

    bool disordered() const;
    void insertionsort(ListNodePosi(T) p, int n);   //  对p后面n个节点进行插入排序
    void insertionsort();                           //  对整个列表进行插入排序
    void selectionsort(ListNodePosi(T) p, int n);   //  对p后面n个节点进行选择排序
    void selectionsort();                           //  对整个列表进行选择排序

    void reverse();                     //  前后倒置
    void traverse(void(*visit)(T&));    //  遍历
};

template <class T>
void List<T>::init(){
    this->header = new ListNode<T>;
    this->trailer = new ListNode<T>;
    this->header->succ = this->trailer;
    this->header->pred =NULL;
    this->trailer->pred = this->header;
    this->trailer->succ = NULL;
    this->_size = 0;
}

template <class T>
T List<T>::remove(ListNodePosi(T) p){
    T e = p->data;
    p->pred->succ = p->succ;
    p->succ->pred = p->pred;
    delete p;
    this->_size--;
    return e;
}

template <class T>
int List<T>::clear(){
    int oldsize = this->_size;
    while(this->_size>0){
        this->remove(this->header->succ);
    }
    return oldsize;
}

template <class T>
T& List<T>::operator[](Rank index) const {
    if(index < 0 || index >= this->_size){
        throw std::out_of_range("index out of range");
    }
    ListNodePosi(T) p = this->first();
    while(0 < index--){
        p = p->succ;
    }
    return p->data;
}

template <class T>
bool List<T>::valid (ListNodePosi(T) p){
    return p && ( trailer != p ) && ( header != p );
}

template <class T>
ListNodePosi(T) List<T>::find(const T& e, int n, ListNodePosi(T) p) const {
    while(0 < n--){
        p = p->pred;
        if(p->data == e){
            return p;
        }
    }
    return NULL;
}

template <class T>
ListNodePosi(T) List<T>::find(const T& e) const {
    ListNodePosi(T) p = this->trailer->pred;
    int n = this->_size;
    return this->find(e, n, p);
}

template <class T>
ListNodePosi(T) List<T>::insertAsFirst(const T& e){
    this->_size ++;
    return this->header->insertAsSucc(e);
}

template <class T>
ListNodePosi(T) List<T>::insertAsLast(const T& e){
    this->_size ++;
    return this->trailer->insertAsPred(e);
}

template <class T>
ListNodePosi(T) List<T>::insertAfter(ListNodePosi(T) p, const T& e){
    this->_size++;
    return p->insertAsSucc(e);
}

template <class T>
ListNodePosi(T) List<T>::insertBefore(ListNodePosi(T) p, const T& e){
    this->_size++;
    return p->insertAsPred(e);
}

template <class T>
void List<T>::copyNodes(ListNodePosi(T) p, int n){
    this->init();
    while(n--){
        this->insertAsLast(p->data);
        p = p->succ;
    }
}

template <class T>
List<T>::List(List<T> const& L){
    this->copyNodes(L.first(), L._size);
}

template <class T>
List<T>::List(ListNodePosi(T) p, int n){
    this->copyNodes(p, n);
}

template <class T>
List<T>::List(List<T> const& L, Rank r, int n){
    ListNodePosi(T) p = L.first();
    for(Rank i = 0; i < r; ++i) p = p->succ; 
    this->copyNodes(p, n);
}

template <class T>
List<T>::~List(){
    this->clear();
    delete this->header;
    delete this->trailer;
}

template <class T>
int List<T>::deduplicate(){
    if(this->_size<2) return 0;
    int oldSize = this->_size;
    ListNodePosi(T) p=this->header;
    Rank r=0;
    while(p!=this->trailer){
        p = p->succ;
        ListNodePosi(T) q=this->find(p->data, r, p);
        q ? remove(q) : r++;
    }
    return oldSize - this->_size;
}

template <class T>
int List<T>::uniquify(){
    if(this->_size<2) return 0;
    int oldSize = this->_size;
    ListNodePosi(T) p = this->first();
    ListNodePosi(T) q;
    while(q != this->trailer){
        q = p->succ;
        if(p->data != q->data) p = q;
        else this->remove(q);
    }
    return oldSize - this->_size;
}

template <class T>
ListNodePosi(T) List<T>::search (T const& e, int n, ListNodePosi(T) p) const{
    while(n-->=0){
        p = p->pred;
        if(p->data <= e) break;
    }
    return p;
}   //  失败时，返回区间左边界的前驱（可能是header）

template <class T>
ListNodePosi(T) List<T>::search (T const& e) const{
    return search(e, this->_size, this->trailer);
}   //  失败时，返回 header

template <class T>
ListNodePosi(T) List<T>::selectMax(ListNodePosi(T) p, int n){
    ListNodePosi(T) Max = p;
    while(n-- > 1){ //  注意，n = n-1发生在进入循环前
        p = p->succ;
        if(Max->data <= p->data) Max = p;
    }
    return Max;
}

template <class T>
ListNodePosi(T) List<T>::selectMax(){
    return this->selectMax(this->first(), this->_size);
}

template <class T>
void List<T>::reverse(){    
    if (_size <= 1) return; 
    ListNodePosi(T) current = header->succ;  // 指向第一个实际元素
    ListNodePosi(T) nextNode;                // 用于保存下一个节点
    this->header->succ = this->trailer;
    this->trailer->pred = this->header;
    while(current != trailer){
        nextNode = current->succ;
        current->pred = this->header;
        current->succ = this->header->succ;
        if (header->succ != nullptr) this->header->succ->pred = current;
        current = nextNode;
    }
}

template <class T>
void List<T>::insertionsort(ListNodePosi(T) p, int n){
    for(int r = 0; r < n; r++){
        ListNodePosi(T) q=this->search(p->data, r, p);
        this->insertAfter(q, p->data);
        p = p->succ;
        this->remove(p->pred);
    }
}

template <class T>
void List<T>::insertionsort(){
    this->insertionsort(this->first(), this->_size);
}

template <class T>
void List<T>::selectionsort(ListNodePosi(T) p, int n){
    ListNodePosi(T) head = p->pred;
    ListNodePosi(T) trail = p;
    for(int i=0; i<n; i++) trail = trail->succ;
    while(n > 1){
        ListNodePosi(T) max = selectMax(head->succ, n);
        this->insertBefore(trail, this->remove(max));   //  注意！！！先删除，再插入
        // this->remove(max);
        trail = trail->pred;
        n--;
    }
}

template <class T>
void List<T>::selectionsort(){
    this->selectionsort(this->first(), this->_size);
}

template <class T>
bool List<T>::disordered() const{
    ListNodePosi(T) p = this->first();
    for (int i = 0; i < this->_size-1; ++i) {
        if(p->data > p->succ->data) return false;
    }
    return true;
}
