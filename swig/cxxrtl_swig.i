/* -*- c++ -*- */

#define CXXRTL_API

%include "gnuradio.i"           // the common stuff

//load generated python docstrings
%include "cxxrtl_swig_doc.i"

%{
#include "cxxrtl/sim.h"
%}

%include "cxxrtl/sim.h"
GR_SWIG_BLOCK_MAGIC2(cxxrtl, sim);
