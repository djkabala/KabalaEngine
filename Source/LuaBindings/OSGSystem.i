%include <OSGBase.i>
%module OSG
%native(createFieldContainer) int createFieldContainer(lua_State*L);  // registers native_function() with SWIG
%native(getFieldContainer) int getFieldContainer(lua_State*L);  // registers native_function() with SWIG
%{
#include <OpenSG/OSGFieldContainerType.h>
#include <OpenSG/OSGFieldContainerPtr.h>
#include <OpenSG/OSGFieldDescription.h>
#include <OpenSG/OSGBaseTypes.h>
#include <OpenSG/OSGAttachment.h>
#include <OpenSG/OSGAttachmentContainer.h>
#include <OpenSG/OSGSimpleAttachments.h>
#include <OpenSG/OSGAttachmentContainerPtr.h>
#include <OpenSG/OSGSimpleGeometry.h>
#include <OpenSG/OSGGeoFunctions.h>
#include <OpenSG/OSGNode.h>
#include <OpenSG/OSGNodeCore.h>
#include <OpenSG/OSGGeometry.h>
#include <OpenSG/OSGViewport.h>
#include <OpenSG/OSGCamera.h>
#include <OpenSG/OSGImage.h>
#include <OpenSG/OSGSysFieldDataType.h>
#include <OpenSG/OSGVecFieldDataType.h>
#include <OpenSG/OSGMathFieldDataType.h>
#include <OpenSG/OSGSFVecTypes.h>
#include <OpenSG/OSGSFMathTypes.h>
#include <OpenSG/OSGSFSysTypes.h>
#include <OpenSG/OSGMFVecTypes.h>
#include <OpenSG/OSGMFMathTypes.h>
#include <OpenSG/OSGMFSysTypes.h>
#include <OpenSG/OSGMFBaseTypes.h>
#include <OpenSG/OSGFieldContainerFields.h>
#include <OpenSG/Toolbox/OSGFieldContainerUtils.h>
#include <OpenSG/Toolbox/OSGActivity.h>
#include <OpenSG/Toolbox/OSGEventProducerType.h>
    
    int createFieldContainer(lua_State*L) // my native code
    {
      int SWIG_arg = 0;
      osg::Char8 *arg1 = (osg::Char8 *) 0 ;
      osg::FieldContainerPtr result;
      
      SWIG_check_num_args("createFieldContainer",1,1)
      if(!lua_isstring(L,1)) SWIG_fail_arg("createFieldContainer",1,"string");
      
      arg1 = (osg::Char8 *)lua_tostring(L, 1);
      
      result = osg::FieldContainerFactory::the()->createFieldContainer(arg1);
      if(result != osg::NullFC)
      {
        osg::FieldContainerPtr * resultptr = new osg::FieldContainerPtr((const osg::FieldContainerPtr &) result);
        SWIG_NewPointerObj(L,(void *) resultptr,SWIGTYPE_p_osg__FieldContainerPtr,1); SWIG_arg++;
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
      osg::Char8 *arg1 = (osg::Char8 *) 0 ;
      osg::FieldContainerPtr result;
      
      SWIG_check_num_args("getFieldContainer",1,1)
      if(!lua_isstring(L,1)) SWIG_fail_arg("getFieldContainer",1,"string");
      
      arg1 = (osg::Char8 *)lua_tostring(L, 1);
      
      result = osg::getFieldContainer(arg1);
      if(result != osg::NullFC)
      {
        osg::FieldContainerPtr * resultptr = new osg::FieldContainerPtr((const osg::FieldContainerPtr &) result);
        SWIG_NewPointerObj(L,(void *) resultptr,SWIGTYPE_p_osg__FieldContainerPtr,1); SWIG_arg++;
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
          osg::FieldContainerPtr *arg1 = (osg::FieldContainerPtr *) 0 ;
          osg::Char8 *arg2 = (osg::Char8 *) 0 ;
          std::string result;
          
          SWIG_check_num_args("getFieldValue",2,2)
          if(!SWIG_isptrtype(L,1)) SWIG_fail_arg("getFieldValue",1,"osg::FieldContainerPtr *");
          if(!lua_isstring(L,2)) SWIG_fail_arg("getFieldValue",2,"osg::Char8 const *");
              
          if (!SWIG_IsOK(SWIG_ConvertPtr(L,1,(void**)&arg1,SWIGTYPE_p_osg__FieldContainerPtr,0))){
            SWIG_fail_ptr("getFieldValue",1,SWIGTYPE_p_osg__FieldContainerPtr);
          }
          arg2 = (osg::Char8 *)lua_tostring(L, 2);
          
          const osg::Field* TheField((*arg1)->getField(arg2));
          if(TheField == NULL)
          {
              lua_pushfstring(L,"Error in getFieldValue there is no field of name '%s' on type '%s'",arg2,(*arg1)->getTypeName());
              goto fail;
          }
          //Check that this is not a MultiField
          if(TheField->getCardinality() == osg::FieldType::MULTI_FIELD)
          {
              lua_pushfstring(L,"Error in getFieldValue field of name '%s' on type '%s' is a multi-field, you must also supply the index.",arg2,(*arg1)->getTypeName());
              goto fail;
          }
          //Types
          const osg::DataType& FieldContentType(TheField->getContentType());
          
#if defined(WIN32)
          //bool
          //string
          if(FieldContentType == osg::FieldDataTraits<std::string>::getType() )
          {
              lua_pushstring(L,dynamic_cast<const osg::SFString*>(TheField)->getValue().c_str()); SWIG_arg++;
          }
#else
          //bool
          if(FieldContentType == osg::FieldDataTraits2<bool>::getType() )
          {
              lua_pushboolean(L,dynamic_cast<const osg::SFBool*>(TheField)->getValue()); SWIG_arg++;
          }
          //string
          else if(FieldContentType == osg::FieldDataTraits<std::string>::getType() )
          {
              lua_pushstring(L,dynamic_cast<const osg::SFString*>(TheField)->getValue().c_str()); SWIG_arg++;
          }
#endif
          //UInt8
          else if(FieldContentType == osg::FieldDataTraits<osg::UInt8>::getType() )
          {
              lua_pushnumber(L,dynamic_cast<const osg::SFUInt8*>(TheField)->getValue()); SWIG_arg++;
          }
          //UInt16
          else if(FieldContentType == osg::FieldDataTraits<osg::UInt16>::getType() )
          {
              lua_pushnumber(L,dynamic_cast<const osg::SFUInt16*>(TheField)->getValue()); SWIG_arg++;
          }
          //UInt32
          else if(FieldContentType == osg::FieldDataTraits<osg::UInt32>::getType() )
          {
              lua_pushnumber(L,dynamic_cast<const osg::SFUInt32*>(TheField)->getValue()); SWIG_arg++;
          }
          //UInt64
          else if(FieldContentType == osg::FieldDataTraits<osg::UInt64>::getType() )
          {
              lua_pushnumber(L,dynamic_cast<const osg::SFUInt64*>(TheField)->getValue()); SWIG_arg++;
          }
          //BitVector
          else if(FieldContentType == osg::FieldDataTraits1<osg::BitVector>::getType() )
          {
              lua_pushnumber(L,dynamic_cast<const osg::SFBitVector*>(TheField)->getValue()); SWIG_arg++;
          }
          //GLenum
          else if(FieldContentType == osg::FieldDataTraits1<GLenum>::getType() )
          {
              lua_pushnumber(L,dynamic_cast<const osg::SFGLenum*>(TheField)->getValue()); SWIG_arg++;
          }
          //Int8
          else if(FieldContentType == osg::FieldDataTraits<osg::Int8>::getType() )
          {
              lua_pushnumber(L,dynamic_cast<const osg::SFInt8*>(TheField)->getValue()); SWIG_arg++;
          }
          //Int16
          else if(FieldContentType == osg::FieldDataTraits<osg::Int16>::getType() )
          {
              lua_pushnumber(L,dynamic_cast<const osg::SFInt16*>(TheField)->getValue()); SWIG_arg++;
          }
          //Int32
          else if(FieldContentType == osg::FieldDataTraits<osg::Int32>::getType() )
          {
              lua_pushnumber(L,dynamic_cast<const osg::SFInt32*>(TheField)->getValue()); SWIG_arg++;
          }
          //Int64
          else if(FieldContentType == osg::FieldDataTraits<osg::Int64>::getType() )
          {
              lua_pushnumber(L,dynamic_cast<const osg::SFInt64*>(TheField)->getValue()); SWIG_arg++;
          }
          //Real32
          else if(FieldContentType == osg::FieldDataTraits<osg::Real32>::getType() )
          {
              lua_pushnumber(L,dynamic_cast<const osg::SFReal32*>(TheField)->getValue()); SWIG_arg++;
          }
          //Time
          else if(FieldContentType == osg::FieldDataTraits1<osg::Time>::getType() )
          {
              lua_pushnumber(L,dynamic_cast<const osg::SFTime*>(TheField)->getValue()); SWIG_arg++;
          }
          //Real64
          else if(FieldContentType == osg::FieldDataTraits<osg::Real64>::getType() )
          {
              lua_pushnumber(L,dynamic_cast<const osg::SFReal64*>(TheField)->getValue()); SWIG_arg++;
          }
          //Color3f
          else if(FieldContentType == osg::FieldDataTraits<osg::Color3f>::getType() )
          {
              osg::Color3f * resultptr = new osg::Color3f((const osg::Color3f &) dynamic_cast<const osg::SFColor3f*>(TheField)->getValue());
              SWIG_NewPointerObj(L,(void *) resultptr,SWIGTYPE_p_osg__Color3T_float_t,1); SWIG_arg++;
          }
          //Color4f
          else if(FieldContentType == osg::FieldDataTraits<osg::Color4f>::getType() )
          {
              osg::Color4f * resultptr = new osg::Color4f((const osg::Color4f &) dynamic_cast<const osg::SFColor4f*>(TheField)->getValue());
              SWIG_NewPointerObj(L,(void *) resultptr,SWIGTYPE_p_osg__Color4T_float_t,1); SWIG_arg++;
          }
          //Vec2f
          else if(FieldContentType == osg::FieldDataTraits<osg::Vec2f>::getType() )
          {
              osg::Vec2f * resultptr = new osg::Vec2f((const osg::Vec2f &) dynamic_cast<const osg::SFVec2f*>(TheField)->getValue());
              SWIG_NewPointerObj(L,(void *) resultptr,SWIGTYPE_p_osg__Vec2f,1); SWIG_arg++;
          }
          //Vec3f
          else if(FieldContentType == osg::FieldDataTraits<osg::Vec3f>::getType() )
          {
              osg::Vec3f * resultptr = new osg::Vec3f((const osg::Vec3f &) dynamic_cast<const osg::SFVec3f*>(TheField)->getValue());
              SWIG_NewPointerObj(L,(void *) resultptr,SWIGTYPE_p_osg__Vec3f,1); SWIG_arg++;
          }
          //Vec4f
          else if(FieldContentType == osg::FieldDataTraits<osg::Vec4f>::getType() )
          {
              osg::Vec4f * resultptr = new osg::Vec4f((const osg::Vec4f &) dynamic_cast<const osg::SFVec4f*>(TheField)->getValue());
              SWIG_NewPointerObj(L,(void *) resultptr,SWIGTYPE_p_osg__Vec4f,1); SWIG_arg++;
          }
          //Pnt2f
          else if(FieldContentType == osg::FieldDataTraits<osg::Pnt2f>::getType() )
          {
              osg::Pnt2f * resultptr = new osg::Pnt2f((const osg::Pnt2f &) dynamic_cast<const osg::SFPnt2f*>(TheField)->getValue());
              SWIG_NewPointerObj(L,(void *) resultptr,SWIGTYPE_p_osg__Pnt2f,1); SWIG_arg++;
          }
          //Pnt3f
          else if(FieldContentType == osg::FieldDataTraits<osg::Pnt3f>::getType() )
          {
              osg::Pnt3f * resultptr = new osg::Pnt3f((const osg::Pnt3f &) dynamic_cast<const osg::SFPnt3f*>(TheField)->getValue());
              SWIG_NewPointerObj(L,(void *) resultptr,SWIGTYPE_p_osg__Pnt3f,1); SWIG_arg++;
          }
          //Pnt4f
          else if(FieldContentType == osg::FieldDataTraits<osg::Pnt4f>::getType() )
          {
              osg::Pnt4f * resultptr = new osg::Pnt4f((const osg::Pnt4f &) dynamic_cast<const osg::SFPnt4f*>(TheField)->getValue());
              SWIG_NewPointerObj(L,(void *) resultptr,SWIGTYPE_p_osg__Pnt4f,1); SWIG_arg++;
          }
          //Matrix
          else if(FieldContentType == osg::FieldDataTraits<osg::Matrix>::getType() )
          {
              osg::Matrix * resultptr = new osg::Matrix((const osg::Matrix &) dynamic_cast<const osg::SFMatrix*>(TheField)->getValue());
              SWIG_NewPointerObj(L,(void *) resultptr,SWIGTYPE_p_osg__Matrix,1); SWIG_arg++;
          }
          //Quaternion
          else if(FieldContentType == osg::FieldDataTraits<osg::Quaternion>::getType() )
          {
              osg::Quaternion * resultptr = new osg::Quaternion((const osg::Quaternion &) dynamic_cast<const osg::SFQuaternion*>(TheField)->getValue());
              SWIG_NewPointerObj(L,(void *) resultptr,SWIGTYPE_p_osg__Quaternion,1); SWIG_arg++;
          }
          //FieldContainerPtrs
          else if(isFieldAFieldContainerPtr(TheField))
          {
            osg::FieldContainerPtr * resultptr = new osg::FieldContainerPtr((const osg::FieldContainerPtr &) static_cast<const osg::SFFieldContainerPtr *>(TheField)->getValue());
            SWIG_NewPointerObj(L,(void *) resultptr,SWIGTYPE_p_osg__FieldContainerPtr,1); SWIG_arg++;
          }
          //Volumes
          //otherwize
          else
          {
              TheField->getValueByStr(result);
              lua_pushstring(L,result.c_str()); SWIG_arg++;
          }
          return SWIG_arg;
          
          if(0) SWIG_fail;
        }
        else if (argc == 3) {
          osg::FieldContainerPtr *arg1 = (osg::FieldContainerPtr *) 0 ;
          osg::Char8 *arg2 = (osg::Char8 *) 0 ;
          osg::UInt32 arg3 ;
          std::string result;
          
          SWIG_check_num_args("getFieldValue",3,3)
          if(!SWIG_isptrtype(L,1)) SWIG_fail_arg("getFieldValue",1,"osg::FieldContainerPtr *");
          if(!lua_isstring(L,2)) SWIG_fail_arg("getFieldValue",2,"osg::Char8 const *");
          if(!lua_isnumber(L,3)) SWIG_fail_arg("getFieldValue",3,"osg::UInt32");
              
          if (!SWIG_IsOK(SWIG_ConvertPtr(L,1,(void**)&arg1,SWIGTYPE_p_osg__FieldContainerPtr,0))){
            SWIG_fail_ptr("getFieldValue",1,SWIGTYPE_p_osg__FieldContainerPtr);
          }
          arg2 = (osg::Char8 *)lua_tostring(L, 2);
          arg3 = (osg::UInt32)lua_tonumber(L, 3);
          
          const osg::Field* TheField((*arg1)->getField(arg2));
          if(TheField == NULL)
          {
              lua_pushfstring(L,"Error in getFieldValue there is no field of name '%s' on type '%s'",arg2,(*arg1)->getTypeName());
              goto fail;
          }
          if(TheField->getCardinality() == osg::FieldType::SINGLE_FIELD)
          {
              lua_pushfstring(L,"Error in getFieldValue field of name '%s' on type '%s' is a single-field, you do not need to supply an index..",arg2,(*arg1)->getTypeName());
              goto fail;
          }
          //Types
          const osg::DataType& FieldContentType(TheField->getContentType());
#if defined(WIN32)
          //bool
          //string
          if(FieldContentType == osg::FieldDataTraits<std::string>::getType() )
#else
          //bool
          if(FieldContentType == osg::FieldDataTraits2<bool>::getType() )
          {
              lua_pushboolean(L,dynamic_cast<const osg::MFBool*>(TheField)->getValue(arg3)); SWIG_arg++;
          }
          //string
          else if(FieldContentType == osg::FieldDataTraits<std::string>::getType() )
#endif
          {
              lua_pushstring(L,dynamic_cast<const osg::MFString*>(TheField)->getValue(arg3).c_str()); SWIG_arg++;
          }
          //UInt8
          else if(FieldContentType == osg::FieldDataTraits<osg::UInt8>::getType() )
          {
              lua_pushnumber(L,dynamic_cast<const osg::MFUInt8*>(TheField)->getValue(arg3)); SWIG_arg++;
          }
          //UInt16
          else if(FieldContentType == osg::FieldDataTraits<osg::UInt16>::getType() )
          {
              lua_pushnumber(L,dynamic_cast<const osg::MFUInt16*>(TheField)->getValue(arg3)); SWIG_arg++;
          }
          //UInt32
          else if(FieldContentType == osg::FieldDataTraits<osg::UInt32>::getType() )
          {
              lua_pushnumber(L,dynamic_cast<const osg::MFUInt32*>(TheField)->getValue(arg3)); SWIG_arg++;
          }
          //UInt64
          else if(FieldContentType == osg::FieldDataTraits<osg::UInt64>::getType() )
          {
              lua_pushnumber(L,dynamic_cast<const osg::MFUInt64*>(TheField)->getValue(arg3)); SWIG_arg++;
          }
          //BitVector
          else if(FieldContentType == osg::FieldDataTraits1<osg::BitVector>::getType() )
          {
              lua_pushnumber(L,dynamic_cast<const osg::MFBitVector*>(TheField)->getValue(arg3)); SWIG_arg++;
          }
          //GLenum
          else if(FieldContentType == osg::FieldDataTraits1<GLenum>::getType() )
          {
              lua_pushnumber(L,dynamic_cast<const osg::MFGLenum*>(TheField)->getValue(arg3)); SWIG_arg++;
          }
          //Int8
          else if(FieldContentType == osg::FieldDataTraits<osg::Int8>::getType() )
          {
              lua_pushnumber(L,dynamic_cast<const osg::MFInt8*>(TheField)->getValue(arg3)); SWIG_arg++;
          }
          //Int16
          else if(FieldContentType == osg::FieldDataTraits<osg::Int16>::getType() )
          {
              lua_pushnumber(L,dynamic_cast<const osg::MFInt16*>(TheField)->getValue(arg3)); SWIG_arg++;
          }
          //Int32
          else if(FieldContentType == osg::FieldDataTraits<osg::Int32>::getType() )
          {
              lua_pushnumber(L,dynamic_cast<const osg::MFInt32*>(TheField)->getValue(arg3)); SWIG_arg++;
          }
          //Int64
          else if(FieldContentType == osg::FieldDataTraits<osg::Int64>::getType() )
          {
              lua_pushnumber(L,dynamic_cast<const osg::MFInt64*>(TheField)->getValue(arg3)); SWIG_arg++;
          }
          //Real32
          else if(FieldContentType == osg::FieldDataTraits<osg::Real32>::getType() )
          {
              lua_pushnumber(L,dynamic_cast<const osg::MFReal32*>(TheField)->getValue(arg3)); SWIG_arg++;
          }
          //Time
          else if(FieldContentType == osg::FieldDataTraits1<osg::Time>::getType() )
          {
              lua_pushnumber(L,dynamic_cast<const osg::MFTime*>(TheField)->getValue(arg3)); SWIG_arg++;
          }
          //Real64
          else if(FieldContentType == osg::FieldDataTraits<osg::Real64>::getType() )
          {
              lua_pushnumber(L,dynamic_cast<const osg::MFReal64*>(TheField)->getValue(arg3)); SWIG_arg++;
          }
          //Color3f
          else if(FieldContentType == osg::FieldDataTraits<osg::Color3f>::getType() )
          {
              osg::Color3f * resultptr = new osg::Color3f((const osg::Color3f &) dynamic_cast<const osg::MFColor3f*>(TheField)->getValue(arg3));
              SWIG_NewPointerObj(L,(void *) resultptr,SWIGTYPE_p_osg__Color3T_float_t,1); SWIG_arg++;
          }
          //Color4f
          else if(FieldContentType == osg::FieldDataTraits<osg::Color4f>::getType() )
          {
              osg::Color4f * resultptr = new osg::Color4f((const osg::Color4f &) dynamic_cast<const osg::MFColor4f*>(TheField)->getValue(arg3));
              SWIG_NewPointerObj(L,(void *) resultptr,SWIGTYPE_p_osg__Color4T_float_t,1); SWIG_arg++;
          }
          //Vec2f
          else if(FieldContentType == osg::FieldDataTraits<osg::Vec2f>::getType() )
          {
              osg::Vec2f * resultptr = new osg::Vec2f((const osg::Vec2f &) dynamic_cast<const osg::MFVec2f*>(TheField)->getValue(arg3));
              SWIG_NewPointerObj(L,(void *) resultptr,SWIGTYPE_p_osg__Vec2f,1); SWIG_arg++;
          }
          //Vec3f
          else if(FieldContentType == osg::FieldDataTraits<osg::Vec3f>::getType() )
          {
              osg::Vec3f * resultptr = new osg::Vec3f((const osg::Vec3f &) dynamic_cast<const osg::MFVec3f*>(TheField)->getValue(arg3));
              SWIG_NewPointerObj(L,(void *) resultptr,SWIGTYPE_p_osg__Vec3f,1); SWIG_arg++;
          }
          //Vec4f
          else if(FieldContentType == osg::FieldDataTraits<osg::Vec4f>::getType() )
          {
              osg::Vec4f * resultptr = new osg::Vec4f((const osg::Vec4f &) dynamic_cast<const osg::MFVec4f*>(TheField)->getValue(arg3));
              SWIG_NewPointerObj(L,(void *) resultptr,SWIGTYPE_p_osg__Vec4f,1); SWIG_arg++;
          }
          //Pnt2f
          else if(FieldContentType == osg::FieldDataTraits<osg::Pnt2f>::getType() )
          {
              osg::Pnt2f * resultptr = new osg::Pnt2f((const osg::Pnt2f &) dynamic_cast<const osg::MFPnt2f*>(TheField)->getValue(arg3));
              SWIG_NewPointerObj(L,(void *) resultptr,SWIGTYPE_p_osg__Pnt2f,1); SWIG_arg++;
          }
          //Pnt3f
          else if(FieldContentType == osg::FieldDataTraits<osg::Pnt3f>::getType() )
          {
              osg::Pnt3f * resultptr = new osg::Pnt3f((const osg::Pnt3f &) dynamic_cast<const osg::MFPnt3f*>(TheField)->getValue(arg3));
              SWIG_NewPointerObj(L,(void *) resultptr,SWIGTYPE_p_osg__Pnt3f,1); SWIG_arg++;
          }
          //Pnt4f
          else if(FieldContentType == osg::FieldDataTraits<osg::Pnt4f>::getType() )
          {
              osg::Pnt4f * resultptr = new osg::Pnt4f((const osg::Pnt4f &) dynamic_cast<const osg::MFPnt4f*>(TheField)->getValue(arg3));
              SWIG_NewPointerObj(L,(void *) resultptr,SWIGTYPE_p_osg__Pnt4f,1); SWIG_arg++;
          }
          //Matrix
          else if(FieldContentType == osg::FieldDataTraits<osg::Matrix>::getType() )
          {
              osg::Matrix * resultptr = new osg::Matrix((const osg::Matrix &) dynamic_cast<const osg::MFMatrix*>(TheField)->getValue(arg3));
              SWIG_NewPointerObj(L,(void *) resultptr,SWIGTYPE_p_osg__Matrix,1); SWIG_arg++;
          }
          //Quaternion
          else if(FieldContentType == osg::FieldDataTraits<osg::Quaternion>::getType() )
          {
              osg::Quaternion * resultptr = new osg::Quaternion((const osg::Quaternion &) dynamic_cast<const osg::MFQuaternion*>(TheField)->getValue(arg3));
              SWIG_NewPointerObj(L,(void *) resultptr,SWIGTYPE_p_osg__Quaternion,1); SWIG_arg++;
          }
          //FieldContainerPtrs
          else if(isFieldAFieldContainerPtr(TheField))
          {
            osg::FieldContainerPtr * resultptr = new osg::FieldContainerPtr((const osg::FieldContainerPtr &) static_cast<const osg::MFFieldContainerPtr *>(TheField)->getValue(arg3));
            SWIG_NewPointerObj(L,(void *) resultptr,SWIGTYPE_p_osg__FieldContainerPtr,1); SWIG_arg++;
          }
          //Volumes
          //otherwize
          else
          {
              TheField->getValueByStr(result, arg3);
              lua_pushstring(L,result.c_str()); SWIG_arg++;
          }
          return SWIG_arg;
          
          if(0) SWIG_fail;
        }
      
    fail:
      lua_error(L);
      return SWIG_arg;
    }
    
    bool LUA_BINDING_check_num_args(lua_State*L, char* func_name,unsigned int a,unsigned int b)
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
          osg::FieldContainerPtr *arg1 = (osg::FieldContainerPtr *) 0 ;
          osg::Char8 *arg2 = (osg::Char8 *) 0 ;
          
          //Check if there are the correct number of arguments
          if (!LUA_BINDING_check_num_args(L,"setFieldValue",3,3)){ return SWIG_arg;}
          //Check the type of argument 1
          if(!SWIG_isptrtype(L,1))
          {
              LUA_BINDING_fail_arg(L,"setFieldValue",1,"FieldContainerPtr *");
              return SWIG_arg;
          }
          //Check the type of argument 2
          if(!lua_isstring(L,2))
          {
              LUA_BINDING_fail_arg(L,"setFieldValue",2,"osg::Char8 const *'");
              return SWIG_arg;
          }
              
          //Check the pointer convertion on arg 1
          if (!SWIG_IsOK(SWIG_ConvertPtr(L,1,(void**)&arg1,SWIGTYPE_p_osg__FieldContainerPtr,0)))
          {
              LUA_BINDING_fail_ptr(L,"setFieldValue",1,SWIGTYPE_p_osg__FieldContainerPtr);
              return SWIG_arg;
          }
          //Cast arg 2 to a string
          arg2 = (osg::Char8 *)lua_tostring(L, 2);
          
          //Check that arg1 is not NullFC
          if((*arg1) == osg::NullFC)
          {
              lua_pushfstring(L,"Error in setFieldValue the FieldContainer given is Null");
              lua_error(L);
              return SWIG_arg;
          }
          //Check that the field referenced exists
          osg::Field* TheField((*arg1)->getField(arg2));
          if(TheField == NULL)
          {
              lua_pushfstring(L,"Error in setFieldValue there is no field of name '%s' on type '%s'",arg2,(*arg1)->getTypeName());
              lua_error(L);
              return SWIG_arg;
          }
          const osg::DataType& FieldContentType(TheField->getContentType());
          osg::BitVector TheMask((*arg1)->getType().findFieldDescription(arg2)->getFieldMask());
#if defined(WIN32)
          //bool
          //string
          if(FieldContentType == osg::FieldDataTraits<std::string>::getType() )
#else
          //bool
          if(FieldContentType == osg::FieldDataTraits2<bool>::getType() )
          {
              if(!lua_isboolean(L,3))
              {
                  LUA_BINDING_fail_arg(L,"setFieldValue",3,"boolean'");
                  return SWIG_arg;
              }
              osg::beginEditCP((*arg1), TheMask);
                  dynamic_cast<osg::SFBool*>(TheField)->setValue(static_cast<bool>(lua_toboolean(L, 3)));
              osg::endEditCP((*arg1), TheMask);
          }
          //string
          else if(FieldContentType == osg::FieldDataTraits<std::string>::getType() )
#endif
          {
              if(!lua_isstring(L,3))
              {
                  LUA_BINDING_fail_arg(L,"setFieldValue",3,"string'");
                  return SWIG_arg;
              }
              osg::beginEditCP((*arg1), TheMask);
                  dynamic_cast<osg::SFString*>(TheField)->setValue(static_cast<const osg::Char8*>(lua_tostring(L, 3)));
              osg::endEditCP((*arg1), TheMask);
          }
          //UInt8
          else if(FieldContentType == osg::FieldDataTraits<osg::UInt8>::getType() )
          {
              if(!lua_isnumber(L,3))
              {
                  LUA_BINDING_fail_arg(L,"setFieldValue",3,"UInt8'");
                  return SWIG_arg;
              }
              osg::beginEditCP((*arg1), TheMask);
                  dynamic_cast<osg::SFUInt8*>(TheField)->setValue(static_cast<osg::UInt8>(lua_tonumber(L, 3)));
              osg::endEditCP((*arg1), TheMask);
          }
          //UInt16
          else if(FieldContentType == osg::FieldDataTraits<osg::UInt16>::getType() )
          {
              if(!lua_isnumber(L,3))
              {
                  LUA_BINDING_fail_arg(L,"setFieldValue",3,"UInt16'");
                  return SWIG_arg;
              }
              osg::beginEditCP((*arg1), TheMask);
                  dynamic_cast<osg::SFUInt16*>(TheField)->setValue(static_cast<osg::UInt16>(lua_tonumber(L, 3)));
              osg::endEditCP((*arg1), TheMask);
          }
          //UInt32
          else if(TheField->getContentType() == osg::FieldDataTraits<osg::UInt32>::getType()) 
          {
              if(!lua_isnumber(L,3))
              {
                  LUA_BINDING_fail_arg(L,"setFieldValue",3,"UInt32'");
                  return SWIG_arg;
              }
              osg::beginEditCP((*arg1), TheMask);
                  dynamic_cast<osg::SFUInt32*>(TheField)->setValue(static_cast<osg::UInt32>(lua_tonumber(L, 3)));
              osg::endEditCP((*arg1), TheMask);
          }
          //UInt64
          else if(FieldContentType == osg::FieldDataTraits<osg::UInt64>::getType() )
          {
              if(!lua_isnumber(L,3))
              {
                  LUA_BINDING_fail_arg(L,"setFieldValue",3,"UInt64'");
                  return SWIG_arg;
              }
              osg::beginEditCP((*arg1), TheMask);
                  dynamic_cast<osg::SFUInt64*>(TheField)->setValue(static_cast<osg::UInt64>(lua_tonumber(L, 3)));
              osg::endEditCP((*arg1), TheMask);
          }
          //BitVector
          else if(FieldContentType == osg::FieldDataTraits1<osg::BitVector>::getType() )
          {
              if(!lua_isnumber(L,3))
              {
                  LUA_BINDING_fail_arg(L,"setFieldValue",3,"BitVector'");
                  return SWIG_arg;
              }
              osg::beginEditCP((*arg1), TheMask);
                  dynamic_cast<osg::SFBitVector*>(TheField)->setValue(static_cast<osg::BitVector>(lua_tonumber(L, 3)));
              osg::endEditCP((*arg1), TheMask);
          }
          //GLenum
          else if(FieldContentType == osg::FieldDataTraits1<GLenum>::getType() )
          {
              if(!lua_isnumber(L,3))
              {
                  LUA_BINDING_fail_arg(L,"setFieldValue",3,"GLenum'");
                  return SWIG_arg;
              }
              osg::beginEditCP((*arg1), TheMask);
                  dynamic_cast<osg::SFGLenum*>(TheField)->setValue(static_cast<GLenum>(lua_tonumber(L, 3)));
              osg::endEditCP((*arg1), TheMask);
          }
          //Int8
          else if(FieldContentType == osg::FieldDataTraits<osg::Int8>::getType() )
          {
              if(!lua_isnumber(L,3))
              {
                  LUA_BINDING_fail_arg(L,"setFieldValue",3,"Int8'");
                  return SWIG_arg;
              }
              osg::beginEditCP((*arg1), TheMask);
                  dynamic_cast<osg::SFInt8*>(TheField)->setValue(static_cast<osg::Int8>(lua_tonumber(L, 3)));
              osg::endEditCP((*arg1), TheMask);
          }
          //Int16
          else if(FieldContentType == osg::FieldDataTraits<osg::Int16>::getType() )
          {
              if(!lua_isnumber(L,3))
              {
                  LUA_BINDING_fail_arg(L,"setFieldValue",3,"Int16'");
                  return SWIG_arg;
              }
              osg::beginEditCP((*arg1), TheMask);
                  dynamic_cast<osg::SFInt16*>(TheField)->setValue(static_cast<osg::Int16>(lua_tonumber(L, 3)));
              osg::endEditCP((*arg1), TheMask);
          }
          //Int32
          else if(FieldContentType == osg::FieldDataTraits<osg::Int32>::getType() )
          {
              if(!lua_isnumber(L,3))
              {
                  LUA_BINDING_fail_arg(L,"setFieldValue",3,"Int32'");
                  return SWIG_arg;
              }
              osg::beginEditCP((*arg1), TheMask);
                  dynamic_cast<osg::SFInt32*>(TheField)->setValue(static_cast<osg::Int32>(lua_tonumber(L, 3)));
              osg::endEditCP((*arg1), TheMask);
          }
          //Int64
          else if(FieldContentType == osg::FieldDataTraits<osg::Int64>::getType() )
          {
              if(!lua_isnumber(L,3))
              {
                  LUA_BINDING_fail_arg(L,"setFieldValue",3,"Int64'");
                  return SWIG_arg;
              }
              osg::beginEditCP((*arg1), TheMask);
                  dynamic_cast<osg::SFInt64*>(TheField)->setValue(static_cast<osg::Int64>(lua_tonumber(L, 3)));
              osg::endEditCP((*arg1), TheMask);
          }
          //Real32
          else if(FieldContentType == osg::FieldDataTraits<osg::Real32>::getType() )
          {
              if(!lua_isnumber(L,3))
              {
                  LUA_BINDING_fail_arg(L,"setFieldValue",3,"Real32'");
                  return SWIG_arg;
              }
              osg::beginEditCP((*arg1), TheMask);
                  dynamic_cast<osg::SFReal32*>(TheField)->setValue(static_cast<osg::Real32>(lua_tonumber(L, 3)));
              osg::endEditCP((*arg1), TheMask);
          }
          //Time
          else if(FieldContentType == osg::FieldDataTraits1<osg::Time>::getType() )
          {
              if(!lua_isnumber(L,3))
              {
                  LUA_BINDING_fail_arg(L,"setFieldValue",3,"Time'");
                  return SWIG_arg;
              }
              osg::beginEditCP((*arg1), TheMask);
                  dynamic_cast<osg::SFTime*>(TheField)->setValue(static_cast<osg::Time>(lua_tonumber(L, 3)));
              osg::endEditCP((*arg1), TheMask);
          }
          //Real64
          else if(FieldContentType == osg::FieldDataTraits<osg::Real64>::getType() )
          {
              if(!lua_isnumber(L,3))
              {
                  LUA_BINDING_fail_arg(L,"setFieldValue",3,"Real64'");
                  return SWIG_arg;
              }
              osg::beginEditCP((*arg1), TheMask);
                  dynamic_cast<osg::SFReal64*>(TheField)->setValue(static_cast<osg::Real64>(lua_tonumber(L, 3)));
              osg::endEditCP((*arg1), TheMask);
          }
          //Color3f
          else if(FieldContentType == osg::FieldDataTraits<osg::Color3f>::getType() )
          {
              osg::Color3f *arg3 = 0 ;
              if (!SWIG_IsOK(SWIG_ConvertPtr(L,3,(void**)&arg3,SWIGTYPE_p_osg__Color3T_float_t,0))){
                  LUA_BINDING_fail_ptr(L,"setFieldValue",3,SWIGTYPE_p_osg__Color3T_float_t);
                  return SWIG_arg;
              }
              
              osg::beginEditCP((*arg1), TheMask);
                  dynamic_cast<osg::SFColor3f*>(TheField)->setValue(static_cast<osg::Color3f const &>(*arg3));
              osg::endEditCP((*arg1), TheMask);
          }
          //Color4f
          else if(FieldContentType == osg::FieldDataTraits<osg::Color4f>::getType() )
          {
              osg::Color4f *arg3 = 0 ;
              if (!SWIG_IsOK(SWIG_ConvertPtr(L,3,(void**)&arg3,SWIGTYPE_p_osg__Color4T_float_t,0))){
                  LUA_BINDING_fail_ptr(L,"setFieldValue",3,SWIGTYPE_p_osg__Color4T_float_t);
                  return SWIG_arg;
              }
              
              osg::beginEditCP((*arg1), TheMask);
                  dynamic_cast<osg::SFColor4f*>(TheField)->setValue(static_cast<osg::Color4f const &>(*arg3));
              osg::endEditCP((*arg1), TheMask);
          }
          //Vec2f
          else if(FieldContentType == osg::FieldDataTraits<osg::Vec2f>::getType() )
          {
              osg::Vec2f *arg3 = 0 ;
              if (!SWIG_IsOK(SWIG_ConvertPtr(L,3,(void**)&arg3,SWIGTYPE_p_osg__Vec2f,0))){
                  LUA_BINDING_fail_ptr(L,"setFieldValue",3,SWIGTYPE_p_osg__Vec2f);
                  return SWIG_arg;
              }
              
              osg::beginEditCP((*arg1), TheMask);
                  dynamic_cast<osg::SFVec2f*>(TheField)->setValue(static_cast<osg::Vec2f const &>(*arg3));
              osg::endEditCP((*arg1), TheMask);
          }
          //Vec3f
          else if(FieldContentType == osg::FieldDataTraits<osg::Vec3f>::getType() )
          {
              osg::Vec3f *arg3 = 0 ;
              if (!SWIG_IsOK(SWIG_ConvertPtr(L,3,(void**)&arg3,SWIGTYPE_p_osg__Vec3f,0))){
                  LUA_BINDING_fail_ptr(L,"setFieldValue",3,SWIGTYPE_p_osg__Vec3f);
                  return SWIG_arg;
              }
              
              osg::beginEditCP((*arg1), TheMask);
                  dynamic_cast<osg::SFVec3f*>(TheField)->setValue(static_cast<osg::Vec3f const &>(*arg3));
              osg::endEditCP((*arg1), TheMask);
          }
          //Vec4f
          else if(FieldContentType == osg::FieldDataTraits<osg::Vec4f>::getType() )
          {
              osg::Vec4f *arg3 = 0 ;
              if (!SWIG_IsOK(SWIG_ConvertPtr(L,3,(void**)&arg3,SWIGTYPE_p_osg__Vec4f,0))){
                  LUA_BINDING_fail_ptr(L,"setFieldValue",3,SWIGTYPE_p_osg__Vec4f);
                  return SWIG_arg;
              }
              
              osg::beginEditCP((*arg1), TheMask);
                  dynamic_cast<osg::SFVec4f*>(TheField)->setValue(static_cast<osg::Vec4f const &>(*arg3));
              osg::endEditCP((*arg1), TheMask);
          }
          //Pnt2f
          else if(FieldContentType == osg::FieldDataTraits<osg::Pnt2f>::getType() )
          {
              osg::Pnt2f *arg3 = 0 ;
              if (!SWIG_IsOK(SWIG_ConvertPtr(L,3,(void**)&arg3,SWIGTYPE_p_osg__Pnt2f,0))){
                  LUA_BINDING_fail_ptr(L,"setFieldValue",3,SWIGTYPE_p_osg__Pnt2f);
                  return SWIG_arg;
              }
              
              osg::beginEditCP((*arg1), TheMask);
                  dynamic_cast<osg::SFPnt2f*>(TheField)->setValue(static_cast<osg::Pnt2f const &>(*arg3));
              osg::endEditCP((*arg1), TheMask);
          }
          //Pnt3f
          else if(FieldContentType == osg::FieldDataTraits<osg::Pnt3f>::getType() )
          {
              osg::Pnt3f *arg3 = 0 ;
              if (!SWIG_IsOK(SWIG_ConvertPtr(L,3,(void**)&arg3,SWIGTYPE_p_osg__Pnt3f,0))){
                  LUA_BINDING_fail_ptr(L,"setFieldValue",3,SWIGTYPE_p_osg__Pnt3f);
                  return SWIG_arg;
              }
              
              osg::beginEditCP((*arg1), TheMask);
                  dynamic_cast<osg::SFPnt3f*>(TheField)->setValue(static_cast<osg::Pnt3f const &>(*arg3));
              osg::endEditCP((*arg1), TheMask);
          }
          //Pnt4f
          else if(FieldContentType == osg::FieldDataTraits<osg::Pnt4f>::getType() )
          {
              osg::Pnt4f *arg3 = 0 ;
              if (!SWIG_IsOK(SWIG_ConvertPtr(L,3,(void**)&arg3,SWIGTYPE_p_osg__Pnt4f,0))){
                  LUA_BINDING_fail_ptr(L,"setFieldValue",3,SWIGTYPE_p_osg__Pnt4f);
                  return SWIG_arg;
              }
              
              osg::beginEditCP((*arg1), TheMask);
                  dynamic_cast<osg::SFPnt4f*>(TheField)->setValue(static_cast<osg::Pnt4f const &>(*arg3));
              osg::endEditCP((*arg1), TheMask);
          }
          //Matrix
          else if(FieldContentType == osg::FieldDataTraits<osg::Matrix>::getType() )
          {
              osg::Matrix *arg3 = 0 ;
              if (!SWIG_IsOK(SWIG_ConvertPtr(L,3,(void**)&arg3,SWIGTYPE_p_osg__Matrix,0))){
                  LUA_BINDING_fail_ptr(L,"setFieldValue",3,SWIGTYPE_p_osg__Matrix);
                  return SWIG_arg;
              }
              
              osg::beginEditCP((*arg1), TheMask);
                  dynamic_cast<osg::SFMatrix*>(TheField)->setValue(static_cast<osg::Matrix const &>(*arg3));
              osg::endEditCP((*arg1), TheMask);
          }
          //Quaternion
          else if(FieldContentType == osg::FieldDataTraits<osg::Quaternion>::getType() )
          {
              osg::Quaternion *arg3 = 0 ;
              if (!SWIG_IsOK(SWIG_ConvertPtr(L,3,(void**)&arg3,SWIGTYPE_p_osg__Quaternion,0))){
                  LUA_BINDING_fail_ptr(L,"setFieldValue",3,SWIGTYPE_p_osg__Quaternion);
                  return SWIG_arg;
              }
              
              osg::beginEditCP((*arg1), TheMask);
                  dynamic_cast<osg::SFQuaternion*>(TheField)->setValue(static_cast<osg::Quaternion const &>(*arg3));
              osg::endEditCP((*arg1), TheMask);
          }
          //FieldContainerPtrs
          else if(isFieldAFieldContainerPtr(TheField))
          {
              osg::FieldContainerPtr *arg3 = (osg::FieldContainerPtr *) 0 ;
              if (!SWIG_IsOK(SWIG_ConvertPtr(L,3,(void**)&arg3,SWIGTYPE_p_osg__FieldContainerPtr,0)))
              {
                  LUA_BINDING_fail_ptr(L,"setFieldValue",3,SWIGTYPE_p_osg__FieldContainerPtr);
                  return SWIG_arg;
              }
              osg::beginEditCP((*arg1), TheMask);
                  static_cast<osg::SFFieldContainerPtr*>(TheField)->setValue(*arg3);
              osg::endEditCP((*arg1), TheMask);
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
              osg::beginEditCP((*arg1), TheMask);
                  TheField->pushValueByStr((osg::Char8 *)lua_tostring(L, 3));
              osg::endEditCP((*arg1), TheMask);
          }
        }
        else if (argc == 4) {
          osg::FieldContainerPtr *arg1 = (osg::FieldContainerPtr *) 0 ;
          osg::Char8 *arg2 = (osg::Char8 *) 0 ;
          osg::UInt32 arg4 ;
          
          //Check if there are the correct number of arguments
          if (!LUA_BINDING_check_num_args(L,"setFieldValue",4,4)){ return SWIG_arg;}
          //Check the type of argument 1
          if(!SWIG_isptrtype(L,1))
          {
              LUA_BINDING_fail_arg(L,"setFieldValue",1,"FieldContainerPtr *");
              return SWIG_arg;
          }
          //Check the type of argument 2
          if(!lua_isstring(L,2))
          {
              LUA_BINDING_fail_arg(L,"setFieldValue",2,"osg::Char8 const *'");
              return SWIG_arg;
          }
          if(!lua_isnumber(L,4))
          {
              LUA_BINDING_fail_arg(L,"setFieldValue",4,"osg::UInt32'");
              return SWIG_arg;
          }
              
          //Check the pointer convertion on arg 1
          if (!SWIG_IsOK(SWIG_ConvertPtr(L,1,(void**)&arg1,SWIGTYPE_p_osg__FieldContainerPtr,0)))
          {
              LUA_BINDING_fail_ptr(L,"setFieldValue",1,SWIGTYPE_p_osg__FieldContainerPtr);
              return SWIG_arg;
          }
          //Cast arg 2 to a string
          arg2 = (osg::Char8 *)lua_tostring(L, 2);
          arg4 = (osg::UInt32)lua_tonumber(L, 4);
          
          //Check that arg1 is not NullFC
          if((*arg1) == osg::NullFC)
          {
              lua_pushfstring(L,"Error in setFieldValue the FieldContainer given is Null");
              lua_error(L);
              return SWIG_arg;
          }
          //Check that the field referenced exists
          osg::Field* TheField((*arg1)->getField(arg2));
          if(TheField == NULL)
          {
              lua_pushfstring(L,"Error in setFieldValue there is no field of name '%s' on type '%s'",arg2,(*arg1)->getTypeName());
              lua_error(L);
              return SWIG_arg;
          }
          if(TheField->getCardinality() == osg::FieldType::SINGLE_FIELD)
          {
              lua_pushfstring(L,"Error in setFieldValue field of name '%s' on type '%s' is a single-field, you do not need to supply an index..",arg2,(*arg1)->getTypeName());
              lua_error(L);
              return SWIG_arg;
          }
          const osg::DataType& FieldContentType(TheField->getContentType());
          osg::BitVector TheMask((*arg1)->getType().findFieldDescription(arg2)->getFieldMask());
#if defined(WIN32)
          //bool
          //string
          if(FieldContentType == osg::FieldDataTraits<std::string>::getType() )
#else
          //bool
          if(FieldContentType == osg::FieldDataTraits2<bool>::getType() )
          {
              if(!lua_isboolean(L,3))
              {
                  LUA_BINDING_fail_arg(L,"setFieldValue",3,"boolean'");
                  return SWIG_arg;
              }
              osg::beginEditCP((*arg1), TheMask);
                  dynamic_cast<osg::MFBool*>(TheField)->operator[](arg4) = (static_cast<bool>(lua_toboolean(L, 3)));
              osg::endEditCP((*arg1), TheMask);
          }
          //string
          else if(FieldContentType == osg::FieldDataTraits<std::string>::getType() )
#endif
          {
              if(!lua_isstring(L,3))
              {
                  LUA_BINDING_fail_arg(L,"setFieldValue",3,"string'");
                  return SWIG_arg;
              }
              osg::beginEditCP((*arg1), TheMask);
                  dynamic_cast<osg::MFString*>(TheField)->operator[](arg4) = (static_cast<const osg::Char8*>(lua_tostring(L, 3)));
              osg::endEditCP((*arg1), TheMask);
          }
          //UInt8
          else if(FieldContentType == osg::FieldDataTraits<osg::UInt8>::getType() )
          {
              if(!lua_isnumber(L,3))
              {
                  LUA_BINDING_fail_arg(L,"setFieldValue",3,"UInt8'");
                  return SWIG_arg;
              }
              osg::beginEditCP((*arg1), TheMask);
                  dynamic_cast<osg::MFUInt8*>(TheField)->operator[](arg4) = (static_cast<osg::UInt8>(lua_tonumber(L, 3)));
              osg::endEditCP((*arg1), TheMask);
          }
          //UInt16
          else if(FieldContentType == osg::FieldDataTraits<osg::UInt16>::getType() )
          {
              if(!lua_isnumber(L,3))
              {
                  LUA_BINDING_fail_arg(L,"setFieldValue",3,"UInt16'");
                  return SWIG_arg;
              }
              osg::beginEditCP((*arg1), TheMask);
                  dynamic_cast<osg::MFUInt16*>(TheField)->operator[](arg4) = (static_cast<osg::UInt16>(lua_tonumber(L, 3)));
              osg::endEditCP((*arg1), TheMask);
          }
          //UInt32
          else if(TheField->getContentType() == osg::FieldDataTraits<osg::UInt32>::getType()) 
          {
              if(!lua_isnumber(L,3))
              {
                  LUA_BINDING_fail_arg(L,"setFieldValue",3,"UInt32'");
                  return SWIG_arg;
              }
              osg::beginEditCP((*arg1), TheMask);
                  dynamic_cast<osg::MFUInt32*>(TheField)->operator[](arg4) = (static_cast<osg::UInt32>(lua_tonumber(L, 3)));
              osg::endEditCP((*arg1), TheMask);
          }
          //UInt64
          else if(FieldContentType == osg::FieldDataTraits<osg::UInt64>::getType() )
          {
              if(!lua_isnumber(L,3))
              {
                  LUA_BINDING_fail_arg(L,"setFieldValue",3,"UInt64'");
                  return SWIG_arg;
              }
              osg::beginEditCP((*arg1), TheMask);
                  dynamic_cast<osg::MFUInt64*>(TheField)->operator[](arg4) = (static_cast<osg::UInt64>(lua_tonumber(L, 3)));
              osg::endEditCP((*arg1), TheMask);
          }
          //BitVector
          else if(FieldContentType == osg::FieldDataTraits1<osg::BitVector>::getType() )
          {
              if(!lua_isnumber(L,3))
              {
                  LUA_BINDING_fail_arg(L,"setFieldValue",3,"BitVector'");
                  return SWIG_arg;
              }
              osg::beginEditCP((*arg1), TheMask);
                  dynamic_cast<osg::MFBitVector*>(TheField)->operator[](arg4) = (static_cast<osg::BitVector>(lua_tonumber(L, 3)));
              osg::endEditCP((*arg1), TheMask);
          }
          //GLenum
          else if(FieldContentType == osg::FieldDataTraits1<GLenum>::getType() )
          {
              if(!lua_isnumber(L,3))
              {
                  LUA_BINDING_fail_arg(L,"setFieldValue",3,"GLenum'");
                  return SWIG_arg;
              }
              osg::beginEditCP((*arg1), TheMask);
                  dynamic_cast<osg::MFGLenum*>(TheField)->operator[](arg4) = (static_cast<GLenum>(lua_tonumber(L, 3)));
              osg::endEditCP((*arg1), TheMask);
          }
          //Int8
          else if(FieldContentType == osg::FieldDataTraits<osg::Int8>::getType() )
          {
              if(!lua_isnumber(L,3))
              {
                  LUA_BINDING_fail_arg(L,"setFieldValue",3,"Int8'");
                  return SWIG_arg;
              }
              osg::beginEditCP((*arg1), TheMask);
                  dynamic_cast<osg::MFInt8*>(TheField)->operator[](arg4) = (static_cast<osg::Int8>(lua_tonumber(L, 3)));
              osg::endEditCP((*arg1), TheMask);
          }
          //Int16
          else if(FieldContentType == osg::FieldDataTraits<osg::Int16>::getType() )
          {
              if(!lua_isnumber(L,3))
              {
                  LUA_BINDING_fail_arg(L,"setFieldValue",3,"Int16'");
                  return SWIG_arg;
              }
              osg::beginEditCP((*arg1), TheMask);
                  dynamic_cast<osg::MFInt16*>(TheField)->operator[](arg4) = (static_cast<osg::Int16>(lua_tonumber(L, 3)));
              osg::endEditCP((*arg1), TheMask);
          }
          //Int32
          else if(FieldContentType == osg::FieldDataTraits<osg::Int32>::getType() )
          {
              if(!lua_isnumber(L,3))
              {
                  LUA_BINDING_fail_arg(L,"setFieldValue",3,"Int32'");
                  return SWIG_arg;
              }
              osg::beginEditCP((*arg1), TheMask);
                  dynamic_cast<osg::MFInt32*>(TheField)->operator[](arg4) = (static_cast<osg::Int32>(lua_tonumber(L, 3)));
              osg::endEditCP((*arg1), TheMask);
          }
          //Int64
          else if(FieldContentType == osg::FieldDataTraits<osg::Int64>::getType() )
          {
              if(!lua_isnumber(L,3))
              {
                  LUA_BINDING_fail_arg(L,"setFieldValue",3,"Int64'");
                  return SWIG_arg;
              }
              osg::beginEditCP((*arg1), TheMask);
                  dynamic_cast<osg::MFInt64*>(TheField)->operator[](arg4) = (static_cast<osg::Int64>(lua_tonumber(L, 3)));
              osg::endEditCP((*arg1), TheMask);
          }
          //Real32
          else if(FieldContentType == osg::FieldDataTraits<osg::Real32>::getType() )
          {
              if(!lua_isnumber(L,3))
              {
                  LUA_BINDING_fail_arg(L,"setFieldValue",3,"Real32'");
                  return SWIG_arg;
              }
              osg::beginEditCP((*arg1), TheMask);
                  dynamic_cast<osg::MFReal32*>(TheField)->operator[](arg4) = (static_cast<osg::Real32>(lua_tonumber(L, 3)));
              osg::endEditCP((*arg1), TheMask);
          }
          //Time
          else if(FieldContentType == osg::FieldDataTraits1<osg::Time>::getType() )
          {
              if(!lua_isnumber(L,3))
              {
                  LUA_BINDING_fail_arg(L,"setFieldValue",3,"Time'");
                  return SWIG_arg;
              }
              osg::beginEditCP((*arg1), TheMask);
                  dynamic_cast<osg::MFTime*>(TheField)->operator[](arg4) = (static_cast<osg::Time>(lua_tonumber(L, 3)));
              osg::endEditCP((*arg1), TheMask);
          }
          //Real64
          else if(FieldContentType == osg::FieldDataTraits<osg::Real64>::getType() )
          {
              if(!lua_isnumber(L,3))
              {
                  LUA_BINDING_fail_arg(L,"setFieldValue",3,"Real64'");
                  return SWIG_arg;
              }
              osg::beginEditCP((*arg1), TheMask);
                  dynamic_cast<osg::MFReal64*>(TheField)->operator[](arg4) = (static_cast<osg::Real64>(lua_tonumber(L, 3)));
              osg::endEditCP((*arg1), TheMask);
          }
          //Color3f
          else if(FieldContentType == osg::FieldDataTraits<osg::Color3f>::getType() )
          {
              osg::Color3f *arg3 = 0 ;
              if (!SWIG_IsOK(SWIG_ConvertPtr(L,3,(void**)&arg3,SWIGTYPE_p_osg__Color3T_float_t,0))){
                  LUA_BINDING_fail_ptr(L,"setFieldValue",3,SWIGTYPE_p_osg__Color3T_float_t);
                  return SWIG_arg;
              }
              
              osg::beginEditCP((*arg1), TheMask);
                  dynamic_cast<osg::MFColor3f*>(TheField)->operator[](arg4) = (static_cast<osg::Color3f const &>(*arg3));
              osg::endEditCP((*arg1), TheMask);
          }
          //Color4f
          else if(FieldContentType == osg::FieldDataTraits<osg::Color4f>::getType() )
          {
              osg::Color4f *arg3 = 0 ;
              if (!SWIG_IsOK(SWIG_ConvertPtr(L,3,(void**)&arg3,SWIGTYPE_p_osg__Color4T_float_t,0))){
                  LUA_BINDING_fail_ptr(L,"setFieldValue",3,SWIGTYPE_p_osg__Color4T_float_t);
                  return SWIG_arg;
              }
              
              osg::beginEditCP((*arg1), TheMask);
                  dynamic_cast<osg::MFColor4f*>(TheField)->operator[](arg4) = (static_cast<osg::Color4f const &>(*arg3));
              osg::endEditCP((*arg1), TheMask);
          }
          //Vec2f
          else if(FieldContentType == osg::FieldDataTraits<osg::Vec2f>::getType() )
          {
              osg::Vec2f *arg3 = 0 ;
              if (!SWIG_IsOK(SWIG_ConvertPtr(L,3,(void**)&arg3,SWIGTYPE_p_osg__Vec2f,0))){
                  LUA_BINDING_fail_ptr(L,"setFieldValue",3,SWIGTYPE_p_osg__Vec2f);
                  return SWIG_arg;
              }
              
              osg::beginEditCP((*arg1), TheMask);
                  dynamic_cast<osg::MFVec2f*>(TheField)->operator[](arg4) = (static_cast<osg::Vec2f const &>(*arg3));
              osg::endEditCP((*arg1), TheMask);
          }
          //Vec3f
          else if(FieldContentType == osg::FieldDataTraits<osg::Vec3f>::getType() )
          {
              osg::Vec3f *arg3 = 0 ;
              if (!SWIG_IsOK(SWIG_ConvertPtr(L,3,(void**)&arg3,SWIGTYPE_p_osg__Vec3f,0))){
                  LUA_BINDING_fail_ptr(L,"setFieldValue",3,SWIGTYPE_p_osg__Vec3f);
                  return SWIG_arg;
              }
              
              osg::beginEditCP((*arg1), TheMask);
                  dynamic_cast<osg::MFVec3f*>(TheField)->operator[](arg4) = (static_cast<osg::Vec3f const &>(*arg3));
              osg::endEditCP((*arg1), TheMask);
          }
          //Vec4f
          else if(FieldContentType == osg::FieldDataTraits<osg::Vec4f>::getType() )
          {
              osg::Vec4f *arg3 = 0 ;
              if (!SWIG_IsOK(SWIG_ConvertPtr(L,3,(void**)&arg3,SWIGTYPE_p_osg__Vec4f,0))){
                  LUA_BINDING_fail_ptr(L,"setFieldValue",3,SWIGTYPE_p_osg__Vec4f);
                  return SWIG_arg;
              }
              
              osg::beginEditCP((*arg1), TheMask);
                  dynamic_cast<osg::MFVec4f*>(TheField)->operator[](arg4) = (static_cast<osg::Vec4f const &>(*arg3));
              osg::endEditCP((*arg1), TheMask);
          }
          //Pnt2f
          else if(FieldContentType == osg::FieldDataTraits<osg::Pnt2f>::getType() )
          {
              osg::Pnt2f *arg3 = 0 ;
              if (!SWIG_IsOK(SWIG_ConvertPtr(L,3,(void**)&arg3,SWIGTYPE_p_osg__Pnt2f,0))){
                  LUA_BINDING_fail_ptr(L,"setFieldValue",3,SWIGTYPE_p_osg__Pnt2f);
                  return SWIG_arg;
              }
              
              osg::beginEditCP((*arg1), TheMask);
                  dynamic_cast<osg::MFPnt2f*>(TheField)->operator[](arg4) = (static_cast<osg::Pnt2f const &>(*arg3));
              osg::endEditCP((*arg1), TheMask);
          }
          //Pnt3f
          else if(FieldContentType == osg::FieldDataTraits<osg::Pnt3f>::getType() )
          {
              osg::Pnt3f *arg3 = 0 ;
              if (!SWIG_IsOK(SWIG_ConvertPtr(L,3,(void**)&arg3,SWIGTYPE_p_osg__Pnt3f,0))){
                  LUA_BINDING_fail_ptr(L,"setFieldValue",3,SWIGTYPE_p_osg__Pnt3f);
                  return SWIG_arg;
              }
              
              osg::beginEditCP((*arg1), TheMask);
                  dynamic_cast<osg::MFPnt3f*>(TheField)->operator[](arg4) = (static_cast<osg::Pnt3f const &>(*arg3));
              osg::endEditCP((*arg1), TheMask);
          }
          //Pnt4f
          else if(FieldContentType == osg::FieldDataTraits<osg::Pnt4f>::getType() )
          {
              osg::Pnt4f *arg3 = 0 ;
              if (!SWIG_IsOK(SWIG_ConvertPtr(L,3,(void**)&arg3,SWIGTYPE_p_osg__Pnt4f,0))){
                  LUA_BINDING_fail_ptr(L,"setFieldValue",3,SWIGTYPE_p_osg__Pnt4f);
                  return SWIG_arg;
              }
              
              osg::beginEditCP((*arg1), TheMask);
                  dynamic_cast<osg::MFPnt4f*>(TheField)->operator[](arg4) = (static_cast<osg::Pnt4f const &>(*arg3));
              osg::endEditCP((*arg1), TheMask);
          }
          //Matrix
          else if(FieldContentType == osg::FieldDataTraits<osg::Matrix>::getType() )
          {
              osg::Matrix *arg3 = 0 ;
              if (!SWIG_IsOK(SWIG_ConvertPtr(L,3,(void**)&arg3,SWIGTYPE_p_osg__Matrix,0))){
                  LUA_BINDING_fail_ptr(L,"setFieldValue",3,SWIGTYPE_p_osg__Matrix);
                  return SWIG_arg;
              }
              
              osg::beginEditCP((*arg1), TheMask);
                  dynamic_cast<osg::MFMatrix*>(TheField)->operator[](arg4) = (static_cast<osg::Matrix const &>(*arg3));
              osg::endEditCP((*arg1), TheMask);
          }
          //Quaternion
          else if(FieldContentType == osg::FieldDataTraits<osg::Quaternion>::getType() )
          {
              osg::Quaternion *arg3 = 0 ;
              if (!SWIG_IsOK(SWIG_ConvertPtr(L,3,(void**)&arg3,SWIGTYPE_p_osg__Quaternion,0))){
                  LUA_BINDING_fail_ptr(L,"setFieldValue",3,SWIGTYPE_p_osg__Quaternion);
                  return SWIG_arg;
              }
              
              osg::beginEditCP((*arg1), TheMask);
                  dynamic_cast<osg::MFQuaternion*>(TheField)->operator[](arg4) = (static_cast<osg::Quaternion const &>(*arg3));
              osg::endEditCP((*arg1), TheMask);
          }
          //FieldContainerPtrs
          else if(isFieldAFieldContainerPtr(TheField))
          {
              osg::FieldContainerPtr *arg3 = (osg::FieldContainerPtr *) 0 ;
              if (!SWIG_IsOK(SWIG_ConvertPtr(L,3,(void**)&arg3,SWIGTYPE_p_osg__FieldContainerPtr,0)))
              {
                  LUA_BINDING_fail_ptr(L,"setFieldValue",3,SWIGTYPE_p_osg__FieldContainerPtr);
                  return SWIG_arg;
              }
              osg::beginEditCP((*arg1), TheMask);
                  static_cast<osg::MFFieldContainerPtr*>(TheField)->operator[](arg4) = (*arg3);
              osg::endEditCP((*arg1), TheMask);
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
          osg::FieldContainerPtr *arg1 = (osg::FieldContainerPtr *) 0 ;
          osg::Char8 *arg2 = (osg::Char8 *) 0 ;
          
          //Check if there are the correct number of arguments
          if (!LUA_BINDING_check_num_args(L,"pushFieldValue",3,3)){ return SWIG_arg;}
          //Check the type of argument 1
          if(!SWIG_isptrtype(L,1))
          {
              LUA_BINDING_fail_arg(L,"pushFieldValue",1,"FieldContainerPtr *");
              return SWIG_arg;
          }
          //Check the type of argument 2
          if(!lua_isstring(L,2))
          {
              LUA_BINDING_fail_arg(L,"pushFieldValue",2,"osg::Char8 const *'");
              return SWIG_arg;
          }
              
          //Check the pointer convertion on arg 1
          if (!SWIG_IsOK(SWIG_ConvertPtr(L,1,(void**)&arg1,SWIGTYPE_p_osg__FieldContainerPtr,0)))
          {
              LUA_BINDING_fail_ptr(L,"pushFieldValue",1,SWIGTYPE_p_osg__FieldContainerPtr);
              return SWIG_arg;
          }
          //Cast arg 2 to a string
          arg2 = (osg::Char8 *)lua_tostring(L, 2);
          
          //Check that arg1 is not NullFC
          if((*arg1) == osg::NullFC)
          {
              lua_pushfstring(L,"Error in pushFieldValue the FieldContainer given is Null");
              lua_error(L);
              return SWIG_arg;
          }
          //Check that the field referenced exists
          osg::Field* TheField((*arg1)->getField(arg2));
          if(TheField == NULL)
          {
              lua_pushfstring(L,"Error in pushFieldValue there is no field of name '%s' on type '%s'",arg2,(*arg1)->getTypeName());
              lua_error(L);
              return SWIG_arg;
          }
          if(TheField->getCardinality() == osg::FieldType::SINGLE_FIELD)
          {
              lua_pushfstring(L,"Error in pushFieldValue field of name '%s' on type '%s' is a single-field.  Use setFieldValue instead.",arg2,(*arg1)->getTypeName());
              lua_error(L);
              return SWIG_arg;
          }
          const osg::DataType& FieldContentType(TheField->getContentType());
          osg::BitVector TheMask((*arg1)->getType().findFieldDescription(arg2)->getFieldMask());
#if defined(WIN32)
          //bool
          //string
          if(FieldContentType == osg::FieldDataTraits<std::string>::getType() )
#else
          //bool
          if(FieldContentType == osg::FieldDataTraits2<bool>::getType() )
          {
              if(!lua_isboolean(L,3))
              {
                  LUA_BINDING_fail_arg(L,"pushFieldValue",3,"boolean'");
                  return SWIG_arg;
              }
              osg::beginEditCP((*arg1), TheMask);
                  dynamic_cast<osg::MFBool*>(TheField)->push_back(static_cast<bool>(lua_toboolean(L, 3)));
              osg::endEditCP((*arg1), TheMask);
          }
          //string
          else if(FieldContentType == osg::FieldDataTraits<std::string>::getType() )
#endif
          {
              if(!lua_isstring(L,3))
              {
                  LUA_BINDING_fail_arg(L,"pushFieldValue",3,"string'");
                  return SWIG_arg;
              }
              osg::beginEditCP((*arg1), TheMask);
                  dynamic_cast<osg::MFString*>(TheField)->push_back(static_cast<const osg::Char8*>(lua_tostring(L, 3)));
              osg::endEditCP((*arg1), TheMask);
          }
          //UInt8
          else if(FieldContentType == osg::FieldDataTraits<osg::UInt8>::getType() )
          {
              if(!lua_isnumber(L,3))
              {
                  LUA_BINDING_fail_arg(L,"pushFieldValue",3,"UInt8'");
                  return SWIG_arg;
              }
              osg::beginEditCP((*arg1), TheMask);
                  dynamic_cast<osg::MFUInt8*>(TheField)->push_back(static_cast<osg::UInt8>(lua_tonumber(L, 3)));
              osg::endEditCP((*arg1), TheMask);
          }
          //UInt16
          else if(FieldContentType == osg::FieldDataTraits<osg::UInt16>::getType() )
          {
              if(!lua_isnumber(L,3))
              {
                  LUA_BINDING_fail_arg(L,"pushFieldValue",3,"UInt16'");
                  return SWIG_arg;
              }
              osg::beginEditCP((*arg1), TheMask);
                  dynamic_cast<osg::MFUInt16*>(TheField)->push_back(static_cast<osg::UInt16>(lua_tonumber(L, 3)));
              osg::endEditCP((*arg1), TheMask);
          }
          //UInt32
          else if(TheField->getContentType() == osg::FieldDataTraits<osg::UInt32>::getType()) 
          {
              if(!lua_isnumber(L,3))
              {
                  LUA_BINDING_fail_arg(L,"pushFieldValue",3,"UInt32'");
                  return SWIG_arg;
              }
              osg::beginEditCP((*arg1), TheMask);
                  dynamic_cast<osg::MFUInt32*>(TheField)->push_back(static_cast<osg::UInt32>(lua_tonumber(L, 3)));
              osg::endEditCP((*arg1), TheMask);
          }
          //UInt64
          else if(FieldContentType == osg::FieldDataTraits<osg::UInt64>::getType() )
          {
              if(!lua_isnumber(L,3))
              {
                  LUA_BINDING_fail_arg(L,"pushFieldValue",3,"UInt64'");
                  return SWIG_arg;
              }
              osg::beginEditCP((*arg1), TheMask);
                  dynamic_cast<osg::MFUInt64*>(TheField)->push_back(static_cast<osg::UInt64>(lua_tonumber(L, 3)));
              osg::endEditCP((*arg1), TheMask);
          }
          //BitVector
          else if(FieldContentType == osg::FieldDataTraits1<osg::BitVector>::getType() )
          {
              if(!lua_isnumber(L,3))
              {
                  LUA_BINDING_fail_arg(L,"pushFieldValue",3,"BitVector'");
                  return SWIG_arg;
              }
              osg::beginEditCP((*arg1), TheMask);
                  dynamic_cast<osg::MFBitVector*>(TheField)->push_back(static_cast<osg::BitVector>(lua_tonumber(L, 3)));
              osg::endEditCP((*arg1), TheMask);
          }
          //GLenum
          else if(FieldContentType == osg::FieldDataTraits1<GLenum>::getType() )
          {
              if(!lua_isnumber(L,3))
              {
                  LUA_BINDING_fail_arg(L,"pushFieldValue",3,"GLenum'");
                  return SWIG_arg;
              }
              osg::beginEditCP((*arg1), TheMask);
                  dynamic_cast<osg::MFGLenum*>(TheField)->push_back(static_cast<GLenum>(lua_tonumber(L, 3)));
              osg::endEditCP((*arg1), TheMask);
          }
          //Int8
          else if(FieldContentType == osg::FieldDataTraits<osg::Int8>::getType() )
          {
              if(!lua_isnumber(L,3))
              {
                  LUA_BINDING_fail_arg(L,"pushFieldValue",3,"Int8'");
                  return SWIG_arg;
              }
              osg::beginEditCP((*arg1), TheMask);
                  dynamic_cast<osg::MFInt8*>(TheField)->push_back(static_cast<osg::Int8>(lua_tonumber(L, 3)));
              osg::endEditCP((*arg1), TheMask);
          }
          //Int16
          else if(FieldContentType == osg::FieldDataTraits<osg::Int16>::getType() )
          {
              if(!lua_isnumber(L,3))
              {
                  LUA_BINDING_fail_arg(L,"pushFieldValue",3,"Int16'");
                  return SWIG_arg;
              }
              osg::beginEditCP((*arg1), TheMask);
                  dynamic_cast<osg::MFInt16*>(TheField)->push_back(static_cast<osg::Int16>(lua_tonumber(L, 3)));
              osg::endEditCP((*arg1), TheMask);
          }
          //Int32
          else if(FieldContentType == osg::FieldDataTraits<osg::Int32>::getType() )
          {
              if(!lua_isnumber(L,3))
              {
                  LUA_BINDING_fail_arg(L,"pushFieldValue",3,"Int32'");
                  return SWIG_arg;
              }
              osg::beginEditCP((*arg1), TheMask);
                  dynamic_cast<osg::MFInt32*>(TheField)->push_back(static_cast<osg::Int32>(lua_tonumber(L, 3)));
              osg::endEditCP((*arg1), TheMask);
          }
          //Int64
          else if(FieldContentType == osg::FieldDataTraits<osg::Int64>::getType() )
          {
              if(!lua_isnumber(L,3))
              {
                  LUA_BINDING_fail_arg(L,"pushFieldValue",3,"Int64'");
                  return SWIG_arg;
              }
              osg::beginEditCP((*arg1), TheMask);
                  dynamic_cast<osg::MFInt64*>(TheField)->push_back(static_cast<osg::Int64>(lua_tonumber(L, 3)));
              osg::endEditCP((*arg1), TheMask);
          }
          //Real32
          else if(FieldContentType == osg::FieldDataTraits<osg::Real32>::getType() )
          {
              if(!lua_isnumber(L,3))
              {
                  LUA_BINDING_fail_arg(L,"pushFieldValue",3,"Real32'");
                  return SWIG_arg;
              }
              osg::beginEditCP((*arg1), TheMask);
                  dynamic_cast<osg::MFReal32*>(TheField)->push_back(static_cast<osg::Real32>(lua_tonumber(L, 3)));
              osg::endEditCP((*arg1), TheMask);
          }
          //Time
          else if(FieldContentType == osg::FieldDataTraits1<osg::Time>::getType() )
          {
              if(!lua_isnumber(L,3))
              {
                  LUA_BINDING_fail_arg(L,"pushFieldValue",3,"Time'");
                  return SWIG_arg;
              }
              osg::beginEditCP((*arg1), TheMask);
                  dynamic_cast<osg::MFTime*>(TheField)->push_back(static_cast<osg::Time>(lua_tonumber(L, 3)));
              osg::endEditCP((*arg1), TheMask);
          }
          //Real64
          else if(FieldContentType == osg::FieldDataTraits<osg::Real64>::getType() )
          {
              if(!lua_isnumber(L,3))
              {
                  LUA_BINDING_fail_arg(L,"pushFieldValue",3,"Real64'");
                  return SWIG_arg;
              }
              osg::beginEditCP((*arg1), TheMask);
                  dynamic_cast<osg::MFReal64*>(TheField)->push_back(static_cast<osg::Real64>(lua_tonumber(L, 3)));
              osg::endEditCP((*arg1), TheMask);
          }
          //Color3f
          else if(FieldContentType == osg::FieldDataTraits<osg::Color3f>::getType() )
          {
              osg::Color3f *arg3 = 0 ;
              if (!SWIG_IsOK(SWIG_ConvertPtr(L,3,(void**)&arg3,SWIGTYPE_p_osg__Color3T_float_t,0))){
                  LUA_BINDING_fail_ptr(L,"pushFieldValue",3,SWIGTYPE_p_osg__Color3T_float_t);
                  return SWIG_arg;
              }
              
              osg::beginEditCP((*arg1), TheMask);
                  dynamic_cast<osg::MFColor3f*>(TheField)->push_back(static_cast<osg::Color3f const &>(*arg3));
              osg::endEditCP((*arg1), TheMask);
          }
          //Color4f
          else if(FieldContentType == osg::FieldDataTraits<osg::Color4f>::getType() )
          {
              osg::Color4f *arg3 = 0 ;
              if (!SWIG_IsOK(SWIG_ConvertPtr(L,3,(void**)&arg3,SWIGTYPE_p_osg__Color4T_float_t,0))){
                  LUA_BINDING_fail_ptr(L,"pushFieldValue",3,SWIGTYPE_p_osg__Color4T_float_t);
                  return SWIG_arg;
              }
              
              osg::beginEditCP((*arg1), TheMask);
                  dynamic_cast<osg::MFColor4f*>(TheField)->push_back(static_cast<osg::Color4f const &>(*arg3));
              osg::endEditCP((*arg1), TheMask);
          }
          //Vec2f
          else if(FieldContentType == osg::FieldDataTraits<osg::Vec2f>::getType() )
          {
              osg::Vec2f *arg3 = 0 ;
              if (!SWIG_IsOK(SWIG_ConvertPtr(L,3,(void**)&arg3,SWIGTYPE_p_osg__Vec2f,0))){
                  LUA_BINDING_fail_ptr(L,"pushFieldValue",3,SWIGTYPE_p_osg__Vec2f);
                  return SWIG_arg;
              }
              
              osg::beginEditCP((*arg1), TheMask);
                  dynamic_cast<osg::MFVec2f*>(TheField)->push_back(static_cast<osg::Vec2f const &>(*arg3));
              osg::endEditCP((*arg1), TheMask);
          }
          //Vec3f
          else if(FieldContentType == osg::FieldDataTraits<osg::Vec3f>::getType() )
          {
              osg::Vec3f *arg3 = 0 ;
              if (!SWIG_IsOK(SWIG_ConvertPtr(L,3,(void**)&arg3,SWIGTYPE_p_osg__Vec3f,0))){
                  LUA_BINDING_fail_ptr(L,"pushFieldValue",3,SWIGTYPE_p_osg__Vec3f);
                  return SWIG_arg;
              }
              
              osg::beginEditCP((*arg1), TheMask);
                  dynamic_cast<osg::MFVec3f*>(TheField)->push_back(static_cast<osg::Vec3f const &>(*arg3));
              osg::endEditCP((*arg1), TheMask);
          }
          //Vec4f
          else if(FieldContentType == osg::FieldDataTraits<osg::Vec4f>::getType() )
          {
              osg::Vec4f *arg3 = 0 ;
              if (!SWIG_IsOK(SWIG_ConvertPtr(L,3,(void**)&arg3,SWIGTYPE_p_osg__Vec4f,0))){
                  LUA_BINDING_fail_ptr(L,"pushFieldValue",3,SWIGTYPE_p_osg__Vec4f);
                  return SWIG_arg;
              }
              
              osg::beginEditCP((*arg1), TheMask);
                  dynamic_cast<osg::MFVec4f*>(TheField)->push_back(static_cast<osg::Vec4f const &>(*arg3));
              osg::endEditCP((*arg1), TheMask);
          }
          //Pnt2f
          else if(FieldContentType == osg::FieldDataTraits<osg::Pnt2f>::getType() )
          {
              osg::Pnt2f *arg3 = 0 ;
              if (!SWIG_IsOK(SWIG_ConvertPtr(L,3,(void**)&arg3,SWIGTYPE_p_osg__Pnt2f,0))){
                  LUA_BINDING_fail_ptr(L,"pushFieldValue",3,SWIGTYPE_p_osg__Pnt2f);
                  return SWIG_arg;
              }
              
              osg::beginEditCP((*arg1), TheMask);
                  dynamic_cast<osg::MFPnt2f*>(TheField)->push_back(static_cast<osg::Pnt2f const &>(*arg3));
              osg::endEditCP((*arg1), TheMask);
          }
          //Pnt3f
          else if(FieldContentType == osg::FieldDataTraits<osg::Pnt3f>::getType() )
          {
              osg::Pnt3f *arg3 = 0 ;
              if (!SWIG_IsOK(SWIG_ConvertPtr(L,3,(void**)&arg3,SWIGTYPE_p_osg__Pnt3f,0))){
                  LUA_BINDING_fail_ptr(L,"pushFieldValue",3,SWIGTYPE_p_osg__Pnt3f);
                  return SWIG_arg;
              }
              
              osg::beginEditCP((*arg1), TheMask);
                  dynamic_cast<osg::MFPnt3f*>(TheField)->push_back(static_cast<osg::Pnt3f const &>(*arg3));
              osg::endEditCP((*arg1), TheMask);
          }
          //Pnt4f
          else if(FieldContentType == osg::FieldDataTraits<osg::Pnt4f>::getType() )
          {
              osg::Pnt4f *arg3 = 0 ;
              if (!SWIG_IsOK(SWIG_ConvertPtr(L,3,(void**)&arg3,SWIGTYPE_p_osg__Pnt4f,0))){
                  LUA_BINDING_fail_ptr(L,"pushFieldValue",3,SWIGTYPE_p_osg__Pnt4f);
                  return SWIG_arg;
              }
              
              osg::beginEditCP((*arg1), TheMask);
                  dynamic_cast<osg::MFPnt4f*>(TheField)->push_back(static_cast<osg::Pnt4f const &>(*arg3));
              osg::endEditCP((*arg1), TheMask);
          }
          //Matrix
          else if(FieldContentType == osg::FieldDataTraits<osg::Matrix>::getType() )
          {
              osg::Matrix *arg3 = 0 ;
              if (!SWIG_IsOK(SWIG_ConvertPtr(L,3,(void**)&arg3,SWIGTYPE_p_osg__Matrix,0))){
                  LUA_BINDING_fail_ptr(L,"pushFieldValue",3,SWIGTYPE_p_osg__Matrix);
                  return SWIG_arg;
              }
              
              osg::beginEditCP((*arg1), TheMask);
                  dynamic_cast<osg::MFMatrix*>(TheField)->push_back(static_cast<osg::Matrix const &>(*arg3));
              osg::endEditCP((*arg1), TheMask);
          }
          //Quaternion
          else if(FieldContentType == osg::FieldDataTraits<osg::Quaternion>::getType() )
          {
              osg::Quaternion *arg3 = 0 ;
              if (!SWIG_IsOK(SWIG_ConvertPtr(L,3,(void**)&arg3,SWIGTYPE_p_osg__Quaternion,0))){
                  LUA_BINDING_fail_ptr(L,"pushFieldValue",3,SWIGTYPE_p_osg__Quaternion);
                  return SWIG_arg;
              }
              
              osg::beginEditCP((*arg1), TheMask);
                  dynamic_cast<osg::MFQuaternion*>(TheField)->push_back(static_cast<osg::Quaternion const &>(*arg3));
              osg::endEditCP((*arg1), TheMask);
          }
          //FieldContainerPtrs
          else if(isFieldAFieldContainerPtr(TheField))
          {
              osg::FieldContainerPtr *arg3 = (osg::FieldContainerPtr *) 0 ;
              if (!SWIG_IsOK(SWIG_ConvertPtr(L,3,(void**)&arg3,SWIGTYPE_p_osg__FieldContainerPtr,0)))
              {
                  LUA_BINDING_fail_ptr(L,"pushFieldValue",3,SWIGTYPE_p_osg__FieldContainerPtr);
                  return SWIG_arg;
              }
              osg::beginEditCP((*arg1), TheMask);
                  static_cast<osg::MFFieldContainerPtr*>(TheField)->push_back(*arg3);
              osg::endEditCP((*arg1), TheMask);
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
              osg::beginEditCP((*arg1), TheMask);
                  TheField->pushValueByStr((osg::Char8 *)lua_tostring(L, 3));
              osg::endEditCP((*arg1), TheMask);
          }

          return SWIG_arg;
    }
    
    int insertFieldValue(lua_State*L) // my native code
    {
        int SWIG_arg = 0;
          osg::FieldContainerPtr *arg1 = (osg::FieldContainerPtr *) 0 ;
          osg::Char8 *arg2 = (osg::Char8 *) 0 ;
          osg::UInt32 arg4 ;
          
          //Check if there are the correct number of arguments
          if (!LUA_BINDING_check_num_args(L,"insertFieldValue",4,4)){ return SWIG_arg;}
          //Check the type of argument 1
          if(!SWIG_isptrtype(L,1))
          {
              LUA_BINDING_fail_arg(L,"insertFieldValue",1,"FieldContainerPtr *");
              return SWIG_arg;
          }
          //Check the type of argument 2
          if(!lua_isstring(L,2))
          {
              LUA_BINDING_fail_arg(L,"insertFieldValue",2,"osg::Char8 const *'");
              return SWIG_arg;
          }
          if(!lua_isnumber(L,4))
          {
              LUA_BINDING_fail_arg(L,"setFieldValue",4,"osg::UInt32'");
              return SWIG_arg;
          }
              
          //Check the pointer convertion on arg 1
          if (!SWIG_IsOK(SWIG_ConvertPtr(L,1,(void**)&arg1,SWIGTYPE_p_osg__FieldContainerPtr,0)))
          {
              LUA_BINDING_fail_ptr(L,"insertFieldValue",1,SWIGTYPE_p_osg__FieldContainerPtr);
              return SWIG_arg;
          }
          //Cast arg 2 to a string
          arg2 = (osg::Char8 *)lua_tostring(L, 2);
          arg4 = (osg::UInt32)lua_tonumber(L, 4);
          
          //Check that arg1 is not NullFC
          if((*arg1) == osg::NullFC)
          {
              lua_pushfstring(L,"Error in insertFieldValue the FieldContainer given is Null");
              lua_error(L);
              return SWIG_arg;
          }
          //Check that the field referenced exists
          osg::Field* TheField((*arg1)->getField(arg2));
          if(TheField == NULL)
          {
              lua_pushfstring(L,"Error in insertFieldValue there is no field of name '%s' on type '%s'",arg2,(*arg1)->getTypeName());
              lua_error(L);
              return SWIG_arg;
          }
          if(TheField->getCardinality() == osg::FieldType::SINGLE_FIELD)
          {
              lua_pushfstring(L,"Error in insertFieldValue field of name '%s' on type '%s' is a single-field.  Use setFieldValue instead.",arg2,(*arg1)->getTypeName());
              lua_error(L);
              return SWIG_arg;
          }
          //Make sure the index is in range
          if(arg4 > TheField->getSize())
          {
              lua_pushfstring(L,"Error in insertFieldValue: arg4 out of range.  Attempted to insert before index: %s, on a field %s of size %s.",arg4,arg2,TheField->getSize());
              lua_error(L);
              return SWIG_arg;
          }
          const osg::DataType& FieldContentType(TheField->getContentType());
          osg::BitVector TheMask((*arg1)->getType().findFieldDescription(arg2)->getFieldMask());
#if defined(WIN32)
          //bool
          //string
          if(FieldContentType == osg::FieldDataTraits<std::string>::getType() )
#else
          //bool
          if(FieldContentType == osg::FieldDataTraits2<bool>::getType() )
          {
              if(!lua_isboolean(L,3))
              {
                  LUA_BINDING_fail_arg(L,"insertFieldValue",3,"boolean'");
                  return SWIG_arg;
              }
              osg::MFBool::iterator InsertItor(dynamic_cast<osg::MFBool*>(TheField)->begin());
              InsertItor += arg4;
              osg::beginEditCP((*arg1), TheMask);
                  dynamic_cast<osg::MFBool*>(TheField)->insert(InsertItor, static_cast<bool>(lua_toboolean(L, 3)));
              osg::endEditCP((*arg1), TheMask);
          }
          //string
          else if(FieldContentType == osg::FieldDataTraits<std::string>::getType() )
#endif
          {
              if(!lua_isstring(L,3))
              {
                  LUA_BINDING_fail_arg(L,"insertFieldValue",3,"string'");
                  return SWIG_arg;
              }
              osg::MFString::iterator InsertItor(dynamic_cast<osg::MFString*>(TheField)->begin());
              InsertItor += arg4;
              osg::beginEditCP((*arg1), TheMask);
                  dynamic_cast<osg::MFString*>(TheField)->insert(InsertItor, static_cast<const osg::Char8*>(lua_tostring(L, 3)));
              osg::endEditCP((*arg1), TheMask);
          }
          //UInt8
          else if(FieldContentType == osg::FieldDataTraits<osg::UInt8>::getType() )
          {
              if(!lua_isnumber(L,3))
              {
                  LUA_BINDING_fail_arg(L,"insertFieldValue",3,"UInt8'");
                  return SWIG_arg;
              }
              osg::MFUInt8::iterator InsertItor(dynamic_cast<osg::MFUInt8*>(TheField)->begin());
              InsertItor += arg4;
              osg::beginEditCP((*arg1), TheMask);
                  dynamic_cast<osg::MFUInt8*>(TheField)->insert(InsertItor, static_cast<osg::UInt8>(lua_tonumber(L, 3)));
              osg::endEditCP((*arg1), TheMask);
          }
          //UInt16
          else if(FieldContentType == osg::FieldDataTraits<osg::UInt16>::getType() )
          {
              if(!lua_isnumber(L,3))
              {
                  LUA_BINDING_fail_arg(L,"insertFieldValue",3,"UInt16'");
                  return SWIG_arg;
              }
              osg::MFUInt16::iterator InsertItor(dynamic_cast<osg::MFUInt16*>(TheField)->begin());
              InsertItor += arg4;
              osg::beginEditCP((*arg1), TheMask);
                  dynamic_cast<osg::MFUInt16*>(TheField)->insert(InsertItor, static_cast<osg::UInt16>(lua_tonumber(L, 3)));
              osg::endEditCP((*arg1), TheMask);
          }
          //UInt32
          else if(TheField->getContentType() == osg::FieldDataTraits<osg::UInt32>::getType()) 
          {
              if(!lua_isnumber(L,3))
              {
                  LUA_BINDING_fail_arg(L,"insertFieldValue",3,"UInt32'");
                  return SWIG_arg;
              }
              osg::MFUInt32::iterator InsertItor(dynamic_cast<osg::MFUInt32*>(TheField)->begin());
              InsertItor += arg4;
              osg::beginEditCP((*arg1), TheMask);
                  dynamic_cast<osg::MFUInt32*>(TheField)->insert(InsertItor, static_cast<osg::UInt32>(lua_tonumber(L, 3)));
              osg::endEditCP((*arg1), TheMask);
          }
          //UInt64
          else if(FieldContentType == osg::FieldDataTraits<osg::UInt64>::getType() )
          {
              if(!lua_isnumber(L,3))
              {
                  LUA_BINDING_fail_arg(L,"insertFieldValue",3,"UInt64'");
                  return SWIG_arg;
              }
              osg::MFUInt64::iterator InsertItor(dynamic_cast<osg::MFUInt64*>(TheField)->begin());
              InsertItor += arg4;
              osg::beginEditCP((*arg1), TheMask);
                  dynamic_cast<osg::MFUInt64*>(TheField)->insert(InsertItor, static_cast<osg::UInt64>(lua_tonumber(L, 3)));
              osg::endEditCP((*arg1), TheMask);
          }
          //BitVector
          else if(FieldContentType == osg::FieldDataTraits1<osg::BitVector>::getType() )
          {
              if(!lua_isnumber(L,3))
              {
                  LUA_BINDING_fail_arg(L,"insertFieldValue",3,"BitVector'");
                  return SWIG_arg;
              }
              osg::MFBitVector::iterator InsertItor(dynamic_cast<osg::MFBitVector*>(TheField)->begin());
              InsertItor += arg4;
              osg::beginEditCP((*arg1), TheMask);
                  dynamic_cast<osg::MFBitVector*>(TheField)->insert(InsertItor, static_cast<osg::BitVector>(lua_tonumber(L, 3)));
              osg::endEditCP((*arg1), TheMask);
          }
          //GLenum
          else if(FieldContentType == osg::FieldDataTraits1<GLenum>::getType() )
          {
              if(!lua_isnumber(L,3))
              {
                  LUA_BINDING_fail_arg(L,"insertFieldValue",3,"GLenum'");
                  return SWIG_arg;
              }
              osg::MFGLenum::iterator InsertItor(dynamic_cast<osg::MFGLenum*>(TheField)->begin());
              InsertItor += arg4;
              osg::beginEditCP((*arg1), TheMask);
                  dynamic_cast<osg::MFGLenum*>(TheField)->insert(InsertItor, static_cast<GLenum>(lua_tonumber(L, 3)));
              osg::endEditCP((*arg1), TheMask);
          }
          //Int8
          else if(FieldContentType == osg::FieldDataTraits<osg::Int8>::getType() )
          {
              if(!lua_isnumber(L,3))
              {
                  LUA_BINDING_fail_arg(L,"insertFieldValue",3,"Int8'");
                  return SWIG_arg;
              }
              osg::MFInt8::iterator InsertItor(dynamic_cast<osg::MFInt8*>(TheField)->begin());
              InsertItor += arg4;
              osg::beginEditCP((*arg1), TheMask);
                  dynamic_cast<osg::MFInt8*>(TheField)->insert(InsertItor, static_cast<osg::Int8>(lua_tonumber(L, 3)));
              osg::endEditCP((*arg1), TheMask);
          }
          //Int16
          else if(FieldContentType == osg::FieldDataTraits<osg::Int16>::getType() )
          {
              if(!lua_isnumber(L,3))
              {
                  LUA_BINDING_fail_arg(L,"insertFieldValue",3,"Int16'");
                  return SWIG_arg;
              }
              osg::MFInt16::iterator InsertItor(dynamic_cast<osg::MFInt16*>(TheField)->begin());
              InsertItor += arg4;
              osg::beginEditCP((*arg1), TheMask);
                  dynamic_cast<osg::MFInt16*>(TheField)->insert(InsertItor, static_cast<osg::Int16>(lua_tonumber(L, 3)));
              osg::endEditCP((*arg1), TheMask);
          }
          //Int32
          else if(FieldContentType == osg::FieldDataTraits<osg::Int32>::getType() )
          {
              if(!lua_isnumber(L,3))
              {
                  LUA_BINDING_fail_arg(L,"insertFieldValue",3,"Int32'");
                  return SWIG_arg;
              }
              osg::MFInt32::iterator InsertItor(dynamic_cast<osg::MFInt32*>(TheField)->begin());
              InsertItor += arg4;
              osg::beginEditCP((*arg1), TheMask);
                  dynamic_cast<osg::MFInt32*>(TheField)->insert(InsertItor, static_cast<osg::Int32>(lua_tonumber(L, 3)));
              osg::endEditCP((*arg1), TheMask);
          }
          //Int64
          else if(FieldContentType == osg::FieldDataTraits<osg::Int64>::getType() )
          {
              if(!lua_isnumber(L,3))
              {
                  LUA_BINDING_fail_arg(L,"insertFieldValue",3,"Int64'");
                  return SWIG_arg;
              }
              osg::MFInt64::iterator InsertItor(dynamic_cast<osg::MFInt64*>(TheField)->begin());
              InsertItor += arg4;
              osg::beginEditCP((*arg1), TheMask);
                  dynamic_cast<osg::MFInt64*>(TheField)->insert(InsertItor, static_cast<osg::Int64>(lua_tonumber(L, 3)));
              osg::endEditCP((*arg1), TheMask);
          }
          //Real32
          else if(FieldContentType == osg::FieldDataTraits<osg::Real32>::getType() )
          {
              if(!lua_isnumber(L,3))
              {
                  LUA_BINDING_fail_arg(L,"insertFieldValue",3,"Real32'");
                  return SWIG_arg;
              }
              osg::MFReal32::iterator InsertItor(dynamic_cast<osg::MFReal32*>(TheField)->begin());
              InsertItor += arg4;
              osg::beginEditCP((*arg1), TheMask);
                  dynamic_cast<osg::MFReal32*>(TheField)->insert(InsertItor, static_cast<osg::Real32>(lua_tonumber(L, 3)));
              osg::endEditCP((*arg1), TheMask);
          }
          //Time
          else if(FieldContentType == osg::FieldDataTraits1<osg::Time>::getType() )
          {
              if(!lua_isnumber(L,3))
              {
                  LUA_BINDING_fail_arg(L,"insertFieldValue",3,"Time'");
                  return SWIG_arg;
              }
              osg::MFTime::iterator InsertItor(dynamic_cast<osg::MFTime*>(TheField)->begin());
              InsertItor += arg4;
              osg::beginEditCP((*arg1), TheMask);
                  dynamic_cast<osg::MFTime*>(TheField)->insert(InsertItor, static_cast<osg::Time>(lua_tonumber(L, 3)));
              osg::endEditCP((*arg1), TheMask);
          }
          //Real64
          else if(FieldContentType == osg::FieldDataTraits<osg::Real64>::getType() )
          {
              if(!lua_isnumber(L,3))
              {
                  LUA_BINDING_fail_arg(L,"insertFieldValue",3,"Real64'");
                  return SWIG_arg;
              }
              osg::MFReal64::iterator InsertItor(dynamic_cast<osg::MFReal64*>(TheField)->begin());
              InsertItor += arg4;
              osg::beginEditCP((*arg1), TheMask);
                  dynamic_cast<osg::MFReal64*>(TheField)->insert(InsertItor, static_cast<osg::Real64>(lua_tonumber(L, 3)));
              osg::endEditCP((*arg1), TheMask);
          }
          //Color3f
          else if(FieldContentType == osg::FieldDataTraits<osg::Color3f>::getType() )
          {
              osg::Color3f *arg3 = 0 ;
              if (!SWIG_IsOK(SWIG_ConvertPtr(L,3,(void**)&arg3,SWIGTYPE_p_osg__Color3T_float_t,0))){
                  LUA_BINDING_fail_ptr(L,"insertFieldValue",3,SWIGTYPE_p_osg__Color3T_float_t);
                  return SWIG_arg;
              }
              osg::MFColor3f::iterator InsertItor(dynamic_cast<osg::MFColor3f*>(TheField)->begin());
              InsertItor += arg4;
              osg::beginEditCP((*arg1), TheMask);
                  dynamic_cast<osg::MFColor3f*>(TheField)->insert(InsertItor, static_cast<osg::Color3f const &>(*arg3));
              osg::endEditCP((*arg1), TheMask);
          }
          //Color4f
          else if(FieldContentType == osg::FieldDataTraits<osg::Color4f>::getType() )
          {
              osg::Color4f *arg3 = 0 ;
              if (!SWIG_IsOK(SWIG_ConvertPtr(L,3,(void**)&arg3,SWIGTYPE_p_osg__Color4T_float_t,0))){
                  LUA_BINDING_fail_ptr(L,"insertFieldValue",3,SWIGTYPE_p_osg__Color4T_float_t);
                  return SWIG_arg;
              }
              osg::MFColor4f::iterator InsertItor(dynamic_cast<osg::MFColor4f*>(TheField)->begin());
              InsertItor += arg4;
              osg::beginEditCP((*arg1), TheMask);
                  dynamic_cast<osg::MFColor4f*>(TheField)->insert(InsertItor, static_cast<osg::Color4f const &>(*arg3));
              osg::endEditCP((*arg1), TheMask);
          }
          //Vec2f
          else if(FieldContentType == osg::FieldDataTraits<osg::Vec2f>::getType() )
          {
              osg::Vec2f *arg3 = 0 ;
              if (!SWIG_IsOK(SWIG_ConvertPtr(L,3,(void**)&arg3,SWIGTYPE_p_osg__Vec2f,0))){
                  LUA_BINDING_fail_ptr(L,"insertFieldValue",3,SWIGTYPE_p_osg__Vec2f);
                  return SWIG_arg;
              }
              osg::MFVec2f::iterator InsertItor(dynamic_cast<osg::MFVec2f*>(TheField)->begin());
              InsertItor += arg4;
              osg::beginEditCP((*arg1), TheMask);
                  dynamic_cast<osg::MFVec2f*>(TheField)->insert(InsertItor, static_cast<osg::Vec2f const &>(*arg3));
              osg::endEditCP((*arg1), TheMask);
          }
          //Vec3f
          else if(FieldContentType == osg::FieldDataTraits<osg::Vec3f>::getType() )
          {
              osg::Vec3f *arg3 = 0 ;
              if (!SWIG_IsOK(SWIG_ConvertPtr(L,3,(void**)&arg3,SWIGTYPE_p_osg__Vec3f,0))){
                  LUA_BINDING_fail_ptr(L,"insertFieldValue",3,SWIGTYPE_p_osg__Vec3f);
                  return SWIG_arg;
              }
              osg::MFVec3f::iterator InsertItor(dynamic_cast<osg::MFVec3f*>(TheField)->begin());
              InsertItor += arg4;
              osg::beginEditCP((*arg1), TheMask);
                  dynamic_cast<osg::MFVec3f*>(TheField)->insert(InsertItor, static_cast<osg::Vec3f const &>(*arg3));
              osg::endEditCP((*arg1), TheMask);
          }
          //Vec4f
          else if(FieldContentType == osg::FieldDataTraits<osg::Vec4f>::getType() )
          {
              osg::Vec4f *arg3 = 0 ;
              if (!SWIG_IsOK(SWIG_ConvertPtr(L,3,(void**)&arg3,SWIGTYPE_p_osg__Vec4f,0))){
                  LUA_BINDING_fail_ptr(L,"insertFieldValue",3,SWIGTYPE_p_osg__Vec4f);
                  return SWIG_arg;
              }
              osg::MFVec4f::iterator InsertItor(dynamic_cast<osg::MFVec4f*>(TheField)->begin());
              InsertItor += arg4;
              osg::beginEditCP((*arg1), TheMask);
                  dynamic_cast<osg::MFVec4f*>(TheField)->insert(InsertItor, static_cast<osg::Vec4f const &>(*arg3));
              osg::endEditCP((*arg1), TheMask);
          }
          //Pnt2f
          else if(FieldContentType == osg::FieldDataTraits<osg::Pnt2f>::getType() )
          {
              osg::Pnt2f *arg3 = 0 ;
              if (!SWIG_IsOK(SWIG_ConvertPtr(L,3,(void**)&arg3,SWIGTYPE_p_osg__Pnt2f,0))){
                  LUA_BINDING_fail_ptr(L,"insertFieldValue",3,SWIGTYPE_p_osg__Pnt2f);
                  return SWIG_arg;
              }
              osg::MFPnt2f::iterator InsertItor(dynamic_cast<osg::MFPnt2f*>(TheField)->begin());
              InsertItor += arg4;
              osg::beginEditCP((*arg1), TheMask);
                  dynamic_cast<osg::MFPnt2f*>(TheField)->insert(InsertItor, static_cast<osg::Pnt2f const &>(*arg3));
              osg::endEditCP((*arg1), TheMask);
          }
          //Pnt3f
          else if(FieldContentType == osg::FieldDataTraits<osg::Pnt3f>::getType() )
          {
              osg::Pnt3f *arg3 = 0 ;
              if (!SWIG_IsOK(SWIG_ConvertPtr(L,3,(void**)&arg3,SWIGTYPE_p_osg__Pnt3f,0))){
                  LUA_BINDING_fail_ptr(L,"insertFieldValue",3,SWIGTYPE_p_osg__Pnt3f);
                  return SWIG_arg;
              }
              osg::MFPnt3f::iterator InsertItor(dynamic_cast<osg::MFPnt3f*>(TheField)->begin());
              InsertItor += arg4;
              osg::beginEditCP((*arg1), TheMask);
                  dynamic_cast<osg::MFPnt3f*>(TheField)->insert(InsertItor, static_cast<osg::Pnt3f const &>(*arg3));
              osg::endEditCP((*arg1), TheMask);
          }
          //Pnt4f
          else if(FieldContentType == osg::FieldDataTraits<osg::Pnt4f>::getType() )
          {
              osg::Pnt4f *arg3 = 0 ;
              if (!SWIG_IsOK(SWIG_ConvertPtr(L,3,(void**)&arg3,SWIGTYPE_p_osg__Pnt4f,0))){
                  LUA_BINDING_fail_ptr(L,"insertFieldValue",3,SWIGTYPE_p_osg__Pnt4f);
                  return SWIG_arg;
              }
              osg::MFPnt4f::iterator InsertItor(dynamic_cast<osg::MFPnt4f*>(TheField)->begin());
              InsertItor += arg4;
              osg::beginEditCP((*arg1), TheMask);
                  dynamic_cast<osg::MFPnt4f*>(TheField)->insert(InsertItor, static_cast<osg::Pnt4f const &>(*arg3));
              osg::endEditCP((*arg1), TheMask);
          }
          //Matrix
          else if(FieldContentType == osg::FieldDataTraits<osg::Matrix>::getType() )
          {
              osg::Matrix *arg3 = 0 ;
              if (!SWIG_IsOK(SWIG_ConvertPtr(L,3,(void**)&arg3,SWIGTYPE_p_osg__Matrix,0))){
                  LUA_BINDING_fail_ptr(L,"insertFieldValue",3,SWIGTYPE_p_osg__Matrix);
                  return SWIG_arg;
              }
              osg::MFMatrix::iterator InsertItor(dynamic_cast<osg::MFMatrix*>(TheField)->begin());
              InsertItor += arg4;
              osg::beginEditCP((*arg1), TheMask);
                  dynamic_cast<osg::MFMatrix*>(TheField)->insert(InsertItor, static_cast<osg::Matrix const &>(*arg3));
              osg::endEditCP((*arg1), TheMask);
          }
          //Quaternion
          else if(FieldContentType == osg::FieldDataTraits<osg::Quaternion>::getType() )
          {
              osg::Quaternion *arg3 = 0 ;
              if (!SWIG_IsOK(SWIG_ConvertPtr(L,3,(void**)&arg3,SWIGTYPE_p_osg__Quaternion,0))){
                  LUA_BINDING_fail_ptr(L,"insertFieldValue",3,SWIGTYPE_p_osg__Quaternion);
                  return SWIG_arg;
              }
              osg::MFQuaternion::iterator InsertItor(dynamic_cast<osg::MFQuaternion*>(TheField)->begin());
              InsertItor += arg4;
              osg::beginEditCP((*arg1), TheMask);
                  dynamic_cast<osg::MFQuaternion*>(TheField)->insert(InsertItor, static_cast<osg::Quaternion const &>(*arg3));
              osg::endEditCP((*arg1), TheMask);
          }
          //FieldContainerPtrs
          else if(isFieldAFieldContainerPtr(TheField))
          {
              osg::FieldContainerPtr *arg3 = (osg::FieldContainerPtr *) 0 ;
              if (!SWIG_IsOK(SWIG_ConvertPtr(L,3,(void**)&arg3,SWIGTYPE_p_osg__FieldContainerPtr,0)))
              {
                  LUA_BINDING_fail_ptr(L,"insertFieldValue",3,SWIGTYPE_p_osg__FieldContainerPtr);
                  return SWIG_arg;
              }
              osg::MFFieldContainerPtr::iterator InsertItor(static_cast<osg::MFFieldContainerPtr*>(TheField)->begin());
              InsertItor += arg4;
              osg::beginEditCP((*arg1), TheMask);
                  static_cast<osg::MFFieldContainerPtr*>(TheField)->insert(InsertItor, *arg3);
              osg::endEditCP((*arg1), TheMask);
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

namespace osg {

    class FieldDescription;
    class FieldContainerPtr;
    class FieldContainerType;
    class FieldContainer;
    class AttachmentContainer;
    class Attachment;
    class AttachmentPtr;
    class AttachmentContainerPtr;
    class NodePtr;
    class NodeCorePtr;
    class Node;
    class Viewport;
    class ViewportPtr;
    class Camera;
    class CameraPtr;
    class Image;
    class ImagePtr;
    class Matrix;
    class DynamicVolume;
    class BoxVolume;
    /******************************************************/
    /*              FieldDescription                    */
    /******************************************************/
    class FieldDescription
    {
      public :


        FieldDescription(const FieldDescription &source                     );

        virtual ~FieldDescription(void); 

        const Char8     *getCName       (void                ) const;

              UInt32     getTypeId      (void                ) const;  

              BitVector  getFieldMask   (void                ) const;
              void       setFieldMask   (BitVector vFieldMask);

              UInt32     getFieldId     (void                ) const;
              void       setFieldId     (UInt32 uiFieldId    );

        const Char8     *getDefaultValue(void                ) const;

        const TypeBase  &getFieldType   (void                ) const;

              bool       isInternal     (void                ) const;

              bool       isValid        (void                ) const;

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
    /*              FieldContainerPtr                    */
    /******************************************************/
    class FieldContainerPtr
    {
      public:

        typedef FieldContainer        StoredObjectType;
        typedef FieldContainerPtr     ObjectType;

        typedef FieldContainerPtrBase Inherited;

        FieldContainer *operator->(void);

        FieldContainerPtr(      void                         );
        /*FieldContainerPtr(const NullFieldContainerPtr &      );*/
        FieldContainerPtr(const FieldContainerPtr     &source);

        ~FieldContainerPtr(void); 

    };
    %extend FieldContainerPtr
    {
        void setName(Char8* NewName) throw(const char *)
        {
            osg::AttachmentContainerPtr AsAttachmentContainer(osg::AttachmentContainerPtr::dcast(*$self));
            if(AsAttachmentContainer == osg::NullFC)
            {
                throw("Error in setName: must be called on an AttachmentContainer.");
            }
            osg::setName(AsAttachmentContainer, NewName);
        }
        const Char8* getName(void) throw(const char *)
        {
            osg::AttachmentContainerPtr AsAttachmentContainer(osg::AttachmentContainerPtr::dcast(*$self));
            if(AsAttachmentContainer == osg::NullFC)
            {
                throw("Error in setName: must be called on an AttachmentContainer.");
            }
            return osg::getName(AsAttachmentContainer);
        }
        
        bool operator==(const Int32& val) throw(const char *)
        {
            return (val == 0 && (*$self) == osg::NullFC);
        }
        
        FieldType::Cardinality getFieldCardinality(Char8* FieldName) throw(const char *)
        {
              //Check that the field referenced exists
              osg::Field* TheField((*$self)->getField(FieldName));
              if(TheField == NULL)
              {
                  std::string ErrorString = "Error in getFieldCardinality: there is no field of name '";
                  ErrorString += FieldName;
                  ErrorString += "' on type '";
                  ErrorString += (*$self)->getTypeName();
                  ErrorString += "'";
                  throw(ErrorString.c_str());
              }
              return TheField->getCardinality();
        }
        
        FieldContainerPtr deepClone(const std::string& shareString) throw(const char *)
        {
            return osg::deepClone((*$self), shareString);
        }
        
        UInt32 getFieldSize(Char8* FieldName) throw(const char *)
        {
              //Check that the field referenced exists
              osg::Field* TheField((*$self)->getField(FieldName));
              if(TheField == NULL)
              {
                  std::string ErrorString = "Error in getFieldSize: there is no field of name '";
                  ErrorString += FieldName;
                  ErrorString += "' on type '";
                  ErrorString += (*$self)->getTypeName();
                  ErrorString += "'";
                  throw(ErrorString.c_str());
              }
              //Make sure its a MultiField
              if(TheField->getCardinality() == osg::FieldType::SINGLE_FIELD)
              {
                  std::string ErrorString = "Error in getFieldSize: field of name '";
                  ErrorString += FieldName;
                  ErrorString += "' on type '";
                  ErrorString += (*$self)->getTypeName();
                  ErrorString += "' is a single-field,  clearField: cannot be used on it.";
                  throw(ErrorString.c_str());
              }
              return TheField->getSize();
        }
        
        void clearField(Char8* FieldName) throw(const char *)
        {
              //Check that the field referenced exists
              osg::Field* TheField((*$self)->getField(FieldName));
              if(TheField == NULL)
              {
                  std::string ErrorString = "Error in clear there is no field of name '";
                  ErrorString += FieldName;
                  ErrorString += "' on type '";
                  ErrorString += (*$self)->getTypeName();
                  ErrorString += "'";
                  throw(ErrorString.c_str());
              }
              //Make sure its a MultiField
              if(TheField->getCardinality() == osg::FieldType::SINGLE_FIELD)
              {
                  std::string ErrorString = "Error in clearField: field of name '";
                  ErrorString += FieldName;
                  ErrorString += "' on type '";
                  ErrorString += (*$self)->getTypeName();
                  ErrorString += "' is a single-field,  clearField: cannot be used on it.";
                  throw(ErrorString.c_str());
              }
              const osg::DataType& FieldContentType(TheField->getContentType());
              osg::BitVector TheMask((*$self)->getType().findFieldDescription(FieldName)->getFieldMask());
    //#if defined(WIN32)
              //bool
              //string
              if(FieldContentType == osg::FieldDataTraits<std::string>::getType() )
    /*#else
              //bool
              if(FieldContentType == osg::FieldDataTraits2<bool>::getType() )
              {
                  osg::beginEditCP((*$self), TheMask);
                      dynamic_cast<osg::MFBool*>(TheField)->clear();
                  osg::endEditCP((*$self), TheMask);
              }
              //string
              else if(FieldContentType == osg::FieldDataTraits<std::string>::getType() )
    #endif*/
              {
                  osg::beginEditCP((*$self), TheMask);
                      dynamic_cast<osg::MFString*>(TheField)->clear();
                  osg::endEditCP((*$self), TheMask);
              }
              //UInt8
              else if(FieldContentType == osg::FieldDataTraits<osg::UInt8>::getType() )
              {
                  osg::beginEditCP((*$self), TheMask);
                      dynamic_cast<osg::MFUInt8*>(TheField)->clear();
                  osg::endEditCP((*$self), TheMask);
              }
              //UInt16
              else if(FieldContentType == osg::FieldDataTraits<osg::UInt16>::getType() )
              {
                  osg::beginEditCP((*$self), TheMask);
                      dynamic_cast<osg::MFUInt16*>(TheField)->clear();
                  osg::endEditCP((*$self), TheMask);
              }
              //UInt32
              else if(TheField->getContentType() == osg::FieldDataTraits<osg::UInt32>::getType()) 
              {
                  osg::beginEditCP((*$self), TheMask);
                      dynamic_cast<osg::MFUInt32*>(TheField)->clear();
                  osg::endEditCP((*$self), TheMask);
              }
              //UInt64
              else if(FieldContentType == osg::FieldDataTraits<osg::UInt64>::getType() )
              {
                  osg::beginEditCP((*$self), TheMask);
                      dynamic_cast<osg::MFUInt64*>(TheField)->clear();
                  osg::endEditCP((*$self), TheMask);
              }
              //BitVector
              else if(FieldContentType == osg::FieldDataTraits1<osg::BitVector>::getType() )
              {
                  osg::beginEditCP((*$self), TheMask);
                      dynamic_cast<osg::MFBitVector*>(TheField)->clear();
                  osg::endEditCP((*$self), TheMask);
              }
              //GLenum
              else if(FieldContentType == osg::FieldDataTraits1<GLenum>::getType() )
              {
                  osg::beginEditCP((*$self), TheMask);
                      dynamic_cast<osg::MFGLenum*>(TheField)->clear();
                  osg::endEditCP((*$self), TheMask);
              }
              //Int8
              else if(FieldContentType == osg::FieldDataTraits<osg::Int8>::getType() )
              {
                  osg::beginEditCP((*$self), TheMask);
                      dynamic_cast<osg::MFInt8*>(TheField)->clear();
                  osg::endEditCP((*$self), TheMask);
              }
              //Int16
              else if(FieldContentType == osg::FieldDataTraits<osg::Int16>::getType() )
              {
                  osg::beginEditCP((*$self), TheMask);
                      dynamic_cast<osg::MFInt16*>(TheField)->clear();
                  osg::endEditCP((*$self), TheMask);
              }
              //Int32
              else if(FieldContentType == osg::FieldDataTraits<osg::Int32>::getType() )
              {
                  osg::beginEditCP((*$self), TheMask);
                      dynamic_cast<osg::MFInt32*>(TheField)->clear();
                  osg::endEditCP((*$self), TheMask);
              }
              //Int64
              else if(FieldContentType == osg::FieldDataTraits<osg::Int64>::getType() )
              {
                  osg::beginEditCP((*$self), TheMask);
                      dynamic_cast<osg::MFInt64*>(TheField)->clear();
                  osg::endEditCP((*$self), TheMask);
              }
              //Real32
              else if(FieldContentType == osg::FieldDataTraits<osg::Real32>::getType() )
              {
                  osg::beginEditCP((*$self), TheMask);
                      dynamic_cast<osg::MFReal32*>(TheField)->clear();
                  osg::endEditCP((*$self), TheMask);
              }
              //Time
              else if(FieldContentType == osg::FieldDataTraits1<osg::Time>::getType() )
              {
                  osg::beginEditCP((*$self), TheMask);
                      dynamic_cast<osg::MFTime*>(TheField)->clear();
                  osg::endEditCP((*$self), TheMask);
              }
              //Real64
              else if(FieldContentType == osg::FieldDataTraits<osg::Real64>::getType() )
              {
                  osg::beginEditCP((*$self), TheMask);
                      dynamic_cast<osg::MFReal64*>(TheField)->clear();
                  osg::endEditCP((*$self), TheMask);
              }
              //Color3f
              else if(FieldContentType == osg::FieldDataTraits<osg::Color3f>::getType() )
              {
                  osg::beginEditCP((*$self), TheMask);
                      dynamic_cast<osg::MFColor3f*>(TheField)->clear();
                  osg::endEditCP((*$self), TheMask);
              }
              //Color4f
              else if(FieldContentType == osg::FieldDataTraits<osg::Color4f>::getType() )
              {
                  osg::beginEditCP((*$self), TheMask);
                      dynamic_cast<osg::MFColor4f*>(TheField)->clear();
                  osg::endEditCP((*$self), TheMask);
              }
              //Vec2f
              else if(FieldContentType == osg::FieldDataTraits<osg::Vec2f>::getType() )
              {
                  osg::beginEditCP((*$self), TheMask);
                      dynamic_cast<osg::MFVec2f*>(TheField)->clear();
                  osg::endEditCP((*$self), TheMask);
              }
              //Vec3f
              else if(FieldContentType == osg::FieldDataTraits<osg::Vec3f>::getType() )
              {
                  osg::beginEditCP((*$self), TheMask);
                      dynamic_cast<osg::MFVec3f*>(TheField)->clear();
                  osg::endEditCP((*$self), TheMask);
              }
              //Vec4f
              else if(FieldContentType == osg::FieldDataTraits<osg::Vec4f>::getType() )
              {
                  osg::beginEditCP((*$self), TheMask);
                      dynamic_cast<osg::MFVec4f*>(TheField)->clear();
                  osg::endEditCP((*$self), TheMask);
              }
              //Pnt2f
              else if(FieldContentType == osg::FieldDataTraits<osg::Pnt2f>::getType() )
              {
                  osg::beginEditCP((*$self), TheMask);
                      dynamic_cast<osg::MFPnt2f*>(TheField)->clear();
                  osg::endEditCP((*$self), TheMask);
              }
              //Pnt3f
              else if(FieldContentType == osg::FieldDataTraits<osg::Pnt3f>::getType() )
              {
                  osg::beginEditCP((*$self), TheMask);
                      dynamic_cast<osg::MFPnt3f*>(TheField)->clear();
                  osg::endEditCP((*$self), TheMask);
              }
              //Pnt4f
              else if(FieldContentType == osg::FieldDataTraits<osg::Pnt4f>::getType() )
              {
                  osg::beginEditCP((*$self), TheMask);
                      dynamic_cast<osg::MFPnt4f*>(TheField)->clear();
                  osg::endEditCP((*$self), TheMask);
              }
              //Matrix
              else if(FieldContentType == osg::FieldDataTraits<osg::Matrix>::getType() )
              {
                  osg::beginEditCP((*$self), TheMask);
                      dynamic_cast<osg::MFMatrix*>(TheField)->clear();
                  osg::endEditCP((*$self), TheMask);
              }
              //Quaternion
              else if(FieldContentType == osg::FieldDataTraits<osg::Quaternion>::getType() )
              {
                  osg::beginEditCP((*$self), TheMask);
                      dynamic_cast<osg::MFQuaternion*>(TheField)->clear();
                  osg::endEditCP((*$self), TheMask);
              }
              //FieldContainerPtrs
              else if(isFieldAFieldContainerPtr(TheField))
              {
                  osg::beginEditCP((*$self), TheMask);
                      static_cast<osg::MFFieldContainerPtr*>(TheField)->clear();
                  osg::endEditCP((*$self), TheMask);
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
              //Check that the field referenced exists
              osg::Field* TheField((*$self)->getField(FieldName));
              if(TheField == NULL)
              {
                  std::string ErrorString = "Error in removeFieldValue: there is no field of name '";
                  ErrorString += FieldName;
                  ErrorString += "' on type '";
                  ErrorString += (*$self)->getTypeName();
                  ErrorString += "'";
                  throw(ErrorString.c_str());
              }
              if(TheField->getCardinality() == osg::FieldType::SINGLE_FIELD)
              {
                  std::string ErrorString = "Error in removeFieldValue: field of name '";
                  ErrorString += FieldName;
                  ErrorString += "' on type '";
                  ErrorString += (*$self)->getTypeName();
                  ErrorString += "' is a single-field,  removeFieldValue cannot be used on it.";
                  throw(ErrorString.c_str());
              }
              //Make sure the index is in range
              if(Index >= TheField->getSize())
              {
                  std::string ErrorString = "Error in removeFieldValue: Index out of range.  Attempted to remove index: .";
                  //ErrorString += ;
                  //ErrorString += ", where the size is ";
                  //ErrorString += ;
                  throw("Error in removeFieldValue: Index out of range.  Attempted to remove index: .");
              }
              const osg::DataType& FieldContentType(TheField->getContentType());
              osg::BitVector TheMask((*$self)->getType().findFieldDescription(FieldName)->getFieldMask());
    //#if defined(WIN32)
              //bool
              //string
              if(FieldContentType == osg::FieldDataTraits<std::string>::getType() )
    /*#else
              //bool
              if(FieldContentType == osg::FieldDataTraits2<bool>::getType() )
              {
                  osg::beginEditCP((*$self), TheMask);
                      dynamic_cast<osg::MFBool*>(TheField)->clear();
                  osg::endEditCP((*$self), TheMask);
              }
              //string
              else if(FieldContentType == osg::FieldDataTraits<std::string>::getType() )
    #endif*/
              {
                  osg::MFString::iterator EraseItor(dynamic_cast<osg::MFString*>(TheField)->begin());
                  EraseItor += Index;
                  osg::beginEditCP((*$self), TheMask);
                      dynamic_cast<osg::MFString*>(TheField)->erase(EraseItor);
                  osg::endEditCP((*$self), TheMask);
              }
              //UInt8
              else if(FieldContentType == osg::FieldDataTraits<osg::UInt8>::getType() )
              {
                  osg::MFUInt8::iterator EraseItor(dynamic_cast<osg::MFUInt8*>(TheField)->begin());
                  EraseItor += Index;
                  osg::beginEditCP((*$self), TheMask);
                      dynamic_cast<osg::MFUInt8*>(TheField)->erase(EraseItor);
                  osg::endEditCP((*$self), TheMask);
              }
              //UInt16
              else if(FieldContentType == osg::FieldDataTraits<osg::UInt16>::getType() )
              {
                  osg::MFUInt16::iterator EraseItor(dynamic_cast<osg::MFUInt16*>(TheField)->begin());
                  EraseItor += Index;
                  osg::beginEditCP((*$self), TheMask);
                      dynamic_cast<osg::MFUInt16*>(TheField)->erase(EraseItor);
                  osg::endEditCP((*$self), TheMask);
              }
              //UInt32
              else if(TheField->getContentType() == osg::FieldDataTraits<osg::UInt32>::getType()) 
              {
                  osg::MFUInt32::iterator EraseItor(dynamic_cast<osg::MFUInt32*>(TheField)->begin());
                  EraseItor += Index;
                  osg::beginEditCP((*$self), TheMask);
                      dynamic_cast<osg::MFUInt32*>(TheField)->erase(EraseItor);
                  osg::endEditCP((*$self), TheMask);
              }
              //UInt64
              else if(FieldContentType == osg::FieldDataTraits<osg::UInt64>::getType() )
              {
                  osg::MFUInt64::iterator EraseItor(dynamic_cast<osg::MFUInt64*>(TheField)->begin());
                  EraseItor += Index;
                  osg::beginEditCP((*$self), TheMask);
                      dynamic_cast<osg::MFUInt64*>(TheField)->erase(EraseItor);
                  osg::endEditCP((*$self), TheMask);
              }
              //BitVector
              else if(FieldContentType == osg::FieldDataTraits1<osg::BitVector>::getType() )
              {
                  osg::MFBitVector::iterator EraseItor(dynamic_cast<osg::MFBitVector*>(TheField)->begin());
                  EraseItor += Index;
                  osg::beginEditCP((*$self), TheMask);
                      dynamic_cast<osg::MFBitVector*>(TheField)->erase(EraseItor);
                  osg::endEditCP((*$self), TheMask);
              }
              //GLenum
              else if(FieldContentType == osg::FieldDataTraits1<GLenum>::getType() )
              {
                  osg::MFGLenum::iterator EraseItor(dynamic_cast<osg::MFGLenum*>(TheField)->begin());
                  EraseItor += Index;
                  osg::beginEditCP((*$self), TheMask);
                      dynamic_cast<osg::MFGLenum*>(TheField)->erase(EraseItor);
                  osg::endEditCP((*$self), TheMask);
              }
              //Int8
              else if(FieldContentType == osg::FieldDataTraits<osg::Int8>::getType() )
              {
                  osg::MFInt8::iterator EraseItor(dynamic_cast<osg::MFInt8*>(TheField)->begin());
                  EraseItor += Index;
                  osg::beginEditCP((*$self), TheMask);
                      dynamic_cast<osg::MFInt8*>(TheField)->erase(EraseItor);
                  osg::endEditCP((*$self), TheMask);
              }
              //Int16
              else if(FieldContentType == osg::FieldDataTraits<osg::Int16>::getType() )
              {
                  osg::MFInt16::iterator EraseItor(dynamic_cast<osg::MFInt16*>(TheField)->begin());
                  EraseItor += Index;
                  osg::beginEditCP((*$self), TheMask);
                      dynamic_cast<osg::MFInt16*>(TheField)->erase(EraseItor);
                  osg::endEditCP((*$self), TheMask);
              }
              //Int32
              else if(FieldContentType == osg::FieldDataTraits<osg::Int32>::getType() )
              {
                  osg::MFInt32::iterator EraseItor(dynamic_cast<osg::MFInt32*>(TheField)->begin());
                  EraseItor += Index;
                  osg::beginEditCP((*$self), TheMask);
                      dynamic_cast<osg::MFInt32*>(TheField)->erase(EraseItor);
                  osg::endEditCP((*$self), TheMask);
              }
              //Int64
              else if(FieldContentType == osg::FieldDataTraits<osg::Int64>::getType() )
              {
                  osg::MFInt64::iterator EraseItor(dynamic_cast<osg::MFInt64*>(TheField)->begin());
                  EraseItor += Index;
                  osg::beginEditCP((*$self), TheMask);
                      dynamic_cast<osg::MFInt64*>(TheField)->erase(EraseItor);
                  osg::endEditCP((*$self), TheMask);
              }
              //Real32
              else if(FieldContentType == osg::FieldDataTraits<osg::Real32>::getType() )
              {
                  osg::MFReal32::iterator EraseItor(dynamic_cast<osg::MFReal32*>(TheField)->begin());
                  EraseItor += Index;
                  osg::beginEditCP((*$self), TheMask);
                      dynamic_cast<osg::MFReal32*>(TheField)->erase(EraseItor);
                  osg::endEditCP((*$self), TheMask);
              }
              //Time
              else if(FieldContentType == osg::FieldDataTraits1<osg::Time>::getType() )
              {
                  osg::MFTime::iterator EraseItor(dynamic_cast<osg::MFTime*>(TheField)->begin());
                  EraseItor += Index;
                  osg::beginEditCP((*$self), TheMask);
                      dynamic_cast<osg::MFTime*>(TheField)->erase(EraseItor);
                  osg::endEditCP((*$self), TheMask);
              }
              //Real64
              else if(FieldContentType == osg::FieldDataTraits<osg::Real64>::getType() )
              {
                  osg::MFReal64::iterator EraseItor(dynamic_cast<osg::MFReal64*>(TheField)->begin());
                  EraseItor += Index;
                  osg::beginEditCP((*$self), TheMask);
                      dynamic_cast<osg::MFReal64*>(TheField)->erase(EraseItor);
                  osg::endEditCP((*$self), TheMask);
              }
              //Color3f
              else if(FieldContentType == osg::FieldDataTraits<osg::Color3f>::getType() )
              {
                  osg::MFColor3f::iterator EraseItor(dynamic_cast<osg::MFColor3f*>(TheField)->begin());
                  EraseItor += Index;
                  osg::beginEditCP((*$self), TheMask);
                      dynamic_cast<osg::MFColor3f*>(TheField)->erase(EraseItor);
                  osg::endEditCP((*$self), TheMask);
              }
              //Color4f
              else if(FieldContentType == osg::FieldDataTraits<osg::Color4f>::getType() )
              {
                  osg::MFColor4f::iterator EraseItor(dynamic_cast<osg::MFColor4f*>(TheField)->begin());
                  EraseItor += Index;
                  osg::beginEditCP((*$self), TheMask);
                      dynamic_cast<osg::MFColor4f*>(TheField)->erase(EraseItor);
                  osg::endEditCP((*$self), TheMask);
              }
              //Vec2f
              else if(FieldContentType == osg::FieldDataTraits<osg::Vec2f>::getType() )
              {
                  osg::MFVec2f::iterator EraseItor(dynamic_cast<osg::MFVec2f*>(TheField)->begin());
                  EraseItor += Index;
                  osg::beginEditCP((*$self), TheMask);
                      dynamic_cast<osg::MFVec2f*>(TheField)->erase(EraseItor);
                  osg::endEditCP((*$self), TheMask);
              }
              //Vec3f
              else if(FieldContentType == osg::FieldDataTraits<osg::Vec3f>::getType() )
              {
                  osg::MFVec3f::iterator EraseItor(dynamic_cast<osg::MFVec3f*>(TheField)->begin());
                  EraseItor += Index;
                  osg::beginEditCP((*$self), TheMask);
                      dynamic_cast<osg::MFVec3f*>(TheField)->erase(EraseItor);
                  osg::endEditCP((*$self), TheMask);
              }
              //Vec4f
              else if(FieldContentType == osg::FieldDataTraits<osg::Vec4f>::getType() )
              {
                  osg::MFVec4f::iterator EraseItor(dynamic_cast<osg::MFVec4f*>(TheField)->begin());
                  EraseItor += Index;
                  osg::beginEditCP((*$self), TheMask);
                      dynamic_cast<osg::MFVec4f*>(TheField)->erase(EraseItor);
                  osg::endEditCP((*$self), TheMask);
              }
              //Pnt2f
              else if(FieldContentType == osg::FieldDataTraits<osg::Pnt2f>::getType() )
              {
                  osg::MFPnt2f::iterator EraseItor(dynamic_cast<osg::MFPnt2f*>(TheField)->begin());
                  EraseItor += Index;
                  osg::beginEditCP((*$self), TheMask);
                      dynamic_cast<osg::MFPnt2f*>(TheField)->erase(EraseItor);
                  osg::endEditCP((*$self), TheMask);
              }
              //Pnt3f
              else if(FieldContentType == osg::FieldDataTraits<osg::Pnt3f>::getType() )
              {
                  osg::MFPnt3f::iterator EraseItor(dynamic_cast<osg::MFPnt3f*>(TheField)->begin());
                  EraseItor += Index;
                  osg::beginEditCP((*$self), TheMask);
                      dynamic_cast<osg::MFPnt3f*>(TheField)->erase(EraseItor);
                  osg::endEditCP((*$self), TheMask);
              }
              //Pnt4f
              else if(FieldContentType == osg::FieldDataTraits<osg::Pnt4f>::getType() )
              {
                  osg::MFPnt4f::iterator EraseItor(dynamic_cast<osg::MFPnt4f*>(TheField)->begin());
                  EraseItor += Index;
                  osg::beginEditCP((*$self), TheMask);
                      dynamic_cast<osg::MFPnt4f*>(TheField)->erase(EraseItor);
                  osg::endEditCP((*$self), TheMask);
              }
              //Matrix
              else if(FieldContentType == osg::FieldDataTraits<osg::Matrix>::getType() )
              {
                  osg::MFMatrix::iterator EraseItor(dynamic_cast<osg::MFMatrix*>(TheField)->begin());
                  EraseItor += Index;
                  osg::beginEditCP((*$self), TheMask);
                      dynamic_cast<osg::MFMatrix*>(TheField)->erase(EraseItor);
                  osg::endEditCP((*$self), TheMask);
              }
              //Quaternion
              else if(FieldContentType == osg::FieldDataTraits<osg::Quaternion>::getType() )
              {
                  osg::MFQuaternion::iterator EraseItor(dynamic_cast<osg::MFQuaternion*>(TheField)->begin());
                  EraseItor += Index;
                  osg::beginEditCP((*$self), TheMask);
                      dynamic_cast<osg::MFQuaternion*>(TheField)->erase(EraseItor);
                  osg::endEditCP((*$self), TheMask);
              }
              //FieldContainerPtrs
              else if(isFieldAFieldContainerPtr(TheField))
              {
                  osg::MFFieldContainerPtr::iterator EraseItor(static_cast<osg::MFFieldContainerPtr*>(TheField)->begin());
                  EraseItor += Index;
                  osg::beginEditCP((*$self), TheMask);
                      static_cast<osg::MFFieldContainerPtr*>(TheField)->erase(EraseItor);
                  osg::endEditCP((*$self), TheMask);
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

        EventConnection attachActivity(FieldContainerPtr TheActivity, const Char8 *ProducedEventName)
        {
            if(!osg::isEventProducer(*$self))
            {
                  std::string ErrorString = "Cannot call attachActivity on FieldContainer of type '";
                  ErrorString += (*$self)->getTypeName();
                  ErrorString += "', because it is not an EventProducer.'";
                  throw(ErrorString.c_str());
            }

            if(!TheActivity->getType().isDerivedFrom(osg::Activity::getClassType()))
            {
                  std::string ErrorString = "Cannot call attachActivity with Argument 1 of type '";
                  ErrorString += TheActivity->getTypeName();
                  ErrorString += "', because it is not derived from Activity.'";
                  throw(ErrorString.c_str());
            }

            osg::EventProducerPtr ProdField = osg::getEventProducer(*$self);
            
            return ProdField->attachActivity(osg::ActivityPtr::dcast(TheActivity),ProducedEventName);
        }

        bool isActivityAttached(FieldContainerPtr TheActivity, const Char8 *ProducedEventName) const
        {
            if(!osg::isEventProducer(*$self))
            {
                  std::string ErrorString = "Cannot call isActivityAttached on FieldContainer of type '";
                  ErrorString += (*$self)->getTypeName();
                  ErrorString += "', because it is not an EventProducer.'";
                  throw(ErrorString.c_str());
            }

            if(!TheActivity->getType().isDerivedFrom(osg::Activity::getClassType()))
            {
                  std::string ErrorString = "Cannot call isActivityAttached with Argument 1 of type '";
                  ErrorString += TheActivity->getTypeName();
                  ErrorString += "', because it is not derived from Activity.'";
                  throw(ErrorString.c_str());
            }

            osg::EventProducerPtr ProdField = osg::getEventProducer(*$self);
            
            return ProdField->isActivityAttached(osg::ActivityPtr::dcast(TheActivity),ProducedEventName);
        }

        UInt32 getNumActivitiesAttached(const Char8 *ProducedEventName) const
        {
            if(!osg::isEventProducer(*$self))
            {
                  std::string ErrorString = "Cannot call getNumActivitiesAttached on FieldContainer of type '";
                  ErrorString += (*$self)->getTypeName();
                  ErrorString += "', because it is not an EventProducer.'";
                  throw(ErrorString.c_str());
            }

            osg::EventProducerPtr ProdField = osg::getEventProducer(*$self);
            
            return ProdField->getNumActivitiesAttached(ProducedEventName);
        }

        FieldContainerPtr getAttachedActivity(const Char8 *ProducedEventName, UInt32 ActivityIndex) const
        {
            if(!osg::isEventProducer(*$self))
            {
                  std::string ErrorString = "Cannot call getAttachedActivity on FieldContainer of type '";
                  ErrorString += (*$self)->getTypeName();
                  ErrorString += "', because it is not an EventProducer.'";
                  throw(ErrorString.c_str());
            }

            osg::EventProducerPtr ProdField = osg::getEventProducer(*$self);
            
            return ProdField->getAttachedActivity(ProducedEventName, ActivityIndex);
        }

        void detachActivity(FieldContainerPtr TheActivity, const Char8 *ProducedEventName)
        {
            if(!osg::isEventProducer(*$self))
            {
                  std::string ErrorString = "Cannot call detachActivity on FieldContainer of type '";
                  ErrorString += (*$self)->getTypeName();
                  ErrorString += "', because it is not an EventProducer.'";
                  throw(ErrorString.c_str());
            }

            if(!TheActivity->getType().isDerivedFrom(osg::Activity::getClassType()))
            {
                  std::string ErrorString = "Cannot call detachActivity with Argument 1 of type '";
                  ErrorString += TheActivity->getTypeName();
                  ErrorString += "', because it is not derived from Activity.'";
                  throw(ErrorString.c_str());
            }

            osg::EventProducerPtr ProdField = osg::getEventProducer(*$self);
            
            return ProdField->detachActivity(osg::ActivityPtr::dcast(TheActivity),ProducedEventName);
        }

        EventConnection attachActivity(FieldContainerPtr TheActivity, UInt32 ProducedEventId)
        {
            if(!osg::isEventProducer(*$self))
            {
                  std::string ErrorString = "Cannot call attachActivity on FieldContainer of type '";
                  ErrorString += (*$self)->getTypeName();
                  ErrorString += "', because it is not an EventProducer.'";
                  throw(ErrorString.c_str());
            }

            if(!TheActivity->getType().isDerivedFrom(osg::Activity::getClassType()))
            {
                  std::string ErrorString = "Cannot call attachActivity with Argument 1 of type '";
                  ErrorString += TheActivity->getTypeName();
                  ErrorString += "', because it is not derived from Activity.'";
                  throw(ErrorString.c_str());
            }

            osg::EventProducerPtr ProdField = osg::getEventProducer(*$self);
            
            return ProdField->attachActivity(osg::ActivityPtr::dcast(TheActivity),ProducedEventId);
        }

        bool isActivityAttached(FieldContainerPtr TheActivity, UInt32 ProducedEventId) const
        {
            if(!osg::isEventProducer(*$self))
            {
                  std::string ErrorString = "Cannot call isActivityAttached on FieldContainer of type '";
                  ErrorString += (*$self)->getTypeName();
                  ErrorString += "', because it is not an EventProducer.'";
                  throw(ErrorString.c_str());
            }

            if(!TheActivity->getType().isDerivedFrom(osg::Activity::getClassType()))
            {
                  std::string ErrorString = "Cannot call isActivityAttached with Argument 1 of type '";
                  ErrorString += TheActivity->getTypeName();
                  ErrorString += "', because it is not derived from Activity.'";
                  throw(ErrorString.c_str());
            }

            osg::EventProducerPtr ProdField = osg::getEventProducer(*$self);
            
            return ProdField->isActivityAttached(osg::ActivityPtr::dcast(TheActivity),ProducedEventId);
        }

        UInt32 getNumActivitiesAttached(UInt32 ProducedEventId) const
        {
            if(!osg::isEventProducer(*$self))
            {
                  std::string ErrorString = "Cannot call getNumActivitiesAttached on FieldContainer of type '";
                  ErrorString += (*$self)->getTypeName();
                  ErrorString += "', because it is not an EventProducer.'";
                  throw(ErrorString.c_str());
            }

            osg::EventProducerPtr ProdField = osg::getEventProducer(*$self);
            
            return ProdField->getNumActivitiesAttached(ProducedEventId);
        }

        FieldContainerPtr getAttachedActivity(UInt32 ProducedEventId, UInt32 ActivityIndex) const
        {
            if(!osg::isEventProducer(*$self))
            {
                  std::string ErrorString = "Cannot call getAttachedActivity on FieldContainer of type '";
                  ErrorString += (*$self)->getTypeName();
                  ErrorString += "', because it is not an EventProducer.'";
                  throw(ErrorString.c_str());
            }

            osg::EventProducerPtr ProdField = osg::getEventProducer(*$self);
            
            return ProdField->getAttachedActivity(ProducedEventId, ActivityIndex);
        }
        
        void detachActivity(FieldContainerPtr TheActivity, UInt32 ProducedEventId)
        {
            if(!osg::isEventProducer(*$self))
            {
                  std::string ErrorString = "Cannot call detachActivity on FieldContainer of type '";
                  ErrorString += (*$self)->getTypeName();
                  ErrorString += "', because it is not an EventProducer.'";
                  throw(ErrorString.c_str());
            }

            if(!TheActivity->getType().isDerivedFrom(osg::Activity::getClassType()))
            {
                  std::string ErrorString = "Cannot call detachActivity with Argument 1 of type '";
                  ErrorString += TheActivity->getTypeName();
                  ErrorString += "', because it is not derived from Activity.'";
                  throw(ErrorString.c_str());
            }

            osg::EventProducerPtr ProdField = osg::getEventProducer(*$self);
            
            return ProdField->detachActivity(osg::ActivityPtr::dcast(TheActivity),ProducedEventId);
        }

        void detachAllActivities(void)
        {
            if(!osg::isEventProducer(*$self))
            {
                  std::string ErrorString = "Cannot call detachAllActivities on FieldContainer of type '";
                  ErrorString += (*$self)->getTypeName();
                  ErrorString += "', because it is not an EventProducer.'";
                  throw(ErrorString.c_str());
            }

            osg::EventProducerPtr ProdField = osg::getEventProducer(*$self);
            
            return ProdField->detachAllActivities();
        }

        UInt32 getNumAttachedActivities(void) const
        {
            if(!osg::isEventProducer(*$self))
            {
                  std::string ErrorString = "Cannot call getNumAttachedActivities on FieldContainer of type '";
                  ErrorString += (*$self)->getTypeName();
                  ErrorString += "', because it is not an EventProducer.'";
                  throw(ErrorString.c_str());
            }

            osg::EventProducerPtr ProdField = osg::getEventProducer(*$self);
            
            return ProdField->getNumAttachedActivities();
        }

        const EventProducerType &getProducerType(void) const
        {
            if(!osg::isEventProducer(*$self))
            {
                  std::string ErrorString = "Cannot call getProducerType on FieldContainer of type '";
                  ErrorString += (*$self)->getTypeName();
                  ErrorString += "', because it is not an EventProducer.'";
                  throw(ErrorString.c_str());
            }
            
            return osg::getEventProducer(*$self)->getProducerType();
        }

        UInt32 getNumProducedEvents(void) const
        {
            if(!osg::isEventProducer(*$self))
            {
                  std::string ErrorString = "Cannot call getNumProducedEvents on FieldContainer of type '";
                  ErrorString += (*$self)->getTypeName();
                  ErrorString += "', because it is not an EventProducer.'";
                  throw(ErrorString.c_str());
            }

            osg::EventProducerPtr ProdField = osg::getEventProducer(*$self);
            
            return ProdField->getNumProducedEvents();
        }

        const MethodDescription *getProducedEventDescription(const Char8 *ProducedEventName) const
        {
            if(!osg::isEventProducer(*$self))
            {
                  std::string ErrorString = "Cannot call getProducedEventDescription on FieldContainer of type '";
                  ErrorString += (*$self)->getTypeName();
                  ErrorString += "', because it is not an EventProducer.'";
                  throw(ErrorString.c_str());
            }

            osg::EventProducerPtr ProdField = osg::getEventProducer(*$self);
            
            return ProdField->getProducedEventDescription(ProducedEventName);
        }

        const MethodDescription *getProducedEventDescription(UInt32 ProducedEventId) const
        {
            if(!osg::isEventProducer(*$self))
            {
                  std::string ErrorString = "Cannot call getProducedEventDescription on FieldContainer of type '";
                  ErrorString += (*$self)->getTypeName();
                  ErrorString += "', because it is not an EventProducer.'";
                  throw(ErrorString.c_str());
            }

            osg::EventProducerPtr ProdField = osg::getEventProducer(*$self);
            
            return ProdField->getProducedEventDescription(ProducedEventId);
        }

        UInt32 getProducedEventId(const Char8 *ProducedEventName) const
        {
            if(!osg::isEventProducer(*$self))
            {
                  std::string ErrorString = "Cannot call getProducedEventId on FieldContainer of type '";
                  ErrorString += (*$self)->getTypeName();
                  ErrorString += "', because it is not an EventProducer.'";
                  throw(ErrorString.c_str());
            }

            osg::EventProducerPtr ProdField = osg::getEventProducer(*$self);
            
            return ProdField->getProducedEventId(ProducedEventName);
        }

        
     };
    /******************************************************/
    /*              FieldContainerType                    */
    /******************************************************/
    class FieldContainerType : public DataType
    {
      public :

        FieldContainerType(const FieldContainerType &source);

        virtual ~FieldContainerType(void); 

        UInt16              getGroupId(void) const;
        FieldContainerType *getParent (void) const;

              FieldDescription *getFieldDescription (UInt32 uiFieldId);

              FieldDescription *findFieldDescription(const Char8 *szFieldName);

        const FieldDescription *findFieldDescription(
            const Char8 *szFieldName) const; 

        UInt32                 getNumFieldDescs(void) const;

        UInt32                 addDescription  (const FieldDescription &desc     );
        bool                   subDescription  (      UInt32            uiFieldId);

        FieldContainerPtr getPrototype(void                        ) const;
        bool              setPrototype(FieldContainerPtr pPrototype);

        bool isInitialized(void                           ) const;

        bool isAbstract   (void                           ) const;

        bool isDerivedFrom(const TypeBase           &other) const;
        bool isDerivedFrom(const FieldContainerType &other) const;    

        bool isNode       (void                           ) const;
        bool isNodeCore   (void                           ) const;
        bool isAttachment (void                           ) const;

        FieldContainerPtr createFieldContainer(void) const;
        NodePtr           createNode          (void) const;
        NodeCorePtr       createNodeCore      (void) const;
        AttachmentPtr     createAttachment    (void) const;

        virtual void dump(      UInt32    uiIndent = 0, 
                          const BitVector bvFlags  = 0) const;
    };

    /******************************************************/
    /*              FieldContainer                        */
    /******************************************************/
    class FieldContainer 
    {
      public:
        virtual       FieldContainerType &getType    (void);

                      UInt16              getGroupId (void) const;


                Field  *getField        (      UInt32 fieldId  );

                Field  *getField        (const Char8 *fieldName);

        virtual FieldContainerPtr shallowCopy(void) const = 0;

      protected:
        FieldContainer(void);

        FieldContainer(const FieldContainer &obj);

        virtual ~FieldContainer (void);

    };

    /******************************************************/
    /*              FieldContainerFactory                 */
    /******************************************************/
    class FieldContainerFactory
    {
      public :

        static FieldContainerFactory *the(void);
            
        FieldContainerType *findType    (      UInt32  uiTypeId) const;
        FieldContainerType *findType    (const Char8  *szName  ) const;
        UInt32              getNumTypes (void                  ) const;

              UInt16  findGroupId  (const Char8  *szName   ) const;
        const Char8  *findGroupName(      UInt16  uiGroupId) const;
            
              UInt16  getNumGroups (      void             ) const;


        FieldContainerPtr getContainer      (UInt32 uiFieldContainerId) const;

        FieldContainerPtr createFieldContainer(const Char8 *name) const;
        NodePtr           createNode          (const Char8 *name) const;
        NodeCorePtr       createNodeCore      (const Char8 *name) const;
        AttachmentPtr     createAttachment    (const Char8 *name) const;

      protected:
        FieldContainerFactory(void);

        virtual ~FieldContainerFactory(void); 
    };
    /******************************************************/
    /*                    AttachmentContainerPtr          */
    /******************************************************/
    class AttachmentContainerPtr : 
        public FieldContainerPtr
    {
      public:

        AttachmentContainerPtr(      void                          );
        AttachmentContainerPtr(const AttachmentContainerPtr &source);
        /*AttachmentContainerPtr(const NullFieldContainerPtr  &source);*/
        ~AttachmentContainerPtr(void);

        AttachmentContainer *operator->(void);
        
         static AttachmentContainerPtr dcast(const FieldContainerPtr oIn);

      protected:
    };

    /******************************************************/
    /*                    AttachmentContainer             */
    /******************************************************/
    class AttachmentContainer : public FieldContainer 
    {
      public:
        void          addAttachment (const AttachmentPtr &fieldContainerP, 
                                           UInt16         binding        = 0);

        void          subAttachment (const AttachmentPtr &fieldContainerP,
                                           UInt16         binding        = 0);

        AttachmentPtr findAttachment(      UInt32         groupId,
                                           UInt16         binding        = 0);

        AttachmentPtr findAttachment(const FieldContainerType &type,
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
    /*                    NodeCorePtr          */
    /******************************************************/
    class NodeCorePtr : 
        public AttachmentContainerPtr
    {
      public:

        NodeCorePtr(      void                          );
        NodeCorePtr(const NodeCorePtr &source);
        /*NodeCorePtr(const NullFieldContainerPtr  &source);*/
        ~NodeCorePtr(void);
        
         static NodeCorePtr dcast(const FieldContainerPtr oIn);

        NodeCore *operator->(void);
      protected:
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
    /*                    GeometryPtr          */
    /******************************************************/
    class GeometryPtr : 
        public NodeCorePtr
    {
      public:

        GeometryPtr(      void                          );
        GeometryPtr(const GeometryPtr &source);
        /*GeometryPtr(const NullFieldContainerPtr  &source);*/
        ~GeometryPtr(void);
        
         static GeometryPtr dcast(const FieldContainerPtr oIn);

        Geometry *operator->(void);
      protected:
    };
    
    /******************************************************/
    /*              NodePtr                               */
    /******************************************************/
    class NodePtr : public AttachmentContainerPtr
    {
      public:
         NodePtr(void);
         NodePtr(const NodePtr               &source);
         /*NodePtr(const NullFieldContainerPtr &source);*/


        ~NodePtr(void); 
        Node *operator->(void);
        
        static NodePtr dcast(const FieldContainerPtr oIn);
    };

    /******************************************************/
    /*              Node                                  */
    /******************************************************/
    class Node : public AttachmentContainer 
    {
      public:
        
        UInt32  getNChildren  (void                     ) const;
        
        void    addChild      (const NodePtr &childP    );

        void    insertChild   (      UInt32   childIndex, 
                               const NodePtr &childP    );

        void    replaceChild  (      UInt32   childIndex,    
                               const NodePtr &childP    );

        Int32   findChild     (const NodePtr &childP    ) const;

        void    subChild      (const NodePtr &childP    );
        void    subChild      (      UInt32   childIndex);

        NodePtr getChild      (      UInt32   childIndex);
        
        bool   getActive  (void      ) const;

        void   setActive  (bool   val);

        void   setTravMask(UInt32 val);
        UInt32 getTravMask(void      ) const;

        void   setOcclusionMask(UInt8 val);
        UInt8  getOcclusionMask(void      ) const;

        NodePtr clone(void);
        
        Matrix getToWorld(void          );
        
        void   getToWorld(Matrix &result);
               DynamicVolume &getVolume       (bool update          );
               /*BoxVolume     &editVolume      (bool update          );*/
        /*const  BoxVolume     &getVolume       (void                 ) const;*/
               /*void           getWorldVolume  (BoxVolume     &result);*/
        
               void           updateVolume    (void                 );

               void           invalidateVolume(void                 );
      protected:
        Node(void);
        Node(const Node &source);
        virtual ~Node (void);
    };
    
    /******************************************************/
    /*              ViewportPtr                             */
    /******************************************************/
    class ViewportPtr : public AttachmentContainerPtr
    {
      public:
         ViewportPtr(void);
         ViewportPtr(const ViewportPtr               &source);
         /*ViewportPtr(const NullFieldContainerPtr &source);*/


        ~ViewportPtr(void); 
        Viewport *operator->(void);
        
        static ViewportPtr dcast(const FieldContainerPtr oIn);
    };

    /******************************************************/
    /*                     Viewport                       */
    /******************************************************/ 
    class Viewport : public AttachmentContainer
    {
      public:
        
        Int32 getPixelLeft  (void) const;
        Int32 getPixelRight (void) const;
        Int32 getPixelBottom(void) const;
        Int32 getPixelTop   (void) const;
        Int32 getPixelWidth (void) const;
        Int32 getPixelHeight(void) const;
        
        bool isFullWindow( void ) const;
      protected:
        Viewport(void);
        Viewport(const Image &source);

        virtual ~Viewport(void);
    };
    
    
    /******************************************************/
    /*              CameraPtr                             */
    /******************************************************/
    class CameraPtr : public AttachmentContainerPtr
    {
      public:
         CameraPtr(void);
         CameraPtr(const CameraPtr               &source);
         /*CameraPtr(const NullFieldContainerPtr &source);*/


        ~CameraPtr(void); 
        Camera *operator->(void);
        
        static CameraPtr dcast(const FieldContainerPtr oIn);
    };
    
    /******************************************************/
    /*                       Camera                       */
    /******************************************************/ 
    class Camera : public AttachmentContainer
    {
     public:
        virtual void getProjection           (Matrix        &result, 
                                              UInt32 width, UInt32 height);

        virtual void getProjectionTranslation(Matrix        &result, 
                                              UInt32 width, UInt32 height);

        virtual void getViewing              (Matrix        &result, 
                                              UInt32 width, UInt32 height);

        /*virtual void getFrustum              (FrustumVolume &result,*/
                                              /*const Viewport& port);*/

        /*virtual void getFrustum              (FrustumVolume &result,*/
                                              /*UInt32 width, UInt32 height);*/

        virtual void getWorldToScreen        (Matrix        &result, 
                                              const Viewport& port);
      
        virtual void getDecoration           (Matrix        &result, 
                                              UInt32 width, UInt32 height);

        //bool calcViewRay( Line &line, Int32 x, Int32 y, const Viewport& port, 
        //       Real32 *t = NULL );

     protected:
        Camera(void);
        Camera(const Camera &source);

        virtual ~Camera(void); 
    };
    %extend Camera
    {
        bool calcViewRay( Line &line, Int32 x, Int32 y, const ViewportPtr port, 
               Real32 *t = NULL )
        {
            return ($self)->calcViewRay(line, x, y, (*port), t);
        }
    };
    
    /******************************************************/
    /*              ImagePtr                             */
    /******************************************************/
    class ImagePtr : public AttachmentContainerPtr
    {
      public:
         ImagePtr(void);
         ImagePtr(const ImagePtr               &source);
         /*ImagePtr(const NullFieldContainerPtr &source);*/


        ~ImagePtr(void); 
        Image *operator->(void);
        
        static ImagePtr dcast(const FieldContainerPtr oIn);
    };
    
    /******************************************************/
    /*                       Image                       */
    /******************************************************/ 
    class Image : public AttachmentContainer
    {
      public:

        enum PixelFormat {   OSG_INVALID_PF = 0,

                             OSG_A_PF       = GL_ALPHA,
                             OSG_I_PF       = GL_INTENSITY,

                             OSG_L_PF       = GL_LUMINANCE,
                             OSG_LA_PF      = GL_LUMINANCE_ALPHA,

                             OSG_BGR_PF     = GL_BGR,

                             OSG_BGRA_PF    = GL_BGRA,
                             OSG_RGB_DXT1   = GL_COMPRESSED_RGB_S3TC_DXT1_EXT,
                             OSG_RGBA_DXT1  = GL_COMPRESSED_RGBA_S3TC_DXT1_EXT,
                             OSG_RGBA_DXT3  = GL_COMPRESSED_RGBA_S3TC_DXT3_EXT,
                             OSG_RGBA_DXT5  = GL_COMPRESSED_RGBA_S3TC_DXT5_EXT,
                             OSG_RGB_PF     = GL_RGB,
                             OSG_RGBA_PF    = GL_RGBA,
                             
                             OSG_ALPHA_INTEGER_PF = GL_ALPHA_INTEGER_EXT,
                             OSG_RGB_INTEGER_PF = GL_RGB_INTEGER_EXT,
                             OSG_RGBA_INTEGER_PF = GL_RGBA_INTEGER_EXT,
                             OSG_BGR_INTEGER_PF = GL_BGR_INTEGER_EXT,
                             OSG_BGRA_INTEGER_PF = GL_BGRA_INTEGER_EXT,
                             OSG_LUMINANCE_INTEGER_PF = GL_LUMINANCE_INTEGER_EXT,
                             OSG_LUMINANCE_ALPHA_INTEGER_PF = GL_LUMINANCE_ALPHA_INTEGER_EXT
        };

        enum Type {
                             OSG_INVALID_IMAGEDATATYPE  = GL_NONE,
                             OSG_UINT8_IMAGEDATA        = GL_UNSIGNED_BYTE,
                             OSG_UINT16_IMAGEDATA       = GL_UNSIGNED_SHORT,
                             OSG_UINT32_IMAGEDATA       = GL_UNSIGNED_INT,
                             OSG_FLOAT16_IMAGEDATA      = GL_HALF_FLOAT_NV,
                             OSG_FLOAT32_IMAGEDATA      = GL_FLOAT,
                             OSG_INT16_IMAGEDATA         = GL_SHORT,
                             OSG_INT32_IMAGEDATA         = GL_INT
        };

        enum ResUnit {
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

        bool set                (      ImagePtr   image            );
        bool setData            (const UInt8     *data = 0         );
        void clearData          (void                              );
        bool setSubData ( Int32 offX, Int32 offY, Int32 offZ,
                          Int32 srcW, Int32 srcH, Int32 srcD,
                          const UInt8 *data );
        bool flipDepthFrameData (void                              );

        void imageContentChanged(Int32 minX = -1, Int32 maxX = -1,
                                 Int32 minY = -1, Int32 maxY = -1,
                                 Int32 minZ = -1, Int32 maxZ = -1 );
        
        bool addValue (const char *value);

        /*bool reformat ( const PixelFormat pixelFormat,*/
                        /*ImagePtr destination = NullFC);*/

        /*void swapDataEndian(void);*/
        /*bool convertDataTypeTo ( Int32 destDataType = OSG_UINT8_IMAGEDATA );*/

        bool scale          ( Int32 width, Int32 height = 1,
                              Int32 depth = 1,
                              ImagePtr destination = NullFC );
        /*bool scaleNextPower2( ImagePtr destination = NullFC );*/

        bool subImage ( Int32 offX, Int32 offY, Int32 offZ,
                        Int32 destW, Int32 destH, Int32 destD,
                        ImagePtr destination = NullFC);

        bool slice ( Int32 offX = -1, Int32 offY = -1, Int32 offZ = -1,
                     ImagePtr destination = NullFC);

        /*bool createMipmap ( Int32 level = -1, ImagePtr destination = NullFC);*/

        /*bool removeMipmap (void);*/

        bool write (const Char8 *fileName);
        bool read  (const Char8 *fileName);

        /*UInt64 store   (const Char8 *mimeType, UInt8* mem, Int32 memSize = -1);*/
        /*UInt64 restore (const UInt8* mem, Int32 memSize = -1);*/


               bool   isValid           (void) const;
               bool   hasAlphaChannel   (void);
               bool   isAlphaBinary     (void);
               bool   hasColorChannel   (void);
               bool   hasCompressedData (void);
               UInt8  getComponents     (void) const;
               
               bool   calcIsAlphaBinary (void);

        inline unsigned long getSize ( bool withMipmap = true,
                                       bool withFrames = true,
                                       bool withSides  = true ) const;

        inline const UInt8 *getData ( UInt32 mipmapNum = 0,
                                      UInt32 frameNum = 0,
                                      UInt32 sideNum = 0 ) const;
        inline       UInt8 *editData( UInt32 mipmapNum = 0,
                                      UInt32 frameNum = 0,
                                      UInt32 sideNum = 0 );
        inline const UInt8 *getDataFast ( UInt32 mipmapNum = 0,
                                          UInt32 frameNum = 0,
                                          UInt32 sideNum = 0 ) const;
        inline       UInt8 *editDataFast( UInt32 mipmapNum = 0,
                                          UInt32 frameNum = 0,
                                          UInt32 sideNum=0);

        /*void   calcMipmapGeometry   ( UInt32 mipmapNum,*/
                                      /*UInt32 &width,*/
                                      /*UInt32 &height,*/
                                      /*UInt32 &depth       ) const;*/

        /*UInt32 calcMipmapLevelCount ( void                       ) const;*/
        /*UInt32 calcFrameNum         ( Time time, bool loop = true) const;*/

        virtual void clear (UChar8 pixelValue = 0);
        virtual void clearFloat (Real32 pixelValue = 0.0);
        //virtual void clearHalf (Real16 pixelValue = Real16( 0.0 ));

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
    /*              Geom Creation Functions               */
    /******************************************************/ 
    FieldContainerPtr               makePlaneGeo          (Real32 xsize, 
                                                     Real32 ysize,
                                                     UInt16 hor,   
                                                     UInt16 vert);
     
    FieldContainerPtr                   makePlane             (Real32 xsize, 
                                                     Real32 ysize,
                                                     UInt16 hor,   
                                                     UInt16 vert);
     
    FieldContainerPtr               makeBoxGeo            (Real32 xsize,
                                                     Real32 ysize,
                                                     Real32 zsize,
                                                     UInt16 hor,
                                                     UInt16 vert,
                                                     UInt16 depth);
     
    FieldContainerPtr                   makeBox               (Real32 xsize,
                                                     Real32 ysize,
                                                     Real32 zsize,
                                                     UInt16 hor,
                                                     UInt16 vert,
                                                     UInt16 depth);
     
    FieldContainerPtr               makeConeGeo           (Real32 height,
                                                     Real32 botradius,
                                                     UInt16 sides,
                                                     bool   doSide,
                                                     bool   doBottom);
     
    FieldContainerPtr                   makeCone              (Real32 height,
                                                     Real32 botradius,
                                                     UInt16 sides,
                                                     bool   doSide,
                                                     bool   doBottom);
     
    FieldContainerPtr               makeCylinderGeo       (Real32 height,
                                                     Real32 radius,
                                                     UInt16 sides,
                                                     bool   doSide,
                                                     bool   doTop,
                                                     bool   doBottom);
     
    FieldContainerPtr                   makeCylinder          (Real32 height,
                                                     Real32 radius,
                                                     UInt16 sides,
                                                     bool   doSide,
                                                     bool   doTop,
                                                     bool   doBottom);
     
    FieldContainerPtr               makeTorusGeo          (Real32 innerRadius,
                                                     Real32 outerRadius,
                                                     UInt16 sides, 
                                                     UInt16 rings );
    
     
    FieldContainerPtr                   makeTorus             (Real32 innerRadius,
                                                     Real32 outerRadius,
                                                     UInt16 sides, 
                                                     UInt16 rings);
     
    FieldContainerPtr               makeSphereGeo         (UInt16 depth,
                                                     Real32 radius);
     
    FieldContainerPtr                   makeSphere            (UInt16 depth, 
                                                     Real32 radius);
     
    FieldContainerPtr               makeLatLongSphereGeo  (UInt16 latres,
                                                     UInt16 longres,
                                                     Real32 radius);
     
    FieldContainerPtr                   makeLatLongSphere     (UInt16 latres, 
                                                     UInt16 longres,
                                                     Real32 radius);
     
    FieldContainerPtr               makeConicalFrustumGeo (Real32 height,
                                                     Real32 topradius,
                                                     Real32 botradius,
                                                     UInt16 sides,
                                                     bool   doSide,
                                                     bool   doTop,
                                                     bool   doBottom);
     
    FieldContainerPtr                   makeConicalFrustum    (Real32 height,
                                                     Real32 topradius,
                                                     Real32 botradius,
                                                     UInt16 sides,
                                                     bool   doSide,
                                                     bool   doTop,
                                                     bool   doBottom); 
     
    void                    calcVertexNormals   (GeometryPtr geo);
    
     
    void                    calcVertexNormals   (GeometryPtr geo,
                                                 Real32 creaseAngle);
     
    void                    calcFaceNormals     (GeometryPtr geo);
    
     
    void                    calcVertexTangents  (GeometryPtr geo,
                                                 Int32 srcTexIndex,
                                                 Int32 dstAttribTan,
                                                 Int32 dstAttribBin);
    
    
    void                    calcVertexTexCoords (GeometryPtr geo,
                                                 Int32 texIndex);
    
     
    Int32              createOptimizedPrimitives(GeometryPtr geo,
                                                 UInt32 iteration,
                                                 bool createStrips,
                                                 bool createFans,
                                                 UInt32 minFanEdgeCount,
                                                 bool colorCode,
                                                 bool stitchStrips);
    
     
    void                  createConvexPrimitives(GeometryPtr geo);
    
     
    Int32                      createSharedIndex(GeometryPtr geo);
    
     
    Int32                      createSingleIndex(GeometryPtr geo);
    
     
    UInt32                    calcPrimitiveCount(GeometryPtr geo,
                                                 UInt32 &triangle,
                                                 UInt32 &line,
                                                 UInt32 &point);
    
     
    NodePtr                 calcVertexNormalsGeo(GeometryPtr geo, 
                                                 Real32 length);
    
     
    NodePtr                   calcFaceNormalsGeo(GeometryPtr geo, 
                                                 Real32 length);
     
    void                         mergeGeometries(std::vector<NodePtr> &nodes,
                                                 std::vector<NodePtr> &results);
    
    
    void                        separateProperties(GeometryPtr geo);


}

