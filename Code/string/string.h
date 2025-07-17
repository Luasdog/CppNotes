#pragma once
#include <iostream>

namespace my
{
    class string // 实现string类，放入自己的命名空间中
    {
    public:
        // 默认成员函数
        string(const char* str = ""); // 构造函数
        string(const string& s); // 拷贝构造函数
        string& operator=(const string& s); // 赋值运算符重载
        ~string(); // 析构函数

        // 迭代器
        typedef char* iterator; //字符指针
        typedef const char* const_iterator;
        iterator begin();
        iterator end();
        const_iterator begin()const;
        const_iterator end()const;

        // 容量和大小
        size_t size(); // 有效长度
        size_t capacity(); // 容量
        void reserve(size_t n); // 改变容量
        void resize(size_t n, char c = '\0'); // 改变有效长度
        bool empty()const;

        // 添加字符串
        void push_back(char c);
        void append(const char* str);
        string& operator+=(char c);
        string& operator+=(const char* str);
        string& insert(size_t pos, char c);
        string& insert(size_t pos, const char* str);

        // 删除字符串
        string& erase(size_t pos, size_t len);
        void clear();

        // 交换字符串
        void swap(string& s);

        // 返回以 \0 结尾的C风格字符串
        const char* c_str()const;

        // 访问字符串
        char& operator[](size_t i);
        const char& operator[](size_t i)const;
        size_t find(char c, size_t pos = 0)const;
        size_t find(const char* str, size_t pos = 0)const;
        size_t rfind(char c, size_t pos = npos)const;
        size_t rfind(const char* str, size_t pos = 0)const;

        // 比较字符串
        bool operator>(const string& s)const;
        bool operator>=(const string& s)const;
        bool operator<(const string & s)const;
        bool operator<=(const string & s)const;
        bool operator==(const string & s)const;
        bool operator!=(const string & s)const;

    private:
        char* _str; // 存储字符串
        size_t _size; // 记录字符串当前的有效长度
        size_t _capacity; // 记录字符串当前的容量
        static const size_t npos; // 整型最大值
    };

    const size_t string::npos = -1;

    // 字符串输入输出
    std::istream& operator>>(std::istream& in, string& s);
    std::ostream& operator<<(std::ostream& out, const string& s);
    std::istream& getline(std::istream& in, string& s);
}