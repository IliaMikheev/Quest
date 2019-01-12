#ifndef DIALOGPOINT_H
#define DIALOGPOINT_H

#include "dialogpoint_global.h"
#include <QObject>
#include <QHash>
#include <QString>

class DIALOGPOINTSHARED_EXPORT DialogPoint
{

public:

    enum Resource {
        Keys,
        Payment,
        Award
    };

    DialogPoint();

    QString name() const;
    void setName(const QString &name);

    QString answer() const;
    void setAnswer(const QString &answer);

    const QStringList & jumps() const;
    void setJumps(const QStringList &jumps);

    void addJump(const QString & otherName);
    void removeJump(const QString & otherName);

    // Методы entryKeys() и entryPayment()  нужны, чтобы проверить, можно ли войти в данную точку
    const QHash<QString, uint> & entryKeys() const;
    const QHash<QString, uint> & entryPayment() const;
    const QHash<QString, uint> & entryAward() const;    // Вот тут вообще то нет необходимости, вроде бы

    void addEntry(DialogPoint::Resource type, const QString & name, uint count);
    void removeEntry(DialogPoint::Resource type, const QString & name);

    void addEntryKey(const QString &name, uint count);
    void addEntryAward(const QString &name, uint count);
    void addEntryPayment(const QString &name, uint count);
    void dropEntryKey(const QString &name);
    void dropEntryAward(const QString &name);
    void dropEntryPayment(const QString &name);
private:
    //void copy(const DialogPoint &other);    // А может нафиг его? с конструктором копирования, и перегрузкой =? Чем мне побитовое копирование не угодило
    QHash<QString, uint> &resource(DialogPoint::Resource type);

    QString m_name;
    QString m_answer;
    QStringList m_jumps;

    // QString - имя ресурса; uint - количество ресурса данного типа
    QHash<QString, uint> m_entryKeys;   // ресурсы, которые нужно иметь для входа в данную точку, но которые не требуется тратить
    QHash<QString, uint> m_entryAward;  // ресурсы, которые игрок получит за вход в эту точку
    QHash<QString, uint> m_entryPayment;// ресурсы, которые нужно отдать при входе в эту точку
};

#endif // DIALOGPOINT_H
