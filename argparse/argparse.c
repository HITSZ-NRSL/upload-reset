/**********************************************************************************
 **********************************************************************************
 ***
 ***    argparse.c
 ***    - simple parser for command line arguments
 ***      checks which command submodule an argument is for and then dispatches
 ***      processing to the apropriate parser
 ***
 ***    Copyright (C) 2014 Christian Klippel <ck@atelier-klippel.de>
 ***
 ***    This program is free software; you can redistribute it and/or modify
 ***    it under the terms of the GNU General Public License as published by
 ***    the Free Software Foundation; either version 2 of the License, or
 ***    (at your option) any later version.
 ***
 ***    This program is distributed in the hope that it will be useful,
 ***    but WITHOUT ANY WARRANTY; without even the implied warranty of
 ***    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 ***    GNU General Public License for more details.
 ***
 ***    You should have received a copy of the GNU General Public License along
 ***    with this program; if not, write to the Free Software Foundation, Inc.,
 ***    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 ***
 **/

#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>
#include <errno.h>

#include "infohelper.h"
// main parser state machine, returns the number of arguments used by
// the called sub-parser
#include "argparse.h"


const char *serial_port =
#if defined(LINUX)
"/dev/ttyUSB0";
#elif defined(WINDOWS)
"COM1";
#elif defined(OSX)
"/dev/tty.usbserial";
#else
"";
#endif

uint32_t serial_baudrate = 19200;
uint32_t delaytime = 2000;

static void print_help()
{
    const char* help = "\
upload-reset v" VERSION " - (c) 2017 robin <robin@molmc.com>\n\
molmc upload reset tool\n\
Maintained by robin\n\
\n\
The program interprets arguments given on the command line, and in the order\n\
they are given.\n\
\n\
-p <device>\n\
    Select the serial port device to use for communicating with the ESP.\n\
    Default is /dev/ttyUSB0 on Linux, COM1 on Windows, /dev/tty.usbserial on Mac OS.\n\
\n\
-b <baudrate>\n\
    Select the baudrate to use, default is 115200.\n\
\n\
-t <delay time>\n\
    the time delay.\n\
\n";
    INFO(help);
}

int parse_arg(int num_args, char **arg_ptr)
{
    if(arg_ptr[0][0] == '-' && num_args)
    {
        switch(arg_ptr[0][1])
        {
            case 'p':
                if(num_args < 1)
                {
                    return 0;
                }
                serial_port = (arg_ptr+1)[0];
                return 2;
                break;

            case 'b':
                if(num_args < 1)
                {
                    return 0;
                }
                serial_baudrate = (uint32_t) strtol((arg_ptr+1)[0], NULL, 10);
                return 2;
                break;

            case 't':
                if(num_args < 1)
                {
                    return 0;
                }
                delaytime = (uint32_t) strtol((arg_ptr+1)[0], NULL, 10);
                return 2;
                break;

            case '?':
            case 'h':
                print_help();
                return 1;
                break;

            default:
                return 0;
                break;
        }
    }
    return 0;
}
