import subprocess
import glob

libs = " ".join(glob.glob("libs/*.c"))
cmd = f"emcc gradOS.c {libs} -Os -g2 -s WASM=1 -s IMPORTED_MEMORY=1 -x c -s EXPORTED_FUNCTIONS=_malloc -o gradOS.js"
print("NOTE: the gradOS.js file this command generates is not the JS you should be using. Read the README from more info.")
result = subprocess.run(cmd, text=True, shell=True)

if result.returncode == 0:
	print("\n\u001b[1m\u001b[32;1mSuccess in compiling.\u001b[0m")
else:
	print("\n\u001b[1m\u001b[31;1mFailure in compiling.\u001b[0m")