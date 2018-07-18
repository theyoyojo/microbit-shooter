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

// Notes:
// framework for distributed games?

// game has entities
// game ticks update entites
// game state shared accross multiple devices
// all involved devices constantly sending and recieving packets with game data

#include "radio.h"
#include "core.h"
#include "debug.h"
#include "animator.h"
#include "images.h" 

#include "MicroBitButton.h"

ECG::Debug db ;


ECG::Core core;

int main() {

    db.dump("begin main.") ;




    // copy contents of animation a to animation b
    //b = a ;

    db.dump("aboutta release") ;

    core.abandon_thread() ;

    db.dump("hitting end of main") ;
}