
%module OSGToolbox
%include <std_except.i>
%import  <OSGBase.i>
%import  <OSGSystem.i>
%include <lua/std_map.i>
%include <lua/std_vector.i>
%{
#include "OSGWindowEventProducer.h"
#include "OSGKeyEventDetails.h"

#include "OSGSound.h"
#include "OSGSoundGroup.h"
#include "OSGSoundManager.h"

#include "OSGAnimation.h"

#include "OSGComponent.h"

#include "OSGParticleSystem.h"
#include "OSGDistribution1D.h"
#include "OSGDistribution2D.h"
#include "OSGDistribution3D.h"

#include "OSGPhysicsHandler.h"
#include "OSGPhysicsBody.h"
#include "OSGPhysicsSpace.h"
#include "OSGPhysicsWorld.h"

#include "OSGVideoWrapper.h"
#include "OSGVideoManager.h"

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
#include "OSGActivity.h"
#include "OSGWindow.h"
#include "OSGLuaActivity.h"
#include "OSGGenericEventDetails.h"
#include "OSGCgFXMaterial.h"
        
%}

namespace std {
    %template(UInt32Vec) vector<OSG::UInt32>;
    %template(StringToUInt32Map) map<string, OSG::UInt32>;
}
    

namespace OSG {

    class WindowEventProducer;
    class Sound;
    class Animation;
    class Component;
    class ParticleSystem;
    class PhysicsBody;
    class PhysicsHandler;
    class PhysicsWorld;
    class WindowRefPtr;
    
    /******************************************************/
    /*              WindowEventProducerRefPtr                             */
    /******************************************************/
    class WindowEventProducerRefPtr : public AttachmentContainerRefPtr
    {
      public:
         WindowEventProducerRefPtr(void);
         WindowEventProducerRefPtr(const WindowEventProducerRefPtr               &source);
         /*WindowEventProducerRefPtr(const NullFieldContainerRefPtr &source);*/


        ~WindowEventProducerRefPtr(void); 
        WindowEventProducer *operator->(void);
    };
    %extend WindowEventProducerRefPtr
    {
        static WindowEventProducerRefPtr dcast(const FieldContainerRefPtr oIn)
        {
            return OSG::dynamic_pointer_cast<OSG::WindowEventProducer>(oIn);
        }
    };
    
    /******************************************************/
    /*                       WindowEventProducer                       */
    /******************************************************/ 
    class WindowEventProducer : public AttachmentContainer
    {
      public:

        /*class FileDialogFilter*/
        /*{*/
        /*public:*/
            /*FileDialogFilter(const std::string& Name, const std::string& Filter);*/

            /*const std::string& getName(void) const;*/
            /*const std::string& getFilter(void) const;*/
        /*private:*/
            /*std::string _Name;*/
            /*std::string _Filter;*/
        /*};*/

        enum CursorType {
            CURSOR_POINTER         = 0,
            CURSOR_HAND            = 1,
            CURSOR_I_BEAM          = 2,
            CURSOR_WAIT            = 3,
            CURSOR_RESIZE_W_TO_E   = 4,
            CURSOR_RESIZE_N_TO_S   = 5,
            CURSOR_RESIZE_NW_TO_SE = 6,
            CURSOR_RESIZE_SW_TO_NE = 7,
            CURSOR_RESIZE_ALL      = 8,
            CURSOR_NONE            = 9
        };

        //virtual WindowRefPtr initWindow(void);

        virtual void openWindow(const Pnt2f& ScreenPosition,
                           const Vec2f& Size,
                           const std::string& WindowName) = 0;
        virtual void closeWindow(void) = 0;
        
        /*virtual void mainLoop(void) = 0;*/

        //Set the Window Position
        virtual void setPosition(Pnt2f Pos) = 0;
        //Set the Window Position
        virtual Pnt2f getPosition(void) const = 0;

        //Set the Window size
        //virtual void setSize(Vec2us Size) = 0;

        //Get the Window size
        virtual Vec2f getSize(void) const = 0;

        //Focused
        //Set the Window Focus
        virtual void setFocused(bool Focused) = 0;

        //Get the Window Focus
        virtual bool getFocused(void) const = 0;

        //Visible / Iconify / Normal
        //Set the Window Visible
        virtual void setVisible(bool Visible) = 0;

        //Get the Window Visible
        virtual bool getVisible(void) const = 0;

        //Set the Window Iconify
        virtual void setIconify(bool Iconify) = 0;

        //Get the Window Iconify
        virtual bool getIconify(void) const = 0;

        //Fullscreen
        virtual void setFullscreen(bool Fullscreen) = 0;

        //Get the Window Fullscreen
        virtual bool getFullscreen(void) const = 0;

        //Set the text on the Title bar of the window
        virtual void setTitle(const std::string& TitleText) = 0;

        //Get the text of the Title bar of the window
        virtual std::string getTitle(void) = 0;

        //Set the window to allow or not allow Resizing
        virtual void setRisizable(bool IsResizable) = 0;

        //Get whether or not the window allows resizing
        virtual bool getRisizable(void) = 0;

        //Set the window to draw or not draw it's border
        /*virtual void setDrawBorder(bool DrawBorder) = 0;*/

        //Get wether or not the window is drawing a border
        /*virtual bool getDrawBorder(void) = 0;*/

        virtual void setShowCursor(bool showCursor) = 0;

        virtual bool getShowCursor(void) const = 0;
        
        virtual void setAttachMouseToCursor(bool attach) = 0;
        
        virtual bool getAttachMouseToCursor(void) const = 0;

        //Set Display Callback Function
        /*virtual void setDisplayCallback(DisplayCallbackFunc Callback);*/

        //Set Reshape Callback Function
        /*virtual void setReshapeCallback(ReshapeCallbackFunc Callback);*/

        virtual Vec2f getDesktopSize(void) const = 0;

