# BigNumbers
Class representing integral "big numbers" in C++.  
# Tests
I'm using Boost::Test framework(dynamic libraries) for unit tests, so you should download the latest Boost libraries.
Using Visual Studio 2015 you have to:  
- at Linker / System / SubSystem set value Console (/SUBSYSTEM:CONSOLE)  
- at C/C++ / General / Additional Include Directories/ set value to your Boost path(e.g. C:\boost_1_60_0)  
- at Linker / General / Additional Library Directories set value to Boost's MSVC libs path(e.g. C:\boost_1_60_0\lib64-msvc-14.0)  
- at Linker/Input/Additional Dependencies set value "libboost_unit_test_framework-vc140-mt-gd-1_60.lib"  
- at C/C++ / Code Generation set value "Multi-threaded Debug DLL (/MDd)"  
If you want to use only header, you have to change includes to:
```C++
#include <boost/test/included/unit_test.hpp>
```
and perform only two first steps.  

It's very handy to use Boost Unit Test Adapter for VS2015.
