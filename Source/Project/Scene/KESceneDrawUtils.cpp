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
#include "KESceneDrawUtils.h"

#include "KEScene.h"
#include <OpenSG/OSGTextureObjChunk.h>
#include <OpenSG/OSGWindow.h>
#include <OpenSG/OSGRenderAction.h>
#include <OpenSG/OSGNode.h>
#include <OpenSG/OSGMatrixCamera.h>
#include <OpenSG/OSGPassiveBackground.h>
#include <OpenSG/OSGGroup.h>
#include <OpenSG/OSGViewport.h>

#include <OpenSG/OSGFrameBufferObject.h>
#include <OpenSG/OSGTextureBuffer.h>
#include <OpenSG/OSGRenderBuffer.h>
#include <OpenSG/OSGSimpleStage.h>

OSG_USING_NAMESPACE

void renderSceneToTexture(Scene* const TheScene,
                          TextureObjChunk* const ColorTexture,
                          Window* const TheWindow,
                          RenderAction* TheRenderAction)
{
    //Create an FBO to render the Scene's Viewport(s) into
    
    FrameBufferObjectRecPtr SceneFBO         = FrameBufferObject::create();
    TextureBufferRecPtr     FBOTextureBuffer = TextureBuffer    ::create();
    RenderBufferRecPtr      FBODepthBuffer   = RenderBuffer     ::create();

    
    //Attache the Texture to the TexureBuffer
    FBOTextureBuffer->setTexture(ColorTexture);

    // add a depth attachment, otherwise there is no depth buffer when
    // rendering to the FBO
    FBODepthBuffer->setInternalFormat(GL_DEPTH_COMPONENT24);

    // make the fbo render to the texture
    SceneFBO->setColorAttachment(FBOTextureBuffer,   0);
    SceneFBO->setDepthAttachment(FBODepthBuffer   );
    SceneFBO->editMFDrawBuffers()->push_back(GL_COLOR_ATTACHMENT0_EXT);
    SceneFBO->setWidth (FBOTextureBuffer->getTexture()->getImage()->getWidth() );
    SceneFBO->setHeight(FBOTextureBuffer->getTexture()->getImage()->getHeight());

    
    /*
        Next we set up a Stage, which renders the subtree below it to its
        render target (the FBO from above).
    */
    
    SimpleStageRefPtr SceneStage     = SimpleStage::create();
    NodeRefPtr        SceneStageNode = makeNodeFor(SceneStage);

    ViewportRecPtr SceneViewport(TheScene->getPrimaryViewport());
    SceneStage->setRenderTarget(SceneFBO);
    SceneStage->setLeft(SceneViewport->getLeft());
    SceneStage->setRight(SceneViewport->getRight());
    SceneStage->setTop(SceneViewport->getTop());
    SceneStage->setBottom(SceneViewport->getBottom());
    SceneStage->setCamera(SceneViewport->getCamera());
    SceneStage->setBackground(SceneViewport->getBackground());

    for(UInt32 i(0) ; i<SceneViewport->getMFForegrounds()->size() ; ++i)
    {
        SceneStage->pushToForegrounds(SceneViewport->getForegrounds(i));
    }

    SceneStageNode->addChild(SceneViewport->getRoot());

    NodeRecPtr ThumbRootNode = makeCoredNode<Group>();
    ThumbRootNode->addChild(SceneStageNode);
    
    CameraRecPtr ThumbCamera = MatrixCamera::create();
    ThumbCamera->setBeacon(ThumbRootNode);

    BackgroundRecPtr ThumbBackground = PassiveBackground::create();

    //Create a dummy Viewport for attaching to the window
    ViewportRecPtr ThumbViewport = Viewport::create();
    ThumbViewport->setBackground(ThumbBackground);
    ThumbViewport->setRoot(ThumbRootNode);
    ThumbViewport->setCamera(ThumbCamera);

    //Get all of the original TravMasks of the Viewports on the window
    //Set all of the TravMasks of the Viewports on the window to 0
    std::vector<UInt32> OrigTravMasks;
    OrigTravMasks.reserve(TheWindow->getMFPort()->size());
    for(UInt32 i(0) ; i<TheWindow->getMFPort()->size() ; ++i)
    {
        OrigTravMasks.push_back(TheWindow->getPort(i)->getTravMask());

        TheWindow->getPort(i)->setTravMask(0);
    }

    //Attach the Viewport to the Window
    TheWindow->addPort(ThumbViewport);

    //Draw the window
    TheWindow->render(TheRenderAction);

    //Detach the Viewport from the Window
    TheWindow->subPortByObj(ThumbViewport);

    //Reset all of the original TravMasks of the Viewports on the window
    for(UInt32 i(0) ; i<TheWindow->getMFPort()->size() ; ++i)
    {
        TheWindow->getPort(i)->setTravMask(OrigTravMasks[i]);
    }
}

