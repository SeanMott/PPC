import subprocess
import os
import sys

#defines a function for making a folder if it doesn't exist
def MakeFolder(dir):
    os.makedirs(dir, exist_ok=True)

#if no arguments or not enough

print("PPC Stage 0: Gathering Data")

DTK = "C:/Decomps/dtk_130"
ROM = sys.argv[1]
DTKOuputDir = sys.argv[2]
MakeFolder(DTKOuputDir)

#extracts the ROM
print("PPC Stage 0: Extracting ROM")
ROMAssetsDir = DTKOuputDir + "/ROMAssets"
MakeFolder(ROMAssetsDir)
subprocess.run([DTK, "disc", "extract", ROM, ROMAssetsDir], text=True)

#generates the config
print("PPC Stage 0: Generating DTK Config")

DTKRawAssembly = DTKOuputDir + "/RawASM"
MakeFolder(DTKRawAssembly)
DTKRawAssembly_Symbols = DTKRawAssembly + "/DTKSymbolsNSplits"
MakeFolder(DTKRawAssembly_Symbols)

#generate inital config
DTKConfig = DTKRawAssembly + "/DTKConfig.yml"
subprocess.run([DTK, "dol", "config", ROMAssetsDir + "/sys/main.dol", "-o", DTKConfig], text=True)

#adds symbols and splits paths
with open(DTKConfig, "a") as file:
    file.write("symbols: " + DTKRawAssembly_Symbols[2:] + "/symbols.txt\n")
    file.write("splits: " + DTKRawAssembly_Symbols[2:] + "/splits.txt\n")

#generates the assembly
subprocess.run([DTK, "dol", "split", DTKConfig, DTKRawAssembly], text=True)

#cleans up the directory