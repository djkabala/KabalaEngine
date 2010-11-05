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

#ifndef _KESCENEVIEWPORTTOOLBAR_H_
#define _KESCENEVIEWPORTTOOLBAR_H_
#ifdef __sgi
#pragma once
#endif

#include "KESceneViewportToolbarBase.h"

#include <OpenSG/OSGButtonFields.h>
#include <OpenSG/OSGToggleButtonFields.h>
#include <OpenSG/OSGMenuButtonFields.h>
#include <OpenSG/OSGActionEventDetailsFields.h>

OSG_BEGIN_NAMESPACE

/*! \brief SceneViewportToolbar class. See \ref
           PageKabalaEngineSceneViewportToolbar for a description.
*/

class KE_KABALAENGINE_DLLMAPPING SceneViewportToolbar : public SceneViewportToolbarBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef SceneViewportToolbarBase Inherited;
    typedef SceneViewportToolbar     Self;

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

    void setTranslationEditing(bool Enabled);
    void setRotationEditing(bool Enabled);
    void setScaleEditing(bool Enabled);
    void disableTransformationEditing(void);
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in SceneViewportToolbarBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    SceneViewportToolbar(void);
    SceneViewportToolbar(const SceneViewportToolbar &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~SceneViewportToolbar(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    void handleSplitSelection(ActionEventDetails* const details);
    void handleFullscreenButton(ActionEventDetails* const details);
    void handleConfigurationButton(ActionEventDetails* const details);
    void handleFocusButton(ActionEventDetails* const details);
    void handleTranslateButton(ActionEventDetails* const details);
    void handleRotateButton(ActionEventDetails* const details);
    void handleScaleButton(ActionEventDetails* const details);
    void handleStatisticsButton(ActionEventDetails* const details);

    boost::signals2::connection _SplitSelectionConnection,
                                _FullscreenButtonConnection,
                                _ConfigurationButtonConnection,
                                _FocusButtonConnection,
                                _TranslateButtonConnection,
                                _RotateButtonConnection,
                                _ScaleButtonConnection,
                                _StatisticsButtonConnection;
    
    MenuButtonRecPtr  _SplitScrenMenuButton;
    ButtonRecPtr      _FullScreenButton;
    ButtonRecPtr      _ConfigurationButton;
    ButtonRecPtr      _FocusButton;
    ToggleButtonRecPtr      _TranslateButton;
    ToggleButtonRecPtr      _RotateButton;
    ToggleButtonRecPtr      _ScaleButton;
    ToggleButtonRecPtr      _StatisticsButton;
    

    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class SceneViewportToolbarBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const SceneViewportToolbar &source);
};

typedef SceneViewportToolbar *SceneViewportToolbarP;

OSG_END_NAMESPACE

#include "KESceneViewportToolbarBase.inl"
#include "KESceneViewportToolbar.inl"

#endif /* _KESCENEVIEWPORTTOOLBAR_H_ */
