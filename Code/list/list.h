#pragma once

namespace my {
    // 双向链表节点结构体，list当中的结点类
    template <class T>
    struct _list_node {
        // 成员函数
        _list_node(const T& val = T()); // 构造函数

        // 成员变量
        T _val; // 节点存储的数据
        _list_node<T>* _next; // 指向下一个节点的指针
        _list_node<T>* _prev; // 指向前一个节点的指针
    };

    // 迭代器结构体
    template <class T, class Ref, class Ptr>
    struct _list_iterator {
        typedef _list_node<T> node;
        typedef _list_iterator<T, Ref, Ptr> self;

        _list_iterator(node* pnode); // 构造函数

        // 运算符重载函数
        self operator++(); // 前置自增操作符
        self operator--(); // 前置自减操作符
        self operator++(int); // 后置自增操作符
        self operator--(int); // 后置自减操作符
        bool operator==(const self& rhs) const; // 相等比较操作符
        bool operator!=(const self& rhs) const; // 不相等比较操作符
        Ref operator*(); // 解引用操作符
        Ptr operator->(); // 成员访问操作符

        // 成员变量
        node* _pnode; // 指向当前节点的指针
    };

    // list类模板
    template <class T>
    class list {
    public:
        typedef _list_node<T> node; // 节点类型
        typedef _list_iterator<T, T&, T*> iterator; // 迭代器类型
        typedef _list_iterator<T, const T&, const T*> const_iterator; // 常量迭代器类型

        // 默认成员函数
        list(); // 构造函数
        list(const list<T>& lt); // 拷贝构造函数
        list<T>& operator=(const list<T>& lt); // 赋值运算符重载
        ~list(); // 析构函数

        // 迭代器相关函数
        iterator begin(); // 返回迭代器指向头部
        iterator end(); // 返回迭代器指向尾部
        const_iterator begin()const; // 返回常量迭代器指向头部
        const_iterator end()const; // 返回常量迭代器指向尾部

        // 访问容器相关函数
        T& front(); // 返回头部元素的引用
        T& back(); // 返回尾部元素的引用
        const T& front() const; // 返回头部元素的常量引用
        const T& back() const; // 返回尾部元素的常量引用

        // 插入、删除函数
        void insert(iterator pos, const T& x); // 在指定位置插入元素
        iterator erase(iterator pos); // 删除指定位置的元素
        void push_back(const T& x); // 在尾部添加元素
        void push_front(const T& x); // 在头部添加元素
        void pop_back(); // 移除尾部元素
        void pop_front(); // 移除头部元素
        
        // 其他函数
        size_t size()const; // 返回容器大小
        void resize(size_t n, const T& val = T()); // 调整容器大小
        void clear(); // 清空容器
        bool empty()const; // 检查容器是否为空
        void swap(list<T>& lt); // 交换两个容器的内容

    private:
        node* _head; // 指向头部节点的指针
    };

    // 结点类构造函数
    template <class T>
    _list_node<T>::_list_node(const T& val = T())
        : _val(val)
        , _next(nullptr)
        , _prev(nullptr)
    {}

    // 迭代器类作用：list各个结点在内存当中的位置是随机的，不连续的，结点指针的自增、自减以及解引用等操作不行
    // 迭代器类来封装这些操作，用简单统一的方式对容器内的数据进行访问
  
    // 迭代器类构造函数
    template <class T, class Ref, class Ptr>
    _list_iterator<T, Ref, Ptr>::_list_iterator(node* pnode)
        : _pnode(pnode) {}

    // 前置自增操作符 ++t
    template <class T, class Ref, class Ptr>
    _list_iterator<T, Ref, Ptr>::self _list_iterator<T, Ref, Ptr>::operator++() {
        _pnode = _pnode->_next;
        return *this;
    }
    
    // 后置自增操作符 t++
    template <class T, class Ref, class Ptr>
    _list_iterator<T, Ref, Ptr>::self _list_iterator<T, Ref, Ptr>::operator++(int) {
        self tmp(*this);
        _pnode = _pnode->_next;
        return tmp;
    } 

