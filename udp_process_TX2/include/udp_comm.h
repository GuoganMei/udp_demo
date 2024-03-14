#pragma once

/* related header files */

/* c system header files */
#include <memory>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

/* c++ standard library header files */
#include <cerrno>
#include <cstring>

/* external project header files */

/* internal project header files */
#include "udp_basic.h"

namespace udp
{
// 
typedef struct
{
    uint8_t header[2];
    uint8_t state;
    double udp_motor_receive[12]; 
    uint32_t check_digit;
} __attribute__((packed)) ReceiveData;

// 
typedef struct
{
    uint8_t header[2];
    uint8_t state;
    double udp_imu_send[10];
    uint32_t check_digit;
} __attribute__((packed)) SendData;

} // namespace udp

class UdpComm
{
  public:
    UdpComm(uint16_t local_port, const std::string &target_ip, uint16_t target_port);
    ~UdpComm() = default;
    bool init(void);
    bool receive(int32_t max_wait_ms = -1); // default: blocking(-1)
    bool send(void);
    void setSendData(const udp::SendData &data);
    [[nodiscard]] const udp::ReceiveData &getReceiveData(void) const;

  private:
    uint16_t local_port_{}, target_port_{};
    std::string target_ip_{};
    std::unique_ptr<udp_client_server::udp_server> p_server_ = nullptr;
    std::unique_ptr<udp_client_server::udp_client> p_client_ = nullptr;
    uint8_t receive_buffer_[sizeof(udp::ReceiveData)]{};
    udp::SendData udp_send_data_{};
    udp::ReceiveData udp_receive_data_{};
};
