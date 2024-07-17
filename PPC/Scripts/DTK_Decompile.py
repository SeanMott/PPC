#decompiles the ROM

import subprocess
import os
import sys

python = sys.argv[1]
ninja = sys.argv[2]

projectDir = sys.argv[1]

#decompile
subprocess.call(["python", "configure.py"], cwd= projectDir + "/DTK",
    shell=False)
subprocess.call([ninja], cwd= projectDir + "/DTK",
    shell=False)