        /*virtual std::vector<Path> openFileDialog(const std::string& WindowTitle,*/
            /*const std::vector<FileDialogFilter>& Filters,*/
            /*const Path& InitialDir,*/
            /*bool AllowMultiSelect) = 0;*/

        /*virtual Path saveFileDialog(const std::string& DialogTitle,*/
                        /*const std::vector<FileDialogFilter>& Filters,*/
                        /*const std::string& InitialFile,*/
                        /*const Path& InitialDirectory,*/
                        /*bool PromptForOverwrite*/
                        /*) = 0;*/


        /*virtual void draw(void) = 0;*/
        /*virtual void update(void) = 0;*/

        /*virtual bool attachWindow(void) = 0;*/

        virtual UInt32 getKeyModifiers(void) const = 0;
        //virtual KeyEvent::KeyState getKeyState(KeyEvent::Key TheKey) const = 0;
        
        virtual Pnt2f getMousePosition(void) const = 0;

        ViewportRefPtr windowToViewport(const Pnt2f& WindowPoint, Pnt2f& ViewportPoint);

        virtual std::string getClipboard(void) const = 0;

        virtual void putClipboard(const std::string Value) = 0;

        UInt32 getCursorType(void) const;
        void setCursorType(UInt32 Type); 

        /*RenderAction * getRenderAction(void);*/
        /*void setRenderAction(RenderAction *action);*/

        /*CursorRegionListItor addCursorRegion(const CursorRegion& r);*/
        /*bool removeCursorRegion(CursorRegionListItor RegionItor);*/

        void blockInputConnections(bool Block);
        bool isBlockInputConnections(void) const;
      protected:
        WindowEventProducer(void);
        WindowEventProducer(const WindowEventProducer &source);

        virtual ~WindowEventProducer(void);
    };


    /******************************************************/
    /*                   LuaManager                       */
    /******************************************************/
    
    /******************************************************/
    /*                 PhysicsHandlerRefPtr                  */
    /******************************************************/
    class PhysicsHandlerRefPtr : public FieldContainerRefPtr
    {
      public:
         PhysicsHandlerRefPtr(void);
         PhysicsHandlerRefPtr(const PhysicsHandlerRefPtr               &source);
         /*PhysicsHandlerRefPtr(const NullFieldContainerRefPtr &source);*/


        ~PhysicsHandlerRefPtr(void); 
        PhysicsHandler *operator->(void);
    };
    %extend PhysicsHandlerRefPtr
    {
        static PhysicsHandlerRefPtr dcast(const FieldContainerRefPtr oIn)
        {
            return OSG::dynamic_pointer_cast<OSG::PhysicsHandler>(oIn);
        }
    };

    /******************************************************/
    /*                 PhysicsHandler                     */
    /******************************************************/
    class PhysicsHandler : public FieldContainer
    {
      public:
        void detachUpdateProducer(void);

      protected:
        PhysicsHandler(void);
        PhysicsHandler(const PhysicsHandler &source);

        virtual ~PhysicsHandler(void);
    };
    %extend PhysicsHandler
    {
        void attachUpdateProducer(FieldContainerRefPtr producer)
        {
            ($self)->attachUpdateProducer(producer);
        }
    };

    /******************************************************/
    /*                 PhysicsWorldRefPtr                  */
    /******************************************************/
    class PhysicsWorldRefPtr : public FieldContainerRefPtr
    {
      public:
         PhysicsWorldRefPtr(void);
         PhysicsWorldRefPtr(const PhysicsWorldRefPtr               &source);
         /*PhysicsWorldRefPtr(const NullFieldContainerRefPtr &source);*/


        ~PhysicsWorldRefPtr(void); 
        PhysicsWorld *operator->(void);
    };
    %extend PhysicsWorldRefPtr
    {
        static PhysicsWorldRefPtr dcast(const FieldContainerRefPtr oIn)
        {
            return OSG::dynamic_pointer_cast<OSG::PhysicsWorld>(oIn);
        }
    };

    /******************************************************/
    /*                 PhysicsWorld                     */
    /******************************************************/
    class PhysicsWorld : public FieldContainer
    {
      public:
        Vec3f impulseToForce(Real32 stepsize, const Vec3f& Impulse);
        //void worldStep(Real32 stepsize);
        //void worldQuickStep(Real32 stepsize);
        void initWorld();

        PhysicsHandlerRefPtr getParentHandler(void) const;

      protected:
        PhysicsWorld(void);
        PhysicsWorld(const PhysicsWorld &source);

        virtual ~PhysicsWorld(void);
    };

    /******************************************************/
    /*                 PhysicsBodyRefPtr                  */
    /******************************************************/
    class PhysicsBodyRefPtr : public FieldContainerRefPtr
    {
      public:
         PhysicsBodyRefPtr(void);
         PhysicsBodyRefPtr(const PhysicsBodyRefPtr               &source);
         /*PhysicsBodyRefPtr(const NullFieldContainerRefPtr &source);*/


        ~PhysicsBodyRefPtr(void); 
        PhysicsBody *operator->(void);
    };
    %extend PhysicsBodyRefPtr
    {
        static PhysicsBodyRefPtr dcast(const FieldContainerRefPtr oIn)
        {
            return OSG::dynamic_pointer_cast<OSG::PhysicsBody>(oIn);
        }
    };

    /******************************************************/
    /*                 PhysicsBody                     */
    /******************************************************/
    class PhysicsBody : public FieldContainer
    {
      public:
      //dBodyID getBodyID(void);

      static  PhysicsBodyRefPtr      create          (PhysicsWorldRefPtr World);

      void setEnable(bool enable);
      bool getEnable(void) const;

