# Facade
Facade provides a unified interface to a set of interfaces in a subsystem.
Facade knows which subsystem classes are responsible for a request. It delegates client
requests to appropriate subsystem objects.
It promotes weak coupling between the subsystem and its clients.
```cpp
#include <iostream>

// Subsystem classes
class AudioSystem {
public:
    void turnOn() {
        std::cout << "Audio system turned on." << std::endl;
    }

    void playMusic() {
        std::cout << "Playing music." << std::endl;
    }
};

class VideoSystem {
public:
    void turnOn() {
        std::cout << "Video system turned on." << std::endl;
    }

    void playVideo() {
        std::cout << "Playing video." << std::endl;
    }
};

class InputSystem {
public:
    void turnOn() {
        std::cout << "Input system turned on." << std::endl;
    }

    void readInput() {
        std::cout << "Reading input." << std::endl;
    }
};

// Facade class
class MultimediaFacade {
public:
    MultimediaFacade() {
        audioSystem = new AudioSystem();
        videoSystem = new VideoSystem();
        inputSystem = new InputSystem();
    }

    void start() {
        audioSystem->turnOn();
        videoSystem->turnOn();
        inputSystem->turnOn();
    }

    void playMedia() {
        audioSystem->playMusic();
        videoSystem->playVideo();
        inputSystem->readInput();
    }

private:
    AudioSystem* audioSystem;
    VideoSystem* videoSystem;
    InputSystem* inputSystem;
};

int main() {
    MultimediaFacade multimediaFacade;

    // Simplified interface provided by the facade
    multimediaFacade.start();
    multimediaFacade.playMedia();

    return 0;
}
```
