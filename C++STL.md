# 什么是STL？

C++ 标准模板库（Standard Template Library，STL）是一套功能强大的 C++ 模板类和函数的集合，它提供了一系列通用的、可复用的算法和数据结构。

STL 的设计基于泛型编程，这意味着使用模板可以编写出独立于任何特定数据类型的代码。

STL 分为多个组件，包括容器（Containers）、迭代器（Iterators）、算法（Algorithms）、函数对象（Function Objects）和适配器（Adapters）等。

# 使用 STL 的好处
代码复用：STL 提供了大量的通用数据结构和算法，可以减少重复编写代码的工作。

性能优化：STL 中的算法和数据结构都经过了优化，以提供最佳的性能。

泛型编程：使用模板，STL 支持泛型编程，使得算法和数据结构可以适用于任何数据类型。

易于维护：STL 的设计使得代码更加模块化，易于阅读和维护。

# vector

## vector的实现

- vector接口见[ `vector.h` ](./Code/vector/vector.h)
- vector具体函数实现见[ `vector.cpp` ](./Code/vector/vector.cpp)

## `std::vector::resize()` 和 `std::vector::reserve()` 

---

### 对比

| 特性             | `resize(n)`      | `reserve(n)`                   |
| -------------- | ---------------- | ------------------------------ |
| 是否改变 vector 大小 | ✅ 是的，逻辑大小变为 n    | ❌ 不变，只预留空间                     |
| 是否构造元素         | ✅ 会构造或销毁元素       | ❌ 不构造任何元素                      |
| 影响 `size()`？   | ✅ 改变 `size()`    | ❌ `size()` 不变，只影响 `capacity()` |
| 用于什么时候         | 你想**真正拥有 n 个元素** | 你想**提前分配空间、避免多次扩容**            |
| 内存分配           | 有时分配             | 一定会分配（如果 n > 当前 capacity）      |

---

### 示例

1. `resize()` 示例

```cpp
std::vector<int> v;
v.resize(5);  // v.size() == 5，包含5个默认值为0的元素
```

可以访问 `v[0]` 到 `v[4]`，因为这些元素真的存在了。

---

2. `reserve()` 示例

```cpp
std::vector<int> v;
v.reserve(100);  // 只是预留空间，不构造元素
```

此时 `v.size() == 0`，你不能访问 `v[0]`，否则是**未定义行为**。你只能通过 `push_back()` 等方式添加元素。

---
> **`resize()` 是改变实际大小并构造元素，`reserve()` 是预留内存不构造元素**。
---

# string

## string的实现

- string接口见[ `string.h` ](./Code/string/string.h)
- string具体函数实现见[ `string.cpp` ](./Code/string/string.cpp)

# list

- 可在常数范围内在任意位置进行插入和删除的序列式容器，并且该容器可以前后双向迭代。
- 底层是**双向链表结构**，双向链表中每个元素存储在互不相关的独立结点当中，在结点中通过指针指向其前一个元素和后一个元素。
- list与forward_list相似，不同在于forward_list是单链表，只能进行单方向迭代。
- 在任意位置进行插入、删除元素的执行效率更高。
- list和forward_list最大的缺陷是不支持在任意位置的随机访问，其次，list还需要一些额外的空间，以保存每个结点之间的关联信息（对于存储的类型较小元素来说这可能是一个重要的因素）。

## list的实现

- list接口见[ `list.h` ](./Code/list/list.h)
- list具体函数实现[ `list.cpp` ](./Code/list/list.cpp)

# 函数

## `std::sort`

`std::sort` 是 C++ 标准库中使用最广泛的排序函数，它内部的实现方式通常是 **Introsort（内省排序）**。

---

### 实现方式：**Introsort**

### Introsort 是一种混合排序算法：

它结合了三种排序算法的优点：

1. **快速排序（Quicksort）**

   * 用作主排序策略。
   * 平均时间复杂度为 O(n log n)。
   * 快速处理大多数情况。

2. **堆排序（Heapsort）**

   * 当递归深度太大（接近最坏情况）时切换到堆排序。
   * 保证最坏情况时间复杂度为 O(n log n)。

3. **插入排序（Insertion Sort）**

   * 用于处理小范围（通常 <16 个元素）的排序。
   * 常数开销小，适合小数组。

### 为什么选择 Introsort？

