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


/*! \mainpage  apt (debian) style package manager engine
 *
 * Utility that parse a file database to solve dependencies or conflicts from another packages by using a series of algorithms.
 * Basically it reads the database which consist in the file "available.txt" and generates the dependencies from it.

 *In it's current state it doesn't perform an actual installation of the packages.
*/
int main()
{
	JSApm::UserInter *objuserinter;
	objuserinter = new JSApm::UserInter;

	std::string package;
	std::cout << "Enter the package name" << std::endl;
	std::cin >> package;

	objuserinter->Install(package);
	
	delete objuserinter;
}
