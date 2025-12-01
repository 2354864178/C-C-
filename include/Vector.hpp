#pragma once
#include <algorithm>

void run_vector_test();

using namespace std;
using Rank=int;                 //  同(typedef int Rank;)
const int DEFAULT_CAPACITY=3;   //  默认容量，同#define DEFAULT_CAPACITY 3

template<class T>class Vector{
protected:
    Rank _size;      // 规模
    int _capacity;   // 容量
    T* _elem;        // 头指针

    void CopyFrom(const T *A, Rank lo, Rank hi);    //  数组区间复制
    void expand();  //  扩容
    void shrink();  //  缩容
    bool bubble(Rank lo, Rank hi);          //  扫描交换
    Rank max(Rank lo, Rank hi);             //  找到最大值的下标
    void merge(Rank lo, Rank mi, Rank hi);  //  归并算法

public:
    //构造函数
    //容量为c、规模为s、所有元素为v
    Vector(int c=DEFAULT_CAPACITY, int s=0, T v=0){
        this->_elem = new T[this->_capacity = c];
        for(this->_size=0; this->_size<s; this->_size++){
            this->_elem[this->_size] = v;
        }
    }
    Vector(const Vector& A){ CopyFrom(A._elem, 0, A._size); }               // 拷贝构造，整体复制
    Vector(const Vector& A, int lo, int hi){ CopyFrom(A._elem, lo, hi); }   //  拷贝构造，区间复制
    Vector(const T *A, int n){ CopyFrom(A, 0, n); }             //  数组复制构造（可以以数组为输入）
    Vector(const T *A, int lo, int hi){ CopyFrom(A, lo, hi); }  //  数组区间复制构造（可以以数组为输入）
    ~Vector(){ delete[] this->_elem; }  //  析构函数，释放内部空间

//-----------------------------------------------------------
    Rank size() const {return _size;} 
    T& operator[](Rank k) const;              //  重载[]，支持下标访问
    Vector& operator=(const Vector& A); //  重载=，支持直接赋值

    void unsort(Rank lo, Rank hi);  //  区间置乱
    void unsort();                  //  整体置乱

    Rank find(const T& e, Rank lo, Rank hi) const;          //  区间查找
    Rank find(const T& e) const;                            //  全局查找
    Rank binSearch (const T& e, Rank lo, Rank hi) const;    //  二分查找
    
    void traverse(void(*visit)(T&)); //  遍历(visit可用来自定义遍历操作)
    template <typename VST> void traverse(VST&);

    Rank insert(Rank r, const T& e);    // 插入
    Rank insert (const T& e);           // 默认尾部插入

    int remove(Rank lo, Rank hi);   //  区间删除
    T remove(Rank r);               //  单元素删除

    int deduplicate();  // 无序唯一化
    void uniquify();    // 有序唯一化

    void bubbleSort(Rank lo, Rank hi);      //  区间冒泡排序
    void bubbleSort();                      //  整体冒泡排序
    void selectionSort(Rank lo, Rank hi);   //  区间选择排序
    void selectionSort();                   //  整体选择排序
    void insertionSort(Rank lo, Rank hi);   //  区间插入排序
    void insertionSort();                   //  整体插入排序
    void mergeSort(Rank lo, Rank hi);       //  区间归并排序
    void mergeSort();                       //  整体归并排序
};

template <class T>
void Vector<T>::CopyFrom(const T *A, Rank lo, Rank hi){
    this->_capacity=2*(hi-lo);
        this->_elem = new T[this->_capacity];     //深拷贝，申请双倍容量
        this->_size = 0;
        while(lo < hi) this->_elem[this->_size++] = A[lo++];
}

template <class T>
void Vector<T>::expand(){
    if(this->_size<this->_capacity) return;
    if(this->_capacity<DEFAULT_CAPACITY) this->_capacity=DEFAULT_CAPACITY;
    T* oldElem = this->_elem;
    this->_elem = new T[this->_capacity<<=1];
    for(int i=0; i<this->_size; i++){
        this->_elem[i] = oldElem[i];
    }
    delete[] oldElem;
}

template <class T>
void Vector<T>::shrink(){
    if(this->_capacity < DEFAULT_CAPACITY) return;
    if(this->_size<<2 < this->_capacity){
        T* oldElem = this->_elem;
        this->_elem = new T[this->_capacity>>=1];
        for(int i=0; i<this->_size; i++){
            this->_elem[i] = oldElem[i];
        }
        delete[] oldElem;
    }    
}

template <class T>
T& Vector<T>::operator[](Rank k) const {
    return this->_elem[k];
}

template <class T>
Vector<T>& Vector<T>::operator=(const Vector<T>& A){
    this->CopyFrom(A._elem, 0, A._size);
    return *this;
}

template <class T>
void Vector<T>::unsort(Rank lo, Rank hi){
    T* V = this->_elem+lo;
    for(Rank i = hi-lo; i>0; i--){
        swap(V[i-1], V[rand()%i]);
    }
}

template <class T>
void Vector<T>::unsort(){
    this->unsort(0, this->_size);
}

template <class T>
Rank Vector<T>::find(const T& e, Rank lo, Rank hi) const{
    while((hi-- > lo) && (e != this->_elem[hi]));
    return (hi >= lo) ? hi : -1;
}

