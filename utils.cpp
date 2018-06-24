/* Copyright (C) Johnny Saenz                                                 

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details. */

#include "utils.h"

namespace JSApm
{

    /**
     * Constructor for class Util.
     */
    Utils::Utils()
    {
    }

    /**
     * Split a string and store the results in a vector.
     * @param str: String to split.
     * @param delim: String who delimite the split.
     * @param lim: Number to limit the lentgh of the string to split.
     * @param results: Vector in that save the cut string.
     */
    void Utils::split_vec(std::string str, std::string delim, int lim, std::vector<std::string> &results)
    {
        if ( (int)(str).length() > lim )
        {
		    std::cout << "String to split is too large. Exiting..." << std::endl;
            exit(1);
        }

        int cutAt;
        while( (cutAt = str.find(delim)) != str.npos )
        {
		    if(cutAt > 0)
		    {
			    results.push_back(str.substr(0,cutAt));
		    }

		    str = str.substr( cutAt + delim.length() );
	    }

	    if(str.length() > 0)
	    {
		    results.push_back(str);
	    }
    }

    /**
     * Transform version in a number, without ".", "-", and other characters.
     * @param version: String to transform.
     * @return Transformed version.
     */
    int Utils::transform_version(std::string version)
    {
	    int i=0, y=0, z=0;
	    int transformed;
	    std::string tmp1;
	    std::string tmp2;
	    std::string tmp3;

        tmp1 = version;
        /* strip dots, '-' and '_' */
        for(i=0; i < tmp1.size() && tmp1[i] != '\0'; i++)
        {
		    if( tmp1[i] != '.' && tmp1[i] != '-' && tmp1[i] != '_'
		    && tmp1[i] != '\r' && tmp1[i] != '\n' && tmp1[i] != ' ' )
		    {
			    tmp2.push_back(tmp1[i]);
			    y++;
		    }
	    }

        // Add 1 to all digits and translate chars to digits //
        z=0;
        for(i=0; i< tmp2.size() && tmp2[i] != '\0'; i++)
	    {
		    // Digits //
		    if( tmp2[i] == '0' )
			    tmp3.push_back('1');

		    if( tmp2[i] == '1' )
                tmp3.push_back('2');

            if( tmp2[i] == '2' )
			    tmp3.push_back('3');

            if( tmp2[i] == '3' )
			    tmp3.push_back('4');

            if( tmp2[i] == '4' )
			    tmp3.push_back('5');

            if( tmp2[i] == '5' )
                tmp3.push_back('6');

            if( tmp2[i] == '6' )
                tmp3.push_back('7');

            if( tmp2[i] == '7' )
                tmp3.push_back('8');

            if( tmp2[i] == '8' )
                tmp3.push_back('9');

            if( tmp2[i] == '9' )
            {
			    tmp3.push_back('1'); ++z; tmp3.push_back('0');
            }

            //Chars 
            if( tmp2[i] == 'A' || tmp2[i] == 'a' )
                tmp3.push_back('1');

            if( tmp2[i] == 'B' || tmp2[i] == 'b' )
                tmp3.push_back('2');

            if( tmp2[i] == 'C' || tmp2[i] == 'c' )
                tmp3.push_back('3');

            if( tmp2[i] == 'D' || tmp2[i] == 'd' )
                tmp3.push_back('4');

            if( tmp2[i] == 'E' || tmp2[i] == 'e' )
                tmp3.push_back('5');

            if( tmp2[i] == 'F' || tmp2[i] == 'f' )
                tmp3.push_back('6');

            if( tmp2[i] == 'G' || tmp2[i] == 'g' )
                tmp3.push_back('7');

            if( tmp2[i] == 'H' || tmp2[i] == 'h' )
                tmp3.push_back('8');

            if( tmp2[i] == 'I' || tmp2[i] == 'i' )
                tmp3.push_back('9');

            if( tmp2[i] == 'J' || tmp2[i] == 'j' )
            {
                tmp3.push_back('1'); ++z; tmp3.push_back('0');
            }
		
            if( tmp2[i] == 'K' || tmp2[i] == 'k' )
            {
                tmp3.push_back('1'); ++z; tmp3.push_back('1');
            }
		
            if( tmp2[i] == 'L' || tmp2[i] == 'l' )
            {
                tmp3.push_back('1'); ++z; tmp3.push_back('2');
            }
	
            if( tmp2[i] == 'M' || tmp2[i] == 'm' )
            {
                tmp3.push_back('1'); ++z; tmp3.push_back('3');
            }
	
            if( tmp2[i] == 'N' || tmp2[i] == 'n' )
            {
                tmp3.push_back('1'); ++z; tmp3.push_back('4');
            }
	
            if( tmp2[i] == 'O' || tmp2[i] == 'o' )
            {
                tmp3.push_back('1'); ++z; tmp3.push_back('5');
            }
	
            if( tmp2[i] == 'P' || tmp2[i] == 'p' )
            {
                tmp3.push_back('1'); ++z; tmp3.push_back('6');
            }
	
            if( tmp2[i] == 'Q' || tmp2[i] == 'q' )
            {
                tmp3.push_back('1'); ++z; tmp3.push_back('7');
            }
	
            if( tmp2[i] == 'R' || tmp2[i] == 'r' )
            {
                tmp3.push_back('1'); ++z; tmp3.push_back('8');
            }
	
            if( tmp2[i] == 'S' || tmp2[i] == 's' )
            {
                tmp3.push_back('1'); ++z; tmp3.push_back('9');
            }
	
            if( tmp2[i] == 'T' || tmp2[i] == 't' )
            {
                tmp3.push_back('2'); ++z; tmp3.push_back('0');
            }
	
            if( tmp2[i] == 'U' || tmp2[i] == 'u' )
            {
                tmp3.push_back('2'); ++z; tmp3.push_back('1');
            }
	
            if( tmp2[i] == 'V' || tmp2[i] == 'v' )
            {
                tmp3.push_back('2'); ++z; tmp3.push_back('2');
            }
	
            if( tmp2[i] == 'W' || tmp2[i] == 'w' )
            {
                tmp3.push_back('2'); ++z; tmp3.push_back('3');
            }

            if( tmp2[i] == 'X' || tmp2[i] == 'x' )
            {
                tmp3.push_back('2'); ++z; tmp3.push_back('4');
            }
	
            if( tmp2[i] == 'Y' || tmp2[i] == 'y' )
            {
                tmp3.push_back('2'); ++z; tmp3.push_back('5');
            }
		
            if( tmp2[i] == 'Z' || tmp2[i] == 'z' )
            {
                tmp3.push_back('2'); ++z; tmp3.push_back('6');
            }

            ++z;
        }

        std::stringstream ss(tmp3);
        ss >> transformed;

        return transformed;
    }

    Utils::~Utils()
    {
    }

}
