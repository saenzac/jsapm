/* Copyright (C) Johnny Saenz                                                 

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details. */

#ifndef YAMSN_DEBUG_H
#define YAMSN_DEBUG_H

    class Debug
    {
    private:
        static void message_( int, const std::string& );
    public:
        static void Info( const std::string& );      // informational message
        static void Notice( const std::string& );    // normal, but significant, condition
        static void Warning( const std::string& );   // warning conditions
        static void Error( const std::string& );     // error conditions
    };

#endif
