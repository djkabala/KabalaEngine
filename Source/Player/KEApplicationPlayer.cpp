/*---------------------------------------------------------------------------*\
 *                             Kabala Engine                                 *
 *                                                                           *
 *                         www.vrac.iastate.edu                              *
 *                                                                           *
 *   Authors: David Kabala (dkabala@vrac.iastate.edu)                        *
 *                                                                           *
\*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*\
 *                                License                                    *
 *                                                                           *
 * This library is free software; you can redistribute it and/or modify it   *
 * under the terms of the GNU Library General Public License as published    *
 * by the Free Software Foundation, version 3.                               *
 *                                                                           *
 * This library is distributed in the hope that it will be useful, but       *
 * WITHOUT ANY WARRANTY; without even the implied warranty of                *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU         *
 * Library General Public License for more details.                          *
 *                                                                           *
 * You should have received a copy of the GNU Library General Public         *
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

#include <stdlib.h>
#include <stdio.h>

#define KE_COMPILEKABALAENGINELIB

#include <OpenSG/OSGConfig.h>
#include <OpenSG/OSGDrawable.h>
#include <OpenSG/Input/OSGWindowEventProducer.h>
#include <OpenSG/Input/OSGStringUtils.h>

#include "KEApplicationPlayer.h"
#include "Project/KEProject.h"
#include "Application/KEMainApplication.h"

OSG_USING_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::ApplicationPlayer
The ApplicationPlayer. 
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void ApplicationPlayer::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/


void ApplicationPlayer::reset(void)
{
}

void ApplicationPlayer::attachApplication(void)
{
	Inherited::attachApplication();

	//Main Window Titlebar
	ProjectPtr TheProject(MainApplication::the()->getProject());
	std::string MainWindowTitle(TheProject->getName());
	MainApplication::the()->getMainWindowEventProducer()->setTitle(MainWindowTitle);
	MainApplication::the()->getMainWindowEventProducer()->addKeyListener(&_PlayerKeyListener);

}

void ApplicationPlayer::dettachApplication(void)
{
	MainApplication::the()->getMainWindowEventProducer()->removeKeyListener(&_PlayerKeyListener);

	Inherited::dettachApplication();
}

void ApplicationPlayer::attachInterface(void)
{
}

void ApplicationPlayer::attachListeners(void)
{
}

void ApplicationPlayer::start(void)
{
	if(MainApplication::the()->getProject() != NullFC)
	{
		MainApplication::the()->getProject()->start();

        enableDebug(false);
	}
}

void ApplicationPlayer::stop(void)
{
	if(MainApplication::the()->getProject() != NullFC)
	{
		MainApplication::the()->getProject()->stop();
	}
}

void ApplicationPlayer::enableDebug(bool EnableDebug)
{
    _IsDebugActive = EnableDebug;
    if(_IsDebugActive)
    {
        std::cout << "Debug Mode Enabled" << std::endl;
        MainApplication::the()->getProject()->attachFlyNavigation();
    }
    else
    {
        std::cout << "Debug Mode Disabled" << std::endl;
        MainApplication::the()->getProject()->dettachFlyNavigation();
    }
}

void ApplicationPlayer::keyTyped(const KeyEventPtr e)
{
    if(e->getKey() == KeyEvent::KEY_D && e->getModifiers() & KeyEvent::KEY_MODIFIER_CONTROL && e->getModifiers() & KeyEvent::KEY_MODIFIER_SHIFT)
    {
        enableDebug(!_IsDebugActive);
        return;
    }

    if(_IsDebugActive)
    {
        //Force Quit
        if(e->getKey() == KeyEvent::KEY_Q && e->getModifiers() & KeyEvent::KEY_MODIFIER_CONTROL)
        {
            MainApplication::the()->exit();
        }

        
        //Pause Active Updates
        if(e->getKey() == KeyEvent::KEY_SPACE)
        {
            MainApplication::the()->getProject()->togglePauseActiveUpdates();
        }

        //Scene Activation
        if(e->getKey() == KeyEvent::KEY_TAB && !(e->getModifiers() & KeyEvent::KEY_MODIFIER_SHIFT))
        {
            //Move to next scene
            MFScenePtr::iterator SearchItor(MainApplication::the()->getProject()->getScenes().find(MainApplication::the()->getProject()->getActiveScene()));
            if(SearchItor != MainApplication::the()->getProject()->getScenes().end())
            {
                ++SearchItor;
                if(SearchItor == MainApplication::the()->getProject()->getScenes().end())
                {
                    SearchItor = MainApplication::the()->getProject()->getScenes().begin();
                }
            }
            else
            {
                SearchItor = MainApplication::the()->getProject()->getScenes().begin();
            }
            MainApplication::the()->getProject()->setActiveScene(*SearchItor);
        }
        else if(e->getKey() == KeyEvent::KEY_TAB && e->getModifiers() & KeyEvent::KEY_MODIFIER_SHIFT)
        {
            //Move to previous scene
            MFScenePtr::iterator SearchItor(MainApplication::the()->getProject()->getScenes().find(MainApplication::the()->getProject()->getActiveScene()));
            if(SearchItor != MainApplication::the()->getProject()->getScenes().end())
            {
                if(SearchItor == MainApplication::the()->getProject()->getScenes().begin())
                {
                    SearchItor = MainApplication::the()->getProject()->getScenes().end();
                }
                if(MainApplication::the()->getProject()->getScenes().size() > 1)
                {
                    --SearchItor;
                }
            }
            else
            {
                SearchItor = MainApplication::the()->getProject()->getScenes().begin();
            }
            MainApplication::the()->getProject()->setActiveScene(*SearchItor);
        }
        else if(isNumericKey(static_cast<KeyEvent::Key>(e->getKey())) && e->getModifiers() & KeyEvent::KEY_MODIFIER_CONTROL && e->getModifiers() & KeyEvent::KEY_MODIFIER_SHIFT)
        {
            //Switch To scene #
            UInt32 SceneNumber(boost::lexical_cast<UInt32>(KeyEvent::getCharFromKey(e->getKey(),0)));
            if(SceneNumber < MainApplication::the()->getProject()->getScenes().size())
            {
                MFScenePtr::iterator SearchItor(MainApplication::the()->getProject()->getScenes().begin());
                SearchItor = SearchItor + SceneNumber;
                MainApplication::the()->getProject()->setActiveScene(*SearchItor);
            }
        }
        //Statistic Foregrounds
        else if(e->getKey() == KeyEvent::KEY_B && e->getModifiers() & KeyEvent::KEY_MODIFIER_CONTROL)  //Basic Statistics Foreground
        {
            toggleStatForeground(_DebugBasicStatForeground);
        }
        else if(e->getKey() == KeyEvent::KEY_R && e->getModifiers() & KeyEvent::KEY_MODIFIER_CONTROL)  //Basic Statistics Foreground
        {
            toggleStatForeground(_DebugRenderStatForeground);
        }
        else if(e->getKey() == KeyEvent::KEY_Y && e->getModifiers() & KeyEvent::KEY_MODIFIER_CONTROL)  //Basic Statistics Foreground
        {
            toggleStatForeground(_DebugPhysicsStatForeground);
        }
        else if(e->getKey() == KeyEvent::KEY_P && e->getModifiers() & KeyEvent::KEY_MODIFIER_CONTROL)  //Basic Statistics Foreground
        {
            toggleStatForeground(_DebugParticleSystemStatForeground);
        }
        else if(e->getKey() == KeyEvent::KEY_A && e->getModifiers() & KeyEvent::KEY_MODIFIER_CONTROL)  //Basic Statistics Foreground
        {
            toggleStatForeground(_DebugAnimationStatForeground);
        }
    }
}

void ApplicationPlayer::toggleStatForeground(StatisticsForegroundPtr TheForeground)
{
    MFForegroundPtr::iterator SearchItor(MainApplication::the()->getProject()->getActiveForegrounds().find(TheForeground));
    if( SearchItor != MainApplication::the()->getProject()->getActiveForegrounds().end())
    {
        //If the Stat foreground is present then switch it off
        beginEditCP(MainApplication::the()->getProject(), Project::InternalActiveForegroundsFieldMask);
            MainApplication::the()->getProject()->getActiveForegrounds().erase(SearchItor);
        endEditCP(MainApplication::the()->getProject(), Project::InternalActiveForegroundsFieldMask);
    }
    else
    {
        //If not present then switch all other stat foregrounds off
        hideAllStatForegrounds();
        //and switch it on
        beginEditCP(MainApplication::the()->getProject(), Project::InternalActiveForegroundsFieldMask);
            MainApplication::the()->getProject()->getActiveForegrounds().push_back(TheForeground);
        endEditCP(MainApplication::the()->getProject(), Project::InternalActiveForegroundsFieldMask);
        MainApplication::the()->getMainWindowEventProducer()->getRenderAction()->setStatistics(&TheForeground->getCollector());
    }
}

void ApplicationPlayer::hideAllStatForegrounds(void)
{
    
    MFForegroundPtr::iterator SearchItor;

    beginEditCP(MainApplication::the()->getProject(), Project::InternalActiveForegroundsFieldMask);
        //Hide Basic Stat Foreground if present
        if( (SearchItor = MainApplication::the()->getProject()->getActiveForegrounds().find(_DebugBasicStatForeground)) != MainApplication::the()->getProject()->getActiveForegrounds().end() )
        {
            MainApplication::the()->getProject()->getActiveForegrounds().erase(SearchItor);
        }
        //Hide Render Stat Foreground if present
        if( (SearchItor = MainApplication::the()->getProject()->getActiveForegrounds().find(_DebugRenderStatForeground)) != MainApplication::the()->getProject()->getActiveForegrounds().end() )
        {
            MainApplication::the()->getProject()->getActiveForegrounds().erase(SearchItor);
        }
        //Hide Physics Stat Foreground if present
        if( (SearchItor = MainApplication::the()->getProject()->getActiveForegrounds().find(_DebugPhysicsStatForeground)) != MainApplication::the()->getProject()->getActiveForegrounds().end() )
        {
            MainApplication::the()->getProject()->getActiveForegrounds().erase(SearchItor);
        }
        //Hide Particle System Stat Foreground if present
        if( (SearchItor = MainApplication::the()->getProject()->getActiveForegrounds().find(_DebugParticleSystemStatForeground)) != MainApplication::the()->getProject()->getActiveForegrounds().end() )
        {
            MainApplication::the()->getProject()->getActiveForegrounds().erase(SearchItor);
        }
        //Hide Animation Stat Foreground if present
        if( (SearchItor = MainApplication::the()->getProject()->getActiveForegrounds().find(_DebugAnimationStatForeground)) != MainApplication::the()->getProject()->getActiveForegrounds().end() )
        {
            MainApplication::the()->getProject()->getActiveForegrounds().erase(SearchItor);
        }
    endEditCP(MainApplication::the()->getProject(), Project::InternalActiveForegroundsFieldMask);
}

void ApplicationPlayer::initDebugStatForegrounds(void)
{
    //Basic Statistics
    _DebugBasicStatForeground = SimpleStatisticsForeground::create();
    beginEditCP(_DebugBasicStatForeground);
        _DebugBasicStatForeground->setSize(25);
        _DebugBasicStatForeground->setColor(Color4f(0,1,0,0.7));
        _DebugBasicStatForeground->addElement(RenderAction::statDrawTime, "Draw FPS: %r.3f");
        _DebugBasicStatForeground->addElement(RenderAction::statNGeometries, "%d Nodes drawn");
        _DebugBasicStatForeground->addElement(Drawable::statNTriangles, "%d triangles drawn");
    endEditCP(_DebugBasicStatForeground);
    addRefCP(_DebugBasicStatForeground);
    
    //Rendering Statistics
    _DebugRenderStatForeground = SimpleStatisticsForeground::create();
    beginEditCP(_DebugRenderStatForeground);
        _DebugRenderStatForeground->setSize(25);
        _DebugRenderStatForeground->setColor(Color4f(0,1,0,0.7));

        _DebugRenderStatForeground->addElement(RenderAction::statDrawTime, "Draw FPS: %r.3f");
        _DebugRenderStatForeground->addElement(RenderAction::statNGeometries, "%d Nodes drawn");
        _DebugRenderStatForeground->addElement(DrawActionBase::statTravTime, "TravTime: %.3f s");
        _DebugRenderStatForeground->addElement(RenderAction::statDrawTime, "DrawTime: %.3f s");
        _DebugRenderStatForeground->addElement(DrawActionBase::statCullTestedNodes, "%d Nodes culltested");
        _DebugRenderStatForeground->addElement(DrawActionBase::statCulledNodes, "%d Nodes culled");
        _DebugRenderStatForeground->addElement(RenderAction::statNMaterials, "%d material changes");
        _DebugRenderStatForeground->addElement(RenderAction::statNMatrices, "%d matrix changes");
        _DebugRenderStatForeground->addElement(RenderAction::statNGeometries, "%d Nodes drawn");
        _DebugRenderStatForeground->addElement(RenderAction::statNTransGeometries, "%d transparent Nodes drawn");
        _DebugRenderStatForeground->addElement(Drawable::statNTriangles, "%d triangles drawn");
        _DebugRenderStatForeground->addElement(Drawable::statNLines, "%d lines drawn");
        _DebugRenderStatForeground->addElement(Drawable::statNPoints, "%d points drawn");
        _DebugRenderStatForeground->addElement(Drawable::statNPrimitives,"%d primitive groups drawn");
        _DebugRenderStatForeground->addElement(Drawable::statNVertices, "%d vertices transformed");
        _DebugRenderStatForeground->addElement(Drawable::statNGeoBytes, "%d bytes of geometry used");
        _DebugRenderStatForeground->addElement(RenderAction::statNTextures, "%d textures used");
        _DebugRenderStatForeground->addElement(RenderAction::statNTexBytes, "%d bytes of texture used");
    endEditCP(_DebugRenderStatForeground);
    addRefCP(_DebugRenderStatForeground);
    
    //Physics Statistics
    _DebugPhysicsStatForeground = SimpleStatisticsForeground::create();
    beginEditCP(_DebugPhysicsStatForeground);
        _DebugPhysicsStatForeground->setSize(25);
        _DebugPhysicsStatForeground->setColor(Color4f(0,1,0,0.7));
        _DebugPhysicsStatForeground->addElement(RenderAction::statDrawTime, "Draw FPS: %r.3f");
    endEditCP(_DebugPhysicsStatForeground);
    addRefCP(_DebugPhysicsStatForeground);
    
    //Particle System Statistics
    _DebugParticleSystemStatForeground = SimpleStatisticsForeground::create();
    beginEditCP(_DebugParticleSystemStatForeground);
        _DebugParticleSystemStatForeground->setSize(25);
        _DebugParticleSystemStatForeground->setColor(Color4f(0,1,0,0.7));
        _DebugParticleSystemStatForeground->addElement(RenderAction::statDrawTime, "Draw FPS: %r.3f");
    endEditCP(_DebugParticleSystemStatForeground);
    addRefCP(_DebugParticleSystemStatForeground);
    
    //Animation Statistics
    _DebugAnimationStatForeground = SimpleStatisticsForeground::create();
    beginEditCP(_DebugAnimationStatForeground);
        _DebugAnimationStatForeground->setSize(25);
        _DebugAnimationStatForeground->setColor(Color4f(0,1,0,0.7));
        _DebugAnimationStatForeground->addElement(RenderAction::statDrawTime, "Draw FPS: %r.3f");
    endEditCP(_DebugAnimationStatForeground);
    addRefCP(_DebugAnimationStatForeground);
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

ApplicationPlayer::ApplicationPlayer(void) :
    Inherited(),
	_PlayerKeyListener(ApplicationPlayerPtr(this)),
    _IsDebugActive(false)
{
    initDebugStatForegrounds();
}

ApplicationPlayer::ApplicationPlayer(const ApplicationPlayer &source) :
    Inherited(source),
	_PlayerKeyListener(ApplicationPlayerPtr(this)),
    _IsDebugActive(false),
    _DebugBasicStatForeground(source._DebugBasicStatForeground),
    _DebugRenderStatForeground(source._DebugRenderStatForeground),
    _DebugPhysicsStatForeground(source._DebugPhysicsStatForeground),
    _DebugParticleSystemStatForeground(source._DebugParticleSystemStatForeground),
    _DebugAnimationStatForeground(source._DebugAnimationStatForeground)
{
}

ApplicationPlayer::~ApplicationPlayer(void)
{
}

/*----------------------------- class specific ----------------------------*/

void ApplicationPlayer::changed(BitVector whichField, ::osg::UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void ApplicationPlayer::dump(      ::osg::UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump ApplicationPlayer NI" << std::endl;
}

void ApplicationPlayer::PlayerKeyListener::keyTyped(const KeyEventPtr e)
{
    _ApplicationPlayer->keyTyped(e);
}
