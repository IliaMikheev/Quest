#include "jumplistmodel.h"
#include <QDebug>

JumpListModel::JumpListModel(QObject *parent) : QAbstractListModel(parent)
{

}

int JumpListModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_texts.count();
}

QVariant JumpListModel::data(const QModelIndex &index, int role) const
{
    Q_UNUSED(role)
    return m_texts[index.row()];
}

QHash<int, QByteArray> JumpListModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[TextRole] = "textRole";
    return roles;
}

QStringList JumpListModel::texts() const
{
    return m_texts;
}

/*! Фактически полностью заменяет всю модель */
void JumpListModel::setTexts(const QStringList &texts)
{

    if (m_texts.count()) {
        beginRemoveRows(QModelIndex(),0,m_texts.count()-1);
        m_texts.clear();
        endRemoveRows();
    }
    /*
    beginRemoveRows(QModelIndex(),0,m_texts.count() );
    endRemoveRows();
    */
    if(texts.count()) {
        beginInsertRows(QModelIndex(), 0, texts.count()-1);
        m_texts = texts;
        endInsertRows();
    }
    /*
    int x = texts.count();
    int y = texts.size();
    qDebug() << "Rows count " + QString::number(texts.count());
    qDebug() << "Rows count " + QString::number(texts.size());
    qDebug() << x <<" " << y;
    */

}

QString JumpListModel::pointText(int index)
{
    return m_texts[index];
}