* 快速排序通常是最快的，但最坏情况是 O(n²)。
* 为了避免这个最坏情况，std::sort 设置了一个最大递归深度（通常是 `2 * log2(n)`），超过这个深度就转用堆排序。
* 小数组直接用插入排序更快。

---

### 时间复杂度

| 情况   | 时间复杂度                    |
| ---- | ------------------------ |
| 最好情况 | O(n log n)               |
| 平均情况 | O(n log n)               |
| 最坏情况 | O(n log n)     (使用堆排序保证) |

---

### 空间复杂度

* **O(log n)**：主要用于递归栈（不会额外分配数组，原地排序）。

---

### 稳定性

* ❌ **不稳定排序**（即相等元素排序后相对位置可能改变）。

如果你需要 **稳定排序**，请使用：

```cpp
std::stable_sort();
```

---

### 示例说明（简化逻辑）：

```cpp
template<typename RandomIt>
void introsort(RandomIt first, RandomIt last, int depth_limit) {
    if (last - first <= SMALL_THRESHOLD)
        insertion_sort(first, last);
    else if (depth_limit == 0)
        heapsort(first, last);
    else {
        auto pivot = partition(first, last);
        introsort(first, pivot, depth_limit - 1);
        introsort(pivot, last, depth_limit - 1);
    }
}
```

标准库实现（如 libc++、libstdc++）都有类似逻辑。

---

### 总结

| 特性    | 说明                           |
| ----- | ---------------------------- |
| 算法    | Introsort（快速排序 + 堆排序 + 插入排序） |
| 平均复杂度 | O(n log n)                   |
| 最坏复杂度 | O(n log n)                   |
| 空间复杂度 | O(log n)                     |
| 稳定性   | ❌ 不稳定                        |
| 排序位置  | 原地排序（in-place）               |

---

### **简化版的 `std::sort` 实现**

使用的是 **Introsort** 思想（快速排序为主，回退到堆排序，处理小数组用插入排序）。真实标准库实现更复杂、更优化。

---

简化版 `introsort` 实现（适用于 `std::vector<int>` 等）

```cpp
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

const int INSERTION_SORT_THRESHOLD = 16;

// 插入排序（处理小范围）
template<typename RandomIt>
void insertion_sort(RandomIt first, RandomIt last) {
    for (auto i = first + 1; i < last; ++i) {
        auto key = *i;
        auto j = i;
        while (j > first && *(j - 1) > key) {
            *j = *(j - 1);
            --j;
        }
        *j = key;
    }
}

// 堆排序（最坏情况）
template<typename RandomIt>
void heapsort(RandomIt first, RandomIt last) {
    std::make_heap(first, last);
    std::sort_heap(first, last);  // sort_heap 也是标准库函数
}

// 快速排序的 partition 操作
template<typename RandomIt>
RandomIt partition(RandomIt first, RandomIt last) {
    auto pivot = *(first + (last - first) / 2);
    auto left = first;
    auto right = last - 1;
    while (true) {
        while (*left < pivot) ++left;
        while (*right > pivot) --right;
        if (left >= right) return left;
        std::iter_swap(left, right);
        ++left;
        --right;
    }
}

// introsort 主体
template<typename RandomIt>
void introsort_impl(RandomIt first, RandomIt last, int depth_limit) {
    auto size = last - first;
    if (size <= INSERTION_SORT_THRESHOLD) {
        insertion_sort(first, last);
        return;
    }
    if (depth_limit == 0) {
        heapsort(first, last);
        return;
    }

    auto pivot = partition(first, last);
    introsort_impl(first, pivot, depth_limit - 1);
    introsort_impl(pivot, last, depth_limit - 1);
}

// 公共接口
template<typename RandomIt>
void introsort(RandomIt first, RandomIt last) {
    int depth_limit = 2 * std::log2(last - first);
    introsort_impl(first, last, depth_limit);
}
```

---

使用示例

```cpp
int main() {
    std::vector<int> vec = {5, 2, 9, 1, 7, 3, 8, 6};

    introsort(vec.begin(), vec.end());

    for (int x : vec)
        std::cout << x << " ";
}
```

---

特点说明：

* 使用 `partition` 实现中间选 pivot。
* `std::make_heap` 和 `std::sort_heap` 用于堆排序。
* `insertion_sort` 对小数组效率较高。
* 没有支持自定义比较器、投影、泛型容器等高级功能（如真实 `std::sort`）。

