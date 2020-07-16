#ifndef PERFORMANCECONTEXT_H
#define PERFORMANCECONTEXT_H

#include <QElapsedTimer>
#include <QList>

class PerformanceContext
{
public:
    PerformanceContext();
    ~PerformanceContext();

    void start();
//    void pause();
//    void resume();
    void stop();

    void reset();

    double average();
    double std();
    double fractionOfWallTime();
    qint64 min();
    qint64 max();
    int count();

private:
    QList<qint64> m_activeTimes;
    QList<qint64> m_inactiveTimes;
    QElapsedTimer m_timer;
    qint64 m_min;
    qint64 m_max;
    int m_lastIndex;
    bool m_active;
};

#endif // PERFORMANCECONTEXT_H
