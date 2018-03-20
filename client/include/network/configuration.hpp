
/// Store values used to communicate in the namespace net::config.

#pragma once

#include <cstdint>
#include <chrono>

namespace net {

    constexpr uint16_t welcoming_server_port = 26'789;

    class configuration {
    public:
        float ping_time() const { return pingTime_; }

        void begin_ping_measure();
        void end_ping_measure();
    private:
        float pingTime_;
        std::chrono::time_point<std::chrono::system_clock> pingBegin_;
    };

    extern configuration gConfig;

}
