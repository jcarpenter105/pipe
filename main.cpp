#include <iostream>
#include <fstream>
#include <thread>
#include <csignal>

static bool escape = false; // flag for exiting the program

class server {
public:

    std::string filepath; // holds the path the piped file will be stored

    explicit server(char* args[]) {
        if (args[1])
            filepath = args[1];
    }
    
    // start() opens a file, scans for user input, then prints the user input to both command prompt and piped file
    void start() const {
        std::ofstream pipefile; // The piped file
        std::string textstream; // One line of text from the original file
        pipefile.open("example.txt", std::ios_base::app);
        while(!escape) {
            std::getline(std::cin, textstream);
            pipefile << textstream  << std::endl;
            std::cout << textstream << " " << filepath << std::endl;
        }
        pipefile.close();
    }

    // stop sets the flag to exit the while loop located in start
    static void stop(int signum){
        escape = true;
    }
};

int main(int argc, char* argv[]) {
    signal(SIGINT, server::stop); // declaring signal for interrupt (CTL+C)
    server server(argv); // initializing the server class with the first command line argument
    std::thread t1(&server::start, server);
    t1.join();
    return 0;
}
