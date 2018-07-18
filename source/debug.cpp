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

#include "debug.h"

#include <stdarg.h>

using namespace ECG ;

MicroBitSerial serial(USBTX,USBRX) ;

Debug::Debug() {

    // Clean the cobwebs out of our character buffer    
    memset(strBuff,0,DB_BUFFSZ) ;
}

int Debug::dump(char const * strFmt, ...) {

    // Construct final output string and write it to buffer
    va_list argList ;
    va_start(argList, strFmt) ;
    int16_t lenBuff = vsnprintf(strBuff, DB_BUFFSZ - 3, strFmt, argList) ;

    // If there was an error with vsnprintf, fail and leave after reporting to user.
    if (lenBuff == -1) {
        serial.printf("There was an error constructing a string and this message is being send instead.\r\n") ;
        return lenBuff ;
    }

    // Case: less than two characters written to buffer (nearly forgot this one)
    // If this case is true, there will be a guarenteed segfault due to the next if()
    if (lenBuff < 2) {
        if (lenBuff < 1) {
            strBuff[lenBuff++] = '\r' ;
            strBuff[lenBuff++] = '\n' ;
        }
        else {
            if (strBuff[lenBuff - 1] == '\n') {
                strBuff[lenBuff - 1] = '\r' ;
                strBuff[lenBuff++] = '\n' ;
            }
            else {
                if (strBuff[lenBuff - 1] != '\r') {
                   strBuff[lenBuff++] = '\r' ;
                }
                strBuff[lenBuff++] = '\n' ;
            }
        }
    }
    // Case: \r\n terminated (CRLF)
    else if(strBuff[lenBuff - 2] == '\r' && strBuff[lenBuff - 1] == '\n') {
        // CRLF in place, continue to addition of null terminator
    }
    // Case: \r terminated
    else if (strBuff[lenBuff - 1] == '\r'){
        // Add an '\n' and increment size
        strBuff[lenBuff++] = '\n' ;
    }
    // Case: \n terminted
    else if (strBuff[lenBuff - 1] == '\n') {
        // Overwrite \n with an \r and append an \n. Increment size
        strBuff[lenBuff - 1] = '\r' ;
        strBuff[lenBuff++] = '\n' ;
    }
    // Case: The user (probably also the person writing these lines) did some other random unsupported garbage.
    else {
        // Just append a CRLF and increment the size twice.
        strBuff[lenBuff++] = '\r' ;
        strBuff[lenBuff++] = '\n' ;
    }

    // Append a null terminator before printing. You can never go wrong by appending a null terminator
    // to a c-string as far as I know, especially when printf is involved
    strBuff[lenBuff++] = '\0' ;

    // Send it.
    serial.printf("%s", strBuff) ;

    // Finally return the number of characters sent over the serial line in case the user needs that information
    return lenBuff ;
}

int Debug::dump_naked(char const * strFmt, ...) {

    // Construct final output string and write it to buffer
    va_list argList ;
    va_start(argList, strFmt) ;
    int16_t lenBuff = vsnprintf(strBuff, DB_BUFFSZ - 1, strFmt, argList) ;

    // If there was an error with vsnprintf, fail and leave after reporting to user.
    if (lenBuff == -1) {
        serial.printf("There was an error constructing a string and this message is being send instead.\r\n") ;
        return lenBuff ;
    }

    // As above, add that null guy in there (as you can see, I didn't completely copy and paste this code)
    strBuff[lenBuff++] = '\0' ;

    // Ship it.
    serial.printf("%s", strBuff) ;

    // See clothed version of function if you really want a comment on this line.
    return lenBuff ;
}
