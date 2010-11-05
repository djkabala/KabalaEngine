/*---------------------------------------------------------------------------*\
 *                             Kabala Engine                                 *
 *                                                                           *
 *               Copyright (C) 2009-2010 by David Kabala                     *
 *                                                                           *
 *   authors:  David Kabala (djkabala@gmail.com)                             *
 *                                                                           *
\*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*\
 *                                License                                    *
 *                                                                           *
 * This library is free software; you can redistribute it and/or modify it   *
 * under the terms of the GNU General Public License as published            *
 * by the Free Software Foundation, version 3.                               *
 *                                                                           *
 * This library is distributed in the hope that it will be useful, but       *
 * WITHOUT ANY WARRANTY; without even the implied warranty of                *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU         *
 * Library General Public License for more details.                          *
 *                                                                           *
 * You should have received a copy of the GNU General Public                 *
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

#ifndef _KEMAINMENU_H_
#define _KEMAINMENU_H_
#ifdef __sgi
#pragma once
#endif

#include "KEMainMenuBase.h"
#include <OpenSG/OSGMenuItemFields.h>
#include <OpenSG/OSGMenuFields.h>
#include <OpenSG/OSGActionEventDetailsFields.h>
#include <OpenSG/OSGChangeEventDetailsFields.h>
#include <OpenSG/OSGUndoManager.h>
#include <OpenSG/OSGCommandManager.h>

OSG_BEGIN_NAMESPACE

/*! \brief MainMenu class. See \ref
           PageKabalaEngineMainMenu for a description.
*/

class KE_KABALAENGINE_DLLMAPPING MainMenu : public MainMenuBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef MainMenuBase Inherited;
    typedef MainMenu     Self;

    /*---------------------------------------------------------------------*/
    /*! \name                      Sync                                    */
    /*! \{                                                                 */

    virtual void changed(ConstFieldMaskArg whichField,
                         UInt32            origin,
                         BitVector         details    );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    virtual void dump(      UInt32     uiIndent = 0,
                      const BitVector  bvFlags  = 0) const;

    /*! \}                                                                 */

	virtual void createInterface(ApplicationBuilder* const TheApplicationBuilder);
	virtual void destroyInterface(ApplicationBuilder* const TheApplicationBuilder);

	virtual void attachInterface(ApplicationBuilder* const TheApplicationBuilder);
	virtual void dettachInterface(ApplicationBuilder* const TheApplicationBuilder);
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in MainMenuBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    MainMenu(void);
    MainMenu(const MainMenu &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~MainMenu(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    void updateRecentProjectsMenu(void);
    void updateUndoRedoInterfaces(void);
    void createRecentProjectMenuItems(void);
    void updateRecentProjectMenuItems(void);
    void connectRecentProjectMenuItems(void);
    void disconnectRecentProjectMenuItems(void);

    void handleOpenMenuItem(ActionEventDetails* const details);
    void handleSaveMenuItem(ActionEventDetails* const details);
    void handleSaveAsMenuItem(ActionEventDetails* const details);
    void handleCloseMenuItem(ActionEventDetails* const details);
    void handleSettingsMenuItem(ActionEventDetails* const details);
    void handleNewMenuItem(ActionEventDetails* const details);
    void handleRecentProjectMenuItem(ActionEventDetails* const details,
                                     UInt32 Index);
    void handleQuitMenuItem(ActionEventDetails* const details);

    void handleUndoMenuItem(ActionEventDetails* const details);
    void handleRedoMenuItem(ActionEventDetails* const details);

    void handlePlayMenuItem(ActionEventDetails* const details);
    void handleProjectAdvancedSettingsMenuItem(ActionEventDetails* const details);
    void handleProjectPropertiesMenuItem(ActionEventDetails* const details);

    void handleHelpMenuItem(ActionEventDetails* const details);
    void handleAboutMenuItem(ActionEventDetails* const details);
    void handleCreditsMenuItem(ActionEventDetails* const details);
    
    void handleUndoChange(ChangeEventDetails* const details);

    boost::signals2::connection _OpenMenuItemConnection,
                                _SaveMenuItemConnection,
                                _SaveAsMenuItemConnection,
                                _CloseMenuItemConnection,
                                _SettingsMenuItemConnection,
                                _NewMenuItemConnection,
                                _QuitMenuItemConnection,

                                _UndoMenuItemConnection,
                                _RedoMenuItemConnection,

                                _PlayMenuItemConnection,
                                _ProjectAdvancedSettingsMenuItemConnection,
                                _ProjectPropertiesMenuItemConnection,

                                _HelpMenuItemConnection,
                                _AboutMenuItemConnection,
                                _CreditsMenuItemConnection,

                                _UndoChangeConnection;

    std::vector<boost::signals2::connection> _RecentProjectMenuItemConnections;

    MenuItemRecPtr _OpenMenuItem;
    MenuItemRecPtr _SaveMenuItem;
    MenuItemRecPtr _SaveAsMenuItem;
    MenuItemRecPtr _CloseMenuItem;
    MenuItemRecPtr _SettingsMenuItem;
    MenuRecPtr _RecentProjectsMenu;
    MenuItemRecPtr _NewMenuItem;
    MenuItemRecPtr _QuitMenuItem;

    MenuItemRecPtr _UndoMenuItem;
    MenuItemRecPtr _RedoMenuItem;

    MenuItemRecPtr _PlayMenuItem;
    MenuItemRecPtr _ProjectAdvancedSettingsMenuItem;
    MenuItemRecPtr _ProjectPropertiesMenuItem;

    MenuItemRecPtr _HelpMenuItem;
    MenuItemRecPtr _AboutMenuItem;
    MenuItemRecPtr _CreditsMenuItem;
    
    CommandManagerPtr _TheCommandManager;
    UndoManagerPtr    _UndoManager;
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class MainMenuBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const MainMenu &source);
};

typedef MainMenu *MainMenuP;

OSG_END_NAMESPACE

#include "KEMainMenuBase.inl"
#include "KEMainMenu.inl"

#endif /* _KEMAINMENU_H_ */
