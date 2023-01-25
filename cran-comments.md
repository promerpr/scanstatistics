## Release summary

This release fixes two warnings in the most recent CRAN package checks:

* Update EBZIPscan.h to remove a warning when using r-devel on Linux systems. 
* Remove test-pgumbel to remove a warning when using windows-oldrelease. 

## Test environments

* local: Windows 10 x64, R 4.1.3 
* r-hub: debian-clang-devel, debian-gcc-devel, fedora-clang-devel, fedora-gcc-devel
* win-builder: windows-oldrease

## R CMD check results

There were no ERRORs or WARNINGs on any platforms

There was 1 NOTE:

* installed size is 8.4Mb, sub-directories of 1Mb or more: libs   8.0Mb

Explanation (same as given on previous releases): The size is due to use of 
templated classes and functions, and virtual functions. The cost, in terms of 
code duplication and inability to add new functionality, that would result from 
not using these features of C++ is simply too high. Thus, I think the larger 
size of the installed package is warranted.

# Downstream dependencies

There are currently no downstream dependencies for this package.

