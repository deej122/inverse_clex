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


CXX      = g++ 
CPPFLAGS += -w $(foreach i,$(INCLUDE),-I$(i))

ifeq "$(BOOST_LIB)" ""
	LFLAGS = -lboost_system
else
	BOOST_LIB = libboost_system.so
	LFLAGS += $(foreach i, $(BOOST_LIB), $(BOOST_LIB)/$(i))

endif

#######################################################

example: example.o jsonParser.o
	$(CXX) -o example example.o jsonParser.o $(CPPFLAGS) $(LFLAGS)

example.o: example.cpp
	$(CXX) -c example.cpp $(CPPFLAGS)

jsonParser.o: jsonParser.hh jsonParser.cc
	$(CXX) -c jsonParser.cc $(CPPFLAGS)

clean:
	@rm -f *.o example example.json

