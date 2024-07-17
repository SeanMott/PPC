#extracts the content of the ROM to the correct folder

import subprocess
import os
import sys

dtk = sys.argv[1]

projectDir = sys.argv[2]
ROMPath = sys.argv[3]

#extract ROM contents
subprocess.call([dtk, "disc", "extract", ROMPath, projectDir + "/DTK/orig/GAMEID"],
    shell=True)