/* Copyright (C) Johnny Saenz                                                 

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details. */

#include "getinfo.h"

namespace JSApm
{
    tags _tags_opts[] = 
    {
        {"Version",     MAX_VER_LEN},
        {"Section",     MAX_SECTION_LEN},
        {"Depends",     MAX_DEP_LEN},
        {"Description", MAX_DSCR_LEN},
        {0, 0}
    };
    // We avoided problems of relink of memory.
    const tags *tags_opts = _tags_opts;

    /**
     * @brief Constructor for GetInfo class.
     * Initializes variables
     * @param idconf: (int) 1 or 2, 1 for get the pointer to the begin of the linked list,
     * pertaining to AV_CONF_FILE, and 2 for LOCAL_CONF_FILE.
     */
    GetInfo::GetInfo(int idconf)
    {
        debug = 0;

        objutils  = new Utils;
        objreadav = new Read(1);
        objreadlo = new Read(2);

        if ( idconf == 1 )
            begin = objreadav->get_begin();
        if ( idconf == 2 )
            begin = objreadlo->get_begin();

        found_tag_name   = false;
    }

    /**
     * Parse {AV|LOCAL}_CONF_FILE, searching package name.
     * @param package: Name of package.
     * @return "True" if the package found, and return "False" if not found.
     */
    bool GetInfo::ParsePkg(std::string package)
    {
        std::string package_tag = "Package: ";
        std::string esc_chr 	= "\n";
        std::string index_name 	= package_tag + package + esc_chr;

        index = begin;
        while( index != NULL )
        {
            if( !(*index->line).compare(index_name) )
            {
                index=index->next;
                return true;
            }
            index=index->next;
        }
        return false;
    }

    /**
     * Parse {AV|LOCAL}_CONF_FILE, searching a tag.
     * @param package: Name of package.
     * @param tag_name: Id for tag, defined in "tags_opts" variable.
     * @return "True" if the tag found, and return "False" if not found.
     */
    bool GetInfo::ParseTag(std::string package, int tag_name)
    {
        found_tag_name == false;
        std::string tag(tags_opts[tag_name].name); tag.append(":");
        if ( ParsePkg(package) )
        {
            while( index != NULL )
            {
                if ( !(*index->line).compare("\n") ) { break; }
                if ((*index->line).rfind(tag) != std::string::npos)
                {
                    boost::smatch what;	boost::regex reg;
                    // @<space>@:@ @<hexa>@\n@<hexa>.*@;
                    reg = "([^\\s]+): ([^\\W].*)\n";
                    if( boost::regex_match((*index->line), what, reg, boost::match_perl) )
                    {
                        found_tag_name = true;
                        index = index->next;
                        continue;
                    }
                    else
                    {
                        std::cout << "[BAD]" << std::endl;
                        std::cout << "Error of parsing,  line: " << index->nline << std::endl;
                    }
                }
                index = index->next;
            }
        }
        if ( found_tag_name ) { return true; }
        else { return false; };
    }

    /**
     * Parse {AV|LOCAL}_CONF_FILE, searching a tag.
     * @param package: Name of package.
     * @param tag_name: Id for tag, defined in "tags_opts" variable.
     * @param taginfo_o: Struct in that save the results of the search, tag.
     * @return "True" if the tag found, and return "False" if not found.
     */
    bool GetInfo::ParseTag(std::string package, int tag_name, taginfo &taginfo_o)
    {
        found_tag_name == false;
        std::string tag(tags_opts[tag_name].name);
        tag.append(":");
        if ( ParsePkg( package ) )
        {
            while( index != NULL )
            {
                if (!(*index->line).compare("\n")) { break; };
                if ((*index->line).rfind(tag) != std::string::npos)
                {
                    boost::smatch what;	boost::regex reg;
                    // @<space>@:@ @<hexa>@\n@<hexa>.*@;
                    reg = "([^\\s]+): ([^\\W].*)\n";
                    if( boost::regex_match((*index->line), what, reg, boost::match_perl) )
                    {
                        taginfo_o.content = what[2];
                        taginfo_o.nline = index->nline;
                        found_tag_name = true;
                        index = index->next;
                        continue;
                    }
                    else
                    {
                        std::cout << "[BAD]" << std::endl;
                        std::cout << "Error of parsing,  line: " << index->nline << std::endl;
					    exit(2);
				    }
                }
                if (tag_name == 3 && found_tag_name == true){(taginfo_o.content).append(*index->line);};
                index = index->next;
            }
            if ( found_tag_name ) { return true; }
            else { return false; };
        }
        else
        {
            std::cout << "[BAD]" << std::endl;
            std::cout << "Package not exists: " << package << std::endl;
            exit(2);
        }
    }

