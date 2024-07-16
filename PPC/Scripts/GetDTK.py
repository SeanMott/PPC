#pulls down DTK if it doesn't exist

import subprocess
import os
import sys

if not os.path.exists(sys.argv[1] + "/DTK"):
    subprocess.run(["git", "clone", "https://github.com/encounter/dtk-template.git", sys.argv[1] + "/DTK"],
    shell=True)