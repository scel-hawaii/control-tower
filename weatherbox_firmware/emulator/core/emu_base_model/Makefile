#
# 	Copyright 2008, 2009 Michel Pollet <buserror@gmail.com>
#
#	This file is part of simavr.
#
#	simavr is free software: you can redistribute it and/or modify
#	it under the terms of the GNU General Public License as published by
#	the Free Software Foundation, either version 3 of the License, or
#	(at your option) any later version.
#
#	simavr is distributed in the hope that it will be useful,
#	but WITHOUT ANY WARRANTY; without even the implied warranty of
#	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#	GNU General Public License for more details.
#
#	You should have received a copy of the GNU General Public License
#	along with simavr.  If not, see <http://www.gnu.org/licenses/>.

target=	emu_base_model
firm_src = ${wildcard atmega*.c}
firmware = ${firm_src:.c=.hex}
simavr = ../simavr

IPATH = .
IPATH += ../simavr/examples/parts
IPATH += ${simavr}/include
IPATH += ${simavr}/simavr/sim

VPATH = .
VPATH += ../simavr/examples/parts

LDFLAGS += -lpthread -lutil

include ../simavr/examples/Makefile.opengl

all: obj ${firmware} ${target}

include ${simavr}/Makefile.common
LDFLAGS += -L${shell realpath ../simavr/simavr/${OBJ}}
CFLAGS += -Wl,-rpath=${shell realpath ../simavr/simavr/${OBJ}}

board = ${OBJ}/${target}.elf

${board} : ${OBJ}/uart_pty.o
${board} : ${OBJ}/${target}.o

${target}: ${board}
	@echo $@ done

clean: clean-${OBJ}
	rm -rf *.a *.axf ${target} *.vcd *.hex
	rm -rf *.bin
