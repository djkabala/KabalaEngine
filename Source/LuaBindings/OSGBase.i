%include <lua/std_string.i>
%module OSG
%native(version) int OSGVersion(lua_State*L);  // registers native_function() with SWIG
%native(LOG) int OSGLogLOG(lua_State*L);  // registers native_function() with SWIG
%native(FATAL) int OSGLogFATAL(lua_State*L);  // registers native_function() with SWIG
%native(WARNING) int OSGLogWARNING(lua_State*L);  // registers native_function() with SWIG
%native(NOTICE) int OSGLogNOTICE(lua_State*L);  // registers native_function() with SWIG
%native(INFO) int OSGLogINFO(lua_State*L);  // registers native_function() with SWIG
%{
#include "OSGConfig.h"
#include "OSGBaseFunctions.h"
#include "OSGColor.h"
#include "OSGVector.h"
#include "OSGMatrix.h"
#include "OSGMatrixUtility.h"
#include "OSGQuaternion.h"
#include "OSGLine.h"
#include "OSGPlane.h"
#include "OSGTypeBase.h"
#include "OSGDataType.h"
#include "OSGTypeFactory.h"
#include "OSGFieldType.h"
#include "OSGField.h"
/*#include "OSGFieldFactory.h"*/
#include "OSGTime.h"
#include "OSGVolume.h"
#include "OSGBoxVolume.h"
#include "OSGReal16.h"
#include "OSGLog.h"

    int OSGVersion(lua_State*L) // my native code
    {
      int SWIG_arg = 0;
      std::string result(OSG_VERSION_STRING);
      SWIG_check_num_args("version",0,0);
      
      lua_pushstring(L,result.c_str()); SWIG_arg++;
      return SWIG_arg;
      
      if(0) SWIG_fail;
      
    fail:
      lua_error(L);
      return SWIG_arg;
    }
    
    int OSGLogLOG(lua_State*L)
    {
      int SWIG_arg = 0;
      OSG::Char8 *arg1 = (OSG::Char8 *) 0 ;
      
      SWIG_check_num_args("LOG",1,1)
      if(!lua_isstring(L,1)) SWIG_fail_arg("LOG",1,"string");
      
      arg1 = (OSG::Char8 *)lua_tostring(L, 1);
      
      SLOG << arg1 << std::endl;
      return SWIG_arg;
      
    fail:
      lua_error(L);
      return SWIG_arg;
    }
    
    int OSGLogFATAL(lua_State*L)
    {
      int SWIG_arg = 0;
      OSG::Char8 *arg1 = (OSG::Char8 *) 0 ;
      
      SWIG_check_num_args("FATAL",1,1)
      if(!lua_isstring(L,1)) SWIG_fail_arg("FATAL",1,"string");
      
      arg1 = (OSG::Char8 *)lua_tostring(L, 1);
      
      SFATAL << arg1 << std::endl;
      return SWIG_arg;
      
    fail:
      lua_error(L);
      return SWIG_arg;
    }
    
    int OSGLogWARNING(lua_State*L)
    {
      int SWIG_arg = 0;
      OSG::Char8 *arg1 = (OSG::Char8 *) 0 ;
      
      SWIG_check_num_args("WARNING",1,1)
      if(!lua_isstring(L,1)) SWIG_fail_arg("WARNING",1,"string");
      
      arg1 = (OSG::Char8 *)lua_tostring(L, 1);
      
      SWARNING << arg1 << std::endl;
      return SWIG_arg;
      
    fail:
      lua_error(L);
      return SWIG_arg;
    }
    
    int OSGLogNOTICE(lua_State*L)
    {
      int SWIG_arg = 0;
      OSG::Char8 *arg1 = (OSG::Char8 *) 0 ;
      
      SWIG_check_num_args("NOTICE",1,1)
      if(!lua_isstring(L,1)) SWIG_fail_arg("NOTICE",1,"string");
      
      arg1 = (OSG::Char8 *)lua_tostring(L, 1);
      
      SNOTICE << arg1 << std::endl;
      return SWIG_arg;
      
    fail:
      lua_error(L);
      return SWIG_arg;
    }
    
    int OSGLogINFO(lua_State*L)
    {
      int SWIG_arg = 0;
      OSG::Char8 *arg1 = (OSG::Char8 *) 0 ;
      
      SWIG_check_num_args("INFO",1,1)
      if(!lua_isstring(L,1)) SWIG_fail_arg("INFO",1,"string");
      
      arg1 = (OSG::Char8 *)lua_tostring(L, 1);
      
      SINFO << arg1 << std::endl;
      return SWIG_arg;
      
    fail:
      lua_error(L);
      return SWIG_arg;
    }
%}

namespace OSG {
    typedef char           Char8;
    typedef unsigned char UChar8;
    typedef signed char   SChar8;
    typedef int     Int8;
    typedef unsigned int   UInt8;
    typedef int    Int16;
    typedef unsigned int  UInt16;
    typedef int    Int32;
    typedef unsigned int  UInt32;
    typedef long    Int64;
    typedef long     TimeStamp;
    typedef unsigned long  UInt64;
    typedef unsigned long  BitVector;
    typedef float      Real16;
    typedef float      Real32;
    typedef double     Real64;
    typedef double     Time;
    typedef long double Real128;
    
    class Volume;
    class Line;
    class Plane;


    /******************************************************/
    /*              Real16                                */
    /******************************************************/

