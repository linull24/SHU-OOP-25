/*
Promise 是一个对象，它代表了一个异步操作的最终完成或者失败。因为大多数人仅仅是使用已创建的 
Promise 实例对象，所以本教程将首先说明怎样使用 Promise，再说明如何创建 Promise。

本质上 Promise 是一个函数返回的对象，我们可以在它上面绑定回调函数，这样我们就
不需要在一开始把回调函数作为参数传入这个函数了。
*/
{
    function doSomething() {
        console.log("doSomething");
        return Promise.resolve();//兑现
    }
    function successCallback() {
        console.log("success");
    }
    function failureCallback() {
        console.log("failure");
    }
    const promise = doSomething();
    const promise2 = promise.then(successCallback, failureCallback);
}

// Promise链式调用 - 使用箭头函数
{
    // 箭头函数：(参数) => 表达式 或 (参数) => { 代码块 }
    const doSomething = () => Promise.resolve('第一步结果');
    const doSomethingElse = result => Promise.resolve(result + ' -> 第二步结果');
    const doThirdThing = result => Promise.resolve(result + ' -> 第三步结果');
    const failureCallback = error => console.log('错误:', error);
    
    // 链式调用：每个then返回新Promise，可以继续链接
    doSomething()
        .then(result => doSomethingElse(result))  // 传递结果到下一步
        .then(newResult => doThirdThing(newResult))  // 继续传递
        .then(finalResult => {
            console.log(`得到最终结果：${finalResult}`);
        })
        .catch(failureCallback);  // 捕获任何步骤的错误
}

// fetch API
// fetch会原生的返回一个Promise<Response>
{
    const doSomething = () => Promise.resolve('https://jsonplaceholder.typicode.com/posts/1');
    
    doSomething()
        .then((url) => {

            return fetch(url);
        })
        .then((result) => {
            // result 是一个 Response 对象
            return result.json(); // 解析JSON数据
        })
        .then((data) => {
            console.log('获取到的数据:', data);
        })
        .catch(error => console.log('请求失败:', error));
}
//题目：红灯三秒亮一次，绿灯一秒亮一次，黄灯2秒亮一次；如何让三个灯不断交替重复亮灯？（用Promse实现）
//三个亮灯函数已经存在：
{
    function red(){
        console.log('red');
    }
    function green(){
        console.log('green');
    }
    function yellow(){
        console.log('yellow');
    }
    const lightShowRed = () => new Promise(resolve => {
        setTimeout(() => {
            red();
            resolve();
        }, 3000);
    });
    
    const lightShowGreen = () => new Promise(resolve => {
        setTimeout(() => {
            green();
            resolve();
        }, 1000);
    });
    
    const lightShowYellow = () => new Promise(resolve => {
        setTimeout(() => {
            yellow();
            resolve();
        }, 2000);
    });
    
    const trafficLight = () => {
        lightShowRed()
            .then(() => lightShowGreen())
            .then(() => lightShowYellow())
            .then(() => trafficLight());
    };
    
    trafficLight(); // 取消注释以启动
    
}
