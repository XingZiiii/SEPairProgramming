import Module from "./function.js";

var RealModule = await Module()
var callMancalaResult = RealModule.cwrap('mancalaResult', 'number', ['number', 'number', 'number'])

export function mancalaResult(flag, array, size) {
    const bytesPerElement = Int32Array.BYTES_PER_ELEMENT;
    const numBytes = size * bytesPerElement;
    const ptr = RealModule._malloc(numBytes);
    
    let heapView = new Int32Array(RealModule.HEAP32.buffer, ptr, size);
    heapView.set(array);
    
    const result = callMancalaResult(flag, ptr, size);
    
    RealModule._free(ptr);

    return result;
}