    /******************************************************/
    /*              Colors                                */
    /******************************************************/
    class Color3f
    {
        public:
        Color3f(      void             );
        Color3f(const Color3f    &source);
        Color3f(      Real32  red,
                     Real32  green,
                     Real32  blue  );
        void clear        (     void               );

        void setValuesRGB(const Real32  red,
                          const Real32  green,
                          const Real32  blue    );

        void setValuesHSV(const Real32     h,
                          const Real32     s,
                          const Real32     v       );

        void setRandom   (      void               );
        void setRGB      (      UInt32     rgbPack );

        void setValue    (      Char8     *szString);
              UInt32     getRGB       (void           ) const;

              void       getValuesHSV(Real32    &h,
                                      Real32    &s,
                                      Real32    &v    ) const;

              Real32  red         (void            ) const;
              Real32  green       (void            ) const;
              Real32  blue        (void            ) const;

          Color3f     operator * (const Real32  val      ) const;
          Color3f     operator / (const Real32  val      ) const;
          Color3f     operator + (const Real32  val      ) const;
          Color3f     operator - (const Real32  val      ) const;
          Color3f     operator + (const Color3f    &other    ) const;
          Color3f     operator - (const Color3f    &other    ) const;
           bool      equals     (const Color3f    &other,
                                 const Real32  tolerance) const;
           bool      operator < (const Color3f    &other    ) const;
           bool      operator ==(const Color3f    &other    ) const;
    };

    class Color4f
    {
      public:

        Color4f(      void             );
        Color4f(const Color4f    &source);
        Color4f(const Real32  red,
               const Real32  green,
               const Real32  blue,
               const Real32  alpha );
        ~Color4f(void);
        void clear        (      void           );

        void setValuesRGBA(const Real32 red,
                           const Real32 green,
                           const Real32 blue,
                           const Real32 alpha);

        void setValuesHSV (const Real32 h,
                           const Real32 s,
                           const Real32 v       );

        void setRandom    (      void           );
        void setRGBA      (      UInt32 rgbPack );   

        void setValue     (      Char8 *szString);
              UInt32    getRGBA       (void            ) const;

              void      getValuesHSV  (Real32    &h,
                                       Real32    &s,
                                       Real32    &v    ) const;

              Real32 red           (void            ) const;
              Real32 green         (void            ) const;
              Real32 blue          (void            ) const;
              Real32 alpha         (void            ) const;

              Color4f     operator * (const Real32  val      ) const;
              Color4f     operator / (const Real32  val      ) const;
              Color4f     operator + (const Real32  val      ) const;
              Color4f     operator - (const Real32  val      ) const;
              Color4f     operator + (const Color4f    &other    ) const;
              Color4f     operator - (const Color4f    &other    ) const;
              bool       equals     (const Color4f    &other,
                                     const Real32  tolerance) const;

              bool       operator < (const Color4f    &other    ) const;
              bool       operator ==(const Color4f    &other    ) const;
    };

    /******************************************************/
    /*              Pnts                                  */
    /******************************************************/
    class Pnt2f
    {
    public:
        typedef          Real32                             ValueType;
        typedef          Pnt2f                             PointType;
        typedef          Vec2f                             VectorType;
        Pnt2f(void);
        
        Pnt2f(const PointType &source);
        Pnt2f(const VectorType &source);
        Pnt2f(const ValueType rVal1, const ValueType rVal2);
        ~Pnt2f(void);

        Pnt2f(const ValueType rVal1);
        void setValueFromCString(      Char8              *szString);
              bool            isZero  (      void                 ) const;

              void            negate  (      void                 );

              bool            equals  (const PointType      &vec,
                                       const ValueType  tolerance) const;

              VectorType     &subZero (      void                 );

              ValueType  dist    (const PointType      &vec      ) const;
              ValueType  dist2   (const PointType      &vec      ) const;

              ValueType  maxValue(      void                 ) const;

        void       setValues        (const ValueType  rVal1,
                                     const ValueType  rVal2);
        ValueType x                (void                   ) const;
        ValueType y                (void                   ) const;

        VectorType operator - (const PointType      &vec ) const;

        PointType      operator + (const VectorType &vec ) const;

        PointType      operator - (const VectorType &vec ) const;

        PointType      operator * (const ValueType  rVal) const;

        PointType      operator / (const ValueType  rVal) const;

        PointType      operator - (      void            );
    };

    class Pnt3f
    {
    public:
        typedef          Real32                             ValueType;
        typedef          Pnt3f                             PointType;
        typedef          Vec3f                             VectorType;
        Pnt3f(void);
        
        Pnt3f(const PointType &source);
        Pnt3f(const VectorType &source);
        Pnt3f(const ValueType rVal1, const ValueType rVal2, const ValueType rVal3);
        ~Pnt3f(void);

        Pnt3f(const ValueType rVal1);
        void setValueFromCString(      Char8              *szString);
              bool            isZero  (      void                 ) const;

              void            negate  (      void                 );

              bool            equals  (const PointType      &vec,
                                       const ValueType  tolerance) const;

              VectorType     &subZero (      void                 );

              ValueType  dist    (const PointType      &vec      ) const;
              ValueType  dist2   (const PointType      &vec      ) const;

              ValueType  maxValue(      void                 ) const;

        void       setValues        (const ValueType  rVal1,
                                     const ValueType  rVal2,
                                     const ValueType  rVal3);
        ValueType x                (void                   ) const;
        ValueType y                (void                   ) const;
        ValueType z                (void                   ) const;

        VectorType operator - (const PointType      &vec ) const;

        PointType      operator + (const VectorType &vec ) const;

