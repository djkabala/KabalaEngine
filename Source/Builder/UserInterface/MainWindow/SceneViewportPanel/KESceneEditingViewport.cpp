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

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <cstdlib>
#include <cstdio>

#define KE_COMPILEKABALAENGINELIB

#include <OpenSG/OSGConfig.h>

#include "KESceneEditingViewport.h"
#include "Project/Scene/KEScene.h"

#include <OpenSG/OSGBlendChunk.h>
#include <OpenSG/OSGChunkMaterial.h>
#include <OpenSG/OSGMultiPassMaterial.h>
#include <OpenSG/OSGLineChunk.h>
#include <OpenSG/OSGMaterialChunk.h>
#include <OpenSG/OSGDepthChunk.h>
#include <OpenSG/OSGReplicateTransform.h>
#include <OpenSG/OSGSimpleGeometryExt.h>
#include <OpenSG/OSGTypedGeoIntegralProperty.h>
#include <OpenSG/OSGTypedGeoVectorProperty.h>
#include <OpenSG/OSGVisitSubTree.h>
#include <OpenSG/OSGMaterialGroup.h>
#include <OpenSG/OSGPassiveBackground.h>
#include <OpenSG/OSGDirectionalLight.h>
#include <OpenSG/OSGStackedTransform.h>
#include <OpenSG/OSGTransformationElement.h>
#include <OpenSG/OSGPhysicsBody.h>
#include <OpenSG/OSGSetFieldValueCommand.h>
#include <OpenSG/OSGSceneFileHandler.h>


#include <OpenSG/OSGMaterialChunkOverrideGroup.h>
#include <OpenSG/OSGPolygonChunk.h>

#include <OpenSG/OSGKeyframeSequences.h>
#include <OpenSG/OSGFieldAnimation.h>
#include <OpenSG/OSGAnimationGroup.h>
#include <OpenSG/OSGKeyframeAnimator.h>
#include <OpenSG/OSGKeyframeAnimator.h>
#include <OpenSG/OSGSimpleStatisticsForeground.h>

#include "Builder/KEApplicationBuilder.h"
#include "Builder/UserInterface/MainWindow/KEMainWindow.h"
#include "Builder/UserInterface/MainWindow/MainMenu/KEMainMenu.h"
#include "Builder/UserInterface/MainWindow/MainToolbar/KEMainToolbar.h"
#include "Builder/UserInterface/MainWindow/StatusBar/KEStatusBar.h"
#include "Builder/UserInterface/MainWindow/HelpPanel/KEHelpPanel.h"
#include "Builder/UserInterface/MainWindow/SceneComponentTree/KESceneComponentTree.h"
#include "Builder/UserInterface/MainWindow/SceneNavigationPanel/KESceneNavigationPanel.h"
#include "Builder/UserInterface/MainWindow/SceneViewportPanel/KESceneViewportPanel.h"
#include "Builder/UserInterface/MainWindow/SceneViewportToolbar/KESceneViewportToolbar.h"
#include "Builder/UserInterface/MainWindow/Editors/KEEditors.h"

#include "KEUtils.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGSceneEditingViewportBase.cpp file.
// To modify it, please change the .fcd file (OSGSceneEditingViewport.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void SceneEditingViewport::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/
void SceneEditingViewport::updateLayout(void)
{
    Pnt2f InsetsTopLeft, InsetBottomRight;
    getInsideInsetsBounds(InsetsTopLeft, InsetBottomRight);
	Vec2f borderSize(InsetBottomRight-InsetsTopLeft);

    for(UInt32 i(0) ; i<getMFSceneViewports()->size() ; ++i)
    {
        getSceneViewports(i)->setPosition(InsetsTopLeft);
        getSceneViewports(i)->setSize(borderSize);
        getEditorOverlayViewports(i)->setPosition(InsetsTopLeft);
        getEditorOverlayViewports(i)->setSize(borderSize);
    }
}

void SceneEditingViewport::mouseClicked(MouseEventDetails* const details)
{
    if(details->getButton() == MouseEventDetails::BUTTON1)
    {
        ApplicationBuilderUnrecPtr AppBuilder = dynamic_cast<ApplicationBuilder*>(MainApplication::the()->getBuilderMode());
        if (details->getButton() == MouseEventDetails::BUTTON1)
        {
            Node* SelectedNode;
            for(UInt32 i(0) ; i<getMFSceneViewports()->size() ; ++i)
            {
                SelectedNode = getSceneViewports(i)->grabNode(details->getLocation());
                SceneObjectUnrecPtr ParentSceneObject = AppBuilder->getSelectedScene()->findParentSceneObject(SelectedNode);
                if(ParentSceneObject != NULL)
                {
                    AppBuilder->getMainWindow()->getSceneComponentTree()->selectSceneObject(ParentSceneObject);
                    Component::mouseClicked(details);
                    return;
                }
            }
        }

        //Select a Node
        AppBuilder->getMainWindow()->getSceneComponentTree()->clearSelection();
    }
    Inherited::mouseClicked(details);
}

void SceneEditingViewport::mouseEntered(MouseEventDetails* const details)
{
    Inherited::mouseEntered(details);
}

void SceneEditingViewport::mouseExited(MouseEventDetails* const details)
{
    Inherited::mouseExited(details);
}

void SceneEditingViewport::mousePressed(MouseEventDetails* const details)
{
    if(details->getButton() == MouseEventDetails::BUTTON1)
    {
        for(UInt32 i(0) ; i<getMFSceneViewports()->size() ; ++i)
        {
            _XFormManipMgr.handleMouseSelectionTest(details->getButton(), details->getX(),details->getY());
            if (_XFormManipMgr.isManipulating() )
            {
                _SceneEditorPanelMouseDraggedConnection = dynamic_cast<WindowEventProducer*>(details->getSource())->connectMouseDragged(boost::bind(&SceneEditingViewport::handleSceneEditorPanelMouseDragged, this, _1));
                _SceneEditorPanelMouseReleasedConnection = dynamic_cast<WindowEventProducer*>(details->getSource())->connectMouseReleased(boost::bind(&SceneEditingViewport::handleSceneEditorPanelMouseReleased, this, _1));
                details->consume();
                return;
            }
        }
    }
    Inherited::mousePressed(details);
}

