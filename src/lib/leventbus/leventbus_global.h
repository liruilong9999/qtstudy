#ifndef LEVENTBUS_GLOBAL_H
#define LEVENTBUS_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(LEVENTBUS_LIBRARY)
#define LEVENTBUS_EXPORT Q_DECL_EXPORT
#else
#define LEVENTBUS_EXPORT Q_DECL_IMPORT
#endif

#endif // LLOG_GLOBAL_H
