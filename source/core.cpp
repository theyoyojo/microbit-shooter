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

#include "core.h"

#include "debug.h"

using namespace ECG ;

#include "MicroBitFiber.h"
#include "MicroBitMessageBus.h"
#include "MicroBitHeapAllocator.h"
#include "MicroBitEvent.h"
#include "MicroBitButton.h"
#include "animator.h"
#include "images.h"

Debug cdb ;

MicroBitButton buttonA(MICROBIT_PIN_BUTTON_A,MICROBIT_ID_BUTTON_A) ;
MicroBitButton buttonB(MICROBIT_PIN_BUTTON_B,MICROBIT_ID_BUTTON_B) ;

ECG::Animator a ;
ECG::Animator b ;

void onButtonADown(MicroBitEvent e) {
    cdb.dump("in onButtonADown") ;
    cdb.valueof(a.getSize()) ;
    a() ;
}

void onButtonBDown(MicroBitEvent e) {
    cdb.dump("in onButtonBDown") ;
    cdb.valueof(b.getSize()) ;
    b() ;
}

// The reason for the name is the fact of this being written for a school
MicroBitMessageBus schoolbus ;

Core::Core() {
    cdb.dump("core constructor called") ;

    // The schoolbus must run on time
    scheduler_init(schoolbus) ;

    // Free up space usually taken up by bluetooth stack (this library does not use it right now)
    microbit_create_heap(MICROBIT_SD_GATT_TABLE_START + MICROBIT_SD_GATT_TABLE_SIZE, MICROBIT_SD_LIMIT) ;

    cdb.dump("core constructed.") ;

    listen(MICROBIT_ID_BUTTON_A, MICROBIT_BUTTON_EVT_DOWN, onButtonADown) ;
    listen(MICROBIT_ID_BUTTON_B, MICROBIT_BUTTON_EVT_DOWN, onButtonBDown) ;

    a << ECG::Images::centerRing << ECG::Images::middleRing << ECG::Images::outerRing ;

    // add elements from animation a to animation b in a speficied order
    b << a[2] << a[1] << a[0] ;
}

void Core::sleep(unsigned long ms) {
    fiber_sleep(ms) ;
}

void Core::abandon_thread() {
    cdb.dump("about to call release_fiber...") ;
    release_fiber() ;
    cdb.dump("post fiber release(should not get here tbh)") ;
}

void Core::listen(uint16_t id, uint16_t value, void (*handler)(MicroBitEvent)) {
    schoolbus.listen(id, value, handler) ;
    cdb.dump("listener wrapper terminating") ;
}