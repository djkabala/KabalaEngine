/*---------------------------------------------------------------------------*\
 *                        OpenSG ToolBox Toolbox                             *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                         www.vrac.iastate.edu                              *
 *                                                                           *
 *            Authors: David Kabala,Eric Langkamp,Robert Goetz               *
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

#include "Project/Scene/KESceneFields.h"

#include "OSGBaseTypes.h"

#include <map>
#include <boost/function.hpp>
#include "OSGTypeBase.h"

#include "OSGFilePathAttachment.h"
#include "OSGContainerUtils.h"
#include <fstream>
#include <sstream>


OSG_BEGIN_NAMESPACE

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
	std::vector<UInt32>	_bActiveEventIDs;
	
	void registerWithScene(Scene* scene);

	UInt32 findEventID(std::string eventName);
    std::string findEventName(UInt32 id);

    std::vector<std::string> BehaviorType::getLuaFunctionNames();

	std::string getCode();
	void setCode(std::string bCode);

	FieldContainerType * getFieldContainerType();

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    BehaviorType(const std::string &szName,
				 FieldContainerType * bBehaviorFieldContainerType,
                 std::vector<std::string> eventSourceNames = std::vector<std::string>(),
				 std::vector<std::string> bEvents = std::vector<std::string>(),
				 std::vector<std::string> bEventLinks = std::vector<std::string>(),
                 std::vector<std::string> bLuaCallbacks = std::vector<std::string>(),
			     BoostPath& FilePath = BoostPath());

    BehaviorType(const BehaviorType &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~BehaviorType(void); 

	/*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name						Get	                                   */
    /*! \{                                                                 */
    const std::vector<std::string> getEvents();
    const std::vector<std::string> getEventLinks();

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name						Has	                                   */
    /*! \{                                                                 */
	bool hasEvent(std::string e);
	bool hasEventLink(std::string e);
	bool hasDependent(BehaviorType* d);
	bool hasDependency(BehaviorType* d);

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

    bool isInitialized(void) const;

    bool isAbstract(void) const;
  

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                        Dump                                  */
    /*! \{                                                                 */

    virtual void dump(UInt32 uiIndent = 0, const BitVector bvFlags  = 0) const;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    /*---------------------------------------------------------------------*/
    /*! \name                      Member                                  */
    /*! \{                                                                 */

    bool _bInitialized;
	std::string TheCode;

	std::vector<BehaviorType*>	_bDependencies;
	std::vector<BehaviorType*>	_bDependents;

    std::vector<std::string>    _bSourceContainers; //("button1",NULL,"Window","Button2",NULL)
	std::vector<std::string>	_bEvents;           //("press  ","evt1","update","press","evt2")
	std::vector<std::string>	_bEventLinks;       //("button1",NULL,"Window","Button2",NULL)
    std::vector<std::string>    luaFunctionNames;   //("button1",NULL,"Window","Button2",NULL)

    BehaviorType *_pParent;

	Scene * attachedScene;
	
	FieldContainerType * behaviorFieldContainerType;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Register                                  */
    /*! \{                                                                 */

    void registerType();

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name             Intialization / Termination                      */
    /*! \{                                                                 */

    bool initialize(void);
    void terminate(void);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:
   // typedef TypeBase Inherited;

    friend class BehaviorFactoryBase;
	friend class Behavior;

    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const BehaviorType &source);
};

OSG_END_NAMESPACE

#include "KEBehaviorType.inl"

#endif /* _KEBEHAVIORTYPE_H_ */
