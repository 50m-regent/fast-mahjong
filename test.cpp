#include <stdint.h>
#include <queue>

namespace mahjong {

enum Tile {
    M1, M2, M3, M4, M5, M6, M7, M8, M9,
    P1, P2, P3, P4, P5, P6, P7, P8, P9,
    S1, S2, S3, S4, S5, S6, S7, S8, S9,
    Z1, Z2, Z3, Z4, Z5, Z6, Z7,
    MR, PR, SR,
    F1, F2, F3, F4, F5, F6, F7, F8,
    LENGTH,
};

class Hand {
private:
    uint8_t tiles[Tile::LENGTH] = {};
    uint8_t tile_count = 0;

    inline bool can_win_normal() const {

    }

    inline bool can_win_seven_pairs() const {

    }

    inline bool can_win_13_orphans() const {
        
    }

public:
    inline uint8_t count() const noexcept {
        return this->tile_count;
    }
    inline uint8_t count(const Tile& tile) const {
        return this->tiles[tile];
    }

    inline bool add(const Tile& tile) {
        if (4 == this->tiles[tile]) {
            return false;
        }

        ++this->tiles[tile];
        ++this->tile_count;
        return true;
    }

    inline bool remove(const Tile& tile) {
        if (0 == this->tiles[tile]) {
            return false;
        }

        --this->tiles[tile];
        --this->tile_count;
        return true;
    }

    inline bool can_win() const noexcept {
        return this->can_win_normal() | this->can_win_seven_pairs() | this->can_win_13_orphans();
    }
};

}

int main() {
    
}