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

#ifndef _KESCENECOMPONENTEDITOR_H_
#define _KESCENECOMPONENTEDITOR_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>

#include "KESceneComponentEditorBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief SceneComponentEditor class. See \ref 
           PageKabalaEngineSceneComponentEditor for a description.
*/

class KE_KABALAENGINELIB_DLLMAPPING SceneComponentEditor : public SceneComponentEditorBase
{
  private:

    typedef SceneComponentEditorBase Inherited;

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
    /*=========================  PROTECTED  ===============================*/
  protected:

    // Variables should all be in SceneComponentEditorBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    SceneComponentEditor(void);
    SceneComponentEditor(const SceneComponentEditor &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~SceneComponentEditor(void); 

    /*! \}                                                                 */
    
    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class SceneComponentEditorBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const SceneComponentEditor &source);
};

typedef SceneComponentEditor *SceneComponentEditorP;

OSG_END_NAMESPACE

#include "KESceneComponentEditorBase.inl"
#include "KESceneComponentEditor.inl"

#endif /* _KESCENECOMPONENTEDITOR_H_ */
