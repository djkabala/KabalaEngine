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
#include <OpenSG/OSGConfig.h>

#include "KEFieldContainerEditor.h"

OSG_BEGIN_NAMESPACE

void FieldContainerEditor::swapTarget(FieldContainerPtr Target)
{
    if(_Target != NullFC)
    {
        detachTarget();
    }

    setTarget(Target);

    if(_Target != NullFC)
    {
        attachTarget();
    }
}

void FieldContainerEditor::attachTarget(void)
{
    if(_Target != NullFC &&
       !_isAttached)
    {
        _isAttached = true;
    }
}

void FieldContainerEditor::detachTarget(void)
{
    if(_Target != NullFC &&
       _isAttached)
    {
        _isAttached = false;
    }
}

void FieldContainerEditor::setTarget(FieldContainerPtr Target)
{
    _Target = Target;
}

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

FieldContainerEditor::~FieldContainerEditor(void)
{
    detachTarget();
}

/*-------------------------------------------------------------------------*/
/*                             Comparison                                  */

OSG_END_NAMESPACE
