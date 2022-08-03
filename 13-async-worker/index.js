
const runWorker = require('bindings')('napi-async-worker');

function asyncWorkerCompletion(err, result) {
    if (err) {
        console.log("SimpleAsyncWorker returned an error: ", err);
    } else {
        console.log("SimpleAsyncWorker returned '" + result + "'.");
    }
};

let result = runWorker.runSimpleAsyncWorker(2, asyncWorkerCompletion);
console.log("runSimpleAsyncWorker returned '" + result + "'.");

result = runWorker.runSimpleAsyncWorker(4, asyncWorkerCompletion);
console.log("runSimpleAsyncWorker returned '" + result + "'.");

result = runWorker.runSimpleAsyncWorker(8, asyncWorkerCompletion);
console.log("runSimpleAsyncWorker returned '" + result + "'.");