        PointType      operator - (const VectorType &vec ) const;

        PointType      operator * (const ValueType  rVal) const;

        PointType      operator / (const ValueType  rVal) const;

        PointType      operator - (      void            );
    };

    class Pnt4f
    {
    public:
        typedef          Real32                             ValueType;
        typedef          Pnt4f                             PointType;
        typedef          Vec4f                             VectorType;
        Pnt4f(void);
        
        Pnt4f(const PointType &source);
        Pnt4f(const VectorType &source);
        Pnt4f(const ValueType rVal1, const ValueType rVal2, const ValueType rVal3, const ValueType rVal4);
        ~Pnt4f(void);

        Pnt4f(const ValueType rVal1);
        void setValueFromCString(      Char8              *szString);
              bool            isZero  (      void                 ) const;

              void            negate  (      void                 );

              bool            equals  (const PointType      &vec,
                                       const ValueType  tolerance) const;

              VectorType     &subZero (      void                 );

              ValueType  dist    (const PointType      &vec      ) const;
              ValueType  dist2   (const PointType      &vec      ) const;

              ValueType  maxValue(      void                 ) const;

        void       setValues        (const ValueType  rVal1,
                                     const ValueType  rVal2,
                                     const ValueType  rVal3,
                                     const ValueType  rVal4);
        ValueType x                (void                   ) const;
        ValueType y                (void                   ) const;
        ValueType z                (void                   ) const;
        ValueType w                (void                   ) const;

        VectorType operator - (const PointType      &vec ) const;

        PointType      operator + (const VectorType &vec ) const;

        PointType      operator - (const VectorType &vec ) const;

        PointType      operator * (const ValueType  rVal) const;

        PointType      operator / (const ValueType  rVal) const;

        PointType      operator - (      void            );
    };
    /******************************************************/
    /*              Vector                                  */
    /******************************************************/
    class Vec2f : public Pnt2f
    {
      public:

        typedef          Real32                             ValueType;
        typedef          Pnt2f                             PointType;
        typedef          Vec2f                             VectorType;

        /*---------------------------------------------------------------------*/
        /*! \name                   Constructors                               */
        /*! \{                                                                 */

        Vec2f(      void                               );


        Vec2f(const VectorType                      &source);
        Vec2f(const PointType                      &source);

        Vec2f(const ValueType                   rVal1 );
        Vec2f(const ValueType rVal1, const ValueType rVal2);

        ~Vec2f(void);
        ValueType  length       (      void            ) const;
        ValueType  squareLength (      void            ) const;

        void            normalize    (      void            );

        VectorType          cross        (const VectorType    &vec  ) const;

        void            crossThis    (const VectorType    &vec  );

        ValueType      dot          (const VectorType    &vec  ) const;
        ValueType      operator *   (const VectorType    &vec  ) const;
        ValueType      dot          (const PointType &pnt  ) const;
        ValueType      operator *   (const PointType &pnt  ) const;

        ValueType  enclosedAngle(const VectorType    &vec  ) const;

        ValueType  projectTo    (const VectorType    &toVec);
              PointType &addToZero (void);
        VectorType operator - (const VectorType     &vec ) const;
        VectorType operator + (const VectorType     &vec ) const;

        VectorType operator * (const ValueType  rVal) const;

        VectorType      operator / (const ValueType  rVal) const;

        VectorType operator - (      void            ) const;
        bool operator <  (const VectorType &other) const;

        bool operator == (const VectorType &other) const;
    };

    class Vec3f : public Pnt3f
    {
      public:

        typedef          Real32                             ValueType;
        typedef          Pnt3f                             PointType;
        typedef          Vec3f                             VectorType;

        /*---------------------------------------------------------------------*/
        /*! \name                   Constructors                               */
        /*! \{                                                                 */

        Vec3f(      void                               );


        Vec3f(const VectorType                      &source);
        Vec3f(const PointType                      &source);

        Vec3f(const ValueType                   rVal1 );
        Vec3f(const ValueType rVal1, const ValueType rVal2, const ValueType rVal3);

        ~Vec3f(void);
        ValueType  length       (      void            ) const;
        ValueType  squareLength (      void            ) const;

        void            normalize    (      void            );

        VectorType          cross        (const VectorType    &vec  ) const;

        void            crossThis    (const VectorType    &vec  );

        ValueType      dot          (const VectorType    &vec  ) const;
        ValueType      operator *   (const VectorType    &vec  ) const;
        ValueType      dot          (const PointType &pnt  ) const;
        ValueType      operator *   (const PointType &pnt  ) const;

        ValueType  enclosedAngle(const VectorType    &vec  ) const;

        ValueType  projectTo    (const VectorType    &toVec);
              PointType &addToZero (void);
        VectorType operator - (const VectorType     &vec ) const;
        VectorType operator + (const VectorType     &vec ) const;

        VectorType operator * (const ValueType  rVal) const;

        VectorType      operator / (const ValueType  rVal) const;

        VectorType operator - (      void            ) const;
        bool operator <  (const VectorType &other) const;

        bool operator == (const VectorType &other) const;
    };

    class Vec4f : public Pnt4f
    {
      public:

        typedef          Real32                             ValueType;
        typedef          Pnt4f                             PointType;
        typedef          Vec4f                             VectorType;

        /*---------------------------------------------------------------------*/
        /*! \name                   Constructors                               */
        /*! \{                                                                 */

        Vec4f(      void                               );


        Vec4f(const VectorType                      &source);
        Vec4f(const PointType                      &source);

