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


OBJS = o/clex.o o/unit_test_clex.o external/jsonParser/jsonParser.o
OBJS2 = o/clex.o o/create_unit_test_clex_key.o external/jsonParser/jsonParser.o
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

execute_clex_unit_test : $(OBJS)
	$(CXX) $(LFLAGS) $(CPPFLAGS) $(OBJS) -o test/execute_clex_unit_test

execute_create_unit_test_key : $(OBJS2)
	$(CXX) $(LFLAGS) $(CPPFLAGS) $(OBJS2) -o test/create_unit_test_key

o/create_unit_test_key.o: source/create_unit_test_clex_key.cpp h/clex.h
	$(CXX) -c source/create_unit_test_clex_key.cpp $(CPPFLAGS)

o/unit_test_clex.o: source/unit_test_clex.cpp h/clex.h
	$(CXX) -c source/unit_test_clex.cpp $(CPPFLAGS)

o/clex.o: h/clex.h source/clex.cpp
	$(CXX) -c source/clex.cpp $(CPPFLAGS)

external/jsonParser/jsonParser.o: FORCE
	cd external/jsonParser; make

FORCE:


clean:
	@rm -f *.o *~ monte_carlo metropolis file_out clex clex.json unit_test_clex
	@cd external/jsonParser; make clean
