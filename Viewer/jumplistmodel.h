#ifndef JUPMSLISTMODEL_H
#define JUPMSLISTMODEL_H

#include <QObject>
#include <QAbstractListModel>

class JumpListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit JumpListModel(QObject *parent = Q_NULLPTR);

    enum Roles {
        TextRole = Qt::UserRole,
    };

    // Интерфейс с Qml - View
    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QHash<int, QByteArray> roleNames() const;

    // Интерфейс с C++ (DialogMashine и др.)
    QStringList texts() const;
    void setTexts(const QStringList &texts); //
    QString pointText(int index);

signals:

public slots:

private:
    QStringList m_texts; // или всё таки будут не строки, а int id?
};

#endif // JUPMSLISTMODEL_H
