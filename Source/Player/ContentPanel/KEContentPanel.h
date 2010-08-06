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
#include <OpenSG/OSGSplitPanel.h>
#include <OpenSG/OSGTabPanel.h>
#include <OpenSG/OSGTextArea.h>
#include <OpenSG/OSGScrollPanel.h>
#include <OpenSG/OSGBorderLayoutConstraints.h>
#include <OpenSG/OSGLabel.h>
#include <OpenSG/OSGPanel.h>
#include <OpenSG/OSGSpringLayout.h>
#include <OpenSG/OSGSpringLayoutConstraints.h>
#include <OpenSG/OSGCardLayout.h>

#include <OpenSG/OSGMouseListener.h>
#include <OpenSG/OSGKeyAdapter.h>
#include <OpenSG/OSGMouseMotionListener.h>
#include <OpenSG/OSGMouseWheelListener.h>
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
    void setApplicationPlayer(ApplicationPlayerRefPtr TheApplicationPlayer);
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
    void actionPerformed(const ActionEventUnrecPtr e);

    class CloseButtonListener:public ActionListener
    {
      public:
        CloseButtonListener(ContentPanelRefPtr TheContentPanel);
        ~CloseButtonListener(void);

        virtual void actionPerformed(const ActionEventUnrecPtr e);
      protected :
        ContentPanelRefPtr _ContentPanel;
    };

    CloseButtonListener _CloseButtonListener;
    friend class CloseButtonListener;


    class SceneEditorPanelListener : public MouseListener, 
    public MouseMotionListener,
    public KeyAdapter,
    public MouseWheelListener
    {
      public:
        SceneEditorPanelListener(ContentPanelRefPtr TheContentPanel);
        ~SceneEditorPanelListener(void);

        virtual void mouseMoved(const MouseEventUnrecPtr e);
        virtual void mouseDragged(const MouseEventUnrecPtr e);

        virtual void mouseClicked(const MouseEventUnrecPtr e);
        virtual void mouseEntered(const MouseEventUnrecPtr e);
        virtual void mouseExited(const MouseEventUnrecPtr e);
        virtual void mousePressed(const MouseEventUnrecPtr e);
        virtual void mouseReleased(const MouseEventUnrecPtr e);

        virtual void mouseWheelMoved(const MouseWheelEventUnrecPtr e);

        virtual void keyTyped(const KeyEventUnrecPtr e);

      protected :
        ContentPanelRefPtr _ContentPanel;
    };

    SceneEditorPanelListener _SceneEditorPanelListener;
    friend class SceneEditorPanelListener;
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
