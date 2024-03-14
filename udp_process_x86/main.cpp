#include "udp_comm.h"
#include "hwInterface.hpp"
int main () {
    hwInterface hw(7, "192.168.1.20", 10); //27
    Eigen::VectorXd legTorque = Eigen::VectorXd::Ones(12);
    hw.setJointTorque(legTorque);
    hw.run();
    return 0;
}