# name the installer
!define ProjectName "KabalaEngine"
!define SMPROGRAMSFolder $SMPROGRAMS\${ProjectName}
!define OutFileName Install${ProjectName}.exe
!define InstallDirName ${ProjectName}
!define ProjectRootDirName "..\.."
!define InputDirName "..\..\Builds\Windows"
!define UninstallFileName "Uninstall ${ProjectName}.exe"

outFile "${OutFileName}"

# define the directory to install to, the desktop in this case as specified  
# by the predefined $DESKTOP variable
installDir $PROGRAMFILES\${InstallDirName}

Page license
   LicenseText "GNU Library General Public License v. 3"
   LicenseData "${ProjectRootDirName}\LICENSE"
   LicenseForceSelection checkbox
   
Page components
Page Directory
Page instfiles

UninstPage uninstConfirm
UninstPage instfiles

# default section start; every NSIS script has at least one section.
section
   
   # define the output path for this file
   setOutPath $INSTDIR
   
   #Create the Install Directory
   CreateDirectory $INSTDIR
   
   # define what to install and place it in the output path
   #file test.txt
   
   # define uninstaller name
   writeUninstaller "$INSTDIR\${UninstallFileName}"
   
   #Create OpenSGToolbox environment variable
   
   # create a shortcut named "new shortcut" in the start menu programs directory
   # presently, the new shortcut doesn't call anything (the second field is blank)
   CreateDirectory "${SMPROGRAMSFolder}"
   createShortCut "${SMPROGRAMSFolder}\${ProjectName}.lnk" "$INSTDIR\KabalaEngine.exe"
   createShortCut "${SMPROGRAMSFolder}\Uninstall ${ProjectName}.lnk" "$INSTDIR\${UninstallFileName}"

# default section end
sectionEnd

/*SectionGroup "Devolopment Files"
   section "Debug Libraries"
      # define the output path for this file
      setOutPath $INSTDIR
      
      #Add lib directory to the path
      
      #Create the Install Directory
      CreateDirectory $INSTDIR\lib
      
      setOutPath $INSTDIR\lib
      
      File "${InputDirName}\lib\OSG*D.lib"
      File "${InputDirName}\lib\OSG*D.dll"
   sectionEnd

   section "Header Files"
      # define the output path for this file
      setOutPath $INSTDIR
      
      #Create the Install Directory
      #CreateDirectory $INSTDIR\include
      
      File /r "${InputDirName}\include"
   sectionEnd
   section "Tutorials"
      # define the output path for this file
      setOutPath $INSTDIR
      
      #Create the Install Directory
      CreateDirectory $INSTDIR\Tutorials
      
      #Create StartMenu Tutorial Directory
      CreateDirectory "${SMPROGRAMSFolder}\Tutorials"
      setOutPath $INSTDIR\Tutorials
      
      
      #File "${InputDirName}\lib\OSG*D.lib"
   sectionEnd
SectionGroupEnd*/

section "Main Application"
   # define the output path for this file
   setOutPath $INSTDIR
   
   #Add lib directory to the path
   
   #Create the Install Directory
   #CreateDirectory $INSTDIR\lib
      
   #setOutPath $INSTDIR\lib
   
   #File "${InputDirName}\lib\OSG*[^D].lib"
   #File "${InputDirName}\lib\OSG*[^D].dll"
   File "${InputDirName}\lib\OSGToolbox.dll"
   File "${InputDirName}\lib\OSGInput.dll"
   File "${InputDirName}\lib\OSGUserInterface.dll"
   File "${InputDirName}\lib\OSGAnimation.dll"
   File "${InputDirName}\lib\OSGDynamics.dll"
   File "${InputDirName}\lib\OSGParticleSystem.dll"
   File "${InputDirName}\lib\OSGGame.dll"
   
   File "${InputDirName}\lib\OSGBase.dll"
   File "${InputDirName}\lib\OSGSystem.dll"
   File "${InputDirName}\lib\OSGWindowWIN32.dll"
   
   File "${InputDirName}\lib\libmmd.dll"
   File "${InputDirName}\lib\msvcp80.dll"
   File "${InputDirName}\lib\msvcr80.dll"
   File "${InputDirName}\lib\msvcrt.dll"
   File "${InputDirName}\lib\stlport_icl46.dll"
   File "${InputDirName}\lib\stlport_vc7146.dll"
   File "${InputDirName}\lib\msvcp60.dll"
   File "${InputDirName}\lib\msvcp71.dll"
   File "${InputDirName}\lib\msvcr71.dll"
   
   File "${InputDirName}\lib\boost_filesystem-vc80-mt-gd-1_36.dll"
   File "${InputDirName}\lib\boost_program_options-vc80-mt-1_36.dll"
   File "${InputDirName}\lib\boost_program_options-vc80-mt-gd-1_36.dll"
   File "${InputDirName}\lib\boost_system-vc80-mt-gd-1_36.dll"
   
   File "${ProjectRootDirName}\KabalaEngine.exe"
   File "${ProjectRootDirName}\.KEDefaultSettings.xml"
   
   #Create the Data Directory
   CreateDirectory $INSTDIR\Data
   
   CreateDirectory $INSTDIR\Data\Models
   setOutPath $INSTDIR\Data\Models
   File "${ProjectRootDirName}\Data\Models\TorusKnot.osb"
   
   CreateDirectory $INSTDIR\Data\Images
   CreateDirectory $INSTDIR\Data\Images\icons
   setOutPath $INSTDIR\Data\Images\icons
   File /r "${ProjectRootDirName}\Data\Images\icons\"
sectionEnd

section "Documentation"
   # define the output path for this file
   setOutPath $INSTDIR
   
   #Create the Install Directory
   CreateDirectory $INSTDIR\Documentation
sectionEnd


# create a section to define what the uninstaller does.
# the section will always be named "Uninstall"
section "un.Uninstall ${ProjectName}"

   # Always delete uninstaller first
   delete "$INSTDIR\${UninstallFileName}"
    
   #Remove the Install Directory
   RMDir /r $INSTDIR
   
   # now delete installed file
   #delete $INSTDIR\test.txt
   
   # second, remove the link from the start menu
   RMDir /r "${SMPROGRAMSFolder}"
 
sectionEnd
