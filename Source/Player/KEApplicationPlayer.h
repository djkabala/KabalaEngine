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

#ifndef _KEAPPLICATIONPLAYER_H_
#define _KEAPPLICATIONPLAYER_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>

#include "KEApplicationPlayerBase.h"
#include <OpenSG/Input/OSGKeyAdapter.h>
#include <OpenSG/OSGSimpleStatisticsForeground.h>
#include <OpenSG/UserInterface/OSGMenu.h>
#include <OpenSG/UserInterface/OSGMenuItem.h>
#include <OpenSG/UserInterface/OSGMenuBar.h>
#include <OpenSG/UserInterface/OSGTextArea.h>
#include <OpenSG/Lua/OSGLuaManager.h>
#include <OpenSG/UserInterface/OSGTabPanel.h>
#include <sstream>
#include <OpenSG/UserInterface/OSGButton.h>
#include <OpenSG/UserInterface/OSGColorLayer.h>
#include <OpenSG/UserInterface/OSGBorderLayout.h>
#include <OpenSG/UserInterface/OSGBorderLayoutConstraints.h>
//text area
#include <OpenSG/UserInterface/OSGScrollPanel.h>
#include <OpenSG/UserInterface/OSGTextArea.h>

// tab panel
#include <OpenSG/UserInterface/OSGTabPanel.h>

//split panel 
#include <OpenSG/UserInterface/OSGSplitPanel.h>

//spring layout
#include <OpenSG/UserInterface/OSGSpringLayout.h>
#include <OpenSG/UserInterface/OSGSpringLayoutConstraints.h>
#include <OpenSG/UserInterface/OSGLabel.h>
#include <OpenSG/UserInterface/OSGBoxLayout.h>
#include <OpenSG/UserInterface/OSGContainer.h>
#include <OpenSG/UserInterface/OSGPanel.h>
#include <OpenSG/UserInterface/OSGColorLayer.h>

// UserInterface Headers
#include <OpenSG/UserInterface/OSGUIForeground.h>
#include <OpenSG/UserInterface/OSGInternalWindow.h>
#include <OpenSG/UserInterface/OSGUIDrawingSurface.h>
#include <OpenSG/UserInterface/OSGGraphics2D.h>
#include <OpenSG/UserInterface/OSGLookAndFeelManager.h>


#include <OpenSG/Physics/OSGPhysicsCharacteristicsDrawable.h>
#include <OpenSG/OSGNode.h>

OSG_BEGIN_NAMESPACE

/*! \brief ApplicationPlayer class. See \ref 
           PageKabalaEngineApplicationPlayer for a description.
*/


class KE_KABALAENGINELIB_DLLMAPPING ApplicationPlayer : public ApplicationPlayerBase 
{
  private:

    typedef ApplicationPlayerBase Inherited;

    /*==========================  PUBLIC  =================================*/
  public:

  	MenuItemPtr ResetItem ;				
    MenuItemPtr ForceQuitItem ;			
    MenuItemPtr NextItem ;				
    MenuItemPtr PrevItem ;				
    MenuItemPtr FirstItem;				
    MenuItemPtr LastItem ;				
	MenuItemPtr FlyNavigatorItem ;		
    MenuItemPtr TrackballNavigatorItem ;
    MenuItemPtr BasicItem ;				
    MenuItemPtr RenderItem ;			
    MenuItemPtr PhysicsItem ;			
    MenuItemPtr ParticleSystemItem ;	
	MenuItemPtr AnimationItem ;			
	MenuItemPtr PauseActiveUpdatesItem;			
	MenuItemPtr DrawBoundingVolumesItem ;		
	MenuItemPtr FrustrumCullingItem  ;
	MenuItemPtr DrawPhysicsCharacteristicsItem  ;
	MenuPtr ProjectMenu;
	MenuPtr SceneMenu;
	MenuPtr NavigatorMenu;
	MenuPtr StatisticsMenu;
	MenuPtr ToggleMenu;
	MenuBarPtr MainMenuBar;
	TabPanelPtr InfoTabPanel;
	ButtonPtr executeBtn;
	TextAreaPtr CodeTextArea;
	TextAreaPtr ErrorTextArea;
	TextAreaPtr StackTraceTextArea;
	BorderLayoutConstraintsPtr ButtonConstraints;
	LabelPtr TabPanel1;
	LabelPtr TabPanel2;
	LabelPtr TabPanel3;
	LabelPtr Label1;
	ScrollPanelPtr TabContentA;
	ScrollPanelPtr TabContentB;
	ScrollPanelPtr TabContentC;
	PanelPtr SplitPanelPanel;
	SpringLayoutPtr PanelFlowLayout;
	BorderLayoutConstraintsPtr SplitPanelConstraints;
	SplitPanelPtr SplitPanel;

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
	virtual void attachApplication(void);
	virtual void dettachApplication(void);
	virtual void attachInterface(void);
	virtual void attachListeners(void);
	virtual void start(void);
	virtual void stop(void);
    virtual void reset(void);
	virtual void attachDebugInterface(void);
	virtual void detachDebugInterface(void);
	virtual void createDebugInterface(void);

