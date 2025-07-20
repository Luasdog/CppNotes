#include "vector.h"
#include <cassert>

using namespace my;

// 默认成员函数

// 构造函数
template <class T>
vector<T>::vector()
    : _start(nullptr)
    , _finish(nullptr)
    , _end_of_storage(nullptr)
{}

// 带参数的构造函数，还有两个重载
template <class T>
vector<T>::vector(size_t n, const T& value)
    : _start(nullptr)
    , _finish(nullptr)
    , _end_of_storage(nullptr)
{
    reserve(n);
    for (size_t i = 0; i < n; i++) {
        push_back(value);
    }
}

template <class T>
vector<T>::vector(long n, const T& value)
    : _start(nullptr)
    , _finish(nullptr)
    , _end_of_storage(nullptr)
{
    reserve(n);
    for (size_t i = 0; i < n; i++) {
        push_back(value);
    }
}

template <class T>
vector<T>::vector(int n, const T& value)
    : _start(nullptr)
    , _finish(nullptr)
    , _end_of_storage(nullptr)
{
    reserve(n);
    for (size_t i = 0; i < n; i++) {
        push_back(value);
    }
}

// 范围构造函数（迭代器）
template <class T>
template<class InputIterator>
vector<T>::vector(InputIterator first, InputIterator last)
    : _start(nullptr)
    , _finish(nullptr)
    , _end_of_storage(nullptr)
{
    while (first != last) {
        push_back(*first);
        ++first;
    }
}

// 拷贝构造函数
// 传统写法
// template <class T>
// vector<T>::vector(const vector<T>& v)
//     : _start(nullptr)
//     , _finish(nullptr)
//     , _end_of_storage(nullptr)
// {
//     _start = new T[v.capacity()]; // 分配内存
//     for (size_t i = 0; i < v.size(); i++) {
//         // 如果vector当中存储的元素类型是内置类型（int）或浅拷贝的自定义类型（Date）
//         // 使用memcpy函数进行进行拷贝构造是没问题的
//         // 但如果vector当中存储的元素类型是深拷贝的自定义类型（string）
//         // 则使用memcpy函数将不能达到我们想要的效果
//         _start[i] = v[i]; // 拷贝元素
//     }
//     _finish = _start + v.size(); // 设置有效数据结束位置
//     _end_of_storage = _start + v.capacity(); // 设置存储结束位置
// }

// 拷贝构造函数
// 现代写法
template <class T>
vector<T>::vector(const vector<T>& v)
    : _start(nullptr)
    , _finish(nullptr)
    , _end_of_storage(nullptr)
{
    reserve(v.capacity());
    for (auto& e : v) {
        // 容器v当中存储的数据是string类
        // 在e拷贝时也会自动调用string的拷贝构造（深拷贝）
        push_back(e);
    }
}

// 赋值运算符重载
// 传统写法
template <class T>
vector<T>& vector<T>::operator=(const vector& v) {
    if (this != &v) {
        delete[] _start;
        _start = new T[v.capacity()];
        for (size_t i = 0; i < v.size(); i++) {
            _start[i] = v[i];
        }
        _finish = _start + v.size();
        _end_of_storage = _start + v.capacity();
    }
    return *this;
}

// 赋值运算符重载
// 现代写法
template <class T>
/**
 * 在右值传参时并没有使用引用传参
 * 因为这样可以间接调用vector的拷贝构造函数
 * 然后将这个拷贝构造出来的容器v与左值进行交换
 * 此时就相当于完成了赋值操作
 * 而容器v会在该函数调用结束时自动析构
 */
vector<T>& vector<T>::operator=(const vector v) { //编译器接收右值的时候自动调用其拷贝构造函数
    swap(v); // 交换两个vector的内容
    return *this; // 支持连续赋值
}

// 析构函数
template <class T>
vector<T>::~vector() {
    if (_start) {
        delete[] _start;
        _start = nullptr;
        _finish = nullptr;
        _end_of_storage = nullptr;
    }
}

// 迭代器相关函数
template <class T>
vector<T>::iterator vector<T>::begin() {
    return _start;
}

