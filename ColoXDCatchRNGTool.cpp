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
    uint32_t initSeed, finalInitSeed;
    unsigned long startingAdvances = 0, advances = 0, hittedAdvances = 0, testedAdvances = 0;
    int counter, catchRate = 0;
    bool found = false;

    cout << "Insert the Initial Seed: ";
    scanf("%X", &initSeed);

    cout << "Insert the Starting Advances: ";
    cin >> startingAdvances;

    cout << "Insert the Catch Rate Value: ";
    cin >> catchRate;

    startingAdvances += 150;

    for (int i = 0; i < startingAdvances; i++) {
        initSeed = XDRNG(initSeed);
    }

    advances = startingAdvances;

    for (unsigned long int j = 0; j < 4294967295 && found == false; j++) {
        counter = 0;

        while (getHighSeed(initSeed) < catchRate && counter < 10) {
            counter++;
            initSeed = XDRNG(initSeed);
            advances++;
        }

        if (counter == 10 && advances - 178 > startingAdvances) {
            finalInitSeed = initSeed;
            for (int i = 0; i < 6; i++) {
                initSeed = XDRNGR(initSeed);
            }
            printf("Seed: %08X - %08X | Advances: %lu - %lu\nTry Advances: %lu\n\n", initSeed, finalInitSeed, advances - 6, advances - 1, advances - 178);
            found = true;
        }
        else {
            initSeed = XDRNG(initSeed);
            advances++;
        }
    }

    while (true) {
        cout << "Tested Advances: ";
        cin >> testedAdvances;
        cout << "Hitted Advances: ";
        cin >> hittedAdvances;

        cout << "Try Advances: ";

        if (hittedAdvances > advances) {
            cout << int(testedAdvances - ((hittedAdvances - advances) * 0.875)) << endl << endl;
        }
        else {
            cout << int(testedAdvances + ((advances - hittedAdvances) * 0.875)) << endl << endl;
        }
    }

    return 0;
}
