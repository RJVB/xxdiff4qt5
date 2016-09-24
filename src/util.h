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

#ifndef INCL_XXDIFF_UTIL
#define INCL_XXDIFF_UTIL

/*==============================================================================
 * EXTERNAL DECLARATIONS
 *============================================================================*/

#ifndef INCL_XXDIFF_DEFS
#include <defs.h>
#endif

#ifndef INCL_QT_QSTRING
#include <QtCore/QString>
#define INCL_QT_QSTRING
#endif

#ifndef INCL_QT_QFILEINFO
#include <QtCore/QFileInfo>
#define INCL_QT_QFILEINFO
#endif

#ifndef INCL_QT_QSTRINGLIST
#include <QtCore/QStringList>
#define INCL_QT_QSTRINGLIST
#endif

#ifndef INCL_STD_STDIO
#include <stdio.h>
#define INCL_STD_STDIO
#endif

#ifndef INCL_STD_SIGNAL
#include <signal.h>
#define INCL_STD_SIGNAL
#endif

#ifndef INCL_STD_IOSTREAM
#include <iostream>
#define INCL_STD_IOSTREAM
#endif


XX_NAMESPACE_BEGIN

/*==============================================================================
 * CLASS XxUtil
 *============================================================================*/

// <summary> utilities </summary>

class XxUtil {

public:

   /*----- static member functions -----*/

   // Copy a stream to a file.
   static void copyToFile( FILE* fin, FILE* fout );

   // Copy a file.
   // Destination may be a directory name or a filename.
   // Returns 0 if no error (see pclose(3)).
   static int copyFile( const QString& src, const QString& dest );

   // Remove a file.
   // Returns 0 if no error.
   static int removeFile( const QString& src );

   // Conduct some tests to determine if the input file is suitable for
   // processing by our program.  Return true on success.
   static bool testFile(
      const QString& filename,
      bool           testAscii,
      bool&          isDirectory
   );
   static bool testFile(
      const QString&   filename,
      const QFileInfo& finfo,
      bool             testAscii,
      bool&            isDirectory
   );

   // Quick heuristic to test whether a file's contents are ascii text
   static bool isAsciiText( const QString& filename );

   // This is code for an interruptible system() call as shown as suggested in
   // GNU libc/Linux system(3) man page.
   static int interruptibleSystem( const QString& command );

   // Time snapshot (extremely rudimentary, modulo 100 seconds)
   static long getCurrentTime();

   // Print time value to stream.
   static void printTime( std::ostream& os, long time );

    // Take the command, filenames, buffer titles, and executable as input and
    // build a list of arguments that can be passed to exec() in 'out_args'.
   static void splitArgs(
      const QString&     command,
      const QStringList& filenames,
      QString&           executable,
      QStringList&       out_args
   );
   static void splitArgs(
      const QString&     command,
      const QString *    titles[3],
      const QStringList& filenames,
      QString&           executable,
      QStringList&       out_args
   );

   // Remove ClearCase extension to filename if it is present.
   static QString removeClearCaseExt( const QString& );

   // Formats user provided format much like GNU coreutils version of stat(2).
   // Performs stat(2)-like %-format sequencing for display names. Output will
   // be in target.  Returns true if success.
   static bool formatFilename(
      QString&         target,
      const QString&   masterformat,
      const QFileInfo& finfo,
      bool             isStdin,
      const QString&   filename,
      bool             newest = false
   );

   // Convert QDateTime to time_t.  This is required only for compatibility with
   // older versions of Qt.
   static unsigned int toTime_t( const QDateTime& t );

   // Escape and unescape chars.
   // <group>
   static QString escapeChars( const QString& format );
   static QString unescapeChars( const QString& format );
   // </group>

   // Create a new temporary file.
   static FILE* tempfile( char* tmplate );

};


XX_NAMESPACE_END

#endif
