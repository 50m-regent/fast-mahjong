#include <stdint.h>
#include <queue>
#include <set>
#include <iostream>

namespace mahjong {

enum Tile: uint64_t {
    M1 = 1ll << 0, P1 = 1ll << 9,  S1 = 1ll << 18, Z1 = 1ll << 27,
    M2 = 1ll << 1, P2 = 1ll << 10, S2 = 1ll << 19, Z2 = 1ll << 28,
    M3 = 1ll << 2, P3 = 1ll << 11, S3 = 1ll << 20, Z3 = 1ll << 29,
    M4 = 1ll << 3, P4 = 1ll << 12, S4 = 1ll << 21, Z4 = 1ll << 30,
    M5 = 1ll << 4, P5 = 1ll << 13, S5 = 1ll << 22, Z5 = 1ll << 31,
    M6 = 1ll << 5, P6 = 1ll << 14, S6 = 1ll << 23, Z6 = 1ll << 32,
    M7 = 1ll << 6, P7 = 1ll << 15, S7 = 1ll << 24, Z7 = 1ll << 33,
    M8 = 1ll << 7, P8 = 1ll << 16, S8 = 1ll << 25,
    M9 = 1ll << 8, P9 = 1ll << 17, S9 = 1ll << 26,

    M = M1 | M2 | M3 | M4 | M5 | M6 | M7 | M8 | M9,
    P = P1 | P2 | P3 | P4 | P5 | P6 | P7 | P8 | P9,
    S = S1 | S2 | S3 | S4 | S5 | S6 | S7 | S8 | S9,

    Terminals = M1 | M9 | P1 | P9 | S1 | S9,
    Honors    = Z1 | Z2 | Z3 | Z4 | Z5 | Z6 | Z7,

    IsDora = 1ll << 34,
    IsRed  = 1ll << 35,
};

inline Tile& operator<<=(Tile& tile, const int& n) noexcept {
    return tile = (Tile)((uint64_t)tile << n);
}

class Tiles {
private:
    uint64_t tiles[4] = {};

public:
    inline uint64_t operator[](const int& n) const noexcept {
        assert((0 < n) && (n < 5));

        return this->tiles[n - 1];
    }

    inline uint16_t count() const noexcept {
        return
            std::popcount(this->tiles[0]) +
            std::popcount(this->tiles[1]) +
            std::popcount(this->tiles[2]) +
            std::popcount(this->tiles[3]);
    }

    inline uint16_t count(const Tile& tile) const noexcept {
        return
            std::popcount(this->tiles[0] & tile) +
            std::popcount(this->tiles[1] & tile) +
            std::popcount(this->tiles[2] & tile) +
            std::popcount(this->tiles[3] & tile);
    }

    inline bool add(const Tile& tile) noexcept {
        if (this->tiles[3] & tile) {
            return false;
        }

        this->tiles[3] |= (this->tiles[2] & tile);
        this->tiles[2] |= (this->tiles[1] & tile);
        this->tiles[1] |= (this->tiles[0] & tile);
        this->tiles[0] |= tile;
        return true;
    }

    inline bool remove(const Tile& tile) noexcept {
        if (!(this->tiles[0] & tile)) {
            return false;
        }

        this->tiles[0] &= (this->tiles[1] | ~tile);
        this->tiles[1] &= (this->tiles[2] | ~tile);
        this->tiles[2] &= (this->tiles[3] | ~tile);
        this->tiles[3] &= ~tile;
        return true;
    }

    uint32_t get_quinary(const Tile& start, const Tile& end) const noexcept {
        assert((1 << 9) > end / start);

        uint32_t result = 0, base = 1;
        for (Tile tile = start; tile <= end; tile <<= 1, base *= 5) {
            result += base * this->count(tile);
        }

        return result;
    }
};

class Hand { 
private:
    inline static const std::set<uint32_t>
        pair_n_sets = {},
        sets = {}; // キャッシュ後で作成

    Tiles tiles;

    inline bool can_win_normal() const {
        assert(14 == this->tiles.count());

        const uint8_t
            M_remainder = this->tiles.count(Tile::M) % 3,
            P_remainder = this->tiles.count(Tile::P) % 3,
            S_remainder = this->tiles.count(Tile::S) % 3;

        const uint8_t Z_headable_count = std::popcount(~this->tiles[3] & this->tiles[2] & Tile::Honors);

        if (
            (1 == M_remainder) ||
            (1 == P_remainder) ||
            (1 == S_remainder) || // has single remained number tile
            (~this->tiles[2] & this->tiles[1] & Tile::Honors) || // has single honor tile
            (1 !=
                (2 == M_remainder) +
                (2 == P_remainder) +
                (2 == S_remainder) +
                Z_headable_count
            ) // has extra or no pair
        ) {
            return false;
        }

        const uint32_t
            M_quinary = this->tiles.get_quinary(Tile::M1, Tile::M9),
            P_quinary = this->tiles.get_quinary(Tile::P1, Tile::P9),
            S_quinary = this->tiles.get_quinary(Tile::S1, Tile::S9),
            Z_quinary = this->tiles.get_quinary(Tile::Z1, Tile::Z7);
        if (2 == M_remainder) { // pair is in M
            return
                Hand::pair_n_sets.contains(M_quinary) &&
                Hand::sets.contains(P_quinary) &&
                Hand::sets.contains(S_quinary) &&
                Hand::sets.contains(Z_quinary);
        } else if (2 == P_remainder) { // pair is in P
            return
                Hand::sets.contains(M_quinary) &&
                Hand::pair_n_sets.contains(P_quinary) &&
                Hand::sets.contains(S_quinary) &&
                Hand::sets.contains(Z_quinary);
        } else if (2 == S_remainder) { // pair is in S
            return
                Hand::sets.contains(M_quinary) &&
                Hand::sets.contains(P_quinary) &&
                Hand::pair_n_sets.contains(S_quinary) &&
                Hand::sets.contains(Z_quinary);
        } else { // pair is in Z
            return
                Hand::sets.contains(M_quinary) &&
                Hand::sets.contains(P_quinary) &&
                Hand::sets.contains(S_quinary) &&
                Hand::pair_n_sets.contains(Z_quinary);
        }
    }

    inline bool can_win_seven_pairs() const noexcept {
        assert(14 == this->tiles.count());

        return 7 == std::popcount(this->tiles[2]);
    }

    inline bool can_win_13_orphans() const noexcept {
        assert(14 == this->tiles.count());

        return
            (13 == std::popcount(this->tiles[1] & (Tile::Terminals | Tile::Honors))) &&
            (1  == std::popcount(this->tiles[2] & (Tile::Terminals | Tile::Honors)));
    }

public:
    inline bool can_win() const noexcept {
        return
            (14 == this->tiles.count()) && (
                this->can_win_normal() ||
                this->can_win_seven_pairs() ||
                this->can_win_13_orphans()
            );
    }

    inline bool draw(const Tile& tile) noexcept {
        if (14 == this->tiles.count()) {
            return false;
        }

        this->tiles.add(tile);
        return true;
    }
};

}

int main() {
}