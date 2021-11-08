#include <iostream>
#include <fstream>
#include <thread>

class server {
public:

    std::string filepath;
    bool escape = false;

    explicit server(char* args[]) {
        if (args[1])
            filepath = args[1];
    }

    void start() const {
        std::ofstream pipefile;
        std::string textstream;
        pipefile.open("example.txt", std::ios_base::app);
        while(1) {
            std::getline(std::cin, textstream);
            pipefile << textstream  << std::endl;
            std::cout << textstream << " " << filepath << std::endl;
        }
        pipefile.close();
    }

    //void stop(){
        //while(std::cin.get() != 46){
         //  escape = false;
       // }
       // escape = true;
    //}
};

int main(int argc, char* argv[]) {
    server server(argv);
    std::thread t1(&server::start, server);
    //std::thread t2(&server::stop, server);
    t1.join();
    //t2.join();
    return 0;
}
