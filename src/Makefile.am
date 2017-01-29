include $(top_srcdir)/m4/autotroll.mk

BUILT_SOURCES =																		\
	$(top_srcdir)/src/userinterface/mainwindow.moc.cpp

lib_LTLIBRARIES = libtrafficredirector.la
libtrafficredirector_la_LIBADD = $(QT_LIBS)
libtrafficredirector_la_LDFLAGS = $(QT_LDFLAGS)
libtrafficredirector_la_CPPFLAGS = $(QT_INCPATH) -std=c++11 -I$(top_srcdir)/src
libtrafficredirector_la_SOURCES = $(BUILT_SOURCES)			\
		userinterface/mainwindow.h							\
		userinterface/mainwindow.cpp						\
		\
		model/trafficdirectionmanager.h						\
		model/trafficdirectionmanager.cpp					\
		model/trafficdirection.h							\
		model/trafficdirection.cpp							\
		model/connection.h									\
		model/connection.cpp								\
		\
		network/networkprovider.h							\
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

trafficredirector_LDADD = $(QT_LIBS) $(top_builddir)/src/libtrafficredirector.la
trafficredirector_CPPFLAGS = $(QT_INCPATH) -std=c++11 -I$(top_srcdir)/src
trafficredirector_LDFLAGS = $(QT_LDFLAGS)
trafficredirector_SOURCES = main.cpp
	

