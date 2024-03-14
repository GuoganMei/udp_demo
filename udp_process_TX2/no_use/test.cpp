
#include "udp_comm.h"

/* c system header files */

/* c++ standard library header files */
#include <condition_variable>
#include <mutex>
#include <thread>

/* external project header files */
#include "gtest/gtest.h"

/* internal project header files */

TEST(ElspiderMiniInterface, udpBlocking)
{
    UdpComm udp_comm(7, "192.168.5.10", 10);
    udp::SendData udp_send_data{};
    std::mutex mutex;
    std::condition_variable cv;
    bool receive_flag = false;

    std::thread thread([&]() {
        if (!udp_comm.init())
            FAIL();
        udp_comm.setSendData(udp_send_data);
        udp_comm.send();
        receive_flag = udp_comm.receive(); // blocking
        cv.notify_one();
    });
    thread.detach();

    std::unique_lock<std::mutex> unique_lock(mutex);
    if (cv.wait_for(unique_lock, std::chrono::milliseconds(100)) == std::cv_status::timeout ||
        !receive_flag)
    {
        FAIL();
    }
}

TEST(ElspiderMiniInterface, udpNonBlocking)
{
    UdpComm udp_comm(7, "192.168.5.10", 10);
    udp::SendData udp_send_data{};
    bool receive_flag = false;

    if (!udp_comm.init())
        FAIL();
    udp_comm.setSendData(udp_send_data);
    udp_comm.send();
    receive_flag = udp_comm.receive(100); // non-blocking
    if (!receive_flag)
        FAIL();
}

TEST(ElspiderMiniInterface, motorComm)
{
    UdpComm udp_comm(7, "192.168.5.10", 10);
    udp::SendData udp_send_data{};
    udp::ReceiveData udp_receive_data{};
    bool receive_flag = false;

    if (!udp_comm.init())
        FAIL();
    udp_send_data.state = static_cast<uint8_t>(CommBoardState::kNormal);
    udp_comm.setSendData(udp_send_data);
    udp_comm.send();
    receive_flag = udp_comm.receive(100);

    if (receive_flag)
        udp_receive_data = udp_comm.getReceiveData();
    else
        FAIL();

    if (udp_receive_data.state != static_cast<uint8_t>(CommBoardState::kNormal))
        FAIL();

    for (int i = 0; i < 18; ++i)
    {
        if (!static_cast<bool>(udp_receive_data.udp_motor_receive->temp))
            FAIL();
    }
}

TEST(ElspiderMiniInterface, imuComm)
{
}
