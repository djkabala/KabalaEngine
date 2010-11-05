#include "KEUtils.h"
#include <boost/lexical_cast.hpp>

#include <OpenSG/OSGAttachmentContainer.h>
#include <OpenSG/OSGCamera.h>
#include <OpenSG/OSGPerspectiveCamera.h>
#include <OpenSG/OSGViewport.h>
#include <OpenSG/OSGNode.h>
#include <OpenSG/OSGNameAttachment.h>
#include <OpenSG/OSGMatrixUtility.h>

OSG_USING_NAMESPACE

bool attachName (AttachmentContainer* const AttContainer)
{
    // Get attachment pointer
    AttachmentRefPtr att = 
        AttContainer->findAttachment(Name::getClassType().getGroupId());

    if(att == NULL ||
       dynamic_pointer_cast<Name>(att) == NULL)
    {
        std::string DefaultName(AttContainer->getType().getCName()
                              + std::string(" ")
                              + boost::lexical_cast<std::string>(AttContainer->getId()));

        setName(AttContainer,DefaultName);

        return true;
    }
    else
    {
        return false;
    }
}

void recurseSetTravMask(Node* const RootNode, 
                        UInt32 TravMask)
{
    if(RootNode->getTravMask() != TravMask)
    {
        RootNode->setTravMask(TravMask);
    }

    for(UInt32 i(0) ; i<RootNode->getNChildren() ; ++i)
    {
        recurseSetTravMask(RootNode->getChild(i),TravMask);
    }
}

void recurseSetTravMasRecord(Node* const RootNode, 
                             UInt32 TravMask,
                             std::vector<std::pair<NodeRefPtr, UInt32> >& NodesChanged)
{
    if(RootNode->getTravMask() != TravMask)
    {
        NodesChanged.push_back(std::pair<NodeRefPtr, UInt32>(RootNode, RootNode->getTravMask()));
        RootNode->setTravMask(TravMask);
    }

    for(UInt32 i(0) ; i<RootNode->getNChildren() ; ++i)
    {
        recurseSetTravMasRecord(RootNode->getChild(i),TravMask, NodesChanged);
    }
}

