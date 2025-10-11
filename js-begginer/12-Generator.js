{
    function* anotherGenerator(i) {
        yield i + 1;
        yield i + 2;
        yield i + 3;
    }

    function* generator(i) {
        yield i;
        yield* anotherGenerator(i);
        yield i + 10;
    }

    const gen = generator(10);

    console.log(gen.next().value); // 10
    console.log(gen.next().value); // 11
    console.log(gen.next().value); // 12
    console.log(gen.next().value); // 13
    console.log(gen.next().value); // 20
}
//   可以传参
{
    function* logGenerator() {
        console.log(0);
        console.log(1, yield);
        console.log(2, yield);
        console.log(3, yield);
    }

    const gen = logGenerator();

    // next 的第一次调用从函数的开头开始执行，直到第一个 yield 语句
    gen.next(); // 0
    gen.next("pretzel"); // 1 pretzel
    gen.next("california"); // 2 california
    gen.next("mayonnaise"); // 3 mayonnaise
}
// return之后就undefined
{
    function* gen() {
        yield 1;
        return 0;
        yield 3;
    }

    const g = gen();
    console.log(g.next()); // { value: 1, done: false }
    console.log(g.next());
    console.log(g.next());
}