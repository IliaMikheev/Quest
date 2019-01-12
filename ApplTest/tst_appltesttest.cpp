#include <QString>
#include <QtTest>
#include <QCoreApplication>

class ApplTestTest : public QObject
{
    Q_OBJECT

public:
    ApplTestTest();

private Q_SLOTS:
    void testCase1();
};

ApplTestTest::ApplTestTest()
{
}

void ApplTestTest::testCase1()
{
    QVERIFY2(true, "Failure");
}

QTEST_MAIN(ApplTestTest)

#include "tst_appltesttest.moc"
