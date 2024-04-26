@echo off
emcc gradOS.c -Os -g2 -sWASM=1 -sIMPORTED_MEMORY=1 -o gradOS.js -sEXPORTED_FUNCTIONS=_malloc && del gradOS.js