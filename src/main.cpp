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
        
        if (arg1 == "unalias") {
            int type = input_type(arg2);

            if (type == 1) { // its an alias
                alias_to_port.erase(arg2);
                std::cout << "Successfully unaliased '" << arg2 << "'.\n";
            } 
            else if (type == 2) { // its a port number
                int targetPort = std::stoi(arg2);
                std::string foundAlias = "";

                // find the alias that matches this port
                for (auto const& [name, port] : alias_to_port) {
                    if (port == targetPort) {
                        foundAlias = name;
                        break; 
                    }
                }

                if (!foundAlias.empty()) {
                    alias_to_port.erase(foundAlias);
                    std::cout << "Successfully removed alias '" << foundAlias << "' for port " << targetPort << ".\n";
                } else {
                    std::cout << "No alias found for port " << targetPort << ".\n";
                }
            } 
            else {
                std::cout << "Error: '" << arg2 << "' is neither a known alias nor a port number.\n";
            }

            // save after a successful change
            fout.open(datapath);
            for (auto const& [name, port] : alias_to_port) {
                fout << name << " " << port << "\n";
            }
            fout.close();
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
            std::cout << "pbl add [alias] [port number] - Add an alias to a specfic port." << "\n";
            std::cout << "pbl clear - clears all port aliases";
            std::cout << "pbl unalias [alias / port number] - Removes an alias from a port.";
            std::cout << "\n";
        }
    }
    if (argc == 1) {
            std::cout << "--- PortBL Commands ---" << "\n";
            std::cout << "pbl list - Lists all aliases and their corresponding port number." << "\n";
            std::cout << "pbl add [alias] [port number] - Add an alias to a specfic port." << "\n";
            std::cout << "pbl clear - clears all port aliases";
            std::cout << "pbl unalias [alias / port number] - Removes an alias from a port.";
            std::cout << "\n";
    }

    return 0;
}
    
