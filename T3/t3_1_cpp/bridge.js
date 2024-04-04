import Module from "./function.js";

var RealModule = await Module()

var callMancalaBoard = RealModule.cwrap("mancalaBoard", "number", ["number", "number", "number"]);

export function mancalaBoard(flag, seq, size) {
    const bytesPerElement = Int32Array.BYTES_PER_ELEMENT;
    const numBytes = size * bytesPerElement;
    const ptr = RealModule._malloc(numBytes);
    
    let heapView = new Int32Array(RealModule.HEAP32.buffer, ptr, size);
    heapView.set(seq);
    
    const result = callMancalaBoard(flag, ptr, size);
    const len = 15;
    const resultArray = RealModule.HEAP32.subarray(result / 4, result / 4 + len);
    return resultArray;
}