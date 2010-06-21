/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000-2002 by the OpenSG Forum                   *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 *   contact: dirk@opensg.org, gerrit.voss@vossg.org, jbehr@zgdv.de          *
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

#ifndef _KEBEHAVIORFACTORYIMPL_H_
#define _KEBEHAVIORFACTORYIMPL_H_

#include "OSGConfig.h"
#include "KEKabalaEngineDef.h"

#include "OSGSingletonHolder.h"
#include "OSGTypeBase.h"
#include "OSGFactoryBase.h"

#include <map>
#include <vector>

OSG_BEGIN_NAMESPACE

//---------------------------------------------------------------------------
//  Forward References                                                       
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//   Types                                                                   
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//  Class                                                                    
//---------------------------------------------------------------------------

/*! \brief Accessible via #TypeFactory
    \ingroup GrpBaseBaseTypeSystem
    \ingroup GrpBaseBase
    \ingroup GrpLibOSGBase
 */

class KE_KABALAENGINE_DLLMAPPING BehaviorFactoryBase : public FactoryBase
{
  public:

    //-----------------------------------------------------------------------
    //   constants                                                           
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    typedef FactoryBase Inherited;

  private:

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    typedef std::map   <std::string, UInt32>   TypeNameMap;

    typedef TypeNameMap::iterator              TypeNameMapIt;
    typedef TypeNameMap::const_iterator        TypeNameMapConstIt;

    typedef std::vector<TypeBase           *>  TypeStore;

    typedef TypeStore::iterator                TypeStoreIt;
    typedef TypeStore::const_iterator          TypeStoreConstIt;

    typedef std::vector<TypeNameMap        *>  TypeMapsStore;

    //-----------------------------------------------------------------------
    //   friend classes                                                      
    //-----------------------------------------------------------------------

    template <class SingletonT>
    friend class SingletonHolder;

    friend class FactoryControllerBase;

    //-----------------------------------------------------------------------
    //   friend functions                                                    
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   class variables                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance variables                                                  
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    //! \brief prohibit default function (move to 'public' if needed) 
    BehaviorFactoryBase(const BehaviorFactoryBase &source);
    //! \brief prohibit default function (move to 'public' if needed) 
    void operator =(const BehaviorFactoryBase &source);

  protected:

    //-----------------------------------------------------------------------
    //   constants                                                           
    //-----------------------------------------------------------------------

    static const UInt32 GlobalNamespace = TypeBase::GlobalNamespace;

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   class variables                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    static void writeTypeDot(FILE     *pOut,
                             TypeBase *pTypeBase);

    //-----------------------------------------------------------------------
    //   instance variables                                                  
    //-----------------------------------------------------------------------

    TypeMapsStore _vTypeNameMaps;
    TypeStore     _vTypeStore;

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    BehaviorFactoryBase(void);
    BehaviorFactoryBase(const Char8 *szName);

    virtual ~BehaviorFactoryBase(void); 

    virtual bool initialize           (void);
    virtual bool terminate            (void);

    virtual bool onLoadInitialize     (void);

    virtual bool initializeFactoryPost(void);

  public :

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    UInt32 registerType(TypeBase *pType);

    /*---------------------------------------------------------------------*/

    UInt32    findTypeId(const Char8    *szName,
                         const UInt32    uiNameSpace = GlobalNamespace);

    TypeBase *findType  (      UInt32    uiTypeId       );
    TypeBase *findType  (const Char8    *szName,
                         const UInt32    uiNameSpace = GlobalNamespace);

    /*---------------------------------------------------------------------*/

    UInt32 getNumTypes(void);

    /*---------------------------------------------------------------------*/

    void writeTypeGraph(      FILE     *pOut      );
    void writeTypeGraph(const Char8    *szFilename);
};

#if defined(WIN32)
#    if !defined(OSG_COMPILE_TYPEFACTORY)
//OSG_BASE_EXPIMP_TMPL 
//template class OSG_BASE_DLLMAPPING SingletonHolder<EventProducerFactoryBase>;
#    endif
#endif

/*! \typedef OSG::SingletonHolder<OSG::EventProducerFactoryBase> TypeFactory;
    \ingroup GrpBaseBaseTypeSystem
    \relatesalso OSG::EventProducerFactoryBase
 */

typedef OSG::SingletonHolder<OSG::BehaviorFactoryBase> BehaviorFactory;

OSG_END_NAMESPACE

#endif /* _KEBEHAVIORFACTORYIMPL_H_ */