template <class T>
vector<T>::iterator vector<T>::end() {
    return _finish;
}

template <class T>
vector<T>::const_iterator vector<T>::begin() const {
    return _start;
}

template <class T>
vector<T>::const_iterator vector<T>::end() const {
    return _finish;
}

// 容量和大小

// 有效长度
template <class T>
size_t vector<T>::size()const {
    return _finish - _start;
}

// 容量
template <class T>
size_t vector<T>::capacity()const {
    return _end_of_storage - _start;
}

/**
 * 改变容量
 * 1、当n大于对象当前的capacity时，将capacity扩大到n或大于n。
 * 2、当n小于对象当前的capacity时，什么也不做。
 */
template <class T>
void vector<T>::reserve(size_t n) {
    if (n > capacity()) {
        size_t sz = size();
        T* tmp = new T[n];
        if (_start) {
            for (size_t i = 0; i < sz; i++) {
                tmp[i] = _start[i]; // 拷贝原有元素
            }
            delete[] _start; // 释放原有内存
        }
        _start = tmp; // 更新起始位置
        _finish = _start + sz; // 更新有效数据结束位置
        _end_of_storage = _start + n; // 更新存储结束位置
    }
}

/**
 * 改变有效长度
 * 1、当n大于当前的size时，将size扩大到n，扩大的数据为val，若val未给出，则默认为容器所存储类型的默认构造函数所构造出来的值。
 * 2、当n小于当前的size时，将size缩小到n。
 */
template <class T>
void vector<T>::resize(size_t n, const T& value = T()) {
    if (n < size()) {
        _finish = _start + n; // 缩小有效长度
    } else {
        if (n > capacity()) {
            reserve(n);
        }
        while (_finish < _start + n) {
            *_finish = value; // 扩大有效长度并填充默认值
            _finish++;
        }
    }
}

template <class T>
bool vector<T>::empty()const {
    return _start == _finish;
}

// 修改容器内容相关函数
template <class T>
void vector<T>::push_back(const T& x) {
    if (_finish == _end_of_storage) {
        size_t new_capacity = capacity() == 0 ? 4 : capacity() * 2; // 扩大容量
        reserve(new_capacity);
    }
    *_finish = x; // 在有效数据结束位置插入新元素
    _finish++; // 更新有效数据结束位置
}

template <class T>
void vector<T>::pop_back() {
    assert(!empty()); // 确保容器不为空
    _finish--; // 更新有效数据结束位置，删除最后一个元素
}

// 在指定位置插入元素
template <class T>
void vector<T>::insert(iterator pos, const T& x) {
    if (_finish == _end_of_storage) {
        size_t len = pos - _start; // 计算插入位置前的元素个数
        size_t new_capacity = capacity() == 0 ? 4 : capacity() * 2; // 扩大容量
        reserve(new_capacity);
        pos = _start + len; // 更新插入位置
    }
    iterator end = _finish;
    while (end >= pos + 1) {
        *(end) = *(end - 1); // 向后移动元素
        end--;
    }
    *pos = x; // 在插入位置插入新元素
    _finish++; // 更新有效数据结束位置
}

// 删除指定位置的元素
template <class T>
vector<T>::iterator vector<T>::erase(iterator pos) {
    assert(!empty()); // 确保容器不为空
    iterator it = pos + 1;
    while (it != _finish) {
        *(it - 1) = *it; // 向前移动元素
        it++;
    }
    _finish--; // 更新有效数据结束位置
    return pos;
}

// 交换两个vector的内容
template <class T>
void vector<T>::swap(vector<T>& v) {
    std::swap(_start, v._start);
    std::swap(_finish, v._finish);
    std::swap(_end_of_storage, v._end_of_storage);
}

// 访问容器相关函数
template <class T>
T& vector<T>::operator[](size_t i) {
    assert(i < size()); // 确保下标合法
    return _start[i];
}

template <class T>
const T& vector<T>::operator[](size_t i)const {
    assert(i < size()); // 确保下标合法
    return _start[i];
}