/* Copyright (C) Johnny Saenz                                                 

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details. */

#ifndef TRISTAN_STRUCTS
#define TRISTAN_STRUCTS

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <list>

/**
 * @struct tags
 * All tags and its respective length.
 */
struct tags
{ 
/** Name of a tag */
char name[40];
/** Length of a tag */
int size;
};

/**
 * @struct taginfo
 * Struct that save content of a tag, and the respective line number.
 */
struct taginfo
{
	/** Content of a tag */
	std::string content;
	/** Line number of the tag */
	int nline;
};

/**
 * @struct candidates_struct
 * Struct that save the packages to upgrade, revupgrade, and new for install.
 */
struct candidates_struct
{
	/** Vector who contents new packages for install */
	std::vector<std::string> candidates_new;
	/** Vector who contents packages for upgrade */
	std::vector<std::string> candidates_upgrade;
	/** Vector who contents packages for revupgrade */
	std::vector<std::string> candidates_revupgrade;
};

/**
 * @struct __node
 * Node of a linked list.
 */
struct __node
{
	/** Next node */
	struct __node *next;
	/** Contains the actual line, while read the {AV|LOCAL}_CONF_FILE  */
	std::string	  *line;
	/** Line number */
	int			  nline;
};

/** 
 * Creates a type name for __node.
 * @typedef _node
 */
typedef __node _node;


/**
 * @struct _Programa
 * Struct that contain information use in handle_dependencies member.
 */
typedef struct _Programa
{
	/** Name of the package */
	std::string name;
	/** Operator for the package */
	std::string op;
	/** Version of the package */
	std::string ver;
	/** Line number of the tag */
	int nline;
} Programa;

/**
 * @struct meta
 * Struct that contain a vector who store information of a package,
 * that information will be treated concluding in the meta_final struct.
 */
struct meta
{
	/** Vector who contains package information
	 *  will be treated concluding in the meta_final struct. */
	std::map<std::pair<std::string, std::string>, int> data;
};

/**
 * @struct meta_final
 * Struct that contain information final of a package, after reviewing conflicts.
 */
struct meta_final
{
	/** Name of the package. */
	std::string package;
	/** Operator of the package. */
	std::string operate;
	/** Version of the package. */
	std::string version;
};

#endif
