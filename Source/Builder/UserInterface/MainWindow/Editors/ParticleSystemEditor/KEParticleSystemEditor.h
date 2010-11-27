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

#ifndef _KEPARTICLESYSTEMEDITOR_H_
#define _KEPARTICLESYSTEMEDITOR_H_
#ifdef __sgi
#pragma once
#endif

#include "KEParticleSystemEditorBase.h"
#include <OpenSG/OSGParticleSystemFields.h>
#include <OpenSG/OSGGenericNameAttachmentEditorFields.h>

OSG_BEGIN_NAMESPACE

/*! \brief ParticleSystemEditor class. See \ref
           PageKabalaEngineParticleSystemEditor for a description.
*/

class KE_KABALAENGINE_DLLMAPPING ParticleSystemEditor : public ParticleSystemEditorBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef ParticleSystemEditorBase Inherited;
    typedef ParticleSystemEditor     Self;

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

    void attachParticleSystem(ParticleSystem* const TheParticleSystem);
    void dettachParticleSystem(void);
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in ParticleSystemEditorBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    ParticleSystemEditor(void);
    ParticleSystemEditor(const ParticleSystemEditor &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~ParticleSystemEditor(void);

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
    friend class ParticleSystemEditorBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const ParticleSystemEditor &source);
};

typedef ParticleSystemEditor *ParticleSystemEditorP;

OSG_END_NAMESPACE

#include "KEParticleSystemEditorBase.inl"
#include "KEParticleSystemEditor.inl"

#endif /* _KEPARTICLESYSTEMEDITOR_H_ */
