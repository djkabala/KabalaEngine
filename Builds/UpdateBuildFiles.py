import os
import sys
import glob
import re


def listDirsRec(DirName, IgnoreDirs):
   Dirs = []
   for File in os.listdir(DirName):
      if (os.path.isdir( os.path.join( DirName,File ) )) and (File not in IgnoreDirs):
         Dirs.append( os.path.join( DirName, File ) )
         Dirs += listDirsRec(os.path.join( DirName, File ), IgnoreDirs)
   return Dirs
   
def listFiles(DirList, FileTypeGlob, IgnoreDirs):
   Files = []
   for Dir in DirList:
      if Dir not in IgnoreDirs:
         Files += glob.glob( os.path.join( Dir, FileTypeGlob))
   return Files
         

def printSourceFilters(SourceDir, IgnoreDirs, RecLevel):
   CppFile = "*.cpp"
   HeaderFile = "*.h"
   
   WritenString = ""
   Dirs = []
   for File in os.listdir(SourceDir):
      if (os.path.isdir( os.path.join( SourceDir,File ) )) and (File not in IgnoreDirs):
         Dirs.append( os.path.join( SourceDir, File ) )
         
   for Dir in Dirs:
      WritenString += ("	"* (RecLevel+3) ) + "<Filter\n"
      WritenString += ("	"* (RecLevel+4) ) + "Name=" +'"' + os.path.split(Dir)[1] + '"\n'
      WritenString += ("	"* (RecLevel+4) ) + """Filter="">
"""
      
      WritenString += printSourceFilters(Dir, IgnoreDirs, RecLevel+1 )
      
      Files = glob.glob(os.path.join( Dir, CppFile))
      Files += glob.glob(os.path.join( Dir, HeaderFile))
      Files.sort()

      for File in Files:
         WritenString += ("	"* (RecLevel+4) ) +"<File\n"
         WritenString += ("	"* (RecLevel+5) ) +"RelativePath=" + '"' +  File + '"' + ">\n"
         WritenString += ("	"* (RecLevel+4) ) +"""</File>
"""
      
      WritenString += ("	"* (RecLevel+3) ) + """</Filter>
"""
   return WritenString

def makeSourceFilters(SourceDir, IgnoreDirs, IgnoreFiles):
   WritenString = ""
   WritenString += """		<Filter
			Name="Source Files"
			Filter="cpp;c;cxx;rc;def;r;odl;idl;hpj;bat;h;hpp;hxx;hm;inl">
"""

   WritenString += printSourceFilters( SourceDir, IgnoreDirs,0)

   CppFile = "*.cpp"
   HeaderFile = "*.h"
   Files = glob.glob(os.path.join( SourceDir, CppFile))
   Files += glob.glob(os.path.join( SourceDir, HeaderFile))
   Files.sort()
   for File in Files:
      if os.path.split(File)[1] not in IgnoreFiles:
         WritenString += ("  "* 3 ) +"<File\n"
         WritenString += ("  "* 4 ) +"RelativePath=" + '"' +  File + '"' + ">\n"
         WritenString += ("  "* 3 ) +"""</File>
"""
         
   WritenString += """		</Filter>
"""
   return WritenString


   
def printDefinitionFilters(DefinitionsDir, IgnoreDirs, RecLevel):
   WritenString = ""
   Dirs = []
   for File in os.listdir(DefinitionsDir):
      if (os.path.isdir( os.path.join( DefinitionsDir,File ) )) and (File not in IgnoreDirs):
         Dirs.append( os.path.join( DefinitionsDir, File ) )
   #print os.path.abspath( DefinitionsDir )
         
   for File in Dirs:
      #print os.path.split(File)[1]
      WritenString += ("	"* (RecLevel+3) ) + "<Filter\n"
      WritenString += ("	"* (RecLevel+4) ) + "Name=" +'"' + os.path.split(File)[1] + '"\n'
      WritenString += ("	"* (RecLevel+4) ) + """Filter="">
"""
      
      WritenString += printDefinitionFilters(File, IgnoreDirs, RecLevel+1 )
      
      JdefFiles = glob.glob(os.path.join( File, "*.jdef"))
      for JdefFile in JdefFiles:
         WritenString += ("	"* (RecLevel+4) ) +"<File\n"
         WritenString += ("	"* (RecLevel+5) ) +"RelativePath=" + '"' +  JdefFile + '"' + ">\n"
         WritenString += ("	"* (RecLevel+4) ) +"""</File>
"""
      
      WritenString += ("	"* (RecLevel+3) ) + """</Filter>
"""
   return WritenString
   
def makeDefinitionsFilters(DefinitionsDir, IgnoreDirs):
   WritenString = ""
   WritenString += """		<Filter
			Name="Definition Files"
			Filter="jdef"
			ParseFiles="FALSE"
			SourceControlFiles="FALSE">
"""
         
   WritenString += printDefinitionFilters( DefinitionsDir, IgnoreDirs,0)
         
   WritenString += """		</Filter>"""
   return WritenString
         
   
