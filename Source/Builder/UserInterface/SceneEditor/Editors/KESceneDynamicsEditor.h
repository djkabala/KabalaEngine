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

#ifndef _KESCENEDYNAMICSEDITOR_H_
#define _KESCENEDYNAMICSEDITOR_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>

#include "KESceneDynamicsEditorBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief SceneDynamicsEditor class. See \ref 
           PageKabalaEngineSceneDynamicsEditor for a description.
*/

class KE_KABALAENGINELIB_DLLMAPPING SceneDynamicsEditor : public SceneDynamicsEditorBase
{
  private:

    typedef SceneDynamicsEditorBase Inherited;

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

	virtual const std::string& getPresentationName(void) const;

	virtual const std::string& getPresentationIconName(void) const;
    /*=========================  PROTECTED  ===============================*/
  protected:

    // Variables should all be in SceneDynamicsEditorBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    SceneDynamicsEditor(void);
    SceneDynamicsEditor(const SceneDynamicsEditor &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~SceneDynamicsEditor(void); 

    /*! \}                                                                 */
	static const std::string _PresentationName;
	static const std::string _PresentationIconName;
    
    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class SceneDynamicsEditorBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const SceneDynamicsEditor &source);
};

typedef SceneDynamicsEditor *SceneDynamicsEditorP;

OSG_END_NAMESPACE

#include "KESceneDynamicsEditorBase.inl"
#include "KESceneDynamicsEditor.inl"

#endif /* _KESCENEDYNAMICSEDITOR_H_ */
