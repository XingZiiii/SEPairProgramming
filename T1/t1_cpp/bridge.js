import Module from "./function.js";

var RealModule = await Module()
var callBocchiShutUp = RealModule.cwrap('bocchiShutUp', 'number', ['number', 'number', 'number'])

export function bocchiShutUp(flag, array, size) {
    const bytesPerElement = Int32Array.BYTES_PER_ELEMENT;
    const numBytes = size * bytesPerElement;
    const ptr = RealModule._malloc(numBytes);
    
    let heapView = new Int32Array(RealModule.HEAP32.buffer, ptr, size);
    heapView.set(array);
    
    const result = callBocchiShutUp(flag, ptr, size);
    
    RealModule._free(ptr);

    return result;
}