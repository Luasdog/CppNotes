#pragma once
#include <deque>

namespace my {
    template <class T, class Container = std::deque<T>>
    class stack {
    public:
        // 元素入栈
        void push(const T& value) {
            _container.push_back(value);
        }

        // 元素出栈
        void pop() {
            _container.pop_back();
        }

        // 获取栈顶元素
        T& top() {
            return _container.back();
        }

        // 获取栈顶元素的常量引用
        const T& top() const {
            return _container.back();
        }

        // 获取栈中有效元素的个数
        size_t size() const {
            return _container.size();
        }

        // 检查栈是否为空
        bool empty() const {
            return _container.empty();
        }

        // 交换两个栈中的数据
        void swap(stack<T, Container>& other) {
            _container.swap(other._container);
        }

        // 清空栈
        void clear() {
            _container.clear();
        }

    private:
        Container _container; // 使用容器来存储元素
    };
}