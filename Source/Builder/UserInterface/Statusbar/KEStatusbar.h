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

#ifndef _KESTATUSBAR_H_
#define _KESTATUSBAR_H_
#ifdef __sgi
#pragma once
#endif

#include "KEConfig.h"

#include "KEStatusbarBase.h"
#include <OpenSG/UserInterface/OSGProgressBar.h>
#include <OpenSG/UserInterface/OSGLabel.h>
#include <OpenSG/UserInterface/OSGImageComponent.h>
#include <OpenSG/UserInterface/OSGDefaultBoundedRangeModel.h>

OSG_USING_NAMESPACE
KE_BEGIN_NAMESPACE

/*! \brief Statusbar class. See \ref 
           PageKabalaEngineStatusbar for a description.
*/

class KE_KABALAENGINELIB_DLLMAPPING Statusbar : public StatusbarBase
{
  private:

    typedef StatusbarBase Inherited;

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
	virtual void createInterface(ApplicationBuilderPtr TheApplicationBuilder);
	virtual void connectInterface(ApplicationBuilderPtr TheApplicationBuilder);
	virtual void disconnectInterface(ApplicationBuilderPtr TheApplicationBuilder);
	virtual void updateInterface(ApplicationBuilderPtr TheApplicationBuilder);
	virtual void destroyInterface(ApplicationBuilderPtr TheApplicationBuilder);

	//setgetStatusIcon
	void setStatusIcon(std::string StatusIconName);

	//setgetStatusDescription
	void setDescription(std::string Description);
	std::string getDescription(void) const;

	//setgetProgress
	void setProgress(const Int32& Value);
	Int32 getProgress(void) const;

    /*=========================  PROTECTED  ===============================*/
  protected:

    // Variables should all be in StatusbarBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    Statusbar(void);
    Statusbar(const Statusbar &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~Statusbar(void); 

    /*! \}                                                                 */
	ImageComponentPtr _IconComponent;
    LabelPtr _DiscriptorLabel;
	ProgressBarPtr _ProgressBar;
    DefaultBoundedRangeModel _ProgressBarBoundedRangeModel;
    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class StatusbarBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const Statusbar &source);
};

typedef Statusbar *StatusbarP;

KE_END_NAMESPACE

#include "KEStatusbarBase.inl"
#include "KEStatusbar.inl"

#endif /* _KESTATUSBAR_H_ */
