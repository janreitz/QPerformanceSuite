#include "performancecontext.h"
#include <QDebug>

PerformanceContext::PerformanceContext()
    : m_min(99999999)
    , m_max(0)
    , m_lastIndex(0)
    , m_active(false)
{
}

PerformanceContext::~PerformanceContext()
{
}

void PerformanceContext::start()
{
    if (m_active)
        qDebug() << "PerformanceContext::start -> multiple start before stop";

    static bool firstCall = false;
    if (!firstCall)
        m_inactiveTimes << m_timer.elapsed();

    m_active = true;
    m_timer.start();
}

void PerformanceContext::stop()
{
    const qint64 elapsed = m_timer.elapsed();
    m_active = false;
    m_timer.start();
    m_activeTimes << elapsed;
    if (elapsed > m_max)
        m_max = elapsed;
    if (elapsed < m_min)
        m_min = elapsed;
}

void PerformanceContext::reset()
{
    m_lastIndex = m_activeTimes.count();
}

double PerformanceContext::average()
{
    qint64 total = 0;
    for (int i = m_lastIndex; i < m_activeTimes.count(); i++)
    {
        total += m_activeTimes[i];
    }
    const int _count = count();
    if(_count == 0)
        return 0;
    return total/_count;
}

double PerformanceContext::std()
{
    const double avg = average();
    double deviations = 0;
    for (int i = m_lastIndex; i < m_activeTimes.count(); i++)
    {
        deviations += pow(m_activeTimes[i] - avg, 2);
    }
    const int _count = count();
    if(_count == 0)
        return 0;
    return deviations/_count;
}

double PerformanceContext::fractionOfWallTime()
{
    double inactiveTime = 0;
    for (int i = m_lastIndex; i < m_inactiveTimes.count(); i++)
    {
        inactiveTime += m_inactiveTimes[i];
    }
    double activeTime = 0;
    for (int i = m_lastIndex; i < m_activeTimes.count(); i++)
    {
        activeTime += m_activeTimes[i];
    }
    if (activeTime + inactiveTime == 0)
        return 0;
    return activeTime / (activeTime + inactiveTime);
}

qint64 PerformanceContext::min()
{
    return m_min;
}

qint64 PerformanceContext::max()
{
    return m_max;
}

int PerformanceContext::count()
{
    return m_activeTimes.count() - m_lastIndex;
}
