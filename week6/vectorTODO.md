作者：minecode
链接：https://www.zhihu.com/question/576003237/answer/2824860858
来源：知乎
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。

* 模板中除了指定存储元素的类型，还要接受分配器类型，并且可以指定 `std::allocator`作为默认分配器类型；然后在容器里要存储这个分配器，后续的内存操作都用这个分配器来做，C++标准对于内存分配器是有规定的，必须具备所要求的接口和成员类型；
* 在编译期判断元素类型是不是平凡类型，如果是的话则允许用 `memcpy`优化（如果想用轮子造轮子的话，可以直接用 `std::copy`/`std::copy_n`，已经做了编译期区分）；
* 需要定义 `value_type`、`pointer`、`reference`、`difference_type`、`iterator`等标准规定的容器必须定义的成员类型；
* 需要实现默认构造、复制构造、复制赋值、移动构造、移动赋值、析构这6种基本的方法；
* 需要实现两种迭代器（`iterator`、`const_iterator`）（其实 `STL`中的 `vector`的迭代器就是个平凡迭代器，直接用指针也未尝不可，但如果你打算采用非连续内存的方式实现 `vector`，比如 `std::deque`的分页式管理，那这个迭代器就需要单独设计了，需要实现 `operator++()`、`operator++(int)`、`operator+=`、`operator<=>`等随机访问迭代器所必须有的接口，C++标准对于随机访问迭代器是有规定的，且根据你想要支持的C++标准，又分为[C++17迭代器](https://zhida.zhihu.com/search?content_id=543696175&content_type=Answer&match_order=1&q=C%2B%2B17%E8%BF%AD%E4%BB%A3%E5%99%A8&zhida_source=entity)（又称老式迭代器）和[C++20迭代器](https://zhida.zhihu.com/search?content_id=543696175&content_type=Answer&match_order=1&q=C%2B%2B20%E8%BF%AD%E4%BB%A3%E5%99%A8&zhida_source=entity)，分别需要定义 `iterator_category`和 `iterator_concept`，而C++20的 `iterator_concept`又对随机访问迭代器和连续迭代器做了区别，需要根据内存管理的方式进行选择）；
* 部分成员函数如 `begin()`要区分const版本，以返回对应的迭代器，对于不修改容器的函数如 `size()`则都要标const说明符；
* 对成员函数进行 `noexcept(noexcept(...))`判定，以静态判断函数执行过程中会不会抛出异常；
* 实现一些构造函数，比如从初始化列表构造、从迭代器对构造；
* 如果支持c++20，则给分配器成员变量标一个 `[[no_unique_address]]`属性，否则采用继承的方法（libstdc++等标准库都是这么操作的，继承空基类不会占空间），来防止空的分配器类型成员占用空间；
* 诸如 `push_back`这样的接口，实现接受左值和右值两种参数的版本，一个复制赋值，一个移动赋值；实现接受参数包的 `emplace_back`，来实现直接构造。实现这些函数时，要用 `std::forward`来转发参数；
* 实现各种各样的接口，比如 `erase`需要调用分配器的 `deallocate`来析构元素（或若 `value_type`为平凡类型则可以跳过，可以用 `if constexpr()`做判断） ，并让维护长度减少。
