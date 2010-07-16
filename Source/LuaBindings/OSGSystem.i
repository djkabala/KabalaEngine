%include <OSGBase.i>
%module OSG
%native(createFieldContainer) int createFieldContainer(lua_State*L);  // registers native_function() with SWIG
%native(getFieldContainer) int getFieldContainer(lua_State*L);  // registers native_function() with SWIG
%{
#include "OSGFieldContainerType.h"
#include "OSGFieldContainer.h"
#include "OSGFieldDescriptionBase.h"
#include "OSGBaseTypes.h"
#include "OSGAttachment.h"
#include "OSGAttachmentContainer.h"
#include "OSGNameAttachment.h"
#include "OSGAttachmentContainer.h"
#include "OSGSimpleGeometry.h"
#include "OSGGeoFunctions.h"
#include "OSGNode.h"
#include "OSGNodeCore.h"
#include "OSGGeometry.h"
#include "OSGViewport.h"
#include "OSGCamera.h"
#include "OSGImage.h"
#include "OSGTextureObjChunk.h"
#include "OSGMathFields.h"
#include "OSGSysFields.h"
#include "OSGBaseFields.h"
#include "OSGVecFields.h"
#include "OSGFieldContainerFields.h"
#include "OSGContainerUtils.h"
#include "OSGActivity.h"
#include "OSGEventProducerType.h"
#include "OSGEventProducer.h"
#include "OSGActivity.h"
#include "OSGWindow.h"
#include "OSGEvent.h"
#include "OSGGenericEvent.h"
#include "OSGLuaActivity.h"
    
    int createFieldContainer(lua_State*L) // my native code
    {
      int SWIG_arg = 0;
      OSG::Char8 *arg1 = (OSG::Char8 *) 0 ;
      OSG::FieldContainerRefPtr result;
      
      SWIG_check_num_args("createFieldContainer",1,1)
      if(!lua_isstring(L,1)) SWIG_fail_arg("createFieldContainer",1,"string");
      
      arg1 = (OSG::Char8 *)lua_tostring(L, 1);
      
      result = OSG::FieldContainerFactory::the()->createContainer(arg1);
      if(result != NULL)
      {
        OSG::FieldContainerRefPtr * resultptr = new OSG::FieldContainerRefPtr((const OSG::FieldContainerRefPtr &) result);
        SWIG_NewPointerObj(L,(void *) resultptr,SWIGTYPE_p_OSG__FieldContainerRefPtr,1); SWIG_arg++;
      }
      else
      {
          lua_pushnil(L); SWIG_arg++;
      }
      return SWIG_arg;
      
      if(0) SWIG_fail;
      
    fail:
      lua_error(L);
      return SWIG_arg;
    }

    int getFieldContainer(lua_State*L) // my native code
    {
      int SWIG_arg = 0;
      OSG::Char8 *arg1 = (OSG::Char8 *) 0 ;
      OSG::FieldContainerRefPtr result;
      
      SWIG_check_num_args("getFieldContainer",1,1)
      if(!lua_isstring(L,1)) SWIG_fail_arg("getFieldContainer",1,"string");
      
      arg1 = (OSG::Char8 *)lua_tostring(L, 1);
      
      result = OSG::getFieldContainer(arg1);
      if(result != NULL)
      {
        OSG::FieldContainerRefPtr * resultptr = new OSG::FieldContainerRefPtr((const OSG::FieldContainerRefPtr &) result);
        SWIG_NewPointerObj(L,(void *) resultptr,SWIGTYPE_p_OSG__FieldContainerRefPtr,1); SWIG_arg++;
      }
      else
      {
          lua_pushnil(L); SWIG_arg++;
      }
      return SWIG_arg;
      
      if(0) SWIG_fail;
      
    fail:
      lua_error(L);
      return SWIG_arg;
    }
    
    int getFieldValue(lua_State*L) // my native code
    {
        int argc = lua_gettop(L);
        int SWIG_arg = 0;
        if (argc == 2) {
          OSG::FieldContainerRefPtr *arg1 = (OSG::FieldContainerRefPtr *) 0 ;
          OSG::Char8 *arg2 = (OSG::Char8 *) 0 ;
          std::string result;
          
          SWIG_check_num_args("getFieldValue",2,2)
          if(!SWIG_isptrtype(L,1)) SWIG_fail_arg("getFieldValue",1,"OSG::FieldContainerRefPtr *");
          if(!lua_isstring(L,2)) SWIG_fail_arg("getFieldValue",2,"OSG::Char8 const *");
              
          if (!SWIG_IsOK(SWIG_ConvertPtr(L,1,(void**)&arg1,SWIGTYPE_p_OSG__FieldContainerRefPtr,0))){
            SWIG_fail_ptr("getFieldValue",1,SWIGTYPE_p_OSG__FieldContainerRefPtr);
          }
          arg2 = (OSG::Char8 *)lua_tostring(L, 2);
          
          const OSG::GetFieldHandlePtr TheFieldHandle((*arg1)->getField(arg2));
          if(!TheFieldHandle->isValid())
          {
              lua_pushfstring(L,"Error in getFieldValue there is no field of name '%s' on type '%s'",arg2,(*arg1)->getTypeName());
              goto fail;
          }
          //Check that this is not a MultiField
          if(TheFieldHandle->getCardinality() == OSG::FieldType::MultiField)
          {
              lua_pushfstring(L,"Error in getFieldValue field of name '%s' on type '%s' is a multi-field, you must also supply the index.",arg2,(*arg1)->getTypeName());
              goto fail;
          }
          //Types
          const OSG::DataType& FieldContentType(TheFieldHandle->getType().getContentType());
          
          //string
          if(FieldContentType == OSG::FieldTraits<std::string>::getType() )
          {
              lua_pushstring(L,static_cast<const OSG::SFString*>(TheFieldHandle->getField())->getValue().c_str()); SWIG_arg++;
          }
          //UInt8
          else if(FieldContentType == OSG::FieldTraits<OSG::UInt8>::getType() )
          {
              lua_pushnumber(L,static_cast<const OSG::SFUInt8*>(TheFieldHandle->getField())->getValue()); SWIG_arg++;
          }
          //UInt16
          else if(FieldContentType == OSG::FieldTraits<OSG::UInt16>::getType() )
          {
              lua_pushnumber(L,static_cast<const OSG::SFUInt16*>(TheFieldHandle->getField())->getValue()); SWIG_arg++;
          }
          //UInt32
          else if(FieldContentType == OSG::FieldTraits<OSG::UInt32>::getType() )
          {
              lua_pushnumber(L,static_cast<const OSG::SFUInt32*>(TheFieldHandle->getField())->getValue()); SWIG_arg++;
          }
          //UInt64
          else if(FieldContentType == OSG::FieldTraits<OSG::UInt64>::getType() )
          {
              lua_pushnumber(L,static_cast<const OSG::SFUInt64*>(TheFieldHandle->getField())->getValue()); SWIG_arg++;
          }
          //BitVector
          else if(FieldContentType == OSG::FieldTraits<OSG::BitVector, 1>::getType() )
          {
              lua_pushnumber(L,static_cast<const OSG::SFBitVector*>(TheFieldHandle->getField())->getValue()); SWIG_arg++;
          }
          //GLenum
          else if(FieldContentType == OSG::FieldTraits<GLenum,1>::getType() )
          {
              lua_pushnumber(L,static_cast<const OSG::SFGLenum*>(TheFieldHandle->getField())->getValue()); SWIG_arg++;
          }
          //Int8
          else if(FieldContentType == OSG::FieldTraits<OSG::Int8>::getType() )
          {
              lua_pushnumber(L,static_cast<const OSG::SFInt8*>(TheFieldHandle->getField())->getValue()); SWIG_arg++;
          }
          //Int16
          else if(FieldContentType == OSG::FieldTraits<OSG::Int16>::getType() )
          {
              lua_pushnumber(L,static_cast<const OSG::SFInt16*>(TheFieldHandle->getField())->getValue()); SWIG_arg++;
          }
          //Int32
          else if(FieldContentType == OSG::FieldTraits<OSG::Int32>::getType() )
          {
              lua_pushnumber(L,static_cast<const OSG::SFInt32*>(TheFieldHandle->getField())->getValue()); SWIG_arg++;
          }
          //Int64
          else if(FieldContentType == OSG::FieldTraits<OSG::Int64>::getType() )
          {
              lua_pushnumber(L,static_cast<const OSG::SFInt64*>(TheFieldHandle->getField())->getValue()); SWIG_arg++;
          }
          //Real16
          else if(FieldContentType == OSG::FieldTraits<OSG::Real16>::getType() )
          {
              lua_pushnumber(L,static_cast<const OSG::SFReal16*>(TheFieldHandle->getField())->getValue()); SWIG_arg++;
          }
          //Real32
          else if(FieldContentType == OSG::FieldTraits<OSG::Real32>::getType() )
          {
              lua_pushnumber(L,static_cast<const OSG::SFReal32*>(TheFieldHandle->getField())->getValue()); SWIG_arg++;
          }
          //Fixed32
          else if(FieldContentType == OSG::FieldTraits<OSG::Fixed32>::getType() )
          {
              lua_pushnumber(L,OSG::Fixed32::toDouble(static_cast<const
                             OSG::SFFixed32*>(TheFieldHandle->getField())->getValue())); SWIG_arg++;
          }
          //Time
          else if(FieldContentType == OSG::FieldTraits<OSG::Time, 1>::getType() )
          {
              lua_pushnumber(L,static_cast<const OSG::SFTime*>(TheFieldHandle->getField())->getValue()); SWIG_arg++;
          }
          //Real64
          else if(FieldContentType == OSG::FieldTraits<OSG::Real64>::getType() )
          {
              lua_pushnumber(L,static_cast<const OSG::SFReal64*>(TheFieldHandle->getField())->getValue()); SWIG_arg++;
          }
          //Color3f
          else if(FieldContentType == OSG::FieldTraits<OSG::Color3f>::getType() )
          {
              OSG::Color3f * resultptr = new OSG::Color3f((const OSG::Color3f &) static_cast<const OSG::SFColor3f*>(TheFieldHandle->getField())->getValue());
              SWIG_NewPointerObj(L,(void *) resultptr,SWIGTYPE_p_OSG__Color3f,1); SWIG_arg++;
          }
          //Color4f
          else if(FieldContentType == OSG::FieldTraits<OSG::Color4f>::getType() )
          {
              OSG::Color4f * resultptr = new OSG::Color4f((const OSG::Color4f &) static_cast<const OSG::SFColor4f*>(TheFieldHandle->getField())->getValue());
              SWIG_NewPointerObj(L,(void *) resultptr,SWIGTYPE_p_OSG__Color4f,1); SWIG_arg++;
          }
          //Vec2f
          else if(FieldContentType == OSG::FieldTraits<OSG::Vec2f>::getType() )
          {
              OSG::Vec2f * resultptr = new OSG::Vec2f((const OSG::Vec2f &) static_cast<const OSG::SFVec2f*>(TheFieldHandle->getField())->getValue());
              SWIG_NewPointerObj(L,(void *) resultptr,SWIGTYPE_p_OSG__Vec2f,1); SWIG_arg++;
          }
          //Vec3f
          else if(FieldContentType == OSG::FieldTraits<OSG::Vec3f>::getType() )
          {
              OSG::Vec3f * resultptr = new OSG::Vec3f((const OSG::Vec3f &) static_cast<const OSG::SFVec3f*>(TheFieldHandle->getField())->getValue());
              SWIG_NewPointerObj(L,(void *) resultptr,SWIGTYPE_p_OSG__Vec3f,1); SWIG_arg++;
          }
          //Vec4f
          else if(FieldContentType == OSG::FieldTraits<OSG::Vec4f>::getType() )
          {
              OSG::Vec4f * resultptr = new OSG::Vec4f((const OSG::Vec4f &) static_cast<const OSG::SFVec4f*>(TheFieldHandle->getField())->getValue());
              SWIG_NewPointerObj(L,(void *) resultptr,SWIGTYPE_p_OSG__Vec4f,1); SWIG_arg++;
          }
          //Pnt2f
          else if(FieldContentType == OSG::FieldTraits<OSG::Pnt2f>::getType() )
          {
              OSG::Pnt2f * resultptr = new OSG::Pnt2f((const OSG::Pnt2f &) static_cast<const OSG::SFPnt2f*>(TheFieldHandle->getField())->getValue());
              SWIG_NewPointerObj(L,(void *) resultptr,SWIGTYPE_p_OSG__Pnt2f,1); SWIG_arg++;
          }
          //Pnt3f
          else if(FieldContentType == OSG::FieldTraits<OSG::Pnt3f>::getType() )
          {
              OSG::Pnt3f * resultptr = new OSG::Pnt3f((const OSG::Pnt3f &) static_cast<const OSG::SFPnt3f*>(TheFieldHandle->getField())->getValue());
              SWIG_NewPointerObj(L,(void *) resultptr,SWIGTYPE_p_OSG__Pnt3f,1); SWIG_arg++;
          }
          //Pnt4f
          else if(FieldContentType == OSG::FieldTraits<OSG::Pnt4f>::getType() )
          {
              OSG::Pnt4f * resultptr = new OSG::Pnt4f((const OSG::Pnt4f &) static_cast<const OSG::SFPnt4f*>(TheFieldHandle->getField())->getValue());
              SWIG_NewPointerObj(L,(void *) resultptr,SWIGTYPE_p_OSG__Pnt4f,1); SWIG_arg++;
          }
          //Matrix
          else if(FieldContentType == OSG::FieldTraits<OSG::Matrix>::getType() )
          {
              OSG::Matrix * resultptr = new OSG::Matrix((const OSG::Matrix &) static_cast<const OSG::SFMatrix*>(TheFieldHandle->getField())->getValue());
              SWIG_NewPointerObj(L,(void *) resultptr,SWIGTYPE_p_OSG__Matrix,1); SWIG_arg++;
          }
          //Quaternion
          else if(FieldContentType == OSG::FieldTraits<OSG::Quaternion>::getType() )
          {
              OSG::Quaternion * resultptr = new OSG::Quaternion((const OSG::Quaternion &) static_cast<const OSG::SFQuaternion*>(TheFieldHandle->getField())->getValue());
              SWIG_NewPointerObj(L,(void *) resultptr,SWIGTYPE_p_OSG__Quaternion,1); SWIG_arg++;
          }
          //FieldContainerRefPtrs
          else if(TheFieldHandle->isPointerField())
          {
            OSG::FieldContainerRefPtr * resultptr = new OSG::FieldContainerRefPtr(static_cast<const OSG::SFUnrecFieldContainerPtr *>(TheFieldHandle->getField())->getValue());
            SWIG_NewPointerObj(L,(void *) resultptr,SWIGTYPE_p_OSG__FieldContainerRefPtr,1); SWIG_arg++;
          }
          //bool
          else if(FieldContentType == OSG::FieldTraits<bool, 2>::getType() )
          {
              lua_pushboolean(L,static_cast<const OSG::SFBool*>(TheFieldHandle->getField())->getValue()); SWIG_arg++;
          }
          //Volumes
          //otherwize
          else
          {
              std::ostringstream TheSStream;
              OSG::OutStream TheOutStream(TheSStream);
              TheFieldHandle->pushValueToStream(TheOutStream);
              lua_pushstring(L,TheSStream.str().c_str()); SWIG_arg++;
          }
          return SWIG_arg;
          
          if(0) SWIG_fail;
        }

        //Multi Field get
        else if (argc == 3) {
          OSG::FieldContainerRefPtr *arg1 = (OSG::FieldContainerRefPtr *) 0 ;
          OSG::Char8 *arg2 = (OSG::Char8 *) 0 ;
          OSG::UInt32 arg3 ;
          std::string result;
          
          SWIG_check_num_args("getFieldValue",3,3)
          if(!SWIG_isptrtype(L,1)) SWIG_fail_arg("getFieldValue",1,"OSG::FieldContainerRefPtr *");
          if(!lua_isstring(L,2)) SWIG_fail_arg("getFieldValue",2,"OSG::Char8 const *");
          if(!lua_isnumber(L,3)) SWIG_fail_arg("getFieldValue",3,"OSG::UInt32");
              
          if (!SWIG_IsOK(SWIG_ConvertPtr(L,1,(void**)&arg1,SWIGTYPE_p_OSG__FieldContainerRefPtr,0))){
            SWIG_fail_ptr("getFieldValue",1,SWIGTYPE_p_OSG__FieldContainerRefPtr);
          }
          arg2 = (OSG::Char8 *)lua_tostring(L, 2);
          arg3 = (OSG::UInt32)lua_tonumber(L, 3);
          
          const OSG::GetFieldHandlePtr TheFieldHandle((*arg1)->getField(arg2));
          if(!TheFieldHandle->isValid())
          {
              lua_pushfstring(L,"Error in getFieldValue there is no field of name '%s' on type '%s'",arg2,(*arg1)->getTypeName());
              goto fail;
          }
          if(TheFieldHandle->getCardinality() != OSG::FieldType::MultiField)
          {
              lua_pushfstring(L,"Error in getFieldValue field of name '%s' on type '%s' is a single-field, you do not need to supply an index..",arg2,(*arg1)->getTypeName());
              goto fail;
          }
          //Types
          const OSG::DataType& FieldContentType(TheFieldHandle->getType().getContentType());
          //string
          if(FieldContentType == OSG::FieldTraits<std::string>::getType() )
          {
              lua_pushstring(L,static_cast<const
                             OSG::MFString*>(TheFieldHandle->getField())->operator[](arg3).c_str()); SWIG_arg++;
          }
          //UInt8
          else if(FieldContentType == OSG::FieldTraits<OSG::UInt8>::getType() )
          {
              lua_pushnumber(L,static_cast<const OSG::MFUInt8*>(TheFieldHandle->getField())->operator[](arg3)); SWIG_arg++;
          }
          //UInt16
          else if(FieldContentType == OSG::FieldTraits<OSG::UInt16>::getType() )
          {
              lua_pushnumber(L,static_cast<const OSG::MFUInt16*>(TheFieldHandle->getField())->operator[](arg3)); SWIG_arg++;
          }
          //UInt32
          else if(FieldContentType == OSG::FieldTraits<OSG::UInt32>::getType() )
          {
              lua_pushnumber(L,static_cast<const OSG::MFUInt32*>(TheFieldHandle->getField())->operator[](arg3)); SWIG_arg++;
          }
          //UInt64
          else if(FieldContentType == OSG::FieldTraits<OSG::UInt64>::getType() )
          {
              lua_pushnumber(L,static_cast<const OSG::MFUInt64*>(TheFieldHandle->getField())->operator[](arg3)); SWIG_arg++;
          }
          //BitVector
          else if(FieldContentType == OSG::FieldTraits<OSG::BitVector, 1>::getType() )
          {
              lua_pushnumber(L,static_cast<const OSG::MFBitVector*>(TheFieldHandle->getField())->operator[](arg3)); SWIG_arg++;
          }
          //GLenum
          else if(FieldContentType == OSG::FieldTraits<GLenum, 1>::getType() )
          {
              lua_pushnumber(L,static_cast<const OSG::MFGLenum*>(TheFieldHandle->getField())->operator[](arg3)); SWIG_arg++;
          }
          //Int8
          else if(FieldContentType == OSG::FieldTraits<OSG::Int8>::getType() )
          {
              lua_pushnumber(L,static_cast<const OSG::MFInt8*>(TheFieldHandle->getField())->operator[](arg3)); SWIG_arg++;
          }
          //Int16
          else if(FieldContentType == OSG::FieldTraits<OSG::Int16>::getType() )
          {
              lua_pushnumber(L,static_cast<const OSG::MFInt16*>(TheFieldHandle->getField())->operator[](arg3)); SWIG_arg++;
          }
          //Int32
          else if(FieldContentType == OSG::FieldTraits<OSG::Int32>::getType() )
          {
              lua_pushnumber(L,static_cast<const OSG::MFInt32*>(TheFieldHandle->getField())->operator[](arg3)); SWIG_arg++;
          }
          //Int64
          else if(FieldContentType == OSG::FieldTraits<OSG::Int64>::getType() )
          {
              lua_pushnumber(L,static_cast<const OSG::MFInt64*>(TheFieldHandle->getField())->operator[](arg3)); SWIG_arg++;
          }
          //Real16
          else if(FieldContentType == OSG::FieldTraits<OSG::Real16>::getType() )
          {
              lua_pushnumber(L,static_cast<const OSG::MFReal16*>(TheFieldHandle->getField())->operator[](arg3)); SWIG_arg++;
          }
          //Real32
          else if(FieldContentType == OSG::FieldTraits<OSG::Real32>::getType() )
          {
              lua_pushnumber(L,static_cast<const OSG::MFReal32*>(TheFieldHandle->getField())->operator[](arg3)); SWIG_arg++;
          }
          //Fixed32
          else if(FieldContentType == OSG::FieldTraits<OSG::Fixed32>::getType() )
          {
              lua_pushnumber(L,OSG::Fixed32::toDouble(static_cast<const
                                                      OSG::MFFixed32*>(TheFieldHandle->getField())->operator[](arg3))); SWIG_arg++;
          }
          //Time
          else if(FieldContentType == OSG::FieldTraits<OSG::Time, 1>::getType() )
          {
              lua_pushnumber(L,static_cast<const OSG::MFTime*>(TheFieldHandle->getField())->operator[](arg3)); SWIG_arg++;
          }
          //Real64
          else if(FieldContentType == OSG::FieldTraits<OSG::Real64>::getType() )
          {
              lua_pushnumber(L,static_cast<const OSG::MFReal64*>(TheFieldHandle->getField())->operator[](arg3)); SWIG_arg++;
          }
          //Color3f
          else if(FieldContentType == OSG::FieldTraits<OSG::Color3f>::getType() )
          {
              OSG::Color3f * resultptr = new OSG::Color3f((const OSG::Color3f &) static_cast<const OSG::MFColor3f*>(TheFieldHandle->getField())->operator[](arg3));
              SWIG_NewPointerObj(L,(void *) resultptr,SWIGTYPE_p_OSG__Color3f,1); SWIG_arg++;
          }
          //Color4f
          else if(FieldContentType == OSG::FieldTraits<OSG::Color4f>::getType() )
          {
              OSG::Color4f * resultptr = new OSG::Color4f((const OSG::Color4f &) static_cast<const OSG::MFColor4f*>(TheFieldHandle->getField())->operator[](arg3));
              SWIG_NewPointerObj(L,(void *) resultptr,SWIGTYPE_p_OSG__Color4f,1); SWIG_arg++;
          }
          //Vec2f
          else if(FieldContentType == OSG::FieldTraits<OSG::Vec2f>::getType() )
          {
              OSG::Vec2f * resultptr = new OSG::Vec2f((const OSG::Vec2f &) static_cast<const OSG::MFVec2f*>(TheFieldHandle->getField())->operator[](arg3));
              SWIG_NewPointerObj(L,(void *) resultptr,SWIGTYPE_p_OSG__Vec2f,1); SWIG_arg++;
          }
          //Vec3f
          else if(FieldContentType == OSG::FieldTraits<OSG::Vec3f>::getType() )
          {
              OSG::Vec3f * resultptr = new OSG::Vec3f((const OSG::Vec3f &) static_cast<const OSG::MFVec3f*>(TheFieldHandle->getField())->operator[](arg3));
              SWIG_NewPointerObj(L,(void *) resultptr,SWIGTYPE_p_OSG__Vec3f,1); SWIG_arg++;
          }
          //Vec4f
          else if(FieldContentType == OSG::FieldTraits<OSG::Vec4f>::getType() )
          {
              OSG::Vec4f * resultptr = new OSG::Vec4f((const OSG::Vec4f &) static_cast<const OSG::MFVec4f*>(TheFieldHandle->getField())->operator[](arg3));
              SWIG_NewPointerObj(L,(void *) resultptr,SWIGTYPE_p_OSG__Vec4f,1); SWIG_arg++;
          }
          //Pnt2f
          else if(FieldContentType == OSG::FieldTraits<OSG::Pnt2f>::getType() )
          {
              OSG::Pnt2f * resultptr = new OSG::Pnt2f((const OSG::Pnt2f &) static_cast<const OSG::MFPnt2f*>(TheFieldHandle->getField())->operator[](arg3));
              SWIG_NewPointerObj(L,(void *) resultptr,SWIGTYPE_p_OSG__Pnt2f,1); SWIG_arg++;
          }
          //Pnt3f
          else if(FieldContentType == OSG::FieldTraits<OSG::Pnt3f>::getType() )
          {
              OSG::Pnt3f * resultptr = new OSG::Pnt3f((const OSG::Pnt3f &) static_cast<const OSG::MFPnt3f*>(TheFieldHandle->getField())->operator[](arg3));
              SWIG_NewPointerObj(L,(void *) resultptr,SWIGTYPE_p_OSG__Pnt3f,1); SWIG_arg++;
          }
          //Pnt4f
          else if(FieldContentType == OSG::FieldTraits<OSG::Pnt4f>::getType() )
          {
              OSG::Pnt4f * resultptr = new OSG::Pnt4f((const OSG::Pnt4f &) static_cast<const OSG::MFPnt4f*>(TheFieldHandle->getField())->operator[](arg3));
              SWIG_NewPointerObj(L,(void *) resultptr,SWIGTYPE_p_OSG__Pnt4f,1); SWIG_arg++;
          }
          //Matrix
          else if(FieldContentType == OSG::FieldTraits<OSG::Matrix>::getType() )
          {
              OSG::Matrix * resultptr = new OSG::Matrix((const OSG::Matrix &) static_cast<const OSG::MFMatrix*>(TheFieldHandle->getField())->operator[](arg3));
              SWIG_NewPointerObj(L,(void *) resultptr,SWIGTYPE_p_OSG__Matrix,1); SWIG_arg++;
          }
          //Quaternion
          else if(FieldContentType == OSG::FieldTraits<OSG::Quaternion>::getType() )
          {
              OSG::Quaternion * resultptr = new OSG::Quaternion((const OSG::Quaternion &) static_cast<const OSG::MFQuaternion*>(TheFieldHandle->getField())->operator[](arg3));
              SWIG_NewPointerObj(L,(void *) resultptr,SWIGTYPE_p_OSG__Quaternion,1); SWIG_arg++;
          }
          //FieldContainerRefPtrs
          else if(TheFieldHandle->isPointerField())
          {
            OSG::FieldContainerRefPtr * resultptr = new OSG::FieldContainerRefPtr(static_cast<const OSG::MFUnrecFieldContainerPtr *>(TheFieldHandle->getField())->operator[](arg3));
            SWIG_NewPointerObj(L,(void *) resultptr,SWIGTYPE_p_OSG__FieldContainerRefPtr,1); SWIG_arg++;
          }
          //bool
          else if(FieldContentType == OSG::FieldTraits<bool, 2>::getType() )
          {
              lua_pushboolean(L,static_cast<const OSG::MFBool*>(TheFieldHandle->getField())->operator[](arg3)); SWIG_arg++;
          }
          //Volumes
          //otherwize
          else
          {
              ////TODO
              //TheField->getValueByStr(result, arg3);
              //lua_pushstring(L,result.c_str()); SWIG_arg++;
          }
          return SWIG_arg;
          
          if(0) SWIG_fail;
        }
      
    fail:
      lua_error(L);
      return SWIG_arg;
    }
    
    bool LUA_BINDING_check_num_args(lua_State*L, const char* func_name,unsigned int a,unsigned int b)
    {
        if (lua_gettop(L)<a || lua_gettop(L)>b)
        {
            lua_pushfstring(L,"Error in %s expected %d..%d args, got %d",func_name,a,b,lua_gettop(L));
            lua_error(L);
            return false;
        }
        return true;
    }

    void LUA_BINDING_fail_arg(lua_State*L, const char* func_name, unsigned int argnum,const char* type)
    {
      lua_pushfstring(L,"Error in %s (arg %d), expected '%s' got '%s'", func_name,argnum,type,SWIG_Lua_typename(L,argnum));
      lua_error(L);
    }

    void LUA_BINDING_fail_ptr(lua_State*L, const char* func_name, unsigned int argnum,swig_type_info* type)
    {
        LUA_BINDING_fail_arg(L, func_name, argnum,(type && type->str)?type->str:"void*");
    }

    int setFieldValue(lua_State*L) // my native code
    {
        int argc = lua_gettop(L);
        int SWIG_arg = 0;
        if (argc == 3) {
          OSG::FieldContainerRefPtr *arg1 = (OSG::FieldContainerRefPtr *) 0 ;
          OSG::Char8 *arg2 = (OSG::Char8 *) 0 ;
          
          //Check if there are the correct number of arguments
          if (!LUA_BINDING_check_num_args(L,"setFieldValue",3,3)){ return SWIG_arg;}
          //Check the type of argument 1
          if(!SWIG_isptrtype(L,1))
          {
              LUA_BINDING_fail_arg(L,"setFieldValue",1,"FieldContainerRefPtr *");
              return SWIG_arg;
          }
          //Check the type of argument 2
          if(!lua_isstring(L,2))
          {
              LUA_BINDING_fail_arg(L,"setFieldValue",2,"OSG::Char8 const *'");
              return SWIG_arg;
          }
              
          //Check the pointer convertion on arg 1
          if (!SWIG_IsOK(SWIG_ConvertPtr(L,1,(void**)&arg1,SWIGTYPE_p_OSG__FieldContainerRefPtr,0)))
          {
              LUA_BINDING_fail_ptr(L,"setFieldValue",1,SWIGTYPE_p_OSG__FieldContainerRefPtr);
              return SWIG_arg;
          }
          //Cast arg 2 to a string
          arg2 = (OSG::Char8 *)lua_tostring(L, 2);
          
          //Check that arg1 is not NullFC
          if((*arg1) == NULL)
          {
              lua_pushfstring(L,"Error in setFieldValue the FieldContainer given is Null");
              lua_error(L);
              return SWIG_arg;
          }
          //Check that the field referenced exists
          OSG::EditFieldHandlePtr TheFieldHandle((*arg1)->editField(arg2));
          if(!TheFieldHandle->isValid())
          {
              lua_pushfstring(L,"Error in setFieldValue there is no field of name '%s' on type '%s'",arg2,(*arg1)->getTypeName());
              lua_error(L);
              return SWIG_arg;
          }
          const OSG::DataType& FieldContentType(TheFieldHandle->getType().getContentType());
          //string
          if(FieldContentType == OSG::FieldTraits<std::string>::getType() )
          {
              if(!lua_isstring(L,3))
              {
                  LUA_BINDING_fail_arg(L,"setFieldValue",3,"string'");
                  return SWIG_arg;
              }
              static_cast<OSG::SFString*>(TheFieldHandle->getField())->setValue(static_cast<const OSG::Char8*>(lua_tostring(L, 3)));
          }
          //UInt8
          else if(FieldContentType == OSG::FieldTraits<OSG::UInt8>::getType() )
          {
              if(!lua_isnumber(L,3))
              {
                  LUA_BINDING_fail_arg(L,"setFieldValue",3,"UInt8'");
                  return SWIG_arg;
              }
                  static_cast<OSG::SFUInt8*>(TheFieldHandle->getField())->setValue(static_cast<OSG::UInt8>(lua_tonumber(L, 3)));
          }
          //UInt16
          else if(FieldContentType == OSG::FieldTraits<OSG::UInt16>::getType() )
          {
              if(!lua_isnumber(L,3))
              {
                  LUA_BINDING_fail_arg(L,"setFieldValue",3,"UInt16'");
                  return SWIG_arg;
              }
                  static_cast<OSG::SFUInt16*>(TheFieldHandle->getField())->setValue(static_cast<OSG::UInt16>(lua_tonumber(L, 3)));
          }
          //UInt32
          else if(FieldContentType == OSG::FieldTraits<OSG::UInt32>::getType())
          {
              if(!lua_isnumber(L,3))
              {
                  LUA_BINDING_fail_arg(L,"setFieldValue",3,"UInt32'");
                  return SWIG_arg;
              }
                  static_cast<OSG::SFUInt32*>(TheFieldHandle->getField())->setValue(static_cast<OSG::UInt32>(lua_tonumber(L, 3)));
          }
          //UInt64
          else if(FieldContentType == OSG::FieldTraits<OSG::UInt64>::getType() )
          {
              if(!lua_isnumber(L,3))
              {
                  LUA_BINDING_fail_arg(L,"setFieldValue",3,"UInt64'");
                  return SWIG_arg;
              }
                  static_cast<OSG::SFUInt64*>(TheFieldHandle->getField())->setValue(static_cast<OSG::UInt64>(lua_tonumber(L, 3)));
          }
          //BitVector
          else if(FieldContentType == OSG::FieldTraits<OSG::BitVector, 1>::getType() )
          {
              if(!lua_isnumber(L,3))
              {
                  LUA_BINDING_fail_arg(L,"setFieldValue",3,"BitVector'");
                  return SWIG_arg;
              }
                  static_cast<OSG::SFBitVector*>(TheFieldHandle->getField())->setValue(static_cast<OSG::BitVector>(lua_tonumber(L, 3)));
          }
          //GLenum
          else if(FieldContentType == OSG::FieldTraits<GLenum, 1>::getType() )
          {
              if(!lua_isnumber(L,3))
              {
                  LUA_BINDING_fail_arg(L,"setFieldValue",3,"GLenum'");
                  return SWIG_arg;
              }
                  static_cast<OSG::SFGLenum*>(TheFieldHandle->getField())->setValue(static_cast<GLenum>(lua_tonumber(L, 3)));
          }
          //Int8
          else if(FieldContentType == OSG::FieldTraits<OSG::Int8>::getType() )
          {
              if(!lua_isnumber(L,3))
              {
                  LUA_BINDING_fail_arg(L,"setFieldValue",3,"Int8'");
                  return SWIG_arg;
              }
                  static_cast<OSG::SFInt8*>(TheFieldHandle->getField())->setValue(static_cast<OSG::Int8>(lua_tonumber(L, 3)));
          }
          //Int16
          else if(FieldContentType == OSG::FieldTraits<OSG::Int16>::getType() )
          {
              if(!lua_isnumber(L,3))
              {
                  LUA_BINDING_fail_arg(L,"setFieldValue",3,"Int16'");
                  return SWIG_arg;
              }
                  static_cast<OSG::SFInt16*>(TheFieldHandle->getField())->setValue(static_cast<OSG::Int16>(lua_tonumber(L, 3)));
          }
          //Int32
          else if(FieldContentType == OSG::FieldTraits<OSG::Int32>::getType() )
          {
              if(!lua_isnumber(L,3))
              {
                  LUA_BINDING_fail_arg(L,"setFieldValue",3,"Int32'");
                  return SWIG_arg;
              }
                  static_cast<OSG::SFInt32*>(TheFieldHandle->getField())->setValue(static_cast<OSG::Int32>(lua_tonumber(L, 3)));
          }
          //Int64
          else if(FieldContentType == OSG::FieldTraits<OSG::Int64>::getType() )
          {
              if(!lua_isnumber(L,3))
              {
                  LUA_BINDING_fail_arg(L,"setFieldValue",3,"Int64'");
                  return SWIG_arg;
              }
                  static_cast<OSG::SFInt64*>(TheFieldHandle->getField())->setValue(static_cast<OSG::Int64>(lua_tonumber(L, 3)));
          }
          //Real16
          else if(FieldContentType == OSG::FieldTraits<OSG::Real16>::getType() )
          {
              if(!lua_isnumber(L,3))
              {
                  LUA_BINDING_fail_arg(L,"setFieldValue",3,"Real16'");
                  return SWIG_arg;
              }
                  static_cast<OSG::SFReal16*>(TheFieldHandle->getField())->setValue(static_cast<OSG::Real16>(lua_tonumber(L, 3)));
          }
          //Real32
          else if(FieldContentType == OSG::FieldTraits<OSG::Real32>::getType() )
          {
              if(!lua_isnumber(L,3))
              {
                  LUA_BINDING_fail_arg(L,"setFieldValue",3,"Real32'");
                  return SWIG_arg;
              }
                  static_cast<OSG::SFReal32*>(TheFieldHandle->getField())->setValue(static_cast<OSG::Real32>(lua_tonumber(L, 3)));
          }
          //Fixed32
          else if(FieldContentType == OSG::FieldTraits<OSG::Fixed32>::getType() )
          {
              if(!lua_isnumber(L,3))
              {
                  LUA_BINDING_fail_arg(L,"setFieldValue",3,"Fixed32'");
                  return SWIG_arg;
              }
                  static_cast<OSG::SFFixed32*>(TheFieldHandle->getField())->setValue(OSG::Fixed32(lua_tonumber(L, 3)));
          }
          //Time
          else if(FieldContentType == OSG::FieldTraits<OSG::Time, 1>::getType() )
          {
              if(!lua_isnumber(L,3))
              {
                  LUA_BINDING_fail_arg(L,"setFieldValue",3,"Time'");
                  return SWIG_arg;
              }
                  static_cast<OSG::SFTime*>(TheFieldHandle->getField())->setValue(static_cast<OSG::Time>(lua_tonumber(L, 3)));
          }
          //Real64
          else if(FieldContentType == OSG::FieldTraits<OSG::Real64>::getType() )
          {
              if(!lua_isnumber(L,3))
              {
                  LUA_BINDING_fail_arg(L,"setFieldValue",3,"Real64'");
                  return SWIG_arg;
              }
                  static_cast<OSG::SFReal64*>(TheFieldHandle->getField())->setValue(static_cast<OSG::Real64>(lua_tonumber(L, 3)));
          }
          //Color3f
          else if(FieldContentType == OSG::FieldTraits<OSG::Color3f>::getType() )
          {
              OSG::Color3f *arg3 = 0 ;
              if (!SWIG_IsOK(SWIG_ConvertPtr(L,3,(void**)&arg3,SWIGTYPE_p_OSG__Color3f,0))){
                  LUA_BINDING_fail_ptr(L,"setFieldValue",3,SWIGTYPE_p_OSG__Color3f);
                  return SWIG_arg;
              }
              
                  static_cast<OSG::SFColor3f*>(TheFieldHandle->getField())->setValue(static_cast<OSG::Color3f const &>(*arg3));
          }
          //Color4f
          else if(FieldContentType == OSG::FieldTraits<OSG::Color4f>::getType() )
          {
              OSG::Color4f *arg3 = 0 ;
              if (!SWIG_IsOK(SWIG_ConvertPtr(L,3,(void**)&arg3,SWIGTYPE_p_OSG__Color4f,0))){
                  LUA_BINDING_fail_ptr(L,"setFieldValue",3,SWIGTYPE_p_OSG__Color4f);
                  return SWIG_arg;
              }
              
                  static_cast<OSG::SFColor4f*>(TheFieldHandle->getField())->setValue(static_cast<OSG::Color4f const &>(*arg3));
          }
          //Vec2f
          else if(FieldContentType == OSG::FieldTraits<OSG::Vec2f>::getType() )
          {
              OSG::Vec2f *arg3 = 0 ;
              if (!SWIG_IsOK(SWIG_ConvertPtr(L,3,(void**)&arg3,SWIGTYPE_p_OSG__Vec2f,0))){
                  LUA_BINDING_fail_ptr(L,"setFieldValue",3,SWIGTYPE_p_OSG__Vec2f);
                  return SWIG_arg;
              }
              
                  static_cast<OSG::SFVec2f*>(TheFieldHandle->getField())->setValue(static_cast<OSG::Vec2f const &>(*arg3));
          }
          //Vec3f
          else if(FieldContentType == OSG::FieldTraits<OSG::Vec3f>::getType() )
          {
              OSG::Vec3f *arg3 = 0 ;
              if (!SWIG_IsOK(SWIG_ConvertPtr(L,3,(void**)&arg3,SWIGTYPE_p_OSG__Vec3f,0))){
                  LUA_BINDING_fail_ptr(L,"setFieldValue",3,SWIGTYPE_p_OSG__Vec3f);
                  return SWIG_arg;
              }
              
                  static_cast<OSG::SFVec3f*>(TheFieldHandle->getField())->setValue(static_cast<OSG::Vec3f const &>(*arg3));
          }
          //Vec4f
          else if(FieldContentType == OSG::FieldTraits<OSG::Vec4f>::getType() )
          {
              OSG::Vec4f *arg3 = 0 ;
              if (!SWIG_IsOK(SWIG_ConvertPtr(L,3,(void**)&arg3,SWIGTYPE_p_OSG__Vec4f,0))){
                  LUA_BINDING_fail_ptr(L,"setFieldValue",3,SWIGTYPE_p_OSG__Vec4f);
                  return SWIG_arg;
              }
              
                  static_cast<OSG::SFVec4f*>(TheFieldHandle->getField())->setValue(static_cast<OSG::Vec4f const &>(*arg3));
          }
          //Pnt2f
          else if(FieldContentType == OSG::FieldTraits<OSG::Pnt2f>::getType() )
          {
              OSG::Pnt2f *arg3 = 0 ;
              if (!SWIG_IsOK(SWIG_ConvertPtr(L,3,(void**)&arg3,SWIGTYPE_p_OSG__Pnt2f,0))){
                  LUA_BINDING_fail_ptr(L,"setFieldValue",3,SWIGTYPE_p_OSG__Pnt2f);
                  return SWIG_arg;
              }
              
                  static_cast<OSG::SFPnt2f*>(TheFieldHandle->getField())->setValue(static_cast<OSG::Pnt2f const &>(*arg3));
          }
          //Pnt3f
          else if(FieldContentType == OSG::FieldTraits<OSG::Pnt3f>::getType() )
          {
              OSG::Pnt3f *arg3 = 0 ;
              if (!SWIG_IsOK(SWIG_ConvertPtr(L,3,(void**)&arg3,SWIGTYPE_p_OSG__Pnt3f,0))){
                  LUA_BINDING_fail_ptr(L,"setFieldValue",3,SWIGTYPE_p_OSG__Pnt3f);
                  return SWIG_arg;
              }
              
                  static_cast<OSG::SFPnt3f*>(TheFieldHandle->getField())->setValue(static_cast<OSG::Pnt3f const &>(*arg3));
          }
          //Pnt4f
          else if(FieldContentType == OSG::FieldTraits<OSG::Pnt4f>::getType() )
          {
              OSG::Pnt4f *arg3 = 0 ;
              if (!SWIG_IsOK(SWIG_ConvertPtr(L,3,(void**)&arg3,SWIGTYPE_p_OSG__Pnt4f,0))){
                  LUA_BINDING_fail_ptr(L,"setFieldValue",3,SWIGTYPE_p_OSG__Pnt4f);
                  return SWIG_arg;
              }
              
                  static_cast<OSG::SFPnt4f*>(TheFieldHandle->getField())->setValue(static_cast<OSG::Pnt4f const &>(*arg3));
          }
          //Matrix
          else if(FieldContentType == OSG::FieldTraits<OSG::Matrix>::getType() )
          {
              OSG::Matrix *arg3 = 0 ;
              if (!SWIG_IsOK(SWIG_ConvertPtr(L,3,(void**)&arg3,SWIGTYPE_p_OSG__Matrix,0))){
                  LUA_BINDING_fail_ptr(L,"setFieldValue",3,SWIGTYPE_p_OSG__Matrix);
                  return SWIG_arg;
              }
              
                  static_cast<OSG::SFMatrix*>(TheFieldHandle->getField())->setValue(static_cast<OSG::Matrix const &>(*arg3));
          }
          //Quaternion
          else if(FieldContentType == OSG::FieldTraits<OSG::Quaternion>::getType() )
          {
              OSG::Quaternion *arg3 = 0 ;
              if (!SWIG_IsOK(SWIG_ConvertPtr(L,3,(void**)&arg3,SWIGTYPE_p_OSG__Quaternion,0))){
                  LUA_BINDING_fail_ptr(L,"setFieldValue",3,SWIGTYPE_p_OSG__Quaternion);
                  return SWIG_arg;
              }
              
                  static_cast<OSG::SFQuaternion*>(TheFieldHandle->getField())->setValue(static_cast<OSG::Quaternion const &>(*arg3));
          }
          //FieldContainerRefPtrs
          else if(TheFieldHandle->isPointerField())
          {
              OSG::FieldContainerRefPtr *arg3 = (OSG::FieldContainerRefPtr *) 0 ;
              if (!SWIG_IsOK(SWIG_ConvertPtr(L,3,(void**)&arg3,SWIGTYPE_p_OSG__FieldContainerRefPtr,0)))
              {
                  LUA_BINDING_fail_ptr(L,"setFieldValue",3,SWIGTYPE_p_OSG__FieldContainerRefPtr);
                  return SWIG_arg;
              }
              switch(TheFieldHandle->getType().getClass())
              {
                  case OSG::FieldType::ChildPtrField:
                       static_cast<OSG::ChildPointerSField <OSG::FieldContainer *,
                                   OSG::UnrecordedRefCountPolicy,1>*>(TheFieldHandle->getField())->setValue(*arg3);
                       break;
                  case OSG::FieldType::ParentPtrField:
                       lua_pushfstring(L,"Error in setFieldValue the FieldContainer given is of the ParentPtr class.  Cannot set the value of this field directly");
                       lua_error(L);
                       break;
                  case OSG::FieldType::PtrField:
                       static_cast<OSG::SFUnrecFieldContainerPtr*>(TheFieldHandle->getField())->setValue(*arg3);
                       break;
              }
          }
          //bool
          else if(FieldContentType == OSG::FieldTraits<bool, 2>::getType() )
          {
              if(!lua_isboolean(L,3))
              {
                  LUA_BINDING_fail_arg(L,"setFieldValue",3,"boolean'");
                  return SWIG_arg;
              }
                  static_cast<OSG::SFBool*>(TheFieldHandle->getField())->setValue(static_cast<bool>(lua_toboolean(L, 3)));
          }
          //Volumes
          //Otherwise
          else
          {
              if(!lua_isstring(L,3))
              {
                  LUA_BINDING_fail_arg(L,"setFieldValue",3,"string'");
                  return SWIG_arg;
              }
              TheFieldHandle->pushValueFromCString(lua_tostring(L, 3));
          }
        }
        else if (argc == 4) {
          OSG::FieldContainerRefPtr *arg1 = (OSG::FieldContainerRefPtr *) 0 ;
          OSG::Char8 *arg2 = (OSG::Char8 *) 0 ;
          OSG::UInt32 arg4 ;
          
          //Check if there are the correct number of arguments
          if (!LUA_BINDING_check_num_args(L,"setFieldValue",4,4)){ return SWIG_arg;}
          //Check the type of argument 1
          if(!SWIG_isptrtype(L,1))
          {
              LUA_BINDING_fail_arg(L,"setFieldValue",1,"FieldContainerRefPtr *");
              return SWIG_arg;
          }
          //Check the type of argument 2
          if(!lua_isstring(L,2))
          {
              LUA_BINDING_fail_arg(L,"setFieldValue",2,"OSG::Char8 const *'");
              return SWIG_arg;
          }
          if(!lua_isnumber(L,4))
          {
              LUA_BINDING_fail_arg(L,"setFieldValue",4,"OSG::UInt32'");
              return SWIG_arg;
          }
              
          //Check the pointer convertion on arg 1
          if (!SWIG_IsOK(SWIG_ConvertPtr(L,1,(void**)&arg1,SWIGTYPE_p_OSG__FieldContainerRefPtr,0)))
          {
              LUA_BINDING_fail_ptr(L,"setFieldValue",1,SWIGTYPE_p_OSG__FieldContainerRefPtr);
              return SWIG_arg;
          }
          //Cast arg 2 to a string
          arg2 = (OSG::Char8 *)lua_tostring(L, 2);
          arg4 = (OSG::UInt32)lua_tonumber(L, 4);
          
          //Check that arg1 is not NullFC
          if((*arg1) == NULL)
          {
              lua_pushfstring(L,"Error in setFieldValue the FieldContainer given is Null");
              lua_error(L);
              return SWIG_arg;
          }
          //Check that the field referenced exists
          OSG::EditFieldHandlePtr TheFieldHandle((*arg1)->editField(arg2));
          if(!TheFieldHandle->isValid())
          {
              lua_pushfstring(L,"Error in setFieldValue there is no field of name '%s' on type '%s'",arg2,(*arg1)->getTypeName());
              lua_error(L);
              return SWIG_arg;
          }
          if(TheFieldHandle->getCardinality() == OSG::FieldType::SingleField)
          {
              lua_pushfstring(L,"Error in setFieldValue field of name '%s' on type '%s' is a single-field, you do not need to supply an index..",arg2,(*arg1)->getTypeName());
              lua_error(L);
              return SWIG_arg;
          }
          const OSG::DataType& FieldContentType(TheFieldHandle->getType().getContentType());
          //string
          if(FieldContentType == OSG::FieldTraits<std::string>::getType() )
          {
              if(!lua_isstring(L,3))
              {
                  LUA_BINDING_fail_arg(L,"setFieldValue",3,"string'");
                  return SWIG_arg;
              }
                  static_cast<OSG::MFString*>(TheFieldHandle->getField())->operator[](arg4) = (static_cast<const OSG::Char8*>(lua_tostring(L, 3)));
          }
          //UInt8
          else if(FieldContentType == OSG::FieldTraits<OSG::UInt8>::getType() )
          {
              if(!lua_isnumber(L,3))
              {
                  LUA_BINDING_fail_arg(L,"setFieldValue",3,"UInt8'");
                  return SWIG_arg;
              }
                  static_cast<OSG::MFUInt8*>(TheFieldHandle->getField())->operator[](arg4) = (static_cast<OSG::UInt8>(lua_tonumber(L, 3)));
          }
          //UInt16
          else if(FieldContentType == OSG::FieldTraits<OSG::UInt16>::getType() )
          {
              if(!lua_isnumber(L,3))
              {
                  LUA_BINDING_fail_arg(L,"setFieldValue",3,"UInt16'");
                  return SWIG_arg;
              }
                  static_cast<OSG::MFUInt16*>(TheFieldHandle->getField())->operator[](arg4) = (static_cast<OSG::UInt16>(lua_tonumber(L, 3)));
          }
          //UInt32
          else if(FieldContentType == OSG::FieldTraits<OSG::UInt32>::getType())
          {
              if(!lua_isnumber(L,3))
              {
                  LUA_BINDING_fail_arg(L,"setFieldValue",3,"UInt32'");
                  return SWIG_arg;
              }
                  static_cast<OSG::MFUInt32*>(TheFieldHandle->getField())->operator[](arg4) = (static_cast<OSG::UInt32>(lua_tonumber(L, 3)));
          }
          //UInt64
          else if(FieldContentType == OSG::FieldTraits<OSG::UInt64>::getType() )
          {
              if(!lua_isnumber(L,3))
              {
                  LUA_BINDING_fail_arg(L,"setFieldValue",3,"UInt64'");
                  return SWIG_arg;
              }
                  static_cast<OSG::MFUInt64*>(TheFieldHandle->getField())->operator[](arg4) = (static_cast<OSG::UInt64>(lua_tonumber(L, 3)));
          }
          //BitVector
          else if(FieldContentType == OSG::FieldTraits<OSG::BitVector, 1>::getType() )
          {
              if(!lua_isnumber(L,3))
              {
                  LUA_BINDING_fail_arg(L,"setFieldValue",3,"BitVector'");
                  return SWIG_arg;
              }
                  static_cast<OSG::MFBitVector*>(TheFieldHandle->getField())->operator[](arg4) = (static_cast<OSG::BitVector>(lua_tonumber(L, 3)));
          }
          //GLenum
          else if(FieldContentType == OSG::FieldTraits<GLenum, 1>::getType() )
          {
              if(!lua_isnumber(L,3))
              {
                  LUA_BINDING_fail_arg(L,"setFieldValue",3,"GLenum'");
                  return SWIG_arg;
              }
                  static_cast<OSG::MFGLenum*>(TheFieldHandle->getField())->operator[](arg4) = (static_cast<GLenum>(lua_tonumber(L, 3)));
          }
          //Int8
          else if(FieldContentType == OSG::FieldTraits<OSG::Int8>::getType() )
          {
              if(!lua_isnumber(L,3))
              {
                  LUA_BINDING_fail_arg(L,"setFieldValue",3,"Int8'");
                  return SWIG_arg;
              }
                  static_cast<OSG::MFInt8*>(TheFieldHandle->getField())->operator[](arg4) = (static_cast<OSG::Int8>(lua_tonumber(L, 3)));
          }
          //Int16
          else if(FieldContentType == OSG::FieldTraits<OSG::Int16>::getType() )
          {
              if(!lua_isnumber(L,3))
              {
                  LUA_BINDING_fail_arg(L,"setFieldValue",3,"Int16'");
                  return SWIG_arg;
              }
                  static_cast<OSG::MFInt16*>(TheFieldHandle->getField())->operator[](arg4) = (static_cast<OSG::Int16>(lua_tonumber(L, 3)));
          }
          //Int32
          else if(FieldContentType == OSG::FieldTraits<OSG::Int32>::getType() )
          {
              if(!lua_isnumber(L,3))
              {
                  LUA_BINDING_fail_arg(L,"setFieldValue",3,"Int32'");
                  return SWIG_arg;
              }
                  static_cast<OSG::MFInt32*>(TheFieldHandle->getField())->operator[](arg4) = (static_cast<OSG::Int32>(lua_tonumber(L, 3)));
          }
          //Int64
          else if(FieldContentType == OSG::FieldTraits<OSG::Int64>::getType() )
          {
              if(!lua_isnumber(L,3))
              {
                  LUA_BINDING_fail_arg(L,"setFieldValue",3,"Int64'");
                  return SWIG_arg;
              }
                  static_cast<OSG::MFInt64*>(TheFieldHandle->getField())->operator[](arg4) = (static_cast<OSG::Int64>(lua_tonumber(L, 3)));
          }
          //Real16
          else if(FieldContentType == OSG::FieldTraits<OSG::Real16>::getType() )
          {
              if(!lua_isnumber(L,3))
              {
                  LUA_BINDING_fail_arg(L,"setFieldValue",3,"Real16'");
                  return SWIG_arg;
              }
                  static_cast<OSG::MFReal16*>(TheFieldHandle->getField())->operator[](arg4) = (static_cast<OSG::Real16>(lua_tonumber(L, 3)));
          }
          //Real32
          else if(FieldContentType == OSG::FieldTraits<OSG::Real32>::getType() )
          {
              if(!lua_isnumber(L,3))
              {
                  LUA_BINDING_fail_arg(L,"setFieldValue",3,"Real32'");
                  return SWIG_arg;
              }
                  static_cast<OSG::MFReal32*>(TheFieldHandle->getField())->operator[](arg4) = (static_cast<OSG::Real32>(lua_tonumber(L, 3)));
          }
          //Fixed32
          else if(FieldContentType == OSG::FieldTraits<OSG::Fixed32>::getType() )
          {
              if(!lua_isnumber(L,3))
              {
                  LUA_BINDING_fail_arg(L,"setFieldValue",3,"Fixed32'");
                  return SWIG_arg;
              }
                  static_cast<OSG::MFFixed32*>(TheFieldHandle->getField())->operator[](arg4) = (OSG::Fixed32(lua_tonumber(L, 3)));
          }
          //Time
          else if(FieldContentType == OSG::FieldTraits<OSG::Time, 1>::getType() )
          {
              if(!lua_isnumber(L,3))
              {
                  LUA_BINDING_fail_arg(L,"setFieldValue",3,"Time'");
                  return SWIG_arg;
              }
                  static_cast<OSG::MFTime*>(TheFieldHandle->getField())->operator[](arg4) = (static_cast<OSG::Time>(lua_tonumber(L, 3)));
          }
          //Real64
          else if(FieldContentType == OSG::FieldTraits<OSG::Real64>::getType() )
          {
              if(!lua_isnumber(L,3))
              {
                  LUA_BINDING_fail_arg(L,"setFieldValue",3,"Real64'");
                  return SWIG_arg;
              }
                  static_cast<OSG::MFReal64*>(TheFieldHandle->getField())->operator[](arg4) = (static_cast<OSG::Real64>(lua_tonumber(L, 3)));
          }
          //Color3f
          else if(FieldContentType == OSG::FieldTraits<OSG::Color3f>::getType() )
          {
              OSG::Color3f *arg3 = 0 ;
              if (!SWIG_IsOK(SWIG_ConvertPtr(L,3,(void**)&arg3,SWIGTYPE_p_OSG__Color3f,0))){
                  LUA_BINDING_fail_ptr(L,"setFieldValue",3,SWIGTYPE_p_OSG__Color3f);
                  return SWIG_arg;
              }
              
                  static_cast<OSG::MFColor3f*>(TheFieldHandle->getField())->operator[](arg4) = (static_cast<OSG::Color3f const &>(*arg3));
          }
          //Color4f
          else if(FieldContentType == OSG::FieldTraits<OSG::Color4f>::getType() )
          {
              OSG::Color4f *arg3 = 0 ;
              if (!SWIG_IsOK(SWIG_ConvertPtr(L,3,(void**)&arg3,SWIGTYPE_p_OSG__Color4f,0))){
                  LUA_BINDING_fail_ptr(L,"setFieldValue",3,SWIGTYPE_p_OSG__Color4f);
                  return SWIG_arg;
              }
              
                  static_cast<OSG::MFColor4f*>(TheFieldHandle->getField())->operator[](arg4) = (static_cast<OSG::Color4f const &>(*arg3));
          }
          //Vec2f
          else if(FieldContentType == OSG::FieldTraits<OSG::Vec2f>::getType() )
          {
              OSG::Vec2f *arg3 = 0 ;
              if (!SWIG_IsOK(SWIG_ConvertPtr(L,3,(void**)&arg3,SWIGTYPE_p_OSG__Vec2f,0))){
                  LUA_BINDING_fail_ptr(L,"setFieldValue",3,SWIGTYPE_p_OSG__Vec2f);
                  return SWIG_arg;
              }
              
                  static_cast<OSG::MFVec2f*>(TheFieldHandle->getField())->operator[](arg4) = (static_cast<OSG::Vec2f const &>(*arg3));
          }
          //Vec3f
          else if(FieldContentType == OSG::FieldTraits<OSG::Vec3f>::getType() )
          {
              OSG::Vec3f *arg3 = 0 ;
              if (!SWIG_IsOK(SWIG_ConvertPtr(L,3,(void**)&arg3,SWIGTYPE_p_OSG__Vec3f,0))){
                  LUA_BINDING_fail_ptr(L,"setFieldValue",3,SWIGTYPE_p_OSG__Vec3f);
                  return SWIG_arg;
              }
              
                  static_cast<OSG::MFVec3f*>(TheFieldHandle->getField())->operator[](arg4) = (static_cast<OSG::Vec3f const &>(*arg3));
          }
          //Vec4f
          else if(FieldContentType == OSG::FieldTraits<OSG::Vec4f>::getType() )
          {
              OSG::Vec4f *arg3 = 0 ;
              if (!SWIG_IsOK(SWIG_ConvertPtr(L,3,(void**)&arg3,SWIGTYPE_p_OSG__Vec4f,0))){
                  LUA_BINDING_fail_ptr(L,"setFieldValue",3,SWIGTYPE_p_OSG__Vec4f);
                  return SWIG_arg;
              }
              
                  static_cast<OSG::MFVec4f*>(TheFieldHandle->getField())->operator[](arg4) = (static_cast<OSG::Vec4f const &>(*arg3));
          }
          //Pnt2f
          else if(FieldContentType == OSG::FieldTraits<OSG::Pnt2f>::getType() )
          {
              OSG::Pnt2f *arg3 = 0 ;
              if (!SWIG_IsOK(SWIG_ConvertPtr(L,3,(void**)&arg3,SWIGTYPE_p_OSG__Pnt2f,0))){
                  LUA_BINDING_fail_ptr(L,"setFieldValue",3,SWIGTYPE_p_OSG__Pnt2f);
                  return SWIG_arg;
              }
              
                  static_cast<OSG::MFPnt2f*>(TheFieldHandle->getField())->operator[](arg4) = (static_cast<OSG::Pnt2f const &>(*arg3));
          }
          //Pnt3f
          else if(FieldContentType == OSG::FieldTraits<OSG::Pnt3f>::getType() )
          {
              OSG::Pnt3f *arg3 = 0 ;
              if (!SWIG_IsOK(SWIG_ConvertPtr(L,3,(void**)&arg3,SWIGTYPE_p_OSG__Pnt3f,0))){
                  LUA_BINDING_fail_ptr(L,"setFieldValue",3,SWIGTYPE_p_OSG__Pnt3f);
                  return SWIG_arg;
              }
              
                  static_cast<OSG::MFPnt3f*>(TheFieldHandle->getField())->operator[](arg4) = (static_cast<OSG::Pnt3f const &>(*arg3));
          }
          //Pnt4f
          else if(FieldContentType == OSG::FieldTraits<OSG::Pnt4f>::getType() )
          {
              OSG::Pnt4f *arg3 = 0 ;
              if (!SWIG_IsOK(SWIG_ConvertPtr(L,3,(void**)&arg3,SWIGTYPE_p_OSG__Pnt4f,0))){
                  LUA_BINDING_fail_ptr(L,"setFieldValue",3,SWIGTYPE_p_OSG__Pnt4f);
                  return SWIG_arg;
              }
              
                  static_cast<OSG::MFPnt4f*>(TheFieldHandle->getField())->operator[](arg4) = (static_cast<OSG::Pnt4f const &>(*arg3));
          }
          //Matrix
          else if(FieldContentType == OSG::FieldTraits<OSG::Matrix>::getType() )
          {
              OSG::Matrix *arg3 = 0 ;
              if (!SWIG_IsOK(SWIG_ConvertPtr(L,3,(void**)&arg3,SWIGTYPE_p_OSG__Matrix,0))){
                  LUA_BINDING_fail_ptr(L,"setFieldValue",3,SWIGTYPE_p_OSG__Matrix);
                  return SWIG_arg;
              }
              
                  static_cast<OSG::MFMatrix*>(TheFieldHandle->getField())->operator[](arg4) = (static_cast<OSG::Matrix const &>(*arg3));
          }
          //Quaternion
          else if(FieldContentType == OSG::FieldTraits<OSG::Quaternion>::getType() )
          {
              OSG::Quaternion *arg3 = 0 ;
              if (!SWIG_IsOK(SWIG_ConvertPtr(L,3,(void**)&arg3,SWIGTYPE_p_OSG__Quaternion,0))){
                  LUA_BINDING_fail_ptr(L,"setFieldValue",3,SWIGTYPE_p_OSG__Quaternion);
                  return SWIG_arg;
              }
              
                  static_cast<OSG::MFQuaternion*>(TheFieldHandle->getField())->operator[](arg4) = (static_cast<OSG::Quaternion const &>(*arg3));
          }
          //FieldContainerRefPtrs
          else if(TheFieldHandle->isPointerField())
          {
              OSG::FieldContainerRefPtr *arg3 = (OSG::FieldContainerRefPtr *) 0 ;
              if (!SWIG_IsOK(SWIG_ConvertPtr(L,3,(void**)&arg3,SWIGTYPE_p_OSG__FieldContainerRefPtr,0)))
              {
                  LUA_BINDING_fail_ptr(L,"setFieldValue",3,SWIGTYPE_p_OSG__FieldContainerRefPtr);
                  return SWIG_arg;
              }
              //TODO
              switch(TheFieldHandle->getType().getClass())
              {
                  case OSG::FieldType::ChildPtrField:
                       static_cast<OSG::ChildPointerMField <OSG::FieldContainer *,
                                   OSG::UnrecordedRefCountPolicy,1>*>(TheFieldHandle->getField())->replace(arg4,*arg3);
                       break;
                  case OSG::FieldType::ParentPtrField:
                       lua_pushfstring(L,"Error in setFieldValue the FieldContainer given is of the ParentPtr class.  Cannot set the value of this field directly");
                       lua_error(L);
                       break;
                  case OSG::FieldType::PtrField:
                       static_cast<OSG::MFUnrecFieldContainerPtr*>(TheFieldHandle->getField())->replace(arg4,*arg3);
                       break;
              }
          }
          //bool
          else if(FieldContentType == OSG::FieldTraits<bool, 2>::getType() )
          {
              if(!lua_isboolean(L,3))
              {
                  LUA_BINDING_fail_arg(L,"setFieldValue",3,"boolean'");
                  return SWIG_arg;
              }
                  static_cast<OSG::MFBool*>(TheFieldHandle->getField())->operator[](arg4) = (static_cast<bool>(lua_toboolean(L, 3)));
          }
          //Volumes
          //Otherwise
          else
          {
              lua_pushfstring(L,"Error in setFieldValue field of name '%s' on type '%s', could not set the indexed value of the multi-field because that type is not supported in this biding.",arg2,(*arg1)->getTypeName());
              lua_error(L);
          }
        }

          return SWIG_arg;
    }

    int pushFieldValue(lua_State*L) // my native code
    {
        int SWIG_arg = 0;
          OSG::FieldContainerRefPtr *arg1 = (OSG::FieldContainerRefPtr *) 0 ;
          OSG::Char8 *arg2 = (OSG::Char8 *) 0 ;
          
          //Check if there are the correct number of arguments
          if (!LUA_BINDING_check_num_args(L,"pushFieldValue",3,3)){ return SWIG_arg;}
          //Check the type of argument 1
          if(!SWIG_isptrtype(L,1))
          {
              LUA_BINDING_fail_arg(L,"pushFieldValue",1,"FieldContainerRefPtr *");
              return SWIG_arg;
          }
          //Check the type of argument 2
          if(!lua_isstring(L,2))
          {
              LUA_BINDING_fail_arg(L,"pushFieldValue",2,"OSG::Char8 const *'");
              return SWIG_arg;
          }
              
          //Check the pointer convertion on arg 1
          if (!SWIG_IsOK(SWIG_ConvertPtr(L,1,(void**)&arg1,SWIGTYPE_p_OSG__FieldContainerRefPtr,0)))
          {
              LUA_BINDING_fail_ptr(L,"pushFieldValue",1,SWIGTYPE_p_OSG__FieldContainerRefPtr);
              return SWIG_arg;
          }
          //Cast arg 2 to a string
          arg2 = (OSG::Char8 *)lua_tostring(L, 2);
          
          //Check that arg1 is not NullFC
          if((*arg1) == NULL)
          {
              lua_pushfstring(L,"Error in pushFieldValue the FieldContainer given is Null");
              lua_error(L);
              return SWIG_arg;
          }
          //Check that the field referenced exists
          OSG::EditFieldHandlePtr TheFieldHandle((*arg1)->editField(arg2));
          if(!TheFieldHandle->isValid())
          {
              lua_pushfstring(L,"Error in pushFieldValue there is no field of name '%s' on type '%s'",arg2,(*arg1)->getTypeName());
              lua_error(L);
              return SWIG_arg;
          }
          if(TheFieldHandle->getCardinality() == OSG::FieldType::SingleField)
          {
              lua_pushfstring(L,"Error in pushFieldValue field of name '%s' on type '%s' is a single-field.  Use setFieldValue instead.",arg2,(*arg1)->getTypeName());
              lua_error(L);
              return SWIG_arg;
          }
          const OSG::DataType& FieldContentType(TheFieldHandle->getType().getContentType());
          //string
          if(FieldContentType == OSG::FieldTraits<std::string>::getType() )
          {
              if(!lua_isstring(L,3))
              {
                  LUA_BINDING_fail_arg(L,"pushFieldValue",3,"string'");
                  return SWIG_arg;
              }
                  static_cast<OSG::MFString*>(TheFieldHandle->getField())->push_back(static_cast<const OSG::Char8*>(lua_tostring(L, 3)));
          }
          //UInt8
          else if(FieldContentType == OSG::FieldTraits<OSG::UInt8>::getType() )
          {
              if(!lua_isnumber(L,3))
              {
                  LUA_BINDING_fail_arg(L,"pushFieldValue",3,"UInt8'");
                  return SWIG_arg;
              }
                  static_cast<OSG::MFUInt8*>(TheFieldHandle->getField())->push_back(static_cast<OSG::UInt8>(lua_tonumber(L, 3)));
          }
          //UInt16
          else if(FieldContentType == OSG::FieldTraits<OSG::UInt16>::getType() )
          {
              if(!lua_isnumber(L,3))
              {
                  LUA_BINDING_fail_arg(L,"pushFieldValue",3,"UInt16'");
                  return SWIG_arg;
              }
                  static_cast<OSG::MFUInt16*>(TheFieldHandle->getField())->push_back(static_cast<OSG::UInt16>(lua_tonumber(L, 3)));
          }
          //UInt32
          else if(FieldContentType == OSG::FieldTraits<OSG::UInt32>::getType())
          {
              if(!lua_isnumber(L,3))
              {
                  LUA_BINDING_fail_arg(L,"pushFieldValue",3,"UInt32'");
                  return SWIG_arg;
              }
                  static_cast<OSG::MFUInt32*>(TheFieldHandle->getField())->push_back(static_cast<OSG::UInt32>(lua_tonumber(L, 3)));
          }
          //UInt64
          else if(FieldContentType == OSG::FieldTraits<OSG::UInt64>::getType() )
          {
              if(!lua_isnumber(L,3))
              {
                  LUA_BINDING_fail_arg(L,"pushFieldValue",3,"UInt64'");
                  return SWIG_arg;
              }
                  static_cast<OSG::MFUInt64*>(TheFieldHandle->getField())->push_back(static_cast<OSG::UInt64>(lua_tonumber(L, 3)));
          }
          //BitVector
          else if(FieldContentType == OSG::FieldTraits<OSG::BitVector, 1>::getType() )
          {
              if(!lua_isnumber(L,3))
              {
                  LUA_BINDING_fail_arg(L,"pushFieldValue",3,"BitVector'");
                  return SWIG_arg;
              }
                  static_cast<OSG::MFBitVector*>(TheFieldHandle->getField())->push_back(static_cast<OSG::BitVector>(lua_tonumber(L, 3)));
          }
          //GLenum
          else if(FieldContentType == OSG::FieldTraits<GLenum, 1>::getType() )
          {
              if(!lua_isnumber(L,3))
              {
                  LUA_BINDING_fail_arg(L,"pushFieldValue",3,"GLenum'");
                  return SWIG_arg;
              }
                  static_cast<OSG::MFGLenum*>(TheFieldHandle->getField())->push_back(static_cast<GLenum>(lua_tonumber(L, 3)));
          }
          //Int8
          else if(FieldContentType == OSG::FieldTraits<OSG::Int8>::getType() )
          {
              if(!lua_isnumber(L,3))
              {
                  LUA_BINDING_fail_arg(L,"pushFieldValue",3,"Int8'");
                  return SWIG_arg;
              }
                  static_cast<OSG::MFInt8*>(TheFieldHandle->getField())->push_back(static_cast<OSG::Int8>(lua_tonumber(L, 3)));
          }
          //Int16
          else if(FieldContentType == OSG::FieldTraits<OSG::Int16>::getType() )
          {
              if(!lua_isnumber(L,3))
              {
                  LUA_BINDING_fail_arg(L,"pushFieldValue",3,"Int16'");
                  return SWIG_arg;
              }
                  static_cast<OSG::MFInt16*>(TheFieldHandle->getField())->push_back(static_cast<OSG::Int16>(lua_tonumber(L, 3)));
          }
          //Int32
          else if(FieldContentType == OSG::FieldTraits<OSG::Int32>::getType() )
          {
              if(!lua_isnumber(L,3))
              {
                  LUA_BINDING_fail_arg(L,"pushFieldValue",3,"Int32'");
                  return SWIG_arg;
              }
                  static_cast<OSG::MFInt32*>(TheFieldHandle->getField())->push_back(static_cast<OSG::Int32>(lua_tonumber(L, 3)));
          }
          //Int64
          else if(FieldContentType == OSG::FieldTraits<OSG::Int64>::getType() )
          {
              if(!lua_isnumber(L,3))
              {
                  LUA_BINDING_fail_arg(L,"pushFieldValue",3,"Int64'");
                  return SWIG_arg;
              }
                  static_cast<OSG::MFInt64*>(TheFieldHandle->getField())->push_back(static_cast<OSG::Int64>(lua_tonumber(L, 3)));
          }
          //Real16
          else if(FieldContentType == OSG::FieldTraits<OSG::Real16>::getType() )
          {
              if(!lua_isnumber(L,3))
              {
                  LUA_BINDING_fail_arg(L,"pushFieldValue",3,"Real16'");
                  return SWIG_arg;
              }
                  static_cast<OSG::MFReal16*>(TheFieldHandle->getField())->push_back(static_cast<OSG::Real16>(lua_tonumber(L, 3)));
          }
          //Real32
          else if(FieldContentType == OSG::FieldTraits<OSG::Real32>::getType() )
          {
              if(!lua_isnumber(L,3))
              {
                  LUA_BINDING_fail_arg(L,"pushFieldValue",3,"Real32'");
                  return SWIG_arg;
              }
                  static_cast<OSG::MFReal32*>(TheFieldHandle->getField())->push_back(static_cast<OSG::Real32>(lua_tonumber(L, 3)));
          }
          //Fixed32
          else if(FieldContentType == OSG::FieldTraits<OSG::Fixed32>::getType() )
          {
              if(!lua_isnumber(L,3))
              {
                  LUA_BINDING_fail_arg(L,"pushFieldValue",3,"Fixed32'");
                  return SWIG_arg;
              }
                  static_cast<OSG::MFFixed32*>(TheFieldHandle->getField())->push_back(OSG::Fixed32(lua_tonumber(L, 3)));
          }
          //Time
          else if(FieldContentType == OSG::FieldTraits<OSG::Time, 1>::getType() )
          {
              if(!lua_isnumber(L,3))
              {
                  LUA_BINDING_fail_arg(L,"pushFieldValue",3,"Time'");
                  return SWIG_arg;
              }
                  static_cast<OSG::MFTime*>(TheFieldHandle->getField())->push_back(static_cast<OSG::Time>(lua_tonumber(L, 3)));
          }
          //Real64
          else if(FieldContentType == OSG::FieldTraits<OSG::Real64>::getType() )
          {
              if(!lua_isnumber(L,3))
              {
                  LUA_BINDING_fail_arg(L,"pushFieldValue",3,"Real64'");
                  return SWIG_arg;
              }
                  static_cast<OSG::MFReal64*>(TheFieldHandle->getField())->push_back(static_cast<OSG::Real64>(lua_tonumber(L, 3)));
          }
          //Color3f
          else if(FieldContentType == OSG::FieldTraits<OSG::Color3f>::getType() )
          {
              OSG::Color3f *arg3 = 0 ;
              if (!SWIG_IsOK(SWIG_ConvertPtr(L,3,(void**)&arg3,SWIGTYPE_p_OSG__Color3f,0))){
                  LUA_BINDING_fail_ptr(L,"pushFieldValue",3,SWIGTYPE_p_OSG__Color3f);
                  return SWIG_arg;
              }
              
                  static_cast<OSG::MFColor3f*>(TheFieldHandle->getField())->push_back(static_cast<OSG::Color3f const &>(*arg3));
          }
          //Color4f
          else if(FieldContentType == OSG::FieldTraits<OSG::Color4f>::getType() )
          {
              OSG::Color4f *arg3 = 0 ;
              if (!SWIG_IsOK(SWIG_ConvertPtr(L,3,(void**)&arg3,SWIGTYPE_p_OSG__Color4f,0))){
                  LUA_BINDING_fail_ptr(L,"pushFieldValue",3,SWIGTYPE_p_OSG__Color4f);
                  return SWIG_arg;
              }
              
                  static_cast<OSG::MFColor4f*>(TheFieldHandle->getField())->push_back(static_cast<OSG::Color4f const &>(*arg3));
          }
          //Vec2f
          else if(FieldContentType == OSG::FieldTraits<OSG::Vec2f>::getType() )
          {
              OSG::Vec2f *arg3 = 0 ;
              if (!SWIG_IsOK(SWIG_ConvertPtr(L,3,(void**)&arg3,SWIGTYPE_p_OSG__Vec2f,0))){
                  LUA_BINDING_fail_ptr(L,"pushFieldValue",3,SWIGTYPE_p_OSG__Vec2f);
                  return SWIG_arg;
              }
              
                  static_cast<OSG::MFVec2f*>(TheFieldHandle->getField())->push_back(static_cast<OSG::Vec2f const &>(*arg3));
          }
          //Vec3f
          else if(FieldContentType == OSG::FieldTraits<OSG::Vec3f>::getType() )
          {
              OSG::Vec3f *arg3 = 0 ;
              if (!SWIG_IsOK(SWIG_ConvertPtr(L,3,(void**)&arg3,SWIGTYPE_p_OSG__Vec3f,0))){
                  LUA_BINDING_fail_ptr(L,"pushFieldValue",3,SWIGTYPE_p_OSG__Vec3f);
                  return SWIG_arg;
              }
              
                  static_cast<OSG::MFVec3f*>(TheFieldHandle->getField())->push_back(static_cast<OSG::Vec3f const &>(*arg3));
          }
          //Vec4f
          else if(FieldContentType == OSG::FieldTraits<OSG::Vec4f>::getType() )
          {
              OSG::Vec4f *arg3 = 0 ;
              if (!SWIG_IsOK(SWIG_ConvertPtr(L,3,(void**)&arg3,SWIGTYPE_p_OSG__Vec4f,0))){
                  LUA_BINDING_fail_ptr(L,"pushFieldValue",3,SWIGTYPE_p_OSG__Vec4f);
                  return SWIG_arg;
              }
              
                  static_cast<OSG::MFVec4f*>(TheFieldHandle->getField())->push_back(static_cast<OSG::Vec4f const &>(*arg3));
          }
          //Pnt2f
          else if(FieldContentType == OSG::FieldTraits<OSG::Pnt2f>::getType() )
          {
              OSG::Pnt2f *arg3 = 0 ;
              if (!SWIG_IsOK(SWIG_ConvertPtr(L,3,(void**)&arg3,SWIGTYPE_p_OSG__Pnt2f,0))){
                  LUA_BINDING_fail_ptr(L,"pushFieldValue",3,SWIGTYPE_p_OSG__Pnt2f);
                  return SWIG_arg;
              }
              
                  static_cast<OSG::MFPnt2f*>(TheFieldHandle->getField())->push_back(static_cast<OSG::Pnt2f const &>(*arg3));
          }
          //Pnt3f
          else if(FieldContentType == OSG::FieldTraits<OSG::Pnt3f>::getType() )
          {
              OSG::Pnt3f *arg3 = 0 ;
              if (!SWIG_IsOK(SWIG_ConvertPtr(L,3,(void**)&arg3,SWIGTYPE_p_OSG__Pnt3f,0))){
                  LUA_BINDING_fail_ptr(L,"pushFieldValue",3,SWIGTYPE_p_OSG__Pnt3f);
                  return SWIG_arg;
              }
              
                  static_cast<OSG::MFPnt3f*>(TheFieldHandle->getField())->push_back(static_cast<OSG::Pnt3f const &>(*arg3));
          }
          //Pnt4f
          else if(FieldContentType == OSG::FieldTraits<OSG::Pnt4f>::getType() )
          {
              OSG::Pnt4f *arg3 = 0 ;
              if (!SWIG_IsOK(SWIG_ConvertPtr(L,3,(void**)&arg3,SWIGTYPE_p_OSG__Pnt4f,0))){
                  LUA_BINDING_fail_ptr(L,"pushFieldValue",3,SWIGTYPE_p_OSG__Pnt4f);
                  return SWIG_arg;
              }
              
                  static_cast<OSG::MFPnt4f*>(TheFieldHandle->getField())->push_back(static_cast<OSG::Pnt4f const &>(*arg3));
          }
          //Matrix
          else if(FieldContentType == OSG::FieldTraits<OSG::Matrix>::getType() )
          {
              OSG::Matrix *arg3 = 0 ;
              if (!SWIG_IsOK(SWIG_ConvertPtr(L,3,(void**)&arg3,SWIGTYPE_p_OSG__Matrix,0))){
                  LUA_BINDING_fail_ptr(L,"pushFieldValue",3,SWIGTYPE_p_OSG__Matrix);
                  return SWIG_arg;
              }
              
                  static_cast<OSG::MFMatrix*>(TheFieldHandle->getField())->push_back(static_cast<OSG::Matrix const &>(*arg3));
          }
          //Quaternion
          else if(FieldContentType == OSG::FieldTraits<OSG::Quaternion>::getType() )
          {
              OSG::Quaternion *arg3 = 0 ;
              if (!SWIG_IsOK(SWIG_ConvertPtr(L,3,(void**)&arg3,SWIGTYPE_p_OSG__Quaternion,0))){
                  LUA_BINDING_fail_ptr(L,"pushFieldValue",3,SWIGTYPE_p_OSG__Quaternion);
                  return SWIG_arg;
              }
              
                  static_cast<OSG::MFQuaternion*>(TheFieldHandle->getField())->push_back(static_cast<OSG::Quaternion const &>(*arg3));
          }
          //FieldContainerRefPtrs
          else if(TheFieldHandle->isPointerField())
          {
              OSG::FieldContainerRefPtr *arg3 = (OSG::FieldContainerRefPtr *) 0 ;
              if (!SWIG_IsOK(SWIG_ConvertPtr(L,3,(void**)&arg3,SWIGTYPE_p_OSG__FieldContainerRefPtr,0)))
              {
                  LUA_BINDING_fail_ptr(L,"pushFieldValue",3,SWIGTYPE_p_OSG__FieldContainerRefPtr);
                  return SWIG_arg;
              }
              //TODO
              switch(TheFieldHandle->getType().getClass())
              {
                  case OSG::FieldType::ChildPtrField:
                       static_cast<OSG::ChildPointerMField <OSG::FieldContainer *,
                                   OSG::UnrecordedRefCountPolicy,1>*>(TheFieldHandle->getField())->push_back(*arg3);
                       break;
                  case OSG::FieldType::ParentPtrField:
                       lua_pushfstring(L,"Error in pushFieldValue the FieldContainer given is of the ParentPtr class.  Cannot set the value of this field directly");
                       lua_error(L);
                       break;
                  case OSG::FieldType::PtrField:
                       static_cast<OSG::MFUnrecFieldContainerPtr*>(TheFieldHandle->getField())->push_back(*arg3);
                       break;
              }
          }
          //bool
          else if(FieldContentType == OSG::FieldTraits<bool, 2>::getType() )
          {
              if(!lua_isboolean(L,3))
              {
                  LUA_BINDING_fail_arg(L,"pushFieldValue",3,"boolean'");
                  return SWIG_arg;
              }
                  static_cast<OSG::MFBool*>(TheFieldHandle->getField())->push_back(static_cast<bool>(lua_toboolean(L, 3)));
          }
          //Volumes
          //Otherwise
          else
          {
              if(!lua_isstring(L,3))
              {
                  LUA_BINDING_fail_arg(L,"pushFieldValue",3,"string'");
                  return SWIG_arg;
              }
                  TheFieldHandle->pushValueFromCString((OSG::Char8 *)lua_tostring(L, 3));
          }

          return SWIG_arg;
    }
    
    int insertFieldValue(lua_State*L) // my native code
    {
        int SWIG_arg = 0;
          OSG::FieldContainerRefPtr *arg1 = (OSG::FieldContainerRefPtr *) 0 ;
          OSG::Char8 *arg2 = (OSG::Char8 *) 0 ;
          OSG::UInt32 arg4 ;
          
          //Check if there are the correct number of arguments
          if (!LUA_BINDING_check_num_args(L,"insertFieldValue",4,4)){ return SWIG_arg;}
          //Check the type of argument 1
          if(!SWIG_isptrtype(L,1))
          {
              LUA_BINDING_fail_arg(L,"insertFieldValue",1,"FieldContainerRefPtr *");
              return SWIG_arg;
          }
          //Check the type of argument 2
          if(!lua_isstring(L,2))
          {
              LUA_BINDING_fail_arg(L,"insertFieldValue",2,"OSG::Char8 const *'");
              return SWIG_arg;
          }
          if(!lua_isnumber(L,4))
          {
              LUA_BINDING_fail_arg(L,"setFieldValue",4,"OSG::UInt32'");
              return SWIG_arg;
          }
              
          //Check the pointer convertion on arg 1
          if (!SWIG_IsOK(SWIG_ConvertPtr(L,1,(void**)&arg1,SWIGTYPE_p_OSG__FieldContainerRefPtr,0)))
          {
              LUA_BINDING_fail_ptr(L,"insertFieldValue",1,SWIGTYPE_p_OSG__FieldContainerRefPtr);
              return SWIG_arg;
          }
          //Cast arg 2 to a string
          arg2 = (OSG::Char8 *)lua_tostring(L, 2);
          arg4 = (OSG::UInt32)lua_tonumber(L, 4);
          
          //Check that arg1 is not NullFC
          if((*arg1) == NULL)
          {
              lua_pushfstring(L,"Error in insertFieldValue the FieldContainer given is Null");
              lua_error(L);
              return SWIG_arg;
          }
          //Check that the field referenced exists
          OSG::EditFieldHandlePtr TheFieldHandle((*arg1)->editField(arg2));
          if(!TheFieldHandle->isValid())
          {
              lua_pushfstring(L,"Error in insertFieldValue there is no field of name '%s' on type '%s'",arg2,(*arg1)->getTypeName());
              lua_error(L);
              return SWIG_arg;
          }
          if(TheFieldHandle->getCardinality() == OSG::FieldType::SingleField)
          {
              lua_pushfstring(L,"Error in insertFieldValue field of name '%s' on type '%s' is a single-field.  Use setFieldValue instead.",arg2,(*arg1)->getTypeName());
              lua_error(L);
              return SWIG_arg;
          }
          //Make sure the index is in range
          if(arg4 > TheFieldHandle->size())
          {
              lua_pushfstring(L,"Error in insertFieldValue: arg4 out of range. Attempted to insert before index: %s, on a field %s of size %s.",arg4,arg2,TheFieldHandle->size());
              lua_error(L);
              return SWIG_arg;
          }
          const OSG::DataType& FieldContentType(TheFieldHandle->getType().getContentType());
          //string
          if(FieldContentType == OSG::FieldTraits<std::string>::getType() )
          {
              if(!lua_isstring(L,3))
              {
                  LUA_BINDING_fail_arg(L,"insertFieldValue",3,"string'");
                  return SWIG_arg;
              }
              OSG::MFString::iterator InsertItor(static_cast<OSG::MFString*>(TheFieldHandle->getField())->begin());
              InsertItor += arg4;
                  static_cast<OSG::MFString*>(TheFieldHandle->getField())->insert(InsertItor, static_cast<const OSG::Char8*>(lua_tostring(L, 3)));
          }
          //UInt8
          else if(FieldContentType == OSG::FieldTraits<OSG::UInt8>::getType() )
          {
              if(!lua_isnumber(L,3))
              {
                  LUA_BINDING_fail_arg(L,"insertFieldValue",3,"UInt8'");
                  return SWIG_arg;
              }
              OSG::MFUInt8::iterator InsertItor(static_cast<OSG::MFUInt8*>(TheFieldHandle->getField())->begin());
              InsertItor += arg4;
                  static_cast<OSG::MFUInt8*>(TheFieldHandle->getField())->insert(InsertItor, static_cast<OSG::UInt8>(lua_tonumber(L, 3)));
          }
          //UInt16
          else if(FieldContentType == OSG::FieldTraits<OSG::UInt16>::getType() )
          {
              if(!lua_isnumber(L,3))
              {
                  LUA_BINDING_fail_arg(L,"insertFieldValue",3,"UInt16'");
                  return SWIG_arg;
              }
              OSG::MFUInt16::iterator InsertItor(static_cast<OSG::MFUInt16*>(TheFieldHandle->getField())->begin());
              InsertItor += arg4;
                  static_cast<OSG::MFUInt16*>(TheFieldHandle->getField())->insert(InsertItor, static_cast<OSG::UInt16>(lua_tonumber(L, 3)));
          }
          //UInt32
          else if(FieldContentType == OSG::FieldTraits<OSG::UInt32>::getType())
          {
              if(!lua_isnumber(L,3))
              {
                  LUA_BINDING_fail_arg(L,"insertFieldValue",3,"UInt32'");
                  return SWIG_arg;
              }
              OSG::MFUInt32::iterator InsertItor(static_cast<OSG::MFUInt32*>(TheFieldHandle->getField())->begin());
              InsertItor += arg4;
                  static_cast<OSG::MFUInt32*>(TheFieldHandle->getField())->insert(InsertItor, static_cast<OSG::UInt32>(lua_tonumber(L, 3)));
          }
          //UInt64
          else if(FieldContentType == OSG::FieldTraits<OSG::UInt64>::getType() )
          {
              if(!lua_isnumber(L,3))
              {
                  LUA_BINDING_fail_arg(L,"insertFieldValue",3,"UInt64'");
                  return SWIG_arg;
              }
              OSG::MFUInt64::iterator InsertItor(static_cast<OSG::MFUInt64*>(TheFieldHandle->getField())->begin());
              InsertItor += arg4;
                  static_cast<OSG::MFUInt64*>(TheFieldHandle->getField())->insert(InsertItor, static_cast<OSG::UInt64>(lua_tonumber(L, 3)));
          }
          //BitVector
          else if(FieldContentType == OSG::FieldTraits<OSG::BitVector, 1>::getType() )
          {
              if(!lua_isnumber(L,3))
              {
                  LUA_BINDING_fail_arg(L,"insertFieldValue",3,"BitVector'");
                  return SWIG_arg;
              }
              OSG::MFBitVector::iterator InsertItor(static_cast<OSG::MFBitVector*>(TheFieldHandle->getField())->begin());
              InsertItor += arg4;
                  static_cast<OSG::MFBitVector*>(TheFieldHandle->getField())->insert(InsertItor, static_cast<OSG::BitVector>(lua_tonumber(L, 3)));
          }
          //GLenum
          else if(FieldContentType == OSG::FieldTraits<GLenum, 1>::getType() )
          {
              if(!lua_isnumber(L,3))
              {
                  LUA_BINDING_fail_arg(L,"insertFieldValue",3,"GLenum'");
                  return SWIG_arg;
              }
              OSG::MFGLenum::iterator InsertItor(static_cast<OSG::MFGLenum*>(TheFieldHandle->getField())->begin());
              InsertItor += arg4;
                  static_cast<OSG::MFGLenum*>(TheFieldHandle->getField())->insert(InsertItor, static_cast<GLenum>(lua_tonumber(L, 3)));
          }
          //Int8
          else if(FieldContentType == OSG::FieldTraits<OSG::Int8>::getType() )
          {
              if(!lua_isnumber(L,3))
              {
                  LUA_BINDING_fail_arg(L,"insertFieldValue",3,"Int8'");
                  return SWIG_arg;
              }
              OSG::MFInt8::iterator InsertItor(static_cast<OSG::MFInt8*>(TheFieldHandle->getField())->begin());
              InsertItor += arg4;
                  static_cast<OSG::MFInt8*>(TheFieldHandle->getField())->insert(InsertItor, static_cast<OSG::Int8>(lua_tonumber(L, 3)));
          }
          //Int16
          else if(FieldContentType == OSG::FieldTraits<OSG::Int16>::getType() )
          {
              if(!lua_isnumber(L,3))
              {
                  LUA_BINDING_fail_arg(L,"insertFieldValue",3,"Int16'");
                  return SWIG_arg;
              }
              OSG::MFInt16::iterator InsertItor(static_cast<OSG::MFInt16*>(TheFieldHandle->getField())->begin());
              InsertItor += arg4;
                  static_cast<OSG::MFInt16*>(TheFieldHandle->getField())->insert(InsertItor, static_cast<OSG::Int16>(lua_tonumber(L, 3)));
          }
          //Int32
          else if(FieldContentType == OSG::FieldTraits<OSG::Int32>::getType() )
          {
              if(!lua_isnumber(L,3))
              {
                  LUA_BINDING_fail_arg(L,"insertFieldValue",3,"Int32'");
                  return SWIG_arg;
              }
              OSG::MFInt32::iterator InsertItor(static_cast<OSG::MFInt32*>(TheFieldHandle->getField())->begin());
              InsertItor += arg4;
                  static_cast<OSG::MFInt32*>(TheFieldHandle->getField())->insert(InsertItor, static_cast<OSG::Int32>(lua_tonumber(L, 3)));
          }
          //Int64
          else if(FieldContentType == OSG::FieldTraits<OSG::Int64>::getType() )
          {
              if(!lua_isnumber(L,3))
              {
                  LUA_BINDING_fail_arg(L,"insertFieldValue",3,"Int64'");
                  return SWIG_arg;
              }
              OSG::MFInt64::iterator InsertItor(static_cast<OSG::MFInt64*>(TheFieldHandle->getField())->begin());
              InsertItor += arg4;
                  static_cast<OSG::MFInt64*>(TheFieldHandle->getField())->insert(InsertItor, static_cast<OSG::Int64>(lua_tonumber(L, 3)));
          }
          //Real16
          else if(FieldContentType == OSG::FieldTraits<OSG::Real16>::getType() )
          {
              if(!lua_isnumber(L,3))
              {
                  LUA_BINDING_fail_arg(L,"insertFieldValue",3,"Real16'");
                  return SWIG_arg;
              }
              OSG::MFReal16::iterator InsertItor(static_cast<OSG::MFReal16*>(TheFieldHandle->getField())->begin());
              InsertItor += arg4;
                  static_cast<OSG::MFReal16*>(TheFieldHandle->getField())->insert(InsertItor, static_cast<OSG::Real16>(lua_tonumber(L, 3)));
          }
          //Real32
          else if(FieldContentType == OSG::FieldTraits<OSG::Real32>::getType() )
          {
              if(!lua_isnumber(L,3))
              {
                  LUA_BINDING_fail_arg(L,"insertFieldValue",3,"Real32'");
                  return SWIG_arg;
              }
              OSG::MFReal32::iterator InsertItor(static_cast<OSG::MFReal32*>(TheFieldHandle->getField())->begin());
              InsertItor += arg4;
                  static_cast<OSG::MFReal32*>(TheFieldHandle->getField())->insert(InsertItor, static_cast<OSG::Real32>(lua_tonumber(L, 3)));
          }
          //Fixed32
          else if(FieldContentType == OSG::FieldTraits<OSG::Fixed32>::getType() )
          {
              if(!lua_isnumber(L,3))
              {
                  LUA_BINDING_fail_arg(L,"insertFieldValue",3,"Fixed32'");
                  return SWIG_arg;
              }
              OSG::MFFixed32::iterator InsertItor(static_cast<OSG::MFFixed32*>(TheFieldHandle->getField())->begin());
              InsertItor += arg4;
                  static_cast<OSG::MFFixed32*>(TheFieldHandle->getField())->insert(InsertItor, OSG::Fixed32(lua_tonumber(L, 3)));
          }
          //Time
          else if(FieldContentType == OSG::FieldTraits<OSG::Time, 1>::getType() )
          {
              if(!lua_isnumber(L,3))
              {
                  LUA_BINDING_fail_arg(L,"insertFieldValue",3,"Time'");
                  return SWIG_arg;
              }
              OSG::MFTime::iterator InsertItor(static_cast<OSG::MFTime*>(TheFieldHandle->getField())->begin());
              InsertItor += arg4;
                  static_cast<OSG::MFTime*>(TheFieldHandle->getField())->insert(InsertItor, static_cast<OSG::Time>(lua_tonumber(L, 3)));
          }
          //Real64
          else if(FieldContentType == OSG::FieldTraits<OSG::Real64>::getType() )
          {
              if(!lua_isnumber(L,3))
              {
                  LUA_BINDING_fail_arg(L,"insertFieldValue",3,"Real64'");
                  return SWIG_arg;
              }
              OSG::MFReal64::iterator InsertItor(static_cast<OSG::MFReal64*>(TheFieldHandle->getField())->begin());
              InsertItor += arg4;
                  static_cast<OSG::MFReal64*>(TheFieldHandle->getField())->insert(InsertItor, static_cast<OSG::Real64>(lua_tonumber(L, 3)));
          }
          //Color3f
          else if(FieldContentType == OSG::FieldTraits<OSG::Color3f>::getType() )
          {
              OSG::Color3f *arg3 = 0 ;
              if (!SWIG_IsOK(SWIG_ConvertPtr(L,3,(void**)&arg3,SWIGTYPE_p_OSG__Color3f,0))){
                  LUA_BINDING_fail_ptr(L,"insertFieldValue",3,SWIGTYPE_p_OSG__Color3f);
                  return SWIG_arg;
              }
              OSG::MFColor3f::iterator InsertItor(static_cast<OSG::MFColor3f*>(TheFieldHandle->getField())->begin());
              InsertItor += arg4;
                  static_cast<OSG::MFColor3f*>(TheFieldHandle->getField())->insert(InsertItor, static_cast<OSG::Color3f const &>(*arg3));
          }
          //Color4f
          else if(FieldContentType == OSG::FieldTraits<OSG::Color4f>::getType() )
          {
              OSG::Color4f *arg3 = 0 ;
              if (!SWIG_IsOK(SWIG_ConvertPtr(L,3,(void**)&arg3,SWIGTYPE_p_OSG__Color4f,0))){
                  LUA_BINDING_fail_ptr(L,"insertFieldValue",3,SWIGTYPE_p_OSG__Color4f);
                  return SWIG_arg;
              }
              OSG::MFColor4f::iterator InsertItor(static_cast<OSG::MFColor4f*>(TheFieldHandle->getField())->begin());
              InsertItor += arg4;
                  static_cast<OSG::MFColor4f*>(TheFieldHandle->getField())->insert(InsertItor, static_cast<OSG::Color4f const &>(*arg3));
          }
          //Vec2f
          else if(FieldContentType == OSG::FieldTraits<OSG::Vec2f>::getType() )
          {
              OSG::Vec2f *arg3 = 0 ;
              if (!SWIG_IsOK(SWIG_ConvertPtr(L,3,(void**)&arg3,SWIGTYPE_p_OSG__Vec2f,0))){
                  LUA_BINDING_fail_ptr(L,"insertFieldValue",3,SWIGTYPE_p_OSG__Vec2f);
                  return SWIG_arg;
              }
              OSG::MFVec2f::iterator InsertItor(static_cast<OSG::MFVec2f*>(TheFieldHandle->getField())->begin());
              InsertItor += arg4;
                  static_cast<OSG::MFVec2f*>(TheFieldHandle->getField())->insert(InsertItor, static_cast<OSG::Vec2f const &>(*arg3));
          }
          //Vec3f
          else if(FieldContentType == OSG::FieldTraits<OSG::Vec3f>::getType() )
          {
              OSG::Vec3f *arg3 = 0 ;
              if (!SWIG_IsOK(SWIG_ConvertPtr(L,3,(void**)&arg3,SWIGTYPE_p_OSG__Vec3f,0))){
                  LUA_BINDING_fail_ptr(L,"insertFieldValue",3,SWIGTYPE_p_OSG__Vec3f);
                  return SWIG_arg;
              }
              OSG::MFVec3f::iterator InsertItor(static_cast<OSG::MFVec3f*>(TheFieldHandle->getField())->begin());
              InsertItor += arg4;
                  static_cast<OSG::MFVec3f*>(TheFieldHandle->getField())->insert(InsertItor, static_cast<OSG::Vec3f const &>(*arg3));
          }
          //Vec4f
          else if(FieldContentType == OSG::FieldTraits<OSG::Vec4f>::getType() )
          {
              OSG::Vec4f *arg3 = 0 ;
              if (!SWIG_IsOK(SWIG_ConvertPtr(L,3,(void**)&arg3,SWIGTYPE_p_OSG__Vec4f,0))){
                  LUA_BINDING_fail_ptr(L,"insertFieldValue",3,SWIGTYPE_p_OSG__Vec4f);
                  return SWIG_arg;
              }
              OSG::MFVec4f::iterator InsertItor(static_cast<OSG::MFVec4f*>(TheFieldHandle->getField())->begin());
              InsertItor += arg4;
                  static_cast<OSG::MFVec4f*>(TheFieldHandle->getField())->insert(InsertItor, static_cast<OSG::Vec4f const &>(*arg3));
          }
          //Pnt2f
          else if(FieldContentType == OSG::FieldTraits<OSG::Pnt2f>::getType() )
          {
              OSG::Pnt2f *arg3 = 0 ;
              if (!SWIG_IsOK(SWIG_ConvertPtr(L,3,(void**)&arg3,SWIGTYPE_p_OSG__Pnt2f,0))){
                  LUA_BINDING_fail_ptr(L,"insertFieldValue",3,SWIGTYPE_p_OSG__Pnt2f);
                  return SWIG_arg;
              }
              OSG::MFPnt2f::iterator InsertItor(static_cast<OSG::MFPnt2f*>(TheFieldHandle->getField())->begin());
              InsertItor += arg4;
                  static_cast<OSG::MFPnt2f*>(TheFieldHandle->getField())->insert(InsertItor, static_cast<OSG::Pnt2f const &>(*arg3));
          }
          //Pnt3f
          else if(FieldContentType == OSG::FieldTraits<OSG::Pnt3f>::getType() )
          {
              OSG::Pnt3f *arg3 = 0 ;
              if (!SWIG_IsOK(SWIG_ConvertPtr(L,3,(void**)&arg3,SWIGTYPE_p_OSG__Pnt3f,0))){
                  LUA_BINDING_fail_ptr(L,"insertFieldValue",3,SWIGTYPE_p_OSG__Pnt3f);
                  return SWIG_arg;
              }
              OSG::MFPnt3f::iterator InsertItor(static_cast<OSG::MFPnt3f*>(TheFieldHandle->getField())->begin());
              InsertItor += arg4;
                  static_cast<OSG::MFPnt3f*>(TheFieldHandle->getField())->insert(InsertItor, static_cast<OSG::Pnt3f const &>(*arg3));
          }
          //Pnt4f
          else if(FieldContentType == OSG::FieldTraits<OSG::Pnt4f>::getType() )
          {
              OSG::Pnt4f *arg3 = 0 ;
              if (!SWIG_IsOK(SWIG_ConvertPtr(L,3,(void**)&arg3,SWIGTYPE_p_OSG__Pnt4f,0))){
                  LUA_BINDING_fail_ptr(L,"insertFieldValue",3,SWIGTYPE_p_OSG__Pnt4f);
                  return SWIG_arg;
              }
              OSG::MFPnt4f::iterator InsertItor(static_cast<OSG::MFPnt4f*>(TheFieldHandle->getField())->begin());
              InsertItor += arg4;
                  static_cast<OSG::MFPnt4f*>(TheFieldHandle->getField())->insert(InsertItor, static_cast<OSG::Pnt4f const &>(*arg3));
          }
          //Matrix
          else if(FieldContentType == OSG::FieldTraits<OSG::Matrix>::getType() )
          {
              OSG::Matrix *arg3 = 0 ;
              if (!SWIG_IsOK(SWIG_ConvertPtr(L,3,(void**)&arg3,SWIGTYPE_p_OSG__Matrix,0))){
                  LUA_BINDING_fail_ptr(L,"insertFieldValue",3,SWIGTYPE_p_OSG__Matrix);
                  return SWIG_arg;
              }
              OSG::MFMatrix::iterator InsertItor(static_cast<OSG::MFMatrix*>(TheFieldHandle->getField())->begin());
              InsertItor += arg4;
                  static_cast<OSG::MFMatrix*>(TheFieldHandle->getField())->insert(InsertItor, static_cast<OSG::Matrix const &>(*arg3));
          }
          //Quaternion
          else if(FieldContentType == OSG::FieldTraits<OSG::Quaternion>::getType() )
          {
              OSG::Quaternion *arg3 = 0 ;
              if (!SWIG_IsOK(SWIG_ConvertPtr(L,3,(void**)&arg3,SWIGTYPE_p_OSG__Quaternion,0))){
                  LUA_BINDING_fail_ptr(L,"insertFieldValue",3,SWIGTYPE_p_OSG__Quaternion);
                  return SWIG_arg;
              }
              OSG::MFQuaternion::iterator InsertItor(static_cast<OSG::MFQuaternion*>(TheFieldHandle->getField())->begin());
              InsertItor += arg4;
                  static_cast<OSG::MFQuaternion*>(TheFieldHandle->getField())->insert(InsertItor, static_cast<OSG::Quaternion const &>(*arg3));
          }
          //FieldContainerRefPtrs
          else if(TheFieldHandle->isPointerField())
          {
              OSG::FieldContainerRefPtr *arg3 = (OSG::FieldContainerRefPtr *) 0 ;
              if (!SWIG_IsOK(SWIG_ConvertPtr(L,3,(void**)&arg3,SWIGTYPE_p_OSG__FieldContainerRefPtr,0)))
              {
                  LUA_BINDING_fail_ptr(L,"insertFieldValue",3,SWIGTYPE_p_OSG__FieldContainerRefPtr);
                  return SWIG_arg;
              }
              //TODO
              switch(TheFieldHandle->getType().getClass())
              {
                  case OSG::FieldType::ChildPtrField:
                  {
                       OSG::ChildPointerMField <OSG::FieldContainer *,
                                   OSG::UnrecordedRefCountPolicy,1>::iterator InsertItor(static_cast<OSG::ChildPointerMField <OSG::FieldContainer *,
                                   OSG::UnrecordedRefCountPolicy,1>*>(TheFieldHandle->getField())->begin());
                       InsertItor += arg4;
                       static_cast<OSG::ChildPointerMField <OSG::FieldContainer *,
                                   OSG::UnrecordedRefCountPolicy,1>*>(TheFieldHandle->getField())->insert(InsertItor, *arg3);
                  }
                       break;
                  case OSG::FieldType::ParentPtrField:
                       lua_pushfstring(L,"Error in insertFieldValue the FieldContainer given is of the ParentPtr class.  Cannot set the value of this field directly");
                       lua_error(L);
                       break;
                  case OSG::FieldType::PtrField:
                  {
                       OSG::MFUnrecFieldContainerPtr::iterator InsertItor(static_cast<OSG::MFUnrecFieldContainerPtr*>(TheFieldHandle->getField())->begin());
                       InsertItor += arg4;
                       static_cast<OSG::MFUnrecFieldContainerPtr*>(TheFieldHandle->getField())->insert(InsertItor, *arg3);
                  }
                       break;
              }
          }
          //bool
          else if(FieldContentType == OSG::FieldTraits<bool, 2>::getType() )
          {
              if(!lua_isboolean(L,3))
              {
                  LUA_BINDING_fail_arg(L,"insertFieldValue",3,"boolean'");
                  return SWIG_arg;
              }
              OSG::MFBool::iterator InsertItor(static_cast<OSG::MFBool*>(TheFieldHandle->getField())->begin());
              InsertItor += arg4;
                  static_cast<OSG::MFBool*>(TheFieldHandle->getField())->insert(InsertItor, static_cast<bool>(lua_toboolean(L, 3)));
          }
          //Volumes
          //Otherwise
          else
          {
              lua_pushfstring(L,"Error in insertFieldValue field of name '%s' on type '%s', could not insert the value of the multi-field because that type is not supported in this biding.",arg2,(*arg1)->getTypeName());
              lua_error(L);
          }

          return SWIG_arg;
    }
%}

