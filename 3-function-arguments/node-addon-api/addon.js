let addon = require('bindings')('addon')

const a = 5;
const b = 11;
console.log(`${a} + ${b} = `, addon.add(a, b));
