#pragma once
#include "Vector.hpp"   //以向量为基类，派生出栈模板类
#include "List.hpp"     //以List为基类，派生出队列模板类

void run_stackqueue_test();

template <typename T> class Stack: public Vector<T> {   //  将向量的首/末端作为栈底/顶
public: //  size()、empty()以及其它开放接口，均可直接沿用
    void push(T const& e){this->insert(this->size(), e);}   //入栈
    T pop(){return this->remove(this->size() - 1);}         //出栈
    T& top(){return (*this) [this->size() - 1];}            //栈顶
};

template <typename T> class Queue: public List<T> {     //  队列模板类（继承List原有接口）
public: //  size()、empty()以及其它开放接口均可直接沿用
    void enqueue(T const& e) { this->insertAsLast(e); }  //  入队：尾部插入
    T dequeue(){ return this->remove(this->first()); }     //  出队：首部删除
    T& front(){ return this->first()->data; }             //  队首
};
