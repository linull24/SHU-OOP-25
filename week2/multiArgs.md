## Cpp中函数可变参数

为了使得构造函数中，可以选择接受1-4个参数数量，但是我不希望通过写四个函数和重载来完成。

我之前学过别的脚本型语言：

例如Javascript

```javascript
function multiply(multiplier, ...theArgs) {
 return theArgs.map((x) => multiplier * x);
}
```

以及Python

```python
def flexible_function(*args, **kwargs):
    print("Positional args:", args)
    print("Keyword args:", kwargs)
    // 前者传递数值，后者传递字典
```

以及Go(虽然不是脚本语言)

```Go
func sum(numbers ...int) int {
    total := 0
    for _, num := range numbers {
        total += num
    }
    return total
}
```

C++有没有？

> 有的兄弟有的。

> 通过AI拿到一系列相关的术语
>
> 1. `typename...`, `Args&&...`, `std::forward`, `sizeof...`, `static_assert`
> 2. ：`std::initializer_list`（同类型场景）、数组展开技巧
> 3. ：折叠表达式（C++17）、Concepts（C++20）

## `...`

这实际上是C风格的东西要声明一个变长参数函数，参数列表后面会出现一个省略号，例 `printf(char *,...format)`.

在 `cstrarg`中提供了

| 类型 / 宏    | 描述                                                                | 备注                 |
| ------------ | ------------------------------------------------------------------- | -------------------- |
| `va_list`  | 存储 `va_start`、`va_arg`、`va_end` 和 `va_copy` 所需的信息 | `typedef`          |
| `va_start` | 启用对变长函数参数的访问                                            | 函数宏               |
| `va_arg`   | 访问下一个变长函数参数                                              | 函数宏               |
| `va_copy`  | 复制变长函数参数                                                    | C++11 起支持，函数宏 |
| `va_end`   | 结束变长函数参数的遍历                                              | 函数宏               |

```cpp
__BEGIN_DECLS
int	 printf(const char * __restrict, ...) __printflike(1, 2);
__END_DECLS

```

就是使用了这种风格

## `Typename...`

主要用于在模版中对应的声明可变的参数数量。

## `Args&&...`

### 转发引用forwarding reference

首先，需要注意的是，在模版中，行为与传统的左值右值有不同。

在cpp中转发的行为：

```cpp
T&  &   → T&
T&  &&  → T&
T&& &   → T&
T&& &&  → T&&
```

那么在这个场景之下，传递给 `T...`的都会被“保留原来的结构”

## `std::forward`与 `std::move`

`std::move` 将东西强制转换为右值

`std::forward` 的作用类似 `Args&&...`，调用的过程保留左值右值。

## `assert`和 `concept`的区别

### `assert`

调试用的东西，在**运行时**检查

```cpp
x=114514;
assert(x >=0 && x <100);
// 运行时如果x不满足条件,就报错
```

### `static_assert`

调试用的东西，在**编译时**检查,在cpp11引入

```cpp
static_assert(sizeof(int) == 4, "This code requires int to be 4 bytes)
// 编译时报错
```

### `concept`

在cpp20引入，主要是用于模版的检查。

> Concept其实是一个语法糖，它的本质可以认为是一个模板类型的bool变量。定义一个concept本质上是在定义一个bool类型的编译期的变量。使用一个concept本质上是利用SFINAE机制来约束模板类型。
> SFINAE:Substitution Failure Is Not An Error

网上找到了例子：

```cpp
template<std::integral T>  
T add_original(T a, T b) {
    return a + b;
}
```

$$
\equiv
$$

```
template <typename T, std::enable_if_t<std::is_integral_v<T>, int> = 0>
T add_original(T a, T b) {
    return a + b;
}
```

## std::initializer_list

```cpp
void print(std::initializer_list<int> list) {
    for (int x : list) std::cout << x << " ";
}

print({1, 2, 3});  
//内部是 const T[]
```

## 折叠表达式

| 类型                 | 语法                      | 展开                          | 例                                                     |
| -------------------- | ------------------------- | ----------------------------- | ------------------------------------------------------ |
| **一元左折叠** | `(pack op ...)`         | `((a op b) op c)`           | `(1 + 2 + 3)` → `((1 + 2) + 3) = 6`               |
| **一元右折叠** | `(... op pack)`         | `(a op (b op c))`           | `(... + 1, 2, 3)` → `(1 + (2 + 3)) = 6`           |
| **二元左折叠** | `(init op ... op pack)` | `(((init op a) op b) op c)` | `(0 + ... + 1, 2, 3)` → `(((0 + 1) + 2) + 3) = 6` |
| **二元右折叠** | `(pack op ... op init)` | `(a op (b op (c op init)))` | `(1, 2, 3 - ... - 0)` → `(1 - (2 - (3 - 0))) = 2` |
