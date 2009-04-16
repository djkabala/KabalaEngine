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

#ifndef _KESCENEBACKGROUNDSEDITOR_H_
#define _KESCENEBACKGROUNDSEDITOR_H_
#ifdef __sgi
#pragma once
#endif

#include "KEConfig.h"

#include <vector>
#include <map>

#include "KESceneBackgroundsEditorBase.h"
#include <OpenSG/UserInterface/OSGList.h>
#include <OpenSG/UserInterface/OSGDefaultListSelectionModel.h>
#include <OpenSG/UserInterface/OSGScrollPanel.h>
#include <OpenSG/UserInterface/OSGSplitPanel.h>
#include <OpenSG/UserInterface/OSGComboBox.h>
#include <OpenSG/UserInterface/OSGLabel.h>
#include <OpenSG/UserInterface/OSGTextField.h>
#include <OpenSG/UserInterface/OSGImageComponent.h>
#include <OpenSG/UserInterface/OSGPanel.h>
#include "KEBackgroundsListComponentGeneratorFields.h"
#include <OpenSG/UserInterface/OSGListSelectionListener.h>
#include <OpenSG/UserInterface/OSGTextListener.h>
#include <OpenSG/UserInterface/OSGMenuButton.h>

#include <OpenSG/UserInterface/OSGGLViewport.h>
#include <OpenSG/OSGNode.h>
#include <OpenSG/OSGGroup.h>
#include <OpenSG/OSGViewport.h>

#include "KESceneBackgroundsComboBoxModel.h"
#include "Builder/UserInterface/Editors/KEFieldContainerEditor.h"

#include <OpenSG/UserInterface/OSGActionListener.h>
#include <OpenSG/UserInterface/OSGDerivedFieldContainerComboBoxModel.h>
#include "Builder/UserInterface/IconManager/KEIconManager.h"

OSG_USING_NAMESPACE
KE_BEGIN_NAMESPACE

/*! \brief SceneBackgroundsEditor class. See \ref 
           PageKabalaEngineSceneBackgroundsEditor for a description.
*/

class KE_KABALAENGINELIB_DLLMAPPING SceneBackgroundsEditor : public SceneBackgroundsEditorBase
{
  private:

    typedef SceneBackgroundsEditorBase Inherited;

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
    /*=========================  PROTECTED  ===============================*/
  protected:

    // Variables should all be in SceneBackgroundsEditorBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    SceneBackgroundsEditor(void);
    SceneBackgroundsEditor(const SceneBackgroundsEditor &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~SceneBackgroundsEditor(void); 

    /*! \}                                                                 */
	static const std::string _PresentationName;
	static const std::string _PresentationIconName;

	IconManagerPtr _IconManager;
    PanelPtr _BackgroundNavigationPanel;
	LabelPtr _InitialBackgroundLabel;
	ComboBoxPtr _InitialBackgroundComboBox;
	::osg::ListPtr _BackgroundsList;
	SceneBackgroundsComboBoxModelPtr _ListModel;
	ListSelectionModelPtr _ListSelectionModel;
	BackgroundsListComponentGeneratorPtr _ListComponentGenerator;
	ScrollPanelPtr _BackgroundListScrollPanel;
	SplitPanelPtr _BackgroundSplitPanel;

    PanelPtr _BackgroundViewEditorPanel;
	ViewportPtr _BackgroundPreviewViewport;
	GLViewportPtr _BackgroundPreviewComponent;
	PanelPtr _BackgroundDescEditorPanel;
	PanelPtr _BackgroundEditorPanel;
    TextFieldPtr _BackgroundNameTextField;
    ImageComponentPtr _BackgroundTypeIcon;
    LabelPtr _BackgroundTypeLabel;

    //The Background creator Menu Button
    MenuButtonPtr _BackgroundCreateMenuButton;
    DerivedFieldContainerComboBoxModelPtr _BackgroundTypesModel;
    
	class BackgroundsListListener: public ListSelectionListener
	{
	  public:
		BackgroundsListListener(SceneBackgroundsEditorPtr TheSceneBackgroundsEditor);

		virtual void selectionChanged(const ListSelectionEvent& e);
	  protected :
		SceneBackgroundsEditorPtr _SceneBackgroundsEditor;
	};

	friend class BackgroundsListListener;

	BackgroundsListListener _BackgroundsListListener;
    
	class BackgroundCreateMenuButtonListener: public ActionListener
	{
	  public:
		BackgroundCreateMenuButtonListener(SceneBackgroundsEditorPtr TheSceneBackgroundsEditor);

        virtual void actionPerformed(const ActionEvent& e);

        void setApplicationBuilder(ApplicationBuilderPtr TheApplicationBuilder);
	  protected :
		SceneBackgroundsEditorPtr _SceneBackgroundsEditor;
        ApplicationBuilderPtr _ApplicationBuilder;
	};

	friend class BackgroundCreateMenuButtonListener;

	BackgroundCreateMenuButtonListener _BackgroundCreateMenuButtonListener;
	class BackgroundDeleteActionListener: public ActionListener
	{
	  public:
		BackgroundDeleteActionListener(SceneBackgroundsEditorPtr TheSceneBackgroundsEditor);

        virtual void actionPerformed(const ActionEvent& e);

        void setApplicationBuilder(ApplicationBuilderPtr TheApplicationBuilder);
	  protected :
		SceneBackgroundsEditorPtr _SceneBackgroundsEditor;
        ApplicationBuilderPtr _ApplicationBuilder;
	};

	friend class BackgroundDeleteActionListener;

	BackgroundDeleteActionListener _BackgroundDeleteActionListener;
    
	class BackgroundNameTextListener: public TextListener
	{
	  public:
		BackgroundNameTextListener(SceneBackgroundsEditorPtr TheSceneBackgroundsEditor);

        virtual void textValueChanged(const TextEvent& e);

        void setApplicationBuilder(ApplicationBuilderPtr TheApplicationBuilder);
	  protected :
		SceneBackgroundsEditorPtr _SceneBackgroundsEditor;
        ApplicationBuilderPtr _ApplicationBuilder;
	};

	friend class BackgroundNameTextListener;

	BackgroundNameTextListener _BackgroundNameTextListener;

    std::vector<ComponentPtr> _Tools;
    
    std::map<UInt32, FieldContainerEditorPtr> _Editors;
    FieldContainerEditorPtr _GenericEditor;
    FieldContainerEditorPtr _ActiveEditor;
    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class SceneBackgroundsEditorBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const SceneBackgroundsEditor &source);
};

typedef SceneBackgroundsEditor *SceneBackgroundsEditorP;

KE_END_NAMESPACE

#include "KESceneBackgroundsEditorBase.inl"
#include "KESceneBackgroundsEditor.inl"

#endif /* _KESCENEBACKGROUNDSEDITOR_H_ */
