#pragma once
#include <deque>

namespace my {
    template <class T, class Container = std::deque<T>>
    class queue {
    public:
        // 队尾入队列
        void push(const T& value) {
            _container.push_back(value);
        }

        // 队头出队列
        void pop() {
            _container.pop_front();
        }

        // 获取队头元素
        T& front() {
            return _container.front();
        }

        // 获取队头元素的常量引用
        const T& front() const {
            return _container.front();
        }

        // 获取队尾元素
        T& back() {
            return _container.back();
        }

        // 获取队尾元素的常量引用
        const T& back() const {
            return _container.back();
        }

        // 获取队列中有效元素的个数
        size_t size() const {
            return _container.size();
        }

        // 检查队列是否为空
        bool empty() const {
            return _container.empty();
        }

        // 交换两个队列的内容
        void swap(queue<T, Container>& other) {
            _container.swap(other._container);
        }

        // 清空队列
        void clear() {
            _container.clear();
        }

    private:
        Container _container; // 使用容器来存储数据
    };
}