	  //void setMassStruct(const dMass &mass );
	  //void getMassStruct(dMass &mass );
	  void addForce(const Vec3f &v);
	  void addTorque(const Vec3f &v);
	  void addRelForce(const Vec3f &v);
	  void addRelTorque(const Vec3f &v);
	  void addForceAtPos(const Vec3f &v,const  Vec3f &p);
	  void addForceAtRelPos(const Vec3f &v,const  Vec3f &p);
	  void addRelForceAtPos(const Vec3f &v,const Vec3f &p);
	  void addRelForceAtRelPos(const Vec3f &v,const Vec3f &p);
	  void getRelPointPos(const Vec3f &p, Vec3f &result);
	  void getRelPointVel(const Vec3f &p, Vec3f &result);
	  void getPointVel(const Vec3f &p, Vec3f &result);
	  void getPosRelPoint(const Vec3f &p, Vec3f &result);
	  void vectorToWorld(const Vec3f &p, Vec3f &result);
	  void vectorFromWorld(const Vec3f &p, Vec3f &result);
	  void setAutoDisableDefaults(void);
	  //void setData(void* someData);
	  //void* getData(void);
	  Int32 getNumJoints(void);
	  //dJointID getJoint(Int32 index);
      void initDefaults(void);

      //Mass
      void resetMass();
      void setMassParams( Real32 theMass, const Vec3f& cg,
          Real32 I11, Real32 I22, Real32 I33,
          Real32 I12, Real32 I13, Real32 I23 );
      void setSphereMass( Real32 density, Real32 radius );
      void setSphereMassTotal( Real32 totalMass, Real32 radius );
      void setCapsuleMass( Real32 density, Int32 direction,
          Real32 radius, Real32 length );
      void setCapsuleMassTotal( Real32 totalMass, Int32 direction,
          Real32 radius, Real32 length );
      void setBoxMass( Real32 density, Real32 lx, Real32 ly, Real32 lz );
      void setBoxMassTotal( Real32 totalMass, Real32 lx, Real32 ly, Real32 lz );
      void adjustMass( Real32 newMass );
      void translateMass( const Vec3f& );
      void rotateMass( const Matrix& );
      //void addMassOf( dBodyID otherBody );

      //Damping
      void setDamping (Real32 linear_scale, Real32 angular_scale);


      void setDampingDefaults (void);

      protected:
        PhysicsBody(void);
        PhysicsBody(const PhysicsBody &source);

        virtual ~PhysicsBody(void);
    };

    /******************************************************/
    /*                 PhysicsSpace                     */
    /******************************************************/
    class PhysicsSpace : public FieldContainer
    {
      public:
          //void addCollisionContactCategory(UInt64 Category1, UInt64 Category2, CollisionContactParametersRefPtr ContactParams);
          //void removeCollisionContactCategory(UInt64 Category1, UInt64 Category2);
          //CollisionContactParametersRefPtr getCollisionContactCategory(UInt64 Category1, UInt64 Category2);
          //CollisionContactParametersRefPtr getCollisionContact(UInt64 Category1, UInt64 Category2);
    
          
          //void addCollisionListenerCategory();
    
          virtual bool isPlaceable(void) const;
    
          virtual void discardLastCollision(void);

      protected:
        PhysicsSpace(void);
        PhysicsSpace(const PhysicsSpace &source);

        virtual ~PhysicsSpace(void);
    };
    /******************************************************/
    /*                 PhysicsSpaceRefPtr                  */
    /******************************************************/
    class PhysicsSpaceRefPtr : public FieldContainerRefPtr
    {
      public:
         PhysicsSpaceRefPtr(void);
         PhysicsSpaceRefPtr(const PhysicsSpaceRefPtr               &source);
         /*PhysicsSpaceRefPtr(const NullFieldContainerRefPtr &source);*/


        ~PhysicsSpaceRefPtr(void); 
        PhysicsSpace *operator->(void);
    };
    %extend PhysicsSpaceRefPtr
    {
        static PhysicsSpaceRefPtr dcast(const FieldContainerRefPtr oIn)
        {
            return OSG::dynamic_pointer_cast<OSG::PhysicsSpace>(oIn);
        }
    };

    /******************************************************/
    /*                 Key Bindings                       */
    /******************************************************/
    class KeyEventDetails
    {
      public:

         enum KeyModifiers { KEY_MODIFIER_UNKNOWN     = 0,
                             KEY_MODIFIER_SHIFT       = 1,
                             KEY_MODIFIER_CONTROL     = 2,
                             KEY_MODIFIER_ALT         = 4,
                             KEY_MODIFIER_META        = 8,
                             KEY_MODIFIER_CAPS_LOCK   = 16,
                             KEY_MODIFIER_NUM_LOCK    = 32,
                             KEY_MODIFIER_SCROLL_LOCK = 64,
//#ifdef __APPLE__
//                         KEY_MODIFIER_COMMAND     = KEY_MODIFIER_META
//#else
                         KEY_MODIFIER_COMMAND     = KEY_MODIFIER_CONTROL
//#endif
                            };
         enum Key
          {
             KEY_UNKNOWN = 0,

             KEY_BACK_SPACE = 8,
             KEY_TAB        = 9 ,


             KEY_ESCAPE     = 27 ,

