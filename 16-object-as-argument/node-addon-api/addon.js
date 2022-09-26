let addon = require('bindings')('addon')

const obj = {
    a: 3,
    b: 5,
}
const sum = addon.sumAllProps(obj);
console.log(`${obj.a} + ${obj.b} = `, sum);
