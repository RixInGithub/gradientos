#!/bin/bash
echo NOTE: the gradOS.js file this command generates is not the JS you should be using. Read the README from more info.
emcc gradOS.c -Os -g2 -sWASM=1 -sIMPORTED_MEMORY=1 -o gradOS.js -sEXPORTED_FUNCTIONS=_malloc && rm gradOS.js