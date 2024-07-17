#generate config

import subprocess
import os
import sys

dtk = sys.argv[1]
projectDir = sys.argv[2]

subprocess.call([dtk, "dol", "config", projectDir + "/DTK/orig/GAMEID/sys/main.dol", "-o", projectDir + "/DTK/config/GAMEID/config.yml"],
    shell=True)
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