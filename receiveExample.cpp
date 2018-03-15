#include "mcp_can.h"

#include "Cosa/Trace.hh"
#include "Cosa/UART.hh"
#include "Cosa/PinChangeInterrupt.hh"

unsigned char Flag_Recv = 0;
unsigned char len = 0;
unsigned char buf[8];
char str[20];

class PinInterrupt : public PinChangeInterrupt {
    public:
        PinInterrupt(Board::InterruptPin pin, InterruptMode mode) : PinChangeInterrupt(pin, mode) {};

    private:
        virtual void on_interrupt(uint16_t arg=0) {Flag_Recv = 1;}
};

PinInterrupt interrupt(Board::PCI1, PinChangeInterrupt::ON_FALLING_MODE);

void setup() {
    CAN.begin(CAN_500KBPS);
    PinChangeInterrupt::begin();
    interrupt.enable();
    uart.begin(115200);
    trace.begin(&uart);
}

void loop() {
    if (Flag_Recv){
        Flag_Recv = 0;
        CAN.readMsgBuf(&len, buf);
        trace << "data len = ";
        trace << len << endl;
      
        for(int i = 0; i<len; i++){
            trace << buf[i];
        }
    }
}