        Vec4f(const ValueType                   rVal1 );
        Vec4f(const ValueType rVal1, const ValueType rVal2, const ValueType rVal3, const ValueType rVal4);

        ~Vec4f(void);
        ValueType  length       (      void            ) const;
        ValueType  squareLength (      void            ) const;

        void            normalize    (      void            );

        VectorType          cross        (const VectorType    &vec  ) const;

        void            crossThis    (const VectorType    &vec  );

        ValueType      dot          (const VectorType    &vec  ) const;
        ValueType      operator *   (const VectorType    &vec  ) const;
        ValueType      dot          (const PointType &pnt  ) const;
        ValueType      operator *   (const PointType &pnt  ) const;

        ValueType  enclosedAngle(const VectorType    &vec  ) const;

        ValueType  projectTo    (const VectorType    &toVec);
              PointType &addToZero (void);
        VectorType operator - (const VectorType     &vec ) const;
        VectorType operator + (const VectorType     &vec ) const;

        VectorType operator * (const ValueType  rVal) const;
        VectorType      operator / (const ValueType  rVal) const;

        VectorType operator - (      void            ) const;
        bool operator <  (const VectorType &other) const;

        bool operator == (const VectorType &other) const;
    };
    /******************************************************/
    /*              Matricies                             */
    /******************************************************/
    class Matrix
    {
      public:

        typedef                 Real32                ValueType;
        typedef          Vec4f VectorType;

        typedef Quaternion                QuaternionType;

        typedef Vec3f VectorType3f;
        typedef Pnt4f PointType;
        typedef Pnt3f PointType3f;
                               
        /*---------------------------------------------------------------------*/
        static const Matrix &identity(void);

        /*---------------------------------------------------------------------*/
        Matrix(void);
        Matrix(const Matrix &source );

        Matrix(const VectorType3f         &vector1,
                             const VectorType3f         &vector2,
                             const VectorType3f         &vector3);   

        Matrix(const VectorType3f         &vector1,
                             const VectorType3f         &vector2,
                             const VectorType3f         &vector3,
                             const VectorType3f         &vector4);   

        Matrix(const ValueType            rVal00,
                             const ValueType            rVal10,
                             const ValueType            rVal20,
                             const ValueType            rVal30,
                             
                             const ValueType            rVal01,
                             const ValueType            rVal11,
                             const ValueType            rVal21,
                             const ValueType            rVal31,
                             
                             const ValueType            rVal02,
                             const ValueType            rVal12,
                             const ValueType            rVal22,
                             const ValueType            rVal32,
                             
                             const ValueType            rVal03,
                             const ValueType            rVal13,
                             const ValueType            rVal23,
                             const ValueType            rVal33);
     
        /*---------------------------------------------------------------------*/
        ~Matrix(void);

        /*---------------------------------------------------------------------*/
        void setIdentity       (void                                           );

        void setValue          (const Matrix &mat                );

        void setValue          (const VectorType3f         &vector1,
                                const VectorType3f         &vector2,
                                const VectorType3f         &vector3            );

        void setValue          (const VectorType3f         &vector1,
                                const VectorType3f         &vector2,
                                const VectorType3f         &vector3,
                                const VectorType3f         &vector4            );

        void setValue          (const ValueType            rVal00,
                                const ValueType            rVal10,
                                const ValueType            rVal20,
                                const ValueType            rVal30,
                                
                                const ValueType            rVal01,
                                const ValueType            rVal11,
                                const ValueType            rVal21,
                                const ValueType            rVal31,
                                
                                const ValueType            rVal02,
                                const ValueType            rVal12,
                                const ValueType            rVal22,
                                const ValueType            rVal32,
                                
                                const ValueType            rVal03,
                                const ValueType            rVal13,
                                const ValueType            rVal23,
                                const ValueType            rVal33             );


        void setValue          (const ValueType           *pMat,
                                      bool                  bTransposed = true );

        void setValue           (const Char8               *string,
                                       bool                 bTransposed = true );

        /*---------------------------------------------------------------------*/
        void setScale    (const ValueType      s               );

        void setScale    (const ValueType      sx,
                          const ValueType      sy,
                          const ValueType      sz              );

        void setScale    (const VectorType3f   &s               );


        void setTranslate(const ValueType      tx,
                          const ValueType      ty,
                          const ValueType      tz              );

        void setTranslate(const VectorType3f   &t               );

        void setTranslate(const PointType3f    &t               );


        void setRotate   (const QuaternionType &q               );


        void setTransform(const VectorType3f   &t               );

        void setTransform(const QuaternionType &r               );

        void setTransform(const VectorType3f   &t,
                          const QuaternionType &r               );

        void setTransform(const VectorType3f   &t,
                          const QuaternionType &r,
                          const VectorType3f   &s               );

        void setTransform(const VectorType3f   &t,
                          const QuaternionType &r,
                          const VectorType3f   &s,
                          const QuaternionType &so              );

        void setTransform(const VectorType3f   &translation,
                          const QuaternionType &rotation,
                          const VectorType3f   &scaleFactor,
                          const QuaternionType &scaleOrientation,
                          const VectorType3f   &center          );

        void getTransform(      VectorType3f         &translation,
                                QuaternionType       &rotation,
                                VectorType3f         &scaleFactor,
                                QuaternionType       &scaleOrientation,
                          const VectorType3f         &center) const;

        void getTransform(      VectorType3f         &translation,
                                QuaternionType       &rotation,
                                VectorType3f         &scaleFactor,
                                QuaternionType       &scaleOrientation) const;

