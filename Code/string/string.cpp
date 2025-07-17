#include "string.h"
#include <cassert>

using namespace my;

// 默认成员函数

// 构造函数
string::string(const char* str = "") {
    _size = strlen(str);
    _capacity = _size;
    _str = new char[_capacity + 1]; // 多的一个用于存放'\0'
    strcpy(_str, str);
}

// 拷贝构造函数

// 传统写法
// string::string(const string& s)
//     : _str(new char[s._capacity + 1])
//     , _size(0)
//     , _capacity(0)
// {
//     strcpy(_str, s._str);
//     _size = s._size;
//     _capacity = s._capacity;
// }

// 现代写法
string::string(const string& s)
    : _str(nullptr)
    , _size(0)
    , _capacity(0)
{
    string tmp(s._str);
    swap(tmp);
}

// 赋值运算符重载

// 传统写法
// string& string::operator=(const string& s) {
//     // 防止自己给自己赋值
//     if (this != &s) {
//         delete[] _str;
//         _str = new char[s._capacity + 1];
//         strcpy(_str, s._str);
//         _size = s._size;
//         _capacity = s._capacity;
//     }
//     return *this; // 返回左值（支持连续赋值）
// }

// 现代写法
string& string::operator=(const string& s) {
    if (this != &s) {
        string tmp(s);
        swap(tmp);
    }
    return *this;
}
// 析构函数
string::~string() {
    delete[] _str;
    _str = nullptr;
    _size = 0;
    _capacity = 0;
}


// 迭代器

// begin返回字符串中第一个字符的地址
string::iterator string::begin() {
    return _str;
}
string::const_iterator string::begin()const {
    return _str;
}

// end返回字符串最后一个字读的后一个字符（'\0'）的地址
string::iterator string::end() {
    return _str + _size;
}
string::const_iterator string::end()const {
    return _str + _size;
}

// 容量和大小

// 获取字符串当前的有效长度（不包括’\0’）
size_t string::size() {
    return _size;
}

// 获取字符串当前的容量
size_t string::capacity() {
    return _capacity;
}

/**
 * 改变容量，大小不变
 * 1、当n大于对象当前的capacity时，将capacity扩大到n或大于n。
 * 2、当n小于对象当前的capacity时，什么也不做。
 */
void string::reserve(size_t n) {
    if (n > _capacity) {
        char* tmp = new char[n + 1];
        strncpy(tmp, _str, _size + 1); // 限制最大拷贝长度为n
        delete[] _str;
        _str = tmp; // 将新开辟的空间交给_str
        _capacity = n;
    }
}

/**
 * 改变有效长度
 * 1、当n大于当前的size时，将size扩大到n，扩大的字符为ch，若ch未给出，则默认为’\0’。
 * 2、当n小于当前的size时，将size缩小到n。
 */
void string::resize(size_t n, char c = '\0') {
    if (n <= _size) {
        _size = n;
        _str[_size] = '\0';
    } else {
        if (n > _capacity) {
            reserve(n);
        }
        for (size_t i = _size; i < n; i++) { //将size扩大到n，扩大的字符为c
            _str[i] = c;
        }
        _size = n;
        _str[_size] = '\0';
    }
}

// 判空
bool string::empty()const {
    return strcmp(_str, "") == 0;
}

// 添加字符串

// 在当前字符串的后面尾插上一个字符
void string::push_back(char c) {
    if (_size == _capacity) {
        reserve(_capacity == 0 ? 4 : _capacity * 2);
    }
    _str[_size] = c;
    _str[_size + 1] = '\0';
    _size++;
} // insert(_size, c);

// 在当前字符串的后面尾插一个字符串
void string::append(const char* str) {
    size_t len = _size + strlen(str);
    if (len > _capacity) {
        reserve(len);
    }
    strcpy(_str + _size, str);
    _size = len;
} // insert(_size, str);


string& string::operator+=(char c) {
    push_back(c);
    return *this;
}
string& string::operator+=(const char* str) {
    append(str);
    return *this;
}

// 在字符串的任意位置插入字符或是字符串
string& string::insert(size_t pos, char c) {
    assert(pos <= _size); // 检测下标的合法性
    if (_size == _capacity) {
        reserve(_capacity == 0 ? 4 : _capacity * 2);
    }
    char* end = _str + _size;
    // 后移
    while (end >= _str + pos) {
        *(end + 1) = *(end);
        end--;
    }
    _str[pos] = c;
    _size++;
    return *this;
}
string& string::insert(size_t pos, const char* str) {
    assert(pos <= _size);
    size_t len = strlen(str);
    if (len + _size > _capacity) {
        reserve(len + _size);
    }
    char* end = _str + _size;
    while (end >= _str + pos)
    {
        *(end + len) = *(end);
        end--;
    }
    strncpy(_str + pos, str, len); // 注意末尾不需要多加入'\0'
    _size += len;
    return *this;
}

