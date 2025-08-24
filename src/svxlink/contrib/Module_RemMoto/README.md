# cm119

`cm119` is a command line GPIO tool for CMedia CM108 and CM119 audio devices.
It's a small adaptation of [Dire Wolf][1]'s cm108 driver to compile with very
few dependencies and to take options to set GPIO pins.

# Building

    $ sudo apt-get install libudev-dev
    $ make

# Installing

    $ sudo make install

# Using

## Print Attached Devices

    $ cm119 -p

## Setting a GPIO Pin

    $ cm119 -H /dev/hidraw1 -P 5 -L 1

## Setting a channel on a Motorola GM300

    $ cm119 -H /dev/hidraw1 -M [channel no]
    
## Command line Help
    $ cm119 -h
    
## Verabose Output for debug
$ cm119 -H /dev/hidraw1 -P 5 -L 1 -v

        
 [1]: https://github.com/wb2osz/direwolf
