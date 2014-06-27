rfidBoard
=========

RFID/NFC board with ethernet+PoE with numerous I/Os.

Notes
=========
* The 12V power supply current rating pretty much maxes out what the PoE can theoretically supply. Probably should derate the 12V supply quite a lot. This means that the 3.3V, 5V, and 12V will interfere with each other which is bad.
* D1 may need to be unidirectional. The part specified in the BOM is currently bidirectional.
* D2 is actually a zener, not a schottky as currently shown.
* Double check IC schematic symbols for belly pads.