        bool factor      (      Matrix &r,
                                VectorType3f         &s,
                                Matrix &u,
                                VectorType3f         &t,
                                Matrix &proj) const;
        
        void mult    (const PointType    &pntIn, PointType    &pntOut) const;
        void multFull(const PointType3f  &pntIn, PointType3f  &pntOut) const;
        void mult    (const PointType3f  &pntIn, PointType3f  &pntOut) const;
        
        void mult    (const VectorType   &vecIn, VectorType   &vecOut) const;
        void multFull(const VectorType3f &vecIn, VectorType3f &vecOut) const;
        void mult    (const VectorType3f &vecIn, VectorType3f &vecOut) const;
        
        void mult3x3 (const PointType3f  &pntIn, PointType3f  &pntOut) const;
        void mult3x3 (const VectorType3f &vecIn, VectorType3f &vecOut) const;
        
        PointType    operator *(const PointType    &pntIn) const;
        PointType3f  operator *(const PointType3f  &pntIn) const;
                 
        VectorType   operator *(const VectorType   &vecIn) const;
        VectorType3f operator *(const VectorType3f &vecIn) const;

        
        bool       equals       (const Matrix &matrix,
                                 const ValueType             tol   ) const;

        ValueType det3         (      void                        ) const;
        ValueType det          (      void                        ) const;

        bool       inverse      (      Matrix &result) const;
        bool       invert       (      void                        );
        bool       invertFrom   (const Matrix &matrix);

        bool       inverse3     (      Matrix &result) const;
        bool       invert3      (      void                        );
        bool       invertFrom3  (const Matrix &matrix);

        bool       transposed   (      Matrix &result) const;
        bool       transpose    (      void                        );
        bool       transposeFrom(const Matrix &matrix);

        void       mult         (const Matrix &matrix);
        void       multLeft     (const Matrix &matrix);
        
        void       add          (const Matrix &matrix);
        void       scale        (      ValueType            s     );
        void       addScaled    (const Matrix &matrix,
                                       ValueType            s     );
        void       negate       (      void                        );
        
        ValueType norm1        (      void                        ) const;
        ValueType norm2        (      void                        ) const;
        ValueType normInfinity (      void                        ) const;
        
        bool       sqrtOf       (const Matrix &matrix);
        bool       sqrt         (      void                        );
        
        bool       log          (      Matrix &result) const;
        bool       logOf        (const Matrix &matrix);
        
        bool       exp          (      Matrix &result) const;
        bool       expOf        (const Matrix &matrix);


        bool operator == (const Matrix &other) const;

    };

    /******************************************************/
    /*              Quaternion                            */
    /******************************************************/
    class Quaternion
    {
      public:
        typedef Vec3f VectorType;
        typedef Matrix MatrixType;
        static const Quaternion &identity(void                          );

                    Quaternion(      void                               );
                    Quaternion(const Quaternion &source             );
        explicit    Quaternion(const MatrixType     &matrix             );
                    Quaternion(const VectorType     &axis,
                                   const Real32      angle              );
                    Quaternion(const VectorType     &rotateFrom,
                                   const VectorType     &rotateTo           );
        virtual ~Quaternion(void);
        void setIdentity      (       void                  );

        void setValueAsAxisRad(const  Real32  x,
                               const  Real32  y,
                               const  Real32  z,
                               const  Real32  w         );
        void setValueAsAxisDeg(const  Real32  x,
                               const  Real32  y,
                               const  Real32  z,
                               const  Real32  w         );
        void setValueAsQuat   (const  Real32  x,
                               const  Real32  y,
                               const  Real32  z,
                               const  Real32  w         );

        void setValue         (const  MatrixType &matrix    );

        void setValueAsAxisRad(const  VectorType &axis,   
                                      Real32  angle     );
        void setValueAsAxisDeg(const  VectorType &axis,
                                      Real32  angle     );

        void setValue         (const  VectorType &rotateFrom,
                               const  VectorType &rotateTo  );

        void setValueAsAxisRad(const  Char8       *str      );
        void setValueAsAxisDeg(const  Char8       *str      );
        void setValueAsQuat   (const  Char8       *str      );

        void setValue         (const  Real32 alpha,
                               const  Real32 beta,
                               const  Real32 gamma      );

              void        getValueAsAxisDeg(Real32 &x,
                                            Real32 &y,
                                            Real32 &z,
                                            Real32 &w      ) const;
              void        getValueAsAxisRad(Real32 &x,
                                            Real32 &y,
                                            Real32 &z,
                                            Real32 &w      ) const;
              void        getValueAsQuat   (Real32 &x,
                                            Real32 &y,
                                            Real32 &z,
                                            Real32 &w      ) const;

              void       getValueAsAxisRad (VectorType &axis,
                                            Real32 &radians) const;
              void       getValueAsAxisDeg (VectorType &axis,
                                            Real32 &degrees) const;
              void       getEulerAngleRad  (VectorType &euler  ) const;
              void       getEulerAngleDeg  (VectorType &euler  ) const;
              void       getValue          (MatrixType &matrix ) const;
              void       getValuesOnly     (MatrixType &matrix ) const;

              Real32 x                 (void               ) const;
              Real32 y                 (void               ) const;
              Real32 z                 (void               ) const;
              Real32 w                 (void               ) const;
              Real32      length    (void                        ) const;
          Real32      lengthSquared (void                        ) const;
              void            normalize (void                        );

