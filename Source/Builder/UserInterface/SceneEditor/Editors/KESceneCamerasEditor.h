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

#ifndef _KESCENECAMERASEDITOR_H_
#define _KESCENECAMERASEDITOR_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>

#include "KESceneCamerasEditorBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief SceneCamerasEditor class. See \ref 
           PageKabalaEngineSceneCamerasEditor for a description.
*/

class KE_KABALAENGINELIB_DLLMAPPING SceneCamerasEditor : public SceneCamerasEditorBase
{
  private:

    typedef SceneCamerasEditorBase Inherited;

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

    // Variables should all be in SceneCamerasEditorBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    SceneCamerasEditor(void);
    SceneCamerasEditor(const SceneCamerasEditor &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~SceneCamerasEditor(void); 

    /*! \}                                                                 */
	static const std::string _PresentationName;
	static const std::string _PresentationIconName;
    
    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class SceneCamerasEditorBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const SceneCamerasEditor &source);
};

typedef SceneCamerasEditor *SceneCamerasEditorP;

OSG_END_NAMESPACE

#include "KESceneCamerasEditorBase.inl"
#include "KESceneCamerasEditor.inl"

#endif /* _KESCENECAMERASEDITOR_H_ */
