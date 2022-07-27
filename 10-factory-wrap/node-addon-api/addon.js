let MyObject = require('bindings')('addon');

console.log(MyObject)

let obj = MyObject(10);
console.log(obj.plusOne()); // 11
console.log(obj.plusOne()); // 12
console.log(obj.plusOne()); // 13

let obj2 = MyObject(20);
console.log(obj2.plusOne()); // 21
console.log(obj2.plusOne()); // 22
console.log(obj2.plusOne()); // 23
