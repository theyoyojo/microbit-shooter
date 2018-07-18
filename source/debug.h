/*
The MIT License (MIT)

Copyright (c) 2018 Joel Savitz

Permission is hereby granted, free of charge, to any person obtaining a
copy of this software and associated documentation files (the "Software"),
to deal in the Software without restriction, including without limitation
the rights to use, copy, modify, merge, publish, distribute, sublicense,
and/or sell copies of the Software, and to permit persons to whom the
Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
DEALINGS IN THE SOFTWARE.
*/

#ifndef DEBUG_H
#define DEBUG_H "debug.h"

#include <ctype.h>
#include <type_traits>
#include "MicroBitSerial.h"

#define VARNAME(x) #x
#define valueof(x) dump(x,VARNAME(x)) ;

#define DB_BUFFSZ 1024

namespace ECG {

class Debug {

char strBuff[DB_BUFFSZ] ;

public:

    /**
      * Default constructor
      * 
      * Sets content of buffer to all 0s
      */
    Debug() ;

    /**
      * Dump content to output monitor in printf style
      * ;
      * @param strFmt: a format string (like printf)
      * 
      * @param ... (varadic): an ordered list of arguments to fill each format specifier in strFmt
      * 
      * @return On success, number of bytes sent over serial. On failure, -1
      * 
      * @note don't call with arguments that will result in more than DB_BUFFSZ - 3 bytes being needed as buffer space.
      * Additional bytes will be ignored with no remorse. The '- 3' is to ensure null termination and presence of CRLF
      */
    int dump(char const * strFmt, ...) ;


    /**
      * Dump content of a single variable to output monitor
      * 
      * @param value: The content to be dumped to output monitor
      * 
      * @return On success, number of bytes sent over serial. On failure, -1
      * 
      * @note Makes use of dump(char, ...)
      * 
      * TODO:
      *  -- add support for more primitive types
      */
    template <class T>
    int dump(T value) {

        //serial.printf("THIS IS: %s\r\n", __PRETTY_FUNCTION__) ;
        if (std::is_same<T,int>::value) {
            return dump("%d", value) ;
        }
        else if (std::is_same<T,double>::value) {
            return dump("%lf", value) ;
        }
        else if (std::is_same<T,char const *>::value) {
            return dump("%s", value) ;
        }
        else if (std::is_same<T,size_t>::value) {
          return dump("%ld", value) ;
        }
        else {
            // TODO: stringify & print
            // expected bug: unspported dump(char*,T) calls will cause strange behavior
            // I'll leave this here to ensure there is at least a newline and an obvious behavior
            dump("<unsupported dump, please complain to dev>") ;
            return -1 ;
        }
    }

    /**
      * Dump content of a single variable to output monitor with a string label next to it
      * 
      * @param value: The content to be dumped to output monitor
      * 
      * @param label: A string to be printed next to the content for readability
      * 
      * @return On success, number of bytes sent over serial. On failure, -1
      * 
      * @note Makes use of dump(char, ...)
      */
    template <class T>
    int dump(T value, char const * label) {
        //serial.printf("THIS IS: %s\r\n",__PRETTY_FUNCTION__) ;
        return dump_naked("%s = ", label) + dump(value) ;
    }

    /**
      * A simple variant of dump(char const *, ...) that does not bother with modifying line endings
      * 
      * @param strFmt: a format string (like printf)
      * 
      * @param ... (varadic): an ordered list of arguments to fill each format specifier in strFmt
      * 
      * @return On success, number of bytes sent over serial. On failure, -1
      * 
      * @note don't call with arguments that will result in more than DB_BUFFSZ - 1 bytes being needed as buffer space.
      * Additional bytes will be ignored with no remorse. The '- 1' is to ensure null termination of buffer
      */
    int dump_naked(char const * strFmt, ...) ;

} ; // class Debug

} // namespace ECG

#endif // DEBUG_H