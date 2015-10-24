// basic file operations
#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <stdio.h>
#include <exception>
#include <vector>
#include <sstream>      // std::ostringstream

using namespace std;

class DockerNotExistsException: public exception {
};

class Machine {
    string host, ip;
    public:
        Machine(string, string);
        string get_entry();
};

Machine::Machine(string _host, string _ip) {
    host = _host;
    ip = _ip;
}

string Machine::get_entry() {
    std::ostringstream stringStream;
    stringStream << ip << '\t' << host << ".docker.local";
    return stringStream.str();
}

void process_line(string line) {
    cout << line << '\n';
}

string get_docker_machines() {
    FILE* pipe = popen("docker-machine ls", "r");
    if (!pipe) {
        throw DockerNotExistsException();
    }
    char buffer[128];
    std::string result = "";
    while (!feof(pipe)) {
        if (fgets(buffer, 128, pipe) != NULL)
            result += buffer;
    }
    pclose(pipe);
    return result;
}

vector<string> add_machines(ostream &out, string result) {
    size_t pos = 0;
    int row = 0;
    std::regex re_machine("([a-zA-Z0-9]+)[\\s\\*]+\\w+\\s+Running\\s+tcp://([^:]+).*");
    std::smatch match;

    vector<string> machines;

    std::string token;
    while ((pos = result.find("\n")) != std::string::npos) {
        token = result.substr(0, pos);
        if( row > 0 ) {
            if( std::regex_search(token, match, re_machine) ) {
                int result_index = 0;
                string host,ip;
                for (auto x:match) {
                    if( result_index == 1 ) {
                        host = x;
                    }
                    if( result_index == 2 ) {
                        ip = x;
                    }
                    result_index++;
                }
                Machine machine(host, ip);
                out << machine.get_entry() << endl;
            }
        }
        result.erase(0, pos + 1);
        row++;
    }
    return machines;
}

void backup(string filename) {
    std::ifstream  src(filename, std::ios::binary);
    std::ofstream  dst(filename+".0", std::ios::binary);
    dst << src.rdbuf();
}

int main (int argc, char* argv[]) {
    string line;
    string docker_machines = get_docker_machines();
    backup("/etc/hosts");
    ifstream backupfile("/etc/hosts.0");
    ofstream hostfile("/etc/hosts");

    if( backupfile.is_open() && hostfile.is_open() ) {
        while( getline(backupfile, line) ) {
            std::size_t found = line.find(".docker.local");
            if( found == std::string::npos) {
                hostfile << line << endl;
            }
        }
        add_machines(hostfile, docker_machines);
        hostfile.close();
        backupfile.close();
    }
    return 0;
}
