/*---------------------------------------------------------------------------*\
 *                             Kabala Engine                                 *
 *                                                                           *
 *                                                                           *
 *   contact: djkabala@gmail.com                                             *
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

#include <OpenSG/OSGConfig.h>

#include "KEContentPanelBase.h"

#include <OpenSG/UserInterface/OSGSplitPanel.h>
#include <OpenSG/UserInterface/OSGTabPanel.h>
#include <OpenSG/UserInterface/OSGTextArea.h>
#include <OpenSG/UserInterface/OSGScrollPanel.h>
#include <OpenSG/UserInterface/OSGBorderLayoutConstraints.h>
#include <OpenSG/UserInterface/OSGLabel.h>
#include <OpenSG/UserInterface/OSGPanel.h>
#include <OpenSG/UserInterface/OSGSpringLayout.h>
#include <OpenSG/UserInterface/OSGSpringLayoutConstraints.h>
#include <OpenSG/UserInterface/OSGCardLayout.h>

OSG_BEGIN_NAMESPACE

/*! \brief ContentPanel class. See \ref 
           PageKabalaEngineContentPanel for a description.
*/

class KE_KABALAENGINELIB_DLLMAPPING ContentPanel : public ContentPanelBase
{
  private:

    typedef ContentPanelBase Inherited;

	bool _IsSplit;

    SplitPanelPtr  _LuaEditorSplitPanel;
    PanelPtr       _SceneEditorPanel;

    CardLayoutPtr  _MainCardLayout;

    TabPanelPtr    _LeftTabPanel;
    LabelPtr       _LeftTabPanelLabel;
    ScrollPanelPtr _LeftTabPanelContent;
    TextAreaPtr    _LeftTabPanelTextArea;


    TabPanelPtr    _RightTabPanel;
    LabelPtr       _RightTabPanelLabel;
    ScrollPanelPtr _RightTabPanelContent;
    TextAreaPtr    _RightTabPanelTextArea;

    void createLuaEditorSplitPanel(void);
    void createSceneEditorPanel(void);
	void createLeftTabPanel(void);
	void createRightTabPanel(void);
	void createDefaultTabs(void);
	void updatePanel(void);
	void actionPerformed(const ActionEventPtr e);
	

    /*==========================  PUBLIC  =================================*/
  public:
	
	void addTab(void);
	void removeTab(UInt32);
	void setIsSplit(bool value);	
	bool getIsSplit(void);
	void init(void);
	void addTabWithText(Path);
	void closeCurrentWindow(void);
	void saveTextFile(Path);

    void setView(UInt32 Index);
	
    /*---------------------------------------------------------------------*/
    /*! \name                      Sync                                    */
    /*! \{                                                                 */

    virtual void changed(BitVector  whichField, 
                         UInt32     origin    );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    virtual void dump(      UInt32     uiIndent = 0, 
                      const BitVector  bvFlags  = 0) const;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:

	  class CloseButtonListener:public ActionListener
	  {
		public:
			CloseButtonListener(ContentPanelPtr TheContentPanel);
			~CloseButtonListener(void);

			virtual void actionPerformed(const ActionEventPtr e);
		protected :
			ContentPanelPtr _ContentPanelPtr;
	  };

	  CloseButtonListener _CloseButtonListener;
	  friend class CloseButtonListener;

	 
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
    
    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class ContentPanelBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const ContentPanel &source);
};

typedef ContentPanel *ContentPanelP;

OSG_END_NAMESPACE

#include "KEContentPanelBase.inl"
#include "KEContentPanel.inl"

#endif /* _KECONTENTPANEL_H_ */
