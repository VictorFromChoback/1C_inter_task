#include <vector>
#include <optional>
#include <unordered_map>
#include <queue>
#include <string>
#include <iostream>


enum Cards {
    Six,
    Seven,
    Eight,
    Nine,
    Ten,
    Jack,
    Queen,
    King,
    Ace,
    Closed
};


class VertexStacks {

public:

    using StackType = std::vector<Cards>;
    using Table = std::vector<StackType>;
    static const size_t stacks_amount = 8;
    static const size_t cards_amount = 9;
    

    std::string convert() const& {
        static std::unordered_map<Cards, char> mapping;

        mapping[Six] = 'a';
        mapping[Seven] = 'b';
        mapping[Eight] = 'c';
        mapping[Nine] = 'd';
        mapping[Ten] = 'e';
        mapping[Jack] = 'f';
        mapping[Queen] = 'g';
        mapping[King] = 'h';
        mapping[Ace] = 'k';
        mapping[Closed] = 'l';

        // # is of new stack

        std::string answer = "";

        for (const auto& vect : stacks) {
            for (const auto& value : vect) {
                answer.push_back(mapping[value]);
            }
            answer.push_back('#');
        }

        return answer;
    }

    VertexStacks(const Table& init_table) : stacks(init_table) {}
    VertexStacks(Table&& init_table) : stacks(std::move(init_table)) {}
    VertexStacks() = default;
    VertexStacks(const VertexStacks& vertex) : stacks(vertex.stacks) {}
    VertexStacks& operator=(const VertexStacks& other) {
        stacks = other.stacks;
        return *this;
    }
    VertexStacks(VertexStacks&& vertex) : stacks(std::move(vertex.stacks)) {}
    VertexStacks(const std::string& code) {
        static std::unordered_map<char, Cards> mapping;

        mapping['a'] = Six;
        mapping['b'] = Seven;
        mapping['c'] = Eight;
        mapping['d'] = Nine;
        mapping['e'] = Ten;
        mapping['f'] = Jack;
        mapping['g'] = Queen;
        mapping['h'] = King;
        mapping['k'] = Ace;
        mapping['l'] = Closed;

        // # is of new stack

        std::string answer = "";

        stacks.resize(stacks_amount);

        size_t cur_vect = 0;

        for (char symbol : code) {
            if (symbol == '#') {
                cur_vect++;
                continue;
            }

            stacks[cur_vect].push_back(mapping[symbol]);
        }
    }

    VertexStacks make_hidden() const;

    friend std::istream& operator>>(std::istream& in, VertexStacks& obj);

    Table stacks;

};


class Solitaire {

public:

    using StatesTable = std::unordered_map<std::string, bool>;
    using StatesQueue = std::queue<VertexStacks>;

    Solitaire() = default;
    Solitaire(const VertexStacks& init) {
        states_[init.convert()] = true;
        real_ = init.make_hidden();
        queue_.push(real_);
    }

    void make_step();
    bool HasAchived();
    bool run_loop();


private:

    bool move_cards_(const VertexStacks& table, size_t cards_to_move, size_t ind);

    StatesTable states_;
    StatesQueue queue_;
    VertexStacks real_;

};