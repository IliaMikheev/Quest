#ifndef INVENTARYHASHMODEL_H
#define INVENTARYHASHMODEL_H

#include <QObject>
#include <QAbstractListModel>

class InventaryHashModel : public QAbstractListModel
{
    Q_OBJECT
    //Q_PROPERTY(QString Name READ Name WRITE setName NOTIFY NameChanged)
    //Q_PROPERTY(int count READ count NOTIFY countChanged)  // Зачем мне это?
public:
    explicit InventaryHashModel(QObject *parent = 0);

    enum Roles {
        NameRole = Qt::UserRole+10,
        CountRole
    };

signals:
    //void countChanged(int count);

    // QAbstractItemModel interface
public:
    // Интерфейс с Qml - View
    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QHash<int, QByteArray> roleNames() const;

    // Интерфейс с кодом на  c++ (DialogMashine и др)
    int count() const;
    void addItemCopy(const QString & name, uint count);
    void dropItemCopy(const QString & name, uint count);
    void changeItems(const QString & name, uint count, bool add);

    int itemCopyCount(const QString &name) const;
    const QHash<QString, uint> &toHash();

private:
    QModelIndex indexForName(const QString &name);
   // int m_count;
    QHash<QString, uint> m_data; // Имена предметов в инвентаре и количество экземпляров каждого предмета

};

#endif // INVENTARYHASHMODEL_H
