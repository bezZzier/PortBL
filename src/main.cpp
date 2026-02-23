#include <iostream>
#include <map>
#include <string>
#include <cstdlib>
#include <fstream>
#include <algorithm>
#include <cctype>

std::map<std::string, int> alias_to_port = {

};

int input_type(std::string input) {
    // if is alias
    if (alias_to_port.count(input)) {
        return 1;
    }

    // if is port number
    if (!input.empty() && std::all_of(input.begin(), input.end(), ::isdigit)) {
        return 2;
    }

    // neither port nor alias
    return 0;
}

int main(int argc, char const *argv[]) {
    std::ifstream fin;
    std::ofstream fout;
    std::string homedir = std::getenv("HOME");
    std::string datapath = homedir + "/.portbl_data";

    fin.open(datapath);
        if (fin.is_open()) {
            std::string name;
            int port;
            while (fin >> name >> port) {
                alias_to_port[name] = port;
            }
            fin.close();
    }

    if (argc == 4) {
        std::string arg1 = argv[1];
        std::string arg2 = argv[2];
        std::string arg3 = argv[3];

        if (arg1 == "add") {
            std::string portname = arg2;
            try {
                int portint = std::stoi(arg3);
                alias_to_port[portname] = portint;

                std::cout << "Alias " << portname << " added to port " << portint << ". " << "\n";

                fout.open(datapath);
                for (auto const& [name, port] : alias_to_port) {
                    fout << name << " " << port << "\n";
                }
                fout.close();
            } catch (...) {
                std::cout << "Error: '" << argv[3] << "' is not a valid port number." << "\n";
            }
        }
    }

    if (argc == 3) {
        std::string arg1 = argv[1];
        std::string arg2 = argv[2];
        if(arg1 == "delete" || arg1 == "unalias") {
            if (input_type(arg2) == 1) {
                alias_to_port.erase(arg2);
                std::cout << "Succesfully unaliased the port." << "\n";
            }
            else if (input_type(arg2) == 2) {
                
            }
        }
    }

    if (argc == 2) {
        std::string arg1 = argv[1];
        if (arg1 == "list") {
                for (auto const& [portname, port] : alias_to_port) {
                    std::cout << portname << "'s port number is " << port << ".\n"; 
            }
        }
        if (arg1 == "help") {
            std::cout << "--- PortBL Commands ---" << "\n";
            std::cout << "pbl list - Lists all aliases and their corresponding port number." << "\n";
            std::cout << "pbl add [alias] [port number]" << "\n";
            std::cout << "\n";
        }
    }
    if (argc == 1) {
        std::cout << "--- PortBL Commands ---" << "\n";
        std::cout << "pbl list - Lists all aliases and their corresponding port number." << "\n";
        std::cout << "pbl add [alias] [port number] - adds an alias " << "\n";
        std::cout << "pbl clear - ";
        std::cout << "\n";
    }

    return 0;
}
    
