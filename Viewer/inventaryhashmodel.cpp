#include "inventaryhashmodel.h"

/*! Конструктор */
InventaryHashModel::InventaryHashModel(QObject *parent)
    : QAbstractListModel(parent)
{

}

/*! Возвращает число строк */
int InventaryHashModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_data.count();
}

/*! Возвращает даные элемента */
QVariant InventaryHashModel::data(const QModelIndex &index, int role) const
{
    if (index.row() < 0 || index.row() >= m_data.count())
        return QVariant();
    auto iter = m_data.constBegin() + index.row();
    QVariant x = iter.key();
    QVariant y = iter.value();

    switch (role) {
    case NameRole:
        return iter.key();
    case CountRole:
        return iter.value();
    default:
        return QVariant();
    }
}

/*! Возвращает список ролей */
QHash<int, QByteArray> InventaryHashModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[NameRole] = "name";
    roles[CountRole] = "count";
    return roles;
}

/*! Возвращает число строк */
int InventaryHashModel::count() const
{
    return m_data.count();
}

/*! Добавляет  \a count экземпляров предмета с именем \a name в инвентарь
 * В случае переполнения значения uint (что маловероятно, но вё же)
 * устанавливает значение равное максимальному. *
 * */
void InventaryHashModel::addItemCopy(const QString &name, uint count)
{
    if (!m_data.contains(name)){
        m_data[name] = count;
        QModelIndex index = indexForName(name);
        beginInsertRows(QModelIndex(), index.row(), index.row());
        m_data[name] = count;
        endInsertRows();

        emit dataChanged(index,index);
        return;
    }

    if ((UINT_MAX - count) < m_data[name]){// Если увеличение числа предметов приведёт к переполнению (а вдруг?)
        m_data[name] = UINT_MAX;
    }
    else {
        m_data[name] +=count;
    }
    QModelIndex index = indexForName(name);
    emit dataChanged(index,index);
}

/*! Убирает \a count предметов с именем \a name из инвентаря
 *  Если таких предметов нет - ничего не забирает
 * Если пытается забрать больше экземпляров, чем есть - их
 * становитмся 0 (спорно, но пока так), даный ключ убирается из m_data
*/
void InventaryHashModel::dropItemCopy(const QString &name, uint count)
{
    if (!m_data.contains(name)){
        return;
    }

    if (count >= m_data.value(name)) {          // Если нужно забрать из инвентаря все копии данного предмета или больше чем есть,
        QModelIndex index = indexForName(name);
        beginRemoveRows(QModelIndex(), index.row(), index.row());
        m_data.remove(name);                    // предметов становится ноль, такой тип предметов убирается
        endRemoveRows();
        return;
    }

    m_data[name] -= count;

    QModelIndex index = indexForName(name);
    emit dataChanged(index,index);
}

/*! Метод изменения количества предметов, выбирающий, убрать, или добавить предмет
 *  на основе параметра \a add
 *  Можно было бы создать класс "changer" с наследниками "deleter" и "appender"
 *  но в данной ситуации это не оправдано. Лямбда функции?

*/
void InventaryHashModel::changeItems(const QString &name, uint count, bool add)
{
    if (add)
        addItemCopy(name, count);
    else
        dropItemCopy(name, count);

}

/*! Возвращает индекс элемента согласно его имени */
QModelIndex InventaryHashModel::indexForName(const QString &name) {
    if (!m_data.contains(name)) {
        return QModelIndex();
    }
    auto begin = m_data.begin();
    auto iter = m_data.find(name);
    int row = 0;
    while (iter != begin) {
        iter--;
        row++;
    }


    QModelIndex index = createIndex(row, 0, static_cast<void *>(0));
    return index;
}

/*! Возвращает количество экземпляров данного предмета
 * Если их нет, возвращает 0 */
int InventaryHashModel::itemCopyCount(const QString &name) const
{
    if (!m_data.contains(name)){
        return 0;
    }
    return m_data.value(name);
}

/*! Возвращает константную ссылку на инфентарь */
const QHash<QString, uint> &InventaryHashModel::toHash()
{
    return m_data;
}


