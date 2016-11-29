lib_LTLIBRARIES = libtrafficredirector.la
libtrafficredirector_la_CPPFLAGS = -std=c++11 $(GLIBMM_CFLAGS) -I$(top_srcdir)/src
libtrafficredirector_la_SOURCES = 							\
		model/trafficdirectionmanager.h						\
		model/trafficdirectionmanager.cpp					\
		model/trafficdirection.h							\
		model/trafficdirection.cpp							\
		model/connection.h									\
		model/connection.cpp								\
		\
		network/tcpclient.h									\
		network/tcpclient.cpp								\
		network/tcpserver.h									\
		network/tcpserver.cpp								\
		network/udpclient.h									\
		network/udpclient.cpp								\
		\
		configuration/configurationmanager.h				\
		configuration/configurationmanager.cpp

bin_PROGRAMS=trafficredirector

trafficredirector_LDADD = $(top_builddir)/src/libtrafficredirector.la
trafficredirector_CPPFLAGS = -std=c++11 -I$(top_srcdir)/src
trafficredirector_LDFLAGS = $(GLIBMM_LIBS)
trafficredirector_SOURCES = main.cpp
	

