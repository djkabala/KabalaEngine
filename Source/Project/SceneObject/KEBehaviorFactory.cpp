/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2006 by the OpenSG Forum                 *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 *   contact:  David Kabala (djkabala@gmail.com)                             *
 *                                                                           *
\*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*\
 *                                License                                    *
 *                                                                           *
 * This library is free software; you can redistribute it and/or modify it   *
 * under the terms of the GNU Library General Public License as published    *
 * by the Free Software Foundation, version 2.                               *
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

#include "OSGEventProducerFactory.h"

#include "OSGFactoryController.h"
#include "OSGLog.h"
#include "OSGTypeBase.h"
#include "KEBehaviorFactory.h"
#include "KEBehavior.h"
#include "KEBehaviorType.h"

#include "OSGSingletonHolder.ins"

#include <algorithm>
#include <functional>

OSG_BEGIN_NAMESPACE

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

OSG_SINGLETON_INST(BehaviorFactoryBase, addPostFactoryExitFunction)

template class SingletonHolder<BehaviorFactory>;

/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

void BehaviorFactoryBase::writeTypeDot(FILE     *pOut,
                                   TypeBase *pTypeBase)
{
    fprintf(pOut, "    OpenSG%s [shape=record,label=\"%s - %s\"]\n", 
            pTypeBase->getCName(),
            pTypeBase->getCName(),
            pTypeBase->isInitialized() ? "Init" : "UnInit");

    if(pTypeBase->getCParentName() != NULL)
    {
        fprintf(pOut, 
                "    OpenSG%s -> OpenSG%s\n", 
                pTypeBase->getCParentName(), 
                pTypeBase->getCName());
    }
}

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

BehaviorTransitPtr BehaviorFactoryBase::createBehavior(std::string Name)
{
	BehaviorTransitPtr newBehavior = OSG::Behavior::create();

	BehaviorType* BehaviorTypeBase = findType(static_cast<const Char8*>(Name.c_str()));

	newBehavior->TheBehaviorType = BehaviorTypeBase;

	return newBehavior;
}

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

/*------------- constructors & destructors --------------------------------*/

BehaviorFactoryBase::BehaviorFactoryBase(void) :
     Inherited    ("EventProducerFactory"),
    _vBehaviorTypeStore   (             )
{
    _vBehaviorTypeStore.reserve  (512 );
    _vBehaviorTypeStore.push_back(NULL);

    FactoryController::the()->registerFactory(this);
}

BehaviorFactoryBase::BehaviorFactoryBase(const Char8 *szName) :
     Inherited    (szName),
    _vBehaviorTypeStore   (      )
{
    _vBehaviorTypeStore.reserve  (512 );
    _vBehaviorTypeStore.push_back(NULL);

    FactoryController::the()->registerFactory(this);
}

BehaviorFactoryBase::~BehaviorFactoryBase(void)
{
}

bool BehaviorFactoryBase::initialize(void)
{
    BehaviorTypeStoreIt typeIt  = _vBehaviorTypeStore.begin();
    BehaviorTypeStoreIt typeEnd = _vBehaviorTypeStore.end  ();

    while(typeIt != typeEnd)
    {
  //      if((*typeIt) != NULL)
  //          (*typeIt)->initialize();

        ++typeIt;
    }

    return true;
}

bool BehaviorFactoryBase::initializeFactoryPost(void)
{
    return true;
}

bool BehaviorFactoryBase::terminate(void)
{
    return true;
}

bool BehaviorFactoryBase::onLoadInitialize(void)
{
    return true;
}

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

