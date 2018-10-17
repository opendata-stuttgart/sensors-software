Import("env")
import os
import shutil
from base64 import b64decode

flags = " ".join(env['LINKFLAGS'])
flags = flags.replace("-u _printf_float", "")
flags = flags.replace("-u _scanf_float", "")
newflags = flags.split()
env.Replace(
  LINKFLAGS=newflags
) 

def after_build(source, target, env):
  if not os.path.exists("./builds"):
    os.mkdir("./builds")
  shutil.copy(target[0].path, "./builds/latest_"+b64decode(ARGUMENTS.get("LANG"))+".bin")


env.AddPostAction("$BUILD_DIR/firmware.bin", after_build)
