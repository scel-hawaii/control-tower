# Control Tower

Central repository for scel-weatherbox project and related modules.

* [weatherbox_firmware](weatherbox_firmware)
* [gateway](gateway)
* [api](api)
* [db](database)

Developers: See the [development docs](docs/development.md) for more instructions.

The main changes that are made in this branch is the implementation of GPS and RTC.
It is not fully functional as it is unable to get a fix and send accurate data. 
Some other changes include gen_guava debug leds. They can also be enabled by 
defining "DEBUG" in the gg_board.h and xbee.h headder files. Lastly are 
gen_cranberry untested debug leds.Similar in design to gen_guava however do not 
have a firmware enable/disable.