             KEY_SPACE             = 32,
             KEY_EXCLAMATION_MARK  = 33 ,
             KEY_QUOTE             = 34 ,
             KEY_NUMBER_SIGN       = 35 ,
             KEY_DOLLAR            = 36 ,
             KEY_PERCENT           = 37 ,
             KEY_AMPERSAND         = 38 ,
             KEY_APOSTROPHE        = 39 ,
             KEY_LEFT_PARENTHESIS  = 40 ,
             KEY_RIGHT_PARENTHESIS = 41 ,
             KEY_ASTERISK          = 42 ,
             KEY_PLUS              = 43 ,
             KEY_COMMA             = 44,
             KEY_MINUS  = 45,
             KEY_PERIOD = 46 ,
             KEY_SLASH  = 47 ,
             KEY_0 = 48,
             KEY_1 = 49 ,
             KEY_2 = 50 ,
             KEY_3 = 51 ,
             KEY_4 = 52 ,
             KEY_5 = 53 ,
             KEY_6 = 54 ,
             KEY_7 = 55 ,
             KEY_8 = 56 ,
             KEY_9 = 57 ,
             KEY_COLON         = 58,
             KEY_SEMICOLON     = 59 ,
             KEY_LESS          = 60 ,
             KEY_EQUALS        = 61 ,
             KEY_GREATER       = 62 ,
             KEY_QUESTION_MARK = 63 ,
             KEY_AT            = 64 ,
             KEY_A = 65,
             KEY_B = 66,
             KEY_C = 67,
             KEY_D = 68,
             KEY_E = 69,
             KEY_F = 70,
             KEY_G = 71,
             KEY_H = 72,
             KEY_I = 73,
             KEY_J = 74,
             KEY_K = 75,
             KEY_L = 76,
             KEY_M = 77,
             KEY_N = 78,
             KEY_O = 79,
             KEY_P = 80,
             KEY_Q = 81,
             KEY_R = 82,
             KEY_S = 83,
             KEY_T = 84,
             KEY_U = 85,
             KEY_V = 86,
             KEY_W = 87,
             KEY_X = 88,
             KEY_Y = 89,
             KEY_Z = 90,
             KEY_OPEN_BRACKET  = 91,
             KEY_BACK_SLASH    = 92 ,
             KEY_CLOSE_BRACKET = 93 ,
             KEY_CIRCUMFLEX    = 94 ,
             KEY_UNDERSCORE    = 95 ,
             KEY_BACK_QUOTE    = 96 ,

             
             KEY_BRACE_LEFT  = 123,
             KEY_PIPE        = 124 ,
             KEY_BRACE_RIGHT = 125 ,
             KEY_TILDE       = 126 ,
             KEY_DELETE      = 127 ,

             KEY_INVERTED_EXCLAMATION_MARK,

             KEY_ALT           = 131,
             KEY_CONTROL       = 132 ,
             KEY_CAPS_LOCK     = 133 ,
             KEY_SCROLL_LOCK   = 134 ,
             KEY_NUM_LOCK      = 135 ,
             KEY_SHIFT         = 136 ,
             KEY_MENU          = 137 ,
             KEY_META          = 138 ,
             KEY_ENTER         = 139 ,

             KEY_CANCEL        = 140 ,
             KEY_CLEAR         = 141 ,
             KEY_COPY          = 142 ,
             KEY_CUT           = 143 ,
             KEY_END           = 144 ,
             KEY_INSERT        = 145 ,
             KEY_HOME          = 146 ,
             KEY_PAGE_DOWN     = 147 ,
             KEY_PAGE_UP       = 148 ,
             KEY_FIND          = 149 ,
             KEY_HELP          = 150 ,
             KEY_PASTE         = 151 ,
             KEY_PAUSE         = 152 ,
             KEY_PRINTSCREEN   = 153 ,
             KEY_STOP          = 154 ,
             KEY_UNDO          = 155 ,

             KEY_F1            = 156 ,
             KEY_F2            = 157 ,
             KEY_F3            = 158 ,
             KEY_F4            = 159 ,
             KEY_F5            = 160 ,
             KEY_F6            = 161 ,
             KEY_F7            = 162 ,
             KEY_F8            = 163 ,
             KEY_F9            = 164 ,
             KEY_F10           = 165 ,
             KEY_F11           = 166 ,
             KEY_F12           = 167 ,
             KEY_F13           = 168 ,
             KEY_F14           = 169 ,
             KEY_F15           = 170 ,
             KEY_F16           = 171 ,
             KEY_F17           = 172 ,
             KEY_F18           = 173 ,
             KEY_F19           = 174 ,
             KEY_F20           = 175 ,
             KEY_F21           = 176 ,
             KEY_F22           = 177 ,
             KEY_F23           = 178 ,
             KEY_F24           = 179 ,


             KEY_RIGHT         = 180 ,
             KEY_LEFT          = 181 ,
             KEY_UP            = 182 ,
             KEY_DOWN          = 183 ,

             KEY_MULTIPLY      = 184 ,
             KEY_DECIMAL       = 185 ,
             KEY_ADD           = 186 ,
             KEY_DIVIDE        = 187 ,
             KEY_SUBTRACT      = 188 ,
             KEY_KEYPAD_UP     = 189 ,
             KEY_KEYPAD_DOWN   = 190 ,
             KEY_KEYPAD_LEFT   = 191 ,
             KEY_KEYPAD_RIGHT  = 192 ,
             KEY_NONE          = 193 ,
             KEY_NUMPAD_0      = 194 ,
             KEY_NUMPAD_1      = 195 ,
             KEY_NUMPAD_2      = 196 ,
             KEY_NUMPAD_3      = 197 ,
             KEY_NUMPAD_4      = 198 ,
             KEY_NUMPAD_5      = 199 ,
             KEY_NUMPAD_6      = 200 ,
             KEY_NUMPAD_7      = 201 ,
             KEY_NUMPAD_8      = 202 ,
             KEY_NUMPAD_9      = 203 ,
             KEY_NUMPAD_EQUALS = 204 ,

#ifdef __APPLE__
                         KEY_COMMAND     = KEY_META,
#else
                         KEY_COMMAND     = KEY_CONTROL,
#endif
             KEY_UNDEFINED     = 205 ,
          };
          enum KeyState
          {
              KEY_STATE_UP      = 1,
              KEY_STATE_DOWN    = 2 ,
              KEY_STATE_TOGGLED = 3 
          };
      protected:
        KeyEventDetails(void);
        KeyEventDetails(const PhysicsHandler &source);

