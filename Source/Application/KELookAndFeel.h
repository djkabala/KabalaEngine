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

#ifndef _KELOOKANDFEEL_H_
#define _KELOOKANDFEEL_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "KEConfig.h"

OSG_BEGIN_NAMESPACE

/*! \brief KELookAndFeel class. See \ref 
           PageKabalaEngineKELookAndFeel for a description.
*/

class KE_KABALAENGINE_DLLMAPPING KELookAndFeel
{
  private:
    /*==========================  PUBLIC  =================================*/
      static KELookAndFeel* _Instance;
  public:

      static KELookAndFeel* the(void);

      bool init(void);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */


    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~KELookAndFeel(void); 
    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/
  private:

    void operator =(const KELookAndFeel &source);
    KELookAndFeel(void);
    KELookAndFeel(const KELookAndFeel &source);
};

typedef KELookAndFeel *KELookAndFeelP;

OSG_END_NAMESPACE

#include "KELookAndFeel.inl"

#endif /* _KEMAINAPPLICATION_H_ */