namespace OSG {

    class FieldDescription;
    class FieldContainerRefPtr;
    class FieldContainerType;
    class FieldContainer;
    class AttachmentContainer;
    class Attachment;
    class AttachmentRefPtr;
    class AttachmentContainerRefPtr;
    class NodeRefPtr;
    class NodeCoreRefPtr;
    class Node;
    class Viewport;
    class ViewportRefPtr;
    class Camera;
    class CameraRefPtr;
    class Image;
    class ImageRefPtr;
    class WindowRefPtr;
    class Matrix;
    class BoxVolume;
    class EventProducerType;

    class EventProducer
    {
      public:

        //Attaching Activities
        /*EventConnection attachActivity(ActivityPtr TheActivity, UInt32 ProducedEventId);*/
        /*bool isActivityAttached(ActivityPtr TheActivity, UInt32 ProducedEventId) const;*/
        UInt32 getNumActivitiesAttached(UInt32 ProducedEventId) const;
        /*ActivityPtr getAttachedActivity(UInt32 ProducedEventId, UInt32 ActivityIndex) const;*/
        /*void detachActivity(ActivityPtr TheActivity, UInt32 ProducedEventId);*/

        /*EventConnection attachActivity(ActivityPtr TheActivity, const Char8 *ProducedEventName);*/
        /*bool isActivityAttached(ActivityPtr TheActivity, const Char8 *ProducedEventName) const;*/
        UInt32 getNumActivitiesAttached(const Char8 *ProducedEventName) const;
        /*ActivityPtr getAttachedActivity(const Char8 *ProducedEventName, UInt32 ActivityIndex) const;*/
        /*void detachActivity(ActivityPtr TheActivity, const Char8 *ProducedEventName);*/
        void detachAllActivities(void);
        UInt32 getNumAttachedActivities(void) const;