              void            invert    (void                        );
        const Quaternion  inverse   (void                        ) const;
          Quaternion  conj   (void                        ) const;
          Quaternion  exp    (void                        ) const;
          Quaternion  log    (void                        ) const;

              void            multVec   (const VectorType &src,
                                               VectorType &dst       ) const;

              void            scaleAngle(      Real32 scaleFactor);

              void            slerpThis (const Quaternion &rot0,
                                         const Quaternion &rot1,
                                         const Real32      t     );

              void            nlerpThis (const Quaternion &rot0,
                                     const Quaternion &rot1,
                                     const Real32      t     );

              void            mult      (const Quaternion &other );
              void            multLeft  (const Quaternion &other );

              bool            equals    (const Quaternion &rot,
                                         const Real32 tolerance  ) const;

        bool operator == (const Quaternion &other) const;

    };

    /******************************************************/
    /*              TypeBase                              */
    /******************************************************/
    class TypeBase
    {
      public :
        TypeBase(const Char8  *szName,
                 const Char8  *szParentName,
                 const UInt32  uiNameSpace = 0);
        virtual ~TypeBase(void);

              UInt32    getId         (void) const;

        const std::string &getName       (void) const;

        const std::string &getParentName (void) const;

              UInt32    getNameSpace  (void) const;

        virtual bool isDerivedFrom(const TypeBase &other) const;

        bool operator ==(const TypeBase &other) const;
    };
    /******************************************************/
    /*              DataType                              */
    /******************************************************/
    class DataType : public TypeBase
    {
      public :
        DataType(const Char8  *szName,
                 const Char8  *szParentName,
                 const UInt32  uiNameSpace = 0);
        virtual ~DataType(void);

        bool operator ==(const DataType &other) const;
    };

    /******************************************************/
    /*              TypeFactory                           */
    /******************************************************/
    class TypeFactory
    {
      public :
        static TypeFactory *the(void);

    protected:
        TypeFactory(void);

        virtual ~TypeFactory(void);

    };
    %extend TypeFactory
    {
        UInt32    registerType  (      TypeBase *pType          )
        {
            return OSG::TypeFactory::the()->registerType(pType);
        }

        UInt32    findTypeId    (const Char8    *szName,
                                 const UInt32    uiNameSpace = 0)
        {
            return OSG::TypeFactory::the()->findTypeId(szName,uiNameSpace);
        }

        TypeBase *findType      (      UInt32    uiTypeId       )
        {
            return OSG::TypeFactory::the()->findType(uiTypeId);
        }
        TypeBase *findType      (const Char8    *szName  ,
                                 const UInt32    uiNameSpace = 0)
        {
            return OSG::TypeFactory::the()->findType(szName,uiNameSpace);
        }


        UInt32    getNumTypes   (      void                     )
        {
            return OSG::TypeFactory::the()->getNumTypes();
        }

        void      writeTypeGraph(const Char8    *szFilename     )
        {
            OSG::TypeFactory::the()->writeTypeGraph(szFilename);
        }
    }

    /******************************************************/
    /*              Volumes                               */
    /******************************************************/
    class Volume
    {
      public:
        void   setValid     (const bool   value = true);
        bool   isValid      (      void               ) const;
    
        void   setEmpty     (const bool   value = true);
        bool   isEmpty      (      void               ) const;
    
        void   setStatic    (const bool   value = true);
        bool   isStatic     (      void               ) const;
    
        void   setInfinite  (const bool   value = true);
        bool   isInfinite   (      void               ) const;
    
        bool   isUntouchable(      void               ) const;
    
        UInt16 getState     (      void               ) const;
        void   setState     (      UInt16 state       );
    
        
        virtual void  getCenter      (Pnt3f &center         ) const = 0;
    
        virtual float getScalarVolume(void                  ) const = 0;
    
        virtual void  getBounds      (Pnt3f &min, Pnt3f &max) const = 0;
    
                Pnt3f getMin         (void                  ) const;
                Pnt3f getMax         (void                  ) const;
    
        virtual void extendBy(const Pnt3f  &pt    ) = 0;
        virtual void extendBy(const Volume &volume) = 0;
    
        virtual bool intersect  (const Pnt3f  &point ) const = 0;
        virtual bool intersect  (const Line   &line  ) const = 0;
        virtual bool intersect  (const Line   &line,
                                       Real32 &enter,
                                       Real32 &exit  ) const = 0;
        virtual bool intersect  (const Volume &volume) const = 0;
    
        virtual bool isOnSurface(const Pnt3f  &point ) const = 0;
    
        
        virtual void transform(const Matrix &matrix) = 0;
    
        bool operator ==(const Volume &other) const;
    
      protected:
        Volume(void);
        Volume(const Volume &obj);
    };

    /******************************************************/
    /*              BoxVolume                             */
    /******************************************************/
    class BoxVolume : public Volume
    {
      public:

        BoxVolume(      void          );

        BoxVolume(const Pnt3f     &min,
                  const Pnt3f     &max);
        BoxVolume(const BoxVolume &obj);

        
        ~BoxVolume();
        
                const Pnt3f &getMin         (void                      ) const;   
                const Pnt3f &getMax         (void                      ) const;

        virtual       void   getCenter      (Pnt3f &center             ) const;

        virtual       Real32   getScalarVolume(void                      ) const;


                      void   getCorners     (Pnt3f &nlt,    Pnt3f &nlb,
                                             Pnt3f &nrt,    Pnt3f &nrb,
                                             Pnt3f &flt,    Pnt3f &flb,
                                             Pnt3f &frt,    Pnt3f &frb ) const;
        

