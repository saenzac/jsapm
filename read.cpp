/* Copyright (C) Johnny Saenz                                                 

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details. */

#include "read.h"

namespace JSApm
{

    /**
     * @brief Constructor for Read class.
     * Insert AV_CONF_FILE or LOCAL_CONF_FILE in memory, in order to increase speed of reading.
     * @param idconf: (int) 1 or 2, 1 for AV_CONF_FILE file and 2 for LOCAL_CONF_FILE.
     */
    Read::Read(int idconf)
    {
	std::ifstream file;
        if ( idconf == 1 )
        {
            file.open(AV_CONF_FILE);
            if ( ! file )
            { 
                std::cout << "Error to open file " << AV_CONF_FILE << std::endl;
                exit(2);
            }
        }
        else if ( idconf == 2 )
        {
            file.open(LOCAL_CONF_FILE);
            if ( ! file )
            {
                std::cout << "Error to open file " << LOCAL_CONF_FILE << std::endl;
                exit(2);
            }
        }
        else
        {
            std::cout << "Incorrect value of idconf " << std::endl;
            exit(2);
        }

        begin = NULL;
        index = NULL;
        temp  = NULL;

        std::string buffer;
        int nline = 1;

        //Reading the file while return lines.
        while(!file.eof())
        {
            getline(file, buffer, '\n');

            //We created a new temporary node.
		    temp = new_node();

            //We verified if the index exists, if no, this new node becomes the index
            if (!index)
                index = temp;

            //We verified if the begin of the linked list exists, if no, this new node becomes the begin.
            if (!begin)
                begin = index;

            temp->line = new std::string;
            // We copied the line read within the node.
            (*temp->line).append(buffer); (*temp->line).append("\n");
            temp->nline = nline;
            nline++;


            // If the index is different from the weather, just we connected the nodes, if no, 
            // does not exist more that one node, so it is not necessary to connect nothing.
            if(index!=temp)
            {
                index->next = temp;
                index = temp;
             }
        }

        file.close();
    }

    /**
     * Member who return the begin(pointer) to the linked list.
     * @return Pointer at the beginning of the linked list.
     */
    _node * Read::get_begin()
    {
        return begin;
    }

    /**
     * Member who create a node for the linked list.
     * @return Pointer to the create node.
     */
    _node * Read::new_node()
    {
        //@DEL-L//
        _node *node_return;

        node_return = new _node[sizeof(struct __node)];

        //Initializing internal variable.
        node_return->line=NULL;
        node_return->next=NULL;

        return(node_return);
    }

    /*
     * Destroy memory allocation of the linked list.
     */
    Read::~Read()
    {
        // We cross the linked list, erasing the nodes.
        while ( begin != NULL )
        {
            index = begin->next;
            delete begin->line;
            delete begin;
            begin = index;
        }
    }
}
