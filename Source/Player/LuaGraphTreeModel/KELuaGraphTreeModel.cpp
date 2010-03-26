/*---------------------------------------------------------------------------*\
 *                             Kabala Engine                                 *
 *                                                                           *
 *                                                                           *
 *   contact: djkabala@gmail.com                                             *
 *                                                                           *
\*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*\
 *                                License                                    *
 *                                                                           *
 * This library is free software; you can redistribute it and/or modify it   *
 * under the terms of the GNU General Public License as published            *
 * by the Free Software Foundation, version 3.                               *
 *                                                                           *
 * This library is distributed in the hope that it will be useful, but       *
 * WITHOUT ANY WARRANTY; without even the implied warranty of                *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU         *
 * Library General Public License for more details.                          *
 *                                                                           *
 * You should have received a copy of the GNU General Public                 *
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

#include "KELuaGraphTreeModel.h"

#include <boost/filesystem/operations.hpp>
#include <OpenSG/UserInterface/OSGTreePath.h>
#include "boost/filesystem.hpp"


OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::LuaGraphTreeModel
A UI LuaGraphTreeModel. 	
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void LuaGraphTreeModel::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

bool  LuaGraphTreeModel::isValidFile(const Path& path) const
{
	//Path path = boost::any_cast<Path>(boostanypath);
	
	if( boost::filesystem::exists(path) && ( boost::filesystem::is_directory(path) || (boost::filesystem::is_regular_file(path) && boost::filesystem::extension(path)==".lua")) )
	{
		return true;
	}
	return false;
}




boost::any LuaGraphTreeModel::getChild(const boost::any& parent, const UInt32& index) const
{
    try
    {
		Path ThePath = boost::any_cast<Path>(parent);

        if(!ThePath.empty() &&
			boost::filesystem::exists(ThePath))
        {
			boost::filesystem::directory_iterator end_iter;
			UInt32 Count(0);
			for ( boost::filesystem::directory_iterator dir_itr(ThePath); dir_itr != end_iter; ++dir_itr )
			{
				if( isValidFile(dir_itr->path()) )
				{
						if(Count == index)
						{
							return boost::any(dir_itr->path());
						}
						++Count;
				}
			}
        }
        return boost::any();
    }
    catch(boost::bad_any_cast &)
    {
        return boost::any();
    }
}

boost::any LuaGraphTreeModel::getParent(const boost::any& node) const
{
    try
    {
		Path ThePath = boost::any_cast<Path>(node);

        if((!ThePath.empty() || 
            ThePath == getInternalRoot() ||
            boost::filesystem::equivalent(ThePath, getInternalRoot())) &&
           (boost::filesystem::exists(ThePath) && boost::filesystem::exists(getInternalRoot())))
        {
            return boost::any(ThePath.parent_path());
        }

    }
    catch(boost::bad_any_cast &)
    {
    }
    return boost::any();
}

UInt32 LuaGraphTreeModel::getChildCount(const boost::any& parent) const
{
    try
    {
		Path ThePath = boost::any_cast<Path>(parent);

		UInt32 Count(0);
        if(!ThePath.empty() &&
			boost::filesystem::exists(ThePath))
        {
			boost::filesystem::directory_iterator end_iter;
			for ( boost::filesystem::directory_iterator dir_itr( ThePath ); dir_itr != end_iter; ++dir_itr )
			{
				if(isValidFile(dir_itr->path()))
				{
					++Count;
				}
			}
        }
        return Count;
    }
    catch(boost::bad_any_cast &)
    {
        return 0;
    }
}

UInt32 LuaGraphTreeModel::getIndexOfChild(const boost::any& parent, const boost::any& child) const
{
	try
    {
		Path ParentPath = boost::any_cast<Path>(parent);
		Path ChildPath = boost::any_cast<Path>(child);

        if(!ParentPath.empty() &&
			boost::filesystem::exists(ParentPath))
        {
			boost::filesystem::directory_iterator end_iter;
			UInt32 Count(0);
			for ( boost::filesystem::directory_iterator dir_itr( ParentPath ); dir_itr != end_iter; ++dir_itr )
			{
                try
                {
				    if(ChildPath == dir_itr->path() || boost::filesystem::equivalent(dir_itr->path(), ChildPath))
				    {
					    return Count;
				    }
                }
                catch(boost::filesystem::filesystem_error &)
                {
					    return Count;
                }
				if(isValidFile(dir_itr->path()))
				{
					++Count;
				}
			}
        }
        return 0;
    }
    catch(boost::bad_any_cast &)
    {
        return 0;
    }
}

boost::any LuaGraphTreeModel::getRoot(void) const
{
    if(boost::filesystem::exists(getInternalRoot()))
    {
        return boost::any(getInternalRoot());
    }
    else
    {
        return boost::any();
    }
}

bool LuaGraphTreeModel::isLeaf(const boost::any& node) const
{
    try
    {
		Path ThePath = boost::any_cast<Path>(node);

		return !boost::filesystem::is_directory(ThePath);
    }
    catch(boost::bad_any_cast &)
    {
        return false;
    }
}

bool LuaGraphTreeModel::isEqual(const boost::any& left, const boost::any& right) const
{
    try
    {
		Path LeftPath = boost::any_cast<Path>(left);
		Path RightPath = boost::any_cast<Path>(right);

        return LeftPath == RightPath || boost::filesystem::equivalent(LeftPath, RightPath);
    }
    catch(boost::bad_any_cast &)
    {
        return false;
    }
}

void LuaGraphTreeModel::valueForPathChanged(TreePath path, const boost::any& newValue)
{
	//Do Nothing
}

void LuaGraphTreeModel::setRoot(const Path& root)
{
    beginEditCP(LuaGraphTreeModelPtr(this), InternalRootFieldMask);
        setInternalRoot(root);
    endEditCP(LuaGraphTreeModelPtr(this), InternalRootFieldMask);
}

const Path& LuaGraphTreeModel::getRootPath(void) const
{
    return getInternalRoot();
}
/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

LuaGraphTreeModel::LuaGraphTreeModel(void) :
    Inherited()
{
}

LuaGraphTreeModel::LuaGraphTreeModel(const LuaGraphTreeModel &source) :
    Inherited(source)
{
}

LuaGraphTreeModel::~LuaGraphTreeModel(void)
{
}

/*----------------------------- class specific ----------------------------*/

void LuaGraphTreeModel::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void LuaGraphTreeModel::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump LuaGraphTreeModel NI" << std::endl;
}


OSG_END_NAMESPACE

