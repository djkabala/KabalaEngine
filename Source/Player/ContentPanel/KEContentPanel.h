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

#ifndef _KECONTENTPANEL_H_
#define _KECONTENTPANEL_H_
#ifdef __sgi
#pragma once
#endif

#include "KEContentPanelBase.h"
#include <OpenSG/OSGSplitPanelFields.h>
#include <OpenSG/OSGTabPanelFields.h>
#include <OpenSG/OSGTextAreaFields.h>
#include <OpenSG/OSGScrollPanelFields.h>
#include <OpenSG/OSGBorderLayoutConstraintsFields.h>
#include <OpenSG/OSGLabelFields.h>
#include <OpenSG/OSGPanelFields.h>
#include <OpenSG/OSGSpringLayoutFields.h>
#include <OpenSG/OSGSpringLayoutConstraintsFields.h>
#include <OpenSG/OSGCardLayoutFields.h>
#include <OpenSG/OSGActionEventDetailsFields.h>

#include "Player/KEApplicationPlayerFields.h"

OSG_BEGIN_NAMESPACE

/*! \brief ContentPanel class. See \ref
           PageKabalaEngineContentPanel for a description.
*/

class KE_KABALAENGINE_DLLMAPPING ContentPanel : public ContentPanelBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef ContentPanelBase Inherited;
    typedef ContentPanel     Self;

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
	
    void addTab(void);
    void removeTab(UInt32);
    void setIsSplit(bool value);	
    bool getIsSplit(void);
    void init(void);
    void addTabWithText(BoostPath);
    void closeCurrentWindow(void);
    void saveTextFile(BoostPath);

    void setView(UInt32 Index);
    void setApplicationPlayer(ApplicationPlayer* const TheApplicationPlayer);
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in ContentPanelBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    ContentPanel(void);
    ContentPanel(const ContentPanel &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~ContentPanel(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Sync                                   */
    /*! \{                                                                 */

    virtual void resolveLinks(void);

    /*! \}                                                                 */

    ApplicationPlayerRefPtr _ApplicationPlayer;

    bool _IsSplit;

    SplitPanelRefPtr  _LuaEditorSplitPanel;
    PanelRefPtr       _SceneEditorPanel;

    CardLayoutRefPtr  _MainCardLayout;

    TabPanelRefPtr    _LeftTabPanel;
    LabelRefPtr       _LeftTabPanelLabel;
    ScrollPanelRefPtr _LeftTabPanelContent;
    TextAreaRefPtr    _LeftTabPanelTextArea;


    TabPanelRefPtr    _RightTabPanel;
    LabelRefPtr       _RightTabPanelLabel;
    ScrollPanelRefPtr _RightTabPanelContent;
    TextAreaRefPtr    _RightTabPanelTextArea;

    void createLuaEditorSplitPanel(void);
    void createSceneEditorPanel(void);
    void createLeftTabPanel(void);
    void createRightTabPanel(void);
    void createDefaultTabs(void);
    void updatePanel(void);

    void handleCloseButtonAction(ActionEventDetails* const details);
    boost::signals2::connection _CloseRightButtonActionConnection,
                                _CloseLeftButtonActionConnection;

    void handleSceneEditorPanelMouseDragged(MouseEventDetails* const details);
    void handleSceneEditorPanelMouseClicked(MouseEventDetails* const details);
    void handleSceneEditorPanelMousePressed(MouseEventDetails* const details);
    void handleSceneEditorPanelMouseReleased(MouseEventDetails* const details);
    void handleSceneEditorPanelMouseWheelMoved(MouseWheelEventDetails* const details);
    void handleSceneEditorPanelKeyTyped(KeyEventDetails* const details);
    boost::signals2::connection _SceneEditorPanelMouseDraggedConnection,
                                _SceneEditorPanelMouseClickedConnection,
                                _SceneEditorPanelMousePressedConnection,
                                _SceneEditorPanelMouseReleasedConnection,
                                _SceneEditorPanelMouseWheelMovedConnection,
                                _SceneEditorPanelKeyTypedConnection;
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class ContentPanelBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const ContentPanel &source);
};

typedef ContentPanel *ContentPanelP;

OSG_END_NAMESPACE

#include "Player/KEApplicationPlayer.h"
#include "KEContentPanelBase.inl"
#include "KEContentPanel.inl"

#endif /* _KECONTENTPANEL_H_ */
