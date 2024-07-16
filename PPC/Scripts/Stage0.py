#performs the entire stage 0

import subprocess
import os
import sys

python = sys.argv[1]
ninja = sys.argv[2]
dtk = sys.argv[3]
git = sys.argv[4]

projectDir = sys.argv[5]
ROMPath = sys.argv[6]

#gets DTK
if not os.path.exists(sys.argv[1] + "/DTK"):
    subprocess.run([git, "clone", "https://github.com/encounter/dtk-template.git", projectDir + "/DTK"],
    shell=True)

#extract ROM contents
subprocess.run([dtk, "disc", "extract", ROMPath, projectDir + "/DTK/orig/GAMEID"],
    shell=False)

#generate config
subprocess.run([dtk, "dol", "config", projectDir + "/DTK/orig/GAMEID/sys/main.dol", "-o", projectDir + "/DTK/config/GAMEID/config.yml"],
    shell=False)
configFile = open(projectDir + "/DTK/config/GAMEID/config.yml", "a")
configFile.write("""symbols: config/GAMEID/symbols.txt\n"""
		"""splits: config/GAMEID/splits.txt\n"""
		"""quick_analysis : false\n"""
		"""detect_objects : true\n"""
		"""detect_strings : true\n"""
		"""write_asm : true\n"""
		"""fill_gaps : true\n"""
		"""export_all : true\n""")
configFile.close()

#decompile
subprocess.run([python, "Configure.py"], cwd= projectDir + "/DTK")
subprocess.run([ninja], cwd= projectDir + "/DTK")