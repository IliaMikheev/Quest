#include <QString>
#include <QtTest>
#include "../DialogPoint/xmlstoryreader.h"
#include <QDebug>
#include <QCoreApplication>
#include <QFile>

class XmlStoryReaderTest : public QObject
{
    Q_OBJECT

public:
    XmlStoryReaderTest();

private Q_SLOTS:
    void testCase1();
};

XmlStoryReaderTest::XmlStoryReaderTest()
{
}

void XmlStoryReaderTest::testCase1()
{

    qDebug() << qApp->applicationDirPath();
    qDebug() << qApp->applicationFilePath();

    QFile file();
    //QFile file()


    //XmlStoryReader reader();

    //XmlStoryReader reader()
    //QCOMPARE(reader.test(),QString("I AM STORY READER"));
    //qDebug() << reader.test();
    //QVERIFY2(true, "Failure");
}

QTEST_MAIN(XmlStoryReaderTest)

#include "tst_xmlstoryreadertest.moc"
