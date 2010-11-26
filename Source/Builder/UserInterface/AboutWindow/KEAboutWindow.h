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

#ifndef _KEABOUTWINDOW_H_
#define _KEABOUTWINDOW_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "KEKabalaEngineDef.h"

#include <OpenSG/OSGDialogWindowFields.h>
#include <OpenSG/OSGActionEventDetailsFields.h>
#include <OpenSG/OSGPathFields.h>

OSG_BEGIN_NAMESPACE

void KE_KABALAENGINE_DLLMAPPING openAboutWindow(void);
DialogWindowTransitPtr KE_KABALAENGINE_DLLMAPPING createAboutWindow(void);
DialogWindowTransitPtr KE_KABALAENGINE_DLLMAPPING loadAboutWindow(const BoostPath& WindowDefinitionFile);

void KE_KABALAENGINE_DLLMAPPING handleAboutWindowCloseButton(ActionEventDetails* const details,
                                                            DialogWindow* const TheAboutWindow);
OSG_END_NAMESPACE

#include "KEAboutWindow.inl"

#endif /* _KEABOUTWINDOW_H_ */
