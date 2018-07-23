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

#ifndef ANIMATOR_H
#define ANIMATOR_H "animator.h" ;

#include <vector>
#include "MicroBitImage.h"

/* 
purpose: provide an easy to use framework for displaying 5x5 led images of 1 or more frames,
loading and saving images from MicroBitImage and other formats, modifying images, and animating with different properties

metaphor: there are instances of a little elf inside your computer for each instatiation of this class. These animator elves
are extremely passionate about doing things with a very constrained set of images. You can ask an elf to take control
of the screen and do things to it using what it knows
*/

// include a standard static image library (i.e. images.h) 
// -- would contain blank, full, etc
// -- static methods to clear screan, fill it, etc

// Method to generate animations from an image (like gradual fade transform)

// Eventually, I would want to be able to coordinate multiple 5x5 displays as one single unit

    /*
    TODO:
        -- testing
        -- macros for speeds (e.g. ANIMATE_FAST, ANIMATE_SLOW)
    */

// Labels for one dimensional direcitons
typedef enum d1_direction {FORWARD,BACKWARD} D1_direction ;

namespace ECG {

class Animator {

    /* TODO:
      -- consider an upgrade to a universal animator
      -- std::map<std::string,std::vector<MicroBitImage>> as internal data type
    */

    // The images known to the animator
    std::vector<MicroBitImage> _images;

public:

    /* Static data members */

    // TODO: move below to images or move images here?

    // A const representation of a blank image saved in flash
    static const uint8_t blank_arr[] __attribute__ ((aligned(4))) ;

    // Decleration of a usable reference to the above
    static const MicroBitImage& blankImage ;

    /* Constructors */

    /**
      * Default constructor
      * 
      * Create an empty animator
      */
    Animator() ;

    /**
      * Parameterized constructor
      * 
      * Create an animator from an existing vector of images
      */
    Animator(std::vector<MicroBitImage>& images) ;

    /**
      * Parameterized constructor
      * 
      * Create an animator from a single image
      */
    Animator(MicroBitImage& image) ;

    /**
      * Copy constructor
      * 
      * Create an animator by copying data from an existing animator
      */
    Animator(Animator& existing) ;

    /* Member functions */

    /**
      * Show current stored animation on display
      * 
      * @param direction: An option to display the images in forwards or backwards order.
      * Type is enum defined above. Default to forwards
      * 
      * @param msDelay: Time in ms to wait between displaying each image in the animation
      */
    void animate(int msDelay, D1_direction direction)  ;

    // Wrapper for above but with defaults
    void animate() ;

    /**
      * Add an image to end of the animator's list
      * 
      * @param image: The image to add
      * 
      */
    void push_back(MicroBitImage& image) ;

    /**
      * Remove the last image from the animator's list
      */
    void pop_back() ;

    /**
      * Add an image to begining of the animator's list
      * 
      * @param image: The image to add
      * 
      */
    void push_front(MicroBitImage& image) ;

    /**
      * Remove the first image in the animator's list
      */
    void pop_front() ;

    /**
      * Access a in image at a specific index of the list 
      * 
      * @param index: The number index to access
      * 
      * @return: a pointer to the image at index if it exists, otherwise returns blankImage
      */
    MicroBitImage& at(size_t index) ;
        
    /**
      * Show a single frame of an animation
      * 
      * @param index: Index of the frame. If out of bounds, blankImage will be shown
      */
    void showFrame(size_t index) ;

    /**
      * Get vector iterators for easy iteration
      * 
      * @return: The relevant iterators
      * 
      * @note: Included are the standard and reverse iterators
      */
    std::vector<MicroBitImage>::iterator begin() ;
    std::vector<MicroBitImage>::iterator end() ;
    std::vector<MicroBitImage>::reverse_iterator rbegin() ;
    std::vector<MicroBitImage>::reverse_iterator rend() ;

    /**
      * Get the number of images in the animation
      * 
      * @return: The number of images in the animation
      */
    size_t getSize() ;

    /* Operators */

    /**
      * Animate using default args by using empty function call syntax on object
      */
    void operator () () ;

    /**
      * Animate using custom args by using function call syntax on object
      * 
      * @param msDelay: see animate()
      * 
      * @param direciton see animate()
      */
    void operator () (int msDelay, D1_direction direction) ;

    /**
      * Access images of the animator by index. Uses at()
      */
    MicroBitImage& operator[] (size_t index) ;

    /**
      * Invoke copy constructor using assignment operator
      */
    Animator& operator= (Animator& existing) ;

    /**
      * Invoke push_back using left bitshift operator (like std::cout)
      */
    Animator& operator << (MicroBitImage& image) ;

} ; // Animator

} // namespace ECG

#endif // ANIMATOR_H