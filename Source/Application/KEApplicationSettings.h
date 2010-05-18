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

#ifndef _KEAPPLICATIONSETTINGS_H_
#define _KEAPPLICATIONSETTINGS_H_
#ifdef __sgi
#pragma once
#endif

#include "KEApplicationSettingsBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief ApplicationSettings class. See \ref
           PageKabalaEngineApplicationSettings for a description.
*/

class KE_KABALAENGINE_DLLMAPPING ApplicationSettings : public ApplicationSettingsBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef ApplicationSettingsBase Inherited;
    typedef ApplicationSettings     Self;

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

	void save(const BoostPath& FilePath);

	static ApplicationSettingsUnrecPtr load(const BoostPath& FilePath);

	static ApplicationSettingsUnrecPtr create(const BoostPath& FilePath);
	static ApplicationSettingsTransitPtr create(void);
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in ApplicationSettingsBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    ApplicationSettings(void);
    ApplicationSettings(const ApplicationSettings &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~ApplicationSettings(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class ApplicationSettingsBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const ApplicationSettings &source);
};

typedef ApplicationSettings *ApplicationSettingsP;

OSG_END_NAMESPACE

#include "KEApplicationSettingsBase.inl"
#include "KEApplicationSettings.inl"

#endif /* _KEAPPLICATIONSETTINGS_H_ */
