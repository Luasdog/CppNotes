#include <vector>
namespace my {
    // 比较器 内部结构为大堆
    template <class T>
    struct less { 
        bool operator()(const T& x, const T& y) const {
            return x < y; // 默认小于比较
        }
    };
    // 比较器 内部结构为小堆
    template <class T>
    struct greater {
        bool operator()(const T& x, const T& y) const {
            return x > y; // 默认大于比较
        }
    };

    // 优先队列类模板
    template <class T, class Container = std::vector<T>, class Compare = less<T>>
    class priority_queue {
    public:
        void adjustUp(int child); // 向上调整
        void adjustDown(int n, int parent); // 向下调整
        void push(const T& x); // 插入队尾
        void pop(); // 弹出队头
        T& top(); // 获取队头元素
        const T& top() const; // 获取队头元素的常量引用
        size_t size() const; // 获取队列中有效元素的个数
        bool empty() const; // 检查队列是否为空

    private:
        Container _container; // 使用容器来存储数据
        Compare _compare; // 比较方式
    };

    // 优先队列具体实现

    // 向上调整
    template <class T, class Container, class Compare>
    void priority_queue<T, Container, Compare>::adjustUp(int child) {
        int parent = (child - 1) / 2;
        while (child > 0) {  // child > 0 确保不是根节点
            if (_compare(_container[parent], _container[child])) { // 通过给定的比较器确定是否交换
                std::swap(_container[parent], _container[child]);
                // 更新 child 和 parent
                child = parent;
                parent = (child - 1) / 2;
            } else {
                break;
            }
        }
    }

    // 向下调整
    template <class T, class Container, class Compare>
    void priority_queue<T, Container, Compare>::adjustDown(int n, int parent) {
        int child = 2 * parent + 1;
        while (child < n) {
            // 如果有右子节点，并且右子节点大于左子节点，则选择右子节点
            if (child + 1 < n && _compare(_container[child], _container[child + 1])) {
                child++;
            }
            // 通过给定的比较器确定是否交换
            if (_compare(_container[parent], _container[child])) {
                std::swap(_container[parent], _container[child]);
                parent = child;
                child = 2 * parent + 1;
            } else {
                break;
            }
        }
    }

    // 插入队尾
    template <class T, class Container, class Compare>
    void priority_queue<T, Container, Compare>::push(const T& x) {
        _container.push_back(x);
        adjustUp(_container.size() - 1); // 将最后一个元素进行一次向上调整
    }

    // 弹出队头
    template <class T, class Container, class Compare>
    void priority_queue<T, Container, Compare>::pop() {
        std::swap(_container[0], _container[_container.size() - 1]);
        _container.pop_back();
        adjustDown(_container.size(), 0); // 将根节点进行一次向下调整
    }

    // 获取队头元素
    template <class T, class Container, class Compare>
    T& priority_queue<T, Container, Compare>::top() {
        return _container[0];
    }

    // 获取队头元素的常量引用
    template <class T, class Container, class Compare>
    const T& priority_queue<T, Container, Compare>::top() const {
        return _container[0];
    }

    // 获取队列中有效元素的个数
    template <class T, class Container, class Compare>
    size_t priority_queue<T, Container, Compare>::size() const {
        return _container.size();
    }

    // 检查队列是否为空
    template <class T, class Container, class Compare>
    bool priority_queue<T, Container, Compare>::empty() const {
        return _container.empty();
    }
}