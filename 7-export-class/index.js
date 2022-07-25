const addon = require("./build/Release/addonName.node");

console.log("addon: ", addon);
console.log('\n');

const prevInstance = new addon.WrappedClass(4.3);
console.log("Initial value : ", prevInstance.getValue());
console.log("After adding 3.3 : ", prevInstance.add(3.3));

const newFromExisting = new addon.WrappedClass(prevInstance);
console.log("Testing class initial value for derived instance: ", newFromExisting.getValue());


module.exports = addon;

