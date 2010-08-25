import os
import sys
import glob
import shutil

def convertPathToOutput(Path):
   if os.name == "posix":
        return Path
   else:
	    return '"' + Path + '"'

def GenFCsFromFile(GenFCsPyDir, FcdCompilePath, Path):
   os.system(convertPathToOutput("python " + FcdCompilePath + " -fb -d " + convertPathToOutput(Path) + " -p " + convertPathToOutput(os.path.split(Path)[0]) + " -r " + os.path.join(os.path.join(os.path.split(FcdCompilePath)[0],".."),"..")))


def main():
   print("Operating System:", os.name)
   print("System Platform:", sys.platform)
   if len(sys.argv) < 2:
      print("Must specify a Field Container Description file(.fcd).")
      sys.exit(1)

   GenFCsPyDir = os.path.split(sys.argv[0])[0]
   if os.name == "posix":
      if sys.platform == "darwin":
          FcdCompilePath = os.path.join(GenFCsPyDir, "./fcdCompile")
      else:
          FcdCompilePath = os.path.join(GenFCsPyDir, "./fcdCompile")
   else:
       FcdCompilePath = convertPathToOutput(os.path.join(GenFCsPyDir, ".\\fcd2code")) 

   print("Using fcdCompile to Generate Code...")

   for i in range(1,len(sys.argv)):
       GenFCsFromFile(GenFCsPyDir, FcdCompilePath, sys.argv[i])

   print("Done")

main()

