#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include "tinyxml2.h"

using namespace tinyxml2;

struct Track
{
    std::string trackName;
    int lengthInSec;
};

struct Album
{
    std::string albumName;
    std::string bandName;
    int year;

    std::vector<Track> tracks;
};

std::vector<Album> albums;

bool addNewTrack(Album *talbum)
{
    if(talbum == NULL) return false;


}

bool addNewAlbum()
{
    Album newalbum;
    std::string buf;

    system("cls");

    std::cout << "Enter Band Name : ";
    std::getline(std::cin, buf);
    newalbum.bandName = buf;

    std::cout << "Enter Album Name : ";
    std::getline(std::cin, buf);
    newalbum.albumName = buf;

    std::cout << "Enter Album Release Date : ";
    std::getline(std::cin, buf);
    newalbum.year = atoi(buf.c_str());




}

void mainMenu()
{
    bool quit = false;

    while(!quit)
    {
        system("cls");

        std::string buf;
        int selection = 0;

        std::vector<std::string> menuitems;
        menuitems.push_back("New Album");
        menuitems.push_back("Quit");

        std::cout << "Total Albums In Database : " << albums.size() << "\n\n";

        std::cout << "Menu\n";
        std::cout << "----\n\n";
        for(int i = 0; i < int(menuitems.size()); i++)
        {
            std::cout << i+1 << ". " << menuitems[i] << std::endl;
        }

        std::cout << "\n\n> ";

        std::getline(std::cin, buf);
        selection = atoi(buf.c_str()) - 1;

        if(selection < 0 || selection >= int(menuitems.size()) ) continue;
        else if(menuitems[selection] == "Quit") quit = true;
        else if(menuitems[selection] == "New Album") addNewAlbum();
    }

}

int main(int argc, char *argv[])
{

    mainMenu();

    return 0;
}
