#ifndef MAPSLOADER_H
#define MAPSLOADER_H

#include <fstream>

class MapsLoader
{
    public:
        /** Default constructor */
        MapsLoader();
        /** Default destructor */

        void load_maps( char*** );


        virtual ~MapsLoader();


    protected:

    private:

};

#endif // MAPSLOADER_H
