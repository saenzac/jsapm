/* Copyright (C) Johnny Saenz                                                 

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details. */

#include "handle.h"

namespace JSApm
{

    /**
     * Constructor for handle class.
     */
    Handle::Handle()
    {
        //@Del-l//
        objgetinfo_av    =    new GetInfo(1);
        //@Del-l//
        objgetinfo_lo    =    new GetInfo(2);
        //@Del-l//
        objutils         =    new Utils;
        i = 0;
    }

    /**
     * Takes an integer and squares it
     * @param package: Name of package
     * @param operate: The operate, default is "0"
     * @param ver:     The version, default is "0"
     * @param nline:   The nline,   default is  0
     * @return The struct who contents list of candidates for upgrade, install and revupgrade
     */
    candidates_struct Handle::handle_candidates(std::string package, std::string operate, std::string ver, int nline)
    {
        std::cout << "Gathering dependencies...";
        handle_dependencies(package, operate, ver, nline);
        std::cout << "[OK]" << std::endl;

    	// Vector who contents the final list of packages, results of the handle_dependencies function.
    	std::vector<meta_final> rec_saver_final;

    	std::cout << "Verifying conflicts...";
    	for (std::map<std::string, meta>::iterator iTmap = rec_saver.begin(); iTmap != rec_saver.end(); iTmap++)
    	{
            checkRepeatPkg(iTmap);
            insertPkgInRecSaver(iTmap, rec_saver_final, isMoreEqualPkg(iTmap));

            // Litle progress bar.
            std::cout << ".";
            std::cout << std::flush;
        }
        std::cout << "[OK]" << std::endl;

        std::cout << "Generating candidates...";
        candidates_struct candidates_obj = parseOpAndFillCandStruct(rec_saver_final);
        std::cout << "[OK]" << std::endl;

        return candidates_obj;
    }

    /**
     * Mmember that generate rec_saver map, who contains dependencies with aditional information.
     * @param package: Name of package
     * @param operate: The operate, default is "0"
     * @param version: The version, default is "0"
     * @param nline: The nline,   default is  0
     */
    void Handle::handle_dependencies(std::string package, std::string operate, std::string version, int nline)
    {
        std::map<std::string, meta>::iterator iTrec_saver;
        for (iTrec_saver = rec_saver.begin(); iTrec_saver != rec_saver.end(); iTrec_saver++)
        {
            //Exit if the package limit is reached
            if( i >= MAX_PKG_NUM-1 )
            {
                std::cout << "Maximum number of dependencies reached" << std::endl;
                exit(2);
            }

            meta meta_tmp;
            std::map<std::string, meta>::iterator iTpackage  = rec_saver.find(package);
            if ( iTpackage != rec_saver.end() )
            {
                //copiamos el meta.data(que es un std::map) del actual iterador a meta_tmp
                meta_tmp.data = (*iTpackage).second.data;
                //insertamos si es que no existen los nuevos elementos s meta_tmp.
                meta_tmp.data[make_pair(version, operate)] = nline;
                //insertamos meta_tmp a rec_saver, reemplazando el contenido del antiguo indice
                rec_saver[package] = meta_tmp;
                i++;
                return;
            }
            i++;
        }

        /***	
         Reservamos memoria dinamica
        ***/
        if ( version != "" && operate != "" && nline != 0 )
        {
            meta meta_obj;
            meta_obj.data[make_pair(version, operate)] = nline;
            rec_saver[package] = meta_obj;
            std::cout << ".";
            std::cout << std::flush;
        }
        else if( version == "" && operate == "" && nline == 0 )
        {
            meta meta_obj;
            std::string version; 
            if ( ! objgetinfo_av->GetPkgTag(package, 0, version) )
            {
                std::cout << "[BAD]" << std::endl;
                std::cout << "Tag not found" << std::endl;
                exit(2);
            }
            meta_obj.data[make_pair(version, "=")] = -1;
            rec_saver[package] = meta_obj;
            std::cout << ".";
            std::cout << std::flush;
        }

        /***
         Mostramos una "barrita de progreso".
        ***/
	
        std::vector<Programa> vector_map;
        objgetinfo_av->get_DependsMap(package, vector_map);
        std::vector<Programa>::iterator it = vector_map.begin();

        /***
         Loop que llama en forma recursiva a esta funcion.
        ***/
        while( it != vector_map.end() )
      	{
            handle_dependencies((*it).name, (*it).op, (*it).ver, (*it).nline);
            it++;
        }
    }

