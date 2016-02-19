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

bool promptyorn(std::string pstring)
{
    while(1)
    {
        std::string buf;

        std::cout << pstring;

        std::getline(std::cin, buf);

        if(buf == "y" || buf == "Y" || buf == "yes" || buf == "YES") return true;
        else if(buf == "n" || buf == "N" || buf == "no" || buf == "NO") return false;
    }
    return false;
}

void hitReturn(std::string str = std::string("Hit return to continue..."))
{
    std::string buf;
    std::cout << str;
    std::getline(std::cin, buf);
}
void printAlbum(Album *talbum)
{
    if(talbum == NULL)
    {
        std::cout << "Error : album is NULL\n";
        return;
    }

    std::cout << "Album Title : " << talbum->albumName << std::endl;
    std::cout << "Artist      : " << talbum->bandName << std::endl;
    std::cout << "Release Year: " << talbum->year << std::endl;

    std::cout << "\n";
    std::cout << talbum->tracks.size() << " Tracks.\n";
    for(int i = 0; i < int(talbum->tracks.size()); i++)
    {
        std::cout << "     " << i+1 << "." << talbum->tracks[i].trackName << std::endl;
    }
}

bool addNewTrack(Album *talbum)
{
    if(talbum == NULL) return false;

    Track newtrack;

    std::string buf;

    std::cout << "\nEnter track name : ";
    std::getline(std::cin, buf);
    newtrack.trackName = buf;

    std::cout << "Enter track length (sec) : ";
    std::getline(std::cin, buf);
    newtrack.lengthInSec = atoi(buf.c_str());

    if(promptyorn("Add this track? (y/n)"))
    {
        talbum->tracks.push_back(newtrack);
        return true;
    }
    else return false;
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

    printAlbum(&newalbum);

    while(promptyorn("Add new track? (y/n)"))
    {
        addNewTrack(&newalbum);
    }

    if(promptyorn("Save album? (y/n)"))
    {
        albums.push_back(newalbum);
        return true;
    }
    else return false;
}

void printAlbumList()
{
    std::cout << "\nAlbums:\n";
    for(int i = 0; i < int(albums.size()); i++) std::cout << i+1 << ". " << albums[i].albumName << std::endl;
}

Album *selectAlbum()
{
    Album *talbum = NULL;

    if(albums.empty())
    {
        hitReturn("Album list is empty!");
        return talbum;
    }

    std::string abuf;
    int abufnum = 0;
    printAlbumList();
    std::cout << "Show details for which album? [1-" << albums.size() << "] : ";
    std::getline(std::cin, abuf);
    abufnum = atoi(abuf.c_str())-1;

    if(abufnum < 0 || abufnum >= int(albums.size()) )
    {
        hitReturn("Not a valid album #!");
        return talbum;
    }

    return &albums[abufnum];
}

void editTracks(Album *talbum)
{
    bool quit = false;

    if(talbum == NULL) return;

    std::vector<Track> *tracks = &talbum->tracks;

    while(!quit)
    {
        std::cout << "Total tracks : " << tracks->size() << std::endl;
        for(int i = 0; i < int(tracks->size()); i++)
        {
            std::cout << i+1 << ". " << (*tracks)[i].trackName << std::endl;
        }

        std::cout << "\n\n[n]ew track\n";
        std::cout << "[e]dit track\n";
        std::cout << "[d]elete track\n";
        std::cout << "e[x]it\n\n";

        std::string buf;
        std::cout << "\nEnter selection : ";
        std::getline(std::cin, buf);

        if(buf == "n") addNewTrack(talbum);
        else if(buf == "e")
        {
            std::string tbuf;
            int tnum = 0;
            std::cout << "Edit which track #? : ";
            std::getline(std::cin, tbuf);
            tnum = atoi(tbuf.c_str()) - 1;

            if(tnum < 0 || tnum >= int(tracks->size()) )
            {
                hitReturn("Not a valid track #!");
                continue;
            }

            std::cout << "Enter new track name :";
            std::getline(std::cin, tbuf);
            (*tracks)[tnum].trackName = tbuf;

            std::cout << "Enter new track time in seconds :";
            std::getline(std::cin, tbuf);
            (*tracks)[tnum].lengthInSec = atoi(tbuf.c_str());

        }
        else if(buf == "d")
        {
            std::string tbuf;
            int tnum = 0;
            std::cout << "Delete which track #? : ";
            std::getline(std::cin, tbuf);
            tnum = atoi(tbuf.c_str()) - 1;

            if(tnum < 0 || tnum >= int(tracks->size()) )
            {
                hitReturn("Not a valid track #!");
                continue;
            }
        }
    }
}

void editAlbum(Album *talbum)
{
    bool quit = false;

    if(talbum == NULL) return;

    Album originalalbum = *talbum;

    while(!quit)
    {
        std::string buf;

        std::cout << "\n\n";
        std::cout << "Album [t]itle : " << talbum->albumName << std::endl;
        std::cout << "[a]rtist      : " << talbum->bandName << std::endl;
        std::cout << "Release [y]ear: " << talbum->year << std::endl;
        std::cout << "Edit Trac[k]s...\n";
        std::cout << "\n[s]ave changes\n";
        std::cout << "[d]iscard changes\n";
        std::cout << "[r]emove album\n\n";

        std::cout << "Enter selection : ";
        std::getline(std::cin, buf);

        if(buf == "d")
        {
            *talbum = originalalbum;
            quit = true;
        }
        else if(buf == "s") quit = true;
        else if(buf == "t")
        {
            std::string ntitle;
            std::cout << "New album title :";
            std::getline(std::cin, ntitle);
            talbum->albumName = ntitle;
        }
        else if(buf == "a")
        {
            std::string nartist;
            std::cout << "New artist name :";
            std::getline(std::cin, nartist);
            talbum->bandName = nartist;
        }
        else if(buf == "y")
        {
            std::string nyear;
            std::cout << "New release year :";
            std::getline(std::cin, nyear);
            talbum->year = atoi(nyear.c_str());
        }
        else if(buf == "k")
        {
            editTracks(talbum);
        }
        else if(buf == "r")
        {
            if(promptyorn("Really delete this album? (y/n)"))
            {
                for(int i = 0; i < int(albums.size()); i++)
                {
                    if( &albums[i] == talbum)
                    {
                        albums.erase(albums.begin() + i);
                        talbum = NULL;
                        return;
                    }
                }
            }
        }
    }


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
        menuitems.push_back("Edit Album");
        menuitems.push_back("List Albums");
        menuitems.push_back("Show Album Details");
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
        else if(menuitems[selection] == "List Albums")
        {
            printAlbumList();
            hitReturn();
        }
        else if(menuitems[selection] == "Show Album Details")
        {
            Album *talbum = selectAlbum();

            if(talbum != NULL)
            {
                printAlbum(talbum);
                hitReturn();
            }
        }
        else if(menuitems[selection] == "Edit Album")
        {
            editAlbum(selectAlbum());
        }
    }

}

int main(int argc, char *argv[])
{

    mainMenu();

    return 0;
}
