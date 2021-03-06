curlcpp
=======

An object-oriented C++ wrapper for cURL tool

If you want to know a bit more about cURL, you should go on the official website and read about the three interfaces that curl implements: http://curl.haxx.se/

Compile and link
================

Standalone
----------

```bash
cd build
cmake ..
make # -j2
```

Then add `<curlcpp root>/build/src/` to your library path and `<curlcpp root>/include/` to your include path.

When linking, link against `curlcpp` (e.g.: gcc -std=c++11 example.cpp -o example -lcurlcpp).

Submodule
---------

When using a git submodule and CMake-buildsystem, add the following lines to your `CMakeLists.txt`:

```
ADD_SUBDIRECTORY(ext/curlcpp) # Change `ext/curlcpp` to a directory according to your setup
INCLUDE_DIRECTORIES(${CURLCPP_SOURCE_DIR}/include)
```

Simple usage example
====================

Here's an example of a simple HTTP request to get google web page, using the curl_easy interface:

`````c++
#include <iostream>
#include "../include/curl_easy.h"
// only "curl_easy.h" if you use above submodule-way of compilation and linking

using std::cout;
using std::endl;
using curl::curl_easy;

int main(int argc, const char **argv) {
    curl_easy easy;
    easy.add(curl_pair<CURLoption,string>(CURLOPT_URL,"http://www.google.it") );
    easy.add(curl_pair<CURLoption,long>(CURLOPT_FOLLOWLOCATION,1L));
    try {
        easy.perform();
    } catch (curl_error error) {
        // If you want to get the entire error stack we can do:
        stack<pair<string,string>> errors = error.what();
        // Otherwise we could print the stack like this:
        error.printTraceback();
        // Note that the printing the stack will erase it
    }
    return 0;
}
`````

Here's instead, the creation of an HTTPS POST login form:

`````c++
#include <iostream>
#include "curl_easy.h"
#include "curl_http_post.h"
// only "curl_easy.h" and "curl_http_post.h" if you use above submodule-way of compilation and linking

using std::cout;
using std::endl;
using curl::curl_easy;
using curl::curl_http_post;

int main(int argc, const char * argv[]) {
    curl_easy easy;
    curl_http_post post;
    
    // First example form
    post.add(curl_pair<CURLformoption,string>(CURLFORM_COPYNAME,"user"),curl_pair<CURLformoption,string>(CURLFORM_COPYCONTENTS,"username")); 
    
    // Second example form
    post.add(curl_pair<CURLformoption,string>(CURLFORM_COPYNAME,"passw"), curl_pair<CURLformoption,string>(CURLFORM_COPYCONTENTS,"password"));
                 
    easy.add(curl_pair<CURLoption,string>(CURLOPT_URL,"https://xxxxx/"));
    easy.add(curl_pair<CURLoption,curl_http_post>(CURLOPT_HTTPPOST,post));

    try {
        easy.perform();
    } catch (curl_error error) {
        // If you want to get the entire error stack we can do:
        stack<pair<string,string>> errors = error.what();
        // Otherwise we could print the stack like this:
        error.printTraceback();
        // Note that the printing the stack will erase it
    }
    return 0;
}
`````

That's it! :)
