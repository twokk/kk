#ifndef SCRIPT_GLOBAL_H
#define SCRIPT_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(SCRIPT_LIBRARY)
#  define SCRIPTSHARED_EXPORT Q_DECL_EXPORT
#else
#  define SCRIPTSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // SCRIPT_GLOBAL_H
