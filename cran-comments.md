## Release summary

This release updates the maintainer and makes some other changes to remove
R CMD check warnings. 

## Test environments

* local: Windows 10 x64, R 4.0.5 
* r-hub: windows-x86_64-devel, ubuntu-gcc-release, linux-x86_64-rocker-gcc-san, fedora-clang-devel
* Github Actions: windows-latest-release, macOS-latest-release, ubuntu-latest-release, ubuntu-latest-devel

## R CMD check results

There were no ERRORs or WARNINGs on any platforms

There was 2 NOTES:

* Maintainer: ‘Paul Romer Present <paul.romerpresent@fastmail.fm>’, New submission, Package was archived on CRAN  

This package was previously on CRAN, but was removed due to check issues. In order to get this
package back on to CRAN, I (Paul Romer Present) am taking over maintainer duties from the previous
maintainer, Benjamin Allévius. The previous maintainer has sent an email to
cran-submissions@r-project.org confirming this.

This is my first submission to CRAN. 

* installed size is  5.6Mb, sub-directories of 1Mb or more: libs   5.1Mb

Explanation (same as given on previous releases): The size is due to use of 
templated classes and functions, and virtual functions. The cost, in terms of 
code duplication and inability to add new functionality, that would result from 
not using these features of C++ is simply too high. Thus, I think the larger 
size of the installed package is warranted.

# Downstream dependencies

There are currently no downstream dependencies for this package.

