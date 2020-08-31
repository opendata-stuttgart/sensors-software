Import("env")
import os
import shutil
from base64 import b64decode

try:
    import configparser
except ImportError:
    import ConfigParser as configparser

config = configparser.ConfigParser()
config.read("platformio.ini")

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

  configName = b64decode(ARGUMENTS.get("PIOENV"))
  sectionName = 'env:' + configName.decode('utf-8')
  lang = config.get(sectionName, "lang")
  target_name = lang
  shutil.copy(target[0].path, "./builds/latest_"+target_name.lower()+".bin")

env.AddPostAction("$BUILD_DIR/firmware.bin", after_build)