def makeVCPROJFiles(WindowsBuildDir, SourceDir, IgnoreDirs, IgnoreSourceFiles, DefinitionsDir ):
   CWD = os.getcwd()
   
   os.path.normpath( WindowsBuildDir  )
   os.chdir( WindowsBuildDir )

   os.path.normpath( SourceDir )
   os.path.normpath( DefinitionsDir )


   vcprojFiles = listFiles(["."],"*.vcproj" , IgnoreDirs)
   if len(vcprojFiles) != 1:
       print "There are ", len(vcprojFiles), " .vcproj files in ", WindowsBuildDir, "; there should only be one.  Aborting."
       return
    
   #Get the New Files Text to Insert
   WrittenString = ""
   WrittenString += makeSourceFilters(SourceDir, IgnoreDirs, IgnoreSourceFiles)
   WrittenString += makeDefinitionsFilters(DefinitionsDir, IgnoreDirs)


   #Read the VSEApp File
   VSEAppFile = open(vcprojFiles[0], 'r')
   VSEAppFileText = VSEAppFile.read()
   VSEAppFile.close()

   #Match the correct portions of the file
   m = re.match('(.+<Files>\n*)(.+)(\n\s*</Files>.+)',VSEAppFileText, re.DOTALL)

   #Insert that text at the correct position
   VSEAppFile = open(vcprojFiles[0], 'w')
   VSEAppFile.write(m.group(1))
   VSEAppFile.write(WrittenString)
   VSEAppFile.write(m.group(3))
   
   #Close the File
   VSEAppFile.close()

   #Return to the original directory
   os.chdir( CWD )
   
def makeLinuxSourceDirs(SourceDir, IgnoreDirs):
   CWD = os.getcwd()
   os.chdir( SourceDir )

   Dirs = listDirsRec(".", IgnoreDirs)
    
   WritenString = "$(srcdir)/:"
   for Dir in Dirs:
      WritenString += "$(srcdir)/" + Dir[2:] + ":"

   for i in range(len(WritenString)):
       if WritenString[i] == "\\":
           WritenString = WritenString[:i] + "/" + WritenString[i+1:]

           
   os.chdir( CWD )
   return WritenString

def makeLinuxCppSources(SourceDir, IgnoreDirs, IgnoreFiles):
   CppFile = "*.cpp"
   
   CppFiles = []
   
   Dirs = listDirsRec(SourceDir, IgnoreDirs)
   Dirs.append( SourceDir )
   CppFiles = listFiles(Dirs,CppFile , IgnoreDirs)
   
   #Print out the Source Files Filter
   WritenString = ""
   if len(CppFiles) > 0:
      WritenString += os.path.splitext(os.path.split(CppFiles[0])[1])[0] + ".o"
      CppFiles = CppFiles[1:]
      for File in CppFiles:
         if os.path.split(File)[1] not in IgnoreFiles:
            CppFile = os.path.split(File)[1]
            WritenString += """ \\
	""" + os.path.splitext(CppFile)[0] + ".o"
      
   return WritenString

def makeLinuxMakefile( LinuxBuildDir, SourceDir):
   CWD = os.getcwd()
   
    #Goto the Linux Build directory
   os.path.normpath( LinuxBuildDir )
   os.chdir( LinuxBuildDir )

   #IgnoreSourceFiles = []
   IgnoreDirs = [".svn"]
   os.path.normpath( SourceDir )
   
   #Read the MakeFile
   if not os.path.exists( 'Makefile' ):
      print "No Makefile in", os.getcwd(), "found."
      os.chdir( CWD )
      return
   Makefile = open('Makefile', 'r')
   MakefileText = Makefile.read()
   Makefile.close()

   #print MakefileText
   #Match the correct portions of the file
   #m = re.match('(.+srcdir=)([^\n]+)(.+SRCS=	)(.+\.cpp\n)(.+)',MakefileText, re.DOTALL)
   
   m = re.match('(.+VPATH = )([^\n]+)(.+OBJECTS = )(.+\.o)(.+)',MakefileText, re.DOTALL)

   #Insert that text at the correct position
   Makefile = open('Makefile', 'w')
   Makefile.write(m.group(1))
   Makefile.write(makeLinuxSourceDirs(SourceDir, IgnoreDirs))
   Makefile.write(m.group(3))
   Makefile.write(makeLinuxCppSources(SourceDir, IgnoreDirs, [""]))
   Makefile.write(m.group(5))
   
   #Close the File
   #Makefile.close()
   
   #Return to the original directory
   os.chdir( CWD )

def main():
   #print "Making Windows Build ..."
   
   #WindowsBuildDir = "../Windows.Build/VSEApp"
   #IgnoreSourceFiles = ["Main.cpp"]
   #IgnoreDirs = [".svn"]
   #SourceDir = "../../src"
   #DefinitionsDir = "../../Configure/Definitions"
   
   #makeVCPROJFiles(WindowsBuildDir, SourceDir, IgnoreDirs, IgnoreSourceFiles, DefinitionsDir)
   
   #FileList = listFiles(["../Plugins"],"*",[".svn"])
   #for File in FileList:
   #   if os.path.exists( os.path.join(File,"Builds/Windows.Build") ) and os.path.exists( os.path.join(File,"Configure/Definitions") ):
   #      print "Makeing Plugin", os.path.split(File)[1] ,"Windows Build ..."
   #      makeVCPROJFiles(os.path.join(File,"Builds/Windows.Build"), "../../src", IgnoreDirs, [], "../../Configure/Definitions")

   FilesDir = os.path.split(sys.argv[0])[0]      
   
   print "Making Linux Build ..."
   makeLinuxMakefile(os.path.join(FilesDir,"Linux"),"../../Source")

   #print "Making Apple Build ..."
   #makeLinuxMakefile("Apple","../Source")
   print "Done"
   #raw_input("Type ENTER to close.")

main()