        //Attaching EventListeners
        /*EventConnection attachEventListener(EventListenerPtr TheEventListener, UInt32 ProducedEventId);*/
        /*bool isEventListenerAttached(EventListenerPtr TheEventListener, UInt32 ProducedEventId) const;*/
        UInt32 getNumEventListenersAttached(UInt32 ProducedEventId) const;
        /*EventListenerPtr getAttachedEventListener(UInt32 ProducedEventId, UInt32 EventListenerIndex) const;*/
        /*void detachEventListener(EventListenerPtr TheEventListener, UInt32 ProducedEventId);*/

        /*EventConnection attachEventListener(EventListenerPtr TheEventListener, const Char8 *ProducedEventName);*/
        /*bool isEventListenerAttached(EventListenerPtr TheEventListener, const Char8 *ProducedEventName) const;*/
        UInt32 getNumEventListenersAttached(const Char8 *ProducedEventName) const;
        /*EventListenerPtr getAttachedEventListener(const Char8 *ProducedEventName, UInt32 EventListenerIndex) const;*/
        /*void detachEventListener(EventListenerPtr TheEventListener, const Char8 *ProducedEventName);*/
        void detachAllEventListeners(void);
        UInt32 getNumAttachedEventListeners(void) const;


        /*const EventProducerType &getProducerType(void) const;*/

