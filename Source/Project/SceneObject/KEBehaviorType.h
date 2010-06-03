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

#ifndef _OSGEVENTPRODUCERTYPE_H_
#define _OSGEVENTPRODUCERTYPE_H_

#include "OSGConfig.h"
#include "OSGBaseDef.h"

#include "OSGBaseTypes.h"

#include <map>
#include <boost/function.hpp>

OSG_BEGIN_NAMESPACE

class MethodDescription;

/*! \ingroup GrpSystemFieldContainerFuncs
 */

//typedef void              (*InitContainerF)  (void);

/*! \ingroup GrpSystemFieldContainerFuncs
 */

//typedef FieldContainerPtr (*PrototypeCreateF)(void);

/*! \ingroup GrpSystemFieldContainer
 */
typedef boost::function<void ( void )> InitEventProducerFunctor;

class OSG_BASE_DLLMAPPING EventProducerType : public TypeBase
{
    /*==========================  PUBLIC  =================================*/

  public :

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */
   
    EventProducerType(const std::string                &szName,
                       const std::string    &szParentName      = "",
                       const std::string    &szGroupName       = "",
                       //PrototypeCreateF    fPrototypeCreate  = NULL,
                       InitEventProducerFunctor      fInitMethod       = InitEventProducerFunctor(),
                       MethodDescription **pDesc             = NULL,
                       UInt32              uiDescByteCounter = 0);

    EventProducerType(const EventProducerType &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~EventProducerType(void); 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                  Type Information                            */
    /*! \{                                                                 */

    UInt16              getGroupId(void) const;
    EventProducerType *getParent (void) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                 Description                                  */
    /*! \{                                                                 */

          MethodDescription *getMethodDescription (UInt32 uiMethodId);
    const MethodDescription *getMethodDescription (UInt32 uiMethodId) const;

          MethodDescription *findMethodDescription(const std::string &szMethodName);

    const MethodDescription *findMethodDescription(
        const std::string &szMethodName) const; 

    UInt32                 getNumMethodDescs(void) const;

    UInt32                 addDescription  (const MethodDescription &desc     );
    bool                   subDescription  (      UInt32            uiMethodId);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                 Prototype                                    */
    /*! \{                                                                 */

    //FieldContainerPtr getPrototype(void                        ) const;
    //bool              setPrototype(FieldContainerPtr pPrototype);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                Query Properties                              */
    /*! \{                                                                 */

    bool isInitialized(void                           ) const;

    bool isAbstract   (void                           ) const;

    bool isDerivedFrom(const TypeBase           &other) const;
    bool isDerivedFrom(const EventProducerType &other) const;    

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                        Dump                                  */
    /*! \{                                                                 */

    virtual void dump(      UInt32    uiIndent = 0, 
                      const BitVector bvFlags  = 0) const;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    typedef std::map   <std::string,  MethodDescription *> DescMap;
    typedef std::vector<              MethodDescription *> DescVec;

    typedef DescMap::iterator                             DescMapIt;
    typedef DescVec::iterator                             DescVecIt;

    typedef DescMap::const_iterator                       DescMapConstIt;
    typedef DescVec::const_iterator                       DescVecConstIt;

    /*---------------------------------------------------------------------*/
    /*! \name                      Member                                  */
    /*! \{                                                                 */

    UInt16              _uiGroupId;
    std::string            _szGroupName;

    bool                _bInitialized;

    EventProducerType *_pParent;
    std::string                _szParentName;

    MethodDescription  **_pDesc;
    UInt32              _uiDescByteCounter;

    DescMap             _mDescMap;
    DescVec             _vDescVec;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Register                                  */
    /*! \{                                                                 */

    void registerType(const std::string &szGroupName);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name             Intialization / Termination                      */
    /*! \{                                                                 */

    bool initMethods      (void);
    bool initParentMethods(void);

    bool initialize      (void);
    void terminate       (void);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    typedef TypeBase Inherited;

    friend class EventProducerFactoryBase;

    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const EventProducerType &source);
};

struct OSG_BASE_DLLMAPPING MethodDescriptionPLT
{
    bool operator()(const MethodDescription *pElemDesc1, 
                    const MethodDescription *pElemDesc2) const;
};

OSG_END_NAMESPACE

#include "OSGEventProducerType.inl"

#endif /* _OSGEVENTPRODUCERTYPE_H_ */
