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

#ifndef _KEBEHAVIORTYPE_H_
#define _KEBEHAVIORTYPE_H_

#include "OSGConfig.h"
#include "KEKabalaEngineDef.h"

#include "OSGBaseTypes.h"

#include <map>
#include <boost/function.hpp>
#include "OSGTypeBase.h"

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

class KE_KABALAENGINE_DLLMAPPING BehaviorType : public TypeBase
{
    /*==========================  PUBLIC  =================================*/

  public :
    typedef TypeBase Inherited;

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    BehaviorType(const std::string                &szName,
                       const std::string    &szParentName      = "",
					   std::vector<BehaviorType> bDependencies = std::vector<BehaviorType>());

    BehaviorType(const BehaviorType &source);

	std::string getName();

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~BehaviorType(void); 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                  Type Information                            */
    /*! \{                                                                 */

    BehaviorType *getParent (void) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                 Description                                  */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                 Prototype                                    */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                Query Properties                              */
    /*! \{                                                                 */

    bool isInitialized(void                           ) const;

    bool isAbstract   (void                           ) const;
  

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                        Dump                                  */
    /*! \{                                                                 */

    virtual void dump(      UInt32    uiIndent = 0, 
                      const BitVector bvFlags  = 0) const;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    /*---------------------------------------------------------------------*/
    /*! \name                      Member                                  */
    /*! \{                                                                 */

    bool                _bInitialized;

	std::vector<BehaviorType>	_bDependencies;
	std::vector<BehaviorType>	_bDependents;

    BehaviorType *_pParent;
    std::string                _szParentName;
	std::string				   _bName;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Register                                  */
    /*! \{                                                                 */

    void registerType();

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name             Intialization / Termination                      */
    /*! \{                                                                 */

    bool initialize      (void);
    void terminate       (void);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

   // typedef TypeBase Inherited;

    friend class BehaviorTypeFactoryBase;

    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const BehaviorType &source);
};

OSG_END_NAMESPACE

#include "KEBehaviorType.inl"

#endif /* _KEBEHAVIORTYPE_H_ */