    // 前置自减操作符
    template <class T, class Ref, class Ptr>
    _list_iterator<T, Ref, Ptr>::self _list_iterator<T, Ref, Ptr>::operator--() {
        _pnode = _pnode->_prev;
        return *this;
    }

    // 后置自减操作符
    template <class T, class Ref, class Ptr>
    _list_iterator<T, Ref, Ptr>::self _list_iterator<T, Ref, Ptr>::operator--(int) {
        self tmp(*this);
        _pnode = _pnode->_prev;
        return tmp;
    }
    
    // 相等比较操作符
    template <class T, class Ref, class Ptr>
    bool _list_iterator<T, Ref, Ptr>::operator==(const self& rhs)const {
        return _pnode == rhs._pnode;
    }
    
    // 不相等比较操作符
    template <class T, class Ref, class Ptr>
    bool _list_iterator<T, Ref, Ptr>::operator!=(const self& rhs)const {
        return _pnode != rhs._pnode;
    }

    // 解引用操作符
    template <class T, class Ref, class Ptr>
    Ref _list_iterator<T, Ref, Ptr>::operator*() {
        return _pnode->_val;
    }

    // 成员访问操作符
    template <class T, class Ref, class Ptr>
    Ptr _list_iterator<T, Ref, Ptr>::operator->() {
        return &_pnode->_val; // 返回结点指针所指结点的数据的地址
    }


    // list类模板成员函数实现
    // 默认成员函数
    
    // 构造函数
    template <class T>
    list<T>::list() {
        _head = new node(); // 创建一个头结点
        _head->_next = _head; // 头结点的下一个指向自己
        _head->_prev = _head; // 头结点的前一个指向自己
    }
    // 拷贝构造函数
    template <class T>
    list<T>::list(const list<T>& lt) {
        _head = new node(); // 创建一个头结点
        _head->_next = _head; // 头结点的下一个指向自己
        _head->_prev = _head; // 头结点的前一个指向自己
        for (const auto& e : lt) {
            push_back(e); // 将传入的list中的元素逐个添加到当前list中
        }
    }

    // 赋值运算符重载
    // 传统写法
    // template <class T>
    // list<T>& list<T>::operator=(const list<T>& lt) {
    //     if (this != &lt) {
    //         clear(); // 清空当前list
    //         for (const auto& e : lt) {
    //             push_back(e); // 将传入的list中的元素逐个添加到当前list中
    //         }
    //     }
    //     return *this;
    // }

    // 赋值运算符重载
    // 现代写法
    template <class T>
    list<T>& list<T>::operator=(const list<T>& lt) {
        swap(lt); // 交换当前list和临时list的内容
        return *this;
    }

    // 析构函数
    template <class T>
    list<T>::~list() {
        clear(); // 清空list
        delete _head; // 删除头结点
        _head = nullptr; // 将头结点指针置为nullptr
    }

    // 迭代器相关函数

    // 返回迭代器指向头部
    template <class T>
    list<T>::iterator list<T>::begin() {
        return iterator(_head->_next); // 返回头结点的下一个节点
    }

    // 返回迭代器指向尾部
    template <class T>
    list<T>::iterator list<T>::end() {
        return iterator(_head); // 返回头结点本身
    }

    // 返回常量迭代器指向头部
    template <class T>
    list<T>::const_iterator list<T>::begin()const {
        return const_iterator(_head->_next); // 返回头结点的下一个节点
    }

    // 返回常量迭代器指向尾部
    template <class T>
    list<T>::const_iterator list<T>::end()const {
        return const_iterator(_head); // 返回头结点本身
    }

    // 访问容器相关函数

    // 返回头部元素的引用
    template <class T>
    T& list<T>::front() {
        return *begin(); // 返回头结点的下一个节点的值
    }

    // 返回尾部元素的引用
    template <class T>
    T& list<T>::back() {
        return *--end(); // 返回头结点的前一个节点的值
    }