---
##  `std::sort` 使用自定义比较器

### 1. 使用 lambda 表达式的方式：

```cpp
#include <algorithm>
#include <vector>
#include <iostream>

int main() {
    std::vector<int> v = {5, 2, 8, 1, 4};

    // 降序排序
    std::sort(v.begin(), v.end(), [](int a, int b) {
        return a > b;
    });

    for (int x : v)
        std::cout << x << " ";
}
```

---

### 2. 排序结构体（按字段）：

```cpp
struct Person {
    std::string name;
    int age;
};

std::vector<Person> people = {
    {"Alice", 30}, {"Bob", 25}, {"Charlie", 35}
};

// 按年龄升序
std::sort(people.begin(), people.end(), [](const Person& a, const Person& b) {
    return a.age < b.age;
});
```

---

总结：`std::sort(begin, end, 比较函数)`，比较函数可以是 lambda、函数指针、函数对象。

---

## `std::fill`
`std::fill` 是 C++ 标准库中的一个函数，用来**将指定范围内的所有元素赋值为同一个值**。它非常适合用来初始化数组、`vector` 或任何支持迭代器的数据结构。

---

### 函数原型（来自 `<algorithm>` 头文件）：

```cpp
template< class ForwardIt, class T >
void fill(ForwardIt first, ForwardIt last, const T& value);
```

* `first`：起始迭代器（包含）
* `last`：结束迭代器（不包含）
* `value`：要赋的值
* 即左闭右开`[first, last)`

---

### 常见用法举例：

#### 1. 填充 `vector` 所有元素为 0：

```cpp
#include <vector>
#include <algorithm>

int main() {
    std::vector<int> nums(10);  // 默认构造10个元素
    std::fill(nums.begin(), nums.end(), 0);  // 全部填0
}
```

#### 2. 填充数组：

```cpp
#include <algorithm>

int main() {
    int arr[5];
    std::fill(arr, arr + 5, 7);  // 把所有元素填成 7
}
```

#### 3. 填充部分范围：

```cpp
std::fill(nums.begin() + 2, nums.begin() + 5, 42);  // 填充第3~5个元素为42
```

---

### 注意：

* `std::fill` 只能用在**支持前向迭代器的容器**，如：`vector`, `array`, `deque`, 原生数组等。
* 如果使用 `std::fill(v.begin(), v.end(), value)`，确保容器已经有元素，否则无效（不分配空间，只赋值）。

---

### 🆚 其他类似函数：

* `std::fill_n(first, count, value)`：从 `first` 开始，连续填 `count` 个值为 `value`
* `std::iota(first, last, start)`：从 `start` 开始，递增赋值，比如 0,1,2,...

---

## `reserver()` 和 `resize()`
常用的 C++ STL 容器（主要是 `vector`）成员函数或算法函数
---
### **1. reserve()**

**作用**：

* **预留容量**，改变容器的 **capacity**，但不改变 **size**。

 **使用场景**：

* 提前分配内存，避免多次扩容，提升 push\_back 时的性能。

**例子**：

```cpp
#include <vector>
#include <iostream>
using namespace std;

int main() {
    vector<int> v;
    v.reserve(100); // 预留容量为100，v.size() 仍然是 0

    cout << "v.size(): " << v.size() << endl;       // 0
    cout << "v.capacity(): " << v.capacity() << endl; // >=100

    return 0;
}
```
---

### **2. resize()**

**作用**：

* 改变容器的 **size（大小）**。
* 如果变大，会在末尾插入默认值（对 `int` 为 0）。
* 如果变小，会丢弃末尾的元素。

**例子**：

```cpp
#include <vector>
#include <iostream>
using namespace std;

int main() {
    vector<int> v = {1, 2, 3};
    v.resize(5); // 变成 {1,2,3,0,0}
    
    for (int x : v) cout << x << " ";
    cout << endl;

    v.resize(2); // 变成 {1,2}
    for (int x : v) cout << x << " ";
    cout << endl;

    return 0;
}
```
### **总结**

| 函数        | 所在位置          | 作用                  |
| --------- | ------------- | ------------------- |
| reserve() | vector成员函数    | 预留容量，不改变元素个数        |
| resize()  | vector成员函数    | 改变元素个数，可能插入默认值或删除元素 |

---