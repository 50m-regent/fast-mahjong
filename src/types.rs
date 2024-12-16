use bitflags;
use colored::Colorize;
use std;

bitflags::bitflags! {
    pub struct Tile: isize {
        const _1 = 1 << 0;
        const _2 = 1 << 1;
        const _3 = 1 << 2;
        const _4 = 1 << 3;
        const _5 = 1 << 4;
        const _6 = 1 << 5;
        const _7 = 1 << 6;
        const _8 = 1 << 7;
        const _9 = 1 << 8;

        const M = 1 << 9;
        const P = 1 << 10;
        const S = 1 << 11;
        const Z = 1 << 12;
        const F = 1 << 13;

        const R = 1 << 14;
        const G = 1 << 15;

        const M1 = Tile::M.bits() | Tile::_1.bits();
        const M2 = Tile::M.bits() | Tile::_2.bits();
        const M3 = Tile::M.bits() | Tile::_3.bits();
        const M4 = Tile::M.bits() | Tile::_4.bits();
        const M5 = Tile::M.bits() | Tile::_5.bits();
        const MR = Tile::M.bits() | Tile::_5.bits() | Tile::R.bits();
        const MG = Tile::M.bits() | Tile::_5.bits() | Tile::G.bits();
        const M6 = Tile::M.bits() | Tile::_6.bits();
        const M7 = Tile::M.bits() | Tile::_7.bits();
        const M8 = Tile::M.bits() | Tile::_8.bits();
        const M9 = Tile::M.bits() | Tile::_9.bits();

        const P1 = Tile::P.bits() | Tile::_1.bits();
        const P2 = Tile::P.bits() | Tile::_2.bits();
        const P3 = Tile::P.bits() | Tile::_3.bits();
        const P4 = Tile::P.bits() | Tile::_4.bits();
        const P5 = Tile::P.bits() | Tile::_5.bits();
        const PR = Tile::P.bits() | Tile::_5.bits() | Tile::R.bits();
        const PG = Tile::P.bits() | Tile::_5.bits() | Tile::G.bits();
        const P6 = Tile::P.bits() | Tile::_6.bits();
        const P7 = Tile::P.bits() | Tile::_7.bits();
        const P8 = Tile::P.bits() | Tile::_8.bits();
        const P9 = Tile::P.bits() | Tile::_9.bits();

        const S1 = Tile::S.bits() | Tile::_1.bits();
        const S2 = Tile::S.bits() | Tile::_2.bits();
        const S3 = Tile::S.bits() | Tile::_3.bits();
        const S4 = Tile::S.bits() | Tile::_4.bits();
        const S5 = Tile::S.bits() | Tile::_5.bits();
        const SR = Tile::S.bits() | Tile::_5.bits() | Tile::R.bits();
        const SG = Tile::S.bits() | Tile::_5.bits() | Tile::G.bits();
        const S6 = Tile::S.bits() | Tile::_6.bits();
        const S7 = Tile::S.bits() | Tile::_7.bits();
        const S8 = Tile::S.bits() | Tile::_8.bits();
        const S9 = Tile::S.bits() | Tile::_9.bits();

        const Z1 = Tile::Z.bits() | Tile::_1.bits();
        const Z2 = Tile::Z.bits() | Tile::_2.bits();
        const Z3 = Tile::Z.bits() | Tile::_3.bits();
        const Z4 = Tile::Z.bits() | Tile::_4.bits();
        const Z5 = Tile::Z.bits() | Tile::_5.bits();
        const ZG = Tile::Z.bits() | Tile::_5.bits() | Tile::G.bits();
        const Z6 = Tile::Z.bits() | Tile::_6.bits();
        const Z7 = Tile::Z.bits() | Tile::_7.bits();

        const F1 = Tile::F.bits() | Tile::_1.bits();
        const F2 = Tile::F.bits() | Tile::_2.bits();
        const F3 = Tile::F.bits() | Tile::_3.bits();
        const F4 = Tile::F.bits() | Tile::_4.bits();
        const F5 = Tile::F.bits() | Tile::_5.bits();
        const F6 = Tile::F.bits() | Tile::_6.bits();
        const F7 = Tile::F.bits() | Tile::_7.bits();
        const F8 = Tile::F.bits() | Tile::_8.bits();
    }
}

const TILE_UNICODES: [&str; 43] = [
    "\u{1f007}",
    "\u{1f008}",
    "\u{1f009}",
    "\u{1f00a}",
    "\u{1f00b}",
    "\u{1f00c}",
    "\u{1f00d}",
    "\u{1f00e}",
    "\u{1f00f}",
    "\u{1f010}",
    "\u{1f011}",
    "\u{1f012}",
    "\u{1f013}",
    "\u{1f014}",
    "\u{1f015}",
    "\u{1f016}",
    "\u{1f017}",
    "\u{1f018}",
    "\u{1f019}",
    "\u{1f01a}",
    "\u{1f01b}",
    "\u{1f01c}",
    "\u{1f01d}",
    "\u{1f01e}",
    "\u{1f01f}",
    "\u{1f020}",
    "\u{1f021}",
    "\u{1f000}",
    "\u{1f001}",
    "\u{1f002}",
    "\u{1f003}",
    "\u{1f006}",
    "\u{1f005}",
    "\u{1f004}",
    "\u{1f02b}",
    "\u{1f022}",
    "\u{1f023}",
    "\u{1f024}",
    "\u{1f025}",
    "\u{1f026}",
    "\u{1f027}",
    "\u{1f028}",
    "\u{1f029}",
];

impl std::fmt::Display for Tile {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        if self.contains(Tile::ZG) {
            return write!(f, "{}", TILE_UNICODES[34]);
        }

        let i: usize;
        if self.contains(Tile::M) {
            i = 0;
        } else if self.contains(Tile::P) {
            i = 9;
        } else if self.contains(Tile::S) {
            i = 18;
        } else if self.contains(Tile::Z) {
            i = 27;
        } else if self.contains(Tile::F) {
            i = 35;
        } else {
            panic!()
        }

        let output: &str;
        if self.contains(Tile::_1) {
            output = TILE_UNICODES[i + 0];
        } else if self.contains(Tile::_2) {
            output = TILE_UNICODES[i + 1];
        } else if self.contains(Tile::_3) {
            output = TILE_UNICODES[i + 2];
        } else if self.contains(Tile::_4) {
            output = TILE_UNICODES[i + 3];
        } else if self.contains(Tile::_5) {
            output = TILE_UNICODES[i + 4];
        } else if self.contains(Tile::_6) {
            output = TILE_UNICODES[i + 5];
        } else if self.contains(Tile::_7) {
            output = TILE_UNICODES[i + 6];
        } else if self.contains(Tile::_8) {
            output = TILE_UNICODES[i + 7];
        } else if self.contains(Tile::_9) {
            output = TILE_UNICODES[i + 8];
        } else {
            panic!()
        }

        if self.contains(Tile::R) {
            write!(f, "{}", output.bright_red())
        } else if self.contains(Tile::G) {
            write!(f, "{}", output.yellow())
        } else {
            write!(f, "{}", output)
        }
    }
}
