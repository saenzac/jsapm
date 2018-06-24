## apt (debian) style package manager engine

Utility that parse a file database to solve dependencies or conflicts from another packages by using a series of algorithms.
Basically it reads the database which consist in the file "available.txt" and generates the dependencies from it.

In it's current state it doesn't perform an actual installation of the packages.


# output example
Enter the package name
python
Gathering dependencies.........[OK]
Verifying conflicts.........[OK]
Generating candidates.........[OK]

The following packages are going to be installed:
libc6 libdb4.3 libncurses5 python python2.3 zlib1g 

0 to upgrade, 6 new 

Do you want to continue?: (y/n) 


[![Documentation][doxygen-shield]][doxygen-link]

[doxygen-shield]: https://img.shields.io/badge/documentation-master-brightgreen.svg
[doxygen-link]: https://cdn.rawgit.com/saenzac/jsapm/b71d2451/html/index.html

