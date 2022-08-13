'use strict'

const exampleAddon = require('bindings')('addon');

console.log(exampleAddon.increment()); // prints 43
console.log(exampleAddon.increment()); // prints 44
console.log(exampleAddon.subObject.decrement()); // prints 43

const callback = (a) => console.log(a);

// As nodejs works on event loop and
// it will assign the IO operation to thread pool,
// but thread pool default size is 4,
// so at same time maximum 4 thread (IO operation)
// can work and rest has to wait in queue.
// Once any thread complete the execution, they can process.
console.log('* START ECHO ASYNC WORKER *');
exampleAddon.echoAsyncWorker("1", callback);
exampleAddon.echoAsyncWorker('2', callback);
exampleAddon.echoAsyncWorker('3', callback);
exampleAddon.echoAsyncWorker('4', callback);

exampleAddon.echoAsyncWorker('5', callback);
exampleAddon.echoAsyncWorker('6', callback);
exampleAddon.echoAsyncWorker('7', callback);
exampleAddon.echoAsyncWorker('8', callback);

console.log('* END ECHO ASYNC WORKER *');

const num = 99
exampleAddon.incrementAsyncWorker(num, (result) => console.log(`${num} + 1 = ${result}`));