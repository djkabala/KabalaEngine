/*---------------------------------------------------------------------------*\
 *                             Kabala Engine                                 *
 *                                                                           *
 *                         www.vrac.iastate.edu                              *
 *                                                                           *
 *   Authors: David Kabala (dkabala@vrac.iastate.edu)                        *
 *                                                                           *
\*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*\
 *                                License                                    *
 *                                                                           *
 * This library is free software; you can redistribute it and/or modify it   *
 * under the terms of the GNU Library General Public License as published    *
 * by the Free Software Foundation, version 3.                               *
 *                                                                           *
 * This library is distributed in the hope that it will be useful, but       *
 * WITHOUT ANY WARRANTY; without even the implied warranty of                *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU         *
 * Library General Public License for more details.                          *
 *                                                                           *
 * You should have received a copy of the GNU Library General Public         *
 * License along with this library; if not, write to the Free Software       *
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.                 *
 *                                                                           *
\*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*\
 *                                Changes                                    *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
\*---------------------------------------------------------------------------*/

#ifndef _KEMAINAPPLICATION_H_
#define _KEMAINAPPLICATION_H_
#ifdef __sgi
#pragma once
#endif

#include "KEConfig.h"

#include "KEMainApplicationBase.h"
#include <OpenSG/OSGWindowFields.h>
#include <OpenSG/Input/OSGWindowAdapter.h>
#include <boost/program_options.hpp>
#include "Project/KEProjectFields.h"


OSG_USING_NAMESPACE
KE_BEGIN_NAMESPACE

/*! \brief MainApplication class. See \ref 
           PageKabalaEngineMainApplication for a description.
*/

class KE_KABALAENGINELIB_DLLMAPPING MainApplication : public MainApplicationBase
{
  private:

    typedef MainApplicationBase Inherited;

    /*==========================  PUBLIC  =================================*/
  public:

    /*---------------------------------------------------------------------*/
    /*! \name                      Sync                                    */
    /*! \{                                                                 */

    virtual void changed(BitVector  whichField, 
                         ::osg::UInt32     origin    );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    virtual void dump(      ::osg::UInt32     uiIndent = 0, 
                      const BitVector  bvFlags  = 0) const;

    /*! \}                                                                 */

	Int32 run(int argc, char **argv);
	void exitMainLoop(void);
	void exit(void);

	void printCommandLineHelp(void) const;

	void saveSettings(const Path& SettingsFile);
	void loadSettings(const Path& SettingsFile);

	void saveProject(const Path& ProjectFile);
	void loadProject(const Path& ProjectFile);

	void attachBuilder(void);

	void attachPlayer(void);

	void attachStartScreen(void);

    /*=========================  PROTECTED  ===============================*/
  protected:

    static ApplicationSettingsPtr createDefaultSettings(void);

	void createDefaultBuilderMode(void);

	void createDefaultPlayerMode(void);

	void createDefaultStartScreenMode(void);

	ProjectPtr createDefaultProject(void);
    // Variables should all be in MainApplicationBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    MainApplication(void);
    MainApplication(const MainApplication &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~MainApplication(void); 

	class MainWindowListener : public WindowAdapter
	{
	public :
		MainWindowListener(MainApplicationPtr TheMainApplication);
		virtual void windowClosing(const WindowEvent& e);

		virtual void windowClosed(const WindowEvent& e);
	protected :
		MainApplicationPtr _MainApplication;
	};

	MainWindowListener _MainWindowListener;
	bool _ExitMainLoop;

	static boost::program_options::options_description _OptionsDescription;
	static boost::program_options::positional_options_description _PositionalOptions;
    /*! \}                                                                 */
;
    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class MainApplicationBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const MainApplication &source);
};

typedef MainApplication *MainApplicationP;

KE_END_NAMESPACE

#include "KEMainApplicationBase.inl"
#include "KEMainApplication.inl"

#endif /* _KEMAINAPPLICATION_H_ */
