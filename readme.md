# Project abstract

Working with faculty and students at [The Watson Institute](https://www.thewatsoninstitute.org/locations/sewickley-pa/), a school that serves children with disabilities, we have developed a prototype drawing machine for students to use in art class and other creative contexts. The device is to be presented as a demo at [the International Symposium of Academic Makerspaces 2025](https://isam2025.hemi-makers.org/) in functional prototype form, with the ability to manipulate a user-supplied drawing implement (marker, pen, pencil, etc.) to draw a user-selected line drawing, at a user-selected scale, in a user-selected location on a sheet of paper. All user inputs are switch-adapted for accessibility. 

The machine’s hardware is simple to fabricate and assemble using facilities present at many makerspaces; the current design incorporates 3D printed major structural components, as well as common low-cost electronics and motors to drive motion. The firmware runs on an Arduino Mega and is designed for easy modification, including adding new line drawings that are described point-by-point. The hardware, electronics, and firmware are open-sourced under a nonrestrictive [CC-BY-4.0 license](https://creativecommons.org/licenses/by/4.0/) so as to allow others to build on this work, for adaptation to their own contexts or improvements to our design and implementation.

# File structure

Development is currently underway (as of summer 2025), and as such our working files are in the `/development` directory. We anticipate adding a `/production` directory once we have at least a fully-fledged alpha version that is ready for others to duplicate and build upon.

# Acknowledgements

The design for the primary XY linkage that drives motion is derived from an [open-source plan shared via Thingiverse by user imaicom](https://www.thingiverse.com/thing:4607077).

Certain sections of the Arduino firmware were written with assistance from “Claude,” a generative AI service available at <https://claude.ai>.

# License

As mentioned in the abstract, this project is licensed [CC-BY-4.0](https://creativecommons.org/licenses/by/4.0/).
