import { readFileSync, writeFileSync } from 'fs';

const wasm = readFileSync('output/calc.wasm');
const js = readFileSync('output/calc.js', 'utf8');

const base64 = wasm.toString('base64');
const code = `const wasmBinary = Uint8Array.from(atob('${base64}'), c => c.charCodeAt(0));
${js.replace('var wasmBinary;', '')}`;

writeFileSync('src/frontend/wasm-inline.js', code);
console.log('WASM inlined');
