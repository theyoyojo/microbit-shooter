#include "radio.h"

#include "MicroBitRadio.h"

MicroBitRadio radio ;

using namespace ECG ;

Radio::Radio() {
    radio.enable() ;
}

int Radio::recv_all() {

    PacketBuffer temp ;
    int counter = 0 ;

    while ((temp = radio.datagram.recv()).length() > 0) {
        _packetsIn.push(temp) ;
        counter++ ;
    }

    return counter ;
}
int Radio::recv_next() {

    PacketBuffer temp ;
    temp = radio.datagram.recv() ;
    if (temp.length() > 0){
        _packetsIn.push(temp) ;
        return 1 ;
    }
    // If no packet was recieved, none were processed
    return 0 ;
}

int Radio::send_all() {
    while (_packetsOut.size() > 0) {
        send_next() ;
    }
}
int Radio::send_next() {
        radio.datagram.send(_packetsOut.front()) ;
        _packetsOut.pop() ;
}

void Radio::upload(PacketBuffer& p) {
    _packetsOut.push(p) ;
}

PacketBuffer Radio::download() {
    if (_packetsIn.size() > 0) {
        PacketBuffer temp = _packetsIn.front() ;
        _packetsIn.pop() ;
        return temp ;
    }
    else {
        return PacketBuffer::EmptyPacket ;
    }
}

int Radio::broadcast(PacketBuffer& p) {
    upload(p) ;
    return send_next() ;
}