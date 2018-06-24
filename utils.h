/* Copyright (C) Johnny Saenz                                                 

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details. */

#ifndef TRISTAN_UTILS
#define TRISTAN_UTILS

#include <iostream>
#include <string>
#include <vector>
#include <sstream>

namespace JSApm
{

    /**
     * @brief Class Utils.
     * 
     * Class who contains useful functions.
     */
    class Utils
    {
        public:
            Utils();
            ~Utils();
            void split_vec(std::string str, std::string delim, int lim, std::vector<std::string> &results);
            int transform_version(std::string version);
    };
}

#endif