        UInt32 getNumProducedEvents(void) const;
        /*const MethodDescription *getProducedEventDescription(const Char8 *ProducedEventName) const;*/
        /*const MethodDescription *getProducedEventDescription(UInt32 ProducedEventId) const;*/
        UInt32 getProducedEventId(const Char8 *ProducedEventName) const;

        /*static const EventProducerType &getProducerClassType(void);*/
        static UInt32                   getProducerClassTypeId(void);

        //EventProducer(const EventProducerType* TheProducerType);
         ~EventProducer(void);

        
      protected:
        EventProducer(const EventProducer &source);
      private:

        void operator =(const EventProducer &source);
    };

    typedef EventProducer *EventProducerPtr;
    /******************************************************/
    /*              FieldDescription                    */
    /******************************************************/
    class FieldDescriptionBase
    {
      public :



        virtual ~FieldDescriptionBase(void);

          std::string  getName        (void                        ) const;

          std::string  getDocumentation (void                      ) const;

              UInt32     getTypeId      (void                ) const; 

              BitVector  getFieldMask   (void                ) const;
              void       setFieldMask   (BitVector vFieldMask);

              UInt32     getFieldId     (void                ) const;
              void       setFieldId     (UInt32 uiFieldId    );

        const TypeBase  &getFieldType   (void                ) const;

