#ifndef GAMAQ2INTERFACES_gama_q2_interfaces_H
#define GAMAQ2INTERFACES_gama_q2_interfaces_H

#include <QString>
class QWidget;

class DbInterface
{
public:
    virtual ~DbInterface() {}
    virtual QString getName() = 0;
    virtual QWidget* create() = 0;
};

QT_BEGIN_NAMESPACE
Q_DECLARE_INTERFACE(DbInterface, "org.gnu.gama.gama-q2.DbInterface/1.0")
QT_END_NAMESPACE

#endif // GAMAQ2INTERFACES_gama_q2_interfaces_H
