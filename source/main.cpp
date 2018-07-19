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


MicroBitButton buttonA(MICROBIT_PIN_BUTTON_A,MICROBIT_ID_BUTTON_A) ;
MicroBitButton buttonB(MICROBIT_PIN_BUTTON_B,MICROBIT_ID_BUTTON_B) ;


ECG::Radio r ;

class A {
    public:

    A(ECG::Animator& refA, ECG::Animator& refB) ;

    ECG::Animator& a;
    ECG::Animator& b;

    void onButtonADown(MicroBitEvent e) ;
    void onButtonBDown(MicroBitEvent e) ;
} ; // Class A (test class)

A::A(ECG::Animator& refA, ECG::Animator& refB) : a(refA), b(refB) {
    core.listen(MICROBIT_ID_BUTTON_A, MICROBIT_BUTTON_EVT_DOWN, this, &A::onButtonADown) ;
    core.listen(MICROBIT_ID_BUTTON_B, MICROBIT_BUTTON_EVT_DOWN, this, &A::onButtonBDown) ;
}

void A::onButtonADown(MicroBitEvent e) {
    db.dump("in onButtonADown") ;
    db.valueof(a.getSize()) ;
    PacketBuffer p(1) ;
    p[0] = 'j' ;
    r.broadcast(p) ;
    a() ;
}

void A::onButtonBDown(MicroBitEvent e) {
    db.dump("in onButtonBDown") ;
    db.valueof(b.getSize()) ;
    b() ;
    r.recv_next() ;
    PacketBuffer p = r.download() ;
    //db.valueof(p[0]) ;
    db.dump("%d",p[0]) ;
}

ECG::Animator a;
ECG::Animator b;

int main() {

    db.dump("begin main.") ;

    A test(a, b) ;

    /*
    auto ptrA = new ECG::Animator ;
    auto ptrB = new ECG::Animator ;

    ECG::Animator& a = *ptrA ;
    ECG::Animator& b = *ptrB ;
    */

    a << ECG::Images::centerRing << ECG::Images::middleRing << ECG::Images::outerRing ;

    // add elements from animation a to animation b in a speficied order
    b << a[2] << a[1] << a[0] ;

    db.dump("about to abandon main thread") ;

    core.abandon_thread() ;

    db.dump("hitting end of main") ;
}