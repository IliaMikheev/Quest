#include "dialogpoint.h"


DialogPoint::DialogPoint()
{
}


QString DialogPoint::name() const
{
    return m_name;
}

void DialogPoint::setName(const QString &name)
{
    m_name = name;
}

QString DialogPoint::answer() const
{
    return m_answer;
}

void DialogPoint::setAnswer(const QString &answer)
{
    m_answer = answer;
}

const QStringList &DialogPoint::jumps() const
{
    return m_jumps;
}

void DialogPoint::setJumps(const QStringList &jumps)
{
    m_jumps = jumps;
}

void DialogPoint::addJump(const QString &otherName)
{
    if (m_jumps.contains(otherName))
        return;
    m_jumps.append(otherName);
}

void DialogPoint::removeJump(const QString &otherName)
{
    m_jumps.removeOne(otherName);
}

const QHash<QString, uint> &DialogPoint::entryKeys() const
{
    return m_entryKeys;
}

const QHash<QString, uint> &DialogPoint::entryPayment() const
{
    return m_entryPayment;
}

const QHash<QString, uint> &DialogPoint::entryAward() const
{
    return m_entryAward;
}

/*! Добавляет пару значений - имя ресурса + его количество
 *  в одну из таблиц ресурсов (в зависимости от \a type):
 *  - ключи для входа (нужно иметь с собой но е нужно тратить
 *  - нужно потратить для входа
 *  - будет получено при входе
*/
void DialogPoint::addEntry(Resource type, const QString &name, uint count)
{
    QHash<QString, uint> &table = resource(type);
    table[name] = count;
}

/*! Добавляет категорию ключей для входа с именем \a name и количеством \a count */
void DialogPoint::addEntryKey(const QString &name, uint count)
{
    m_entryKeys[name] = count;
}

/*! Добавляет категорию ресурсов получаемых при входе с именем \a name и количеством \a count */
void DialogPoint::addEntryAward(const QString &name, uint count)
{
    m_entryAward[name] = count;
}

/*! Добавляет категорию ресурсов отдаваемых за вход с именем \a name и количеством \a count */
void DialogPoint::addEntryPayment(const QString &name, uint count)
{
    m_entryPayment[name] = count;
}

/*! Удаляет категорию ключей для входа именем \a name */
void DialogPoint::dropEntryKey(const QString &name)
{
    m_entryKeys.remove(name);
}

/*! Удаляет категорию ресурсов получаемых при входе с именем \a name */
void DialogPoint::dropEntryAward(const QString &name)
{
    m_entryAward.remove(name);
}

/*! Удаляет категорию ресурсов отдаваемых за вход с именем \a name */
void DialogPoint::dropEntryPayment(const QString &name)
{
    m_entryPayment.remove(name);
}


/*! Удаляет пару значений - имя ресурса + его количество из
 *  одной из таблиц ресурсов (в зависимости от \a type)
*/
void DialogPoint::removeEntry(DialogPoint::Resource type, const QString &name)
{
    resource(type).remove(name);
}

/*! Возвращает ссылку на таблицу ресурсов, согласно \a type */
QHash<QString, uint>& DialogPoint::resource(DialogPoint::Resource type)
{
    switch(type) {
    case Resource::Keys:
        return m_entryKeys;
    case Resource::Payment:
        return m_entryPayment;
    case Resource::Award:
        return m_entryAward;
    }
    // Вообще то не очень хорошо. Но по ссылке нужно возвращать реально существующий объект...
    // С учётом того, что в switch перечислены все варианты Resource,мы никогда сюда не попадём.
    return m_entryKeys; // Это конечно приведет к отсутствию предупреждения...
}
