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

#ifndef _KESCENEBACKGROUNDSCOMBOBOXMODEL_H_
#define _KESCENEBACKGROUNDSCOMBOBOXMODEL_H_
#ifdef __sgi
#pragma once
#endif

#include "KEConfig.h"
#include "KEKabalaEngineDef.h"

#include "KESceneBackgroundsComboBoxModelBase.h"
#include <OpenSG/OSGBackground.h>

OSG_USING_NAMESPACE
KE_BEGIN_NAMESPACE

/*! \brief SceneBackgroundsComboBoxModel class. See \ref 
           PageUserInterfaceSceneBackgroundsComboBoxModel for a description.
*/

class KE_KABALAENGINELIB_DLLMAPPING SceneBackgroundsComboBoxModel : public SceneBackgroundsComboBoxModelBase
{
  private:

    typedef SceneBackgroundsComboBoxModelBase Inherited;

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
	virtual ::osg::UInt32 getSize(void) const;
	
    virtual boost::any getElementAt(::osg::UInt32 index) const;

	//Returns the selected item
	virtual boost::any getSelectedItem(void) const;

	//Returns the selected item Index
	virtual Int32 getSelectedItemIndex(void) const;

	//Set the selected item.
	virtual void setSelectedItem(const Int32& index);
	
	//Set the selected item.
    virtual void setSelectedItem(const boost::any& anObject);

    Int32 addBackground(BackgroundPtr TheBackground);
    void removeBackground( UInt32 RemoveIndex);
    void renameBackground( UInt32 Index, const std::string& NewName);
    /*=========================  PROTECTED  ===============================*/
  protected:

    // Variables should all be in SceneBackgroundsComboBoxModelBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    SceneBackgroundsComboBoxModel(void);
    SceneBackgroundsComboBoxModel(const SceneBackgroundsComboBoxModel &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~SceneBackgroundsComboBoxModel(void); 

    /*! \}                                                                 */
	
	Int32 calcInitialIndex(void) const;
    
    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class SceneBackgroundsComboBoxModelBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const SceneBackgroundsComboBoxModel &source);
};

typedef SceneBackgroundsComboBoxModel *SceneBackgroundsComboBoxModelP;

KE_END_NAMESPACE

#include "KESceneBackgroundsComboBoxModelBase.inl"
#include "KESceneBackgroundsComboBoxModel.inl"

#endif /* _KESCENEBACKGROUNDSCOMBOBOXMODEL_H_ */
