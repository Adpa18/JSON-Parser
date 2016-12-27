#include <iostream>
#include "Parser.hpp"

#include <list>
#include <dirent.h>
#include <cassert>
#include <string>
#include <fstream>
#include <streambuf>

std::list<std::string>  getAllFilesRecurive(std::string const &folder, std::string const &parent = "") {
    std::list<std::string>  files;

    DIR             *dir;
    struct dirent   *ent;

    if ((dir = opendir(folder.c_str())) != NULL) {
        while ((ent = readdir(dir)) != NULL)
        {
            std::string filename = std::string(ent->d_name);
            if (filename == "." || filename == "..") {
                continue;
            }
            if (ent->d_type == DT_DIR) {
                files.merge(getAllFilesRecurive(folder + filename + "/", filename + "/"));
            } else {
                files.push_back(parent + filename);
            }
        }
        closedir(dir);
    } else {
        std::cerr << "Cannnot open folder " + folder << std::endl;
    }
    return files;
}

std::string readFile(std::string const &filename) {
    std::ifstream t(filename);
    return std::string((std::istreambuf_iterator<char>(t)), std::istreambuf_iterator<char>());
}

void    UnitTests() {
    std::list<std::string> files = getAllFilesRecurive("Tests");

    unsigned nbTest = 0;
    for (std::string file: files) {
        JSON::Parser parser("Tests/" + file);
        JSON::Object *object = parser.Parse();

        std::stringstream ss;

        ss << *object;
        std::cout << object << std::endl;
        std::cout << readFile("Results/" + file);
//        assert(ss.str() == readFile("Results/" + file));
        std::cout << "\t\033[1;34m" << file << " test " << ++nbTest <<  "/" << files.size() << " passed" << "\033[0m" << std::endl;
        delete object;
    }
}

int main() {
//    JSON::Object    *object = new JSON::Object();
//    JSON::Object    *object2 = new JSON::Object();
//
//    object2->set("toto", "cc");
//    object->set("tata", 3);
//    object->set("toto", object2);
//
//    int a;
//    object->get("tata", a);
//    std::cout << object->getInt("tata") << std::endl;
//    std::cout << object->getObject("toto")->getString("toto") << std::endl;
//    std::cout << a << std::endl;

//    UnitTests();

    JSON::Parser parser("test.json");
    JSON::Object *object = parser.Parse();
    std::cout << object << std::endl;
    std::cout << (*object)["toto"] << std::endl;
    delete object;
    return 0;
}