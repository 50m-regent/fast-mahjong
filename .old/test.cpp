#include <vector>
#include <unordered_map>
#include <string>
#include <iostream>

namespace mahjong {

namespace constant {

constexpr uint8_t  HAND_TILE_COUNT      = 14;
constexpr uint16_t REACH_REQUIRED_SCORE = 1000;

enum class Wind: const uint8_t {
    EAST, SOUTH, WEST, NORTH,
};

inline const std::unordered_map<Wind, std::string> WIND2STRING = {
    {Wind::EAST,  "East"},
    {Wind::SOUTH, "South"},
    {Wind::WEST,  "West"},
    {Wind::NORTH, "North"},
};

inline std::ostream& operator<<(
    std::ostream& ostream,
    const Wind& wind
) noexcept {
    ostream << WIND2STRING.at(wind);

    return ostream;
}

inline const Wind operator++(Wind& wind) noexcept {
    return wind = Wind(((uint8_t) wind + 1) % 4);
}

enum class Tile: const uint64_t {
    C1 = 1ull << 0,
    C2 = 1ull << 1,
    C3 = 1ull << 2,
    C4 = 1ull << 3,
    C5 = 1ull << 4,
    CR = 1ull << 5,
    CG = 1ull << 6,
    C6 = 1ull << 7,
    C7 = 1ull << 8,
    C8 = 1ull << 9,
    C9 = 1ull << 10,

    D1 = 1ull << 11,
    D2 = 1ull << 12,
    D3 = 1ull << 13,
    D4 = 1ull << 14,
    D5 = 1ull << 15,
    DR = 1ull << 16,
    DG = 1ull << 17,
    D6 = 1ull << 18,
    D7 = 1ull << 19,
    D8 = 1ull << 20,
    D9 = 1ull << 21,

    B1 = 1ull << 22,
    B2 = 1ull << 23,
    B3 = 1ull << 24,
    B4 = 1ull << 25,
    B5 = 1ull << 26,
    BR = 1ull << 27,
    BG = 1ull << 28,
    B6 = 1ull << 29,
    B7 = 1ull << 30,
    B8 = 1ull << 31,
    B9 = 1ull << 32,

    EAST  = 1ull << 33,
    SOUTH = 1ull << 34,
    WEST  = 1ull << 35,
    NORTH = 1ull << 36,

    WHITE = 1ull << 37,
    GREEN = 1ull << 38,
    RED   = 1ull << 39,

    SPRING = 1ull << 40,
    SUMMER = 1ull << 41,
    AUTUMN = 1ull << 42,
    WINTER = 1ull << 43,

    PLUM         = 1ull << 44,
    ORCHID       = 1ull << 45,
    CRYSANTHEMUM = 1ull << 46,
    BAMBOO       = 1ull << 47,
};

inline const std::unordered_map<Tile, std::string> TILE2STRING = {
    {Tile::C1, "C1"},
    {Tile::C2, "C2"},
    {Tile::C3, "C3"},
    {Tile::C4, "C4"},
    {Tile::C5, "C5"},
    {Tile::CR, "CR"},
    {Tile::CG, "CG"},
    {Tile::C6, "C6"},
    {Tile::C7, "C7"},
    {Tile::C8, "C8"},
    {Tile::C9, "C9"},

    {Tile::D1, "D1"},
    {Tile::D2, "D2"},
    {Tile::D3, "D3"},
    {Tile::D4, "D4"},
    {Tile::D5, "D5"},
    {Tile::DR, "DR"},
    {Tile::DG, "DG"},
    {Tile::D6, "D6"},
    {Tile::D7, "D7"},
    {Tile::D8, "D8"},
    {Tile::D9, "D9"},

    {Tile::B1, "B1"},
    {Tile::B2, "B2"},
    {Tile::B3, "B3"},
    {Tile::B4, "B4"},
    {Tile::B5, "B5"},
    {Tile::BR, "BR"},
    {Tile::BG, "BG"},
    {Tile::B6, "B6"},
    {Tile::B7, "B7"},
    {Tile::B8, "B8"},
    {Tile::B9, "B9"},

    {Tile::EAST,  "WE"},
    {Tile::SOUTH, "WS"},
    {Tile::WEST,  "WW"},
    {Tile::NORTH, "WN"},
    
    {Tile::WHITE, "SW"},
    {Tile::GREEN, "SG"},
    {Tile::RED,   "SR"},

    {Tile::SPRING, "FS"},
    {Tile::SUMMER, "FU"},
    {Tile::AUTUMN, "FA"},
    {Tile::WINTER, "FW"},

    {Tile::PLUM,         "FP"},
    {Tile::ORCHID,       "FO"},
    {Tile::CRYSANTHEMUM, "FC"},
    {Tile::BAMBOO,       "FB"},
};

inline std::ostream& operator<<(
    std::ostream& ostream,
    const Tile& tile
) noexcept {
    ostream << TILE2STRING.at(tile);

    return ostream;
}

}

class State {
public:
    const constant::Wind& game_type, wind;
    const uint32_t score_threshold;
    const std::vector<agent::Agent>& agents;
    const uint8_t round, stack, remanent_bar;
};

namespace agent {

class Agent {
private:
    uint32_t score;

public:
    Hand hand;
    bool is_reach = false;

    explicit Agent(const uint32_t score) noexcept : score(score) {};

    inline const uint32_t get_score() const noexcept {
        return this->score;
    }
    inline const void remove_score(const uint32_t score) noexcept {
        this->score -= score;
    }

    inline const bool heable() const noexcept {
        return this->hand.winnable();
    }
    inline const bool he() const noexcept {
        return true;
    }

    inline const bool reachable() const noexcept {
        return this->hand.is_tingpai() && this->score >= 1000;
    }
    inline const bool reach() const noexcept {
        return true;
    }

