let addon = require('bindings')('addon')

const a = 8;
const b = 80;
console.log(`${a} + ${b} = `, addon.add(a, b));
