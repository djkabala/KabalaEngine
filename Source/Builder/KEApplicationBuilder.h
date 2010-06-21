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

#ifndef _KEAPPLICATIONBUILDER_H_
#define _KEAPPLICATIONBUILDER_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>

#include "KEApplicationBuilderBase.h"
#include <OpenSG/OSGForegroundFields.h>

#include "Builder/UserInterface/IconManager/KEIconManager.h"
#include <OpenSG/UserInterface/OSGCommandManager.h>
#include <OpenSG/UserInterface/OSGUndoManager.h>
#include "Builder/UserInterface/KEBuilderInterfaceFields.h"

OSG_BEGIN_NAMESPACE

/*! \brief ApplicationBuilder class. See \ref 
           PageKabalaEngineApplicationBuilder for a description.
*/

class KE_KABALAENGINELIB_DLLMAPPING ApplicationBuilder : public ApplicationBuilderBase
{
  private:

    typedef ApplicationBuilderBase Inherited;

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

    virtual void dump(      ::osg::UInt32     uiIndent, 
                      const BitVector  bvFlags ) const;

    /*! \}                                                                 */
	virtual void attachApplication(void);
	virtual void dettachApplication(void);
	ForegroundPtr createInterface(void);
	virtual void start(void);
	virtual void stop(void);
    virtual void reset(void);

	IconManagerPtr getIconManager(void) const;
	UndoManagerPtr getUndoManager(void) const;
	CommandManagerPtr getCommandManager(void) const;
	BuilderInterfacePtr getInterface(void) const;

	bool saveProject(void);
	bool saveProjectAs(void);


    /*=========================  PROTECTED  ===============================*/
  protected:

    // Variables should all be in ApplicationBuilderBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    ApplicationBuilder(void);
    ApplicationBuilder(const ApplicationBuilder &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~ApplicationBuilder(void); 

    /*! \}                                                                 */
	IconManagerPtr _IconManager;
	UndoManagerPtr _UndoManager;
	CommandManagerPtr _CommandManager;
	BuilderInterfacePtr _TheBuilderInterface;

	bool saveProject(const Path& ProjectFile);
    
    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class ApplicationBuilderBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const ApplicationBuilder &source);
};

typedef ApplicationBuilder *ApplicationBuilderP;

OSG_END_NAMESPACE

#include "KEApplicationBuilderBase.inl"
#include "KEApplicationBuilder.inl"

#endif /* _KEAPPLICATIONBUILDER_H_ */
