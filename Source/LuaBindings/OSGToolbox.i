
%module OSGToolbox
%import  <OSGBase.i>
%import  <OSGSystem.i>
%{
#include <OpenSG/Input/OSGWindowEventProducer.h>
#include <OpenSG/Sound/OSGSound.h>
#include <OpenSG/Sound/OSGSoundManager.h>
#include <OpenSG/Animation/OSGAnimation.h>
#include <OpenSG/UserInterface/OSGComponent.h>
#include <OpenSG/ParticleSystem/OSGParticleSystem.h>


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
#include <OpenSG/OSGImage.h>S
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
%}

namespace osg {

    class WindowEventProducer;
    class Sound;
    class Animation;
    class Component;
    class ParticleSystem;
    
    /******************************************************/
    /*              WindowEventProducerPtr                             */
    /******************************************************/
    class WindowEventProducerPtr : public AttachmentContainerPtr
    {
      public:
         WindowEventProducerPtr(void);
         WindowEventProducerPtr(const WindowEventProducerPtr               &source);
         /*WindowEventProducerPtr(const NullFieldContainerPtr &source);*/


        ~WindowEventProducerPtr(void); 
        WindowEventProducer *operator->(void);
        
        static WindowEventProducerPtr dcast(const FieldContainerPtr oIn);
    };
    
    /******************************************************/
    /*                       WindowEventProducer                       */
    /******************************************************/ 
    class WindowEventProducer : public AttachmentContainerPtr
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

        enum CursorType {CURSOR_POINTER=0, 
            CURSOR_HAND=1,
            CURSOR_I_BEAM=2,
            CURSOR_WAIT=3,
            CURSOR_RESIZE_W_TO_E=4,
            CURSOR_RESIZE_N_TO_S=5,
            CURSOR_RESIZE_NW_TO_SE=6,
            CURSOR_RESIZE_SW_TO_NE=7,
            CURSOR_RESIZE_ALL=8,
            CURSOR_NONE=9};

        //virtual WindowPtr initWindow(void);

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

        ViewportPtr windowToViewport(const Pnt2f& WindowPoint, Pnt2f& ViewportPoint);

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
    /*                StringToUInt32Map                   */
    /******************************************************/
    typedef std::map<std::string, UInt32> StringToUInt32Map;

    /******************************************************/
    /*                   LuaManager                       */
    /******************************************************/

    
    /******************************************************/
    /*                 Physics Things                     */
    /******************************************************/
    /******************************************************/
    /*                 Key Bindings                       */
    /******************************************************/

    /******************************************************/
    /*                 VideoManager                       */
    /******************************************************/

    /******************************************************/
    /*                 ParticleSystemPtr                       */
    /******************************************************/
    class ParticleSystemPtr : public AttachmentContainerPtr
    {
      public:
         ParticleSystemPtr(void);
         ParticleSystemPtr(const ParticleSystemPtr               &source);
         /*ParticleSystemPtr(const NullFieldContainerPtr &source);*/


        ~ParticleSystemPtr(void); 
        ParticleSystem *operator->(void);
        
