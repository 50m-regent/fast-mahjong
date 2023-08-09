#include <cassert>
#include <iostream>
#include <set>
#include <vector>
#include <math.h>

class Block {
private:
    const uint16_t raw_block;
    const uint32_t quinary;

    inline uint32_t calculate_quinary() {
        uint32_t result = 0;
        for (const uint8_t& tile: this->get_tiles()) {
            result += std::pow(5, tile - 1);
        }

        return result;
    }

public:
    Block(const uint16_t raw_block) :
        raw_block(raw_block),
        quinary(this->calculate_quinary())
    {
        assert(1000 > raw_block);
    }

    inline std::vector<int> get_tiles() const noexcept {
        return {
            this->raw_block / 100,
            this->raw_block / 10 % 10,
            this->raw_block % 10
        };
    }

    inline uint32_t get_quinary() const noexcept {
        return this->quinary;
    }

    inline friend std::ostream& operator<<(std::ostream& os, const Block& block) {
        os << block.raw_block;

        return os;
    }
};

const inline std::vector<Block>
    ALL_SETS({
        0,
        111, 123,
        222, 234,
        333, 345,
        444, 456,
        555, 567,
        666, 678,
        777, 789,
        888,
        999
    }),
    ALL_PAIRS({
        11, 22, 33, 44, 55, 66, 77, 88, 99
    });

bool has_too_many_tiles_of_kind(const std::vector<Block>& blocks) {
    std::vector<unsigned char> count(9, 0);
    for (const Block &block: blocks) {
        for (const uint8_t &tile: block.get_tiles()) {
            if (tile && ++count[tile - 1] > 4) {
                return true;
            }
        }
    }

    return false;
}

std::set<uint32_t> sets_cache() {
    std::set<uint32_t> sets;
    for (uint8_t i1 = 0; i1 < ALL_SETS.size(); ++i1) {
        const Block block1 = ALL_SETS[i1];
        for (uint8_t i2 = i1; i2 < ALL_SETS.size(); ++i2) {
            const Block block2 = ALL_SETS[i2];
            if (has_too_many_tiles_of_kind({block1, block2})) {
                continue;
            }

            for (uint8_t i3 = i2; i3 < ALL_SETS.size(); ++i3) {
                const Block block3 = ALL_SETS[i3];
                if (has_too_many_tiles_of_kind({block1, block2, block3})) {
                    continue;
                }

                for (uint8_t i4 = i3; i4 < ALL_SETS.size(); ++i4) {
                    const Block block4 = ALL_SETS[i4];
                    if (has_too_many_tiles_of_kind({block1, block2, block3, block4})) {
                        continue;
                    }

                    /*
                    std::cout <<
                        block1 << " " <<
                        block2 << " " <<
                        block3 << " " <<
                        block4 << " " <<
                        block1.get_quinary() +
                        block2.get_quinary() +
                        block3.get_quinary() +
                        block4.get_quinary() <<
                        std::endl;
                    */

                    sets.insert(
                        block1.get_quinary() +
                        block2.get_quinary() +
                        block3.get_quinary() +
                        block4.get_quinary()
                    );
                }
            }
        }
    }

    return sets;
}

std::set<uint32_t> pair_n_sets_cache() {
    std::set<uint32_t> pair_n_sets;
    for (uint8_t i1 = 0; i1 < ALL_SETS.size(); ++i1) {
        const Block block1 = ALL_SETS[i1];
        for (uint8_t i2 = i1; i2 < ALL_SETS.size(); ++i2) {
            const Block block2 = ALL_SETS[i2];
            if (has_too_many_tiles_of_kind({block1, block2})) {
                continue;
            }

            for (uint8_t i3 = i2; i3 < ALL_SETS.size(); ++i3) {
                const Block block3 = ALL_SETS[i3];
                if (has_too_many_tiles_of_kind({block1, block2, block3})) {
                    continue;
                }

                for (uint8_t i4 = i3; i4 < ALL_SETS.size(); ++i4) {
                    const Block block4 = ALL_SETS[i4];
                    if (has_too_many_tiles_of_kind({block1, block2, block3, block4})) {
                        continue;
                    }

                    for (uint8_t i5 = 0; i5 < ALL_PAIRS.size(); ++i5) {
                        const Block pair = ALL_PAIRS[i5];
                        if (has_too_many_tiles_of_kind({block1, block2, block3, block4, pair})) {
                            continue;
                        }

                        /*
                        std::cout <<
                            block1 << " " <<
                            block2 << " " <<
                            block3 << " " <<
                            block4 << " " <<
                            pair << " " <<
                            block1.get_quinary() +
                            block2.get_quinary() +
                            block3.get_quinary() +
                            block4.get_quinary() +
                            pair.get_quinary() <<
                            std::endl;
                        */

                        pair_n_sets.insert(
                            block1.get_quinary() +
                            block2.get_quinary() +
                            block3.get_quinary() +
                            block4.get_quinary() +
                            pair.get_quinary()
                        );
                    }
                }
            }
        }
    }

    return pair_n_sets;
}

int main() {
    std::set<uint32_t> sets = sets_cache();
    std::cout << sets.size() << std::endl;

    for (const uint32_t& set: sets) {
        std::cout << set << ", ";
    }
    std::cout << std::endl;

    std::set<uint32_t> pair_n_sets = pair_n_sets_cache();
    std::cout << pair_n_sets.size() << std::endl;

    for (const uint32_t& pair_n_set: pair_n_sets) {
        std::cout << pair_n_set << ", ";
    }
    std::cout << std::endl;
}