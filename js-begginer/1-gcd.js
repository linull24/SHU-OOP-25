const gcd = function gcdRecursive(a, b) {
  return b === 0 ? a : gcdRecursive(b, a % b);
};

const gcdArrow = (a, b) => {
  return b === 0 ? a : gcdArrow(b, a % b);
};

console.log('递归方式:');
console.log(gcd(48, 18));   // 6
console.log(gcd(100, 25));  // 25

console.log('箭头函数方式:');
console.log(gcdArrow(48, 18));   // 6
console.log(gcdArrow(100, 25));  // 25