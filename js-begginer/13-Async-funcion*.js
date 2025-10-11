/////////
//async function* 
// async function* 声明创建一个 AsyncGeneratorFunction 对象。
// 每次调用异步生成器函数时，它都会返回一个新的 AsyncGenerator 对象，
// 该对象符合异步迭代器协议。每次调用 next() 都会返回一个 Promise 对象，
async function* myGenerator(step) {
    await new Promise((resolve) => setTimeout(resolve, 10));
    yield 0;
    yield step;
    yield step * 2;
}

const gen = myGenerator(2);
gen
    .next()
    .then((res) => {
        console.log(res); // { value: 0, done: false }
        return gen.next();
    })
    .then((res) => {
        console.log(res); // { value: 2, done: false }
        return gen.next();
    })
    .then((res) => {
        console.log(res); // { value: 4, done: false }
        return gen.next();
    })
    .then((res) => {
        console.log(res); // { value: undefined, done: true }
        return gen.next();
    });