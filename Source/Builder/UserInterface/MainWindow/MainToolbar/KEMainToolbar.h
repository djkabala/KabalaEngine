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

#ifndef _KEMAINTOOLBAR_H_
#define _KEMAINTOOLBAR_H_
#ifdef __sgi
#pragma once
#endif

#include "KEMainToolbarBase.h"
#include <OpenSG/OSGButtonFields.h>
#include <OpenSG/OSGActionEventDetailsFields.h>
#include <OpenSG/OSGChangeEventDetailsFields.h>
#include <OpenSG/OSGUndoManager.h>
#include <OpenSG/OSGCommandManager.h>

OSG_BEGIN_NAMESPACE

/*! \brief MainToolbar class. See \ref
           PageKabalaEngineMainToolbar for a description.
*/

class KE_KABALAENGINE_DLLMAPPING MainToolbar : public MainToolbarBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef MainToolbarBase Inherited;
    typedef MainToolbar     Self;

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

	virtual void createInterface(ApplicationBuilder* const TheApplicationBuilder);
	virtual void destroyInterface(ApplicationBuilder* const TheApplicationBuilder);

	virtual void attachInterface(ApplicationBuilder* const TheApplicationBuilder);
	virtual void dettachInterface(ApplicationBuilder* const TheApplicationBuilder);
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in MainToolbarBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    MainToolbar(void);
    MainToolbar(const MainToolbar &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~MainToolbar(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    void updateUndoRedoInterfaces(void);

    void handleOpenButton(ActionEventDetails* const details);
    void handleSaveButton(ActionEventDetails* const details);
    void handleNewButton(ActionEventDetails* const details);
    void handleUndoButton(ActionEventDetails* const details);
    void handleRedoButton(ActionEventDetails* const details);
    void handlePlayButton(ActionEventDetails* const details);
    void handleHelpButton(ActionEventDetails* const details);
    
    void handleUndoChange(ChangeEventDetails* const details);

    boost::signals2::connection _OpenButtonConnection,
                                _SaveButtonConnection,
                                _NewButtonConnection,
                                _UndoButtonConnection,
                                _RedoButtonConnection,
                                _PlayButtonConnection,
                                _HelpButtonConnection,

                                _UndoChangeConnection;

    ButtonRecPtr _OpenButton;
    ButtonRecPtr _SaveButton;
    ButtonRecPtr _NewButton;
    ButtonRecPtr _UndoButton;
    ButtonRecPtr _RedoButton;
    ButtonRecPtr _PlayButton;
    ButtonRecPtr _HelpButton;
    
    CommandManagerPtr _TheCommandManager;
    UndoManagerPtr _UndoManager;
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class MainToolbarBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const MainToolbar &source);
};

typedef MainToolbar *MainToolbarP;

OSG_END_NAMESPACE

#include "KEMainToolbarBase.inl"
#include "KEMainToolbar.inl"

#endif /* _KEMAINTOOLBAR_H_ */
