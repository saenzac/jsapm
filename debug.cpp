/* Copyright (C) Johnny Saenz

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details. */

#include <iostream>
#include "debug.h"

#define ACTUAL_LEVEL 0

// Constants
namespace
{
    const int INFO    = 1;
    const int NOTICE  = 2;
    const int WARNING = 4;
    const int ERROR   = 8;
}

    //  Debug::message_
    // --------------------------------------------------------------------
    //
    void Debug::message_( int level, const std::string& debug_message )
    {
        if( level <= ACTUAL_LEVEL )
            std::cerr << "|Debug::Info    | " << debug_message << std::endl;
        else if( level <= ACTUAL_LEVEL )
            std::cerr << "|Debug::Notice  | " << debug_message << std::endl;
        else if( level <= ACTUAL_LEVEL )
            std::cerr << "|Debug::Warning | " << debug_message << std::endl;
        else if( level <= ACTUAL_LEVEL )
            std::cerr << "|Debug::Error   | " << debug_message << std::endl;
    }
    
 
    //  Debug::Info
    // --------------------------------------------------------------------
    //
    void Debug::Info( const std::string& m )
    {
        message_( INFO, m );
    }


    //  Debug::Notice
    // --------------------------------------------------------------------
    //
    void Debug::Notice( const std::string& m )
    {
        message_( NOTICE, m );
    }

    
    //  Debug::Warning
    // --------------------------------------------------------------------
    //
    void Debug::Warning( const std::string& m )
    {
        message_( WARNING, m );
    }


    //  Debug::Error
    // --------------------------------------------------------------------
    //
    void Debug::Error( const std::string& m )
    {
        message_( ERROR, m );
    }
