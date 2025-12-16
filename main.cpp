#include <SFML/Audio.hpp>
#include <iostream>
#include <thread>
#include <chrono>

int main()
{
    sf::SoundBuffer buffer;
    if (!buffer.loadFromFile("../sound.wav"))
        return -1;

    sf::Sound sound;
    sound.setBuffer(buffer);
    sound.play();

    while (sound.getStatus() == sf::Sound::Playing)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    return 0;
}
