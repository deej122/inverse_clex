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


OBJS = monte_carlo.o plotting.o o/clex.o o/metropolis.o o/pass_eq_data.o external/jsonParser/jsonParser.o 
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

execute_mc : $(OBJS)
	$(CXX) $(LFLAGS) $(CPPFLAGS) $(OBJS) -o execute_mc

o/pass_eq_data.o: source/pass_eq_data.cpp h/metropolis.h h/clex.h
	$(CXX) -c source/pass_eq_data.cpp $(CPPFLAGS)

plotting.o: source/plotting.cpp h/metropolis.h h/clex.h
	$(CXX) -c source/plotting.cpp $(CPPFLAGS)

monte_carlo.o: source/monte_carlo.cpp h/metropolis.h h/clex.h
	$(CXX) -c source/monte_carlo.cpp $(CPPFLAGS)

o/metropolis.o: h/metropolis.h source/metropolis.cpp h/clex.h
	$(CXX) -c source/metropolis.cpp $(CPPFLAGS)

o/clex.o: h/clex.h source/clex.cpp
	$(CXX) -c source/clex.cpp $(CPPFLAGS)

external/jsonParser/jsonParser.o: FORCE
	cd external/jsonParser; make

FORCE:


clean:
	@rm -f *.o *~ monte_carlo metropolis plotting file_out clex clex.json
	@cd external/jsonParser; make clean
