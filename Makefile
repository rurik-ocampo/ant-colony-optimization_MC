# Makefile
#
# 2023-03-23 - Benjamin Ocampo - Created
# 2023-03-23 - Benjamin Ocampo - Used to create the binary executable

# The program name is the same as APPNAME in package.conf
PROG1   = ant-colony-optimization
OBJS1   = main.cpp \
					ant_movement.o \
					ant_map.o

PROG2   = ant_movement.o
OBJS2   = ant_movement.cpp ant_movement.h

PROG3   = ant_map.o
OBJS3   = ant_map.cpp ant_map.h

PROGS   = $(PROG3) $(PROG2) $(PROG1)

# # Using standard C++ 17 
CFLAGS += -std=c++17

# # Indicates the library files needed to use the license controller
LDLIBS   += -lpthread -ldl

CFLAGS	+= -O0 -g    \
	    -Wno-psabi   \
        -Wformat=2 \
	    -Wpointer-arith \
	    -Winline \
	    -Wdisabled-optimization \
	    -Wfloat-equal \
	    -Wall \
        -Wextra \
        -Wshadow \
        -Wnon-virtual-dtor \
		-Wno-format-nonliteral


all:	$(PROGS)

$(PROG3): $(OBJS3)
	$(CXX) -c $^ $(CFLAGS) $(LDLIBS) $(IFLAGS)

$(PROG2): $(OBJS2)
	$(CXX) -c $^ $(CFLAGS) $(LDLIBS) $(IFLAGS)

$(PROG1): $(OBJS1)
	$(CXX) $(CFLAGS) -o $@ $^ $(LDFLAGS) $(LIBS) $(LDLIBS) $(IFLAGS)

cflags:
	$(info $(CFLAGS))

ldlibs:
	$(info $(LDLIBS))

ldflags:
	$(info $(LDFLAGS))

clean:
	rm -f $(PROGS) *.o 
