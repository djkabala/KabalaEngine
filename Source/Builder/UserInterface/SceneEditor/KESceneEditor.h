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

#ifndef _KESCENEEDITOR_H_
#define _KESCENEEDITOR_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>

#include "KESceneEditorBase.h"
#include "Builder/UserInterface/IconManager/KEIconManager.h"
#include <OpenSG/UserInterface/OSGTabPanelFields.h>
#include <OpenSG/UserInterface/OSGLabelFields.h>
#include <OpenSG/UserInterface/OSGChangeListener.h>

OSG_BEGIN_NAMESPACE

/*! \brief SceneEditor class. See \ref 
           PageKabalaEngineSceneEditor for a description.
*/

class KE_KABALAENGINELIB_DLLMAPPING SceneEditor : public SceneEditorBase
{
  private:

    typedef SceneEditorBase Inherited;

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

    // Variables should all be in SceneEditorBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    SceneEditor(void);
    SceneEditor(const SceneEditor &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~SceneEditor(void); 

    /*! \}                                                                 */
    
	static const std::string _PresentationName;
	static const std::string _PresentationIconName;

	std::vector< ::osg::UInt32 > getEditorTypeIds(void) const;

	PanelPtr createEditorTab(SceneComponentEditorPtr Editor, IconManagerPtr TheIconManager) const;

    LabelPtr _SceneLabel;
    LabelPtr _SceneNameLabel;
    TabPanelPtr _SceneEditorsTabPanel;
    
	class EditorsTabPanelListener : public ChangeListener
	{
	public :
		EditorsTabPanelListener(SceneEditorPtr TheSceneEditor);
		
        virtual void stateChanged(const ChangeEvent& e);
	protected :
		SceneEditorPtr _SceneEditor;
	};

	friend class EditorsTabPanelListener;

	EditorsTabPanelListener _EditorsTabPanelListener;
    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class SceneEditorBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const SceneEditor &source);
};

typedef SceneEditor *SceneEditorP;

OSG_END_NAMESPACE

#include "KESceneEditorBase.inl"
#include "KESceneEditor.inl"

#endif /* _KESCENEEDITOR_H_ */