    /**
     * Verifies the existence of a package.
     * @param package: Name of package.
     * @return True if the package found, and return "False" if not found.
     */
    bool GetInfo::PkgExist(std::string package)
    {
	    if ( ParsePkg(package) ){ return true; }
        else { return false; };
    }

    /**
     * Verifies the existence of a tag.
     * @param package: Name of package.
     * @param tag_name: Id for tag, defined in "tags_opts" variable.
     * @return True if the tag found, and return "False" if not found.
     */
    bool GetInfo::TagExist(std::string package, int tag_name)
    {
        if ( ParseTag(package, tag_name) ) {return true; }
        else { return false; };
    }


    /**
     * Member that return and save information for a tag in the respective variables.
     * @param package: Name of package.
     * @param tag_name: Id for tag, defined in "tags_opts" variable.
     * @param results_o: Variable in that save the content of the tag.
     * @param nline_o: Variable in that save the line number of the tag.
     * @return True if the tag found, and return "False" if not found.
     */
    bool GetInfo::GetPkgTag(std::string package, int tag_name, std::string &results_o, int &nline_o)
    {
        taginfo taginfo_o;
        bool return_code = ParseTag(package, tag_name, taginfo_o);
        results_o = taginfo_o.content;
        nline_o	  = taginfo_o.nline;
        return return_code;
    }

    /**
     * Member that return and save information for a tag in the respective variables.
     * @param package: Name of package.
     * @param tag_name: Id for tag, defined in "tags_opts" variable.
     * @param results_o: Variable in that save the content of the tag.
     * @return True if the tag found, and return "False" if not found.
     */
    bool GetInfo::GetPkgTag(std::string package, int tag_name, std::string &results_o)
    {
        taginfo taginfo_o;
        bool return_code = ParseTag(package, tag_name, taginfo_o);
        results_o = taginfo_o.content;
        return return_code;
    }

    /**
     * Member that save information in a vector, about the dependencies.
     * @param package: Name of package.
     * @param vector_depends: Dependencies of package.
     */
    void GetInfo::get_DependsMap(std::string package, std::vector<Programa> &vector_depends)
    {
        std::string depends;
        int out_code;
        int nline;

        out_code = GetPkgTag(package, 2, depends, nline);

        if ( out_code )
        {
            std::vector<std::string> split_depends;
            objutils->split_vec(depends, ", ", MAX_DEP_GROUP_LEN, split_depends);

            int m = 0;
            while ( m <  split_depends.size() )
            {
                Programa prog;
                boost::smatch what; boost::regex reg;
                reg = "([^\\s]+) \\(([^\\s]+) ([^\\)]+)\\)";
                if( boost::regex_match(split_depends[m], what, reg, boost::match_perl) )
                {
                   //Programa * prog = new Programa();
                   prog.name	= what[1];
                   prog.op 	= what[2];
                   prog.ver 	= what[3];
                   prog.nline	= nline;
                   vector_depends.push_back(prog);
                    m++;
                }
                else
                {
                   std::cout << "[BAD]" << std::endl;
                    std::cout << "Error of parsing,  line: " << nline <<std::endl;
                    std::cout << "Download again: " << AV_CONF_FILE << " and it tries again" << std::endl;
                    exit (2);
                }
            }
	    }
    }


    GetInfo::~GetInfo()
    {
        delete objreadav;
        delete objreadlo;
        delete objutils;
    }
}
