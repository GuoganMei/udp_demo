#include "hwInterface.hpp"
#include <iostream>
void hwInterface::run() {
    while (true) {
        for (int i = 0; i < 12; i++) {
            udp_send_data_.udp_motor_send[i] = jointTorque_(i);
        }
        udpInterface_.setSendData(udp_send_data_);
        udpInterface_.send();

        receive_flag_ = udpInterface_.receive(10); // non-blocking
        udp::ReceiveData udp_reciv_data{};
        udp_reciv_data_ = udpInterface_.getReceiveData();
        if (receive_flag_) {
            for (int i = 0; i < 10; i++) {
                imuData_(i) = udp_reciv_data_.udp_imu_receive[i];
            }
        }
        std::cout <<imuData_.transpose()<<std::endl;
    }
}