                      void   getOrigin      (Real32  &originX,
                                             Real32  &originY,
                                             Real32  &originZ            ) const;
                      void   getSize        (Vec3f &vec                ) const;   

        void setBounds(      Real32   w,        
                             Real32   h,   
                             Real32   d   );
        void setBounds(const Pnt3f &min,
                       const Pnt3f &max );

        void setBoundsByCenterAndSize(const Pnt3f &center,
                                      const Vec3f &size  );

        virtual void extendBy(const Pnt3f     &pt    );
        virtual void extendBy(const Volume    &volume);
                void extendBy(const BoxVolume &bb    );

        virtual bool intersect  (const Pnt3f     &point ) const;
        virtual bool intersect  (const Line      &line  ) const;
        virtual bool intersect  (const Line      &line,
                                       Real32      &min,
                                       Real32      &max   ) const;
        virtual bool intersect  (const Volume    &volume) const;

                bool intersect  (const BoxVolume &bb    ) const;

        virtual bool isOnSurface(const Pnt3f     &point ) const;

        virtual void transform(const Matrix &m);

        /*BoxVolume &operator = (const BoxVolume &rhs);*/

        bool       operator ==(const BoxVolume &rhs) const;
    };

    /******************************************************/
    /*              FrustumVolume                         */
    /******************************************************/
    class FrustumVolume : public Volume
    {
      public:
        
        enum { P_NONE   = 0,
               P_NEAR   = 1, 
               P_FAR    = 2,
               P_LEFT   = 4,
               P_RIGHT  = 8,
               P_TOP    = 16,
               P_BOTTOM = 32,
               P_ALL    = P_NEAR | P_FAR | P_LEFT | P_RIGHT | P_TOP | P_BOTTOM
             };
             
        typedef UInt8 PlaneSet;
          
        FrustumVolume(      void                                     ); 
        FrustumVolume(const Plane         &pnear, const Plane &pfar,
                      const Plane         &left,  const Plane &right,
                      const Plane         &top,   const Plane &bottom);
        FrustumVolume(const FrustumVolume &obj                       );
        
        ~FrustumVolume(void); 
        
                const Plane  &getNear        (void                      ) const;
                const Plane  &getFar         (void                      ) const;
                const Plane  &getLeft        (void                      ) const;
                const Plane  &getRight       (void                      ) const;
                const Plane  &getTop         (void                      ) const;
                const Plane  &getBottom      (void                      ) const;

        virtual       void    getCenter      (Pnt3f &center             ) const;
        virtual       Real32    getScalarVolume(void                      ) const;
        virtual       void    getBounds      (Pnt3f &minPnt,
                                              Pnt3f &maxPnt             ) const;

                      void    getCorners     (Pnt3f &nlt,    Pnt3f &nlb,
                                              Pnt3f &nrt,    Pnt3f &nrb,
                                              Pnt3f &flt,    Pnt3f &flb,
                                              Pnt3f &frt,    Pnt3f &frb ) const;

        void setPlanes(const Plane   &pnear, const Plane &pfar,
                       const Plane   &left,  const Plane &right,
                       const Plane   &top,   const Plane &bottom);
        void setPlanes(const Matrix &matrix                    );

        virtual void extendBy(const Pnt3f         &pt    );
        virtual void extendBy(const Volume        &volume);   
        inline  void extendBy(const FrustumVolume &bb    );
      
        virtual bool intersect  (const Pnt3f         &point  ) const;
        virtual bool intersect  (const Line          &line   ) const;
        virtual bool intersect  (const Line          &line,
                                       Real32          &minDist,
                                       Real32          &maxDist) const;
        virtual bool intersect  (const Volume        &volume ) const;
                bool intersect  (const FrustumVolume &bb     ) const;
        virtual bool isOnSurface(const Pnt3f         &point  ) const;
      
        virtual void transform(const Matrix &m);
        

        bool           operator ==(const FrustumVolume &rhs) const;
    };

    /******************************************************/
    /*              FieldType                             */
    /******************************************************/
    class FieldType : public DataType
    {
      public:
          enum Cardinality 
          { 
              SingleField,
              MultiField
          };


          enum Class
          {
              ValueField,
              PtrField,
              ParentPtrField,
              ChildPtrField
          };


          virtual ~FieldType(void);

          const DataType    &getContentType(void) const;
          Cardinality  getCardinality(void) const;

          Class        getClass      (void) const;
          UInt32       getScanTypeId (void) const;
          bool         isPtrField    (void) const;
    };
    %extend FieldType
    {
        static FieldType* dcast( TypeBase  *val ) throw(const char *)
        {
            return dynamic_cast<OSG::FieldType  *>(val);
        }
    };

    /******************************************************/
    /*                   FactoryBase                      */
    /******************************************************/
    class FactoryBase
    {
      public :

        const std::string &getName (void) const;

      private:
        FactoryBase(const FactoryBase &source);
        ~FactoryBase();
        void operator =(const FactoryBase &source);
    };

    /******************************************************/
    /*                      Line                          */
    /******************************************************/
    class Line
    {
      public:
        Line(       void                        );
        Line(const  Line  &obj                  );
        Line(const  Pnt3f &p0,  const Pnt3f &p1 );
        Line(const  Pnt3f &pos, const Vec3f &dir);

        ~Line(void);

        bool    getClosestPoints(const Line     &line2,
                                       Pnt3f    &ptOnThis, Pnt3f &ptOnLine2) const;
        Pnt3f   getClosestPoint (const Pnt3f &point                        ) const;
        Real32  distance        (const Pnt3f &point                        ) const;