    inline const bool ronable(const constant::Tile& discard_tile) const noexcept {
        return this->hand.is_tingpai() & discard_tile;
    }

    inline const bool ron(
        const State& state,
        const constant::Tile& discard_tile
    ) const noexcept {
        return true;
    }
};

}

class Mahjong {
private:
    const constant::Wind game_type;
    const uint32_t score_threshold;
    const std::vector<agent::Agent> agents;
    const uint8_t agents_count;
    const bool verbose;

    constant::Wind wind = constant::Wind::EAST;
    uint8_t
        round        = 0,
        stack        = 0,
        remanent_bar = 0;

    const bool has_reached_player() const noexcept {
        for (const agent::Agent& agent: this->agents) {
            if (agent.get_score() >= this->score_threshold) {
                return true;
            }
        }

        return false;
    }

    const bool has_dead_player() const noexcept {
        for (const agent::Agent& agent: this->agents) {
            if (agent.get_score() < 0) {
                return true;
            }
        }

        return false;
    }

    inline const bool is_terminated() const noexcept {
        return
            (
                this->has_reached_player() &&
                this->game_type < this->wind
            ) ||
            this->has_dead_player();
    }

    const void print_round_info() const noexcept {
        std::cout << "round: " << this->wind << " " << (uint16_t) this->round + 1 << std::endl;
        std::cout << "stack: " << (uint16_t) this->stack << std::endl;
    }

    const bool turn_agent_process(agent::Agent& agent) noexcept {
        if (agent.heable() && agent.he()) {
            return true;
        }

        /* if (agent.gangable()) {
            agent.gang();
            return false;
        }*/

        if (agent.reachable() && agent.reach()) {
            agent.remove_score(constant::REACH_REQUIRED_SCORE);
            ++this->remanent_bar;
            agent.is_reach = true;

            return false;
        }

        return false;
    }

    const int8_t other_agents_process(
        const uint8_t& turn,
        const constant::Tile& discard_tile
    ) const noexcept {
        const State state{
            this->game_type, this->wind,
            this->score_threshold,
            this->agents,
            this->round, this->stack, this->remanent_bar
        };

        for (uint8_t i = 1; i < this->agents_count; ++i) {
            const agent::Agent& other_agent = this->agents.at((turn + i) % this->agents_count);
            if (other_agent.ronable(discard_tile)) {
                continue;
            }
            if (other_agent.ron(state, discard_tile)) {
                return (turn + i) % this->agents_count;
            }
        }

        /*for (uint8_t i = 1; i < this->agents.size(); ++i) {
            const agent::Agent other_agent = this->agents.at((turn + i) % this->agents_count);
            if (other_agent.gangable(discard_tile)) {
                other_agent.gang(discard_tile);
                return -1;
            }
        }*/

        for (uint8_t i = 1; i < this->agents_count; ++i) {
            const agent::Agent& other_agent = this->agents.at((turn + i) % this->agents_count);
            if (other_agent.pengable(discard_tile)) {
                continue;
            }
            if (other_agent.peng(state, discard_tile)) {
                return -1;
            }
        }

        for (uint8_t i = 1; i < this->agents_count; ++i) {
            const agent::Agent& other_agent = this->agents.at((turn + i) % this->agents_count);
            if (other_agent.chiable(discard_tile)) {
                continue;
            }
            if (other_agent.chi(state, discard_tile)) {
                return -1;
            }
        }
    }

    const bool run_round() const noexcept {
        if (this->verbose) {
            this->print_round_info();
        }

        Wall wall = Wall(this->original_wall);
        for (uint8_t i = 0; i < this->agents_count; ++i) {
            this->agents.at(i).hand = Hand(wall.pop(constant::HAND_TILE_COUNT - 1));
        }

        uint8_t turn = this->round;
        while (!wall.empty()) {
            const agent::Agent& turn_agent = this->agents.at(turn);

            const constant::Tile& zimo_tile = wall.pop();
            turn_agent.zimo(zimo_tile);

            if (this->verbose) {
                this->print_turn();
            }

            if (this->turn_agent_process(turn_agent)) {
                this->move_he_score();
                return turn == this->round;
            }

            const constant::Tile& discard_tile = turn_agent.discard();
            const int8_t roner = this->other_agents_process(turn, discard_tile);
            if (0 <= roner) {
                this->move_ron_score();
                return roner == this->round;
            }
            
            ++turn %= this->agents_count;
        }

        this->move_tingpai_score();

        return this->agents.at(this->round).hand.is_tingpai();
    }

    const void step(const bool continue_parent) noexcept {
        if (continue_parent) {
            ++this->stack;
        } else {
            this->stack = 0;

            if (this->agents_count <= this->round + 1) {
                ++this->wind;
            }
            this->round = ++this->round % this->agents_count;
        }
    }

public:
    explicit Mahjong(
        const std::vector<agent::Agent>& agents,
        const constant::Wind game_type,
        const uint32_t score_threshold,
        const bool verbose
    ) noexcept :
        agents(agents),
        agents_count(agents.size()),
        game_type(game_type),
        score_threshold(score_threshold),
        verbose(verbose)
    {}

    const void run() noexcept {
        while (!this->is_terminated()) {
            const bool continue_parent = this->run_round();
            this->step(continue_parent);
        }
    }
};

}

int main() {
    const std::vector<mahjong::agent::Agent> players = {
        mahjong::agent::Agent(25000),
        mahjong::agent::Agent(25000),
        mahjong::agent::Agent(25000),
        mahjong::agent::Agent(25000)
    };
    mahjong::Mahjong game = mahjong::Mahjong(
        players, mahjong::constant::Wind::SOUTH, 25000, true
    );
    game.run();
}