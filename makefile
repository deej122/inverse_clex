################################################
# Compile with: 'make' or 'make example'
# Clean with: 'make clean'
#


################################################
# Change these if boost not installed in your compile search path:
BOOST_INCLUDE = 
BOOST_LIB = 


################################################
# Compiler options

INCLUDE = 
ifneq "$(BOOST_INCLUDE)" ""
	INCLUDE += $(BOOST_INCLUDE)
endif


OBJS = source/monte_carlo.o source/plotting.o source/clex.o source/metropolis.o external/jsonParser/jsonParser.o
CXX = g++ 
CPPFLAGS += -w -O3 $(foreach i,$(INCLUDE),-I$(i))

ifeq "$(BOOST_LIB)" ""
	LFLAGS = -lboost_system
else
	BOOST_LIB = libboost_system.so
	LFLAGS += $(foreach i, $(BOOST_LIB), $(BOOST_LIB)/$(i))

endif

#######################################################
#add rule to execute both mc and inverse

source/monte_carlo : $(OBJS)
	$(CXX) $(LFLAGS) $(CPPFLAGS) $(OBJS) -o source/monte_carlo

source/plotting.o: source/plotting.cpp h/metropolis.h h/clex.h
	cd source && $(CXX) -c plotting.cpp $(CPPFLAGS)

source/monte_carlo.o: source/monte_carlo.cpp h/metropolis.h h/clex.h
	cd source && $(CXX) -c monte_carlo.cpp $(CPPFLAGS)

source/metropolis.o: h/metropolis.h source/metropolis.cpp h/clex.h
	cd source && $(CXX) -c metropolis.cpp $(CPPFLAGS)

source/clex.o: h/clex.h source/clex.cpp
	cd source && $(CXX) -c clex.cpp $(CPPFLAGS)

external/jsonParser/jsonParser.o: FORCE
	cd external/jsonParser; make

FORCE:


clean:
	@rm -f *.o *~ monte_carlo metropolis plotting file_out clex clex.json
	@cd external/jsonParser; make clean
