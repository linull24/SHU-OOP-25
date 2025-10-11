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