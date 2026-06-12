#include <iostream>
#include <vector>
#include <map>
#include <functional>
#include <numeric>
#include <algorithm>
#include <thread>
#include <chrono>

class TinyFactory {
private:
    std::map<int, std::function<char()>> machines;

public:
    void installMachine(int slot, std::function<char()> machine) {
        machines[slot] = machine;
    }

    char pressButton(int slot) {
        std::this_thread::sleep_for(std::chrono::milliseconds(30));
        return machines[slot]();
    }
};

int main() {
    TinyFactory factory;

    std::vector<int> secretNumbers = {
        72, 101, 108, 108, 111, 44, 32,
        119, 111, 114, 108, 100, 33
    };

    for (int i = 0; i < secretNumbers.size(); i++) {
        factory.installMachine(i, [secretNumbers, i]() {
            std::vector<int> pointlessBox(100);

            std::iota(pointlessBox.begin(), pointlessBox.end(), 0);

            int completelyUnnecessaryNumber =
                *std::find(pointlessBox.begin(), pointlessBox.end(), secretNumbers[i] % 100);

            return static_cast<char>(
                completelyUnnecessaryNumber + (secretNumbers[i] / 100) * 100
            );
        });
    }

    std::string finalMessage;

    for (int i = 0; i < secretNumbers.size(); i++) {
        char letter = factory.pressButton(i);

        std::vector<char> conveyorBelt;
        conveyorBelt.push_back(letter);

        std::reverse(conveyorBelt.begin(), conveyorBelt.end());

        finalMessage += conveyorBelt[0];
    }

    std::cout << finalMessage << std::endl;

    return 0;
}
