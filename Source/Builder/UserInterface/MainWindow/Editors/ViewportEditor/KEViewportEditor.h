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

#ifndef _KEVIEWPORTEDITOR_H_
#define _KEVIEWPORTEDITOR_H_
#ifdef __sgi
#pragma once
#endif

#include "KEViewportEditorBase.h"
#include <OpenSG/OSGViewportFields.h>
#include <OpenSG/OSGGenericNameAttachmentEditorFields.h>

OSG_BEGIN_NAMESPACE

/*! \brief ViewportEditor class. See \ref
           PageKabalaEngineViewportEditor for a description.
*/

class KE_KABALAENGINE_DLLMAPPING ViewportEditor : public ViewportEditorBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef ViewportEditorBase Inherited;
    typedef ViewportEditor     Self;

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

	virtual void createInterface(ApplicationBuilder* const TheApplicationBuilder);
	virtual void destroyInterface(ApplicationBuilder* const TheApplicationBuilder);

	virtual void attachInterface(ApplicationBuilder* const TheApplicationBuilder);
	virtual void dettachInterface(ApplicationBuilder* const TheApplicationBuilder);

    virtual UInt32 getCardIndex(void) const;
    virtual std::string getEditorTypeText(void) const;

    void attachViewport(Viewport* const TheViewport);
    void dettachViewport(void);
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in ViewportEditorBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    ViewportEditor(void);
    ViewportEditor(const ViewportEditor &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~ViewportEditor(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    GenericNameAttachmentEditorRecPtr _NameEditor;
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class ViewportEditorBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const ViewportEditor &source);
};

typedef ViewportEditor *ViewportEditorP;

OSG_END_NAMESPACE

#include "KEViewportEditorBase.inl"
#include "KEViewportEditor.inl"

#endif /* _KEVIEWPORTEDITOR_H_ */
