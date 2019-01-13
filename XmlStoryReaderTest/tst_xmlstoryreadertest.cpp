#include <QString>
#include <QtTest>
#include "../DialogPoint/xmlstoryreader.h"
#include <QDebug>
#include <QCoreApplication>
#include <QFile>
#include <QIODevice>
#include <QByteArray>


class XmlStoryReaderTest : public QObject
{
    Q_OBJECT

    void printPointEntry(const QHash<QString, uint> &entry, QString name);
    void testName(XmlStoryReader &reader);
public:
    XmlStoryReaderTest();

private Q_SLOTS:
    void testCase1();
    void testCase2();
    void testCase3();
    void testCase4();

};

XmlStoryReaderTest::XmlStoryReaderTest()
{

}

/*! Проверяет что: конструктор на основе файла - работает,
 *  файл прочитан, reader читает точки, видит их имена
*/
void XmlStoryReaderTest::testCase1()
{
    QString path = qApp->applicationDirPath() + "/story.xml";
    QFile file(path);
    QVERIFY2(file.open(QIODevice::ReadOnly), "File not open!");

    XmlStoryReader reader(&file);
    QByteArray story = file.readAll();
    testName(reader);

    file.close();
}

/*! Проверяет что: конструктор на основе байтового массива - работает,
 *  файл прочитан, reader читает точки, видит их имена
*/
void XmlStoryReaderTest::testCase2()
{
    QString path = qApp->applicationDirPath() + "/story.xml";
    QFile file(path);
    QVERIFY2(file.open(QIODevice::ReadOnly), "File not open!");

    QByteArray story = file.readAll();
    XmlStoryReader reader(story);
    testName(reader);

    file.close();
}

void XmlStoryReaderTest::testName(XmlStoryReader & reader)
{
    QVERIFY2(reader.isValid(),"Reader is not valid");
    while (reader.next()) {
        QString name = reader.name();
        QVERIFY2(!name.isEmpty(), "Point is Empty!");
    }
}

/*! Проверяет, что reader корректно читает содержимое точек*/
void XmlStoryReaderTest::testCase3()
{
    QString path = qApp->applicationDirPath() + "/story.xml";
    QFile file(path);
    QVERIFY2(file.open(QIODevice::ReadOnly), "File not open!");

    XmlStoryReader reader(&file);
    int i = 0;

    QStringList names;
    names << "First" << "Second" << "Third" << "Fourts" << "Last";

    QList<int> nJumps;
    nJumps << 3 << 3 << 3 << 4 << 1;

    while (reader.next()) {
        DialogPoint point = reader.point();
        //qDebug() << "**************nextPoint************";
        QCOMPARE(names[i],point.name());
        QCOMPARE(nJumps[i], point.jumps().count());
        i++;
    }
}

/*! Просто печатает в консоль все параметры всех прочитанных точек
 *  для беглой прроверки "на глаз".
*/
void XmlStoryReaderTest::testCase4()
{
    QString path = qApp->applicationDirPath() + "/story.xml";
    QFile file(path);
    QVERIFY2(file.open(QIODevice::ReadOnly), "File not open!");

    XmlStoryReader reader(&file);

    while (reader.next()) {
        DialogPoint point = reader.point();
        qDebug() << "**************nextPoint************";
        qDebug() << "Name: " << point.name();
        qDebug() << "Answer: " << point.answer();
        foreach(QString jump, point.jumps()) {
            qDebug() << "Jump" << jump;
        }
        printPointEntry(point.entryKeys(), "Key");
        printPointEntry(point.entryAward(), "Award");
        printPointEntry(point.entryPayment(), "Payment");
    }
}

void XmlStoryReaderTest::printPointEntry(const QHash<QString, uint> & entry, QString name)
{
    auto iter = entry.begin();
    auto end = entry.end();
    while( iter != end ) {
        qDebug() << name << ": " << iter.key() << " " << iter.value();
        iter++;
    }
}


QTEST_MAIN(XmlStoryReaderTest)

#include "tst_xmlstoryreadertest.moc"