        virtual ~KeyEventDetails(void);
    };

    /******************************************************/
    /*                 VideoManager                       */
    /******************************************************/

    /******************************************************/
    /*                 ParticleSystemRefPtr                       */
    /******************************************************/
    class ParticleSystemRefPtr : public AttachmentContainerRefPtr
    {
      public:
         ParticleSystemRefPtr(void);
         ParticleSystemRefPtr(const ParticleSystemRefPtr               &source);
         /*ParticleSystemRefPtr(const NullFieldContainerRefPtr &source);*/


        ~ParticleSystemRefPtr(void); 
        ParticleSystem *operator->(void);
    };
    %extend ParticleSystemRefPtr
    {
        static ParticleSystemRefPtr dcast(const FieldContainerRefPtr oIn)
        {
            return OSG::dynamic_pointer_cast<OSG::ParticleSystem>(oIn);
        }
    };
    
    /******************************************************/
    /*                 ParticleSystem                       */
    /******************************************************/
    class ParticleSystem : public AttachmentContainer
    {
      public:
    
        UInt32 getNumParticles(void) const;
        const Pnt3f& getPosition(const UInt32& Index) const;
        const Pnt3f& getSecPosition(const UInt32& Index) const;
        Vec3f getPositionChange(const UInt32& Index) const;
        const Vec3f& getNormal(const UInt32& Index) const;
        const Color4f& getColor(const UInt32& Index) const;
        const Vec3f& getSize(const UInt32& Index) const;
        Real32 getLifespan(const UInt32& Index) const;
        Real32 getAge(const UInt32& Index) const;
        const Vec3f& getVelocity(const UInt32& Index) const;
        const Vec3f& getSecVelocity(const UInt32& Index) const;
        Vec3f getVelocityChange(const UInt32& Index) const;
        const Vec3f& getAcceleration(const UInt32& Index) const;
        UInt32 getAttribute(const UInt32& Index, const std::string& AttributeKey) const;
        UInt32 getID(const UInt32& Index) const;
        Int64 getIndex(UInt32 ParticleID) const;
        const std::map<std::string, OSG::UInt32>& getAttributes(const UInt32& Index) const;
    
        void setPosition(const Pnt3f& Pos, const UInt32& Index);
        void setSecPosition(const Pnt3f& SecPosition, const UInt32& Index);
        void setNormal(const Vec3f& Normal, const UInt32& Index);
        void setColor(const Color4f& Color, const UInt32& Index);
        void setSize(const Vec3f& Size, const UInt32& Index);
        void setLifespan(const Time& Lifespan, const UInt32& Index);
        void setAge(const Time& Age, const UInt32& Index);
        void setVelocity(const Vec3f& Velocity, const UInt32& Index);
        void setSecVelocity(const Vec3f& SecVelocity, const UInt32& Index);
        void setAcceleration(const Vec3f& Acceleration, const UInt32& Index);
        void setAttribute(const std::string& AttributeKey, UInt32 AttributeValue, const UInt32& Index);
        void setAttributes(const std::map<std::string, OSG::UInt32>& Attributes, const UInt32& Index);
    
        bool addParticle(const Pnt3f& Position,
                         const Pnt3f& SecPosition,
                         const Vec3f& Normal,
                         const Color4f& Color,
                         const Vec3f& Size,
                         Real32 Lifespan,
                         Real32 Age,
                         const Vec3f& Velocity,
                         const Vec3f& SecVelocity,
                         const Vec3f& Acceleration,
                         const std::map<std::string, OSG::UInt32>& Attributes);
    
        bool addWorldSpaceParticle(const Pnt3f& Position,
                         const Pnt3f& SecPosition,
                         const Vec3f& Normal,
                         const Color4f& Color,
                         const Vec3f& Size,
                         Real32 Lifespan,
                         Real32 Age,
                         const Vec3f& Velocity,
                         const Vec3f& SecVelocity,
                         const Vec3f& Acceleration,
                         const std::map<std::string, OSG::UInt32>& Attributes);
    
        bool addParticle(const Pnt3f& Position,
                         const Vec3f& Normal,
                         const Color4f& Color,
                         const Vec3f& Size,
                         Real32 Lifespan,
                         const Vec3f& Velocity,
                         const Vec3f& Acceleration);
    
        bool addWorldSpaceParticle(const Pnt3f& Position,
                         const Vec3f& Normal,
                         const Color4f& Color,
                         const Vec3f& Size,
                         Real32 Lifespan,
                         const Vec3f& Velocity,
                         const Vec3f& Acceleration);
    
        bool killParticle(UInt32 Index, bool KillNextUpdate = false);
        bool killParticleByID(UInt32 ID, bool KillNextUpdate = false);
    
        void detachUpdateProducer(void);
        
        std::vector<UInt32> intersect(const Line& Ray, Real32 MinDistFromRay, Real32 MinDistFromRayOrigin, bool sort = false, NodeRefPtr Beacon = NullFC) const;
        std::vector<UInt32> intersect(const Pnt3f& p1, const Pnt3f& p2, Real32 IntersectionDistance, NodeRefPtr Beacon = NullFC) const;
        std::vector<UInt32> intersect(const Volume& Vol, Real32 IntersectionDistance, NodeRefPtr Beacon = NullFC) const;
        std::vector<UInt32> intersect(const NodeRefPtr CollisionNode, bool sort = false, NodeRefPtr Beacon = NullFC) const;
        
      protected:
            ParticleSystem(void);
            ParticleSystem(const ParticleSystem &source);
    
            virtual ~ParticleSystem(void);
    };
    %extend ParticleSystem
    {
        void attachUpdateProducer(FieldContainerRefPtr producer)
        {
            ($self)->attachUpdateProducer(producer);
        }
    };

