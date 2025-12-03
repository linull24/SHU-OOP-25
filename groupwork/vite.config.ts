import { defineConfig } from 'vite';
import { svelte } from '@sveltejs/vite-plugin-svelte';
import { viteSingleFile } from 'vite-plugin-singlefile';

export default defineConfig({
  root: 'src',
  plugins: [svelte(), viteSingleFile()],
  build: {
    outDir: '../output',
    emptyOutDir: true
  }
});
