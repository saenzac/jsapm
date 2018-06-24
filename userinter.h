/* Copyright (C) Johnny Saenz                                                 

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details. */

#ifndef TRISTAN_USERINTER
# define TRISTAN_USERINTER

#include "handle.h"

namespace JSApm
{
    class UserInter
    {
    public:
        UserInter();
        ~UserInter();
        void Install(std::string);

    private:
        Handle *objhandle;
    };
}

#endif
