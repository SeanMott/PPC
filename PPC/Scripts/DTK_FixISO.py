#invokes DTK's ability to fix ISOs

import subprocess
import os
import sys

subprocess.run(["dtk", "disc", "convert", sys.argv[1], sys.argv[2]],
    shell=False)