    /*=========================  PROTECTED  ===============================*/
  protected:

    // Variables should all be in ApplicationPlayerBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    ApplicationPlayer(void);
    ApplicationPlayer(const ApplicationPlayer &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~ApplicationPlayer(void); 

    /*! \}                                                                 */
    
	class PlayerKeyListener : public KeyAdapter
	{
	public:
		PlayerKeyListener(ApplicationPlayerPtr TheApplicationPlayer);

		virtual void keyTyped(const KeyEventPtr e);
	protected :
		ApplicationPlayerPtr _ApplicationPlayer;
	};
	
    friend class PlayerKeyListener;

	PlayerKeyListener _PlayerKeyListener;
	
	class BasicListener : public ActionListener
	{
	public:
		BasicListener(ApplicationPlayerPtr TheApplicationPlayer);
		~BasicListener();

		virtual void actionPerformed(const ActionEventPtr e);
	protected :
		ApplicationPlayerPtr _ApplicationPlayer;
	
	};
	
	friend class BasicListener;

	BasicListener _BasicListener;

	
	class LuaErrorListener : public LuaListener
	{

	public:
		LuaErrorListener(ApplicationPlayerPtr TheApplicationPlayer);

	protected :
		ApplicationPlayerPtr _ApplicationPlayer;

	public:

    virtual void error(const LuaErrorEventPtr e)
    {
        std::string ErrorType("");
        switch(e->getStatus())
        {
        case LUA_ERRSYNTAX:
            //Syntax Error
            ErrorType = "Lua Syntax Error";
            break;
        case LUA_ERRMEM:
            //Memory Allocation Error
            ErrorType = "Lua Memory Allocation Error";
            break;
        case LUA_ERRRUN:
            //Memory Allocation Error
            ErrorType = "Lua Runtime Error";
            break;
        case LUA_ERRERR:
            //Memory Allocation Error
            ErrorType = "Lua Error in Error Handler";
            break;
        default:
            //Unknown
            ErrorType = "Lua Unknown Error";
            break;
        }
        _ApplicationPlayer->ErrorTextArea->moveCaretToEnd();
        if(_ApplicationPlayer->ErrorTextArea->getText().size() != 0)
        {
            _ApplicationPlayer->ErrorTextArea->write("\n");
        }
        _ApplicationPlayer->ErrorTextArea->write(ErrorType + ":\n    " + e->getErrorString());

        //Select the Error Tab
        _ApplicationPlayer->InfoTabPanel->setSelectedIndex(1);

        //Fill Stack Trace
        if(e->getStackTraceEnabled() && 
            (e->getStatus() == LUA_ERRMEM ||
             e->getStatus() == LUA_ERRERR ||
             e->getStatus() == LUA_ERRRUN))
        {
            std::stringstream ss;
            ss << "Lua Stack Trace: " << std::endl;
            
            MFString::StorageType::const_iterator ListItor(e->getMFStackTrace()->begin());
            for(; ListItor != e->getMFStackTrace()->end() ; ++ListItor)
            {
                ss << "     " << (*ListItor) << std::endl;
            }
            _ApplicationPlayer->StackTraceTextArea->write(ss.str());
        }
		}
	};



	friend class LuaErrorListener;

	LuaErrorListener  _LuaErrorListener;
	
	

	bool _IsDebugActive;
    void enableDebug(bool EnableDebug);
    void keyTyped(const KeyEventPtr e);
	void actionPerformed(const ActionEventPtr e);

    SimpleStatisticsForegroundPtr _DebugBasicStatForeground;
    SimpleStatisticsForegroundPtr _DebugRenderStatForeground;
    SimpleStatisticsForegroundPtr _DebugPhysicsStatForeground;
    SimpleStatisticsForegroundPtr _DebugParticleSystemStatForeground;
    SimpleStatisticsForegroundPtr _DebugAnimationStatForeground;
	
    void initDebugStatForegrounds(void);
    void hideAllStatForegrounds(void);
    void toggleStatForeground(StatisticsForegroundPtr TheForeground);
    void toggleDrawBoundingVolumes(void);
    void toggleFrustumCulling(void);
    void toggleDrawPhysicsCharacteristics(void);

    NodePtr getPhysicsDrawableNode(void);
    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class ApplicationPlayerBase;
	

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const ApplicationPlayer &source);
    void updateWindowTitle(void);

    PhysicsCharacteristicsDrawablePtr _PhysDrawable;
    NodePtr                           _PhysDrawableNode;
};

typedef ApplicationPlayer *ApplicationPlayerP;


OSG_END_NAMESPACE

#include "KEApplicationPlayerBase.inl"
#include "KEApplicationPlayer.inl"

#endif /* _KEAPPLICATIONPLAYER_H_ */
