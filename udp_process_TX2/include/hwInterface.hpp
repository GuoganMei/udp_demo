#include "udp_comm.h"

#include <eigen3/Eigen/Core>
#include <eigen3/Eigen/Dense>
#include <vector>

class hwInterface {
public:
    hwInterface(uint16_t local_port, const std::string &target_ip, uint16_t target_port)
     : udpInterface_(local_port, target_ip, target_port) {
        jointTorque_ = Eigen::VectorXd::Zero(12);
        imuData_ = Eigen::VectorXd::Zero(10); 
        imuData_(9) = 1.0;
        udpInterface_.init();
    }
    ~hwInterface() {}
    
    void setImuData(Eigen::VectorXd& imuData) { imuData_ = imuData; }
    Eigen::VectorXd getJointTorque() { return jointTorque_;}
    
    void run();

private:
    UdpComm udpInterface_;
    Eigen::VectorXd jointTorque_;
    Eigen::VectorXd imuData_; //omega , acc_body, quat

    udp::SendData udp_send_data_{};
    udp::ReceiveData udp_reciv_data_{};
    bool receive_flag_ = false;
};