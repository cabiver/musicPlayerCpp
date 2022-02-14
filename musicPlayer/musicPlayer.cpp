#include <stdio.h>
#include <irrKlang.h>
#include <conio.h>
#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>
#include <direct.h>

#include <sstream>


using namespace irrklang;

using json = nlohmann::json;
using std::to_string;

std::string split(std::string dir)
{
    std::string datos[12];
    std::string lectura;
    std::stringstream input_stringstream(dir);
    int sizePath = 0;

    while (getline(input_stringstream, lectura, '\\'))
    {
        //std::cout << "Un valor: " << lectura << std::endl;
        datos[sizePath] = lectura;
        sizePath++;
    }
    const size_t n = sizeof(datos) / sizeof(datos[0]);
    
    std::string arr = "";

    for (int x = 0; x < (sizePath-1); x++) {
        for (size_t j = 0; j < datos[x].length(); j++)
        {
            //std::cout << datos[x][j];
            arr += datos[x][j];
        }
        arr += '\\';
        //std::cout << '\\';
    }
    return arr;
}




void show_volumens(json j, int indeces) {
    system("cls");
    for (size_t i = 0; i < j.size(); i++)
    {
        if (indeces == i) {
            std::cout << " >" << j[i]["volumen"] << std::endl;
        }
        else {
            std::cout << "  " << j[i]["volumen"] << std::endl;
        }
    }
}
void show_songs(json j, int indeces, int song) {
    system("cls");
    for (size_t i = 0; i < j[indeces]["songs"].size(); i++)
    {
        if (song == i) {
            std::cout << " >" << j[indeces]["songs"][i]["name"] << std::endl;
        }
        else {
            std::cout << "  " << j[indeces]["songs"][i]["name"] << std::endl;
        }
    }
}

int main(int argc, const char** argv)
{
    ISoundEngine* engine = createIrrKlangDevice();
    if (!engine)
    {
        printf("Could not startup engine\n");
        return 0;
    }

    
    const char* dirname = argv[0];
    std::string dirString = dirname;
    //split funtions get the path of file
    std::string pathfuntion = split(dirString);
    
    //if you want to use this as env variable, need the path of the file, without it the program don´t find the json file
    std::ifstream data_json(pathfuntion +"test.json");   
    
    json j = json::parse(data_json);
    int valueChar = NULL;
    char key = NULL;
    bool quiet_program = true;

    while (quiet_program) {

        bool get_Album = true;
        bool get_song = true;
        int index = 0;
        int index_song = 0;
        show_volumens(j, 0);

        while (get_Album) {
            key = _getch();


            if (key) {
                valueChar = key;
                if (valueChar == 80) {
                    if ((j.size() - 1) > index) {
                        index++;
                        show_volumens(j, index);
                    }
                }
                if (valueChar == 72) {
                    if (0 < index) {
                        index--;
                        show_volumens(j, index);
                    }
                }
                if (valueChar == 13) {
                    std::cout << "salio asi";
                    get_Album = false;
                }
            }
        }

        show_songs(j, index, index_song);
        while (get_song)
        {
            key = _getch();
            if (key) {
                valueChar = key;
                if (valueChar == 80) {
                    if (j[index]["songs"].size() > index_song) {
                        index_song++;
                        show_songs(j, index, index_song);
                    }
                }
                if (valueChar == 72) {
                    if (0 < index_song) {
                        index_song--;
                        show_songs(j, index, index_song);
                    }
                }
                if (valueChar == 13) {
                    engine->removeAllSoundSources();
                    std::cout << "salio asi" << std::endl;
                    std::string url = pathfuntion + "media/";
                    url += j[index]["songs"][index_song]["url"];
                    const char* fol = url.c_str();
                    std::cout << fol << std::endl;
                    engine->play2D(fol, true);
                    get_song = false;
                }
            }
        }
    }

    engine->drop();
    return 0;
}