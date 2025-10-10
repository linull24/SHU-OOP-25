{
  class MyClass {
    // 构造函数
    constructor() {
      // 构造函数体
    }
    // 实例字段
    myField = "foo";
    // 实例方法
    myMethod() {
      // myMethod 体
    }
    // 静态字段
    static myStaticField = "bar";
    // 静态方法
    static myStaticMethod() {
      // myStaticMethod 体
    }
    // 静态块
    static {
      // 静态初始化代码
    }

    // 字段、方法、静态字段、静态方法、静态块都可以使用私有形式
    #myPrivateField = "bar"; // 对于私有的，以#开头
  }

  ///////////

  const myInstance = new MyClass();
  console.log(myInstance.myField); // 'foo'
  myInstance.myMethod();
}
////
//实例方法
{
  class Color {
    constructor(r, g, b) {
      this.values = [r, g, b];
      this.getRed = function () {
        return this.values[0];
      };
    }
  }
  console.log(new Color().getRed === new Color().getRed); // false
}
//因为每次实例化都创建新的函数
// 但是不应该用getXXX函数： 我们有getter的特性
{
  class Color {
    constructor(r, g, b) {
      this.values = [r, g, b];
    }
    get red() {
      return this.values[0];
    }
    set red(value) {
      this.values[0] = value;
    }
  }

  const red = new Color(255, 0, 0);
  red.red = 0;
  console.log(red.red); // 0

}
////继承
{
  class Color {
    #values;
    constructor(r, g, b) {
      this.#values = [r, g, b];
    }
    toString() {
      return this.#values.join(", ");
    }
  }

  console.log(new Color(255, 0, 0).toString()); // '255, 0, 0'
  class ColorWithAlpha extends Color {
    #alpha;
    constructor(r, g, b, alpha) {
      super(r, g, b);
      this.#alpha = alpha;
    }
    toString() {
      // 调用父类的 toString()，并以此构建新的返回值
      return `${super.toString()}, ${this.#alpha}`;
    }
  }

  console.log(new ColorWithAlpha(255, 0, 0, 0.5).toString()); // '255, 0, 0, 0.5'
}