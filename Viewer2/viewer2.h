#ifndef VIEWER_H
#define VIEWER_H

#include <QObject>
#include <QQmlApplicationEngine>
#include "jumplistmodel.h"
#include "inventarylistmodel.h"
#include "../DialogPoint/dialogpoint.h"
#include <QStack>

class Viewer2 : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString answer READ answer NOTIFY answerChanged)
public:
    explicit Viewer2(QObject *parent = 0);


    void initModels(QQmlApplicationEngine &engine);
    Q_INVOKABLE QString answer();

    void jumpTo(const QString &pointName);

signals:
    void answerChanged(QString);

public slots:
    Q_INVOKABLE void onJumpSelected(int);
    Q_INVOKABLE void onJumpBack();


private:
    QStringList filterAvaileble(const QStringList &jumpsNames);
    void initDialog();
    void addToInventary(const QHash<QString, uint> &items);
    void dropFromInventary(const QHash<QString, uint> &items);

    QString m_answer;
    JumpListModel * m_jumpListModel;
    InventaryListModel * m_inventaryModel;
    DialogPoint m_point;
    QHash<QString, DialogPoint> m_storyPoints;
    QStack<QString> m_jumpStack;




};

#endif // VIEWER_H