        static ParticleSystemPtr dcast(const FieldContainerPtr oIn);
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
        const Vec3f getPositionChange(const UInt32& Index) const;
        const Vec3f& getNormal(const UInt32& Index) const;
        const Color4f& getColor(const UInt32& Index) const;
        const Vec3f& getSize(const UInt32& Index) const;
        Real32 getLifespan(const UInt32& Index) const;
        Real32 getAge(const UInt32& Index) const;
        const Vec3f& getVelocity(const UInt32& Index) const;
        const Vec3f& getSecVelocity(const UInt32& Index) const;
        const Vec3f getVelocityChange(const UInt32& Index) const;
        const Vec3f& getAcceleration(const UInt32& Index) const;
        UInt32 getAttribute(const UInt32& Index, const std::string& AttributeKey) const;
        const StringToUInt32Map& getAttributes(const UInt32& Index) const;
    
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
        //void setAttribute(const std::string& AttributeKey, UInt32 AttributeValue, const UInt32& Index);
        void setAttributes(const StringToUInt32Map& Attributes, const UInt32& Index);
    
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
                         const StringToUInt32Map& Attributes);
    
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
                         const StringToUInt32Map& Attributes);
    
    
        bool killParticle(UInt32 Index);
    
        bool attachUpdateListener(WindowEventProducerPtr UpdateProducer);
        void dettachUpdateListener(WindowEventProducerPtr UpdateProducer);
      protected:
            ParticleSystem(void);
            ParticleSystem(const ParticleSystem &source);
    
            virtual ~ParticleSystem(void);
    };

    /******************************************************/
    /*                 ComponentPtr                       */
    /******************************************************/
    class ComponentPtr : public AttachmentContainerPtr
    {
      public:
         ComponentPtr(void);
         ComponentPtr(const ComponentPtr               &source);
         /*ComponentPtr(const NullFieldContainerPtr &source);*/


        ~ComponentPtr(void); 
        Component *operator->(void);
        
        static ComponentPtr dcast(const FieldContainerPtr oIn);
    };

    /******************************************************/
    /*                 Component                       */
    /******************************************************/
    class Component : public AttachmentContainer
    {
      public:
        //virtual void draw(const GraphicsPtr Graphics) const;
    
        virtual void getBounds(Pnt2f& TopLeft, Pnt2f& BottomRight) const;
        virtual void getClipBounds(Pnt2f& TopLeft, Pnt2f& BottomRight) const;
        virtual void getInsideBorderBounds(Pnt2f& TopLeft, Pnt2f& BottomRight) const;
        virtual void getBoundsRenderingSurfaceSpace(Pnt2f& TopLeft, Pnt2f& BottomRight) const;
        virtual void updateContainerLayout(void);
        virtual void updateClipBounds(void);
        virtual Vec2f getRequestedSize(void) const;
        virtual Vec2f getContentRequestedSize(void) const;
        virtual Vec2f getBorderingLength(void) const;
        
        //Mouse Events
        //virtual void mouseClicked(const MouseEventPtr e);
        //virtual void mouseEntered(const MouseEventPtr e);
        ///virtual void mouseExited(const MouseEventPtr e);
        //virtual void mousePressed(const MouseEventPtr e);
        //virtual void mouseReleased(const MouseEventPtr e);
    
        //Mouse Motion Events
        //virtual void mouseMoved(const MouseEventPtr e);
        //virtual void mouseDragged(const MouseEventPtr e);
    
        //Mouse Wheel Events
        //virtual void mouseWheelMoved(const MouseWheelEventPtr e);
    
        //Key Events
        //virtual void keyPressed(const KeyEventPtr e);
        //virtual void keyReleased(const KeyEventPtr e);
        //virtual void keyTyped(const KeyEventPtr e);
    
        //Focus Events
        //virtual void focusGained(const FocusEventPtr e);
        //virtual void focusLost(const FocusEventPtr e);
    
        void setMouseContained(bool Value);
        bool getMouseContained(void);
    
        virtual bool takeFocus(bool Temporary = false);
        
        virtual bool isContained(const Pnt2f& p, bool TestAgainstClipBounds = true) const;
    
        virtual Real32 getBaseline(const Real32& x, const Real32& y) const;
    
        virtual Pnt2f getToolTipLocation(Pnt2f MousePosition);
        //virtual ToolTipPtr createToolTip(void);
        
        virtual Vec2f getPreferredScrollableViewportSize(void);
    
        virtual Int32 getScrollableBlockIncrement(const Pnt2f& VisibleRectTopLeft, const Pnt2f& VisibleRectBottomRight, const UInt32& orientation, const Int32& direction);
    
        virtual bool getScrollableTracksViewportHeight(void);
    
        virtual bool getScrollableTracksViewportWidth(void);
    
        virtual Int32 getScrollableUnitIncrement(const Pnt2f& VisibleRectTopLeft, const Pnt2f& VisibleRectBottomRight, const UInt32& orientation, const Int32& direction);
    
        virtual void scrollToPoint(const Pnt2f& PointInComponent);
    
        //static const OSG::BitVector BordersFieldMask;
        //virtual void setBorders(BorderPtr TheBorder);
    
        //static const OSG::BitVector BackgroundsFieldMask;
        //virtual void setBackgrounds(LayerPtr TheBackground);
        
        //static const OSG::BitVector ForegroundsFieldMask;
        //virtual void setForegrounds(LayerPtr TheForeground);
    
        virtual Pnt2f getParentToLocal(const Pnt2f& Location);
    
        virtual Pnt2f getLocalToParent(const Pnt2f& Location);
    
      protected:
            Component(void);
            Component(const Component &source);
    
            virtual ~Component(void);
    };

    /******************************************************/
    /*                 VideoWrapperPtr                       */
    /******************************************************/
    /*class VideoWrapperPtr : public AttachmentContainerPtr
    {
      public:
         VideoWrapperPtr(void);
         VideoWrapperPtr(const VideoWrapperPtr               &source);
         //VideoWrapperPtr(const NullFieldContainerPtr &source);


        ~VideoWrapperPtr(void); 
        VideoWrapper *operator->(void);
        
        static VideoWrapperPtr dcast(const FieldContainerPtr oIn);
    };*/
    
    /******************************************************/
    /*                 SoundPtr                       */
    /******************************************************/
    class SoundPtr : public AttachmentContainerPtr
    {
      public:
         SoundPtr(void);
         SoundPtr(const SoundPtr               &source);
         /*SoundPtr(const NullFieldContainerPtr &source);*/


        ~SoundPtr(void); 
        Sound *operator->(void);
        
        static SoundPtr dcast(const FieldContainerPtr oIn);
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
        
        static  SoundPtr      create(void); 
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
        virtual SoundPtr createSound(void) const = 0;
    
        virtual void setCamera(CameraPtr TheCamera);
        virtual CameraPtr getCamera(void) const;
    
        void attachUpdateProducer(WindowEventProducerPtr TheProducer);
        void detachUpdateProducer(WindowEventProducerPtr TheProducer);
    
      protected:
        SoundManager(void);
        SoundManager(const SoundManager &source);
        virtual ~SoundManager(void); 
    };
    
    /******************************************************/
    /*                 AnimationPtr                       */
    /******************************************************/
    class AnimationPtr : public AttachmentContainerPtr
    {
      public:
         AnimationPtr(void);
         AnimationPtr(const AnimationPtr               &source);
         /*AnimationPtr(const NullFieldContainerPtr &source);*/


        ~AnimationPtr(void); 
        Animation *operator->(void);
        
        static AnimationPtr dcast(const FieldContainerPtr oIn);
    };
    
    /******************************************************/
    /*                 AnimationPtr                       */
    /******************************************************/
    class Animation : public AttachmentContainer
    {
      public:
        
        //virtual bool update(const AnimationAdvancerPtr& advancer);
    
        virtual Real32 getLength(void) const = 0;
      protected:
      protected:
        Animation(void);
        Animation(const Animation &source);
        virtual ~Animation(void); 
    };
    
}

