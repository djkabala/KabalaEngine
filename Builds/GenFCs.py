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
   os.system(convertPathToOutput(FcdCompilePath + " -b -f " + convertPathToOutput(Path)))

   BaseHeaderFile = "KE" + os.path.splitext(os.path.split(Path)[1])[0] + "Base.h"
   BaseInlineFile = "KE" + os.path.splitext(os.path.split(Path)[1])[0] + "Base.inl"
   FieldsFile = "KE" + os.path.splitext(os.path.split(Path)[1])[0] + "Fields.h"
   BaseCodeFile = "KE" + os.path.splitext(os.path.split(Path)[1])[0] + "Base.cpp"

   HeaderFile = "KE" + os.path.splitext(os.path.split(Path)[1])[0] + ".h"
   InlineFile = "KE" + os.path.splitext(os.path.split(Path)[1])[0] + ".inl"
   CodeFile = "KE" + os.path.splitext(os.path.split(Path)[1])[0] + ".cpp"

   BaseDir = os.path.dirname(Path)
   if(BaseDir == ""):
       BaseDir = os.getcwd()

   #Only move the files if the current working directory is not where they should be put
   if(os.name != "posix" or (not os.path.samefile(os.getcwd(), BaseDir))):
       shutil.move(BaseHeaderFile, os.path.join(os.path.split(Path)[0],BaseHeaderFile))
       shutil.move(BaseInlineFile, os.path.join(os.path.split(Path)[0],BaseInlineFile))
       shutil.move(FieldsFile, os.path.join(os.path.split(Path)[0],FieldsFile))
       shutil.move(BaseCodeFile, os.path.join(os.path.split(Path)[0],BaseCodeFile))

       if(not os.path.exists(os.path.join(os.path.split(Path)[0],HeaderFile))):
           shutil.move(HeaderFile, os.path.join(os.path.split(Path)[0],HeaderFile))
       else:
          print(os.path.join(os.path.split(Path)[0],HeaderFile) + " already exists.")
          os.remove(HeaderFile)

       if(not os.path.exists(os.path.join(os.path.split(Path)[0],InlineFile))):
           shutil.move(InlineFile, os.path.join(os.path.split(Path)[0],InlineFile))
       else:
          print(os.path.join(os.path.split(Path)[0],InlineFile) + " already exists.")
          os.remove(InlineFile)

       if(not os.path.exists(os.path.join(os.path.split(Path)[0],CodeFile))):
           shutil.move(CodeFile, os.path.join(os.path.split(Path)[0],CodeFile))
       else:
          print(os.path.join(os.path.split(Path)[0],CodeFile) + " already exists.")
          os.remove(CodeFile)


def main():
   print("Operating System:", os.name)
   print("System Platform:", sys.platform)
   if len(sys.argv) < 2:
      print("Must specify a Field Container Description file(.fcd).")
      sys.exit(1)

   GenFCsPyDir = os.path.split(sys.argv[0])[0]
   if os.name == "posix":
      if sys.platform == "darwin":
          FcdCompilePath = os.path.join(GenFCsPyDir, "../Tools/OS\ X/fcdCompile")
      else:
          FcdCompilePath = os.path.join(GenFCsPyDir, "../Tools/Linux/fcdCompile")
   else:
       FcdCompilePath = convertPathToOutput(os.path.join(GenFCsPyDir, "..\\Tools\\Windows\\fcdCompile.exe")) 

   print("Using fcdCompile to Generate Code...")

   for i in range(1,len(sys.argv)):
       GenFCsFromFile(GenFCsPyDir, FcdCompilePath, sys.argv[i])

   print("Done")

main()

