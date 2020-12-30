#include "MapsLoader.h"

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
    char* map_names[] = {   "files/maps_text/mapA.txt",     "files/maps_text/mapB.txt",
                            "files/maps_text/mapC1.txt",    "files/maps_text/mapC2.txt",
                            "files/maps_text/mapAP0_1.txt", "files/maps_text/mapAP0_2.txt",
                            "files/maps_text/mapAP1_1.txt", "files/maps_text/mapAP1_2.txt",
                            "files/maps_text/mapAP2_1.txt", "files/maps_text/mapAP2_2.txt"};
    char znak;
    for (int map_number = 0; map_number < 10; map_number++)
    {
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
