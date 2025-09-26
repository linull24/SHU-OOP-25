class Color {
  constructor(r, g, b) {
    // 将 RGB 值作为 `this` 的属性
    this.values = [r, g, b];
  }
}
const red = new Color(255, 0, 0);
console.log(red);
/////////////
class MyClass {
  constructor() {
    this.myField = "foo";
    return {};
  }
}

console.log(new MyClass().myField); // undefined
//Why undefined? 因为constructor显式返回了空对象{}，覆盖了默认的this实例，空对象没有myField属性

// Fixed version:
class MyClassFixed {
  constructor() {
    this.myField = "foo";
    // 不显式返回，默认返回this
  }
}

console.log(new MyClassFixed().myField); // "foo"