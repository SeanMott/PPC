#pulls down DTK if it doesn't exist

import subprocess
import os
import sys

git = sys.argv[1]
projectDir = sys.argv[2]

#gets DTK
if not os.path.exists(projectDir + "/DTK"):
    subprocess.call(["git", "clone", "https://github.com/encounter/dtk-template.git", projectDir + "/DTK"],
    shell=True)