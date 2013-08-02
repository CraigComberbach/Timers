Generic Embedded Peripherals
============================

Project Details
---------------

* Authors: Craig Comberbach
* Processor: 
* Version Control: This code uses Semantic Versioning (http://semver.org/). The code is setup to auto handle changes to source files it depends upon as long as the associated *.h file has the *_MAJOR, *_MINOR, and _PATCH definitions updated every time the file version changes.
* Make sure all changes, additions or deletions are reflected in updated meta-documentation (/***/ tags) and the wiki. It is not fair for someone to write code based off of bad documentation, this is unacceptable.

This code is not written to be used standalone, but rather is used with another project that requires the functionality provided with these files. Generic functionality to modules or connected peripherals is all that should be in this project.

To properly use this code you need to do the following:
C30 compiler:
1)	Go to "pic30-gcc" in Project Properties, choose "General" in the Option Categories dropdown menu box
2)	Scroll down to "Include directories" and add the absolute directory of these files and the project this is to be included in. Click ok until you are viewing the project
3)	Perform a clean and build
4)	...
5)	Profit

XC16 compiler:
Same as C30, but with some minor changes. I haven't done this yet, so I won't make it official.