              bool       isInternal     (void                ) const;

          UInt32       getFlags       (void                        ) const;

              bool       isValid        (void                ) const;
          bool         isSField       (void                        ) const;
          bool         isMField       (void                        ) const;

        /*EditFieldHandlePtr editField(      ReflexiveContainer &oContainer) const;*/
        /*GetFieldHandlePtr  getField (const ReflexiveContainer &oContainer) const;*/
      protected:
        FieldDescriptionBase(const FieldDescriptionBase &source                     );
    };
    
    /******************************************************/
    /*              Event Connection                      */
    /******************************************************/
    class EventConnection
    {
      public:
          EventConnection(void);
          
          EventConnection(const EventConnection& c);
    
          const EventConnection& operator=(const EventConnection& c);
    
          bool isValid(void) const;
    
          bool isConnected(void) const;
    
          void disconnect(void);
    
    };
    
    /******************************************************/
    /*              MethodDescription                      */
    /******************************************************/
    class MethodDescription
    {
      public:
        const Char8        *getCName       (void                ) const;
    
              UInt32     getMethodId       (void                ) const;
    
        const TypeBase& getEventArgumentType   (void                ) const;
      protected:
          MethodDescription(void);
    };
    
    /******************************************************/
    /*              EventProducerType                     */
    /******************************************************/
    class EventProducerType : public TypeBase
    {
      public:
    
