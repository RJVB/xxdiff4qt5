/* -*- c-file-style: "xxdiff" -*- */
/******************************************************************************\
 * $RCSfile$
 *
 * Copyright (C) 1999-2003  Martin Blais <blais@furius.ca>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 ******************************************************************************/

#ifndef INCL_XXDIFF_VERSION
#define INCL_XXDIFF_VERSION

/*==============================================================================
 * PUBLIC DECLARATIONS
 *============================================================================*/

/*
 * Version number. Compiled in version.c everytime we link.
 */
#ifdef	__cplusplus
extern "C" {
#endif

extern char const xx_name[];
extern char const xx_version[];
extern char const xx_description[];
extern char const xx_copyright[];
extern char const xx_homepage[];
extern char const xx_bugs_email[];

#ifdef	__cplusplus
}
#endif

#endif
