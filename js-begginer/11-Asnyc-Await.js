///demo
{
    function resolveAfter2Seconds() {
        return new Promise((resolve) => {
            setTimeout(() => {
                resolve("resolved");
            }, 2000);
        });
    }

    async function asyncCall() {
        console.log("calling");
        const result = await resolveAfter2Seconds();
        console.log(result);
        // Expected output: "resolved"
    }
    asyncCall();
}
//async is not equivilant to Promise.resolve
{
    const p = new Promise((res, rej) => {
        res(1);
    });

    async function asyncReturn() {
        return p;
    }

    function basicReturn() {
        return Promise.resolve(p);
    }

    console.log(p === basicReturn()); // true
    console.log(p === asyncReturn()); // false
}
// 每个 await 表达式之后的代码可以被认为存在于 .then 回调中。
// 通过这种方式，可以通过函数的每个可重入步骤来逐步构建 promise 链。而返回值构成了链中的最后一个环。

// 在接下来的示例中，我们依次 await 两个 promise，整个 foo 函数的执行将会被分为三个阶段。

// foo 函数的第一行将会同步执行，其中 await 配置了待定的 promise。
// 然后 foo 的进程将被暂停，并将控制权交还给调用 foo 的函数。
// 一段时间后，当第一个 promise 被兑现或拒绝的时候，
// 控制权将重新回到 foo 内。第一个 promise 的兑现结果（如果没有被拒绝的话）
// 将作为 await 表达式的返回值。在这里 1 被赋值给 result1。程序继续执行，
// 并计算第二个 await 表达式。同样的，foo 的进程将被暂停，并交出控制权。
// 一段时间后，当第二个 promise 被兑现或拒绝的时候，控制权将重新回到 foo。
// 第二个 promise 的兑现结果将作为第二个 await 表达式的返回值。在这里 2 被赋值给 result2。
// 程序继续执行到返回表达式（如果有的话）。默认的返回值 undefined 将作为当前 promise 的兑现值被返回。
{
    async function foo() {
        const result1 = await new Promise((resolve) =>
            setTimeout(() => resolve("1")),
        );
        const result2 = await new Promise((resolve) =>
            setTimeout(() => resolve("2")),
        );
    }
    foo();
}
//具体的例子，from Mozilla mmdn
{
    function resolveAfter2Seconds() {
        console.log("开始较慢兑现的 promise");
        return new Promise((resolve) => {
            setTimeout(() => {
                resolve("slow");
                console.log("较慢兑现的 promise 完成了");
            }, 2000);
        });
    }

    function resolveAfter1Second() {
        console.log("开始较快兑现的 promise");
        return new Promise((resolve) => {
            setTimeout(() => {
                resolve("fast");
                console.log("较快兑现的 promise 完成了");
            }, 1000);
        });
    }

    async function sequentialStart() {
        console.log("== sequentialStart 开始 ==");

        // 1. 启动一个计时器，并在计时器完成后打印结果
        const slow = resolveAfter2Seconds();
        console.log(await slow);

        // 2. 等待前一个计时器完成后，启动下一个计时器
        const fast = resolveAfter1Second();
        console.log(await fast);

        console.log("== sequentialStart 结束 ==");
    }

    async function sequentialWait() {
        console.log("== sequentialWait 开始 ==");

        // 1. 启动两个计时器，互不等待
        const slow = resolveAfter2Seconds();
        const fast = resolveAfter1Second();

        // 2. 等待较慢的计时器完成后，打印结果
        console.log(await slow);
        // 3. 等待较快的计时器完成后，打印结果
        console.log(await fast);

        console.log("== sequentialWait 结束 ==");
    }

    async function concurrent1() {
        console.log("== concurrent1 开始 ==");

        // 1. 并发启动两个计时器，并等待它们完成
        const results = await Promise.all([
            resolveAfter2Seconds(),
            resolveAfter1Second(),
        ]);
        // 2. 同时打印两个计时器的结果
        console.log(results[0]);
        console.log(results[1]);

        console.log("== concurrent1 完成 ==");
    }

    async function concurrent2() {
        console.log("== concurrent2 开始 ==");

        // 1. 并发启动两个计时器，并在其中任意一个完成后立即打印对应结果
        await Promise.all([
            (async () => console.log(await resolveAfter2Seconds()))(),
            (async () => console.log(await resolveAfter1Second()))(),
        ]);
        console.log("== concurrent2 结束 ==");
    }

    sequentialStart(); // 2 秒后，打印“slow”，然后再过 1 秒，打印“fast”

    // 等待上面的代码执行完毕
    setTimeout(sequentialWait, 4000); // 2 秒后，打印“slow”，然后打印“fast”

    // 再次等待
    setTimeout(concurrent1, 7000); // 跟 sequentialWait 一样

    // 再次等待
    setTimeout(concurrent2, 10000); // 1 秒后，打印“fast”，然后过 1 秒，打印“slow”
}

