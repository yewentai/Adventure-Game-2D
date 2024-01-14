#ifndef PROTAGONISTMODEL_H
#define PROTAGONISTMODEL_H

#include <QObject>
#include "lib/world.h"

class ProtagonistModel : public Protagonist {
    Q_OBJECT
public:
    ProtagonistModel();

    bool getIsPoisoned() const;

    void setIsPoisoned(bool newIsPoisoned);

private:
    bool isPoisoned{false};

public
    slots:
            signals
    :

    void protagPoisoned();

    void protagRecovered();
};

#endif // PROTAGONISTMODEL_H
