#ifndef PERFORMANCESUITE_H
#define PERFORMANCESUITE_H

#include "PerformanceSuite_global.h"
#include "performancecontext.h"
#include <QObject>
#include <QMap>
#include <QTimer>
#include <QElapsedTimer>
#include <memory>


class PERFORMANCESUITE_EXPORT PerformanceSuite : public QObject
{
    Q_OBJECT
public:
    static PerformanceSuite* getInstance();

    void tick(const QString& context);
    void tock(const QString& context);
    void writeToFile(const QString& filePath);

public slots:
    void outputToQDebug();

private:
    PerformanceSuite();

    QTimer m_wallTimer;
    // unique_ptr
    QMap<QString, std::shared_ptr<PerformanceContext>> m_performanceContextsByName;
    static PerformanceSuite* m_instance;
    static constexpr int m_displayIntervalInS = 5;
};

#endif // PERFORMANCESUITE_H