void calcCameraShowAll(Camera* const LocalCamera,
                       Viewport* const LocalViewport,
                       const std::vector<Node* const>& NodesToShow,
                       Matrix& ResultCameraBeacon)
{
    PerspectiveCameraRefPtr ThePerspCamera;
    if(LocalCamera->getType() == PerspectiveCamera::getClassType())
    {
        ThePerspCamera = dynamic_cast<PerspectiveCamera*>(LocalCamera);
    }

    //Make sure the volume is up to date for the FocusNode
    for(UInt32 i(0) ; i<NodesToShow.size() ; ++i)
    {
        NodesToShow[i]->updateVolume();
    }

    //Get the Minimum and Maximum bounds of the volume
    Vec3f min,max;
    BoxVolume AllVolume, NodeVolume;
    AllVolume.setBoundsByCenterAndSize(Pnt3r(0.0f,0.0f,0.0f),Vec3f(0.0f,0.0f,0.0f));
    for(UInt32 i(0) ; i<NodesToShow.size() ; ++i)
    {
        NodesToShow[i]->getWorldVolume(NodeVolume);
        AllVolume.extendBy(NodeVolume);
    }

    AllVolume.getBounds( min, max );

    Vec3f d = max - min;
    if(d.length() < Eps) //The volume is 0
    {
        Pnt3f NodeOrigin(0.0f,0.0f,0.0f);
        Pnt3f AvgOrigin(0.0f,0.0f,0.0f);
        for(UInt32 i(0) ; i<NodesToShow.size() ; ++i)
        {
            NodesToShow[i]->getToWorld().mult(NodeOrigin, NodeOrigin);
            AvgOrigin = AvgOrigin + NodeOrigin.subZero();
        }
        AvgOrigin = AvgOrigin * (1.0f/static_cast<Real32>(NodesToShow.size()));

        //Default to a 1x1x1 box volume
        min = Vec3f(AvgOrigin) - Vec3f(1.0f,1.0f,1.0f);
        max = Vec3f(AvgOrigin) + Vec3f(1.0f,1.0f,1.0f);
        d = max - min;
    }

    // try to be nice to people giving degrees...
    Real32 VertFov(ThePerspCamera->getFov());
    if(VertFov > Pi)
    {
        VertFov = osgDegree2Rad(VertFov);
    }

    //Get the horizontal feild of view
    Real32 HorFov = 2.0f * osgATan(static_cast<Real32>(LocalViewport->getPixelWidth())
                                   /(static_cast<Real32>(LocalViewport->getPixelHeight())/osgTan(VertFov*0.5f)));

    Pnt3f at((min[0] + max[0]) * .5f,(min[1] + max[1]) * .5f,(min[2] + max[2]) * .5f);

    //Get the camera world transformation
    Matrix CameraToWorld(ThePerspCamera->getBeacon()->getToWorld());
    Matrix WorldToCamera(CameraToWorld);
    WorldToCamera.invert();

    //Get the 8 points of the bounding box in camera space
    Pnt3f p1(min),
          p2(max.x(), min.y(), min.z()),
          p3(max.x(), max.y(), min.z()),
          p4(max.x(), min.y(), max.z()),
          p5(min.x(), max.y(), min.z()),
          p6(min.x(), max.y(), max.z()),
          p7(min.x(), min.y(), max.z()),
          p8(max);

    p1 = WorldToCamera * p1;
    p2 = WorldToCamera * p2;
    p3 = WorldToCamera * p3;
    p4 = WorldToCamera * p4;
    p5 = WorldToCamera * p5;
    p6 = WorldToCamera * p6;
    p7 = WorldToCamera * p7;
    p8 = WorldToCamera * p8;

    //Get the min and max of the bounding volume relative camera space
    Vec3f BBMinCamera;
    Vec3f BBMaxCamera;
    BBMinCamera[0] = osgMin(p1.x(),
                     osgMin(p2.x(),
                     osgMin(p3.x(),
                     osgMin(p4.x(),
                     osgMin(p5.x(),
                     osgMin(p6.x(),
                     osgMin(p7.x(),p8.x())))))));

    BBMinCamera[1] = osgMin(p1.y(),
                     osgMin(p2.y(),
                     osgMin(p3.y(),
                     osgMin(p4.y(),
                     osgMin(p5.y(),
                     osgMin(p6.y(),
                     osgMin(p7.y(),p8.y())))))));

    BBMinCamera[2] = osgMin(p1.z(),
                     osgMin(p2.z(),
                     osgMin(p3.z(),
                     osgMin(p4.z(),
                     osgMin(p5.z(),
                     osgMin(p6.z(),
                     osgMin(p7.z(),p8.z())))))));

    BBMaxCamera[0] = osgMax(p1.x(),
                     osgMax(p2.x(),
                     osgMax(p3.x(),
                     osgMax(p4.x(),
                     osgMax(p5.x(),
                     osgMax(p6.x(),
                     osgMax(p7.x(),p8.x())))))));

    BBMaxCamera[1] = osgMax(p1.y(),
                     osgMax(p2.y(),
                     osgMax(p3.y(),
                     osgMax(p4.y(),
                     osgMax(p5.y(),
                     osgMax(p6.y(),
                     osgMax(p7.y(),p8.y())))))));

    BBMaxCamera[2] = osgMax(p1.z(),
                     osgMax(p2.z(),
                     osgMax(p3.z(),
                     osgMax(p4.z(),
                     osgMax(p5.z(),
                     osgMax(p6.z(),
                     osgMax(p7.z(),p8.z())))))));

    Pnt3f CamerAt(WorldToCamera * at);

    //Calculate the distance to move the camera back to make sure the bound
    //box is visible
    Real32 dist = 1.05f * ((BBMaxCamera.z()-CamerAt.z()) +
                          osgMax(((BBMaxCamera.y()-BBMinCamera.y()) / (2.0f * osgTan(VertFov *0.5f))),
                                 ((BBMaxCamera.x()-BBMinCamera.x()) / (2.0f * osgTan(HorFov  *0.5f)))));

    //Get the cameras current orientation
    Vec3f OrigY(0.0f,1.0f,0.0f),
          OrigZ(0.0f,0.0f,1.0f);
    CameraToWorld.mult(OrigY, OrigY);
    CameraToWorld.mult(OrigZ, OrigZ);

    //Keep the same camera heading
    Pnt3f  from = at + (OrigZ * dist); 

    if(MatrixLookAt(ResultCameraBeacon, from, at, OrigY))
    {
        ResultCameraBeacon.setIdentity();
    }
}
