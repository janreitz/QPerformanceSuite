#ifndef PERFORMANCESUITE_GLOBAL_H
#define PERFORMANCESUITE_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(PERFORMANCESUITE_LIBRARY)
#  define PERFORMANCESUITE_EXPORT Q_DECL_EXPORT
#else
#  define PERFORMANCESUITE_EXPORT Q_DECL_IMPORT
#endif

#endif // PERFORMANCESUITE_GLOBAL_H
