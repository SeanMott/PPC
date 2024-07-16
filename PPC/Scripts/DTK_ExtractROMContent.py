#extracts the content of the ROM to the correct folder

import subprocess
import os
import sys

subprocess.run(["dtk", "disc", "extract", sys.argv[1], sys.argv[2]],
    shell=False)