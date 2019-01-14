#ifndef INVENTARYLISTMODEL_H
#define INVENTARYLISTMODEL_H

#include <QAbstractListModel>

class InventaryListModel : public QAbstractListModel
{
    Q_OBJECT

public:
    explicit InventaryListModel(QObject *parent = Q_NULLPTR);

    enum Roles {
        NameRole = Qt::UserRole+10,
        CountRole
    };

    struct Items {
        QString name;
        uint count;

        bool operator ==(const Items & other) const {
            return name == other.name;
        }
    };

    // Интерфейс с Qml - View
    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QHash<int, QByteArray> roleNames() const;

    // Интерфейс с кодом на  c++ (DialogMashine и др)
    int count() const;
    void addItemCopy(const QString & name, uint count);
    void dropItemCopy(const QString & name, uint count);
    void changeItems(const QString & name, uint count, bool add);

    uint itemCopyCount(const QString &name) const;

    bool containsAtLeast(const QString &name, uint count);    
    bool isInventaryHas(const QHash<QString, uint> &requiredItems);

private:
    void updateItemHash();    
    QModelIndex indexWithRow(int row);

    QHash<QString, int> m_itemHash; // Имена предметов в инвентаре и количество экземпляров каждого предмета
    QList<Items> m_data;

};

#endif // INVENTARYLISTMODEL_H
