let addon = require('bindings')('addon');

let obj1 = addon.createObject(10);
let obj2 = addon.createObject(20);
let result = addon.add(obj1, obj2);

console.log(result); // 30
