/* Copyright (C) Johnny Saenz                                                 

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details. */

#ifndef TRISTAN_READ
# define TRISTAN_READ

#include <fstream>
#include <iostream>
#include "structs.h"
#include "globals.h"


namespace JSApm
{

    /**
     * Class to insert in memory the file to parse.
     */
    class Read
    {
	    public:

            Read(int idconf);
            ~Read();
            _node * get_begin();
            _node * new_node();

        private:

            /// Node that contains the pointer for the begin of the linked list.
            _node *begin;
            /// Node who represent the actual node.
            _node *index; 
            /// Node who represent the new created node.
            _node *temp; 
    };

}

#endif