    /******************************************************/
    /*                 ComponentRefPtr                       */
    /******************************************************/
    class ComponentRefPtr : public AttachmentContainerRefPtr
    {
      public:
         ComponentRefPtr(void);
         ComponentRefPtr(const ComponentRefPtr               &source);
         /*ComponentRefPtr(const NullFieldContainerRefPtr &source);*/


        ~ComponentRefPtr(void); 
        Component *operator->(void);
    };
    %extend ComponentRefPtr
    {
        static ComponentRefPtr dcast(const FieldContainerRefPtr oIn)
        {
            return OSG::dynamic_pointer_cast<OSG::Component>(oIn);
        }
    };

    /******************************************************/
    /*                 Component                       */
    /******************************************************/
    class Component : public AttachmentContainer
    {
      public:
        //virtual void draw(const GraphicsRefPtr Graphics) const;
    
        virtual void getBounds(Pnt2f& TopLeft, Pnt2f& BottomRight) const;
        virtual void getClipBounds(Pnt2f& TopLeft, Pnt2f& BottomRight) const;
        virtual void getInsideBorderBounds(Pnt2f& TopLeft, Pnt2f& BottomRight) const;
        virtual void getBoundsRenderingSurfaceSpace(Pnt2f& TopLeft, Pnt2f& BottomRight) const;
        virtual void updateContainerLayout(void);
        virtual void updateClipBounds(void);
        virtual Vec2f getRequestedSize(void) const;
        virtual Vec2f getContentRequestedSize(void) const;
        virtual Vec2f getBorderingLength(void) const;
    
        void setMouseContained(bool Value);
        bool getMouseContained(void);
    
        virtual bool takeFocus(bool Temporary = false);
        
        virtual bool isContained(const Pnt2f& p, bool TestAgainstClipBounds = true) const;
    
        virtual Real32 getBaseline(const Real32& x, const Real32& y) const;
    
        virtual Pnt2f getToolTipLocation(Pnt2f MousePosition);
        //virtual ToolTipRefPtr createToolTip(void);
        
        virtual Vec2f getPreferredScrollableViewportSize(void);
    
        virtual Int32 getScrollableBlockIncrement(const Pnt2f& VisibleRectTopLeft, const Pnt2f& VisibleRectBottomRight, const UInt32& orientation, const Int32& direction);
    
        virtual bool getScrollableTracksViewportHeight(void);
    
        virtual bool getScrollableTracksViewportWidth(void);
    
        virtual Int32 getScrollableUnitIncrement(const Pnt2f& VisibleRectTopLeft, const Pnt2f& VisibleRectBottomRight, const UInt32& orientation, const Int32& direction);
    
        virtual void scrollToPoint(const Pnt2f& PointInComponent);
    
        //static const OSG::BitVector BordersFieldMask;
        //virtual void setBorders(BorderRefPtr TheBorder);
    
        //static const OSG::BitVector BackgroundsFieldMask;
        //virtual void setBackgrounds(LayerRefPtr TheBackground);
        
        //static const OSG::BitVector ForegroundsFieldMask;
        //virtual void setForegrounds(LayerRefPtr TheForeground);
    
        virtual Pnt2f getParentToLocal(const Pnt2f& Location);
    
        virtual Pnt2f getLocalToParent(const Pnt2f& Location);
    
      protected:
            Component(void);
            Component(const Component &source);
    
            virtual ~Component(void);
    };
    
    /******************************************************/
    /*                 SoundRefPtr                       */
    /******************************************************/
    class SoundRefPtr : public AttachmentContainerRefPtr
    {
      public:
         SoundRefPtr(void);
         SoundRefPtr(const SoundRefPtr               &source);
         /*SoundRefPtr(const NullFieldContainerRefPtr &source);*/


        ~SoundRefPtr(void); 
        Sound *operator->(void);
    };
    %extend SoundRefPtr
    {
        static SoundRefPtr dcast(const FieldContainerRefPtr oIn)
        {
            return OSG::dynamic_pointer_cast<OSG::Sound>(oIn);
        }
    };
    
    /******************************************************/
    /*                 Sound                              */
    /******************************************************/
    class Sound : public AttachmentContainer
    {
      public:
    
        virtual UInt32 play(void) = 0;
        virtual Real32 getLength(void) const = 0;
        
        //Channel Methods
        virtual UInt32 getNumChannels(void) const = 0;
        virtual UInt32 getNumPlayingChannels(void) const = 0;
        virtual bool isPlaying(UInt32 ChannelID) const = 0;
        virtual bool isValid(UInt32 ChannelID) const = 0;
        virtual void stop(UInt32 ChannelID) = 0;
    
        virtual void pause(UInt32 ChannelID) = 0;
        virtual void unpause(UInt32 ChannelID) = 0;
        virtual void pauseToggle(UInt32 ChannelID) = 0;
        virtual bool isPaused(UInt32 ChannelID) const = 0;
    
        virtual void seek(Real32 pos, UInt32 ChannelID) = 0;
        virtual Real32 getTime(UInt32 ChannelID) const = 0;
    
        virtual void setChannelPosition(const Pnt3f &pos, UInt32 ChannelID) = 0;
        virtual Pnt3f getChannelPosition(UInt32 ChannelID) const = 0;
    
        virtual void setChannelVelocity(const Vec3f &vec, UInt32 ChannelID) = 0;
        virtual Vec3f getChannelVelocity(UInt32 ChannelID) const = 0;
    
        virtual void setChannelVolume(Real32 volume, UInt32 ChannelID) = 0;
        virtual Real32 getChannelVolume(UInt32 ChannelID) const = 0;
        virtual bool getMute(UInt32 ChannelID) const = 0;
        virtual void mute(bool shouldMute, UInt32 ChannelID) = 0;
    
        
        virtual void setAllChannelsVolume(Real32 volume) = 0;
        virtual void stopAllChannels(void) = 0;
        virtual void setAllChannelPaused(bool paused) = 0;
        virtual void setAllChannelMute(bool shouldMute) = 0;
        
