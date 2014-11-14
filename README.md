General
=========
This repository has the source for a PCB that uses Power over Ethernet (PoE) to power an STM32F103 microcontroller. It has a 10mbit ethernet MAC/PHY and  3.3V (.6A, 2W) and 12V (.5A, 6W) supplies fed from a 5V (1.8A, 9W) power rail. This gives this board the capability to provide power and control for quite a few different peripherals. The first use of the circuit boards and software in this repository is to provide a lower cost and more versatile RFID based entry method for a local hackerspace, Hive13.

In this repository you will currently find two main sections: hardware, and software. The hardware section contains the KiCad files for the PoE (power over ethernet)/micro board and the rfid transceiver board (rfidBoad). The software section contains the software/firmware for the stm32f103 to support the wanted functionality (currently ethernet comms and rfid/access control).
RFID/NFC board with ethernet+PoE with numerous I/Os.

Hardware
=========

The hardware consists of two separate boards: rfidBoard and PoE. rfidBoard is simply an rfid transceiver and antenna. PoE has an STM32F103 microcontroller which is connected to a 10mbit ethernet MAC/PHY. It alsohas a power over ethernet supply that provides 5V@1.8A total. This 5 volt supply provides power for a 3.3V supply and a 12V supply. The 3.3V supply is meant for powering ICs and other electronics while the 12V supply is meant for providing power to electronic door latches (solenoids).

rfid antenna
ST Micro's antenna.exe (can be found with google) was used to calculate the antenna size for an approximately 430nH antenna. A similar antenna of different shapes can be created by using the equations in the paper "Simple Accurate Expressions for Planar Spiral Inductances" (DOI 10.1109/4.792620). The parameters I used in antenna.exe are as follows: 2 turns, 8 segments, 1mm wide conductor, 0.25mm spacing between conductors, 35um conductor thickness, and 40mm by 40mm width and length.

Software
========
There is no software or firmware set up or written yet!
It will consist of a TCP/IP stack, an RFID stack, and a user access stack.

programs needed for compilation on fedora:
sudo yum install arm-none-eabi-gcc-cs arm-none-eabi-newlib scons

To program the board an STLINK v2 programmer is needed as well as stlink (on linux).

When cloning from git cd in to software/libopencm3 and run:
`git submodule init`
`git submodule update`

To flash the board with gdb and an st-link device:
In a separate terminal run the st-link server `st-util -1`
In another terminal run `arm-none-eabi-gdb firmware.elf`
Then in gdb run `tar ext :4242`, `load`, and finally either `continue` or `run`.

Datasheets
========
The datasheets directory contains some datasheets for different chips on board.
Currently it only contains STM32 microcontroller stuff.
They are large and don't fit well in to a git repository, but it helps keep
everything together and makes things easier to investigate down the line.


Notes and Issues
=========
* TODO: Add fuses on to POE board to protect circuitry.
* Several of the components in the PoE circuitry get WAY too hot.
* C5 (4.7uF cap on the PoE input) should have the negative pin connected to  GNDA/Pout rather than VPortN.
* ~~The 12V power supply current rating pretty much maxes out what the PoE can theoretically supply. Probably should derate the 12V supply quite a lot. This means that the 3.3V, 5V, and 12V will interfere with each other which is bad.~~ Updated current rating to 500mA which provides an ok margin for total power.
* ~~D1 may need to be unidirectional. The part specified in the BOM is currently bidirectional.~~ D1 should be a schottky!
* D2 is actually a zener, not a schottky as currently shown.
* *The footprint for U1 (LTC4267) is undersized.*

