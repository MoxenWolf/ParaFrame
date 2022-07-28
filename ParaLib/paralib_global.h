#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(PARALIB_LIB)
#  define PARALIB_EXPORT Q_DECL_EXPORT
# else
#  define PARALIB_EXPORT Q_DECL_IMPORT
# endif
#else
# define PARALIB_EXPORT
#endif
