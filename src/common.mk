# Makefile definitions here common to multiple Makefiles
CXXFLAGS := -std=c++11 -Wall -O3 ${CXXFLAGS} \
  -Wno-deprecated-declarations # temporarily due to setColor version conflict
