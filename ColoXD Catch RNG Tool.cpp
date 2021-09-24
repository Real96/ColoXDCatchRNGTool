#include<iostream>
#include <math.h>

using namespace std;

uint32_t XDRNG(uint32_t targetSeed) {
    return 0x000343FD * targetSeed + 0x00269EC3;
}

uint32_t XDRNGR(uint32_t targetSeed) {
    return 0xB9B33155 * targetSeed + 0xA170F641;
}

uint16_t getHighSeed(uint32_t targetSeed) {
    return targetSeed >> 16;
}

int main() {
    uint32_t startingSeed, finalStartingSeed;
    unsigned long frame = 0, hittedFrame = 0, testedFrame = 0;
    int counter = 0, catchRate = 0;
    bool found = false;

    cout << "Insert the Starting Seed: ";
    scanf("%X", &startingSeed);

    cout << "Insert the Starting Frame: ";
    cin >> frame;

    cout << "Insert the Catch Rate Value: ";
    cin >> catchRate;

    frame += 150;

    for (int i = 0; i < frame; i++) {
        startingSeed = XDRNG(startingSeed);
    }

    for (unsigned long int j = 0; j < 4294967295 && found == false; j++) {
        counter = 0;

        while (getHighSeed(startingSeed) < catchRate && counter < 10) {
            counter++;
            startingSeed = XDRNG(startingSeed);
            frame++;
        }

        if (counter == 10) {
            finalStartingSeed = startingSeed;
            for (int i = 0; i < 6; i++) {
                startingSeed = XDRNGR(startingSeed);
            }
            printf("Seed: %08X - %08X | Frame: %lu - %lu\nTry Frame: %lu\n\n", startingSeed, finalStartingSeed, frame - 6, frame - 1, frame - 3 - 175);
            found = true;
        }
        else {
            startingSeed = XDRNG(startingSeed);
            frame++;
        }
    }

    while (true) {
        cout << "Tested frame: ";
        cin >> testedFrame;
        cout << "Hitted frame: ";
        cin >> hittedFrame;

        cout << "Try Frame: ";

        if (hittedFrame > frame) {
            cout << floor(testedFrame - ((hittedFrame - (frame)) * 0.875)) << endl << endl;
        }
        else {
            cout << floor(testedFrame + (((frame) - hittedFrame) * 0.875)) << endl << endl;
        }
    }

    return 0;
}
