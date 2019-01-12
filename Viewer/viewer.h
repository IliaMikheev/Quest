#ifndef VIEWER_H
#define VIEWER_H

#include <QObject>
#include "../DialogPoint/dialogpoint.h"
#include <QHash>
#include <QStack>
#include <QFile>

#include <QQmlApplicationEngine>
//#include "inventaryhashmodel.h"
#include "inventarylistmodel.h"
#include "jumplistmodel.h"

class Viewer : public QObject
{
    Q_OBJECT

     Q_PROPERTY(QString answer READ answer NOTIFY answerChanged)
public:
    explicit Viewer(QObject *parent = 0);

    void initModels(QQmlApplicationEngine &engine);
    Q_INVOKABLE QString answer();

    void addPoint(const DialogPoint &point);
    void jumpTo(const QString &pointName);
signals:
    void answerChanged(QString);


public slots:
    Q_INVOKABLE void onJumpSelected(int);
    Q_INVOKABLE void onJumpBack();

private:
    void initDialog();
    void fillStory(const QString & filename);
    QStringList filterAvaileble(const QStringList &jumpsNames);
    void changeInventary(const QHash<QString, uint> &items, bool add);
    void addToInventary(const QHash<QString, uint> &items);
    void dropFromInventary(const QHash<QString, uint> &items);
    bool isInventaryHas(const QHash<QString, uint> &requiredItems);

    QString m_answer;
    JumpListModel *m_jumpListModel;
    InventaryListModel *m_inventaryModel;
    QHash<QString, DialogPoint> m_storyPoints;
    QStack<QString> m_jumpStack;


};

#endif // VIEWER_H
