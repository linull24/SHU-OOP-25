function outside() {
  const x = 5;
  function inside(x) {
    return x * 2;
  }
  return inside;
}

console.log(outside()(10)); // 20（而不是 10）

/*
链式函数调用语法说明：

outside()(10) 是JavaScript中的链式函数调用，也叫函数柯里化调用

语法分解：
1. outside() - 调用第一个函数
2. (10) - 对第一步的返回结果再次调用

等价写法：
const returnedFunction = outside();  // 获取返回的函数
returnedFunction(10);                // 调用返回的函数

工作原理：
1. 第一次调用 outside()：返回 inside 函数（函数本身，不是调用结果）
2. 第二次调用 (10)：对返回的 inside 函数传入参数 10，执行 inside(10)

关键概念：
这种语法成立的前提是第一个函数必须返回另一个函数
这是JavaScript中高阶函数的典型用法，函数可以作为返回值传递
*/