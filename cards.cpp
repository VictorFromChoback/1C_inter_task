#include "cards.hpp"


bool Solitaire::move_cards_(const VertexStacks& table, size_t cards_to_move, size_t ind) {
    
    if (table.stacks[ind].size() < cards_to_move) {
        return false;
    }   

    size_t back_index = table.stacks[ind].size() - cards_to_move;

    if (table.stacks[ind][back_index] == Closed) {
        return false;
    }

    for (size_t other_stack = 0; other_stack < VertexStacks::stacks_amount; ++other_stack) {
        if (other_stack == ind) {
            continue;
        }

        bool flag = false;

        if (table.stacks[other_stack].size() == 0) {
            flag = true;
        }

        if ((table.stacks[other_stack].size() > 0) && table.stacks[ind][back_index] < table.stacks[other_stack].back()) {
            flag = true;
        }

        if (flag) {
            
            VertexStacks new_table = table;

            for (size_t i = back_index; i < table.stacks[ind].size(); ++i) {
                new_table.stacks[other_stack].push_back(new_table.stacks[ind][i]);
            }
            
            for (size_t i = 0; i < cards_to_move; ++i) {
                new_table.stacks[ind].pop_back();
            }

            if (back_index > 0) {
                new_table.stacks[ind][back_index - 1] = real_.stacks[ind][back_index - 1];
            }

            bool flag_check = true;

            if (new_table.stacks[other_stack].size() != VertexStacks::cards_amount) {
                flag_check = false;
            }

            for (int i = VertexStacks::cards_amount - 1; (i >= 1) && (flag_check); --i) {
                flag_check &= (new_table.stacks[other_stack][i] > new_table.stacks[other_stack][i]);
            }

            if (flag_check) {
                new_table.stacks.clear();
            }

            std::string view = new_table.convert();

            if (!states_[view]) {
                states_[view] = true;
                queue_.push(new_table); 
            }
        }
    }


    return true;
}


void Solitaire::make_step() {
    VertexStacks now = queue_.front();
    queue_.pop();

    for (size_t s = 0; s < VertexStacks::stacks_amount; ++s) {
        for (size_t to_move = 1; to_move <= VertexStacks::cards_amount; ++to_move) {
            bool result = move_cards_(now, to_move, s);

            if (!result) {
                break;
            }
        }
    }

}

bool Solitaire::run_loop() {

    while (!queue_.empty()) {
        make_step();
        if (HasAchived()) {
            return true;
        }
    }

    return HasAchived();

}



bool Solitaire::HasAchived() {
    std::string answer_epected = "";

    for (size_t i = 0; i < VertexStacks::stacks_amount; ++i) {
        answer_epected.push_back('#');
    }

    return states_[answer_epected];
}


std::istream& operator>>(std::istream& in, VertexStacks& obj) {
    static std::unordered_map<std::string, Cards> mapping;
    obj.stacks.resize(VertexStacks::stacks_amount);

    mapping["Six"] = Six;
    mapping["Seven"] = Seven;
    mapping["Eight"] = Eight;
    mapping["Nine"] = Nine;
    mapping["Ten"] = Ten;
    mapping["Jack"] = Jack;
    mapping["Queen"] = Queen;
    mapping["King"] = King;
    mapping["Ace"] = Ace;
    mapping["Closed"] = Closed;

    std::string cur_string;

    for (size_t i = 0; i < VertexStacks::stacks_amount; ++i) {
        for (size_t j = 0; j < VertexStacks::cards_amount; ++j) {
            in >> cur_string;
            obj.stacks[i].push_back(mapping[cur_string]);
        }
    }


    return in;
}


VertexStacks VertexStacks::make_hidden() const {

    VertexStacks answer = *this;

    for (size_t i = 0; i < VertexStacks::stacks_amount; ++i) {
        for (size_t j = 0; j < VertexStacks::cards_amount - 1; ++j) {
            answer.stacks[i][j] = Closed;
        }
    }

    return answer;
}