        UInt16              getGroupId(void) const;
        EventProducerType *getParent (void) const;
    
              MethodDescription *getMethodDescription (UInt32 uiMethodId);
        const MethodDescription *getMethodDescription (UInt32 uiMethodId) const;
    
              MethodDescription *findMethodDescription(const Char8 *szMethodName);
    
        const MethodDescription *findMethodDescription(
            const Char8 *szMethodName) const;
    
        UInt32                 getNumMethodDescs(void) const;
    
        bool isAbstract   (void                           ) const;
    
        bool isDerivedFrom(const TypeBase           &other) const;
        bool isDerivedFrom(const EventProducerType &other) const;
      protected:
          EventProducerType(void); 
    };

    /******************************************************/
    /*              FieldContainerRefPtr                    */
    /******************************************************/
    class FieldContainerRefPtr
    {
      public:

        FieldContainer *operator->(void);

        FieldContainerRefPtr(      void                         );
        /*FieldContainerRefPtr(const NullFieldContainerRefPtr &      );*/
        FieldContainerRefPtr(const FieldContainerRefPtr     &source);

        ~FieldContainerRefPtr(void);

    };
    %extend FieldContainerRefPtr
    {
        FieldContainerRefPtr getFCPtr(void) throw(const char *)
        {
            return (*$self);
        }
        
        void setName(Char8* NewName) throw(const char *)
        {
            OSG::AttachmentContainerRefPtr AsAttachmentContainer(OSG::dynamic_pointer_cast<OSG::AttachmentContainer>(*$self));
            if(AsAttachmentContainer == NULL)
            {
                throw("Error in setName: must be called on an AttachmentContainer.");
            }
            OSG::setName(AsAttachmentContainer, NewName);
        }

        const Char8* getName(void) throw(const char *)
        {
            OSG::AttachmentContainerRefPtr AsAttachmentContainer(OSG::dynamic_pointer_cast<OSG::AttachmentContainer>(*$self));
            if(AsAttachmentContainer == NULL)
            {
                throw("Error in setName: must be called on an AttachmentContainer.");
            }
            return OSG::getName(AsAttachmentContainer);
        }
        
        bool operator==(const Int32& val) throw(const char *)
        {
            return (val == 0 && (*$self) == NULL);
        }
        
        FieldType::Cardinality getFieldCardinality(Char8* FieldName) throw(const char *)
        {
              //Check that the field referenced exists
              OSG::GetFieldHandlePtr TheFieldHandle((*$self)->getField(FieldName));
              if(!TheFieldHandle->isValid())
              {
                  std::string ErrorString = "Error in getFieldCardinality: there is no field of name '";
                  ErrorString += FieldName;
                  ErrorString += "' on type '";
                  ErrorString += (*$self)->getTypeName();
                  ErrorString += "'";
                  throw(ErrorString.c_str());
              }
              return TheFieldHandle->getCardinality();
        }
        
        FieldContainerRefPtr deepClone(const std::string& shareString) throw(const char *)
        {
            return OSG::deepClone((*$self), shareString);
        }
        
        UInt32 getFieldSize(Char8* FieldName) throw(const char *)
        {
              //Check that the field referenced exists
              OSG::GetFieldHandlePtr TheFieldHandle((*$self)->getField(FieldName));
              if(!TheFieldHandle->isValid())
              {
                  std::string ErrorString = "Error in getFieldSize: there is no field of name '";
                  ErrorString += FieldName;
                  ErrorString += "' on type '";
                  ErrorString += (*$self)->getTypeName();
                  ErrorString += "'";
                  throw(ErrorString.c_str());
              }
              return TheFieldHandle->size();
        }
        
        void clearField(Char8* FieldName) throw(const char *)
        {
              //Check that the field referenced exists
              OSG::EditFieldHandlePtr TheFieldHandle((*$self)->editField(FieldName));
              if(!TheFieldHandle->isValid())
              {
                  std::string ErrorString = "Error in clear there is no field of name '";
                  ErrorString += FieldName;
                  ErrorString += "' on type '";
                  ErrorString += (*$self)->getTypeName();
                  ErrorString += "'";
                  throw(ErrorString.c_str());
              }
              //Make sure its a MultiField
              if(TheFieldHandle->getCardinality() == OSG::FieldType::SingleField)
              {
                  std::string ErrorString = "Error in clearField: field of name '";
                  ErrorString += FieldName;
                  ErrorString += "' on type '";
                  ErrorString += (*$self)->getTypeName();
                  ErrorString += "' is a single-field,  clearField: cannot be used on it.";
                  throw(ErrorString.c_str());
              }
              const OSG::DataType& FieldContentType(TheFieldHandle->getType().getContentType());
              //string
              if(FieldContentType == OSG::FieldTraits<std::string>::getType() )
              {
                  static_cast<OSG::MFString*>(TheFieldHandle->getField())->clear();
              }
              //Bool
              else if(FieldContentType == OSG::FieldTraits<bool, 2>::getType() )
              {
                      static_cast<OSG::MFBool*>(TheFieldHandle->getField())->clear();
              }
              //UInt8
              else if(FieldContentType == OSG::FieldTraits<OSG::UInt8>::getType() )
              {
                      static_cast<OSG::MFUInt8*>(TheFieldHandle->getField())->clear();
              }
              //UInt16
              else if(FieldContentType == OSG::FieldTraits<OSG::UInt16>::getType() )
              {
                      static_cast<OSG::MFUInt16*>(TheFieldHandle->getField())->clear();
              }
              //UInt32
              else if(FieldContentType == OSG::FieldTraits<OSG::UInt32>::getType()) 
              {
                      static_cast<OSG::MFUInt32*>(TheFieldHandle->getField())->clear();
              }
              //UInt64
              else if(FieldContentType == OSG::FieldTraits<OSG::UInt64>::getType() )
              {
                      static_cast<OSG::MFUInt64*>(TheFieldHandle->getField())->clear();
              }
              //BitVector
              else if(FieldContentType == OSG::FieldTraits<OSG::BitVector,1>::getType() )
              {
                      static_cast<OSG::MFBitVector*>(TheFieldHandle->getField())->clear();
              }
              //GLenum
              else if(FieldContentType == OSG::FieldTraits<GLenum,1>::getType() )
              {
                      static_cast<OSG::MFGLenum*>(TheFieldHandle->getField())->clear();
              }
              //Int8
              else if(FieldContentType == OSG::FieldTraits<OSG::Int8>::getType() )
              {
                      static_cast<OSG::MFInt8*>(TheFieldHandle->getField())->clear();
              }
              //Int16
              else if(FieldContentType == OSG::FieldTraits<OSG::Int16>::getType() )
              {
                      static_cast<OSG::MFInt16*>(TheFieldHandle->getField())->clear();
              }
              //Int32
              else if(FieldContentType == OSG::FieldTraits<OSG::Int32>::getType() )
              {
                      static_cast<OSG::MFInt32*>(TheFieldHandle->getField())->clear();
              }
              //Int64
              else if(FieldContentType == OSG::FieldTraits<OSG::Int64>::getType() )
              {
                      static_cast<OSG::MFInt64*>(TheFieldHandle->getField())->clear();
              }
              //Real16
              else if(FieldContentType == OSG::FieldTraits<OSG::Real16>::getType() )
              {
                      static_cast<OSG::MFReal16*>(TheFieldHandle->getField())->clear();
              }
              //Real32
              else if(FieldContentType == OSG::FieldTraits<OSG::Real32>::getType() )
              {
                      static_cast<OSG::MFReal32*>(TheFieldHandle->getField())->clear();
              }
              //Fixed32
              else if(FieldContentType == OSG::FieldTraits<OSG::Fixed32>::getType() )
              {
                      static_cast<OSG::MFFixed32*>(TheFieldHandle->getField())->clear();
              }
              //Time
              else if(FieldContentType == OSG::FieldTraits<OSG::Time,1>::getType() )
              {
                      static_cast<OSG::MFTime*>(TheFieldHandle->getField())->clear();
              }
              //Real64
              else if(FieldContentType == OSG::FieldTraits<OSG::Real64>::getType() )
              {
                      static_cast<OSG::MFReal64*>(TheFieldHandle->getField())->clear();
              }
              //Color3f
              else if(FieldContentType == OSG::FieldTraits<OSG::Color3f>::getType() )
              {
                      static_cast<OSG::MFColor3f*>(TheFieldHandle->getField())->clear();
              }
              //Color4f
              else if(FieldContentType == OSG::FieldTraits<OSG::Color4f>::getType() )
              {
                      static_cast<OSG::MFColor4f*>(TheFieldHandle->getField())->clear();
              }
              //Vec2f
              else if(FieldContentType == OSG::FieldTraits<OSG::Vec2f>::getType() )
              {
                      static_cast<OSG::MFVec2f*>(TheFieldHandle->getField())->clear();
              }
              //Vec3f
              else if(FieldContentType == OSG::FieldTraits<OSG::Vec3f>::getType() )
              {
                      static_cast<OSG::MFVec3f*>(TheFieldHandle->getField())->clear();
              }
              //Vec4f
              else if(FieldContentType == OSG::FieldTraits<OSG::Vec4f>::getType() )
              {
                      static_cast<OSG::MFVec4f*>(TheFieldHandle->getField())->clear();
              }
              //Pnt2f
              else if(FieldContentType == OSG::FieldTraits<OSG::Pnt2f>::getType() )
              {
                      static_cast<OSG::MFPnt2f*>(TheFieldHandle->getField())->clear();
              }
              //Pnt3f
              else if(FieldContentType == OSG::FieldTraits<OSG::Pnt3f>::getType() )
              {
                      static_cast<OSG::MFPnt3f*>(TheFieldHandle->getField())->clear();
              }
              //Pnt4f
              else if(FieldContentType == OSG::FieldTraits<OSG::Pnt4f>::getType() )
              {
                      static_cast<OSG::MFPnt4f*>(TheFieldHandle->getField())->clear();
              }
              //Matrix
              else if(FieldContentType == OSG::FieldTraits<OSG::Matrix>::getType() )
              {
                      static_cast<OSG::MFMatrix*>(TheFieldHandle->getField())->clear();
              }
              //Quaternion
              else if(FieldContentType == OSG::FieldTraits<OSG::Quaternion>::getType() )
              {
                      static_cast<OSG::MFQuaternion*>(TheFieldHandle->getField())->clear();
              }
              //FieldContainerRefPtrs
              else if(TheFieldHandle->isPointerField())
              {
                  switch(TheFieldHandle->getType().getClass())
                  {
                      case OSG::FieldType::ChildPtrField:
                           static_cast<OSG::ChildPointerMField <OSG::FieldContainer *,
                                       OSG::UnrecordedRefCountPolicy,1>*>(TheFieldHandle->getField())->clear();
                           break;
                      case OSG::FieldType::ParentPtrField:
              {
                  std::string ErrorString = "Error in clearField the FieldContainer given is of the ParentPtr class.  Cannot set the value of this field directly";
                           throw(ErrorString.c_str());
              }
                           break;
                      case OSG::FieldType::PtrField:
                           static_cast<OSG::MFUnrecFieldContainerPtr*>(TheFieldHandle->getField())->clear();
                           break;
                  }
              }
              //Volumes
              //Otherwise
              else
              {
                  std::string ErrorString = "Error in clearField: field of name '";
                  ErrorString += FieldName;
                  ErrorString += "' on type '";
                  ErrorString += (*$self)->getTypeName();
                  ErrorString += "' There is no clear method defined for this field type.";
                  throw(ErrorString.c_str());
              }
        }
        
        void removeFieldValue(Char8* FieldName, UInt32 Index) throw(const char *)
        {
              OSG::EditFieldHandlePtr TheFieldHandle((*$self)->editField(FieldName));
              if(!TheFieldHandle->isValid())
              {
                  std::string ErrorString = "Error in removeFieldValue: there is no field of name '";
                  ErrorString += FieldName;
                  ErrorString += "' on type '";
                  ErrorString += (*$self)->getTypeName();
                  ErrorString += "'";
                  throw(ErrorString.c_str());
              }
              if(TheFieldHandle->getCardinality() == OSG::FieldType::SingleField)
              {
                  std::string ErrorString = "Error in removeFieldValue: field of name '";
                  ErrorString += FieldName;
                  ErrorString += "' on type '";
                  ErrorString += (*$self)->getTypeName();
                  ErrorString += "' is a single-field,  removeFieldValue cannot be used on it.";
                  throw(ErrorString.c_str());
              }
              //Make sure the index is in range
              if(Index >= TheFieldHandle->size())
              {
                  std::string ErrorString = "Error in removeFieldValue: Index out of range.  Attempted to remove index: .";
                  //ErrorString += ;
                  //ErrorString += ", where the size is ";
                  //ErrorString += ;
                  throw("Error in removeFieldValue: Index out of range.  Attempted to remove index: .");
              }
              const OSG::DataType& FieldContentType(TheFieldHandle->getType().getContentType());
              //string
              if(FieldContentType == OSG::FieldTraits<std::string>::getType() )
              {
                  static_cast<OSG::MFString*>(TheFieldHandle->getField())->erase(Index);
              }
              //UInt8
              else if(FieldContentType == OSG::FieldTraits<OSG::UInt8>::getType() )
              {
                      static_cast<OSG::MFUInt8*>(TheFieldHandle->getField())->erase(Index);
              }
              //UInt32
              else if(FieldContentType == OSG::FieldTraits<OSG::UInt32>::getType()) 
              {
                      static_cast<OSG::MFUInt32*>(TheFieldHandle->getField())->erase(Index);
              }
              //UInt64
              else if(FieldContentType == OSG::FieldTraits<OSG::UInt64>::getType() )
              {
                      static_cast<OSG::MFUInt64*>(TheFieldHandle->getField())->erase(Index);
              }
              //BitVector
              else if(FieldContentType == OSG::FieldTraits<OSG::BitVector, 1>::getType() )
              {
                      static_cast<OSG::MFBitVector*>(TheFieldHandle->getField())->erase(Index);
              }
              //GLenum
              else if(FieldContentType == OSG::FieldTraits<GLenum, 1>::getType() )
              {
                      static_cast<OSG::MFGLenum*>(TheFieldHandle->getField())->erase(Index);
              }
              //Int8
              else if(FieldContentType == OSG::FieldTraits<OSG::Int8>::getType() )
              {
                      static_cast<OSG::MFInt8*>(TheFieldHandle->getField())->erase(Index);
              }
              //Int16
              else if(FieldContentType == OSG::FieldTraits<OSG::Int16>::getType() )
              {
                      static_cast<OSG::MFInt16*>(TheFieldHandle->getField())->erase(Index);
              }
              //Int32
              else if(FieldContentType == OSG::FieldTraits<OSG::Int32>::getType() )
              {
                      static_cast<OSG::MFInt32*>(TheFieldHandle->getField())->erase(Index);
              }
              //Int64
              else if(FieldContentType == OSG::FieldTraits<OSG::Int64>::getType() )
              {
                      static_cast<OSG::MFInt64*>(TheFieldHandle->getField())->erase(Index);
              }
              //Real16
              else if(FieldContentType == OSG::FieldTraits<OSG::Real16>::getType() )
              {
                      static_cast<OSG::MFReal16*>(TheFieldHandle->getField())->erase(Index);
              }
              //Real32
              else if(FieldContentType == OSG::FieldTraits<OSG::Real32>::getType() )
              {
                      static_cast<OSG::MFReal32*>(TheFieldHandle->getField())->erase(Index);
              }
              //Fixed32
              else if(FieldContentType == OSG::FieldTraits<OSG::Fixed32>::getType() )
              {
                      static_cast<OSG::MFFixed32*>(TheFieldHandle->getField())->erase(Index);
              }
              //Time
              else if(FieldContentType == OSG::FieldTraits<OSG::Time, 1>::getType() )
              {
                      static_cast<OSG::MFTime*>(TheFieldHandle->getField())->erase(Index);
              }
              //Real64
              else if(FieldContentType == OSG::FieldTraits<OSG::Real64>::getType() )
              {
                      static_cast<OSG::MFReal64*>(TheFieldHandle->getField())->erase(Index);
              }
              //Color3f
              else if(FieldContentType == OSG::FieldTraits<OSG::Color3f>::getType() )
              {
                      static_cast<OSG::MFColor3f*>(TheFieldHandle->getField())->erase(Index);
              }
              //Color4f
              else if(FieldContentType == OSG::FieldTraits<OSG::Color4f>::getType() )
              {
                      static_cast<OSG::MFColor4f*>(TheFieldHandle->getField())->erase(Index);
              }
              //Vec2f
              else if(FieldContentType == OSG::FieldTraits<OSG::Vec2f>::getType() )
              {
                      static_cast<OSG::MFVec2f*>(TheFieldHandle->getField())->erase(Index);
              }
              //Vec3f
              else if(FieldContentType == OSG::FieldTraits<OSG::Vec3f>::getType() )
              {
                      static_cast<OSG::MFVec3f*>(TheFieldHandle->getField())->erase(Index);
              }
              //Vec4f
              else if(FieldContentType == OSG::FieldTraits<OSG::Vec4f>::getType() )
              {
                      static_cast<OSG::MFVec4f*>(TheFieldHandle->getField())->erase(Index);
              }
              //Pnt2f
              else if(FieldContentType == OSG::FieldTraits<OSG::Pnt2f>::getType() )
              {
                      static_cast<OSG::MFPnt2f*>(TheFieldHandle->getField())->erase(Index);
              }
              //Pnt3f
              else if(FieldContentType == OSG::FieldTraits<OSG::Pnt3f>::getType() )
              {
                      static_cast<OSG::MFPnt3f*>(TheFieldHandle->getField())->erase(Index);
              }
              //Pnt4f
              else if(FieldContentType == OSG::FieldTraits<OSG::Pnt4f>::getType() )
              {
                      static_cast<OSG::MFPnt4f*>(TheFieldHandle->getField())->erase(Index);
              }
              //Matrix
              else if(FieldContentType == OSG::FieldTraits<OSG::Matrix>::getType() )
              {
                      static_cast<OSG::MFMatrix*>(TheFieldHandle->getField())->erase(Index);
              }
              //Quaternion
              else if(FieldContentType == OSG::FieldTraits<OSG::Quaternion>::getType() )
              {
                      static_cast<OSG::MFQuaternion*>(TheFieldHandle->getField())->erase(Index);
              }
              //FieldContainerRefPtrs
              else if(TheFieldHandle->isPointerField())
              {
                  //TODO
                  switch(TheFieldHandle->getType().getClass())
                  {
                      case OSG::FieldType::ChildPtrField:
                           static_cast<OSG::ChildPointerMField <OSG::FieldContainer *,
                                       OSG::UnrecordedRefCountPolicy,1>*>(TheFieldHandle->getField())->erase(Index);
                           break;
                      case OSG::FieldType::ParentPtrField:
              {
                  std::string ErrorString = "Error in removeFieldValue the FieldContainer given is of the ParentPtr class.  Cannot set the value of this field directly";
                  throw(ErrorString.c_str());
              }
                           break;
                      case OSG::FieldType::PtrField:
                           static_cast<OSG::MFUnrecFieldContainerPtr*>(TheFieldHandle->getField())->erase(Index);
                           break;
                  }
              }
              //bool
              else if(FieldContentType == OSG::FieldTraits<bool, 2>::getType() )
              {
                      static_cast<OSG::MFBool*>(TheFieldHandle->getField())->erase(Index);
              }
              //Volumes
              //Otherwise
              else
              {
                  std::string ErrorString = "Error in clear field of name '";
                  ErrorString += FieldName;
                  ErrorString += "' on type '";
                  ErrorString += (*$self)->getTypeName();
                  ErrorString += "' There is no clear method defined for this field type.";
                  throw(ErrorString.c_str());
              }
        }

        EventConnection attachActivity(FieldContainerRefPtr TheActivity, const Char8 *ProducedEventName)
        {
            if(!OSG::isEventProducer(*$self))
            {
                  std::string ErrorString = "Cannot call attachActivity on FieldContainer of type '";
                  ErrorString += (*$self)->getTypeName();
                  ErrorString += "', because it is not an EventProducer.'";
                  throw(ErrorString.c_str());
            }

            if(!TheActivity->getType().isDerivedFrom(OSG::Activity::getClassType()))
            {
                  std::string ErrorString = "Cannot call attachActivity with Argument 1 of type '";
                  ErrorString += TheActivity->getTypeName();
                  ErrorString += "', because it is not derived from Activity.'";
                  throw(ErrorString.c_str());
            }

            OSG::EventProducerPtr ProdField = OSG::getEventProducer(*$self);
            
            return ProdField->attachActivity(OSG::dynamic_pointer_cast<OSG::Activity>(TheActivity),ProducedEventName);
        }

        bool isActivityAttached(FieldContainerRefPtr TheActivity, const Char8 *ProducedEventName) const
        {
            if(!OSG::isEventProducer(*$self))
            {
                  std::string ErrorString = "Cannot call isActivityAttached on FieldContainer of type '";
                  ErrorString += (*$self)->getTypeName();
                  ErrorString += "', because it is not an EventProducer.'";
                  throw(ErrorString.c_str());
            }

            if(!TheActivity->getType().isDerivedFrom(OSG::Activity::getClassType()))
            {
                  std::string ErrorString = "Cannot call isActivityAttached with Argument 1 of type '";
                  ErrorString += TheActivity->getTypeName();
                  ErrorString += "', because it is not derived from Activity.'";
                  throw(ErrorString.c_str());
            }

            OSG::EventProducerPtr ProdField = OSG::getEventProducer(*$self);
            
            return ProdField->isActivityAttached(OSG::dynamic_pointer_cast<OSG::Activity>(TheActivity),ProducedEventName);
        }

        UInt32 getNumActivitiesAttached(const Char8 *ProducedEventName) const
        {
            if(!OSG::isEventProducer(*$self))
            {
                  std::string ErrorString = "Cannot call getNumActivitiesAttached on FieldContainer of type '";
                  ErrorString += (*$self)->getTypeName();
                  ErrorString += "', because it is not an EventProducer.'";
                  throw(ErrorString.c_str());
            }

            OSG::EventProducerPtr ProdField = OSG::getEventProducer(*$self);
            
            return ProdField->getNumActivitiesAttached(ProducedEventName);
        }

        FieldContainerRefPtr getAttachedActivity(const Char8 *ProducedEventName, UInt32 ActivityIndex) const
        {
            if(!OSG::isEventProducer(*$self))
            {
                  std::string ErrorString = "Cannot call getAttachedActivity on FieldContainer of type '";
                  ErrorString += (*$self)->getTypeName();
                  ErrorString += "', because it is not an EventProducer.'";
                  throw(ErrorString.c_str());
            }

            OSG::EventProducerPtr ProdField = OSG::getEventProducer(*$self);
            
            return ProdField->getAttachedActivity(ProducedEventName, ActivityIndex);
        }

        void detachActivity(FieldContainerRefPtr TheActivity, const Char8 *ProducedEventName)
        {
            if(!OSG::isEventProducer(*$self))
            {
                  std::string ErrorString = "Cannot call detachActivity on FieldContainer of type '";
                  ErrorString += (*$self)->getTypeName();
                  ErrorString += "', because it is not an EventProducer.'";
                  throw(ErrorString.c_str());
            }

            if(!TheActivity->getType().isDerivedFrom(OSG::Activity::getClassType()))
            {
                  std::string ErrorString = "Cannot call detachActivity with Argument 1 of type '";
                  ErrorString += TheActivity->getTypeName();
                  ErrorString += "', because it is not derived from Activity.'";
                  throw(ErrorString.c_str());
            }

            OSG::EventProducerPtr ProdField = OSG::getEventProducer(*$self);
            
            return ProdField->detachActivity(OSG::dynamic_pointer_cast<OSG::Activity>(TheActivity),ProducedEventName);
        }

        EventConnection attachActivity(FieldContainerRefPtr TheActivity, UInt32 ProducedEventId)
        {
            if(!OSG::isEventProducer(*$self))
            {
                  std::string ErrorString = "Cannot call attachActivity on FieldContainer of type '";
                  ErrorString += (*$self)->getTypeName();
                  ErrorString += "', because it is not an EventProducer.'";
                  throw(ErrorString.c_str());
            }

            if(!TheActivity->getType().isDerivedFrom(OSG::Activity::getClassType()))
            {
                  std::string ErrorString = "Cannot call attachActivity with Argument 1 of type '";
                  ErrorString += TheActivity->getTypeName();
                  ErrorString += "', because it is not derived from Activity.'";
                  throw(ErrorString.c_str());
            }

            OSG::EventProducerPtr ProdField = OSG::getEventProducer(*$self);
            
            return ProdField->attachActivity(OSG::dynamic_pointer_cast<OSG::Activity>(TheActivity),ProducedEventId);
        }

        bool isActivityAttached(FieldContainerRefPtr TheActivity, UInt32 ProducedEventId) const
        {
            if(!OSG::isEventProducer(*$self))
            {
                  std::string ErrorString = "Cannot call isActivityAttached on FieldContainer of type '";
                  ErrorString += (*$self)->getTypeName();
                  ErrorString += "', because it is not an EventProducer.'";
                  throw(ErrorString.c_str());
            }

            if(!TheActivity->getType().isDerivedFrom(OSG::Activity::getClassType()))
            {
                  std::string ErrorString = "Cannot call isActivityAttached with Argument 1 of type '";
                  ErrorString += TheActivity->getTypeName();
                  ErrorString += "', because it is not derived from Activity.'";
                  throw(ErrorString.c_str());
            }

            OSG::EventProducerPtr ProdField = OSG::getEventProducer(*$self);
            
            return ProdField->isActivityAttached(OSG::dynamic_pointer_cast<OSG::Activity>(TheActivity),ProducedEventId);
        }

        UInt32 getNumActivitiesAttached(UInt32 ProducedEventId) const
        {
            if(!OSG::isEventProducer(*$self))
            {
                  std::string ErrorString = "Cannot call getNumActivitiesAttached on FieldContainer of type '";
                  ErrorString += (*$self)->getTypeName();
                  ErrorString += "', because it is not an EventProducer.'";
                  throw(ErrorString.c_str());
            }

            OSG::EventProducerPtr ProdField = OSG::getEventProducer(*$self);
            
            return ProdField->getNumActivitiesAttached(ProducedEventId);
        }

        FieldContainerRefPtr getAttachedActivity(UInt32 ProducedEventId, UInt32 ActivityIndex) const
        {
            if(!OSG::isEventProducer(*$self))
            {
                  std::string ErrorString = "Cannot call getAttachedActivity on FieldContainer of type '";
                  ErrorString += (*$self)->getTypeName();
                  ErrorString += "', because it is not an EventProducer.'";
                  throw(ErrorString.c_str());
            }

            OSG::EventProducerPtr ProdField = OSG::getEventProducer(*$self);
            
            return ProdField->getAttachedActivity(ProducedEventId, ActivityIndex);
        }
        
        void detachActivity(FieldContainerRefPtr TheActivity, UInt32 ProducedEventId)
        {
            if(!OSG::isEventProducer(*$self))
            {
                  std::string ErrorString = "Cannot call detachActivity on FieldContainer of type '";
                  ErrorString += (*$self)->getTypeName();
                  ErrorString += "', because it is not an EventProducer.'";
                  throw(ErrorString.c_str());
            }

            if(!TheActivity->getType().isDerivedFrom(OSG::Activity::getClassType()))
            {
                  std::string ErrorString = "Cannot call detachActivity with Argument 1 of type '";
                  ErrorString += TheActivity->getTypeName();
                  ErrorString += "', because it is not derived from Activity.'";
                  throw(ErrorString.c_str());
            }

            OSG::EventProducerPtr ProdField = OSG::getEventProducer(*$self);
            
            return ProdField->detachActivity(OSG::dynamic_pointer_cast<OSG::Activity>(TheActivity),ProducedEventId);
        }

        void detachAllActivities(void)
        {
            if(!OSG::isEventProducer(*$self))
            {
                  std::string ErrorString = "Cannot call detachAllActivities on FieldContainer of type '";
                  ErrorString += (*$self)->getTypeName();
                  ErrorString += "', because it is not an EventProducer.'";
                  throw(ErrorString.c_str());
            }

            OSG::EventProducerPtr ProdField = OSG::getEventProducer(*$self);
            
            return ProdField->detachAllActivities();
        }

        UInt32 getNumAttachedActivities(void) const
        {
            if(!OSG::isEventProducer(*$self))
            {
                  std::string ErrorString = "Cannot call getNumAttachedActivities on FieldContainer of type '";
                  ErrorString += (*$self)->getTypeName();
                  ErrorString += "', because it is not an EventProducer.'";
                  throw(ErrorString.c_str());
            }

            OSG::EventProducerPtr ProdField = OSG::getEventProducer(*$self);
            
            return ProdField->getNumAttachedActivities();
        }

        const EventProducerType &getProducerType(void) const
        {
            if(!OSG::isEventProducer(*$self))
            {
                  std::string ErrorString = "Cannot call getProducerType on FieldContainer of type '";
                  ErrorString += (*$self)->getTypeName();
                  ErrorString += "', because it is not an EventProducer.'";
                  throw(ErrorString.c_str());
            }
            
            return OSG::getEventProducer(*$self)->getProducerType();
        }

        UInt32 getNumProducedEvents(void) const
        {
            if(!OSG::isEventProducer(*$self))
            {
                  std::string ErrorString = "Cannot call getNumProducedEvents on FieldContainer of type '";
                  ErrorString += (*$self)->getTypeName();
                  ErrorString += "', because it is not an EventProducer.'";
                  throw(ErrorString.c_str());
            }

            OSG::EventProducerPtr ProdField = OSG::getEventProducer(*$self);
            
            return ProdField->getNumProducedEvents();
        }

        const MethodDescription *getProducedEventDescription(const Char8 *ProducedEventName) const
        {
            if(!OSG::isEventProducer(*$self))
            {
                  std::string ErrorString = "Cannot call getProducedEventDescription on FieldContainer of type '";
                  ErrorString += (*$self)->getTypeName();
                  ErrorString += "', because it is not an EventProducer.'";
                  throw(ErrorString.c_str());
            }

            OSG::EventProducerPtr ProdField = OSG::getEventProducer(*$self);
            
            return ProdField->getProducedEventDescription(ProducedEventName);
        }

        const MethodDescription *getProducedEventDescription(UInt32 ProducedEventId) const
        {
            if(!OSG::isEventProducer(*$self))
            {
                  std::string ErrorString = "Cannot call getProducedEventDescription on FieldContainer of type '";
                  ErrorString += (*$self)->getTypeName();
                  ErrorString += "', because it is not an EventProducer.'";
                  throw(ErrorString.c_str());
            }

            OSG::EventProducerPtr ProdField = OSG::getEventProducer(*$self);
            
            return ProdField->getProducedEventDescription(ProducedEventId);
        }

        UInt32 getProducedEventId(const Char8 *ProducedEventName) const
        {
            if(!OSG::isEventProducer(*$self))
            {
                  std::string ErrorString = "Cannot call getProducedEventId on FieldContainer of type '";
                  ErrorString += (*$self)->getTypeName();
                  ErrorString += "', because it is not an EventProducer.'";
                  throw(ErrorString.c_str());
            }

            OSG::EventProducerPtr ProdField = OSG::getEventProducer(*$self);
            
            return ProdField->getProducedEventId(ProducedEventName);
        }

        EventProducerPtr getEventProducer(void)
        {
            if(!OSG::isEventProducer(*$self))
            {
                  std::string ErrorString = "Cannot call getEventProducer on FieldContainer of type '";
                  ErrorString += (*$self)->getTypeName();
                  ErrorString += "', because it is not an EventProducer.'";
                  throw(ErrorString.c_str());
            }

            return OSG::getEventProducer(*$self);
            
        }
        bool isEventProducer(void) const
        {
            return (*$self != NULL) && OSG::isEventProducer(*$self);
        }

        
     };

