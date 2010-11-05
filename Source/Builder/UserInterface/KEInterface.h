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

#ifndef _KEINTERFACE_H_
#define _KEINTERFACE_H_
#ifdef __sgi
#pragma once
#endif

#include "KEInterfaceBase.h"
#include "Builder/KEApplicationBuilderFields.h"

OSG_BEGIN_NAMESPACE

/*! \brief Interface class. See \ref
           PageKabalaEngineInterface for a description.
*/

class KE_KABALAENGINE_DLLMAPPING Interface : public InterfaceBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef InterfaceBase Inherited;
    typedef Interface     Self;

    /*---------------------------------------------------------------------*/
    /*! \name                      Sync                                    */
    /*! \{                                                                 */

    virtual void changed(ConstFieldMaskArg whichField,
                         UInt32            origin,
                         BitVector         details    );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    virtual void dump(      UInt32     uiIndent = 0,
                      const BitVector  bvFlags  = 0) const;

    /*! \}                                                                 */

	virtual void createInterface(ApplicationBuilder* const TheApplicationBuilder) = 0;
	virtual void destroyInterface(ApplicationBuilder* const TheApplicationBuilder) = 0;

	virtual void attachInterface(ApplicationBuilder* const TheApplicationBuilder) = 0;
	virtual void dettachInterface(ApplicationBuilder* const TheApplicationBuilder) = 0;
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
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    AttachmentContainer* findContainer(const std::string& RefName,
                                       ApplicationBuilder* const TheApplicationBuilder);
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class InterfaceBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const Interface &source);
};

typedef Interface *InterfaceP;

OSG_END_NAMESPACE

#include "KEInterfaceBase.inl"
#include "KEInterface.inl"

#endif /* _KEINTERFACE_H_ */
