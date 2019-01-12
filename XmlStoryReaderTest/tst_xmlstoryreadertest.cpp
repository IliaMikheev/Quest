#include <QString>
#include <QtTest>
#include "../DialogPoint/xmlstoryreader.h"
#include <QDebug>
#include <QCoreApplication>
#include <QFile>
#include <QIODevice>

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

    QFile file("story.xml");
    QVERIFY2(file.open(QIODevice::ReadOnly), "File not open!");
    XmlStoryReader reader(&file);
    while (reader.next()) {
        QString name = reader.name(); // А чем инициализированы эти точки?
        QVERIFY2(!name.isEmpty(), "Point is Empty!");
    }

}

QTEST_MAIN(XmlStoryReaderTest)

#include "tst_xmlstoryreadertest.moc"
