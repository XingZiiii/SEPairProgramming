import assert from "assert";

// Choose proper "import" depending on your PL.
// import { bocchiShutUp } from "./t1_cpp/example.js";
// import { bocchi_shut_up as bocchiShutUp } from "./t1_rust/pkg/t1_rust.js"
// [Write your own "import" for other PLs.]
// const { bocchiShutUp } = require('./t1_cpp/bocchiShutUp.js')

import Module from "./t1_cpp/function.js";

var RealModule = await Module()
var callBocchiShutUp = RealModule.cwrap('bocchiShutUp', 'number', ['number', 'number', 'number'])

function bocchiShutUp(flag, array, size) {
    const bytesPerElement = Int32Array.BYTES_PER_ELEMENT;
    const numBytes = size * bytesPerElement;
    const ptr = RealModule._malloc(numBytes);
    
    let heapView = new Int32Array(RealModule.HEAP32.buffer, ptr, size);
    heapView.set(array);
    
    const result = callBocchiShutUp(flag, ptr, size);
    
    RealModule._free(ptr);

    return result;
}


assert.strictEqual(bocchiShutUp(1,[13,14,15,21,11,16],6),10);
assert.strictEqual(bocchiShutUp(2,[13,14,13,11,21,13,21,22],8),21);

console.log("🎉 You have passed all the tests provided.");
