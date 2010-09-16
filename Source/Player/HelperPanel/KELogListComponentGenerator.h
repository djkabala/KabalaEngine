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

#ifndef _KELOGLISTCOMPONENTGENERATOR_H_
#define _KELOGLISTCOMPONENTGENERATOR_H_
#ifdef __sgi
#pragma once
#endif

#include "KELogListComponentGeneratorBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief LogListComponentGenerator class. See \ref
           PageKabalaEngineLogListComponentGenerator for a description.
*/

class KE_KABALAENGINE_DLLMAPPING LogListComponentGenerator : public LogListComponentGeneratorBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef LogListComponentGeneratorBase Inherited;
    typedef LogListComponentGenerator     Self;

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
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in LogListComponentGeneratorBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    LogListComponentGenerator(void);
    LogListComponentGenerator(const LogListComponentGenerator &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~LogListComponentGenerator(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */

	virtual void applyBordersAndBackground(Component* const TheComponent, List* const Parent, const std::string& Value, UInt32 Index, bool IsSelected, bool HasFocus) const;
	virtual void applyTextColor(TextComponent* const TheComponent, List* const Parent, const std::string& Value, UInt32 Index, bool IsSelected, bool HasFocus) const;
    virtual std::string getText(List* const Parent, const boost::any& Value, UInt32 Index, bool IsSelected, bool HasFocus) const;

    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class LogListComponentGeneratorBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const LogListComponentGenerator &source);
};

typedef LogListComponentGenerator *LogListComponentGeneratorP;

OSG_END_NAMESPACE

#include "KELogListComponentGeneratorBase.inl"
#include "KELogListComponentGenerator.inl"

#endif /* _KELOGLISTCOMPONENTGENERATOR_H_ */