// 删除字符串任意位置开始的n个字符
string& string::erase(size_t pos, size_t len) {
    assert(pos < _size);
    size_t n = _size - pos;
    if (len >= n) { // pos后面的字符都被删除
        _size = pos;
        _str[_size] = '\0';
    } else {
        strcpy(_str + pos, _str + pos + len);
        _size -= len;
    }
    return *this;
}

// 置空
void string::clear() {
    _size = 0;
    _str[_size] = '\0';
}

// 交换两个对象的数据
void string::swap(string& s) {
    std::swap(_str, s._str);
    std::swap(_size, s._size);
    std::swap(_capacity, s._capacity);
}

// 获取对象C类型的字符串，返回以 \0 结尾的C风格字符串
const char* string::c_str()const {
    return _str;
}

// 访问字符串

// []运算符重载（可读可写），通过[] +下标的方式获取字符串对应位置的字符
char& string::operator[](size_t i) {
    assert(i < _size);
    return _str[i];
}

// []运算符重载（只读）
const char& string::operator[](size_t i)const {
    assert(i < _size);
    return _str[i];
}

// 正向查找第一个匹配的字符
size_t string::find(char c, size_t pos = 0)const {
    assert(pos < _size);
    for (size_t i = pos; i < _size; i++) { // 从pos位置开始向后寻找目标字符
        if (_str[i] == c) {
            return i;
        }
    }
    return npos; // 没有找到目标字符，返回npos
}

// 正向查找第一个匹配的字符串
size_t string::find(const char* str, size_t pos = 0)const {
    assert(pos < _size);
    const char* ret = strstr(_str + pos, str); //调用strstr进行查找
    if (ret) { // ret不为空指针，说明找到了
        return ret - _str; // 返回字符串第一个字符的下标
    } else {
        return npos; // 没有找到目标字符串，返回npos
    }
}

// 反向查找第一个匹配的字符
size_t string::rfind(char c, size_t pos = npos)const {
    string tmp(*this);
    std::reverse(tmp.begin(), tmp.end());
    if (pos >= _size) { // 所给pos大于字符串有效长度，重新设置pos为字符串最后一个字符的下标
        pos = _size - 1;
    }
    pos = _size - 1 - pos; // 将pos改为镜像对称后的位置
    size_t ret = tmp.find(c, pos); // 复用find函数
    if (ret != npos) {
        return _size - 1 - ret; //找到返回ret镜像对称后的位置
    } else {
        return npos;
    }
}

// 反向查找第一个匹配的字符串
size_t string::rfind(const char* str, size_t pos = 0)const {
    string tmp(*this);
    std::reverse(tmp.begin(), tmp.end());
    size_t len = strlen(str);
    char* arr = new char[len + 1];
    strcpy(arr, str);
    size_t left = 0, right = len - 1;
    //逆置字符串arr
    while (left < right) {
        std::swap(arr[left], arr[right]);
        left++;
        right--;
    }
    if (pos >= _size) {
        pos = _size - 1;
    }
    pos = _size - 1 - pos;
    size_t ret = tmp.find(arr, pos);
    delete[] arr;
    if (ret != npos) {
        return _size - 1 - ret - len;
    } else {
        return npos;
    }
}

// 比较字符串
bool string::operator>(const string& s)const {
    return strcmp(_str, s._str) > 0;
}
bool string::operator==(const string & s)const {
    return strcmp(_str, s._str) == 0;
}
bool string::operator>=(const string& s)const {
    return (*this > s) || (*this == s);
}
bool string::operator<(const string & s)const {
    return !(*this >= s);
}
bool string::operator<=(const string & s)const {
    return !(*this > s);
}
bool string::operator!=(const string & s)const {
    return !(*this == s);
}

// 字符串输入
std::istream& operator>>(std::istream& in, string& s) {
    s.clear();
    char c = in.get();
    while (c != ' ' && c != '\n')
    {
        s += c;
        c = in.get();
    }
    return in;
}

// 字符串输出
std::ostream& operator<<(std::ostream& out, const string& s) {
    for (auto c : s) {
        std::cout << c;
    }
    return out;
}

// 读取一行含有空格的字符串
std::istream& getline(std::istream& in, string& s) {
    s.clear();
    char c = in.get();
    while (c != '\n')
    {
        s += c;
        c = in.get();
    }
    return in;
}