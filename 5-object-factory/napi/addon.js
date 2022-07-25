let addon = require('bindings')('addon');

let obj1 = addon('Hello');
let obj2 = addon('world');

console.log(`${obj1.msg} ${obj2.msg}!`);