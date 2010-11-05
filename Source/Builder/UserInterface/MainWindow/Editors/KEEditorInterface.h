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

#ifndef _KEEDITORINTERFACE_H_
#define _KEEDITORINTERFACE_H_
#ifdef __sgi
#pragma once
#endif

#include "KEEditorInterfaceBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief EditorInterface class. See \ref
           PageKabalaEngineEditorInterface for a description.
*/

class KE_KABALAENGINE_DLLMAPPING EditorInterface : public EditorInterfaceBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef EditorInterfaceBase Inherited;
    typedef EditorInterface     Self;

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
    virtual UInt32 getCardIndex(void) const = 0;
    virtual std::string getEditorTypeText(void) const = 0;
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in EditorInterfaceBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    EditorInterface(void);
    EditorInterface(const EditorInterface &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~EditorInterface(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class EditorInterfaceBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const EditorInterface &source);
};

typedef EditorInterface *EditorInterfaceP;

OSG_END_NAMESPACE

#include "KEEditorInterfaceBase.inl"
#include "KEEditorInterface.inl"

#endif /* _KEEDITORINTERFACE_H_ */
