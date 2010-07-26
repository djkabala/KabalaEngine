/*---------------------------------------------------------------------------*\
 *                             Kabala Engine                                 *
 *                                                                           *
 *               Copyright (C) 2009-2010 by David Kabala                     *
 *                                                                           *
 *   authors:  David Kabala (djkabala@gmail.com)                             *
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

#include <cstdlib>
#include <cstdio>

#define KE_COMPILEKABALAENGINELIB

#include <OpenSG/OSGConfig.h>

#include "KELuaGraphTreeModel.h"
#include <boost/filesystem.hpp>
#include <boost/filesystem/operations.hpp>
#include <OpenSG/OSGTreePath.h>

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGLuaGraphTreeModelBase.cpp file.
// To modify it, please change the .fcd file (OSGLuaGraphTreeModel.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void LuaGraphTreeModel::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

bool LuaGraphTreeModel::isValidFile(const BoostPath& path) const
{
    //BoostPath path = boost::any_cast<BoostPath>(boostanypath);

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
        BoostPath ThePath = boost::any_cast<BoostPath>(parent);

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
        BoostPath ThePath = boost::any_cast<BoostPath>(node);

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
        BoostPath ThePath = boost::any_cast<BoostPath>(parent);

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
        BoostPath ParentPath = boost::any_cast<BoostPath>(parent);
        BoostPath ChildPath = boost::any_cast<BoostPath>(child);

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
        SWARNING << "Root doesn't exist." << std::endl;
        return boost::any(getInternalRoot());
        //return boost::any();
    }
}

bool LuaGraphTreeModel::isLeaf(const boost::any& node) const
{
    try
    {
        BoostPath ThePath = boost::any_cast<BoostPath>(node);

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
        BoostPath LeftPath = boost::any_cast<BoostPath>(left);
        BoostPath RightPath = boost::any_cast<BoostPath>(right);

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

void LuaGraphTreeModel::setRoot(const BoostPath& root)
{
    setInternalRoot(root);
}

const BoostPath& LuaGraphTreeModel::getRootPath(void) const
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

void LuaGraphTreeModel::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void LuaGraphTreeModel::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump LuaGraphTreeModel NI" << std::endl;
}

OSG_END_NAMESPACE
