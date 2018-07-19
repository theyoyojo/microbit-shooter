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

#ifndef RADIO_H
#define RADIO_H

#include <queue>
#include "PacketBuffer.h"

// @note Inclusion of this file disables bluetooth

// Disable bluetooth to enable radio
#define MICROBIT_BLE_ENABLED 0 

namespace ECG {

class Radio {

    std::queue<PacketBuffer> _packetsIn ;

    std::queue<PacketBuffer> _packetsOut ;
    
public:

    /**
      * Default constructor
      */
    Radio() ;

    /**
      * Load waiting packets into object buffer
      * 
      * @return: number of packets processed
      */
    int recv_all() ;
    int recv_next() ;
     
    /**
      * Send waiting packets over radio
      * 
      * @return: number of packets processed
      */
    int send_all() ;
    int send_next() ;

    /**
      * Send a packet to the outgoing queue
      */
    void upload(PacketBuffer& p) ;
    
    /**
      * Upload and send a packet
      * 
      * @return: number of packets processed
      */
    int broadcast(PacketBuffer& p) ;

    /**
      * Get the next packet from the incomming queue
      */
    PacketBuffer download() ;

} ; // class Radio

} // namespace ECG

#endif // RADIO_H