# OpenRP1210 Demo Driver
This is a software RP1210 driver for [OpenRP1210](https://github.com/crow9724/OpenRP1210). It's useful for testing if there isn't any actual hardware on hand.

It currently supports connecting and reading messages via RP1210_ReadMessage. 

In the future, this can be developed further to add useful functionality for testing/debugging/developing client applications
as well as controller simulation.

It supports both Windows and Linux.

## Compiling
For Windows there's a Visual Studio 2022 project file.

For Linux there's a Visual Studio Code workspace and also a Makefile.

To build with the Makefile, simply run the [Makefile](project/linux/Makefile) with "make". 

## Installing
On Windows, OpenRP1210Drv.dll and the [OpenRP1210 INI](ini/win/OpenRP1210.ini) file need to be copied to the Windows directory.
In addition, RP1210.ini file in the Windows directory needs to have "OpenRP1210" added to "APIImplementations". There's also a template [RP1210 INI](ini/win/RP121032.ini) file.

On Linux, a user "rp1210" must be created with a home directory "/home/rp1210". Binaries are installed to the rp1210 home directory.
The driver can be installed with "sudo make install".

Note that the driver name is "open_rp1210" on Linux and OpenRP1210 on Windows.

## License
This project is licensed under the [Mozilla Public License 2.0](https://choosealicense.com/licenses/mpl-2.0/).
