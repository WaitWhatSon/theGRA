#include "MapsLoader.h"
#include <iostream>
#include <fstream>

MapsLoader::MapsLoader()
{
    //ctor
}

MapsLoader::~MapsLoader()
{
    //dtor
}

void MapsLoader::load_maps(char*** map_pointer)
{
        FILE *src;

        char* map_names[] = {   "files/mapA.txt", "files/mapB.txt", "files/mapC1.txt",
                                "files/mapC2.txt", "files/mapAP0_1.txt", "files/mapAP0_2.txt",
                                "files/mapAP1_1.txt", "files/mapAP1_2.txt", "files/mapAP2_1.txt",
                                "files/mapAP2_2.txt"};

        char znak;

        std::cout << "elo0";

        for (int map_number = 0; map_number < 10; map_number++)
        {
            std::cout << "ladowanie mapy nr " << map_number << std::endl;
            src = fopen (map_names[map_number], "r");
            znak = fgetc(src);

            for (int i=0; i < 15; i++)
            {

                for (int j=0; j < 77; j++)
                {
                    if(znak != EOF)
                    {
                        if(znak == '\n' || znak == '\r')
                        {
                            j=-1;
                        }
                        else
                        {
                            map_pointer[map_number][i][j] = znak;
                        }
                        znak = fgetc(src);

                    }
                }
            }
        }

        fclose(src); //zamykamy plik
    }
