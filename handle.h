/* Copyright (C) Johnny Saenz                                                 

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details. */

#ifndef TRISTAN_HANDLE
# define TRISTAN_HANDLE

#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include "getinfo.h"
#include "utils.h"
#include "globals.h"
#include "structs.h"

namespace JSApm
{

    /**
     * @brief Class to entrust parse.
     * 
     * Class to entrust parse CONF_FILE,
     * in it looks for dependencies, for the argument package.
     */
    class Handle
    {
    public:	
        Handle();
        ~Handle();	
        candidates_struct handle_candidates(std::string package, std::string operate, std::string ver, int nline);
        void handle_dependencies(std::string package, std::string operate, std::string ver, int nline);
        void MsgError(std::map<std::string, meta>::iterator &iTmap);
        void checkRepeatPkg(std::map<std::string, meta>::iterator & iTmap);
        int isMoreEqualPkg(std::map<std::string, meta>::iterator & iTmap);
        void insertPkgInRecSaver(std::map<std::string, meta>::iterator & iTmap, std::vector<meta_final> & vector_target, int is_more_equal);
        candidates_struct parseOpAndFillCandStruct(std::vector<meta_final> & vector_origin);

    private:
        Utils     * objutils;
        GetInfo * objgetinfo_av;
        GetInfo * objgetinfo_lo;
        std::map<std::string, meta> rec_saver;
        int i;
    };
}

#endif