template <class T>
Rank Vector<T>::find(const T& e) const{
    return this->find(e, 0, this->_size);
}

template <class T>
Rank Vector<T>::insert(Rank r, const T& e){
    this->expand();
    for(int i = this->_size; i>r; i--){
        this->_elem[i] = this->_elem[i-1];
    }
    this->_elem[r] = e;
    this->_size++;
    return r;
}

template <class T>
Rank Vector<T>::insert (const T& e){
    return this->insert(this->_size, e); 
}

template <class T>
int Vector<T>::remove(Rank lo, Rank hi){
    if(lo == hi) return 0;
    while(hi<this->_size){
        this->_elem[lo++] = this->_elem[hi++];
    }
    this->_size = lo;
    this->shrink();
    return hi-lo;
}

template <class T>
T Vector<T>::remove(Rank r){
    T tmp = this->_elem[r];
    this->remove(r, r+1);
    return tmp;
}

template <class T>
int Vector<T>::deduplicate(){
    int oldSize = this->_size;    
    Rank i = 1;
    while(i<this->_size){
        (this->find(this->_elem[i], 0, i)<0) ? i++ : this->remove(i);
    }
    return oldSize-this->_size;
}
template <class T>
void Vector<T>::uniquify(){
    Rank i = 0, j = 0; 
    while (++j < this->_size) {
        if (_elem[i] != _elem[j]) _elem[++i] = _elem[j];
    }
    this->_size = ++i;
    shrink();
}

template <class T>
Rank Vector<T>::binSearch (const T& e, Rank lo, Rank hi) const {
    while ( lo < hi ) {
        Rank mi = ( lo + hi ) >> 1; 
        if ( e < this->_elem[mi] ) hi = mi;
        else if (this->_elem[mi] < e ) lo = mi + 1; 
        else return mi; //在mi处命中
    } 
    return -1; //查找失败
}

template <class T>
void Vector<T>::traverse(void(*visit)(T&)){
    for(int i=0; i<this->_size; i++) visit(this->_elem[i]);
}

template <typename T> template <typename VST> //元素类型、操作器
void Vector<T>::traverse(VST& visit){
    for(int i = 0; i < _size; i++) visit(_elem[i]);
}

template <class T>
bool Vector<T>::bubble(Rank lo, Rank hi){
    bool swapped = true;
    while(++lo<hi){
        if(this->_elem[lo-1] > this->_elem[lo]){
            swapped = false;
            swap(this->_elem[lo-1], this->_elem[lo]);
        }
    }
    return swapped;
}
    
template <class T>
void Vector<T>::bubbleSort(Rank lo, Rank hi){
    while(!this->bubble(lo, hi--));
}

template <class T>
void Vector<T>::bubbleSort(){
    this->bubbleSort(0, this->_size);
}

template <class T>
Rank Vector<T>::max(Rank lo, Rank hi){
    Rank maxLoc = lo;
    while(lo++<hi){
        if(this->_elem[lo]>this->_elem[maxLoc]){
            maxLoc = lo;
        }
    }
    return maxLoc;
}

template <class T>
void Vector<T>::selectionSort(Rank lo, Rank hi){
    while(lo < --hi) swap(this->_elem[hi], this->_elem[max(lo, hi)]);
}

template <class T>
void Vector<T>::selectionSort(){
    this->selectionSort(0, this->_size);
}

template <class T>
void Vector<T>::insertionSort(Rank lo, Rank hi){
    while(lo<hi){
        Rank idx = lo++;
        while(idx-- > 0 && (this->_elem[idx]>this->_elem[idx+1])){
            swap(this->_elem[idx], this->_elem[idx+1]);
        }
    }
}

template <class T>
void Vector<T>::insertionSort(){
    this->insertionSort(0,this->_size);
}

template <class T>
void Vector<T>::merge(Rank lo, Rank mi, Rank hi) {
    T* A = _elem + lo;  // 合并后的结果存储在A中，起始于lo
    int lenB = mi - lo; // 左子区间长度
    T* B = new T[lenB]; // 复制左子区间内容
    for (int i = 0; i < lenB; ++i) {
        B[i] = A[i];    // 将[lo, mi)区间的元素复制到B
    }
    
    int lenC = hi - mi; // 右子区间长度
    T* C = _elem + mi;  // 右子区间起始位置
    
    // 合并B和C到A
    int i = 0, j = 0, k = 0;
    while (i < lenB && j < lenC) {
        // 取较小的元素放入结果
        if (B[i] <= C[j]) {
            A[k++] = B[i++];
        } else {
            A[k++] = C[j++];
        }
    }
    
    // 处理剩余元素
    while (i < lenB) {
        A[k++] = B[i++];
    }
    // 右侧剩余元素已经在正确位置，无需处理
    
    delete[] B; // 释放临时数组
}

template <class T>
void Vector<T>::mergeSort(Rank lo, Rank hi){
    if ( hi - lo < 2 ) return;
    int mi = (lo + hi) >> 1; 
    this->mergeSort(lo, mi); 
    this->mergeSort(mi, hi); 
    this->merge(lo, mi, hi); 
}

template <class T>
void Vector<T>::mergeSort(){
    this->mergeSort(0, this->_size); 
}


