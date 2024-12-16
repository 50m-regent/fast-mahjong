mod types;

use crate::types::Tile;

fn print_tiles() {
    fn print_group(tiles: &[Tile]) {
        for tile in tiles {
            print!("{}", tile);
        }
        println!();
    }

    const M: [Tile; 11] = [
        Tile::M1,
        Tile::M2,
        Tile::M3,
        Tile::M4,
        Tile::M5,
        Tile::MR,
        Tile::MG,
        Tile::M6,
        Tile::M7,
        Tile::M8,
        Tile::M9,
    ];
    const P: [Tile; 11] = [
        Tile::P1,
        Tile::P2,
        Tile::P3,
        Tile::P4,
        Tile::P5,
        Tile::PR,
        Tile::PG,
        Tile::P6,
        Tile::P7,
        Tile::P8,
        Tile::P9,
    ];
    const S: [Tile; 11] = [
        Tile::S1,
        Tile::S2,
        Tile::S3,
        Tile::S4,
        Tile::S5,
        Tile::SR,
        Tile::SG,
        Tile::S6,
        Tile::S7,
        Tile::S8,
        Tile::S9,
    ];
    const Z: [Tile; 8] = [
        Tile::Z1,
        Tile::Z2,
        Tile::Z3,
        Tile::Z4,
        Tile::Z5,
        Tile::ZG,
        Tile::Z6,
        Tile::Z7,
    ];
    const F: [Tile; 8] = [
        Tile::F1,
        Tile::F2,
        Tile::F3,
        Tile::F4,
        Tile::F5,
        Tile::F6,
        Tile::F7,
        Tile::F8,
    ];

    print_group(&M);
    print_group(&P);
    print_group(&S);
    print_group(&Z);
    print_group(&F);
}

fn main() {
    print_tiles();
}