    void Handle::MsgError(std::map<std::string, meta>::iterator &iTmap)
    {
        std::cout << "[BAD]" << std::endl;
        std::cout << "\n" << "* " << (*iTmap).first << std::endl;
        for (std::map<std::pair<std::string, std::string>, int>::iterator iT = (*iTmap).second.data.begin();
        iT != (*iTmap).second.data.end(); iT++)
        {
            if ( (*iT).second == -1 )
            {
                std::cout << "[version]  -> '" << (*iT).first.first  << "'\t";
                std::cout << "[operator] -> '" << (*iT).first.second << "'\t";
                std::cout << "[origin] -> '"   << (*iTmap).first     << "(group)'" << std::endl;
            }
            else
            {
                std::cout << "[version]  -> '" << (*iT).first.first  << "'\t";
                std::cout << "[operator] -> '" << (*iT).first.second << "'\t";
                std::cout << "[origin] -> '"   << (*iT).second       << "(line)'" << std::endl;
            }
        }
        std::cout << "\n";
        exit(2);
    }

    void Handle::checkRepeatPkg(std::map<std::string, meta>::iterator & iTmap)
    {
        // First phase
        // Iterator for the std::map, who is in to the struct "meta"
        std::map<std::pair<std::string, std::string>, int>::iterator iTdata = (*iTmap).second.data.begin();
        for(++iTdata; iTdata != (*iTmap).second.data.end(); iTdata++)
        {
            iTdata--;
            std::map<std::pair<std::string, std::string>, int>::iterator iTtmp = iTdata;
            iTdata++;
            if ( (*iTtmp).first.first == (*iTdata).first.first )
            {
                ((*iTmap).second.data).erase(iTtmp);
                std::string version_tmp = (*iTdata).first.first;
                int nline_tmp = (*iTdata).second;
                ((*iTmap).second.data).erase(iTdata);
                (*iTmap).second.data[std::make_pair(version_tmp, "=")] = nline_tmp;
            }
        }
    }

    int Handle::isMoreEqualPkg(std::map<std::string, meta>::iterator & iTmap)
    {
        // Second phase
        // return: is_more_equal
        int back_is = 0; // "ge"==1; "le"==2; "ee"==3
        int is_more_equal = 0;
        // Iterator for the std::map, who is in to the struct "meta"
        std::map<std::pair<std::string, std::string>, int>::iterator iTdata;
        iTdata = (*iTmap).second.data.begin();
        for (iTdata; iTdata != (*iTmap).second.data.end(); iTdata++)
        {
            if ( ! (*iTdata).first.second.compare(">=") )
            {
                if ( back_is == 1 )	{ continue; } /*OK*/ 
                if ( back_is == 2 ) { MsgError(iTmap); } // ERR[deberia ser <=]
                if ( back_is == 3 && is_more_equal < 2) { MsgError(iTmap); } // ERR [deberia ser <=]
                back_is = 1;
            }
            else if ( ! (*iTdata).first.second.compare("<=") )
            {	
                if ( back_is == 1 ) { MsgError(iTmap); } // ERR [deberia ser >=]
                if ( back_is == 2 )	{ continue; } /*OK*/ 
                if ( back_is == 3 && is_more_equal < 2) { continue; } /*OK*/
                back_is = 2;
            }
            else if ( ! (*iTdata).first.second.compare("=") )
            {
                if ( back_is == 1 )	{ continue; } /*OK*/
                if ( back_is == 2 )	{ MsgError(iTmap); } // ERR[deberia ser <=]
                if ( back_is == 3 ) { MsgError(iTmap); } // ERR["=" consecutivos]
                back_is = 3;
                is_more_equal++;
            }
            else
            {
                std::cout << "Operador no valido!" << std::endl;
                std::cout << "line '" <<  (*iTdata).second << "'" << std::endl;
                exit(2);
            }
        }
        return is_more_equal;
    }

    void Handle::insertPkgInRecSaver(std::map<std::string, meta>::iterator & iTmap, std::vector<meta_final> & vector_target, int is_more_equal)
    {
        // Third Phase
        // Iterator for the std::map, who is in to the struct "meta"
        std::map<std::pair<std::string, std::string>, int>::iterator iTdata;
        iTdata = (*iTmap).second.data.begin();
        std::map<std::pair<std::string, std::string>, int>::iterator iTdata_tmp;
        // Now we inserted in rec_saver_final the elements.
        if ( is_more_equal = 1 )
        {
            meta_final meta_final_str;

            if ( ! (iTdata->first.second.compare("<=")) )
            {
                iTdata_tmp = (*iTmap).second.data.begin();
                meta_final_str.package = (*iTmap).first;
                meta_final_str.version = (*iTdata_tmp).first.first;
                meta_final_str.operate = (*iTdata_tmp).first.second;
                vector_target.push_back(meta_final_str);
            }
            else if ( ! (iTdata->first.second.compare(">=")) )
            {
                iTdata_tmp = (*iTmap).second.data.end();
                iTdata_tmp--;
                meta_final_str.package = (*iTmap).first;
                meta_final_str.version = (*iTdata_tmp).first.first;
                meta_final_str.operate = (*iTdata_tmp).first.second;
                vector_target.push_back(meta_final_str);
            }
            else
            {
                iTdata_tmp = (*iTmap).second.data.begin();
                for(iTdata_tmp; iTdata_tmp != (*iTmap).second.data.end(); iTdata_tmp++)
                {
                    if( ! (iTdata_tmp->first.second.compare("=")) )
                    {
                        meta_final_str.package = (*iTmap).first;
                        meta_final_str.version = (*iTdata_tmp).first.first;
                        meta_final_str.operate = (*iTdata_tmp).first.second;
	
                        vector_target.push_back(meta_final_str);
                    }
                }
            }
        }
    }

