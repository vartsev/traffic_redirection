dnl Process this file with autoconf to produce a configure script.

AC_PREREQ(2.59)
AC_INIT(traffic_redirector, 0.1)


AC_CANONICAL_SYSTEM
AM_INIT_AUTOMAKE([subdir-objects])

AC_PROG_CXX
AC_PROG_CC
AC_LANG([C++])
AC_PROG_LIBTOOL

ACLOCAL_AMFLAGS = '-I m4'

AT_WITH_QT()

AC_SUBST( install_dir, "/usr/share/traffic_redirector/")

AC_MSG_CHECKING([if release version needed])
AC_ARG_ENABLE([release], [ --enable-release 	enable release version],
[ 
	CPPFLAGS="-O3 -Wall -fmessage-length=0 ";
	CXXFLAGS="";
	AC_MSG_RESULT([yes])
	AC_DEFINE_UNQUOTED( CONFIG_DIR, "${install_dir}")
],
[ 
	CPPFLAGS="-O0 -g3 -Wall -fmessage-length=0 ";
	CXXFLAGS="";
	AC_MSG_RESULT([no])
	AC_DEFINE( DEBUG)
	AC_DEFINE_UNQUOTED( CONFIG_DIR, "${srcdir}/config/")
])

AC_CHECK_LIB([gtest], [main], [],
[ 
	echo "gtest failure." 
	exit -1
])

AC_CHECK_LIB([gmock], [main], [],
[ 
	echo "gmock failure." 
	exit -1
])

AC_CHECK_LIB([boost_system], [main], [],
[ 
	echo "boost_system failure." 
	exit -1
])

AC_CHECK_LIB([boost_filesystem], [main], [], 
[
	echo "boost_filesystem failure."
	exit -1
])

AC_CHECK_LIB([boost_thread], [main], [],
[ 
	echo "boost_thread failure." 
	exit -1
])

AC_CHECK_LIB([pthread], [main], [],
[ 
	echo "pthread failure." 
	exit -1
])

AC_CHECK_HEADERS([stdint.h], [], 
[
	echo "stdint.h failure."
	exit -1
])

# Checks for typedefs, structures, and compiler characteristics.
AC_HEADER_STDBOOL
AC_C_INLINE
AC_TYPE_UINT32_T
AC_TYPE_UINT8_T

# Checks for library functions.
AC_CHECK_FUNCS([memset])

AC_PREFIX_DEFAULT( "/usr/")

AC_CONFIG_MACRO_DIR([m4])

AC_CONFIG_FILES(Makefile 
				src/Makefile
				test/Makefile)
AC_OUTPUT

