#include "inventarylistmodel.h"

InventaryListModel::InventaryListModel(QObject *parent)
    : QAbstractListModel(parent)
{
}

int InventaryListModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_data.count();
}

/*! Возвращает даные элемента */
QVariant InventaryListModel::data(const QModelIndex &index, int role) const
{
    if (index.row() < 0 || index.row() >= m_data.count())
        return QVariant();
    int i = index.row();

    switch (role) {
    case NameRole:
        return m_data.at(i).name;
    case CountRole:
        return m_data.at(i).count;
    default:
        return QVariant();
    }
}

/*! Возвращает список ролей */
QHash<int, QByteArray> InventaryListModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[NameRole] = "name";
    roles[CountRole] = "count";
    return roles;
}

/*! Возвращает число строк */
int InventaryListModel::count() const
{
    return m_data.count();
}

/*! Добавляет  \a count экземпляров предмета с именем \a name в инвентарь
 * В случае переполнения значения uint (что маловероятно, но вё же)
 * устанавливает значение равное максимальному. *
 * */
void InventaryListModel::addItemCopy(const QString &name, uint count)
{    
    if (!m_itemHash.contains(name)) { // т.е. элемента с таким именем ещё нет
        int row =  m_data.length(); // т.к. новый вид ресурсов добавляется в конец
        m_itemHash[name] = row;
        QModelIndex index = indexWithRow(row);
        beginInsertRows(QModelIndex(), row, row);
        m_data.append(Items{name, count});
        endInsertRows();

        emit dataChanged(index,index);
        return;
    }
    int row = m_itemHash[name];
    if ((UINT_MAX - count) < m_data[row].count){        // Если увеличение числа предметов приведёт к переполнению (а вдруг?)
        m_data[row].count = UINT_MAX;                   // Число предметов становится максимальным (спорныймомент... )
    }
    else {
        m_data[row].count += count;
    }

    QModelIndex index = indexWithRow(row);
    emit dataChanged(index,index);
}

/*! Убирает \a count предметов с именем \a name из инвентаря
 *  Если таких предметов нет - ничего не забирает
 * Если пытается забрать больше экземпляров, чем есть - их
 * становитмся 0 (спорно, но пока так), даный ключ убирается из m_data
*/
void InventaryListModel::dropItemCopy(const QString &name, uint count)
{    
    if (!m_itemHash.contains(name)) { // т.е. элемента с таким именем ещё нет
        return;
    }

    int row = m_itemHash[name];
    if (count >= m_data[row].count) {// Если нужно забрать из инвентаря все копии данного предмета или больше чем есть

        beginRemoveRows(QModelIndex(), row, row);
        m_data.removeAt(row);        
        endRemoveRows();
        updateItemHash();
        return;
    }

    m_data[row].count -= count;

    QModelIndex index = indexWithRow(row);
    emit dataChanged(index,index);
}

/*! Метод изменения количества предметов, выбирающий, убрать, или добавить предмет
 *  на основе параметра \a add
 *
*/
void InventaryListModel::changeItems(const QString &name, uint count, bool add)
{
    if (add)
        addItemCopy(name, count);
    else
        dropItemCopy(name, count);
}

/*! Возвращает индекс элемента с установленным номером строки */
QModelIndex InventaryListModel::indexWithRow(int row)
{
    return createIndex(row, 0, static_cast<void *>(Q_NULLPTR));
}

/*! Возвращает количество экземпляров данного предмета
 * Если их нет, возвращает 0 */
uint InventaryListModel::itemCopyCount(const QString &name) const
{
    int row = m_data.indexOf(Items{name,0});
    if (row == -1){
        return 0;
    }
    return m_data[row].count;
}

/*! Используется, чтобы обновить m_itemHash целиком,
 *  например при удалении группы предметов из инвентаря */
void InventaryListModel::updateItemHash()
{
    m_itemHash.clear();
    int i = 0;
    foreach(Items cathegory, m_data) {
        m_itemHash[cathegory.name] = i;
        i++;
    }
}

/*!  Проверяет, содеожит ли инвентарь как минимум \a count предметов
 *   с именем \a name
*/
bool InventaryListModel::containsAtLeast(const QString & name, uint count)
{
    int i = m_itemHash.value(name, -1);
    if (i == -1)
        return false;

    if (m_data[i].count < count)
        return false;

    return true;
}

/*! Сравнивает состояние инвентаря с требуемым количеством предметов требуемых типов*/
bool InventaryListModel::isInventaryHas(const QHash<QString, uint> &requiredItems)
{
    if (requiredItems.isEmpty())
        return true;

    auto iter = requiredItems.begin();
    auto end =  requiredItems.end();
    while (iter != end) {
        if (!containsAtLeast(iter.key(), iter.value()))
            return false;
        iter++;
    }
    return true;
}
