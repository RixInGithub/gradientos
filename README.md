# GradientOS C Source
Hello! This is the official GradientOS C source code. If you're looking for the JS source code, take a look at https://gradientos.neocities.org/wasm.js

**NOTE**: The `gradOS.js` file generated from the build command is NOT what you should be using. Instead, take a look at the JS source linked in the previous paragraph.

`gradOS.js` should only be used for searching up the global variables from the WASM to know which letter is which function.

Here, lies the GradientOS C source as well as the building command that I use to build it into WebAssembly.

**HUGE thanks to whoever wrote [this article](https://compile.fi/canvas-filled-three-ways-js-webassembly-and-webgl/) on some Finnish site for helping me start out bring out my true power for GradientOS.**
## Contributing
Contributing, as always, is done by forking, committing changes and making a pull request.

Don't worry, I will see it.

Even if there are too less contributors, I still respect all of them in my heart. ~~If only I am in the image, then I respect noone.~~

[![Contributors.](https://contrib.rocks/image/?repo=RixInGithub/gradientos)](https://github.com/RixInGithub/gradientos/graphs/contributors/)
## Building
Firstly, clone this repo. Then...

If you're on Windows, run:
```bat
build.bat
```

Else, if you're on a UNIX-like system like Mac or Linux, run:
```sh
./build.sh
```
I didn't test the UNIX-like command, so keep that in mind.

If something goes wrong during building, make sure to open an issue with the error log.