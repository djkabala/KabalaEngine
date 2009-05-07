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

#ifndef _KEBUILDERINTERFACE_H_
#define _KEBUILDERINTERFACE_H_
#ifdef __sgi
#pragma once
#endif

#include "KEConfig.h"

#include <OpenSG/UserInterface/OSGMenuFields.h>
#include <OpenSG/UserInterface/OSGMenuItemFields.h>
#include <OpenSG/UserInterface/OSGButtonFields.h>
#include <OpenSG/UserInterface/OSGChangeListener.h>
#include "KEBuilderInterfaceBase.h"
#include "Builder/UserInterface/Commands/KECommandActionListener.h"

OSG_USING_NAMESPACE
KE_BEGIN_NAMESPACE

/*! \brief BuilderInterface class. See \ref 
           PageKabalaEngineBuilderInterface for a description.
*/

class KE_KABALAENGINELIB_DLLMAPPING BuilderInterface : public BuilderInterfaceBase
{
  private:

    typedef BuilderInterfaceBase Inherited;

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
	virtual void createInterface(ApplicationBuilderPtr TheApplicationBuilder);
	virtual void connectInterface(ApplicationBuilderPtr TheApplicationBuilder);
	virtual void disconnectInterface(ApplicationBuilderPtr TheApplicationBuilder);
	virtual void updateInterface(ApplicationBuilderPtr TheApplicationBuilder);
	virtual void destroyInterface(ApplicationBuilderPtr TheApplicationBuilder);

	virtual const std::string& getPresentationName(void) const;
	virtual const std::string& getPresentationIconName(void) const;

    void addToolbarTools(const std::vector<ComponentPtr>& Tools);
    void removeToolbarTools(const std::vector<ComponentPtr>& Tools);
    /*=========================  PROTECTED  ===============================*/
  protected:

    // Variables should all be in BuilderInterfaceBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    BuilderInterface(void);
    BuilderInterface(const BuilderInterface &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~BuilderInterface(void); 

    /*! \}                                                                 */
    
	static const std::string _PresentationName;
	static const std::string _PresentationIconName;

	//Components
	//Menus
    MenuPtr _FileMenu;
    MenuItemPtr _NewProjectMenuItem;
    MenuItemPtr _OpenProjectMenuItem;
    MenuPtr _RecentProjectsMenu;
    std::vector<MenuItemPtr> _RecentProjectsMenuItems;
    MenuItemPtr _CloseProjectMenuItem;
	MenuItemPtr _SaveProjectMenuItem;
	MenuItemPtr _SaveProjectAsMenuItem;
	MenuItemPtr _PlayProjectMenuItem;
	MenuItemPtr _StartScreenMenuItem;
    MenuItemPtr _ExitMenuItem;

    MenuPtr _EditMenu;
    MenuItemPtr _UndoMenuItem;
    MenuItemPtr _RedoMenuItem;
    MenuItemPtr _CutMenuItem;
    MenuItemPtr _CopyMenuItem;
    MenuItemPtr _PasteMenuItem;
    MenuItemPtr _DeleteMenuItem;

    MenuPtr _HelpMenu;
    MenuItemPtr _AboutKEMenuItem;

	//Toolbar
	ButtonPtr _UndoButton;
	ButtonPtr _RedoButton;
	ButtonPtr _OpenProjectButton;
	ButtonPtr _SaveProjectButton;

	//Action Listeners
	CommandActionListener _NewProjectActionListener;
	CommandActionListener _OpenProjectActionListener;
	CommandActionListener _CloseProjectActionListener;
	CommandActionListener _SaveProjectActionListener;
	CommandActionListener _SaveProjectAsActionListener;
	CommandActionListener _PlayProjectListener;
	CommandActionListener _StartScreenListener;
	CommandActionListener _QuitActionListener;

	CommandActionListener _UndoActionListener;
	CommandActionListener _RedoActionListener;

	CommandActionListener _AboutKabalaEngineActionListener;

	void updateUndoRedoInterfaces(UndoManagerPtr TheUndoManager);
    
	class CommandManagerListener: public ChangeListener
	{
	  public:
		CommandManagerListener(BuilderInterfacePtr BuilderInterface);

		virtual void stateChanged(const ChangeEvent& e);

        void setApplicationBuilder(ApplicationBuilderPtr TheApplicationBuilder);
	  protected :
		BuilderInterfacePtr _BuilderInterface;
        ApplicationBuilderPtr _ApplicationBuilder;
	};

	friend class CommandManagerListener;

	CommandManagerListener _CommandManagerListener;

    void updateRecentProjectsMenu(void);

    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class BuilderInterfaceBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const BuilderInterface &source);
};

typedef BuilderInterface *BuilderInterfaceP;

KE_END_NAMESPACE

#include "KEBuilderInterfaceBase.inl"
#include "KEBuilderInterface.inl"

#endif /* _KEBUILDERINTERFACE_H_ */
