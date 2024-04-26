#!/bin/bash
emcc gradOS.c -Os -g2 -sWASM=1 -sIMPORTED_MEMORY=1 -o gradOS.js -sEXPORTED_FUNCTIONS=_malloc && rm gradOS.js