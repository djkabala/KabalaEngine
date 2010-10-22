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

#include "KELookAndFeel.h"
#include "KEMainApplication.h"

#include <OpenSG/OSGLookAndFeelManager.h>
#include <OpenSG/OSGXMLLookAndFeel.h>
#include <boost/filesystem.hpp>
#include <boost/filesystem/convenience.hpp>

OSG_USING_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class OSG::KELookAndFeel
The Main Application. 	
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

KELookAndFeel *KELookAndFeel::_Instance = NULL;

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

bool KELookAndFeel::init(void)
{
    LookAndFeelRecPtr UILookAndFeel(NULL);

    //Get the path to the UI LookAndFeel
    BoostPath LookAndFeelPath(MainApplication::the()->getSettings().get<BoostPath>("basic.data.look_and_feel.path"));

    if(!LookAndFeelPath.is_complete())
    {
        LookAndFeelPath = MainApplication::the()->getSettings().get<BoostPath>("basic.data.directory") / LookAndFeelPath;
    }

    //Check that it exists
    if(boost::filesystem::exists(LookAndFeelPath))
    {
        UILookAndFeel = XMLLookAndFeel::create(LookAndFeelPath);
        
        if(UILookAndFeel != NULL)
        {
            SLOG << "Loaded UI LookAndFeel from: " << LookAndFeelPath.string() << std::endl;
        }
    }
    else
    {
        SWARNING << "Could not load default look and feel because the file doesn't exist.  File: " << LookAndFeelPath.string() << std::endl;
    }

    if(UILookAndFeel == NULL)
    {
        UILookAndFeel = LookAndFeelManager::the()->getLookAndFeel();
    }
    LookAndFeelManager::the()->setLookAndFeel(UILookAndFeel);

    LookAndFeelManager::the()->getLookAndFeel()->init();

    return true;
}


/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

KELookAndFeel::KELookAndFeel(void)
{
}

KELookAndFeel::KELookAndFeel(const KELookAndFeel &source)
{
    assert(false && "KELookAndFeel is a singleton, copy constructor should never be reached");
}

KELookAndFeel::~KELookAndFeel(void)
{
}

/*----------------------------- class specific ----------------------------*/

