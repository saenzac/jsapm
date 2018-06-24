/* Copyright (C) Johnny Saenz                                                 

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details. */

#ifndef OPERATOR_FUNCT
#define OPERATOR_FUNCT

#include "utils.h"
Utils objutils;

bool operator <(const tmplst_nline& a, const tmplst_nline& b)
{
	int opint_a;
	int opint_b;
	if ( !a.operate.compare("<=")) { opint_a = 0; }; if ( !b.operate.compare("<=")) { opint_b = 0; };
	if ( !a.operate.compare(">=")) { opint_a = 1; }; if ( !b.operate.compare(">=")) { opint_b = 1; };
	if ( !a.operate.compare("="))  { opint_a = 2; }; if ( !b.operate.compare("="))  { opint_b = 2; };
	
	return (objutils.transform_version(a.version)+opint_a) < (objutils.transform_version(b.version)+opint_b);
}

bool operator ==(const tmplst_nline& a, const tmplst_nline& b)
{
	return (a.version + a.operate) == (b.version + b.operate);
}
#endif