        static  SoundRefPtr      create(void); 
      private:
        Sound(void);
        Sound(const Sound &source);

        virtual ~Sound(void);
    
    };
    
    /******************************************************/
    /*                 SoundManager                       */
    /******************************************************/
    class SoundManager
    {
      public:
        static SoundManager* the(void);
    
        //create a new sound object by its integer id
        virtual SoundRefPtr createSound(void) const = 0;
    
        virtual void setCamera(CameraRefPtr TheCamera);
        virtual CameraRefPtr getCamera(void) const;
    
        void detachUpdateProducer(void);
    
      protected:
        SoundManager(void);
        SoundManager(const SoundManager &source);
        virtual ~SoundManager(void); 
    };
    %extend SoundManager
    {
        void attachUpdateProducer(FieldContainerRefPtr producer)
        {
            ($self)->attachUpdateProducer(producer);
        }
    };
    
    /******************************************************/
    /*                 SoundGroup                       */
    /******************************************************/
    class SoundGroup : public AttachmentContainer
    {
        public:

            void stop(void);
            void pause(void);
            void unpause(void);
            void setVolume(Real32 volume);
            Real32 getVolume(void) const;
            void mute(bool muted);

            UInt32 getNumSounds(void) const;
            UInt32 getNumPlayingSounds(void) const;
            UInt32 getNumPlayingChannels(void) const;
        protected:
            SoundGroup(void);
            SoundGroup(const SoundGroup &source);
            virtual ~SoundGroup(void); 
    };
    
    /******************************************************/
    /*                 SoundGroupRefPtr                       */
    /******************************************************/
    class SoundGroupRefPtr : public AttachmentContainerRefPtr
    {
      public:
         SoundGroupRefPtr(void);
         SoundGroupRefPtr(const SoundGroupRefPtr               &source);
         /*SoundGroupRefPtr(const NullFieldContainerRefPtr &source);*/


        ~SoundGroupRefPtr(void); 
        SoundGroup *operator->(void);
    };
    %extend SoundGroupRefPtr
    {
        static SoundGroupRefPtr dcast(const FieldContainerRefPtr oIn)
        {
            return OSG::dynamic_pointer_cast<OSG::SoundGroup>(oIn);
        }
    };

    /******************************************************/
    /*                 AnimationRefPtr                       */
    /******************************************************/
    class AnimationRefPtr : public AttachmentContainerRefPtr
    {
      public:
         AnimationRefPtr(void);
         AnimationRefPtr(const AnimationRefPtr               &source);
         /*AnimationRefPtr(const NullFieldContainerRefPtr &source);*/


        ~AnimationRefPtr(void); 
        Animation *operator->(void);
    };
    %extend AnimationRefPtr
    {
        static AnimationRefPtr dcast(const FieldContainerRefPtr oIn)
        {
            return OSG::dynamic_pointer_cast<OSG::Animation>(oIn);
        }
    };
    
    /******************************************************/
    /*                 Animation                       */
    /******************************************************/
    class Animation : public AttachmentContainer
    {
      public:
        
        //virtual bool update(const AnimationAdvancerRefPtr& advancer);
    
        virtual Real32 getLength(void) const;
        virtual Real32 getCycleLength(void) const = 0;
        virtual void start(const Time& StartTime=0.0f);
        virtual void seek(const Time& SeekTime);
        virtual void pause(bool ShouldPause);
        virtual bool isPaused(void) const;
        virtual bool isPlaying(void) const;
        virtual void stop(bool DisconnectFromEventProducer = true);
        
        void detachUpdateProducer(void);
      protected:
        Animation(void);
        Animation(const Animation &source);
        virtual ~Animation(void); 
    };
    %extend Animation
    {
        void attachUpdateProducer(FieldContainerRefPtr producer)
        {
            ($self)->attachUpdateProducer(producer);
        }
    };

    
    /****************************************************/
    /*                VideoWrapper                      */
    /****************************************************/
    class VideoWrapper : public AttachmentContainer
    {
      public:
        //virtual bool open(const std::string& ThePath, Window* const TheWindow) = 0;
    
        virtual bool seek(Real64 SeekPos) = 0;
        virtual bool jump(Real64 Amount) = 0;
        virtual bool setRate(Real64 Rate) = 0;
        virtual Real64 getRate(void) const = 0;
        virtual bool play(void) = 0;
        virtual bool pause(void) = 0;
        virtual bool unpause(void) = 0;
        virtual bool pauseToggle(void) = 0;
        virtual bool stop(void) = 0;
        virtual bool close(void) = 0;
        virtual bool isPlaying(void) const = 0;
        virtual bool isPaused(void) const = 0;
        virtual bool isInitialized(void) const = 0;
        virtual bool isStopped(void) const = 0;
        
        virtual bool canSeekForward(void) const = 0;
        virtual bool canSeekBackward(void) const = 0;
        virtual Real64 getPosition(void) const = 0;
        virtual Real64 getDuration(void) const = 0;
        virtual UInt32 getWidth(void) const = 0;
        virtual UInt32 getHeight(void) const = 0;
    
        virtual bool hasAudio(void) const = 0;
        virtual void enableAudio(void) = 0;
        virtual void disableAudio(void) = 0;
        virtual bool isAudioEnabled(void) const = 0;
    
        virtual Real32 getAudioVolume(void) const = 0;
        virtual void setAudioVolume(Real32 volume) = 0;
    
        virtual bool updateImage(void) = 0;
    
