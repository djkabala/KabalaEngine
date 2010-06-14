# name the installer
!define ProjectName "KabalaEngine"
!define SMPROGRAMSFolder $SMPROGRAMS\${ProjectName}
!define OutFileName Install${ProjectName}.exe
!define InstallDirName ${ProjectName}
!define ProjectRootDirName "..\.."
!define InputDirName "..\..\Builds\Windows"
!define UninstallFileName "Uninstall ${ProjectName}.exe"

!define BoostDepDir "C:\Program Files\boost\boost_1_38_0"
!define ODEDepDir "C:\Documents and Settings\David\My Documents\Work\ode-0.11.1"
!define OpenSGDepDir "C:\Program Files\OpenSG"
!define OpenSGToolboxDepDir "C:\Documents and Settings\David\My Documents\Work\OpenSGToolbox\trunk\Builds\Windows"

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
   
   #File "${OpenSGToolboxDepDir}\lib\OSG*[^D].lib"
   #File "${OpenSGToolboxDepDir}\lib\OSG*[^D].dll"
   File "${OpenSGToolboxDepDir}\lib\OSGToolbox.dll"
   File "${OpenSGToolboxDepDir}\lib\OSGInput.dll"
   File "${OpenSGToolboxDepDir}\lib\OSGUserInterface.dll"
   File "${OpenSGToolboxDepDir}\lib\OSGAnimation.dll"
   File "${OpenSGToolboxDepDir}\lib\OSGDynamics.dll"
   File "${OpenSGToolboxDepDir}\lib\OSGParticleSystem.dll"
   File "${OpenSGToolboxDepDir}\lib\OSGGame.dll"
   File "${OpenSGToolboxDepDir}\lib\OSGPhysics.dll"
   File "${OpenSGToolboxDepDir}\lib\OSGMetabolic.dll"
   
   File "${OpenSGDepDir}\lib\OSGBase.dll"
   File "${OpenSGDepDir}\lib\OSGSystem.dll"
   File "${OpenSGDepDir}\lib\OSGWindowWIN32.dll"
   
   File "${OpenSGDepDir}\lib\libmmd.dll"
   File "${OpenSGDepDir}\lib\msvcp80.dll"
   File "${OpenSGDepDir}\lib\msvcr80.dll"
   File "${OpenSGDepDir}\lib\msvcrt.dll"
   File "${OpenSGDepDir}\lib\stlport_icl46.dll"
   File "${OpenSGDepDir}\lib\stlport_vc7146.dll"
   File "${OpenSGDepDir}\lib\msvcp60.dll"
   File "${OpenSGDepDir}\lib\msvcp71.dll"
   File "${OpenSGDepDir}\lib\msvcr71.dll"
   
   File "${BoostDepDir}\lib\boost_filesystem-*.dll"
   File "${BoostDepDir}\lib\boost_program_options-*.dll"
   File "${BoostDepDir}\lib\boost_system-*.dll"
   
   File "${ODEDepDir}\lib\ode_single.*"
   
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
