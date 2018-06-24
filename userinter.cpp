/* Copyright (C) Johnny Saenz                                                 

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details. */

#include "userinter.h"

namespace JSApm
{
    UserInter::UserInter()
    {
        objhandle = new Handle;
    }

    void UserInter::Install(std::string package)
    {
        candidates_struct candidates = objhandle->handle_candidates(package, "", "", 0);

        if ( candidates.candidates_new.size() != 0 )
        {
            std::cout << "\nThe following packages are going to be installed:" << std::endl;
            std::vector<std::string>::const_iterator cig;
            for(cig=candidates.candidates_new.begin(); cig!=candidates.candidates_new.end(); cig++)
            {
                std::cout << *cig << " ";
            }
        }

        if ( candidates.candidates_revupgrade.size() != 0 )
        {
            std::cout << "\nThe following packages will be outdated:" << std::endl;
            std::vector<std::string>::const_iterator cig;
            for(cig=candidates.candidates_revupgrade.begin(); cig!=candidates.candidates_revupgrade.end(); cig++)
            {
                std::cout << *cig << " ";
            }
        }
	
        if ( candidates.candidates_upgrade.size() != 0 )
        {
            std::cout << "\nThe following packages are going to be updated:" << std::endl;
            std::vector<std::string>::const_iterator cig;
            for(cig=candidates.candidates_upgrade.begin(); cig!=candidates.candidates_upgrade.end(); cig++)
            {
                std::cout << *cig << " ";
            }
        }

        std::cout << "\n\n";
        std::cout << candidates.candidates_upgrade.size() << " to upgrade, ";
        std::cout << candidates.candidates_new.size() 	 << " new ";

        std::cout << "\n\nDo you want to continue?: (y/n) ";
        std::string answ;
        std::cin >> answ;
    }

    UserInter::~UserInter()
    {
    	delete objhandle;
    }
}
