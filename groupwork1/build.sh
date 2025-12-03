#!/bin/bash
em++ linkedlist.cpp -o linkedlist.js \
  -lembind \
  -s WASM=1 \
  -s SINGLE_FILE=1 \
  -s MODULARIZE=1 \
  -s EXPORT_NAME="Module" \
  -O3
