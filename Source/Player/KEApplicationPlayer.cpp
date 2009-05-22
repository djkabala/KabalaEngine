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

#include "KEConfig.h"
#include <OpenSG/Input/OSGWindowEventProducer.h>
#include <OpenSG/Input/OSGStringUtils.h>

#include "KEApplicationPlayer.h"
#include "Project/KEProject.h"
#include "Application/KEMainApplication.h"

KE_USING_NAMESPACE

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

        enableDebug(true);
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
        MainApplication::the()->getProject()->attachFlyNavigation();
    }
}

void ApplicationPlayer::keyTyped(const KeyEvent& e)
{
    if(e.getKey() == KeyEvent::KEY_D && e.getModifiers() & KeyEvent::KEY_MODIFIER_CONTROL && e.getModifiers() & KeyEvent::KEY_MODIFIER_SHIFT)
    {
        enableDebug(!_IsDebugActive);
        return;
    }

    if(_IsDebugActive)
    {
        //Force Quit
        if(e.getKey() == KeyEvent::KEY_Q && e.getModifiers() & KeyEvent::KEY_MODIFIER_CONTROL)
        {
            MainApplication::the()->exit();
        }

        
        //Pause Active Updates
        if(e.getKey() == KeyEvent::KEY_SPACE)
        {
            MainApplication::the()->getProject()->togglePauseActiveUpdates();
        }

        //Scene Activation
        if(e.getKey() == KeyEvent::KEY_TAB && !(e.getModifiers() & KeyEvent::KEY_MODIFIER_SHIFT))
        {
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
        else if(e.getKey() == KeyEvent::KEY_TAB && e.getModifiers() & KeyEvent::KEY_MODIFIER_SHIFT)
        {
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
        else if(isNumericKey(e.getKey()) && e.getModifiers() & KeyEvent::KEY_MODIFIER_CONTROL && e.getModifiers() & KeyEvent::KEY_MODIFIER_SHIFT)
        {
            //Switch To scene #
            UInt32 SceneNumber(boost::lexical_cast<UInt32>(KeyEvent::getCharFromKey(e.getKey(),0)));
            if(SceneNumber < MainApplication::the()->getProject()->getScenes().size())
            {
                MFScenePtr::iterator SearchItor(MainApplication::the()->getProject()->getScenes().begin());
                SearchItor = SearchItor + SceneNumber;
                MainApplication::the()->getProject()->setActiveScene(*SearchItor);
            }
        }
    }
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
}

ApplicationPlayer::ApplicationPlayer(const ApplicationPlayer &source) :
    Inherited(source),
	_PlayerKeyListener(ApplicationPlayerPtr(this)),
    _IsDebugActive(false)
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

void ApplicationPlayer::PlayerKeyListener::keyTyped(const KeyEvent& e)
{
    _ApplicationPlayer->keyTyped(e);
}