    candidates_struct Handle::parseOpAndFillCandStruct(std::vector<meta_final> & vector_origin)
    {
        // Struct who contents contents list of candidates for upgrade, install and revupgrade
        candidates_struct candidates_obj;

        // Generating list
        for (std::vector<meta_final>::iterator iTrec_vector_origin = vector_origin.begin();
        iTrec_vector_origin != vector_origin.end(); iTrec_vector_origin++)
        {
            std::string package((*iTrec_vector_origin).package);
            std::string operate((*iTrec_vector_origin).operate);
            std::string version((*iTrec_vector_origin).version);
            int version_dep = objutils->transform_version((*iTrec_vector_origin).version);

            std::string version_av_str; objgetinfo_av->GetPkgTag(package, 0, version_av_str);
            int version_av = objutils->transform_version(version_av_str);

            std::cout << ".";
            std::cout << std::flush;
            if (  objgetinfo_lo->PkgExist(package) )
            { 
                std::string version_lo_str;
                if ( ! objgetinfo_lo->GetPkgTag(package, 0, version_lo_str) )
                {
                    std::cout << "No existe tag" << "Version" << std::endl;
                    exit(2);
                }
                int version_lo = objutils->transform_version(version_lo_str);

                if ( operate == ">=" )
                {
                    if ( version_lo  >=  version_dep ) { /* ">=Ya no se instala   "  << rec_saver[i][0] */	}
                    else
                    {
                        //cout << ">= Se actualiza " << rec_saver[i][0]  << endl;
                        if ( version_av < version_dep )
                        {
                            std::cout << "No se ha encontrado candidato que satisfaga: " << (*iTrec_vector_origin).package << " >= " << (*iTrec_vector_origin).version << std::endl;
                            exit(1);
                        }
                        else
                        {
                            //cout << "Se ha encontrado candidato" << endl;
                            candidates_obj.candidates_upgrade.push_back(package);
                        }
                    }
                }

                if ( operate == "=" )
                {
                    if ( version_lo ==  version_dep)
                    {
                        //cout << "Ya no se instala " << rec_saver[i][0]  << endl;
                    }
                    else
                    {
                        if (  version_lo >  version_dep )
                        {
                            //cout << "= Se desactualiza el paquete" << rec_saver[i][0] << endl;
                            if ( version_av != version_dep )
                            {
                                std::cout << "No se ha encontrado candidato que satisfaga: " <<  (*iTrec_vector_origin).package << " = " << (*iTrec_vector_origin).version << std::endl;
                                exit(1);
                            }
                            else
                            {
                                //cout << "Se ha encontrado candidato" << endl;
                                candidates_obj.candidates_revupgrade.push_back(package);
                            }
                        }

                        if ( version_lo < version_dep )
                        {
                            //cout << "= Se actualiza el paquete "  << rec_saver[i][0]  << endl;
                            if (version_av != version_dep )
                            {
                                std::cout << "No se ha encontrado candidato que satisfaga: " <<  (*iTrec_vector_origin).package << " = " << (*iTrec_vector_origin).version << std::endl;
                                exit(1);
                            }
                            else
                            {
                                //cout << "Se ha encontrado candidato" << endl;
                                candidates_obj.candidates_upgrade.push_back(package);
                            }
					    }
				    }
			    }

                if ( operate == "<=" )
	            {
                    if ( version_lo <= version_dep)
                    {
                        //cout << "<= Ya no se instala " << rec_saver[i][0] << endl;
                    }
                    else
                    {
                        //cout << "<= Se desactualiza el paquete " << rec_saver[i][0] << endl;
                        if ( version_av > version_dep )
                        {
                            std::cout << "No se ha encontrado candidato que satisfaga: " << (*iTrec_vector_origin).package << " <= " << (*iTrec_vector_origin).version << std::endl;
                            exit(1);
                        }
                        else
                        {
                            //cout << "Se ha encontrado candidato" << endl;
                            candidates_obj.candidates_revupgrade.push_back(package);
                        }
                    }
                }
            }
            else
            {
                //cout << "Paquete Nuevo" << endl;
                candidates_obj.candidates_new.push_back(package);
            }
        }
        return candidates_obj;
    }

    Handle::~Handle()
    {
        delete objgetinfo_av;
        delete objgetinfo_lo;
    }

}
