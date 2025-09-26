function myConcat(separator) {
  let result = ""; // 初始化列表
  // 迭代 arguments
  for (let i = 1; i < arguments.length; i++) {
    result += arguments[i] + separator;
  }
  return result;
}

console.log(myConcat("、", "红", "橙", "蓝"));
// "红、橙、蓝、"

console.log(myConcat("；", "大象", "长颈鹿", "狮子", "猎豹"));
// "大象；长颈鹿；狮子；猎豹；"

console.log(myConcat("。", "智者", "罗勒", "牛至", "胡椒", "香菜"));
// "智者。罗勒。牛至。胡椒。香菜。"