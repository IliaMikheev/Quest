#include <QString>
#include <QtTest>
#include "../DialogPoint/xmlstorywriter.h"

class XmlStoryWriterTest : public QObject
{
    Q_OBJECT

public:
    XmlStoryWriterTest();

private Q_SLOTS:
    void testCase1();
};

XmlStoryWriterTest::XmlStoryWriterTest()
{
}

void XmlStoryWriterTest::testCase1()
{
    //XmlStoryWriter writer;
    //QCOMPARE(writer.test(),QString("I AM STORY WRITER"));
    //qDebug() << writer.test();

    //QVERIFY2(true, "Failure");
}

QTEST_APPLESS_MAIN(XmlStoryWriterTest)

#include "tst_xmlstorywritertest.moc"
