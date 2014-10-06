bin_PROGRAMS = 3dspec

3dspec_SOURCES = src/3dspec.cc src/load_off.cc src/vector.cc src/object.cc \
                 include/3dspec.h include/object.h include/list.h include/vector.h include/matrix.h 

3dspec_CPPFLAGS = -I$(top_srcdir)/include
3dspec_CXXFLAGS = -Wall
3dspec_LDFLAGS = -lalleg -lalleg_unsharable

EXTRA_DIST = off/box.off off/dice.off off/pyramid.off off/tri.off
