#include "cards.hpp"

int main() {

    VertexStacks start;
    std::cin >> start;

    Solitaire game(start);

    bool result = game.run_loop();

    if (result) {
        std::cout << "We can solve we solitaire!!! :)" << std::endl;
    } else {
        std::cout << "Solitare can't be solved :(" << std::endl;
    }


    return 0;
}