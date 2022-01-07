#include <iostream>
#include <cstring>
#include <thread>
#include <unistd.h>

#include <oscpack/osc/OscOutboundPacketStream.h>
#include <oscpack/ip/UdpSocket.h>

#include "TouchMatrix.h"


int msg = 0;
const int bufferSize = 4096;
char udpBuffer[bufferSize];
uint16_t fBuffer[121];

void grabFrame(tm_control::TouchMatrix *tmControl, UdpTransmitSocket *udpTransmitSocket) {
    std::cout << "Start thread" << std::endl;

    while (true) {
        if (msg == -1) {
            std::cout << "End thread" << std::endl;
            break;
        }

        //std::cout << tmControl->getRawValue(17,true) << std::endl;
        //sleep(1);

        tmControl->getFrame(fBuffer, 121); // scan frame

        osc::OutboundPacketStream packetStream(udpBuffer, bufferSize);
        packetStream << osc::BeginBundleImmediate;
        for (int i = 0; i < 121; i++) {
            //std::cout << (int) fBuffer[i] << ", ";
            packetStream << osc::BeginMessage("/sensor_value")
                         << i
                         << (int) fBuffer[i]
                         << osc::EndMessage;
        }
        //std::cout << std::endl;
        packetStream << osc::EndBundle;
        udpTransmitSocket->Send(packetStream.Data(), packetStream.Size());
    }

}

int main() {
    std::cout << "Hello, World!" << std::endl;

    /*
     * GPIO and SPI Setting
     */
    tm_control::Adc adc{0, 0, 2, 10000000, 0, 8};
    tm_control::Driver drv{26, 27, 28, 29};
    tm_control::Decoder dec{0, 2, 3, 4};
    tm_control::Multiplexer mux{22, 23, 24, 25};

    /*
     * TouchMatrix Initialize
     */
    tm_control::SpiAdc adcControl((char *) "/dev/spidev0.0", adc);
    tm_control::Led ledControl(drv);
    tm_control::Selector selControl(dec, mux);
    tm_control::TouchMatrix tmControl(adcControl, selControl, ledControl);


    /*
     * OSC Connection Initialize
     */
    UdpTransmitSocket udpTransmitSocket(IpEndpointName("192.168.137.1", 7000));

    /*
     * buffer Initialize
     */
    memset(fBuffer, 0, sizeof(fBuffer));

    /*
     * Sensor scan Thread Initialize
     */
    std::cout << "Start Scan" << std::endl;

    std::thread scanThread(grabFrame, &tmControl, &udpTransmitSocket);

    std::cout << "Press the enter key to quit." << std::endl;
    int input;
    std::cin >> input;
    msg = -1;

    scanThread.join();

    std::cout << "End Scan" << std::endl;


    return 0;
}
