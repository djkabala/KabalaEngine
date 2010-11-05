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

#ifndef _KESCENETREEMODEL_H_
#define _KESCENETREEMODEL_H_
#ifdef __sgi
#pragma once
#endif

#include "KESceneTreeModelBase.h"
#include <OpenSG/OSGForegroundFields.h>
#include <OpenSG/OSGLightFields.h>
#include "Project/SceneObject/KESceneObject.h"

OSG_BEGIN_NAMESPACE

/*! \brief SceneTreeModel class. See \ref
           PageKabalaEngineSceneTreeModel for a description.
*/

class KE_KABALAENGINE_DLLMAPPING SceneTreeModel : public SceneTreeModelBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

   enum SceneComponents
   {
       SceneComponentsFirst  = 0,
       BasicComponent        = SceneComponentsFirst,
       ForegroundsComponent  = BasicComponent        + 1,
       BackgroundComponent   = ForegroundsComponent  + 1,
       CameraComponent       = BackgroundComponent   + 1,
       SceneObjectsComponent = CameraComponent       + 1,
       LightsComponent       = SceneObjectsComponent + 1,
       DynamicsComponent     = LightsComponent       + 1,
       SceneComponentsLast   = LightsComponent     + 1
   };

   enum DynamicsComponents
   {
       DynamicsComponentsFirst = SceneComponentsLast + 1,
       ScriptsComponent        = DynamicsComponentsFirst,
       BehavioursComponent     = ScriptsComponent    + 1,
       AnimationsComponent     = BehavioursComponent + 1,
       DynamicsComponentsLast  = AnimationsComponent + 1
   };

    typedef SceneTreeModelBase Inherited;
    typedef SceneTreeModel     Self;

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
	//Returns the child of parent at index index in the parent's child array.
	virtual boost::any getChild(const boost::any& parent, const UInt32& index) const;

	//Returns the number of children of parent.
	virtual UInt32 getChildCount(const boost::any& parent) const;

	//Returns the index of child in parent.
	virtual UInt32 getIndexOfChild(const boost::any& parent, const boost::any& child) const;

	//Returns the root of the tree.
	virtual boost::any getRoot(void) const;

	//Returns true if node is a leaf.
	virtual bool isLeaf(const boost::any& node) const;

	//Messaged when the user has altered the value for the item identified by path to newValue.
	virtual void valueForPathChanged(TreePath path, const boost::any& newValue);

    //Sets the root to root.
    void setRoot(Scene* const root);

    //Get the NodeUnrecPtr to the Root Node
    Scene* getRootScene(void) const;

    void foregroundAdded(Foreground* const TheForeground);
    void foregroundWillBeRemoved(Foreground* const TheForeground);
    void foregroundRemoved(Foreground* const TheForeground);

    void lightAdded(Light* const TheLightNode);
    void lightWillBeRemoved(Light* const TheLightNode);
    void lightRemoved(Light* const TheLightNode);

    void sceneObjectAdded(SceneObject* const TheSceneObject);
    void sceneObjectWillBeRemoved(SceneObject* const TheSceneObject);
    void sceneObjectRemoved(SceneObject* const TheSceneObject);

    TreePath getSceneObjectPath(SceneObject* const ObjToSelect) const;
    TreePath getCameraPath(void) const;
    TreePath getLightPath(Light* const LightToSelect) const;
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in SceneTreeModelBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    SceneTreeModel(void);
    SceneTreeModel(const SceneTreeModel &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~SceneTreeModel(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    
    void handleViewportFieldsChanged(FieldContainer *fc, ConstFieldMaskArg whichField);
    void handleSceneFieldsChanged(FieldContainer *fc, ConstFieldMaskArg whichField);
    
    void attachChangedFunctors(void);
    void dettachChangedFunctors(void);
    FieldContainer* _ViewportFieldsChangedContainer;
    FieldContainer* _SceneFieldsChangedContainer;
    


    virtual void setAsVisible(const TreePath& path);

    virtual void setAsNotVisible(const TreePath& path);
    
    void attachChangeHandler(FieldContainer * const TheContainer,
                             const TreePath& Parent, 
                             const TreePath& ChildPath);
    void dettachChangeHandler(FieldContainer * const TheContainer,
                              const TreePath& Parent, 
                              const TreePath& ChildPath);

    void handleFieldChanged(FieldContainer *fc, 
                            ConstFieldMaskArg whichField,
                            const TreePath& Parent, 
                            const TreePath& ChildPath);
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class SceneTreeModelBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const SceneTreeModel &source);
};

typedef SceneTreeModel *SceneTreeModelP;

OSG_END_NAMESPACE

#include "Project/Scene/KEScene.h"      // InternalRoot Class
#include "KESceneTreeModelBase.inl"
#include "KESceneTreeModel.inl"

#endif /* _KESCENETREEMODEL_H_ */
