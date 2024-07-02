#ifndef LLOG_GLOBAL_H
#define LLOG_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(LLOG_LIBRARY)
#  define LLOG_EXPORT Q_DECL_EXPORT
#else
#  define LLOG_EXPORT Q_DECL_IMPORT
#endif

#endif // LLOG_GLOBAL_H
