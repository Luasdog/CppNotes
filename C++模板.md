# 函数模板

在使用时被参数化，根据实参类型产生函数的特定类型版本

## 函数模板格式

typename是用来定义模板参数的关键字，也可以用class代替，但是不能用struct代替

```cpp
template<typename T1,typename T2,…,typename Tn>
返回类型 函数名(参数列表)
{
  //函数体
}

如：
template<typename T>
void Swap(T& x, T& y)
{
	T tmp = x;
	x = y;
	y = tmp;
}
```

## 函数模板的实例化

1. 隐式实例化

```cpp
int c = Add(a, b); //编译器根据实参a和b推演出模板参数为int类型

若：
int a = 10;
double b = 1.1;
int c = Add(a, b);
```
使用模板时，编译器一般不会进行类型转换操作，传入两个不同类型的参数，第一种方法传参时将b强制转换为int类型，第二种使用显示实例化

2. 显示实例化

使用显示实例化时，如果传入的参数类型与模板参数类型不匹配，编译器会尝试进行隐式类型转换，如果无法转换成功，则编译器将会报错

```cpp
int c = Add<int>(a, b); //指定模板参数的实际类型为int
```

## 函数模板的匹配原则

1. 一个非模板函数可以和一个同名的函数模板同时存在，而且该函数模板还可以被实例化为这个非模板函数

```cpp
//专门用于int类型加法的非模板函数
int Add(const int& x, const int& y)
{
	return x + y;
}

//通用类型加法的函数模板
template<typename T>
T Add(const T& x, const T& y)
{
	return x + y;
}

int a = 10, b = 20;
int c = Add(a, b); //调用非模板函数，编译器不需要实例化
int d = Add<int>(a, b); //调用编译器实例化的Add函数
```                      

2. 对于非模板函数和同名的函数模板，如果其他条件都相同，在调用时会优先调用非模板函数，而不会从该模板产生出一个实例。如果模板可以产生一个具有更好匹配的函数，那么选择模板

```cpp
//专门用于int类型加法的非模板函数
int Add(const int& x, const int& y)
{
	return x + y;
}

//通用类型加法的函数模板
template<typename T1, typename T2>
T1 Add(const T1& x, const T2& y)
{
	return x + y;
}

int a = Add(10, 20); //与非模板函数完全匹配，不需要函数模板实例化
int b = Add(2.2, 2); //函数模板可以生成更加匹配的版本，编译器会根据实参生成更加匹配的Add函数
```  

3. 模板函数不允许自动类型转换，但普通函数可以进行自动类型转换

```cpp
template<typename T>
T Add(const T& x, const T& y)
{
	return x + y;
}

int a = Add(2, 2.2); //模板函数不允许自动类型转换，不能通过编译
```

# 类模板

## 类模板格式

类模板不支持分离编译，即声明在xxx.h文件中，而定义却在xxx.cpp文件中

```cpp
template<class T1,class T2,…,class Tn>
class 类模板名
{
  //类内成员声明
};

template<class T>
class Score
{
public:
	void Print()
	{
		cout << "数学:" << _Math << endl;
		cout << "语文:" << _Chinese << endl;
		cout << "英语:" << _English << endl;
	}
private:
	T _Math;
	T _Chinese;
	T _English;
};

template<class T>
class Score
{
public:
	void Print();
private:
	T _Math;
	T _Chinese;
	T _English;
};
//类模板中的成员函数在类外定义，需要加模板参数列表
template<class T>
void Score<T>::Print()
{
	cout << "数学:" << _Math << endl;
	cout << "语文:" << _Chinese << endl;
	cout << "英语:" << _English << endl;
}
```

## 类模板的实例化

类模板实例化需要在类模板名字后面跟<>，然后将实例化的类型放在<>中即可。

类模板名字不是真正的类，而实例化的结果才是真正的类

```cpp
//Score不是真正的类，Score<int>和Score<double>才是真正的类
Score<int> s1;
Score<double> s2;
```