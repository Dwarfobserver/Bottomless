
#include <network/configuration.hpp>

namespace net {

    void configuration::begin_ping_measure() {
        pingBegin_ = std::chrono::system_clock::now();
    }

    void configuration::end_ping_measure() {
        auto pingEnd = std::chrono::system_clock::now();
        std::chrono::duration<float> duration = pingEnd - pingBegin_;
        pingTime_ = duration.count();
    }

    configuration gConfig {};

}
