/* Copyright (C) Johnny Saenz                                                 

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details. */

#ifndef TRISTAN_GETINFO
# define TRISTAN_GETINFO

#include <boost/regex.hpp>
#include <stdlib.h>
#include <stdio.h>

#include "structs.h"
#include "utils.h"
#include "read.h"
#include "globals.h"

namespace JSApm
{

    /**
     * @brief Class GetInfo.
     * Parse AV_CONF_FILE or LOCAL_CONF_FILE and return information like the version, 
     * description, operator, line number and other.
     */
    class GetInfo
    {

    public:
        GetInfo(int idconf);
        ~GetInfo();
        bool ParsePkg(std::string package);
        bool ParseTag(std::string package, int tag_name);
        bool ParseTag(std::string package, int tag_name, taginfo &taginfo_o);
        bool PkgExist(std::string package);
        bool TagExist(std::string, int tag_name);
        bool GetPkgTag(std::string package, int tag_name, std::string &results_o, int &nline_o);
        bool GetPkgTag(std::string package, int tag_name, std::string &results_o);
        void get_DependsMap(std::string package, std::vector<Programa> &vector_depends);

    private: 
        Utils * objutils;
        Read  * objreadav;
        Read  * objreadlo;
        std::string results;	//Contenido de un tag.
        bool found_tag_name;	//Flag que se activa si se encuentra tag
        _node * begin;
        _node * index;
        _node * temp;
        int  debug;				//Flag que activa o desactiva el debug
    };

    extern const tags *tags_opts;
}

#endif
