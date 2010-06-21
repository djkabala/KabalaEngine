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

#ifndef _KEBACKGROUNDSLISTCOMPONENTGENERATOR_H_
#define _KEBACKGROUNDSLISTCOMPONENTGENERATOR_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>

#include "KEBackgroundsListComponentGeneratorBase.h"
#include "Builder/UserInterface/IconManager/KEIconManager.h"

OSG_BEGIN_NAMESPACE

/*! \brief BackgroundsListComponentGenerator class. See \ref 
           PageKabalaEngineBackgroundsListComponentGenerator for a description.
*/

class KE_KABALAENGINELIB_DLLMAPPING BackgroundsListComponentGenerator : public BackgroundsListComponentGeneratorBase
{
  private:

    typedef BackgroundsListComponentGeneratorBase Inherited;

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
	virtual ComponentPtr getListComponent(::osg::ListPtr Parent, const boost::any& Value, ::osg::UInt32 Index, bool IsSelected, bool HasFocus);

	void setIconManager(IconManagerPtr TheIconManager);
	IconManagerPtr getIconManager(void) const;
    /*=========================  PROTECTED  ===============================*/
  protected:

    // Variables should all be in BackgroundsListComponentGeneratorBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    BackgroundsListComponentGenerator(void);
    BackgroundsListComponentGenerator(const BackgroundsListComponentGenerator &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~BackgroundsListComponentGenerator(void); 

    /*! \}                                                                 */
	IconManagerPtr _IconManager;
    
    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class BackgroundsListComponentGeneratorBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const BackgroundsListComponentGenerator &source);
};

typedef BackgroundsListComponentGenerator *BackgroundsListComponentGeneratorP;

OSG_END_NAMESPACE

#include "KEBackgroundsListComponentGeneratorBase.inl"
#include "KEBackgroundsListComponentGenerator.inl"

#endif /* _KEBACKGROUNDSLISTCOMPONENTGENERATOR_H_ */
