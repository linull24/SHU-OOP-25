import { copyFileSync } from 'fs';
import { build } from 'vite';

await build();
copyFileSync('output/index.html', 'output/output.html');
console.log('output/output.html created');
