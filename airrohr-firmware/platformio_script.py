Import("env")
import configparser
import hashlib
import os
import shutil
from base64 import b64decode

config = configparser.ConfigParser()
config.read("platformio.ini")

def _file_md5_hexdigest(fname):
    return hashlib.md5(open(fname, 'rb').read()).hexdigest()

def after_build(source, target, env):
    if not os.path.exists("builds"):
        os.mkdir("builds")

    configName = b64decode(ARGUMENTS.get("PIOENV"))
    sectionName = 'env:' + configName.decode('utf-8')
    lang = config.get(sectionName, "lang")
    target_name = lang.lower()

    with open(f"builds/latest_{target_name}.bin.md5", "w") as md5:
        print(_file_md5_hexdigest(target[0].path), file = md5)
    shutil.copy(target[0].path, f"builds/latest_{target_name}.bin")


env.AddPostAction("$BUILD_DIR/firmware.bin", after_build)
