Import("env")
import hashlib
import os
import shutil

def _file_md5_hexdigest(fname):
    return hashlib.md5(open(fname, 'rb').read()).hexdigest()

def after_build(source, target, env):
    if not os.path.exists("builds"):
        os.mkdir("builds")

    lang = env.GetProjectOption('lang')
    target_name = lang.lower()

    with open(f"builds/latest_{target_name}.bin.md5", "w") as md5:
        print(_file_md5_hexdigest(target[0].path), file = md5)
    shutil.copy(target[0].path, f"builds/latest_{target_name}.bin")


env.AddPostAction("$BUILD_DIR/firmware.bin", after_build)
