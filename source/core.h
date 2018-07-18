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

#ifndef CORE_H
#define CORE_H "core.h"


/* TODO: A home for some core utilities of any useful microbit program
    --Fiber
    --Heap allocator
    --Scheduler
*/

#include "MicroBitEvent.h"

namespace ECG {

class Core {

public:

    /**
      * Default constructor. Initializes the scheduler, message bus, and heap allocator
      */
    Core() ;

    /**
      * Wrapper for fiber_sleep
      * 
      * @param ms: time to sleep in ms
      */
    void sleep(unsigned long ms) ;

    /**
      * Wrapper for release_fiber
      */
    void abandon_thread() ;

    void listen(uint16_t id, uint16_t value, void (*handler)(MicroBitEvent)) ;

} ; // class Core

} // namespace ECG

#endif // CORE_H