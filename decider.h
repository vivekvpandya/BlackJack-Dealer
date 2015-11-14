#ifndef DECIDER_H
#define DECIDER_H

#include <QObject>
#include "table.h"

class Decider : public QObject
{
    Q_OBJECT
public:
    explicit Decider(QObject *parent = 0);
    std::vector<QString> gameDecider(Table *table);

signals:

public slots:
};

#endif // DECIDER_H
