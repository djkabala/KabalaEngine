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

#define KE_COMPILEUSERINTERFACELIB

#include <OpenSG/OSGConfig.h>

#include "KESceneBackgroundsComboBoxModel.h"
#include <Project/Scene/KEScene.h>
#include <OpenSG/OSGSimpleAttachments.h>

OSG_USING_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::SceneBackgroundsComboBoxModel
A UI SceneBackgroundsComboBoxModel. 
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void SceneBackgroundsComboBoxModel::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

Int32 SceneBackgroundsComboBoxModel::addBackground(BackgroundPtr TheBackground)
{
    if(TheBackground != NullFC)
    {
        beginEditCP(getEditingScene(), Scene::BackgroundsFieldMask);
            getEditingScene()->getBackgrounds().push_back(TheBackground );
        endEditCP(getEditingScene(), Scene::BackgroundsFieldMask);
        produceListDataIntervalAdded(NullFC,getEditingScene()->getBackgrounds().getSize()-1,getEditingScene()->getBackgrounds().getSize()-1);
        return getEditingScene()->getBackgrounds().size()-1;
    }
    else
    {
        return -1;
    }
}

void SceneBackgroundsComboBoxModel::removeBackground( UInt32 RemoveIndex)
{
    if(RemoveIndex <= getSize())
    {
        beginEditCP(getEditingScene(), Scene::BackgroundsFieldMask);
            getEditingScene()->getBackgrounds().erase(getEditingScene()->getBackgrounds().find(getEditingScene()->getBackgrounds()[RemoveIndex]) );
        endEditCP(getEditingScene(), Scene::BackgroundsFieldMask);
        produceListDataIntervalRemoved(NullFC,RemoveIndex,RemoveIndex);
    }
}

void SceneBackgroundsComboBoxModel::renameBackground( UInt32 Index, const std::string& NewName)
{
    if(Index <= getSize())
    {
        setName(getEditingScene()->getBackgrounds()[Index], NewName);

        produceListDataContentsChanged(NullFC,Index,Index);
    }
}

::osg::UInt32 SceneBackgroundsComboBoxModel::getSize(void) const
{
	if(getEditingScene() != NullFC)
	{
		::osg::UInt32 Size(getEditingScene()->getBackgrounds().size());
		return getEditingScene()->getBackgrounds().size();
	}
	else
	{
		return 0;
	}
}

boost::any SceneBackgroundsComboBoxModel::getElementAt(::osg::UInt32 index) const
{
	if(getEditingScene() != NullFC &&
		index < getEditingScene()->getBackgrounds().size())
	{
		return boost::any(getEditingScene()->getBackgrounds()[index]);
	}
	else
	{
		return boost::any();
	}
}

Int32 SceneBackgroundsComboBoxModel::calcInitialIndex(void) const
{
	if(getEditingScene() != NullFC)
	{
		Int32 i(0);
		for(; i<getEditingScene()->getBackgrounds().size() ; ++i)
		{
			if(getEditingScene()->getBackgrounds()[i] == getEditingScene()->getInitialBackground())
			{
				return i;
			}
		}
	}

	return -1;
}

boost::any SceneBackgroundsComboBoxModel::getSelectedItem(void) const
{
	Int32 SelectedIndex(calcInitialIndex());
	if(SelectedIndex < 0)
	{
		return boost::any();
	}
	else
	{
		return getElementAt(SelectedIndex);
	}
}

Int32 SceneBackgroundsComboBoxModel::getSelectedItemIndex(void) const
{
	return calcInitialIndex();
}

void SceneBackgroundsComboBoxModel::setSelectedItem(const Int32& index)
{
	Int32 SelectedIndex(index);
	Int32 OldIndex(calcInitialIndex());
	if(SelectedIndex != OldIndex)
	{
		if(SelectedIndex >= 0 && SelectedIndex < getEditingScene()->getBackgrounds().size())
		{
			beginEditCP(getEditingScene(), Scene::InitialBackgroundFieldMask);
				getEditingScene()->setInitialBackground(getEditingScene()->getBackgrounds()[SelectedIndex]);
			endEditCP(getEditingScene(), Scene::InitialBackgroundFieldMask);
		}

		produceSelectionChanged(SceneBackgroundsComboBoxModelPtr(this), SelectedIndex, OldIndex);
	}
}

void SceneBackgroundsComboBoxModel::setSelectedItem(const boost::any& anObject)
{
	if(getEditingScene() != NullFC)
	{
        try
        {
            BackgroundPtr TheBackgroundItem = boost::any_cast<BackgroundPtr>(anObject);
		    for(::osg::UInt32 i(0) ; i<getEditingScene()->getBackgrounds().size() ; ++i)
		    {
			    if(TheBackgroundItem == getEditingScene()->getBackgrounds()[i])
			    {
				    setSelectedItem(i);
				    return;
			    }
		    }
        }
        catch(boost::bad_any_cast &)
        {
        }
	}

	setSelectedItem(-1);
}
/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

SceneBackgroundsComboBoxModel::SceneBackgroundsComboBoxModel(void) :
    Inherited()
{
}

SceneBackgroundsComboBoxModel::SceneBackgroundsComboBoxModel(const SceneBackgroundsComboBoxModel &source) :
    Inherited(source)
{
}

SceneBackgroundsComboBoxModel::~SceneBackgroundsComboBoxModel(void)
{
}

/*----------------------------- class specific ----------------------------*/

void SceneBackgroundsComboBoxModel::changed(BitVector whichField, ::osg::UInt32 origin)
{
    Inherited::changed(whichField, origin);

	if(whichField & EditingSceneFieldMask)
	{
		if(getEditingScene() != NullFC)
		{
			produceListDataIntervalAdded(SceneBackgroundsComboBoxModelPtr(this),0, getEditingScene()->getBackgrounds().size()-1);
		}
	}
}

void SceneBackgroundsComboBoxModel::dump(      ::osg::UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump SceneBackgroundsComboBoxModel NI" << std::endl;
}

