#pragma once
#include <iostream>

namespace my {
    template <class T>
    class vector
    {
    public:
        // 迭代器
        typedef T* iterator;
        typedef const T* const_iterator;
        
        // 默认成员函数
        vector(); // 构造函数
        vector(size_t n, const T& value); // 带参数的构造函数
        vector(long n, const T& value);
        vector(int n, const T& value);
        template<class InputIterator>
        vector(InputIterator first, InputIterator last); // 范围构造函数
        vector(const vector<T>& v); // 拷贝构造函数
        vector<T>& operator=(const vector& v); // 赋值运算符重载
        vector<T>& operator=(const vector v); // 赋值运算符重载（现代写法）
        ~vector(); // 析构函数

        // 迭代器相关函数
        iterator begin();
        iterator end();
        const_iterator begin()const;
        const_iterator end()const;

        // 容量和大小
        size_t size()const; // 有效长度
        size_t capacity()const; // 容量
        void reserve(size_t n); // 改变容量
        void resize(size_t n, const T& value = T()); // 改变有效长度
        bool empty()const;

        // 修改容器内容相关函数
        void push_back(const T& x);
        void pop_back();
        void insert(iterator pos, const T& x); // 在指定位置插入元素
        iterator erase(iterator pos); // 删除指定位置的元素
        void swap(vector<T>& v); // 交换两个vector的内容

        // 访问容器相关函数
        T& operator[](size_t i);
        const T& operator[](size_t i)const;

    private:
        iterator _start; // 指向容器的起始位置
        iterator _finish; // 指向容器有效数据的结束位置
        iterator _end_of_storage; // 指向容器的结束位置
    };
}