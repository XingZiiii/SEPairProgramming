import assert from "assert";

// Choose proper "import" depending on your PL.
// import { mancalaResult } from "./t2-as/build/release.js";
// import { mancala_result as mancalaResult } from "./t2_rust/pkg/t1_rust.js"
// [Write your own "import" for other PLs.]
import Module from "./t2_cpp/function.js";

var RealModule = await Module()
var callMancalaResult = RealModule.cwrap('mancalaResult', 'number', ['number', 'number', 'number'])

function mancalaResult(flag, array, size) {
    const bytesPerElement = Int32Array.BYTES_PER_ELEMENT;
    const numBytes = size * bytesPerElement;
    const ptr = RealModule._malloc(numBytes);
    
    let heapView = new Int32Array(RealModule.HEAP32.buffer, ptr, size);
    heapView.set(array);
    
    const result = callMancalaResult(flag, ptr, size);
    
    RealModule._free(ptr);

    return result;
}

assert.strictEqual(mancalaResult(1,[11,12],2),30001);
assert.strictEqual(mancalaResult(1,[14],1),20001);

console.log("🎉 You have passed all the tests provided.");
