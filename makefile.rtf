{\rtf1\ansi\ansicpg1252\cocoartf1343\cocoasubrtf140
{\fonttbl\f0\fswiss\fcharset0 Helvetica;}
{\colortbl;\red255\green255\blue255;}
\margl1440\margr1440\vieww15280\viewh12120\viewkind0
\pard\tx720\tx1440\tx2160\tx2880\tx3600\tx4320\tx5040\tx5760\tx6480\tx7200\tx7920\tx8640\pardirnatural

\f0\fs24 \cf0 ################################################\
# Compile with: 'make' or 'make example'\
# Clean with: 'make clean'\
#\
\
\
################################################\
# Change these if boost not installed in your compile search path:\
BOOST_INCLUDE = \
BOOST_LIB = \
\
\
################################################\
# Compiler options\
\
INCLUDE = \
ifneq "$(BOOST_INCLUDE)" ""\
	INCLUDE += $(BOOST_INCLUDE)\
endif\
\
\
OBJS = execute_mc.o monte_carlo.o clex.o metropolis.o jsonParser.o\
CXX      = g++ \
CPPFLAGS += -w -O3 $(foreach i,$(INCLUDE),-I$(i))\
\
ifeq "$(BOOST_LIB)" ""\
	LFLAGS = -lboost_system\
else\
	BOOST_LIB = libboost_system.so\
	LFLAGS += $(foreach i, $(BOOST_LIB), $(BOOST_LIB)/$(i))\
\
endif\
\
#######################################################\
//add rule to execute both mc and inverse\
\
execute_mc : $(OBJS)\
	$(CXX) $(LFLAGS) $(CPPFLAGS) $(OBJS) -o execute_mc\
\
//add execute_inverse_clex\
\
\
monte_carlo.o: monte_carlo.cpp metropolis.h clex.h json.h\
	$(CXX) -c monte_carlo.cpp $(CPPFLAGS)\
\
metropolis.o: metropolis.h metropolis.cpp clex.h\
	$(CXX) -c metropolis.cpp $(CPPFLAGS)\
\
clex.o: clex.h clex.cpp\
	$(CXX) -c clex.cpp $(CPPFLAGS)\
\
jsonParser.o: FORCE\
	cd external/jsonParser; make\
\
clean:\
	@rm -f *.o *~ monte_carlo metropolis file_out clex clex.json\
\
}