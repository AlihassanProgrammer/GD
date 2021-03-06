#include "GDCore/Project/ResourcesLoader.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "GDCore/Tools/FileStream.h"
#include "GDCore/String.h"
#include <fstream>
#include <iostream>
#include <utility>
#include <cstring>
#undef LoadImage //Undef a macro from windows.h

using namespace std;

namespace gd
{

ResourcesLoader * ResourcesLoader::_singleton = NULL;

void ResourcesLoader::LoadSFMLImage( const gd::String & filename, sf::Image & image )
{
    gd::SFMLFileStream stream;
    if (!stream.open(filename) || !image.loadFromStream(stream))
        cout << "Failed to load a SFML image: " << filename << endl;
}

sf::Texture ResourcesLoader::LoadSFMLTexture(const gd::String & filename)
{
    sf::Texture texture;
    LoadSFMLTexture(filename, texture);

    return texture;
}

void ResourcesLoader::LoadSFMLTexture( const gd::String & filename, sf::Texture & texture )
{
    gd::SFMLFileStream stream;
    if (!stream.open(filename) || !texture.loadFromStream(stream))
        cout << "Failed to load a SFML texture: " << filename << endl;
}

std::pair<sf::Font *, StreamHolder *> ResourcesLoader::LoadFont(const gd::String & filename)
{
    sf::Font * font = new sf::Font();
    StreamHolder * streamHolder = new StreamHolder();

    if (!streamHolder->stream.open(filename) || !font->loadFromStream(streamHolder->stream))
    {
        cout << "Failed to load a font from a file: " << filename << endl;
        delete font;
        delete streamHolder;
        return std::make_pair((sf::Font*)nullptr, (StreamHolder*)nullptr);
    }

    return std::make_pair(font, streamHolder);
}

sf::SoundBuffer ResourcesLoader::LoadSoundBuffer( const gd::String & filename )
{
    sf::SoundBuffer sbuffer;
    gd::SFMLFileStream stream;
    if (!stream.open(filename) || !sbuffer.loadFromStream(stream))
        cout << "Failed to load a sound buffer: " << filename << endl;

    return sbuffer;
}

gd::String ResourcesLoader::LoadPlainText( const gd::String & filename )
{
    gd::String text;
    gd::FileStream file(filename, ios::in);

    if(!file.fail())
    {
        std::string ligne;
        while(getline(file, ligne))
            text += gd::String::FromUTF8(ligne)+"\n";

        file.close();
    }
    else
        cout << "Failed to read a file: " << filename << endl;

    return text;
}


/**
 * Load a binary text file
 */
char* ResourcesLoader::LoadBinaryFile( const gd::String & filename )
{
    gd::FileStream file (filename, ios::in|ios::binary|ios::ate);
    if (file.is_open()) {
        iostream::pos_type size = file.tellg();
        char * memblock = new char [size];
        file.seekg (0, ios::beg);
        file.read (memblock, size);
        file.close();

        return memblock;
    }

    cout << "Binary file " << filename << " can't be loaded into memory " << endl;
    return NULL;
}

long int ResourcesLoader::GetBinaryFileSize( const gd::String & filename)
{
    gd::FileStream file (filename, ios::in|ios::binary|ios::ate);
    if (file.is_open()) {
        return file.tellg();
    }

    std::cout << "Binary file " << filename << " cannot be read. " << std::endl;
    return 0;
}

}
