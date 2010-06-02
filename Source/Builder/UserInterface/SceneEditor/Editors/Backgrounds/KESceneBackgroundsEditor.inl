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

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <OpenSG/OSGConfig.h>

OSG_BEGIN_NAMESPACE

inline
SceneBackgroundsEditor::BackgroundsListListener::BackgroundsListListener(SceneBackgroundsEditorPtr TheSceneBackgroundsEditor) :
	_SceneBackgroundsEditor(TheSceneBackgroundsEditor)
{
}
inline
SceneBackgroundsEditor::BackgroundCreateMenuButtonListener::BackgroundCreateMenuButtonListener(SceneBackgroundsEditorPtr TheSceneBackgroundsEditor) :
	_SceneBackgroundsEditor(TheSceneBackgroundsEditor)
{
}

inline
void SceneBackgroundsEditor::BackgroundCreateMenuButtonListener::setApplicationBuilder(ApplicationBuilderPtr TheApplicationBuilder)
{
    _ApplicationBuilder = TheApplicationBuilder;
}
inline
SceneBackgroundsEditor::BackgroundDeleteActionListener::BackgroundDeleteActionListener(SceneBackgroundsEditorPtr TheSceneBackgroundsEditor) :
	_SceneBackgroundsEditor(TheSceneBackgroundsEditor)
{
}

inline
void SceneBackgroundsEditor::BackgroundDeleteActionListener::setApplicationBuilder(ApplicationBuilderPtr TheApplicationBuilder)
{
    _ApplicationBuilder = TheApplicationBuilder;
}
inline
SceneBackgroundsEditor::BackgroundNameTextListener::BackgroundNameTextListener(SceneBackgroundsEditorPtr TheSceneBackgroundsEditor) :
	_SceneBackgroundsEditor(TheSceneBackgroundsEditor)
{
}

inline
void SceneBackgroundsEditor::BackgroundNameTextListener::setApplicationBuilder(ApplicationBuilderPtr TheApplicationBuilder)
{
    _ApplicationBuilder = TheApplicationBuilder;
}
OSG_END_NAMESPACE

