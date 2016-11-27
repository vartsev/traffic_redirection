noinst_LTLIBRARIES = libtrafficredirectortest.la
libtrafficredirectortest_la_CPPFLAGS = -std=c++11 $(GLIBMM_CFLAGS) -I$(top_srcdir)/src
libtrafficredirectortest_la_SOURCES =  main.cpp

noinst_PROGRAMS=trafficredirectortest

trafficredirectortest_LDADD = $(top_builddir)/src/libtrafficredirector.la $(top_builddir)/test/libtrafficredirectortest.la
trafficredirectortest_CPPFLAGS = -std=c++11 \
											-I$(top_srcdir)/src \
											-I$(top_srcdir)/test
trafficredirectortest_LDFLAGS = $(GLIBMM_LIBS)
trafficredirectortest_SOURCES = main.cpp
	

