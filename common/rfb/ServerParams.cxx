/* Copyright (C) 2002-2005 RealVNC Ltd.  All Rights Reserved.
 * Copyright (C) 2011 D. R. Commander.  All Rights Reserved.
 * Copyright 2014-2018 Pierre Ossman for Cendio AB
 * 
 * This is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this software; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307,
 * USA.
 */
#include <rfb/Exception.h>
#include <rfb/ledStates.h>
#include <rfb/ServerParams.h>

using namespace rfb;

ServerParams::ServerParams()
  : majorVersion(0), minorVersion(0),
    useCopyRect(false),
    supportsLocalCursor(false), supportsLocalXCursor(false),
    supportsLocalCursorWithAlpha(false),
    supportsDesktopResize(false), supportsExtendedDesktopSize(false),
    supportsDesktopRename(false), supportsLastRect(false),
    supportsLEDState(false), supportsQEMUKeyEvent(false),
    supportsSetDesktopSize(false), supportsFence(false),
    supportsContinuousUpdates(false),
    compressLevel(2), qualityLevel(-1),
    width_(0), height_(0), name_(0),
    ledState_(ledUnknown)
{
  setName("");
  cursor_ = new Cursor(0, 0, Point(), NULL);
}

ServerParams::~ServerParams()
{
  delete [] name_;
  delete cursor_;
}

void ServerParams::setDimensions(int width, int height)
{
  ScreenSet layout;
  layout.add_screen(rfb::Screen(0, 0, 0, width, height, 0));
  setDimensions(width, height, layout);
}

void ServerParams::setDimensions(int width, int height, const ScreenSet& layout)
{
  if (!layout.validate(width, height))
    throw Exception("Attempted to configure an invalid screen layout");

  width_ = width;
  height_ = height;
  screenLayout_ = layout;
}

void ServerParams::setPF(const PixelFormat& pf)
{
  pf_ = pf;

  if (pf.bpp != 8 && pf.bpp != 16 && pf.bpp != 32)
    throw Exception("setPF: not 8, 16 or 32 bpp?");
}

void ServerParams::setName(const char* name)
{
  delete [] name_;
  name_ = strDup(name);
}

void ServerParams::setCursor(const Cursor& other)
{
  delete cursor_;
  cursor_ = new Cursor(other);
}

void ServerParams::setLEDState(unsigned int state)
{
  ledState_ = state;
}
