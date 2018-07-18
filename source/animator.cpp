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

#include "animator.h"

#include "MicroBitDisplay.h"
#include "MicroBitFiber.h"

using namespace ECG ;

#define DEFAULT_ANIMATION_DIRECTION FORWARD
#define DEFAULT_ANIMATION_DELAY 100

MicroBitDisplay display ;

const uint8_t Animator::blank_arr[] __attribute__ ((aligned(4))) = {
    0xff, 0xff, 5, 0, 5, 0,
    0,0,0,0,0,
    0,0,0,0,0,
    0,0,0,0,0,
    0,0,0,0,0,
    0,0,0,0,0
} ;

const MicroBitImage& Animator::blankImage((ImageData*)blank_arr) ;

Animator::Animator() {
    // Nothing to be done here...
}

Animator::Animator(std::vector<MicroBitImage>& images) {

    // Simply copy the argument vector into the object's _images vector
    for(auto img : images) {
        _images.push_back(img) ;
    }
}

Animator::Animator(MicroBitImage& image) {

    // Just stick in in there
    _images.push_back(image) ;
}

Animator::Animator(Animator& existing) {

    // Copy everyting over using vector iterators
    for(auto img = existing.begin(); img != existing.end(); img++) {
        _images.push_back(*img) ;
    }
}

std::vector<MicroBitImage>::iterator Animator::begin() {
    return _images.begin() ;
}

std::vector<MicroBitImage>::iterator Animator::end() {
    return _images.end() ;
}
std::vector<MicroBitImage>::reverse_iterator Animator::rbegin() {
    return _images.rbegin() ;
}
std::vector<MicroBitImage>::reverse_iterator Animator::rend() {
    return _images.rend() ;
}

void Animator::animate(int msDelay = DEFAULT_ANIMATION_DELAY, D1_direction direction = DEFAULT_ANIMATION_DIRECTION) {

    // Case: empty animator
    if (_images.size() == 0) {
        display.print(blankImage) ;
    }
    // Case: animate forwards
    else if (direction == FORWARD) {
        for(auto img = _images.begin(); img != _images.end(); img++) {
            display.print(*img) ;
            fiber_sleep(msDelay) ;
        }
    }
    // Case: animate backwards
    else {
        for(auto img = _images.rbegin(); img != _images.rend(); img++) {
            display.print(*img) ;
            fiber_sleep(msDelay) ;
        }
    }
}

void Animator::animate() {
    animate(DEFAULT_ANIMATION_DELAY, DEFAULT_ANIMATION_DIRECTION) ;
}

void Animator::push_back(MicroBitImage& image) {

    // Calls std::vector method with same name
    _images.push_back(image) ;
}

void Animator::pop_back() {

    // Calls std::vector method with same name
    _images.pop_back() ;
}

void Animator::push_front(MicroBitImage& image) {
    _images.insert(_images.begin(),image) ;
}

void Animator::pop_front() {
    _images.erase(_images.begin()) ;
}

MicroBitImage& Animator::at(size_t index) {
    if(index < _images.size() ) {
        return _images[index] ;
    }
    else {
        return *(new MicroBitImage(blankImage)) ;
    }
}

void Animator::showFrame(size_t index) {
    if (index < _images.size() ) {
        display.print(_images[index]) ;
    }
    else {
        display.print(blankImage) ;
    }
}

size_t Animator::getSize() {
    return _images.size() ;
}

void Animator::operator () () {
    animate(DEFAULT_ANIMATION_DELAY,DEFAULT_ANIMATION_DIRECTION) ;
}

void Animator::operator () (int msDelay, D1_direction direction) {
    animate(msDelay, direction) ;
}

MicroBitImage& Animator::operator[] (size_t index) {
    return at(index) ;
}

Animator& Animator::operator= (Animator& existing) {

    _images.clear() ;

    for(auto img = existing.begin(); img != existing.end(); img++) {
        _images.push_back(*img) ;
    }

    return *this ;
}

Animator& Animator::operator << (MicroBitImage& image) {
    _images.push_back(image) ;
    return *this ;
}