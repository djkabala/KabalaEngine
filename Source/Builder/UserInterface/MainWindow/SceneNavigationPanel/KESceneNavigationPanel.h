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

#ifndef _KESCENENAVIGATIONPANEL_H_
#define _KESCENENAVIGATIONPANEL_H_
#ifdef __sgi
#pragma once
#endif

#include "KESceneNavigationPanelBase.h"

#include "Project/Scene/KESceneFields.h"
#include "Project/KEProjectEventDetailsFields.h"
#include <OpenSG/OSGFocusEventDetailsFields.h>
#include <OpenSG/OSGButtonFields.h>
#include <OpenSG/OSGPanelFields.h>
#include <OpenSG/OSGLabelFields.h>
#include <OpenSG/OSGTextureObjChunkFields.h>
#include <OpenSG/OSGActionEventDetailsFields.h>
#include <OpenSG/OSGMouseEventDetailsFields.h>
#include <OpenSG/OSGFocusEventDetailsFields.h>
#include <OpenSG/OSGListSelectionEventDetailsFields.h>
#include <OpenSG/OSGUIViewportFields.h>
#include <OpenSG/OSGCommandManager.h>

#include <map>

OSG_BEGIN_NAMESPACE

/*! \brief SceneNavigationPanel class. See \ref
           PageKabalaEngineSceneNavigationPanel for a description.
*/

class KE_KABALAENGINE_DLLMAPPING SceneNavigationPanel : public SceneNavigationPanelBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef SceneNavigationPanelBase Inherited;
    typedef SceneNavigationPanel     Self;

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

    void selectScene(Scene* const TheScene);
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in SceneNavigationPanelBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    SceneNavigationPanel(void);
    SceneNavigationPanel(const SceneNavigationPanel &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~SceneNavigationPanel(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    PanelTransitPtr createSceneThumbnail(Scene* const TheScene);
    void createSceneThumbnails(void);
    void clearSceneThumbnails(void);
    void updateSceneThumbnail(Scene* const TheScene);

    void handleSceneSelected(Scene* const TheScene);
    void handleSceneDeselected(Scene* const TheScene);
    void handleSceneAddRemove(Scene* const TheScene);
    void handleSceneChanged(Scene* const TheScene);

    void handleScenesChanged(ProjectEventDetails* const details);
    void handleSelectedSceneChanged(ListSelectionEventDetails* const details);

    void handleSceneThumbFocused(FocusEventDetails* const details,
                                 Scene* const TheScene);
    void handleSceneRemoved(ActionEventDetails* const details,
                            Scene* const TheScene);
    void handleSceneThumbEntered(MouseEventDetails* const details,
                             Scene* const TheScene);
    void handleSceneThumbExited(MouseEventDetails* const details,
                             Scene* const TheScene);
    void handleCreateSceneButton(ActionEventDetails* const details);

    void updatePreferredSize(void);

    void attachSceneThumbs(void);
    void dettachSceneThumbs(void);

    boost::signals2::connection _CreateSceneConnection,
                                _ScenesChangedConnection,
                                _SceneSelectionConnection;

    std::vector<boost::signals2::connection> _SceneThumbConnections;

    ButtonRecPtr _CreateSceneButton;
    PanelRecPtr _DefaultSceneThumbPanel;
    PanelRecPtr _SceneNavigationPanel;
    UIViewportRecPtr _SceneNavigationViewport;

    struct ThumbComp
    {
        Panel* _Panel;
        Label* _NameLabel;
        Button* _RemoveButton;
        Button* _ThumbButton;
    };

    typedef std::map<Scene*, ThumbComp> SceneToThumbMap;
    typedef SceneToThumbMap::iterator SceneToThumbMapItor;
    typedef SceneToThumbMap::const_iterator SceneToThumbMapConstItor;
    SceneToThumbMap _SceneToThumbMap;

    CommandManagerPtr _TheCommandManager;

    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class SceneNavigationPanelBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const SceneNavigationPanel &source);
};

typedef SceneNavigationPanel *SceneNavigationPanelP;

OSG_END_NAMESPACE

#include "KESceneNavigationPanelBase.inl"
#include "KESceneNavigationPanel.inl"

#endif /* _KESCENENAVIGATIONPANEL_H_ */
