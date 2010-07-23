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

#ifndef _KELUABEHAVIORTYPE_H_
#define _KELUABEHAVIORTYPE_H_

#include "OSGConfig.h"
#include "KEKabalaEngineDef.h"

#include "Project/Scene/KESceneFields.h"

#include "OSGBaseTypes.h"

#include <map>
#include <boost/function.hpp>
#include "KEBehaviorType.h"

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

class KE_KABALAENGINE_DLLMAPPING LuaBehaviorType : public BehaviorType
{
    /*==========================  PUBLIC  =================================*/

  public :

	typedef BehaviorType Inherited;

	void registerWithScene(Scene* scene);

    std::vector<std::string> getLuaFunctionNames();

	FieldContainerType * getFieldContainerType();

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    LuaBehaviorType(const std::string &szName,
				 FieldContainerType * bBehaviorFieldContainerType,
                 std::vector<std::string> eventSourceNames = std::vector<std::string>(),
				 std::vector<std::string> bEvents = std::vector<std::string>(),
				 std::vector<std::string> bEventLinks = std::vector<std::string>(),
                 std::vector<std::string> bLuaCallbacks = std::vector<std::string>(),
			     BoostPath& FilePath = BoostPath());

    static LuaBehaviorType create(const std::string &szName,
                               const std::string &type,
                               const std::string &bEvents = "",
                               const std::string &bEventLinks = "",
                               const std::string &luaCallback = "",
                               const std::string &StrFilePath = "");

    LuaBehaviorType(const LuaBehaviorType &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~LuaBehaviorType(void); 

	/*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name						Get	                                   */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name						Has	                                   */
    /*! \{                                                                 */


    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                  Type Information                            */
    /*! \{                                                                 */


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

    std::vector<std::string>    luaFunctionNames;   //("button1",NULL,"Window","Button2",NULL)

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Register                                  */
    /*! \{                                                                 */


    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name             Intialization / Termination                      */
    /*! \{                                                                 */


    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:
   // typedef TypeBase Inherited;

    friend class BehaviorFactoryBase;
	friend class Behavior;

    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const LuaBehaviorType &source);
};

OSG_END_NAMESPACE

#include "KELuaBehaviorType.inl"

#endif /* _KELUABEHAVIORTYPE_H_ */
