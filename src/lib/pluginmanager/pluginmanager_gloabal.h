﻿#ifndef PLUGINMANAGER_GLOBAL_H__
#define PLUGINMANAGER_GLOBAL_H__

#include <QtCore/qglobal.h>

#if defined(PLUGINSMANAGER_LIBRARY)
#  define PLUGINSMANAGERSHARED_EXPORT Q_DECL_EXPORT
#else
#  define PLUGINSMANAGERSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif
