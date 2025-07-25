# 多态

多态：函数调用的多种形态，使用多态能够使得不同的对象去完成同一件事时，产生不同的动作和结果。不同继承关系的类对象，去调用同一函数，产生了不同的行为。

在继承中要想构成多态需要满足两个条件：
1. 必须通过基类的指针或者引用调用虚函数。
2. 被调用的函数必须是虚函数，且派生类必须对基类的虚函数进行重写。

# 虚函数

> **虚函数就是支持子类重写、基类指针/引用调用时能动态选择正确函数的一种机制，是 C++ 实现运行时多态性的核心。**
> 
> **虚函数**就是在基类（父类）中用 `virtual` 关键字声明/修饰的成员函数，允许在**子类中重新定义（重写）**，并且通过**基类指针或引用**调用时，能够**动态决定实际调用子类的版本**。
> 
> **虚函数 = 支持运行时动态绑定（多态性）的函数。**

---

## 为什么需要虚函数？

正常情况下，如果你用**父类指针/引用**去调用一个函数，默认是**编译时绑定**（根据指针类型确定调用哪个函数）。

但如果一个函数是**虚函数**，那么编译器会**延迟到运行时**，根据指针/引用指向的对象实际类型去选择调用哪个函数。这就是**运行时多态**！

| 术语        | 解释 |
|:-----------|:-----|
| 静态绑定    | 编译期确定调用哪个函数（非虚函数默认就是这样） |
| 动态绑定    | 运行期根据对象实际类型决定调用哪个函数（虚函数支持动态绑定） |
| 多态性      | 同一调用接口，根据对象不同表现出不同的行为 |
| override关键字 | C++11 引入，用来明确表示重写虚函数，增强可读性和安全性 |


| 特性            | 说明 |
|:----------------|:-----|
| `virtual` 修饰函数 | 告诉编译器这个函数将来可能会被子类重写 |
| 必须通过**基类指针/引用**调用 | 才能体现出多态性，否则就是正常调用 |
| 支持**运行时多态** | 调用的版本根据实际对象决定 |

注：
1. 只有类的非静态成员函数前可以加virtual，普通函数前不能加virtual。
2. 虚函数这里的virtual和虚继承中的virtual是同一个关键字，但是它们之间没有任何关系。虚函数这里的virtual是为了实现多态，而虚继承的virtual是为了解决菱形继承的数据冗余和二义性。

## 虚函数的重写

也叫做虚函数的覆盖，若派生类中有一个和基类完全相同的虚函数(返回值类型相同、函数名相同以及参数列表完全相同)，此时我们称该派生类的虚函数重写了基类的虚函数。

可以通过父类的指针或者引用调用虚函数，此时不同类型的对象，调用的就是不同的函数，产生的也是不同的结果，进而实现了函数调用的多种形态。

```cpp
//父类
class Person
{
public:
	//父类的虚函数
	virtual void BuyTicket()
	{
		cout << "买票-全价" << endl;
	}
};
//子类
class Student : public Person
{
public:
	//子类的虚函数重写了父类的虚函数
	virtual void BuyTicket()
	{
		cout << "买票-半价" << endl;
	}
};
//子类
class Soldier : public Person
{
public:
	//子类的虚函数重写了父类的虚函数
	virtual void BuyTicket()
	{
		cout << "优先-买票" << endl;
	}
};

void Func(Person& p)
{
	//通过父类的引用调用虚函数
	p.BuyTicket();
}
void Func(Person* p)
{
	//通过父类的指针调用虚函数
	p->BuyTicket();
}
int main()
{
	Person p;   //普通人
	Student st; //学生
	Soldier sd; //军人

	Func(p);  //买票-全价
	Func(st); //买票-半价
	Func(sd); //优先买票

	Func(&p);  //买票-全价
	Func(&st); //买票-半价
	Func(&sd); //优先买票
	return 0;
}
```

注：
1. 重写基类虚函数，派生类的虚函数不加virtual关键字也可以构成重写，主要原因是因为基类的虚函数被继承下来了，在派生类中依旧保持虚函数属性。但是这种写法不是很规范，因此建议在派生类的虚函数前也加上virtual关键字。

### 虚函数重写的两个特例

- 协变Covariance：
    
    基类与派生类虚函数的**返回值类型**不同，派生类重写基类的虚函数时，返回类型可以是基类返回类型的派生类型。

    注：
    1. 协变只适用于返回类型是指针或引用。
    2. 派生类的返回类型必须是基类返回类型的派生类型。
    3. 函数参数类型不支持协变（也不能逆变），必须完全一致。
    4. 只有在**虚函数重写（override）**时才适用协变。

- 析构函数的重写：

    如果基类的析构函数为虚函数，此时派生类析构函数只要定义，无论是否加virtual关键字，都与基类的析构函数构成重写，虽然基类与派生类析构函数名字不同

    例如：
    ```cpp
        int main()
    {
        //分别new一个父类对象和子类对象，并均用父类指针指向它们
        Person* p1 = new Person;
        Person* p2 = new Student;

        //使用delete调用析构函数并释放对象空间
        delete p1;
        delete p2;
        return 0;
    }
    ```
    > 若是父类和子类的析构函数没有构成重写就可能会导致内存泄漏，因为此时delete p1和delete p2都是调用的父类的析构函数，而我们所期望的是p1调用父类的析构函数，p2调用子类的析构函数，即我们期望的是一种多态行为。
    >
    > 此时只有父类和子类的析构函数构成了重写，才能使得delete按照我们的预期进行析构函数的调用，才能实现多态。因此，为了避免出现这种情况，比较建议将父类的析构函数定义为虚函数。
    >
    > 在继承当中，表面上看子类的析构函数和父类的析构函数的函数名不同，但是为了构成重写，编译后析构函数的名字会被统一处理成`destructor();`。

    # 重载、覆盖(重写)、隐藏(重定义)

    - 重载
        1. 发生在同一个作用域（通常是同一个类中）
        2. 函数名相同，参数类型或个数不同
        3. 与是否是虚函数无关
        4. 编译时根据参数决定调用哪个版本
        5. 支持返回类型不同，但不能只靠返回类型来区分

    - 覆盖（重写）
        1. 两个函数分别在基类和派生类的作用域
        2. 父类函数必须是 virtual，子类中函数名、函数参数、返回值必须相同（返回类型可协变）
        3. 两个函数必须都是虚函数
        3. 支持运行时多态：调用的是子类版本

    - 隐藏（重定义）
        1. 两个函数分别在基类和派生类的作用域
        2. 同名但不同参数。即使参数不同，也会隐藏所有同名的父类函数
        3. 两个基类和派生类的同名函数不构成重写就是重定义
        4. 需要用 using Base::show; 恢复基类函数可见性
        5. 不支持多态

# 抽象类

纯虚函数：在虚函数的后面写上=0，包含纯虚函数的类叫做抽象类（也叫接口类），抽象类不能实例化出对象。

派生类继承抽象类后也不能实例化出对象，只有重写纯虚函数，派生类才能实例化出对象。

抽象类存在的意义是什么？

> 抽象类可以更好的去表示现实世界中，没有实例对象对应的抽象类型，比如：植物、人、动物等。
>
> 抽象类很好的体现了虚函数的继承是一种接口继承，强制子类去重写纯虚函数，因为子类若是不重写从父类继承下来的纯虚函数，那么子类也是抽象类也不能实例化出对象。

> 实现继承和接口继承
>
> 实现继承：普通函数的继承是一种实现继承，派生类继承了基类函数的实现，可以使用该函数。
>
> 接口继承：虚函数的继承是一种接口继承，派生类继承的是基类虚函数的接口，目的是为了重写，达成多态。
>
> 如果不实现多态，就不要把函数定义成虚函数。

# 虚函数表

类实例化对象后，此对象当中除了成员外，实际上还有一个_vfptr放在对象的前面（有些平台可能会放到对象的最后面，这个跟平台有关）

对象中的这个指针叫做虚函数表指针，简称虚表指针，虚表指针指向一个虚函数表，简称虚表，每一个含有虚函数的类中都至少有一个虚表指针。

虚表指针指向属于自己的虚表，虚表当中存储的就是虚函数的地址，包含继承的父类的虚函数和自己重写的虚函数。

虚函数表本质是一个存虚函数指针的指针数组，一般情况下会在这个数组最后放一个nullptr

> 虚函数的重写也叫做覆盖，覆盖就是指虚表中虚函数地址的覆盖，重写是语法的叫法，覆盖是原理层的叫法

### 派生类的虚表生成步骤
1. 先将基类中的虚表内容拷贝一份到派生类的虚表。
2. 如果派生类重写了基类中的某个虚函数，则用派生类自己的虚函数地址覆盖虚表中基类的虚函数地址。
3. 派生类自己新增加的虚函数按其在派生类中的声明次序增加到派生类虚表的最后。

虚表实际上是在**构造函数初始化列表阶段**进行初始化的，注意虚表当中存的是虚函数的地址不是虚函数，虚函数和普通函数一样，都是存在代码段的，只是他的地址又存到了虚表当中。另外，对象中存的不是虚表而是指向虚表的指针。

虚表实际上是存在代码段的。（也有说是存储在数据段和静态常量区）

# 多态的原理

- 不同对象去完成同一行为时，展现出不同的形态
- 对象Mike中包含一个成员变量_p和一个虚表指针，对象Johnson中包含两个成员变量_p和_s以及一个虚表指针，这两个对象当中的虚表指针分别指向自己的虚表
- 父类指针p1指向Mike父类对象，p1->BuyTicket在Mike的虚表中找到的虚函数就是Person::BuyTicket。
- 父类指针p2指向Johnson子类对象，p2>BuyTicket在Johnson的虚表中找到的虚函数就是Student::BuyTicket。

> 现在想想多态构成的两个条件，一是完成虚函数的重写，二是必须使用父类的指针或者引用去调用虚函数。
>
> 必须完成虚函数的重写是因为我们需要完成子类虚表当中虚函数地址的覆盖，
>
> 必须使用父类的指针或者引用去调用虚函数，因为使用父类对象去调用虚函数达不到多态的效果。
>
> 父类指针/引用 指向子类对象：不切片，虚表仍然是子类的 → 支持多态。（逻辑上只能“看到”父类那一部分内容，但底层仍然是完整子类对象）
>
> 父类对象 复制子类对象（值传递）：切片发生，虚表变成父类的 → 不支持多态。

# 动态绑定和静态绑定

## 一、静态绑定（Static Binding）

* 又称 **前期绑定（Early Binding）**。
* 编译阶段就**决定调用哪个函数**。
* 不需要通过虚函数机制，也不依赖运行时的对象类型。
* 属于 **静态多态**，典型例子如 **函数重载** 和 **模板实例化**。

### 特点：

* 编译时确定函数地址
* 执行速度更快
* 无需虚表（vtable）支持
* 不支持运行时多态

## 二、动态绑定（Dynamic Binding）

* 又称 **后期绑定（Late Binding）**。
* 函数的调用在运行时根据**对象的实际类型**决定。
* 必须使用 **虚函数（virtual）** 并通过 **基类指针或引用** 调用。
* 属于 **动态多态**。

### 特点：

* 运行时查找函数地址（通过虚表）
* 灵活，支持多态
* 性能略低于静态绑定（但代价小）
* 实现基于虚表（vtable）机制

## 注
1. **非虚函数永远是静态绑定**：
2. **虚函数必须通过指针或引用实现动态绑定**：
3. **析构函数要声明为虚函数，防止内存泄漏**：

## 与相关概念的对照

| 概念          | 示例                               | 属于哪种绑定        |
| ----------- | -------------------------------- | ------------- |
| 函数重载        | `f(int)` vs `f(double)`          | 静态绑定          |
| 函数模板        | `template<typename T> void f(T)` | 静态绑定          |
| 虚函数         | `virtual void f()`               | 动态绑定（取决于调用方式） |
| 普通函数        | `void f()`                       | 静态绑定          |
| 覆盖 override | 子类覆盖基类虚函数                        | 动态绑定          |

# 单继承和多继承关系的虚函数表

## 单继承中的虚函数表

派生类的虚表生成过程如下：
1. 继承基类的虚表内容到派生类的虚表。
2. 对派生类重写了的虚函数地址进行覆盖，比如func1。
3. 虚表当中新增派生类当中新的虚函数地址，比如func3和func4。

## 多继承中的虚函数表

![1-3](/Pictures/Inheritance/1-3.png)
![1-4](/Pictures/Inheritance/1-4.png)

派生类的虚表生成过程如下：
1. 分别继承各个基类的虚表内容到派生类的各个虚表当中。
2. 对派生类重写了的虚函数地址进行覆盖(派生类中的各个虚表中存有该被重写虚函数地址的都需要进行覆盖)，比如func1。
3. 在派生类第一个继承基类部分的虚表当中新增派生类当中新的虚函数地址，比如func3。

## 菱形继承、菱形虚拟继承的虚函数表

A类当中有一个虚函数funcA，B类当中有一个虚函数funcB，C类当中有一个虚函数funcC，D类当中有一个虚函数funcD。此外B类、C类和D类当中均对A类当中的funcA进行了重写

A类对象的成员包括一个虚表指针和成员变量_a，虚表指针指向的虚表当中存储的是A类虚函数funcA的地址。
![1-5](/Pictures/Inheritance/1-5.png)

B类对象当中将A类继承下来的成员放到了最后，除此之外，B类对象的成员还包括一个虚表指针、一个虚基表指针和成员变量_b，虚表指针指向的虚表当中存储的是B类虚函数funcB的地址。虚基表当中存储的是两个偏移量，第一个是虚基表指针距离B虚表指针的偏移量，第二个是虚基表指针距离虚基类A的偏移量。
![1-6](/Pictures/Inheritance/1-6.png)

C同B
![1-7](/Pictures/Inheritance/1-7.png)

D类对象当中成员的分布情况较为复杂，D类的继承方式是菱形虚拟继承，在D类对象当中，将A类继承下来的成员放到了最后，除此之外，D类对象的成员还包括从B类继承下来的成员、从C类继承下来的成员和成员变量_d。
注，D类对象当中的虚函数funcD的地址是存储到了B类的虚表当中。
![1-8](/Pictures/Inheritance/1-8.png)

问答：
1. inline函数可以是虚函数吗？
> 内联函数是会在调用的地方展开的，也就是说内联函数是没有地址的，但是内联函数是可以定义成虚函数的（语法上允许），当我们把内联函数定义虚函数后，编译器就忽略了该函数的内联属性，这个函数就不再是内联函数了，因为需要将虚函数的地址放到虚表中去。
>
> 虚函数（virtual function）理论上可以是内联函数（inline），但实际中几乎不会真正内联。因为虚函数的特性（运行时决定调用哪个函数）和内联的特性（编译时展开函数体）天然冲突。

2. 静态成员函数可以是虚函数吗？
> 静态成员函数不能是虚函数，因为静态成员函数没有this指针，使用类型::成员函数的调用方式无法访问虚表，所以静态成员函数无法放进虚表。

3. 构造函数可以是虚函数吗？
> 构造函数不能是虚函数，因为对象中的虚表指针是在构造函数初始化列表阶段才初始化的，

4. 析构函数可以是虚函数吗？什么场景下析构函数是虚函数？
> 析构函数可以是虚函数，并且最后把基类的析构函数定义成虚函数。若是我们分别new一个父类对象和一个子类对象，并均用父类指针指向它们，当我们使用delete调用析构函数并释放对象空间时，只有当父类的析构函数是虚函数的情况下，才能正确调用父类和子类的析构函数分别对父类和子类对象进行析构，否则当我们使用父类指针delete对象时，只能调用到父类的析构函数。

5. 对象访问普通函数快还是虚函数更快？
> 对象访问普通函数比访问虚函数更快，若我们访问的是一个普通函数，那直接访问就行了，但当我们访问的是虚函数时，我们需要先找到虚表指针，然后在虚表当中找到对应的虚函数，最后才能调用到虚函数。