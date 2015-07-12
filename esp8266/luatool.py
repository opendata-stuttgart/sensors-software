#!/usr/bin/env python2
#
# ESP8266 luatool
# Author e-mail: 4ref0nt@gmail.com
# Site: http://esp8266.ru
# Contributions from: https://github.com/sej7278
#
# This program is free software; you can redistribute it and/or modify it under
# the terms of the GNU General Public License as published by the Free Software
# Foundation; either version 2 of the License, or (at your option) any later version.
#
# This program is distributed in the hope that it will be useful, but WITHOUT
# ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
# FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License along with
# this program; if not, write to the Free Software Foundation, Inc., 51 Franklin
# Street, Fifth Floor, Boston, MA 02110-1301 USA.

import sys
import serial
from time import sleep
import argparse
from os.path import basename

version="0.6.3"

def writeln(data, check = 1):
    if s.inWaiting() > 0:
       s.flushInput()
    if len( data ) > 0:
        sys.stdout.write("\r\n->")
        sys.stdout.write(data.split("\r")[0])
    s.write(data)
    sleep(0.3)
    if check > 0 :
       line = ''
       char = ''
       while char != chr(62) : # '>'
           char = s.read(1)
           if char == '' :
               raise Exception('No proper answer from MCU')
           if char == chr(13) or char == chr(10) : # LF or CR
              if line != '':
                 line = line.strip()
                 if line+'\r' == data :
                    sys.stdout.write(" -> ok")
                 else :
                    if line[:4] == "lua:" :
                       sys.stdout.write("\r\n\r\nLua ERROR: %s" % line)
                       raise Exception('ERROR from Lua interpreter\r\n\r\n')
                    else :
                       data = data.split("\r")[0]
                       sys.stdout.write("\r\n\r\nERROR")
                       sys.stdout.write("\r\n send string    : '%s'" % data)
                       sys.stdout.write("\r\n expected echo  : '%s'" % data)
                       sys.stdout.write("\r\n but got answer : '%s'" % line)
                       sys.stdout.write("\r\n\r\n")
                       raise Exception('Error sending data to MCU\r\n\r\n')
                 line = ''
           else :
              line += char
    else:
       sys.stdout.write(" -> send without check")

def writer(data):
    writeln("file.writeline([==[" + data + "]==])\r")

def openserial(args):
    # Open the selected serial port
    try:
        s = serial.Serial(args.port, args.baud)
    except:
        sys.stderr.write("Could not open port %s\n" % (args.port))
        sys.exit(1)
    if args.verbose: sys.stderr.write("Set timeout %s\r\n" % s.timeout)
    s.timeout = 3
    if args.verbose: sys.stderr.write("Set interCharTimeout %s\r\n" % s.interCharTimeout)
    s.interCharTimeout = 3
    return s

if __name__ == '__main__':
    # parse arguments or use defaults
    parser = argparse.ArgumentParser(description='ESP8266 Lua script uploader.')
    parser.add_argument('-p', '--port',    default='/dev/ttyUSB0', help='Device name, default /dev/ttyUSB0')
    parser.add_argument('-b', '--baud',    default=9600,           help='Baudrate, default 9600')
    parser.add_argument('-f', '--src',     default='main.lua',     help='Source file on computer, default main.lua')
    parser.add_argument('-t', '--dest',    default=None,           help='Destination file on MCU, default to source file name')
    parser.add_argument('-c', '--compile', action='store_true',    help='Compile lua to lc after upload')
    parser.add_argument('-r', '--restart', action='store_true',    help='Restart MCU after upload')
    parser.add_argument('-d', '--dofile',  action='store_true',    help='Run the Lua script after upload')
    parser.add_argument('-v', '--verbose', action='store_true',    help="Show progress messages.")
    parser.add_argument('-l', '--list',    action='store_true',    help='List files on device')
    args = parser.parse_args()

    if args.list:
        s = openserial(args)
        writeln("local l = file.list();for k,v in pairs(l) do print('name:'..k..', size:'..v)end\r", 0)
        while True :
            char = s.read(1)
            if char == '' or char == chr(62): break
            sys.stdout.write(char)
        sys.exit(0)

    if args.dest is None:
        args.dest = basename(args.src)

    # open source file for reading
    try:
        f = open(args.src,"rt")
    except:
        sys.stderr.write("Could not open input file \"%s\"\n" % args.src)
        sys.exit(1)

    # Verify the selected file will not exceed the size of the serial buffer.
    # The size of the buffer is 256. This script does not accept files with
    # lines longer than 230 characters to have some room for command overhead.
    for Ln in f:
        if len(Ln) > 230:
            sys.stderr.write("File \"%s\" contains a line with more than 240 "\
            "characters. This exceeds the size of the serial buffer.\n"
            % args.src)
            f.close()
            sys.exit(1)

    # Go back to the beginning of the file after verifying it has the correct
    # line length
    f.seek(0)

    # Open the selected serial port
    s = openserial(args)

    # set serial timeout
    if args.verbose: sys.stderr.write("Upload starting\r\n")

    # remove existing file on device
    if args.verbose: sys.stderr.write("Stage 1. Deleting old file from flash memory")
    writeln("file.open(\""+args.dest+"\", \"w\")\r")
    writeln("file.close()\r")
    writeln("file.remove(\""+args.dest+"\")\r")

    # read source file line by line and write to device
    if args.verbose: sys.stderr.write("\r\nStage 2. Creating file in flash memory and write first line")
    writeln("file.open(\""+args.dest+"\", \"w+\")\r")
    line = f.readline()
    if args.verbose: sys.stderr.write("\r\nStage 3. Start writing data to flash memory...")
    while line != '':
        writer(line.strip())
        line = f.readline()

    # close both files
    f.close()
    if args.verbose: sys.stderr.write("\r\nStage 4. Flush data and closing file")
    writeln("file.flush()\r")
    writeln("file.close()\r")

    # compile?
    if args.compile:
       if args.verbose: sys.stderr.write("\r\nStage 5. Compiling")
       writeln("node.compile(\""+args.dest+"\")\r")
       writeln("file.remove(\""+args.dest+"\")\r")

    # restart or dofile
    if args.restart:
       writeln("node.restart()\r")
    if args.dofile: # never exec if restart=1
       writeln("dofile(\""+args.dest+"\")\r",0)

    # close serial port
    s.flush()
    s.close()

    # flush screen
    sys.stdout.flush()
    sys.stderr.flush()
    sys.stderr.write("\r\n--->>> All done <<<---\r\n")
