#include "performancesuite.h"

#include <QDebug>
#include <QFile>

PerformanceSuite* PerformanceSuite::m_instance=nullptr;

PerformanceSuite::PerformanceSuite()
{
    connect(&m_wallTimer, &QTimer::timeout, this, &PerformanceSuite::outputToQDebug);
    m_wallTimer.start(m_displayIntervalInS * 1000);
}

PerformanceSuite *PerformanceSuite::getInstance()
{
    if (!m_instance)
        m_instance = new PerformanceSuite();
    return m_instance;
}

void PerformanceSuite::tick(const QString &context)
{
    if (!m_performanceContextsByName.contains(context))
        m_performanceContextsByName[context] = std::make_shared<PerformanceContext>();

    m_performanceContextsByName[context]->start();
}

void PerformanceSuite::tock(const QString &context)
{
    Q_ASSERT(m_performanceContextsByName.contains(context));
    m_performanceContextsByName[context]->stop();
}

void PerformanceSuite::writeToFile(const QString &filePath)
{
    QFile file(filePath);
    if (file.exists())
    {
        qDebug() << "PerformanceSuite::writeToFile -> file already exists";
        return;
    }
    if (file.open(QIODevice::WriteOnly))
    {
        static const QString header("");
        for (const auto name : m_performanceContextsByName.keys())
        {
            file.write("todo");
        }
    }
}

void PerformanceSuite::outputToQDebug()
{
    if (m_performanceContextsByName.isEmpty())
        return;

    qDebug() << QString(" - - - - - - - - - - - - - - PerformanceSuite Results (%1) - - - - - - - - - - - - - - ").arg(m_displayIntervalInS);
    for (auto name : m_performanceContextsByName.keys())
    {
        const auto performanceContext = m_performanceContextsByName[name];
        qDebug() << name + QString(" avg: %1  std: %2 min: %3 max: %4 calls: %5 cpuTime: %6%")
                 .arg(performanceContext->average(), 5)
                 .arg(performanceContext->std(), 5)
                 .arg(performanceContext->min(), 5)
                 .arg(performanceContext->max(), 5)
                 .arg(performanceContext->count(), 5)
                 .arg(performanceContext->fractionOfWallTime() * 100, 5);
        performanceContext->reset();
    }

}

