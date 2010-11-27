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

#ifndef _KESCENEEDITINGVIEWPORT_H_
#define _KESCENEEDITINGVIEWPORT_H_
#ifdef __sgi
#pragma once
#endif

#include "KESceneEditingViewportBase.h"
#include "Project/Scene/KESceneFields.h"

#include <OpenSG/OSGLineChunkFields.h>
#include <OpenSG/OSGMaterialChunkFields.h>
#include <OpenSG/OSGSimpleStatisticsForegroundFields.h>

//XForm Manipulator
#include <OpenSG/OSGManipulatorManager.h>
#include <OpenSG/OSGReplicateTransformFields.h>

//Animation
#include <OpenSG/OSGKeyframeTransformationSequenceFields.h>
#include <OpenSG/OSGKeyframeAnimatorFields.h>
#include <OpenSG/OSGFieldAnimationFields.h>
#include <OpenSG/OSGAnimationGroupFields.h>
#include <OpenSG/OSGAnimationEventDetailsFields.h>

#include <OpenSG/OSGLightFields.h>

OSG_BEGIN_NAMESPACE

/*! \brief SceneEditingViewport class. See \ref
           PageKabalaEngineSceneEditingViewport for a description.
*/

class KE_KABALAENGINE_DLLMAPPING SceneEditingViewport : public SceneEditingViewportBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:
    enum OverlayGraphMasks
    {
        DEBUG_GRAPH_NONE          = 0x0,
        DEBUG_GRAPH_DRAWN         = 0x1,
        DEBUG_GRAPH_INTERSECTABLE = 0x2
    };

    typedef SceneEditingViewportBase Inherited;
    typedef SceneEditingViewport     Self;

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
    virtual void updateLayout(void);

    virtual void mouseClicked(MouseEventDetails* const e);
    virtual void mouseEntered(MouseEventDetails* const e);
    virtual void mouseExited(MouseEventDetails* const e);
    virtual void mousePressed(MouseEventDetails* const e);
    virtual void mouseReleased(MouseEventDetails* const e);
    virtual void mouseMoved(MouseEventDetails* const e);
    virtual void mouseDragged(MouseEventDetails* const e);
    virtual void mouseWheelMoved(MouseWheelEventDetails* const e);
    
	virtual void keyPressed(KeyEventDetails* const e);
	virtual void keyReleased(KeyEventDetails* const e);
	virtual void keyTyped(KeyEventDetails* const e);

	void selectNode(const Pnt2f& ViewportPoint);
    void setNewCameraTransform(const Matrix& Transform);
    void resetCamera(void);

    
    void setManipulatorType(ManipulatorManager::ManipulatorType Type);
    ManipulatorManager::ManipulatorType getManipulatorType(void) const;

    void focusSelectedNodes(void);
    void focusNode(Node* TheNode);
    void showAll(CameraRefPtr TheCameraOrig,
                 NodeRefPtr Scene,
                 ViewportRefPtr LocalViewport);

    void setStatisticsEnabled(bool enable);
    bool getStatisticsEnabled(void) const;
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in SceneEditingViewportBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    SceneEditingViewport(void);
    SceneEditingViewport(const SceneEditingViewport &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~SceneEditingViewport(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*---------------------------------------------------------------------*/
    /*! \}                                                                 */
    /*! \name                  Visual Annotations                          */
    /*! \{                                                                 */

    //Main Highlight Node
    NodeRefPtr _HighlightNode;

    //Volume Box
    NodeRefPtr _HighlightVolumeBoxNode;
    GeometryRefPtr _HighlightVolumeBoxGeo;
    LineChunkRefPtr _HighlightBoundBoxMatLineChunk;

    //Local Coordinate Axis
    NodeRefPtr _HighlightAxisNode;
    GeometryRefPtr _HighlightAxisGeo;
    LineChunkRefPtr _HighlightAxisLineChunk;

    //Mesh Wireframe
    NodeRefPtr _WireframeMatGroupNode;
    NodeRefPtr _WireframeNode;
    ReplicateTransformRefPtr _WireframeTransform;
    MaterialChunkRefPtr _WireframeMatMaterialChunk;
    LineChunkRefPtr _WireframeMatLineChunk;

    //Workspace grid
    NodeRefPtr _WorkspaceGrid;
    LineChunkRefPtr _WorkspaceGridLineChunk;

    LightRecPtr _OverlayLight;
    
    //Transformation Manipulators
    ManipulatorManager _XFormManipMgr;
    NodeRefPtr         _XFormManipNode;

    //Camera Node
    NodeRefPtr               _CameraNode;
    ReplicateTransformRefPtr _CameraNodeCore;


    void handleSceneEditorPanelMouseDragged(MouseEventDetails* const details);
    void handleSceneEditorPanelMouseReleased(MouseEventDetails* const details);
    boost::signals2::connection _SceneEditorPanelMouseDraggedConnection,
                                _SceneEditorPanelMouseReleasedConnection;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \}                                                                 */
    /*! \name                  Camera Animations                           */
    /*! \{                                                                 */

    //Debug Camera Animation
    std::vector<KeyframeTransformationSequenceRefPtr> _CameraTransformationKeyframes;
    std::vector<FieldAnimationRefPtr> _CameraTransAnimations;
    std::vector<AnimationGroupRefPtr> _CameraAnimationGroups;

    /*! \}                                                                 */
    void attachScene(Scene* const TheScene);
    void dettachScene(void);

    ViewportTransitPtr createOverlayViewport(GLViewport* const ViewportComponent);
    void createHighlightNode(void);
    void createHighlightBoundBoxNode(void);
    void createHighlightAxisNode(void);
    void createHighlightTriMeshNode(void);
    void createXFormManipulator(void);
    void createCameraNode(void);
    void updateHighlightNode(void);
    void updateWireframeNode(void);
    void updateXFormManipulator(void);
    void animateCameraBeacon(UInt32 Index, const Matrix& Transform);

    void handleCameraAnimationEnded(AnimationEventDetails* const details,
                                    UInt32 Index,
                                    const Matrix& FinalCameraTransform);

    std::map<UInt32,boost::signals2::connection> _CameraAnimConnections;

	virtual void drawInternal(Graphics* const Graphics, Real32 Opacity = 1.0f) const;

    SimpleStatisticsForegroundTransitPtr createStatisticsForeground(void);
    bool _EnableStatistics;

    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class SceneEditingViewportBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const SceneEditingViewport &source);
};

typedef SceneEditingViewport *SceneEditingViewportP;

OSG_END_NAMESPACE

#include <OpenSG/OSGGLViewport.h>       // SceneViewports Class
#include <OpenSG/OSGGLViewport.h>       // EditorOverlayViewports Class
#include "KESceneEditingViewportBase.inl"
#include "KESceneEditingViewport.inl"

#endif /* _KESCENEEDITINGVIEWPORT_H_ */
