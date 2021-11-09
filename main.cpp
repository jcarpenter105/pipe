#include <iostream>
#include <fstream>
#include <thread>
#include <csignal>

static bool escape = false;

class server {

public:

    std::string filepath;

    explicit server(char* args[]) {
        if (args[1])
            filepath = args[1];
    }

    void start() const {
        std::ofstream pipefile;
        std::string textstream;
        pipefile.open("example.txt", std::ios_base::app);
        while(!escape) {
            std::getline(std::cin, textstream);
            pipefile << textstream  << std::endl;
            std::cout << textstream << " " << filepath << std::endl;
        }
        pipefile.close();
    }

    static void stop(int signum){
        std::cout<<"test"<<std::endl;
        escape = true;
    }
};

int main(int argc, char* argv[]) {
    signal(SIGINT, server::stop);
    server server(argv);
    std::thread t1(&server::start, server);
    t1.join();
    return 0;
}