        //void attachUpdateProducer(ReflexiveContainer* const producer);
        void detachUpdateProducer(void);
      protected:
        VideoWrapper(void);
        VideoWrapper(const VideoWrapper &source);
        virtual ~VideoWrapper(void); 
    };
    %extend VideoWrapper
    {
        bool open(const std::string& ThePath, FieldContainerRefPtr TheWindow)
        {
            return ($self)->open(ThePath, OSG::dynamic_pointer_cast<OSG::Window>(TheWindow));
        }
        void attachUpdateProducer(FieldContainerRefPtr producer)
        {
            ($self)->attachUpdateProducer(producer);
        }
    };
    

    /******************************************************/
    /*                 VideoWrapperRefPtr                       */
    /******************************************************/
    class VideoWrapperRefPtr : public AttachmentContainerRefPtr
    {
      public:
         VideoWrapperRefPtr(void);
         VideoWrapperRefPtr(const VideoWrapperRefPtr               &source);
         //VideoWrapperRefPtr(const NullFieldContainerRefPtr &source);


        ~VideoWrapperRefPtr(void); 
        VideoWrapper *operator->(void);
    };
    %extend VideoWrapperRefPtr
    {
        static VideoWrapperRefPtr dcast(const FieldContainerRefPtr oIn)
        {
            return OSG::dynamic_pointer_cast<OSG::VideoWrapper>(oIn);
        }
    };
    
    class VideoManager
    {
    public:
        //virtual void init(int   argc, char *argv[]) = 0;
        virtual void init(void);
        virtual void exit(void) = 0;
    
        virtual VideoWrapperRefPtr createVideoWrapper(void) const = 0;
    
    private:
    protected:
    };

    typedef VideoManager* VideoManagerPtr;
    VideoManagerPtr getDefaultVideoManager(void);
    
    /******************************************************/
    /*               Distribution1D                       */
    /******************************************************/
    class Distribution1D : public AttachmentContainer
    {
      public:
        
        virtual Real32 generate(void) const = 0;
      protected:
        Distribution1D(void);
        Distribution1D(const Distribution1D &source);
        virtual ~Distribution1D(void); 
    };

    /******************************************************/
    /*               Distribution1DRefPtr                    */
    /******************************************************/
    class Distribution1DRefPtr : public AttachmentContainerRefPtr
    {
      public:
         Distribution1DRefPtr(void);
         Distribution1DRefPtr(const Distribution1DRefPtr               &source);
         /*Distribution1DRefPtr(const NullFieldContainerRefPtr &source);*/


        ~Distribution1DRefPtr(void); 
        Distribution1D *operator->(void);
    };
    %extend Distribution1DRefPtr
    {
        static Distribution1DRefPtr dcast(const FieldContainerRefPtr oIn)
        {
            return OSG::dynamic_pointer_cast<OSG::Distribution1D>(oIn);
        }
    };
    
    
    /******************************************************/
    /*               Distribution2D                       */
    /******************************************************/
    class Distribution2D : public AttachmentContainer
    {
      public:
        
        virtual Vec2f generate(void) const = 0;
      protected:
        Distribution2D(void);
        Distribution2D(const Distribution2D &source);
        virtual ~Distribution2D(void); 
    };

    /******************************************************/
    /*               Distribution2DRefPtr                    */
    /******************************************************/
    class Distribution2DRefPtr : public AttachmentContainerRefPtr
    {
      public:
         Distribution2DRefPtr(void);
         Distribution2DRefPtr(const Distribution2DRefPtr               &source);
         /*Distribution2DRefPtr(const NullFieldContainerRefPtr &source);*/


        ~Distribution2DRefPtr(void); 
        Distribution2D *operator->(void);
    };
    %extend Distribution2DRefPtr
    {
        static Distribution2DRefPtr dcast(const FieldContainerRefPtr oIn)
        {
            return OSG::dynamic_pointer_cast<OSG::Distribution2D>(oIn);
        }
    };
    
    /******************************************************/
    /*               Distribution3D                       */
    /******************************************************/
    class Distribution3D : public AttachmentContainer
    {
      public:
        
        virtual Vec3f generate(void) const = 0;
      protected:
        Distribution3D(void);
        Distribution3D(const Distribution3D &source);
        virtual ~Distribution3D(void); 
    };

    /******************************************************/
    /*               Distribution3DRefPtr                    */
    /******************************************************/
    class Distribution3DRefPtr : public AttachmentContainerRefPtr
    {
      public:
         Distribution3DRefPtr(void);
         Distribution3DRefPtr(const Distribution3DRefPtr               &source);
         /*Distribution3DRefPtr(const NullFieldContainerRefPtr &source);*/


        ~Distribution3DRefPtr(void); 
        Distribution3D *operator->(void);
    };
    %extend Distribution3DRefPtr
    {
        static Distribution3DRefPtr dcast(const FieldContainerRefPtr oIn)
        {
            return OSG::dynamic_pointer_cast<OSG::Distribution3D>(oIn);
        }
    };

    /******************************************************/
    /*               CgFXMaterialRefPtr                    */
    /******************************************************/
    /* class CgFXMaterial : public AttachmentContainer
    {
      public:
	bool setActiveTechnique(std::string techniqueName);
	std::vector<std::string> getAvailableTechniques();
      protected:
        CgFXMaterial(void);
        CgFXMaterial(const CgFXMaterial &source);
        virtual ~CgFXMaterial(void); 
    };
    
    class CgFXMaterialRefPtr : public AttachmentContainerRefPtr
    {
      public:
         CgFXMaterialRefPtr(void);
         CgFXMaterialRefPtr(const CgFXMaterialRefPtr               &source);


        ~CgFXMaterialRefPtr(void); 
        CgFXMaterial *operator->(void);
    };
    %extend CgFXMaterialRefPtr
    {
        static CgFXMaterialRefPtr dcast(const FieldContainerRefPtr oIn)
        {
            return OSG::dynamic_pointer_cast<OSG::CgFXMaterial>(oIn);
        }
    }; */
}

