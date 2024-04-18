@echo off
emcc gradOS.c -Os -g2 -s WASM=1 -o gradOS.js && del gradOS.js