void SceneEditingViewport::mouseReleased(MouseEventDetails* const details)
{
    Inherited::mouseReleased(details);
}

void SceneEditingViewport::mouseMoved(MouseEventDetails* const details)
{
    _XFormManipMgr.handleMouseMoveTest(details->getX(),details->getY());

    Inherited::mouseMoved(details);
}

void SceneEditingViewport::mouseDragged(MouseEventDetails* const details)
{
    Inherited::mouseDragged(details);
}

void SceneEditingViewport::mouseWheelMoved(MouseWheelEventDetails* const details)
{
    Inherited::mouseWheelMoved(details);
}

void SceneEditingViewport::keyReleased(KeyEventDetails* const details)
{
    Inherited::keyReleased(details);
}

void SceneEditingViewport::keyPressed(KeyEventDetails* const details)
{
    Inherited::keyPressed(details);
}

void SceneEditingViewport::keyTyped(KeyEventDetails* const details)
{
    switch(details->getKey())
    {
        case KeyEventDetails::KEY_F:
            focusSelectedNodes();
            break;
        case KeyEventDetails::KEY_T:
            dynamic_cast<ApplicationBuilder*>(MainApplication::the()->getBuilderMode())->getMainWindow()->getSceneViewportToolbar()->setTranslationEditing(true);
            break;
        case KeyEventDetails::KEY_S:
            dynamic_cast<ApplicationBuilder*>(MainApplication::the()->getBuilderMode())->getMainWindow()->getSceneViewportToolbar()->setScaleEditing(true);
            break;
        case KeyEventDetails::KEY_R:
            dynamic_cast<ApplicationBuilder*>(MainApplication::the()->getBuilderMode())->getMainWindow()->getSceneViewportToolbar()->setRotationEditing(true);
            break;
        case KeyEventDetails::KEY_ESCAPE:
            if( _XFormManipMgr.isManipulating() )
            {
                _XFormManipMgr.cancelManip();
            }
            break;
    }

    Inherited::keyTyped(details);
}

void SceneEditingViewport::focusSelectedNodes(void)
{
    std::vector<Node* const> NodesToShow;
    for(UInt32 i(0) ; i<getMFSelectedNodes()->size() ; ++i)
    {
        NodesToShow.push_back(getSelectedNodes(i));
    }

    if(NodesToShow.empty())
    {
        return;
    }

    Matrix NewCamBeaconMatrix;
    for(UInt32 i(0) ; i<getMFEditorOverlayViewports()->size() ; ++i)
    {
        calcCameraShowAll(getEditorOverlayViewports(i)->getCamera(), getEditorOverlayViewports(i)->getPort(), NodesToShow,NewCamBeaconMatrix);
        //getEditorOverlayViewports(i)->set(NewCamBeaconMatrix);
        animateCameraBeacon(i, NewCamBeaconMatrix);
    }
}

void SceneEditingViewport::focusNode(Node* TheNode)
{
    std::vector<Node* const> NodesToShow;
    NodesToShow.push_back(TheNode);

    Matrix NewCamBeaconMatrix;
    for(UInt32 i(0) ; i<getMFEditorOverlayViewports()->size() ; ++i)
    {
        calcCameraShowAll(getEditorOverlayViewports(i)->getCamera(), getEditorOverlayViewports(i)->getPort(), NodesToShow,NewCamBeaconMatrix);
        //getEditorOverlayViewports(i)->set(NewCamBeaconMatrix);
        animateCameraBeacon(i, NewCamBeaconMatrix);
    }
}

void SceneEditingViewport::animateCameraBeacon(UInt32 Index, const Matrix& NewCamBeaconMatrix)
{
    if(getEditorOverlayViewports(Index)->getCamera() !=NULL)
    {
        TransformRecPtr BeaconTransform = dynamic_cast<Transform*>(getEditorOverlayViewports(Index)->getCamera()->getBeacon()->getCore());
        _CameraAnimationGroups[Index]->stop();

        //Update The Camera Animation Values
        _CameraTransformationKeyframes[Index]->clear();
        _CameraTransformationKeyframes[Index]->addKeyframe(BeaconTransform->getMatrix(),0.0f);
        _CameraTransformationKeyframes[Index]->addKeyframe(NewCamBeaconMatrix,1.0f);

        //Attach the Debug Camera Animation
        _CameraTransAnimations[Index]->setAnimatedField(BeaconTransform,
                                                Transform::MatrixFieldId);

        //_CameraFovAnimation->setAnimatedField(_Camera,
        //PerspectiveCamera::FovFieldId);

        _CameraAnimationGroups[Index]->attachUpdateProducer(MainApplication::the()->getMainWindow());

        //Start the Animation
        _CameraAnimationGroups[Index]->start();

        _CameraAnimConnections[Index] = _CameraAnimationGroups[Index]->connectAnimationEnded(boost::bind(&SceneEditingViewport::handleCameraAnimationEnded, this, _1, Index, NewCamBeaconMatrix));
    }
}

void SceneEditingViewport::setStatisticsEnabled(bool enable)
{
    _EnableStatistics = enable;
    for(UInt32 i(0) ; i<getMFEditorOverlayViewports()->size() ; ++i)
    {
        getEditorOverlayViewports(i)->getPort()->getForegrounds(0)->setActive(_EnableStatistics);
    }
}

