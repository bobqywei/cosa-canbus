#include "mcp_can.h"

#include "Cosa/Trace.hh"
#include "Cosa/UART.hh"

void setup() {
    uart.begin(9600);
    trace.begin(&uart);
    if(CAN.begin(CAN_500KBPS) == CAN_OK) {
        trace << "CAN init ok!" << endl;
    } else {
        trace << "CAN init failed" << endl;
    }
}

unsigned char stmp[8] = {0, 1, 2, 3, 4, 5, 6, 7};

void loop() {
    // send data:  id = 0x00, standard frame, data len = 8, stmp: data buf
    CAN.sendMsgBuf(0x00, 0, 8, stmp);  
    delay(100);
}