        const Pnt3f &getPosition (void) const;
        const Vec3f &getDirection(void) const;


        /*bool intersect(const SphereVolume   &sphere                     ) const;*/
        /*bool intersect(const SphereVolume   &sphere,  Real32 &enter,*/
                                                      /*Real32 &exit      ) const;*/
        /*bool intersect(const CylinderVolume &cyl                        ) const;*/
        /*bool intersect(const CylinderVolume &cyl,     Real32 &enter,*/
                                                      /*Real32 &exit      ) const;*/
        /*bool intersect(const FrustumVolume  &frustum                    ) const;*/
        /*bool intersect(const FrustumVolume  &frustum, Real32 &enter,*/
                                                      /*Real32 &exit      ) const;*/
        bool intersect(const BoxVolume      &box,     Real32 &enter,
                                                      Real32 &exit      ) const;
        bool intersect(      Real32          angle,
                       const BoxVolume      &box                        ) const;
        bool intersect(      Real32          angle,
                       const Vec3f          &point                      ) const;

        bool intersect(      Real32          angle,
                       const Vec3f          &v0,
                       const Vec3f          &v1,
                             Vec3f          &pt                         ) const;

        bool intersect(const Pnt3f          &v0,
                       const Pnt3f          &v1,
                       const Pnt3f          &v2,
                             Real32         &t,
                             Vec3f          *normal = NULL              ) const;
        
    };

    /******************************************************/
    /*                      Plane                          */
    /******************************************************/
    class Plane
    {
      public:
        Plane(      void                                        );
        Plane(const Plane &obj                                  );
        Plane(const Pnt3f &p0, const Pnt3f  &p1, const Pnt3f &p2);
        Plane(const Vec3f &n,        Real32  d                  );
        Plane(const Vec3f &n, const  Pnt3f  &p                  );

        ~Plane(void);

        void offset(Real32 d);

        bool   intersect        (const Plane  &pl, Line   &intersection) const;
        bool   intersect        (const Line   &l,  Pnt3f  &intersection) const;
        bool   intersect        (const Line   &l,  Real32 &t           ) const;

        bool   intersectInfinite(const Line   &l,  Real32 &t           ) const;
        bool   intersectInfinite(const Line   &l,  Pnt3f  &intersection) const;

        void   transform        (const Matrix &matrix                  );

        int    clip             (Pnt3f *polyIn, Pnt3f *polyOut, int count) const;

        bool   isOnPlane          (const Pnt3f  &point          ) const;
        bool   isInHalfSpace      (const Pnt3f  &point          ) const;
        Real32 distance           (const Pnt3f  &point          ) const;

        bool   isInHalfSpace  (const Pnt3f  &min, const Pnt3f  &max) const;

        inline const Vec3f  &getNormal            (void) const;
        inline       Real32  getDistanceFromOrigin(void) const;


        inline void  setDirectionIndexPoint(
                            const Pnt3f &min, const Pnt3f & max,
                            const UInt8 index,      Pnt3f & pnt) const;
     
    };

    bool MatrixOrthogonal(Matrix &result, 
            Real32  rLeft, 
            Real32  rRight, 
            Real32  rBottom, 
            Real32  rTop, 
            Real32  rNear, 
            Real32  rFar        );

    bool MatrixFrustum(Matrix &result, 
            Real32     rLeft, 
            Real32     rRight,
            Real32     rBottom, 
            Real32     rTop, 
            Real32     rNear, 
            Real32     rFar       );

    bool MatrixPerspective(Matrix &result, 
            Real32     rFovy, 
            Real32     rAspect,
            Real32     rNear, 
            Real32     rFar        );

    bool MatrixStereoPerspective(Matrix &projection, 
            Matrix &projtrans, 
            Real32     rFovy, 
            Real32     rAspect, 
            Real32     rNear, 
            Real32     rFfar, 
            Real32     rZeroparallax, 
            Real32     rEyedistance, 
            Real32     rWhicheye, 
            Real32     rOverlap    );

    bool MatrixLookAt(Matrix &result, 
            Real32  fromx, 
            Real32  fromy, 
            Real32  fromz, 
            Real32  atx,   
            Real32  aty,   
            Real32  atz, 
            Real32  upx,   
            Real32  upy,   
            Real32  upz);

    bool MatrixLookAt(Matrix &result, 
            Pnt3f   from,
            Pnt3f   at,
            Vec3f   up);


    bool MatrixProjection(Matrix &result, 
            Real32  rLeft,
            Real32  rRight, 
            Real32  rBottom,
            Real32  rTop,  
            Real32  rNear,
            Real32  rFar);

    void makeViewFromUVND(Matrix &Result,
            const Vec3f  &U,
            const Vec3f  &V,
            const Vec3f  &N,
            const Vec3f  &D);

    void makeViewFromUVNP(Matrix &Result,
            const Vec3f  &U,
            const Vec3f  &V,
            const Vec3f  &N,
            const Pnt3f  &P);

    void getUVNDFromMat(const Matrix &Mat,
            Vec3f  &U,
            Vec3f  &V,
            Vec3f  &N,
            Vec3f  &D);
    void getUVNPFromMat(const Matrix &Mat,
            Vec3f  &U,
            Vec3f  &V,
            Vec3f  &N,
            Pnt3f  &P);

    void getPFromViewMat(Pnt3f  &P,
            const Matrix &Mat);

    void setViewMatEyePos(Matrix &Result,
            const Pnt3f  &P);
}

