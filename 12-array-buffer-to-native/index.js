const binding = require('bindings')('array_buffer_to_native');

const arrSize = 10;
const array = new Int32Array(arrSize);

for (let i = 0; i < arrSize; ++i) {
    array[i] = Math.random() * 100 - 50;
}

console.log("JavaScript array buffer:");
array.forEach(num => console.log(num))

console.log("C++ array:");
binding.AcceptArrayBuffer(array.buffer);
