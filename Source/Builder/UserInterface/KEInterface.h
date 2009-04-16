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

#ifndef _KEINTERFACE_H_
#define _KEINTERFACE_H_
#ifdef __sgi
#pragma once
#endif

#include "KEConfig.h"

#include "KEInterfaceBase.h"
#include "Builder/KEApplicationBuilderFields.h"

OSG_USING_NAMESPACE
KE_BEGIN_NAMESPACE

/*! \brief Interface class. See \ref 
           PageKabalaEngineInterface for a description.
*/

class KE_KABALAENGINELIB_DLLMAPPING Interface : public InterfaceBase
{
  private:

    typedef InterfaceBase Inherited;

    /*==========================  PUBLIC  =================================*/
  public:

    /*---------------------------------------------------------------------*/
    /*! \name                      Sync                                    */
    /*! \{                                                                 */

    virtual void changed(BitVector  whichField, 
                         ::osg::UInt32     origin    );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    virtual void dump(      ::osg::UInt32     uiIndent = 0, 
                      const BitVector  bvFlags  = 0) const;

    /*! \}                                                                 */

	virtual void createInterface(ApplicationBuilderPtr TheApplicationBuilder) = 0;
	virtual void connectInterface(ApplicationBuilderPtr TheApplicationBuilder) = 0;
	virtual void disconnectInterface(ApplicationBuilderPtr TheApplicationBuilder) = 0;
	virtual void updateInterface(ApplicationBuilderPtr TheApplicationBuilder) = 0;
	virtual void destroyInterface(ApplicationBuilderPtr TheApplicationBuilder) = 0;
    /*=========================  PROTECTED  ===============================*/
  protected:

    // Variables should all be in InterfaceBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    Interface(void);
    Interface(const Interface &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~Interface(void); 

    /*! \}                                                                 */
    
    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class InterfaceBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const Interface &source);
};

typedef Interface *InterfaceP;

KE_END_NAMESPACE

#include "KEInterfaceBase.inl"
#include "KEInterface.inl"

#endif /* _KEINTERFACE_H_ */