    /******************************************************/
    /*             ReflexiveContainerType                 */
    /******************************************************/
    class ReflexiveContainerType : public DataType
    {
      public:

        virtual ~ReflexiveContainerType(void); 

        UInt16 getGroupId(void) const;

        FieldDescriptionBase *getFieldDesc    (      UInt32  uiFieldId  );
        FieldDescriptionBase *getFieldDesc    (      UInt32  uiFieldId  ) const;

        FieldDescriptionBase *getFieldDesc    (const Char8  *szFieldName);
        FieldDescriptionBase *getFieldDesc    (const Char8  *szFieldName) const;

        UInt32                getNumFieldDescs(      void               ) const;

        BitVector getUnmarkedOnCreate(void);

        void addInitialDesc(FieldDescriptionBase *pDesc);

        UInt32 addDescription(const FieldDescriptionBase &desc     );
        bool   subDescription(      UInt32                uiFieldId);

      protected:

        ReflexiveContainerType(const ReflexiveContainerType &source);
        void operator =(const ReflexiveContainerType &source);
    };

    /******************************************************/
    /*              FieldContainerType                    */
    /******************************************************/
    class FieldContainerType : public ReflexiveContainerType
    {
      public :

        virtual ~FieldContainerType(void);

        bool isAbstract   (void                           ) const;

        bool isDerivedFrom(const TypeBase           &other) const;
        bool isDerivedFrom(const FieldContainerType &other) const;   

        bool isNode      (void) const;
        bool isNodeCore  (void) const;
        bool isAttachment(void) const;


        FieldContainerRefPtr getPrototype    (void) const;
        std::string     getFcdXML       (void) const;
        std::string     getDocumentation(void) const;

        /*FieldContainerTransitPtr createContainer(void) const;*/

      protected:

        FieldContainerType(const FieldContainerType &source);
    };

    /******************************************************/
    /*              FieldContainer                        */
    /******************************************************/
    class FieldContainer
    {
      public:
        virtual       FieldContainerType &getType    (void);

                /*Field  *getField        (      UInt32 fieldId  );*/

                /*Field  *getField        (const Char8 *fieldName);*/

        virtual FieldContainerRefPtr shallowCopy(void) const = 0;

      protected:
        FieldContainer(void);

        FieldContainer(const FieldContainer &obj);

        virtual ~FieldContainer (void);

    };

    /******************************************************/
    /*              FieldContainerFactoryBase             */
    /******************************************************/
    class FieldContainerFactoryBase : public FactoryBase
    {
        /*==========================  PUBLIC  =================================*/

      public:

              UInt16  findGroupId  (const Char8  *szName   ) const;
        const Char8  *findGroupName(      UInt16  uiGroupId) const;

              UInt32  getNumGroups (      void             ) const;

        void   registerType (      FieldContainerType *pType      );
        UInt16 registerGroup(const Char8         *szGroupName);

        FieldContainerType *findType   (      UInt32  uiTypeId) const;
        FieldContainerType *findType   (const Char8  *szName  ) const;
        UInt32         getNumTypes(      void            ) const;

        /*ContainerTransitPtr createContainer(const Char8 *szName);*/

        typedef FieldContainer                *ContainerPtr;
        /*typedef AspectStoreP                   ContainerHandlerP;*/
        /*typedef FieldContainer                *ContainerHandlerP;*/

        /*typedef std::deque<ContainerHandlerP>  ContainerStore;*/
        /*typedef ContainerStore::iterator       ContainerStoreIt;*/

        /*void setMapper(ContainerIdMapper *pMapper);*/

        UInt32            getNumContainers   (void                ) const;
        ContainerPtr      getContainer       (UInt32 uiContainerId) const;
        /*ContainerHandlerP getContainerHandler(UInt32 uiContainerId) const;*/

        ContainerPtr      getMappedContainer (UInt32 uiContainerId) const;

        Int32             findContainer      (ContainerPtr ptr    ) const;
        /*const ContainerStore    &getFieldContainerStore(void             ) const;   */

        UInt32 registerContainer  (const ContainerPtr &pContainer   );
        bool   deregisterContainer(const UInt32        uiContainerId);

      protected:
        FieldContainerFactoryBase(void);
        virtual ~FieldContainerFactoryBase(void);
        FieldContainerFactoryBase(const FieldContainerFactoryBase &source);
        void operator =(const FieldContainerFactoryBase &source);
    };

    /******************************************************/
    /*              FieldContainerFactory             */
    /******************************************************/
    class FieldContainerFactory : public FieldContainerFactoryBase
    {
      public :

        static FieldContainerFactoryBase *the(void);
            

      protected:
        FieldContainerFactory(void);
        virtual ~FieldContainerFactory(void);
        FieldContainerFactory(const FieldContainerFactory &source);
        void operator =(const FieldContainerFactory &source);
    };


    /******************************************************/
    /*                    AttachmentRefPtr          */
    /******************************************************/
    class AttachmentRefPtr :
        public FieldContainerRefPtr
    {
      public:

        AttachmentRefPtr(      void                          );
        AttachmentRefPtr(const AttachmentRefPtr &source);
        /*AttachmentRefPtr(const NullFieldContainerRefPtr  &source);*/
        ~AttachmentRefPtr(void);

        Attachment *operator->(void);

      protected:
    };
    %extend AttachmentRefPtr
    {
        static AttachmentRefPtr dcast(const FieldContainerRefPtr oIn)
        {
            return OSG::dynamic_pointer_cast<OSG::Attachment>(oIn);
        }
    };

    /******************************************************/
    /*                    Attachment             */
    /******************************************************/
    class Attachment : public FieldContainer
    {
      public:
      protected:
        Attachment(void);
        Attachment(const Attachment &source);
        ~Attachment(void);
    };

    /******************************************************/
    /*                    AttachmentContainerRefPtr          */
    /******************************************************/
    class AttachmentContainerRefPtr :
        public FieldContainerRefPtr
    {
      public:

        AttachmentContainerRefPtr(      void                          );
        AttachmentContainerRefPtr(const AttachmentContainerRefPtr &source);
        /*AttachmentContainerRefPtr(const NullFieldContainerRefPtr  &source);*/
        ~AttachmentContainerRefPtr(void);

        AttachmentContainer *operator->(void);
        
      protected:
    };
    %extend AttachmentContainerRefPtr
    {
        static AttachmentContainerRefPtr dcast(const FieldContainerRefPtr oIn)
        {
            return OSG::dynamic_pointer_cast<OSG::AttachmentContainer>(oIn);
        }
    };

    /******************************************************/
    /*                    AttachmentContainer             */
    /******************************************************/
    class AttachmentContainer : public FieldContainer
    {
      public:
        void          addAttachment (const AttachmentRefPtr &fieldContainerP,
                                           UInt16         binding        = 0);

        void          subAttachment (const AttachmentRefPtr &fieldContainerP,
                                           UInt16         binding        = 0);

        AttachmentRefPtr findAttachment(      UInt32         groupId,
                                           UInt16         binding        = 0);

        AttachmentRefPtr findAttachment(const FieldContainerType &type,
                                       UInt16              binding   = 0);
      protected:
        AttachmentContainer(void);
        AttachmentContainer(const AttachmentContainer &source);
        ~AttachmentContainer(void);
    };


    /******************************************************/
    /*                    NodeCore                        */
    /******************************************************/
    class NodeCore : public AttachmentContainer
    {
      public:
        virtual void invalidateVolume(void);

      protected:
        NodeCore(void);
        NodeCore(const NodeCore &obj);
        virtual ~NodeCore(void);
    };
    
    /******************************************************/
    /*                    NodeCoreRefPtr          */
    /******************************************************/
    class NodeCoreRefPtr :
        public AttachmentContainerRefPtr
    {
      public:

        NodeCoreRefPtr(      void                          );
        NodeCoreRefPtr(const NodeCoreRefPtr &source);
        /*NodeCoreRefPtr(const NullFieldContainerRefPtr  &source);*/
        ~NodeCoreRefPtr(void);
        
        NodeCore *operator->(void);
      protected:
    };  
    %extend NodeCoreRefPtr
    {
        static NodeCoreRefPtr dcast(const FieldContainerRefPtr oIn)
        {
            return OSG::dynamic_pointer_cast<OSG::NodeCore>(oIn);
        }
    };

    /******************************************************/
    /*                    Geometry             */
    /******************************************************/
    class Geometry : public NodeCore
    {
      public:
      
      protected:
        Geometry(void);
        Geometry(const Geometry &source);
        ~Geometry(void);
    };
    
    /******************************************************/
    /*                    GeometryRefPtr          */
    /******************************************************/
    class GeometryRefPtr :
        public NodeCoreRefPtr
    {
      public:

        GeometryRefPtr(      void                          );
        GeometryRefPtr(const GeometryRefPtr &source);
        /*GeometryRefPtr(const NullFieldContainerRefPtr  &source);*/
        ~GeometryRefPtr(void);

        Geometry *operator->(void);
      protected:
    };
    %extend GeometryRefPtr
    {
        static GeometryRefPtr dcast(const FieldContainerRefPtr oIn)
        {
            return OSG::dynamic_pointer_cast<OSG::Geometry>(oIn);
        }
    };
    
    /******************************************************/
    /*              NodeRefPtr                               */
    /******************************************************/
    class NodeRefPtr : public AttachmentContainerRefPtr
    {
      public:
         NodeRefPtr(void);
         NodeRefPtr(const NodeRefPtr               &source);
         /*NodeRefPtr(const NullFieldContainerRefPtr &source);*/


        ~NodeRefPtr(void);
        Node *operator->(void);
    };
    %extend NodeRefPtr
    {
        static NodeRefPtr dcast(const FieldContainerRefPtr oIn)
        {
            return OSG::dynamic_pointer_cast<OSG::Node>(oIn);
        }
    };

    /******************************************************/
    /*              Node                                  */
    /******************************************************/
    class Node : public AttachmentContainer
    {
      public:

        typedef AttachmentContainer                    Inherited;
        typedef AttachmentContainer                    ParentContainer;

        typedef Inherited::TypeObject                  TypeObject;