bool SceneEditingViewport::getStatisticsEnabled(void) const
{
    return _EnableStatistics;
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

void SceneEditingViewport::drawInternal(Graphics* const TheGraphics, Real32 Opacity) const
{
    const_cast<SceneEditingViewport*>(this)->updateHighlightNode();
    Inherited::drawInternal(TheGraphics, Opacity);
}

void SceneEditingViewport::handleCameraAnimationEnded(AnimationEventDetails* const details,
                                                      UInt32 Index,
                                                      const Matrix& FinalCameraTransform)
{
    //Set The Navigator
    getEditorOverlayViewports(Index)->set(FinalCameraTransform);

    _CameraAnimConnections[Index].disconnect();
}

SimpleStatisticsForegroundTransitPtr SceneEditingViewport::createStatisticsForeground(void)
{
    Color4f StatColor(0.9f,0.9f,0.9f,0.8f),
            StatShadowColor(0.0f,0.0f,0.0f,0.8f),
            StatBorderColor(0.9f,0.9f,0.9f,0.8f),
            StatBackgroundColor(0.0f,0.0f,0.0f,0.7f);
    UInt32 StatFontSize(25);

    SimpleStatisticsForegroundRecPtr BasicStatForeground = SimpleStatisticsForeground::create();
    BasicStatForeground->setHorizontalAlign(SimpleStatisticsForeground::Right);
    BasicStatForeground->setVerticalAlign(SimpleStatisticsForeground::Top);
    BasicStatForeground->setSize(StatFontSize);
    BasicStatForeground->setColor(StatColor);
    BasicStatForeground->setShadowColor(StatShadowColor);
    BasicStatForeground->setBgColor(StatBackgroundColor);
    BasicStatForeground->setBorderColor(StatBorderColor);
    BasicStatForeground->addElement(RenderAction::statNTriangles, "Triangles: %d");
    BasicStatForeground->getCollector()->getElem(RenderAction::statNTriangles, true);
    BasicStatForeground->addElement(RenderAction::statNGeometries, "Geometry Nodes: %d");
    BasicStatForeground->getCollector()->getElem(RenderAction::statNGeometries, true);
    BasicStatForeground->addElement(RenderAction::statNStates, "Material changes: %d");
    BasicStatForeground->getCollector()->getElem(RenderAction::statNStates, true);
    BasicStatForeground->addElement(TextureObjChunk::statNTextures, "Textures: %d");
    BasicStatForeground->getCollector()->getElem(TextureObjChunk::statNTextures, true);

    return SimpleStatisticsForegroundTransitPtr(BasicStatForeground);
}

void SceneEditingViewport::attachScene(Scene* const TheScene)
{
    dettachScene();

    if(TheScene != NULL)
    {
        UInt32 NumViewports(TheScene->getMFViewports()->size());

        //Resize the number of GLViewports
        while(getMFSceneViewports()->size() < NumViewports)
        {
            GLViewportRecPtr NewOverlayViewportComp = GLViewport::create();
            NewOverlayViewportComp->setMode(Navigator::NAVBALL);
            pushToEditorOverlayViewports(NewOverlayViewportComp);

            GLViewportRecPtr NewViewportComp = GLViewport::create();
            NewViewportComp->setCamera(NewOverlayViewportComp->getCamera());
            NewViewportComp->setMode(Navigator::NONE);
            pushToSceneViewports(NewViewportComp);
        }

        while(getMFSceneViewports()->size() > NumViewports)
        {
            removeFromSceneViewports(getMFSceneViewports()->size()-1);
            removeFromEditorOverlayViewports(getMFSceneViewports()->size()-1);
            _CameraTransformationKeyframes.pop_back();
            _CameraTransAnimations.pop_back();
            _CameraAnimationGroups.pop_back();
        }

        //Attach to the scenes viewports
        for(UInt32 i(0) ; i<NumViewports ; ++i)
        {
            getSceneViewports(i)->setPort(TheScene->getViewports(i));

            if(getEditorOverlayViewports(i)->getPort() == NULL)
            {
                ViewportUnrecPtr OverlayViewport = createOverlayViewport(getSceneViewports(i));
                getEditorOverlayViewports(i)->setPort(OverlayViewport);
                _XFormManipMgr.setViewport(getEditorOverlayViewports(i)->getDrawingViewport());
            }

            getEditorOverlayViewports(i)->getPort()->setCamera(getSceneViewports(i)->getPort()->getCamera());

            _OverlayLight->setBeacon(getEditorOverlayViewports(i)->getDrawingViewport()->getCamera()->getBeacon());
            _CameraNodeCore->setTarget(TheScene->getViewports(i)->getCamera()->getBeacon());
            commitChanges();
            
            std::vector<Node* const> NodesToShow;
            NodesToShow.push_back(getSceneViewports(i)->getPort()->getRoot());
            Matrix NewCamBeaconMatrix;
            calcCameraShowAll(getEditorOverlayViewports(i)->getCamera(), getEditorOverlayViewports(i)->getPort(), NodesToShow,NewCamBeaconMatrix);
            getEditorOverlayViewports(i)->set(NewCamBeaconMatrix);

            Vec3f min,max;
            BoxVolume TheVol;
            getSceneViewports(i)->getPort()->getRoot()->getWorldVolume(TheVol);
            TheVol.getBounds( min, max );

            Vec3f d = max - min;
            if(d.length() < Eps) //The volume is 0
            {
                Pnt3f NodeOrigin(0.0f,0.0f,0.0f);
                getSceneViewports(i)->getPort()->getRoot()->getToWorld().mult(NodeOrigin, NodeOrigin);
                //Default to a 1x1x1 box volume
                min = Vec3f(NodeOrigin) - Vec3f(1.0f,1.0f,1.0f);
                max = Vec3f(NodeOrigin) + Vec3f(1.0f,1.0f,1.0f);
                d = max - min;
            }
            getEditorOverlayViewports(i)->setMotionFactor((d[0] + d[1] + d[2]) / 100.f);
            getEditorOverlayViewports(i)->getRenderAction()->setFrustumCulling(false);
        }

        //Attach the viewports as children
        clearChildren();
        for(UInt32 i(0) ; i<NumViewports ; ++i)
        {
            pushToChildren(getSceneViewports(i));
            pushToChildren(getEditorOverlayViewports(i));
        }
    }
}

void SceneEditingViewport::dettachScene(void)
{
}

void SceneEditingViewport::createCameraNode(void)
{
    BoostPath CameraModelPath(MainApplication::the()->getSettings().get<BoostPath>("builder.ui.visual_annotations.camera.path"));

    if(!CameraModelPath.is_complete())
    {
        CameraModelPath = MainApplication::the()->getSettings().get<BoostPath>("basic.data.directory") / CameraModelPath;
    }
    
    NodeRecPtr CameraGeometryNode = SceneFileHandler::the()->read(CameraModelPath.string().c_str());

    _CameraNodeCore = ReplicateTransform::create();

    _CameraNode = makeNodeFor(_CameraNodeCore);
    _CameraNode->addChild(CameraGeometryNode);
}

ViewportTransitPtr SceneEditingViewport::createOverlayViewport(GLViewport* const MainViewportComponent)
{
    _WorkspaceGridLineChunk = LineChunk::create();
    _WorkspaceGridLineChunk->setWidth(1.0f);
    _WorkspaceGridLineChunk->setSmooth(true);

    BlendChunkRefPtr TheBlendChunk = BlendChunk::create();
    TheBlendChunk->setSrcFactor(GL_SRC_ALPHA);
    TheBlendChunk->setDestFactor(GL_ONE_MINUS_SRC_ALPHA);

    ChunkMaterialRefPtr WorkspaceGridMaterial = ChunkMaterial::create();
    WorkspaceGridMaterial->addChunk (TheBlendChunk);
    WorkspaceGridMaterial->addChunk (_WorkspaceGridLineChunk);

    MaterialGroupRefPtr GridMatGroup = MaterialGroup::create();
    GridMatGroup->setMaterial(WorkspaceGridMaterial);

    //Create the Workspace Grid
    _WorkspaceGrid = Node::create();

    _WorkspaceGrid->setCore(GridMatGroup);
    _WorkspaceGrid->addChild(makeGrid(100.0f, 100.0f, 1.0, Color3f(0.7f,0.7f,0.7f)));

    //Create the Highlight Node
    createHighlightNode();

    //Create the XFormManipulator Node
    createXFormManipulator();

    //Camera Node
    createCameraNode();

    //Create the Light
    _OverlayLight = DirectionalLight::create();

    //Debug Root Node
    NodeRefPtr DefaultRootNode = Node::create();
    DefaultRootNode->setCore(_OverlayLight);

    //bDefaultRootNode->addChild(_CameraBeacon);
    DefaultRootNode->addChild(_HighlightNode);
    DefaultRootNode->addChild(_XFormManipNode);
    DefaultRootNode->addChild(_WorkspaceGrid);
    DefaultRootNode->addChild(_CameraNode);

    //Background
    PassiveBackgroundRefPtr DefaultBackground = PassiveBackground::create();

    //Render Options
    RenderOptionsRecPtr DebugViewportRenderOptions = RenderOptions::create();
    DebugViewportRenderOptions->setFrustumCulling(false);

    ViewportRefPtr DebugViewport = Viewport::create();

    SimpleStatisticsForegroundRecPtr BasicStatistics = createStatisticsForeground();
    MainViewportComponent->getRenderAction()->setStatCollector(BasicStatistics->getCollector());
    BasicStatistics->setActive(_EnableStatistics);

    DebugViewport->setRoot      (DefaultRootNode);
    DebugViewport->setSize      (0.0f,0.0f, 1.0f,1.0f);
    DebugViewport->setBackground(DefaultBackground);
    DebugViewport->setTravMask  (DEBUG_GRAPH_DRAWN);
    DebugViewport->setRenderOptions(DebugViewportRenderOptions);
    DebugViewport->addForeground(BasicStatistics);

    //Setup the XForm Manipulation Manager
    _XFormManipMgr.setTarget(NULL);

    //Transformation Animation
    KeyframeTransformationSequenceMatrix4fRecPtr Seq = KeyframeTransformationSequenceMatrix4f::create();
    _CameraTransformationKeyframes.push_back(Seq);

    KeyframeAnimatorRefPtr DebugCameraTransformationAnimator = KeyframeAnimator::create();
    DebugCameraTransformationAnimator->setKeyframeSequence(_CameraTransformationKeyframes.back());

    FieldAnimationRecPtr Anim = FieldAnimation::create();
    _CameraTransAnimations.push_back(Anim);
    _CameraTransAnimations.back()->setAnimator(DebugCameraTransformationAnimator);
    _CameraTransAnimations.back()->setInterpolationType(Animator::LINEAR_INTERPOLATION);
    _CameraTransAnimations.back()->setCycling(1);

    //Animation Group
    AnimationGroupRecPtr AnimGroup = AnimationGroup::create();
    _CameraAnimationGroups.push_back(AnimGroup);
    _CameraAnimationGroups.back()->setCycling(1);
    _CameraAnimationGroups.back()->pushToAnimations(_CameraTransAnimations.back());

    return ViewportTransitPtr(DebugViewport);
}

void SceneEditingViewport::updateWireframeNode(void)
{
    NodeUnrecPtr SelectedNode = NULL;
    if(getMFSelectedNodes()->size() > 0)
    {
        SelectedNode = getMFSelectedNodes()->front();
    }

    //visit the sub-tree rooted at the selected node
    if(SelectedNode != NULL)
    {
        dynamic_cast<VisitSubTree*>(_WireframeMatGroupNode->getChild(0)->getCore())->setSubTreeRoot(SelectedNode);

        //Use the traversal mask that the viewport this node is in is using
        //dynamic_cast<VisitSubTree*>(_WireframeMatGroupNode->getChild(0)->getCore())->setSubTreeTravMask(dynamic_cast<ApplicationBuilder*>(MainApplication::the()->getBuilderMode())->getSelectedScene()->getPrimaryViewport()->getTravMask());

    }

    //Update the transformation for the wireframe node
    if(SelectedNode != NULL &&
       SelectedNode->getParent() != NULL)
    {
        _WireframeTransform->setTarget(SelectedNode->getParent());
    }
    else
    {
        _WireframeTransform->setTarget(NULL);
    }
}

void SceneEditingViewport::updateHighlightNode(void)
{
    if(_HighlightNode == NULL)
    {
        return;
    }

    if(getMFSelectedNodes()->size() == 0)
    {
        _HighlightNode->setTravMask(DEBUG_GRAPH_NONE);
        return;
    }

    NodeUnrecPtr SelectedNode(getMFSelectedNodes()->front());

    _HighlightNode->setTravMask(DEBUG_GRAPH_DRAWN);

    // calc the world bbox of the highlight object
    BoxVolume      vol;
    SelectedNode->getWorldVolume(vol);

    Pnt3f min,max;
    vol.getBounds(min, max);

    //Get The Local Coordinate System
    Matrix NodeMatrix = SelectedNode->getToWorld();
    Pnt3f NodeOrigin(NodeMatrix * Pnt3f(0.0f,0.0f,0.0f));
    Vec3f NodeXDir(NodeMatrix * Vec3f(1.0f,0.0f,0.0f)),
          NodeYDir(NodeMatrix * Vec3f(0.0f,1.0f,0.0f)),
          NodeZDir(NodeMatrix * Vec3f(0.0f,0.0f,1.0f));

    //If the Volume is Zero, use a volume of size 1.0
    if(min == max)
    {
        min = NodeOrigin - Vec3f(0.5f,0.5f,0.5f);
        max = NodeOrigin + Vec3f(0.5f,0.5f,0.5f);
    }

    //Get the side lengths of the volume
    Vec3f  Sides(max - min);

    GeoPnt3fPropertyRecPtr temphighlightPoints =
        static_cast<GeoPnt3fProperty*>(_HighlightVolumeBoxGeo->getPositions());

    //Update Bounding Box
    temphighlightPoints->setValue(Pnt3f(min[0], min[1], min[2]), 0);
    temphighlightPoints->setValue(Pnt3f(max[0], min[1], min[2]), 1);
    temphighlightPoints->setValue(Pnt3f(min[0], max[1], min[2]), 2);
    temphighlightPoints->setValue(Pnt3f(max[0], max[1], min[2]), 3);
    temphighlightPoints->setValue(Pnt3f(min[0], min[1], max[2]), 4);
    temphighlightPoints->setValue(Pnt3f(max[0], min[1], max[2]), 5);
    temphighlightPoints->setValue(Pnt3f(min[0], max[1], max[2]), 6);
    temphighlightPoints->setValue(Pnt3f(max[0], max[1], max[2]), 7);
    
    temphighlightPoints =
        static_cast<GeoPnt3fProperty*>(_HighlightAxisGeo->getPositions());

    //Update Local Coordinate Axis
    Real32 AxisScaling(Sides.maxValue() * MainApplication::the()->getSettings().get<Real32>("player.debugger.selected_node.axis.relative_length"));
    temphighlightPoints->setValue(NodeOrigin, 0);
    temphighlightPoints->setValue(NodeOrigin + (NodeXDir* AxisScaling), 1);
    temphighlightPoints->setValue(NodeOrigin, 2);
    temphighlightPoints->setValue(NodeOrigin + (NodeYDir* AxisScaling), 3);
    temphighlightPoints->setValue(NodeOrigin, 4);
    temphighlightPoints->setValue(NodeOrigin + (NodeZDir* AxisScaling), 5);
}

void SceneEditingViewport::createXFormManipulator(void)
{
    _XFormManipMgr.setUniformScale(true);
    _XFormManipMgr.setManipulatorScreenDepth(8.0f);


    //X Form root node
    _XFormManipNode = makeCoredNode<Group>();
    _XFormManipNode->addChild(_XFormManipMgr.createManipulator(ManipulatorManager::TRANSLATE));
    _XFormManipNode->setTravMask(DEBUG_GRAPH_NONE);
}

void SceneEditingViewport::createHighlightNode(void)
{
    createHighlightBoundBoxNode();
    createHighlightAxisNode();
    createHighlightTriMeshNode();

    //Highlight Node
    _HighlightNode = Node::create();

    GroupRecPtr HighlightCore = Group::create();
    _HighlightNode->setCore(HighlightCore);
    _HighlightNode->addChild(_HighlightVolumeBoxNode);
    _HighlightNode->addChild(_HighlightAxisNode);
    _HighlightNode->addChild(_WireframeNode);

    //Update from settings
    //updateFromSettings();
}

void SceneEditingViewport::createHighlightBoundBoxNode(void)
{
    //Create the Material for the Highlight
    _HighlightBoundBoxMatLineChunk = LineChunk::create();
    _HighlightBoundBoxMatLineChunk->setWidth(2.0f);
    _HighlightBoundBoxMatLineChunk->setSmooth(true);

    BlendChunkRefPtr TheBlendChunk = BlendChunk::create();
    TheBlendChunk->setSrcFactor(GL_SRC_ALPHA);
    TheBlendChunk->setDestFactor(GL_ONE_MINUS_SRC_ALPHA);

    ChunkMaterialRefPtr FrontHighlightMaterial = ChunkMaterial::create();
    FrontHighlightMaterial->addChunk (TheBlendChunk);
    FrontHighlightMaterial->addChunk (_HighlightBoundBoxMatLineChunk);

    DepthChunkRecPtr BackDepthChunk = DepthChunk::create();

    BackDepthChunk->setEnable(true);
    BackDepthChunk->setFunc(GL_GREATER);
    BackDepthChunk->setReadOnly(true);

    MaterialChunkRecPtr BackWireframeMatMaterialChunk = MaterialChunk::create();
    BackWireframeMatMaterialChunk->setAmbient (Color4f(0.0f,0.0f,0.0f,0.25f));
    BackWireframeMatMaterialChunk->setDiffuse (Color4f(0.0f,0.0f,0.0f,0.25f));
    BackWireframeMatMaterialChunk->setSpecular(Color4f(0.0f,0.0f,0.0f,0.25f));
    BackWireframeMatMaterialChunk->setEmission(Color4f(1.0f,1.0f,1.0f,0.25f));
    BackWireframeMatMaterialChunk->setColorMaterial(GL_EMISSION);
    BackWireframeMatMaterialChunk->setLit(true);

    ChunkMaterialRefPtr BackHighlightMaterial = ChunkMaterial::create();
    BackHighlightMaterial->addChunk (TheBlendChunk);
    BackHighlightMaterial->addChunk (_HighlightBoundBoxMatLineChunk);
    BackHighlightMaterial->addChunk (BackWireframeMatMaterialChunk);
    BackHighlightMaterial->addChunk (BackDepthChunk);

    
    MultiPassMaterialRefPtr HighlightMaterial = MultiPassMaterial::create();
    HighlightMaterial->addMaterial(FrontHighlightMaterial);
    HighlightMaterial->addMaterial(BackHighlightMaterial);

    //Create the Geometry for the highlight
    GeoUInt8PropertyRecPtr type = GeoUInt8Property::create();
    //Volume bound box
    type->push_back(GL_LINE_STRIP);
    type->push_back(GL_LINES);

    GeoUInt32PropertyRefPtr lens = GeoUInt32Property::create();
    //Volume bound box
    lens->push_back(10);
    lens->push_back(6);

    GeoUInt32PropertyRefPtr index = GeoUInt32Property::create();

    //Volume bound box
    index->push_back(0);
    index->push_back(1);
    index->push_back(3);
    index->push_back(2);
    index->push_back(0);
    index->push_back(4);
    index->push_back(5);
    index->push_back(7);
    index->push_back(6);
    index->push_back(4);

    index->push_back(1);
    index->push_back(5);
    index->push_back(2);
    index->push_back(6);
    index->push_back(3);
    index->push_back(7);

    GeoPnt3fPropertyRefPtr highlightPoints = GeoPnt3fProperty::create();
    //Volume bound box
    highlightPoints->push_back(Pnt3f(-1, -1, -1));
    highlightPoints->push_back(Pnt3f( 1, -1, -1));
    highlightPoints->push_back(Pnt3f(-1,  1, -1));
    highlightPoints->push_back(Pnt3f( 1,  1, -1));
    highlightPoints->push_back(Pnt3f(-1, -1,  1));
    highlightPoints->push_back(Pnt3f( 1, -1,  1));
    highlightPoints->push_back(Pnt3f(-1,  1,  1));
    highlightPoints->push_back(Pnt3f( 1,  1,  1));

    //Colors
    Color4f BoundBoxColor(0.0f,1.0f,1.0,1.0f);

    GeoVec4fPropertyRefPtr highlightColors = GeoVec4fProperty::create();
    //Volume bound box
    highlightColors->push_back(BoundBoxColor);
    highlightColors->push_back(BoundBoxColor);
    highlightColors->push_back(BoundBoxColor);
    highlightColors->push_back(BoundBoxColor);
    highlightColors->push_back(BoundBoxColor);
    highlightColors->push_back(BoundBoxColor);
    highlightColors->push_back(BoundBoxColor);
    highlightColors->push_back(BoundBoxColor);

    _HighlightVolumeBoxGeo =Geometry::create();
    _HighlightVolumeBoxGeo->setTypes     (type);
    _HighlightVolumeBoxGeo->setLengths   (lens);
    _HighlightVolumeBoxGeo->setIndices   (index);
    _HighlightVolumeBoxGeo->setPositions (highlightPoints);
    _HighlightVolumeBoxGeo->setColors    (highlightColors);
    _HighlightVolumeBoxGeo->setMaterial  (HighlightMaterial);

    //Highlight Bound Box Node
    _HighlightVolumeBoxNode = Node::create();

    _HighlightVolumeBoxNode->setCore(_HighlightVolumeBoxGeo);
}

void SceneEditingViewport::createHighlightAxisNode(void)
{
    //Create the Material for the Highlight
    _HighlightAxisLineChunk = LineChunk::create();
    _HighlightAxisLineChunk->setWidth(2.0f);
    _HighlightAxisLineChunk->setSmooth(true);

    BlendChunkRefPtr TheBlendChunk = BlendChunk::create();
    TheBlendChunk->setSrcFactor(GL_SRC_ALPHA);
    TheBlendChunk->setDestFactor(GL_ONE_MINUS_SRC_ALPHA);

    ChunkMaterialRefPtr FrontHighlightMaterial = ChunkMaterial::create();
    FrontHighlightMaterial->addChunk (TheBlendChunk);
    FrontHighlightMaterial->addChunk (_HighlightAxisLineChunk);

    DepthChunkRecPtr BackDepthChunk = DepthChunk::create();

    BackDepthChunk->setEnable(true);
    BackDepthChunk->setFunc(GL_GREATER);
    BackDepthChunk->setReadOnly(true);

    MaterialChunkRecPtr BackHighlightMaterialChunk = MaterialChunk::create();
    BackHighlightMaterialChunk->setAmbient (Color4f(0.0f,0.0f,0.0f,0.25f));
    BackHighlightMaterialChunk->setDiffuse (Color4f(0.0f,0.0f,0.0f,0.25f));
    BackHighlightMaterialChunk->setSpecular(Color4f(0.0f,0.0f,0.0f,0.25f));
    BackHighlightMaterialChunk->setEmission(Color4f(1.0f,1.0f,1.0f,0.25f));
    BackHighlightMaterialChunk->setColorMaterial(GL_EMISSION);
    BackHighlightMaterialChunk->setLit(true);

    ChunkMaterialRefPtr BackHighlightMaterial = ChunkMaterial::create();
    BackHighlightMaterial->addChunk (TheBlendChunk);
    BackHighlightMaterial->addChunk (_HighlightAxisLineChunk);
    BackHighlightMaterial->addChunk (BackHighlightMaterialChunk);
    BackHighlightMaterial->addChunk (BackDepthChunk);

    
    MultiPassMaterialRefPtr HighlightMaterial = MultiPassMaterial::create();
    HighlightMaterial->addMaterial(FrontHighlightMaterial);
    HighlightMaterial->addMaterial(BackHighlightMaterial);

    //Create the Geometry for the highlight
    GeoUInt8PropertyRecPtr type = GeoUInt8Property::create();
    //Local Coordinage axis
    type->push_back(GL_LINES);

    GeoUInt32PropertyRefPtr lens = GeoUInt32Property::create();
    //Local Coordinage axis
    lens->push_back(6);

    GeoUInt32PropertyRefPtr index = GeoUInt32Property::create();

    //Local Coordinage axis
    index->push_back(0);
    index->push_back(1);
    index->push_back(2);
    index->push_back(3);
    index->push_back(4);
    index->push_back(5);

    GeoPnt3fPropertyRefPtr highlightPoints = GeoPnt3fProperty::create();

    //Local Coordinage axis
    highlightPoints->push_back(Pnt3f( 0,  0,  0));
    highlightPoints->push_back(Pnt3f( 1,  0,  0));
    highlightPoints->push_back(Pnt3f( 0,  0,  0));
    highlightPoints->push_back(Pnt3f( 0,  1,  0));
    highlightPoints->push_back(Pnt3f( 0,  0,  0));
    highlightPoints->push_back(Pnt3f( 0,  0,  1));

    //Colors
    Color4f XAxisColor   (1.0f,0.0f,0.0,1.0f);
    Color4f YAxisColor   (0.0f,1.0f,0.0,1.0f);
    Color4f ZAxisColor   (0.0f,0.0f,1.0,1.0f);

    GeoVec4fPropertyRefPtr highlightColors = GeoVec4fProperty::create();

    //Local Coordinage axis
    highlightColors->push_back(XAxisColor);
    highlightColors->push_back(XAxisColor);
    highlightColors->push_back(YAxisColor);
    highlightColors->push_back(YAxisColor);
    highlightColors->push_back(ZAxisColor);
    highlightColors->push_back(ZAxisColor);

    _HighlightAxisGeo =Geometry::create();
    _HighlightAxisGeo->setTypes     (type);
    _HighlightAxisGeo->setLengths   (lens);
    _HighlightAxisGeo->setIndices   (index);
    _HighlightAxisGeo->setPositions (highlightPoints);
    _HighlightAxisGeo->setColors    (highlightColors);
    _HighlightAxisGeo->setMaterial  (HighlightMaterial);

    //Highlight Bound Box Node
    _HighlightAxisNode = Node::create();


    _HighlightAxisNode->setCore(_HighlightAxisGeo);
}

void SceneEditingViewport::createHighlightTriMeshNode(void)
{

    //Create the VisitSubTree Node to use to render the wireframe of the
    //selected node
    VisitSubTreeRefPtr SelectedSubTree = VisitSubTree::create();

    NodeRefPtr SelectedSubTreeNode = Node::create();
    SelectedSubTreeNode->setCore(SelectedSubTree);
    

    //Front Pass
    DepthChunkRecPtr FrontDepthChunk = DepthChunk::create();
    FrontDepthChunk->setEnable(true);
    FrontDepthChunk->setFunc(GL_LEQUAL);

    //Create the Material for the Mesh Highlight
    _WireframeMatLineChunk = LineChunk::create();
    _WireframeMatLineChunk->setWidth(1.0f);
    _WireframeMatLineChunk->setSmooth(true);

    BlendChunkRefPtr TheBlendChunk = BlendChunk::create();
    TheBlendChunk->setSrcFactor(GL_SRC_ALPHA);
    TheBlendChunk->setDestFactor(GL_ONE_MINUS_SRC_ALPHA);

    PolygonChunkRefPtr WireframeMatPolygonChunk = PolygonChunk::create();
    WireframeMatPolygonChunk->setCullFace(GL_BACK);
    WireframeMatPolygonChunk->setFrontMode(GL_LINE);
    WireframeMatPolygonChunk->setBackMode(GL_LINE);
    WireframeMatPolygonChunk->setOffsetFactor(1.0f);
    WireframeMatPolygonChunk->setOffsetBias(0.01f);
    WireframeMatPolygonChunk->setOffsetFill(true);

    Color4f WireframeColor(1.0f,0.0f,1.0f,1.0f);
    _WireframeMatMaterialChunk = MaterialChunk::create();
    _WireframeMatMaterialChunk->setAmbient (Color4f(0.0f,0.0f,0.0f,1.0f));
    _WireframeMatMaterialChunk->setDiffuse (Color4f(0.0f,0.0f,0.0f,1.0f));
    _WireframeMatMaterialChunk->setSpecular(Color4f(0.0f,0.0f,0.0f,1.0f));
    _WireframeMatMaterialChunk->setEmission(WireframeColor);
    _WireframeMatMaterialChunk->setLit(true);

    ChunkMaterialRefPtr FrontWireframeMaterial = ChunkMaterial::create();
    FrontWireframeMaterial->addChunk (TheBlendChunk);
    FrontWireframeMaterial->addChunk (WireframeMatPolygonChunk);
    FrontWireframeMaterial->addChunk (_WireframeMatMaterialChunk);
    FrontWireframeMaterial->addChunk (_WireframeMatLineChunk);
    FrontWireframeMaterial->addChunk (FrontDepthChunk);

    //Behind Pass
    DepthChunkRecPtr BackDepthChunk = DepthChunk::create();
    BackDepthChunk->setEnable(true);
    BackDepthChunk->setFunc(GL_GREATER);
    BackDepthChunk->setReadOnly(true);

    Color4f BackWireframeColor(1.0f,0.0f,1.0f,0.15f);
    MaterialChunkRecPtr _BackWireframeMatMaterialChunk = MaterialChunk::create();
    _BackWireframeMatMaterialChunk->setAmbient (Color4f(0.0f,0.0f,0.0f,0.15f));
    _BackWireframeMatMaterialChunk->setDiffuse (Color4f(0.0f,0.0f,0.0f,0.15f));
    _BackWireframeMatMaterialChunk->setSpecular(Color4f(0.0f,0.0f,0.0f,0.15f));
    _BackWireframeMatMaterialChunk->setEmission(BackWireframeColor);
    _BackWireframeMatMaterialChunk->setLit(true);

    ChunkMaterialRefPtr BackWireframeMaterial = ChunkMaterial::create();
    BackWireframeMaterial->addChunk (TheBlendChunk);
    BackWireframeMaterial->addChunk (WireframeMatPolygonChunk);
    BackWireframeMaterial->addChunk (_BackWireframeMatMaterialChunk);
    BackWireframeMaterial->addChunk (_WireframeMatLineChunk);
    BackWireframeMaterial->addChunk (BackDepthChunk);

    
    MultiPassMaterialRefPtr WireframeMaterial = MultiPassMaterial::create();
    WireframeMaterial->addMaterial(FrontWireframeMaterial);
    WireframeMaterial->addMaterial(BackWireframeMaterial);

    //MaterialGroup
    MaterialGroupRefPtr WireframeMaterialGroup = MaterialGroup::create(); 
    WireframeMaterialGroup->setMaterial(WireframeMaterial);

    //Mesh Highlight Node
    _WireframeMatGroupNode = Node::create();

    _WireframeMatGroupNode->setCore(WireframeMaterialGroup);

    _WireframeMatGroupNode->addChild(SelectedSubTreeNode);

    //Mesh Highlight Transformation Node
    _WireframeTransform = ReplicateTransform::create();

    _WireframeNode = Node::create();

    _WireframeNode->setCore(_WireframeTransform);
    _WireframeNode->addChild(_WireframeMatGroupNode);
}

void SceneEditingViewport::updateXFormManipulator(void)
{
    NodeUnrecPtr SelectedNode = NULL;
    if(getMFSelectedNodes()->size() > 0)
    {
        SelectedNode = getMFSelectedNodes()->front();
    }

    Node* XFormTargetNode(NULL);
    if(SelectedNode != NULL)
    {
        if(SelectedNode->getCore()->getType().isDerivedFrom(Transform::getClassType()) || 
           SelectedNode->getCore()->getType().isDerivedFrom(StackedTransform::getClassType()))
        {
            XFormTargetNode = SelectedNode;
        }
        else if(SelectedNode->getParent() != NULL &&
                SelectedNode->getParent()->getNChildren() == 1 &&
                (SelectedNode->getParent()->getCore()->getType().isDerivedFrom(Transform::getClassType()) ||
                SelectedNode->getCore()->getType().isDerivedFrom(StackedTransform::getClassType())))
        {
            XFormTargetNode = SelectedNode->getParent();
        }
    }

    if(XFormTargetNode &&
       XFormTargetNode != _XFormManipMgr.getTarget())
    {
        // calc the world bbox of the highlight object
        BoxVolume      vol;
        XFormTargetNode->getWorldVolume(vol);

        Pnt3f min,max;
        vol.getBounds(min, max);

        //If the Volume is Zero, use a volume of size 1.0
        if(min == max)
        {
            min = Pnt3f(-0.5f,-0.5f,-0.5f);
            max = Pnt3f(0.5f,0.5f,0.5f);
        }

        //Get the side lengths of the volume
        Vec3f  Sides(max - min);
        Real32 AxisScaling(Sides.maxValue() *
                           MainApplication::the()->getSettings().get<Real32>("player.debugger.transform_manip.axis.relative_length"));

        _XFormManipMgr.setTarget(XFormTargetNode);
        _XFormManipNode->setTravMask(DEBUG_GRAPH_DRAWN | DEBUG_GRAPH_INTERSECTABLE);
        if(MainApplication::the()->getSettings().get<bool>("player.debugger.selected_node.axis.draw"))
        {
            _HighlightAxisNode->setTravMask(DEBUG_GRAPH_NONE);
        }
    }
    else
    {
        _XFormManipMgr.setTarget(NULL);
        _XFormManipNode->setTravMask(DEBUG_GRAPH_NONE);
        if(MainApplication::the()->getSettings().get<bool>("player.debugger.selected_node.axis.draw"))
        {
            _HighlightAxisNode->setTravMask(DEBUG_GRAPH_DRAWN);
        }
    }
}

void SceneEditingViewport::handleSceneEditorPanelMouseDragged(MouseEventDetails* const details)
{
    if( _XFormManipMgr.isManipulating() )
    {
        _XFormManipMgr.mouseMove(details->getX(), details->getY());
    }
}

void SceneEditingViewport::handleSceneEditorPanelMouseReleased(MouseEventDetails* const details)
{
    if(details->getButton() == MouseEventDetails::BUTTON1)
    {
        if(_XFormManipMgr.isManipulating() )
        {
            _XFormManipMgr.mouseButtonRelease(details->getButton(), details->getX(), details->getY());
            _XFormManipMgr.endManip();
            details->consume();


            Node* target(_XFormManipMgr.getTarget());
            if(target &&
               target->getCore())
            {
                AttachmentUnrecPtr Att = target->findAttachment(PhysicsBody::getClassType());
                if(Att!=NULL)
                {
                    PhysicsBodyUnrecPtr BodyAtt = dynamic_pointer_cast<PhysicsBody>(Att);

                    Matrix NodeTrans = target->getToWorld();
                    Vec3f Pos, Scale;
                    Quaternion Rot, ScaleOrient;
                    NodeTrans.getTransform(Pos,Rot,Scale,ScaleOrient);
                    BodyAtt->setPosition(Pos);
                    BodyAtt->setQuaternion(Rot);
                }
                if(target->getCore()->getType().isDerivedFrom(Transform::getClassType()))
                {
                    std::ostringstream initMatStrStream;
                    OutStream theinitMatOutStream(initMatStrStream);
                    FieldTraits<Matrix>::putToStream(_XFormManipMgr.getManipulator()->getInitialXForm(),theinitMatOutStream);


                    std::ostringstream matStrStream;
                    OutStream theOutStream(matStrStream);
                    dynamic_cast<Transform*>(target->getCore())->getField(Transform::MatrixFieldId)->pushValueToStream(theOutStream);

                    SetFieldValueCommandPtr SetCommand =
                        SetFieldValueCommand::create(target->getCore(),
                                                     Transform::MatrixFieldId,
                                                     matStrStream.str(),
                                                     initMatStrStream.str());

                    ApplicationBuilderUnrecPtr AppBuilder = dynamic_cast<ApplicationBuilder*>(MainApplication::the()->getBuilderMode());
                    AppBuilder->getCommandManager()->executeCommand(SetCommand);
                }
                else if(target->getCore()->getType().isDerivedFrom(StackedTransform::getClassType()))
                {
                    //Translate
                    //RotateX
                    //RotateY
                    //RotateZ
                    //Scale
                }
            }
        }
    }
    _SceneEditorPanelMouseDraggedConnection.disconnect();
    _SceneEditorPanelMouseReleasedConnection.disconnect();
}

/*----------------------- constructors & destructors ----------------------*/

SceneEditingViewport::SceneEditingViewport(void) :
    Inherited(),
        _EnableStatistics(false)
{
}

SceneEditingViewport::SceneEditingViewport(const SceneEditingViewport &source) :
    Inherited(source),
        _EnableStatistics(source._EnableStatistics)
{
}

SceneEditingViewport::~SceneEditingViewport(void)
{
}

/*----------------------------- class specific ----------------------------*/

void SceneEditingViewport::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);

    if(whichField & EditingSceneFieldMask)
    {
        attachScene(getEditingScene());
    }

    if((whichField & SelectedNodesFieldMask) && 
       _HighlightNode != NULL)
    {
        updateHighlightNode();
        updateWireframeNode();
        updateXFormManipulator();
    }
}

void SceneEditingViewport::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump SceneEditingViewport NI" << std::endl;
}

OSG_END_NAMESPACE
