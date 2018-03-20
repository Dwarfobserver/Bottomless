
#include <iostream>
#include <utility.hpp>
//#include <asio.hpp>
#include <memory>
/*
namespace tcp  = boost::asio::ip::tcp;
namespace asio = boost::asio;
*/
int main() {
    std::cout << "Bottomless -- server v" << build::version_string
              << " (" << build::mode_string << ")\n";
    
    auto waitInput = defer([] { std::cin.get(); });
    try {/*
        asio::io_service ioService;
        tcp::acceptor acceptor(ioService, tcp::endpoint(tcp::v4(), 26'789));
        tcp::socket socket(ioService);
        acceptor.async_accept(socket, [&] {
            std::cout << "Get something !\n";
        });

        ioService.run();*/
    }
    catch(std::exception& e) {
        std::cout << "Exception caught :\n" << e.what() << '\n';
        return 1;
    }
}
