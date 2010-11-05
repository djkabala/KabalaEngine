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

#ifndef _KESCENEVIEWPORTPANEL_H_
#define _KESCENEVIEWPORTPANEL_H_
#ifdef __sgi
#pragma once
#endif

#include "KESceneViewportPanelBase.h"

#include <OpenSG/OSGCardLayoutFields.h>
#include "KESceneEditingViewportFields.h"
#include <OpenSG/OSGListSelectionEventDetailsFields.h>
#include <OpenSG/OSGManipulatorManager.h>

OSG_BEGIN_NAMESPACE

/*! \brief SceneViewportPanel class. See \ref
           PageKabalaEngineSceneViewportPanel for a description.
*/

class KE_KABALAENGINE_DLLMAPPING SceneViewportPanel : public SceneViewportPanelBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:
    enum SplitModes
    {
        SPLIT_NONE = 0,
        SPLIT_ONE_BY_TWO = 1,
        SPLIT_TWO_BY_ONE = 2,
        SPLIT_TWO_BY_TWO = 3,
    };

    typedef SceneViewportPanelBase Inherited;
    typedef SceneViewportPanel     Self;

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

    void setSplitMode(UInt32 Mode);
    UInt32 getSplitMode(void) const;
    
	void selectNode(Node* SelectNode);
    void focusNode(Node* TheNode);
    void focusSelectedNodes(void);

    void setManipulatorType(ManipulatorManager::ManipulatorType Type);
    ManipulatorManager::ManipulatorType getManipulatorType(void) const;

    void setStatisticsEnabled(bool enable);
    bool getStatisticsEnabled(void) const;
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in SceneViewportPanelBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    SceneViewportPanel(void);
    SceneViewportPanel(const SceneViewportPanel &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~SceneViewportPanel(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    void handleSelectedSceneChanged(ListSelectionEventDetails* const details);

    boost::signals2::connection _SceneSelectionConnection;

    UInt32 _SplitMode;
    
    CardLayoutRecPtr _SplitModeSelectionCard;

    //No Split
    SceneEditingViewportRecPtr _NoSplitViewport;

    // 1 x 2
    SceneEditingViewportRecPtr _OneByTwoLeftViewport,
                     _OneByTwoRightViewport;

    // 2 x 1
    SceneEditingViewportRecPtr _TwoByOneTopViewport,
                     _TwoByOneBottomViewport;

    // 2 x 2
    SceneEditingViewportRecPtr _TwoByTwoTopLeftViewport,
                     _TwoByTwoTopRightViewport,
                     _TwoByTwoBottomLeftViewport,
                     _TwoByTwoBottomRightViewport;

    void attachSplitModeViewports(void);
    void dettachSplitModeViewports(void);
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class SceneViewportPanelBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const SceneViewportPanel &source);
};

typedef SceneViewportPanel *SceneViewportPanelP;

OSG_END_NAMESPACE

#include "KESceneViewportPanelBase.inl"
#include "KESceneViewportPanel.inl"

#endif /* _KESCENEVIEWPORTPANEL_H_ */
