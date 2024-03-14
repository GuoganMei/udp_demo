#include "udp_comm.h"
#include "hwInterface.hpp"
int main () {
    hwInterface hw(10, "192.168.1.20", 7);
    Eigen::VectorXd imuData = Eigen::VectorXd::Ones(10);
    hw.setImuData(imuData);
    hw.run();
    return 0;
}