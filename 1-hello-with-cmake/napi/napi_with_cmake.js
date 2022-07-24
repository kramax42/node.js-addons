let addon = require('bindings')('build-napi-with-cmake');

console.log(addon.sayHello());
