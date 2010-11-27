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

#ifndef _KESCENECOMPONENTTREE_H_
#define _KESCENECOMPONENTTREE_H_
#ifdef __sgi
#pragma once
#endif

#include "KESceneComponentTreeBase.h"
#include <OpenSG/OSGTreeFields.h>
#include "KESceneTreeModelFields.h"
#include <OpenSG/OSGListSelectionEventDetailsFields.h>
#include <OpenSG/OSGTreeSelectionEventDetailsFields.h>
#include <OpenSG/OSGKeyEventDetailsFields.h>
#include <OpenSG/OSGActionEventDetailsFields.h>
#include <OpenSG/OSGMenuButtonFields.h>
#include <OpenSG/OSGForegroundFields.h>
#include <OpenSG/OSGLightFields.h>
#include <OpenSG/OSGCommandManager.h>
#include "Project/SceneObject/KESceneObjectFields.h"

OSG_BEGIN_NAMESPACE

/*! \brief SceneComponentTree class. See \ref
           PageKabalaEngineSceneComponentTree for a description.
*/

class KE_KABALAENGINE_DLLMAPPING SceneComponentTree : public SceneComponentTreeBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef SceneComponentTreeBase Inherited;
    typedef SceneComponentTree     Self;

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

    
    SceneTreeModel* getTreeModel(void) const;

    void clearSelection(void);
    void selectSceneObject(SceneObject* const ObjToSelect);
    void selectCamera(void);
    void selectLight(Light* const LightToSelect);
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in SceneComponentTreeBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    SceneComponentTree(void);
    SceneComponentTree(const SceneComponentTree &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~SceneComponentTree(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    void handleSelectedSceneChanged(ListSelectionEventDetails* const details);
    void handleSceneTreeKeyTyped(KeyEventDetails* const details);
    void handleSceneTreeSelectionAdded(TreeSelectionEventDetails* const details);
    void handleSceneTreeSelectionRemoved(TreeSelectionEventDetails* const details);

    
    void handleAddForeground(ActionEventDetails* const details,
                                             MenuButton* const TheMenuButton);
    void handleAddLight(ActionEventDetails* const details,
                                             MenuButton* const TheMenuButton);
    void handleAddSceneObject(ActionEventDetails* const details);

    void handleRemoveForeground(ActionEventDetails* const details,
                                Foreground* const TheForeground);
    void handleRemoveLight(ActionEventDetails* const details,
                           Light* const TheLight);
    void handleRemoveSceneObject(ActionEventDetails* const details,
                                 SceneObject* const TheSceneObject);

    boost::signals2::connection _SceneTreeKeyTypedConnection,
                                _SceneTreeSelectionAddedConnection,
                                _SceneTreeSelectionRemovedConnection;

    boost::signals2::connection _SceneSelectionConnection;

    TreeRecPtr _ComponentTree;
    SceneTreeModelRecPtr _ComponentTreeModel;
    CommandManagerPtr _TheCommandManager;
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class SceneComponentTreeBase;
    friend class SceneComponentTreeComponentGenerator;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const SceneComponentTree &source);
};

typedef SceneComponentTree *SceneComponentTreeP;

OSG_END_NAMESPACE

#include "KESceneComponentTreeBase.inl"
#include "KESceneComponentTree.inl"

#endif /* _KESCENECOMPONENTTREE_H_ */
