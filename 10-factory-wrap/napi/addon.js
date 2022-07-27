let createObject = require('bindings')('addon');

console.log(createObject);

let obj = createObject(10);
console.log(obj.plusOne()); // 11
console.log(obj.plusOne()); // 12
console.log(obj.plusOne()); // 13

let obj2 = createObject(20);
console.log(obj2.plusOne()); // 21
console.log(obj2.plusOne()); // 22
console.log(obj2.plusOne()); // 23

let obj3 = createObject('20'); // Should throw TypeError