        typedef SFBoxVolume             SFVolumeType;
        typedef SFUInt32                SFTravMaskType;
        typedef SFParentNodePtr         SFParentType;
        typedef SFUnrecChildNodeCorePtr SFCoreType;
        typedef MFUnrecChildNodePtr     MFChildrenType;

        typedef BoxVolume               VolumeType;

        /*NodeCore *getCore(void                 );*/
        /*NodeCore *getCore(void                 ) const;*/

        /*void      setCore(NodeCore * const core);*/
        

        /*Node *getParent(void);*/

        UInt32  getNChildren  (void                      ) const;

        /*void    addChild      (Node   * const  childP    );*/
        /*void    addChild      (NodeTransitPtr  childP    );*/

        /*void    insertChild   (UInt32          childIndex,*/
                               /*Node   * const  childP    );*/

        /*void    replaceChild  (UInt32          childIndex,*/
                               /*Node   * const  childP    );*/

        /*bool    replaceChildBy(Node   * const  childP,*/
                               /*Node   * const  newChildP );*/

        /*Int32   findChild     (Node   * const  childP    ) const;*/

        /*void    subChild      (Node   * const  childP    );*/
        void    subChild      (UInt32          childIndex);

        /*Node   *getChild      (UInt32          childIndex) const;*/

        void    clearChildren (void                      );

        void   setTravMask     (UInt32 uiMask);
        UInt32 getTravMask     (void         ) const;

        Matrix getToWorld(void           );

        void    getToWorld(Matrix &result);

                BoxVolume &editVolume      (bool update = false  );

                void       getWorldVolume  (BoxVolume &result    );

                void       updateVolume    (void                 );

        virtual void       invalidateVolume(void                 );
      protected:
        Node(void);
        Node(const Node &source);
        virtual ~Node(void);
        void operator =(const Node &source);
    };
    
    /******************************************************/
    /*              ViewportRefPtr                             */
    /******************************************************/
    class ViewportRefPtr : public AttachmentContainerRefPtr
    {
      public:
         ViewportRefPtr(void);
         ViewportRefPtr(const ViewportRefPtr               &source);
         /*ViewportRefPtr(const NullFieldContainerRefPtr &source);*/


        ~ViewportRefPtr(void);
        Viewport *operator->(void);
    };
    %extend ViewportRefPtr
    {
        static ViewportRefPtr dcast(const FieldContainerRefPtr oIn)
        {
            return OSG::dynamic_pointer_cast<OSG::Viewport>(oIn);
        }
    };

    /******************************************************/
    /*                     Viewport                       */
    /******************************************************/
    class Viewport : public AttachmentContainer
    {
      public:
        
        void setSize        (Real32 left,  
                             Real32 bottom, 
                             Real32 right, 
                             Real32 top   );

        Int32 getPixelLeft  (void) const;
        Int32 getPixelRight (void) const;
        Int32 getPixelBottom(void) const;
        Int32 getPixelTop   (void) const;
        Int32 getPixelWidth (void) const;
        Int32 getPixelHeight(void) const;
        
        bool isFullWindow( void ) const;
        /*Window       *getParent(void) const;*/

        void          getNormalizedCoordinates(      Real32& normX,
                                                     Real32& normY,
                                               const Int32   vpX  ,
                                               const Int32   vpY  ) const;

        virtual bool               isPassive(void);
        /*virtual FrameBufferObject *getTarget(void);*/
      protected:
        Viewport(void);
        Viewport(const Image &source);

        virtual ~Viewport(void);
    };
    
    
    /******************************************************/
    /*              CameraRefPtr                             */
    /******************************************************/
    class CameraRefPtr : public AttachmentContainerRefPtr
    {
      public:
         CameraRefPtr(void);
         CameraRefPtr(const CameraRefPtr               &source);
         /*CameraRefPtr(const NullFieldContainerRefPtr &source);*/


        ~CameraRefPtr(void);
        Camera *operator->(void);
    };
    %extend CameraRefPtr
    {
        static CameraRefPtr dcast(const FieldContainerRefPtr oIn)
        {
            return OSG::dynamic_pointer_cast<OSG::Camera>(oIn);
        }
    };
    
    /******************************************************/
    /*                       Camera                       */
    /******************************************************/
    class Camera : public AttachmentContainer
    {
     public:
        // Getters
        virtual Matrix getProjectionVal           (      UInt32         width,
                                                          UInt32         height);

        virtual Matrix getProjectionTranslationVal(      UInt32         width,
                                                          UInt32         height);

        virtual Matrix getViewingVal              (      UInt32         width,
                                                          UInt32         height);
        virtual Matrix getWorldToScreenVal        (const Viewport      &port  );

        virtual Matrix getDecorationVal           (      UInt32         width,
                                                          UInt32         height);

        virtual FrustumVolume getFrustumVal        (const Viewport      &port  );

        /*virtual Vec2u tileGetFullSize(void) const;*/
        /*virtual Vec4f tileGetRegion  (void) const;*/

     protected:
        Camera(void);
        Camera(const Camera &source);

        virtual ~Camera(void);
    };
    %extend Camera
    {
        bool calcViewRay( Line &line, Int32 x, Int32 y, const ViewportRefPtr port,
               Real32 *t = NULL )
        {
            return ($self)->calcViewRay(line, x, y, (*port), t);
        }
    };
    
    /******************************************************/
    /*              ImageRefPtr                             */
    /******************************************************/
    class ImageRefPtr : public AttachmentContainerRefPtr
    {
      public:
         ImageRefPtr(void);
         ImageRefPtr(const ImageRefPtr               &source);
         /*ImageRefPtr(const NullFieldContainerRefPtr &source);*/


        ~ImageRefPtr(void);
        Image *operator->(void);
    };
    %extend ImageRefPtr
    {
        static ImageRefPtr dcast(const FieldContainerRefPtr oIn)
        {
            return OSG::dynamic_pointer_cast<OSG::Image>(oIn);
        }
    };
    
    /******************************************************/
    /*                       Image                       */
    /******************************************************/
    class Image : public AttachmentContainer
    {
      public:

        enum PixelFormat
        {
            OSG_INVALID_PF                 = 0,

            OSG_A_PF                       = GL_ALPHA,
            OSG_I_PF                       = GL_INTENSITY,

            OSG_L_PF                       = GL_LUMINANCE,
            OSG_LA_PF                      = GL_LUMINANCE_ALPHA,

            OSG_BGR_PF                     = GL_BGR,

            OSG_BGRA_PF                    = GL_BGRA,
            OSG_RGB_DXT1                   = GL_COMPRESSED_RGB_S3TC_DXT1_EXT,
            OSG_RGBA_DXT1                  = GL_COMPRESSED_RGBA_S3TC_DXT1_EXT,
            OSG_RGBA_DXT3                  = GL_COMPRESSED_RGBA_S3TC_DXT3_EXT,
            OSG_RGBA_DXT5                  = GL_COMPRESSED_RGBA_S3TC_DXT5_EXT,
            OSG_RGB_PF                     = GL_RGB,
            OSG_RGBA_PF                    = GL_RGBA,

            OSG_ALPHA_INTEGER_PF           = GL_ALPHA_INTEGER_EXT,
            OSG_RGB_INTEGER_PF             = GL_RGB_INTEGER_EXT,
            OSG_RGBA_INTEGER_PF            = GL_RGBA_INTEGER_EXT,
            OSG_BGR_INTEGER_PF             = GL_BGR_INTEGER_EXT,
            OSG_BGRA_INTEGER_PF            = GL_BGRA_INTEGER_EXT,
            OSG_LUMINANCE_INTEGER_PF       = GL_LUMINANCE_INTEGER_EXT,
            OSG_LUMINANCE_ALPHA_INTEGER_PF = GL_LUMINANCE_ALPHA_INTEGER_EXT
        };

        enum Type {
             OSG_INVALID_IMAGEDATATYPE = GL_NONE,
             OSG_UINT8_IMAGEDATA       = GL_UNSIGNED_BYTE,
             OSG_UINT16_IMAGEDATA      = GL_UNSIGNED_SHORT,
             OSG_UINT32_IMAGEDATA      = GL_UNSIGNED_INT,
             OSG_FLOAT16_IMAGEDATA     = GL_HALF_FLOAT_NV,
             OSG_FLOAT32_IMAGEDATA     = GL_FLOAT,
             OSG_INT16_IMAGEDATA       = GL_SHORT,
             OSG_INT32_IMAGEDATA       = GL_INT
        };

        enum ResUnit
        {
             OSG_RESUNIT_INVALID       = 0,
             OSG_RESUNIT_NONE          = 1,
             OSG_RESUNIT_INCH          = 2
        };

        bool set                (      UInt32      pixelFormat,
                                       Int32       width,
                                       Int32       height = 1,
                                       Int32       depth = 1,
                                       Int32       mipmapCount = 1,
                                       Int32       frameCount = 1,
                                       Time        frameDelay = 0.0,
                                       const UInt8       *data = 0,
                                       Int32 type = OSG_UINT8_IMAGEDATA,
                                       bool        allocMem = true,
                                       Int32       sideCount = 1);

        bool set                (      ImageRefPtr   image            );
        bool setData            (const UInt8     *data = 0         );
        void clearData          (void                              );
        bool setSubData ( Int32 offX, Int32 offY, Int32 offZ,
                          Int32 srcW, Int32 srcH, Int32 srcD,
                          const UInt8 *data );
        bool flipDepthFrameData (void                              );

        /*void imageContentChanged(Int32 minX = -1, Int32 maxX = -1,*/
                                 /*Int32 minY = -1, Int32 maxY = -1,*/
                                 /*Int32 minZ = -1, Int32 maxZ = -1 );*/
        
        bool addValue (const char *value);

        /*bool reformat ( const PixelFormat pixelFormat,*/
                        /*ImageRefPtr destination = NullFC);*/

        /*void swapDataEndian(void);*/
        /*bool convertDataTypeTo ( Int32 destDataType = OSG_UINT8_IMAGEDATA );*/

        bool scale          ( Int32 width, Int32 height = 1,
                              Int32 depth = 1,
                              ImageRefPtr destination = NullFC );
        /*bool scaleNextPower2( ImageRefPtr destination = NullFC );*/
        /*bool mirror         (bool   horizontal,*/
                             /*bool   vertical,*/
                             /*bool   flipDepth   = false,*/
                             /*Image *destination = NULL  );*/

        /*bool subImage ( Int32 offX, Int32 offY, Int32 offZ,*/
                        /*Int32 destW, Int32 destH, Int32 destD,*/
                        /*ImageRefPtr destination = NullFC);*/

        /*bool slice ( Int32 offX = -1, Int32 offY = -1, Int32 offZ = -1,*/
                     /*ImageRefPtr destination = NullFC);*/

        /*bool createMipmap ( Int32 level = -1, ImageRefPtr destination = NullFC);*/

        /*bool removeMipmap (void);*/

        bool write (const Char8 *fileName);
        bool read  (const Char8 *fileName);

        /*UInt64 store   (const Char8 *mimeType, UInt8* mem, Int32 memSize = -1);*/
        /*UInt64 restore (const UInt8* mem, Int32 memSize = -1);*/

        /*bool   operator == (const Image &image);*/

        bool   isValid           (void) const;
        bool   hasAlphaChannel   (void);
        bool   isAlphaBinary     (void);
        bool   hasColorChannel   (void);
        bool   hasCompressedData (void);
        UInt8  getComponents     (void) const;
        
        bool   calcIsAlphaBinary (void);

        unsigned long getSize ( bool withMipmap = true,
                bool withFrames = true,
                bool withSides  = true ) const;

        const UInt8 *getData ( UInt32 mipmapNum = 0,
                UInt32 frameNum = 0,
                UInt32 sideNum = 0 ) const;
        UInt8 *editData( UInt32 mipmapNum = 0,
                UInt32 frameNum = 0,
                UInt32 sideNum = 0 );
        const UInt8 *getDataFast ( UInt32 mipmapNum = 0,
                UInt32 frameNum = 0,
                UInt32 sideNum = 0 ) const;
        UInt8 *editDataFast( UInt32 mipmapNum = 0,
                UInt32 frameNum = 0,
                UInt32 sideNum=0);
        const UInt8 *getDataByTime (Time   time, 
                UInt32 mipmapNum = 1) const;
        UInt8 *editDataByTime(Time   time, 
                UInt32 mipmapNum = 1);

        /*void   calcMipmapGeometry   ( UInt32 mipmapNum,*/
                                      /*UInt32 &width,*/
                                      /*UInt32 &height,*/
                                      /*UInt32 &depth       ) const;*/

        /*UInt32 calcMipmapLevelCount ( void                       ) const;*/
        /*UInt32 calcFrameNum         ( Time time, bool loop = true) const;*/

        virtual void clear (UChar8 pixelValue = 0);
        virtual void clearFloat (Real32 pixelValue = 0.0);
        virtual void clearHalf (Real16 pixelValue = Real16( 0.0 ));

        /*UInt32 calcMipmapLevelSize( UInt32 mipmapNum,*/
                                         /*UInt32 w, UInt32 h, UInt32 d) const;*/
        /*UInt32 calcMipmapLevelSize( UInt32 mipmapNum                 ) const;*/

        /*UInt32 calcMipmapSumSize  ( UInt32 mipmapNum,*/
                                         /*UInt32 w, UInt32 h, UInt32 d) const;*/
        /*UInt32 calcMipmapSumSize  ( UInt32 mipmapNum                 ) const;*/
        
      protected:
        Image(void);
        Image(const Image &source);

        virtual ~Image(void);
    };


    /******************************************************/
    /*                    TextureObjChunk                        */
    /******************************************************/
    class TextureObjChunk : public FieldContainer
    {
      public:

      protected:
        TextureObjChunk(void);
        TextureObjChunk(const TextureObjChunk &obj);
        virtual ~TextureObjChunk(void);
    };
    
    /******************************************************/
    /*                    TextureObjChunkRefPtr          */
    /******************************************************/
    class TextureObjChunkRefPtr :
        public FieldContainerRefPtr
    {
      public:

        TextureObjChunkRefPtr(      void                          );
        TextureObjChunkRefPtr(const TextureObjChunkRefPtr &source);
        /*TextureObjChunkRefPtr(const NullFieldContainerRefPtr  &source);*/
        ~TextureObjChunkRefPtr(void);

        TextureObjChunk *operator->(void);
      protected:
    };
    %extend TextureObjChunkRefPtr
    {
        static TextureObjChunkRefPtr dcast(const FieldContainerRefPtr oIn)
        {
            return OSG::dynamic_pointer_cast<OSG::TextureObjChunk>(oIn);
        }
    };

    /******************************************************/
    /*                    EventPtr          */
    /******************************************************/
    class EventRefPtr : 
        public FieldContainerRefPtr
    {
        public:

            EventRefPtr(      void                          );
            EventRefPtr(const EventRefPtr &source);
            ~EventRefPtr(void);

        protected:
    };
    %extend EventRefPtr
    {
        static EventRefPtr dcast(const FieldContainerRefPtr oIn)
        {
            return OSG::dynamic_pointer_cast<OSG::Event>(oIn);
        }
    };

    /******************************************************/
    /*Event			                       */
    /******************************************************/
    class Event : public FieldContainer
    {
        public:

        protected:
            Event(void);
            Event(const Event &obj);
            virtual ~Event(void);
    };

    /******************************************************/
    /*                    GenericEventPtr          */
    /******************************************************/
    class GenericEventRefPtr : 
        public EventRefPtr
    {
        public:

            GenericEventRefPtr(      void                          );
            GenericEventRefPtr(const GenericEventRefPtr &source);
            ~GenericEventRefPtr(void);
        protected:
    };
    %extend GenericEventRefPtr
    {
        static GenericEventRefPtr dcast(const FieldContainerRefPtr oIn)
        {
            return OSG::dynamic_pointer_cast<OSG::GenericEvent>(oIn);
        }
    };

    /******************************************************/
    /*GenericEvent			                       */
    /******************************************************/
    class GenericEvent : public Event
    {
        public:

        protected:
            GenericEvent(void);
            GenericEvent(const GenericEvent &obj);
            virtual ~GenericEvent(void);
    };
    
    /******************************************************/
    /*                    LuaActivityPtr          */
    /******************************************************/
    class LuaActivityRefPtr : 
        public AttachmentContainerRefPtr
    {
        public:

            LuaActivityRefPtr(      void                          );
            LuaActivityRefPtr(const LuaActivityRefPtr &source);
            ~LuaActivityRefPtr(void);

        protected:
    };
    %extend LuaActivityRefPtr
    {
        static LuaActivityRefPtr dcast(const FieldContainerRefPtr oIn)
        {
            return OSG::dynamic_pointer_cast<OSG::LuaActivity>(oIn);
        }
    };

    /******************************************************/
    /*                 LuaActivity                        */
    /******************************************************/
    class LuaActivity : public AttachmentContainer
    {
        public:

            static LuaActivityRefPtr addLuaCallback(FieldContainerRefPtr producerObject, std::string funcName, UInt32 producedMethodId);
            static void removeLuaCallback(FieldContainerRefPtr producerObject, LuaActivityRefPtr toRemove, UInt32 producedMethodId);

        protected:
            LuaActivity(void);
            LuaActivity(const LuaActivity &obj);
            virtual ~LuaActivity(void);
    };
    
    /******************************************************/
    /*              Geom Creation Functions               */
    /******************************************************/
    FieldContainerRefPtr               makePlaneGeo          (Real32 xsize,
                                                     Real32 ysize,
                                                     UInt16 hor,  
                                                     UInt16 vert);
     
    FieldContainerRefPtr                   makePlane             (Real32 xsize,
                                                     Real32 ysize,
                                                     UInt16 hor,  
                                                     UInt16 vert);
     
    FieldContainerRefPtr               makeBoxGeo            (Real32 xsize,
                                                     Real32 ysize,
                                                     Real32 zsize,
                                                     UInt16 hor,
                                                     UInt16 vert,
                                                     UInt16 depth);
     
    FieldContainerRefPtr                   makeBox               (Real32 xsize,
                                                     Real32 ysize,
                                                     Real32 zsize,
                                                     UInt16 hor,
                                                     UInt16 vert,
                                                     UInt16 depth);
     
    FieldContainerRefPtr               makeConeGeo           (Real32 height,
                                                     Real32 botradius,
                                                     UInt16 sides,
                                                     bool   doSide,
                                                     bool   doBottom);
     
    FieldContainerRefPtr                   makeCone              (Real32 height,
                                                     Real32 botradius,
                                                     UInt16 sides,
                                                     bool   doSide,
                                                     bool   doBottom);
     
    FieldContainerRefPtr               makeCylinderGeo       (Real32 height,
                                                     Real32 radius,
                                                     UInt16 sides,
                                                     bool   doSide,
                                                     bool   doTop,
                                                     bool   doBottom);
     
    FieldContainerRefPtr                   makeCylinder          (Real32 height,
                                                     Real32 radius,
                                                     UInt16 sides,
                                                     bool   doSide,
                                                     bool   doTop,
                                                     bool   doBottom);
     
    FieldContainerRefPtr               makeTorusGeo          (Real32 innerRadius,
                                                     Real32 outerRadius,
                                                     UInt16 sides,
                                                     UInt16 rings );
    
     
    FieldContainerRefPtr                   makeTorus             (Real32 innerRadius,
                                                     Real32 outerRadius,
                                                     UInt16 sides,
                                                     UInt16 rings);
     
    FieldContainerRefPtr               makeSphereGeo         (UInt16 depth,
                                                     Real32 radius);
     
    FieldContainerRefPtr                   makeSphere            (UInt16 depth,
                                                     Real32 radius);
     
    FieldContainerRefPtr               makeLatLongSphereGeo  (UInt16 latres,
                                                     UInt16 longres,
                                                     Real32 radius);
     
    FieldContainerRefPtr                   makeLatLongSphere     (UInt16 latres,
                                                     UInt16 longres,
                                                     Real32 radius);
     
    FieldContainerRefPtr               makeConicalFrustumGeo (Real32 height,
                                                     Real32 topradius,
                                                     Real32 botradius,
                                                     UInt16 sides,
                                                     bool   doSide,
                                                     bool   doTop,
                                                     bool   doBottom);
     
    FieldContainerRefPtr                   makeConicalFrustum    (Real32 height,
                                                     Real32 topradius,
                                                     Real32 botradius,
                                                     UInt16 sides,
                                                     bool   doSide,
                                                     bool   doTop,
                                                     bool   doBottom);
     
    void                    calcVertexNormals   (GeometryRefPtr geo);
    
     
    void                    calcVertexNormals   (GeometryRefPtr geo,
                                                 Real32 creaseAngle);
     
    void                    calcFaceNormals     (GeometryRefPtr geo);
    
     
    void                    calcVertexTangents  (GeometryRefPtr geo,
                                                 Int32 srcTexIndex,
                                                 Int32 dstAttribTan,
                                                 Int32 dstAttribBin);
    
    
    void                    calcVertexTexCoords (GeometryRefPtr geo,
                                                 Int32 texIndex);
    
     
    Int32              createOptimizedPrimitives(GeometryRefPtr geo,
                                                 UInt32 iteration,
                                                 bool createStrips,
                                                 bool createFans,
                                                 UInt32 minFanEdgeCount,
                                                 bool colorCode,
                                                 bool stitchStrips);
    
     
    void                  createConvexPrimitives(GeometryRefPtr geo);
    
     
    Int32                      createSharedIndex(GeometryRefPtr geo);
    
     
    Int32                      createSingleIndex(GeometryRefPtr geo);
    
     
    UInt32                    calcPrimitiveCount(GeometryRefPtr geo,
                                                 UInt32 &triangle,
                                                 UInt32 &line,
                                                 UInt32 &point);
    
     
    NodeRefPtr                 calcVertexNormalsGeo(GeometryRefPtr geo,
                                                 Real32 length);
    
     
    NodeRefPtr                   calcFaceNormalsGeo(GeometryRefPtr geo,
                                                 Real32 length);
     
    /*void                         mergeGeometries(std::vector<NodeRefPtr> &nodes,*/
                                                 /*std::vector<NodeRefPtr> &results);*/
    
    
    void                        separateProperties(GeometryRefPtr geo);


}

