## Resubmission 2

This is a resubmission. In this version I have:

* Removed whitespace in the description text
* Added a reference in the description text
* Added a \value field to print.scanstatistic.Rd
* Removed \dontrun from examples

## Resubmission 1

This is a resubmission. In this version I have:

* Fixed non-canonical CRAN URL
* Updated other URLs to https
* Updated the date field

## Release summary

This release updates the maintainer and updates the flags in src/Makevars.win to fix the issues 
that caused the package to be archived. 

## Test environments

* local: Windows 10 x64, R 4.1.3 
* r-hub: windows-x86_64-devel, ubuntu-gcc-release, linux-x86_64-rocker-gcc-san, fedora-clang-devel
* Github Actions: windows-latest-release, macOS-latest-release, ubuntu-latest-release, ubuntu-latest-devel

## R CMD check results

There were no ERRORs or WARNINGs on any platforms

There was 2 NOTES:

* Maintainer: ‘Paul Romer Present <paul.romerpresent@fastmail.fm>’, New submission, Package was archived on CRAN  

This package was previously on CRAN, but was removed due to check issues. In order to get this
package back on to CRAN, I (Paul Romer Present) am taking over maintainer duties from the previous
maintainer, Benjamin Allévius. The previous maintainer has sent an email to
cran-submissions@r-project.org confirming this. You can also view our discussions on GitHub:
https://github.com/BenjaK/scanstatistics/issues/12

The package was archived due to conflicting macros between PKG_CXXFLAGS and PKG_LIBS. I have
updated src/Makevars.win to remove this note. 

This is my first submission to CRAN. 

* installed size is  5.6Mb, sub-directories of 1Mb or more: libs   5.1Mb

Explanation (same as given on previous releases): The size is due to use of 
templated classes and functions, and virtual functions. The cost, in terms of 
code duplication and inability to add new functionality, that would result from 
not using these features of C++ is simply too high. Thus, I think the larger 
size of the installed package is warranted.

# Downstream dependencies

There are currently no downstream dependencies for this package.