UInt32 BehaviorFactoryBase::registerType(BehaviorType *pType)
{
    UInt32 returnValue = 0;

    if(pType == NULL)
    {
        SWARNING << "no data store given" << endLog;

        return returnValue;
    }

    if(pType->getName().empty() == true)
    {
        SWARNING << "BehaviorType without name" << endLog;

        return returnValue;
    }

    UInt32 uiTypeId = findTypeId(pType->getChar8Name());

    if(uiTypeId != 0)
    {
        if(pType != findType(uiTypeId))
        {
            SWARNING << "ERROR: Can't add a second "
                     << "type with the name " << pType->getName()
                     << "(" << pType << ")"
                     << endLog;
        }
        else
        {
            SWARNING << "Do not run ctr twice "
                     << "type with the name " << pType->getName() 
                     << "(" << pType << ")"
                     << endLog;

//            findType(uiTypeId)->dump();

            returnValue = uiTypeId;
        }

        return returnValue;
    }

    returnValue = _vBehaviorTypeStore.size();

	_vBehaviorTypeNameMap[pType->getCName()] = returnValue;

	for(UInt32 i = 0; i < returnValue; i++)
	{
		if(findType(i) != NULL)
		{
			for(UInt32 d = 0; d < pType->_bEvents.size(); d++)
			{
				if(findType(i)->hasEventLink(pType->_bEvents[d]))
				{
					if(!findType(i)->hasDependency(pType))
					{
						findType(i)->_bDependencies.push_back(pType);
					}
					if(!pType->hasDependent(findType(i)))
					{
						pType->_bDependents.push_back(findType(i));
					}
				}
			}
			for(UInt32 d = 0; d < pType->_bEventLinks.size(); d++)
			{
				if(findType(i)->hasEvent(pType->_bEventLinks[d]))
				{
					if(!findType(i)->hasDependent(pType))
					{
						findType(i)->_bDependents.push_back(pType);
					}
					if(!pType->hasDependency(findType(i)))
					{
						pType->_bDependencies.push_back(findType(i));
					}
				}
			}
		}
	}

    _vBehaviorTypeStore.push_back(pType);

    FDEBUG(("Registered type %s | %d (%p)\n", pType->getName(), returnValue,
                                              pType)); 

    return returnValue;
}

UInt32 BehaviorFactoryBase::findTypeId(const Char8 *szName)
{
    BehaviorNameMapConstIt typeIt;
    UInt32             uiTypeId = 0;

    if(szName == NULL)
        return uiTypeId;

    uiTypeId = _vBehaviorTypeNameMap[szName];

    return uiTypeId;
}

BehaviorType *BehaviorFactoryBase::findType(UInt32 uiTypeId)
{
    if(uiTypeId < _vBehaviorTypeStore.size())
    {
        return _vBehaviorTypeStore[uiTypeId];
    }
    else
    {
        return NULL;
    }
}

BehaviorType *BehaviorFactoryBase::findType(const Char8 *szName)
{
    UInt32 uiTypeId = findTypeId(szName);

    return findType(uiTypeId);
}

UInt32 BehaviorFactoryBase::getNumTypes(void)
{
    return _vBehaviorTypeStore.size();
}

void BehaviorFactoryBase::writeTypeGraph(FILE *pOut)
{
    if(pOut == NULL)
        return;

    fprintf(pOut, "digraph OSGTypeGraph\n{\n");

/* CHECK
    for_each(_vTypeStore.begin(), 
             _vTypeStore.end(),
             bind1st(ptr_fun(writeTypeDot), pOut));
 */

    fprintf(pOut, "    rankdir=LR;\n");
    fprintf(pOut, "    size=\"120,200\";\n");
    fprintf(pOut, "    page=\"8.2677,11.69\";\n");
    fprintf(pOut, "    radio=auto;\n");

    for(UInt32 i = 1; i < _vBehaviorTypeStore.size(); i++)
    {
        writeTypeDot(pOut, _vBehaviorTypeStore[i]);
    }

    fprintf(pOut, "}\n");
}

void BehaviorFactoryBase::writeTypeGraph(const Char8 *szFilename)
{
    if(szFilename == NULL)
        return;

    FILE *pOut = fopen(szFilename, "w");

    if(pOut == NULL)
        return;

    writeTypeGraph(pOut);

    if(pOut != NULL)
        fclose(pOut);
}

OSG_END_NAMESPACE
