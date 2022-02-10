#include <stdio.h>
#include <irrKlang.h>
#include <conio.h>
#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>


using namespace irrklang;

using json = nlohmann::json;
using std::to_string;



void show_volumens(json j, int indeces) {
    system("cls");
    //std::cout << indeces;
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
    //std::cout << indeces;

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

    //engine->play2D("./media/something.mp3", true);

    //printf("\nHello World!\n");
    //printf("%d ",argc);
    //printf(argv[1]);


    bool quiet_program = true;

    std::ifstream datajson("test.json");
    json j;
    datajson >> j;
    int valueChar;
    char key;

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

                //std::cout << "key: " << key << ", value: " << valueChar << std::endl;

                if (valueChar == 80) {


                    if ((j.size() - 1) > index) {
                        index++;
                        show_volumens(j, index);
                    }
                }
                //std::cout << (valueChar == 72);
                if (valueChar == 72) {

                    if (0 < index) {
                        index--;
                        show_volumens(j, index);
                    }
                }
                if (valueChar == 13) {
                    std::cout << "salio asi";
                    get_Album = false;
                    //engine->play2D("./media/something.mp3", true);
                }
            }
        }

        show_songs(j, index, index_song);
        while (get_song)
        {
            key = _getch();


            if (key) {
                valueChar = key;

                //std::cout << "key: " << key << ", value: " << valueChar << std::endl;

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
                    //engine->drop();
                    engine->removeAllSoundSources();
                    std::cout << "salio asi" << std::endl;
                    std::string url = "./media/";
                    url += j[index]["songs"][index_song]["url"];

                    const char* fol = url.c_str();
                    std::cout << fol << std::endl;
                    engine->play2D(fol, true);
                    get_song = false;
                }
            }
        }
    }

    //engine->drop();
    return 0;
}