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

#ifndef _KEKESCENECOMPONENTTREECOMPONENTGENERATOR_H_
#define _KEKESCENECOMPONENTTREECOMPONENTGENERATOR_H_
#ifdef __sgi
#pragma once
#endif

#include "KESceneComponentTreeComponentGeneratorBase.h"
#include "KESceneComponentTreeFields.h"
#include <OpenSG/OSGButtonFields.h>
#include <OpenSG/OSGMenuButtonFields.h>

OSG_BEGIN_NAMESPACE

/*! \brief SceneComponentTreeComponentGenerator class. See \ref
           PageKabalaEngineSceneComponentTreeComponentGenerator for a description.
*/

class KE_KABALAENGINE_DLLMAPPING SceneComponentTreeComponentGenerator : public SceneComponentTreeComponentGeneratorBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef SceneComponentTreeComponentGeneratorBase Inherited;
    typedef SceneComponentTreeComponentGenerator     Self;

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
	virtual ComponentTransitPtr getTreeComponent(Tree* const Parent,
                                             const boost::any& Value,
                                             bool IsSelected,
                                             bool Expanded,
                                             bool Leaf,
                                             UInt32 Row,
                                             bool HasFocus);

    void setSceneComponentTree(SceneComponentTree* const value);
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in SceneComponentTreeComponentGeneratorBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    SceneComponentTreeComponentGenerator(void);
    SceneComponentTreeComponentGenerator(const SceneComponentTreeComponentGenerator &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~SceneComponentTreeComponentGenerator(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    SceneComponentTree* _SceneComponentTree;
    boost::signals2::connection _AddForegroundConnection,
                                _AddLightConnection,
                                _AddSceneObjectConnection;
    
    MenuButtonRecPtr _AddForegroundButton;
    MenuButtonRecPtr _AddLightButton;
    ButtonRecPtr _AddSceneObjectButton;

    friend class FieldContainer;
    friend class SceneComponentTreeComponentGeneratorBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const SceneComponentTreeComponentGenerator &source);
};

typedef SceneComponentTreeComponentGenerator *SceneComponentTreeComponentGeneratorP;

OSG_END_NAMESPACE

#include "KESceneComponentTreeComponentGeneratorBase.inl"
#include "KESceneComponentTreeComponentGenerator.inl"

#endif /* _KEKESCENECOMPONENTTREECOMPONENTGENERATOR_H_ */