    // 返回头部元素的常量引用
    template <class T>
    const T& list<T>::front() const {
        return *begin(); // 返回头结点的下一个节点的值
    }

    // 返回尾部元素的常量引用
    template <class T>
    const T& list<T>::back() const {
        return *(--end()); // 返回头结点的前一个节点的值
    }

    // 插入、删除函数

    // 在指定位置插入元素
    template <class T>
    void list<T>::insert(iterator pos, const T& x) {
        assert(pos._pnode); // 确保迭代器指向有效节点

        node* cur = pos._pnode; // 获取当前迭代器指向的节点
        node* prev = cur->_prev; // 获取当前节点的前一个节点
        node* newNode = new node(x); // 创建新节点
        
        // 将新节点插入到当前节点之前
        newNode->_next = cur;
        newNode->_prev = prev;
        prev->_next = newNode;
        cur->_prev = newNode;
    }
    
    // 删除指定位置的元素
    template <class T>
    list<T>::iterator list<T>::erase(iterator pos) {
        assert(pos._pnode); // 确保迭代器指向有效节点
        assert(pos != end()); // 确保不能删除头结点

        node* cur = pos._pnode; // 获取当前迭代器指向的节点
        node* prev = cur->_prev; // 获取当前节点的前一个节点
        node* next = cur->_next; // 获取当前节点的后一个节点

        delete cur; // 删除当前节点

        // 将前一个节点的next指针指向后一个节点
        prev->_next = next;
        next->_prev = prev;

        return iterator(next); // 返回下一个节点的迭代器
    }
    
    // 在尾部添加元素
    template <class T>
    void list<T>::push_back(const T& x) {
        insert(end(), x); // 在尾部插入新元素
    }

    // 在头部添加元素
    template <class T>
    void list<T>::push_front(const T& x) {
        insert(begin(), x); // 在头部插入新元素
    }

    // 移除尾部元素
    template <class T>
    void list<T>::pop_back() {
        erase(--end()); // 删除尾部元素
    }

    // 移除头部元素
    template <class T>
    void list<T>::pop_front() {
        erase(begin()); // 删除头部元素
    }
    
    // 其他函数

    // 返回容器大小
    template <class T>
    size_t list<T>::size() const {
        size_t sz = 0;
        const_iterator it = begin();
        while (it != end()) { // 迭代器遍历容器
            sz++;
            it++;
        }
        return sz; // 返回计数
    }

    /**
     * 调整容器大小
     * 1、若当前容器的size小于所给n，则尾插结点，直到size等于n为止。
     * 2、若当前容器的size大于所给n，则只保留前n个有效数据。
     *  */ 
    template <class T>
    void list<T>::resize(size_t n, const T& val = T()) {
        iterator it = begin(); // 获取迭代器指向头部
        size_t len = 0; // 计数器初始化为0
        while (len < n && it != end()) { // 遍历容器
            len++; // 计数器加1
            it++; // 迭代器前进
        }
        if (len == n) { // 说明当前容器中的有效数据个数大于或是等于n
            while (it != end()) { // 只保留前n个有效数据
                it = erase(it); // 每次删除以后自动指向下一个节点
            }
        } else { // 当前容器中的有效数据个数小于n
            while (len < n) { // 尾插结点，直到size等于n为止
                push_back(val); // 在尾部添加默认值
                len++; // 计数器加1
            }
        }
    }

    // 清空容器
    template <class T>
    void list<T>::clear() {
        iterator it = begin(); // 获取迭代器指向头部
        while (it != end()) { // 遍历容器
            it = erase(it); // 删除当前节点并返回下一个节点的迭代器
        }
    }

    // 检查容器是否为空
    template <class T>
    bool list<T>::empty()const {
        return begin() == end(); // 如果头部迭代器等于尾部迭代器，则容器为空
    }

    // 交换两个容器的内容
    template <class T>
    void list<T>::swap(list<T>& lt) {
        std::swap(_head, lt._head); // 交换头结点指针即可
    }
}