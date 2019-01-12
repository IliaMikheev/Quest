#ifndef XMLSTORYREADER_H
#define XMLSTORYREADER_H

#include "dialogpoint_global.h"
#include <QObject>
#include <QString>
#include <QXmlStreamReader>
#include <QIODevice>
#include <QByteArray>
#include "dialogpoint.h"

/*!
 * \brief Класс предназначен для преодразования xml файла
 * с описанием точек в классы DialogPoint.
 * xml файл должен иметь следущую структуру
 * <?xml version="1.0" encoding="utf-8"?>
 * <Story>
 *      <Point Id="...">
 *          <Name Text="..."/>
 *          <Answer Text="..."/>
 *          <Jump Name="..."/>
 *          <Jump Name="..."/>
 *          <Jump Name="..."/>
 *          ...
 *          <Entry>
 *              <Keys Name="..." Count="..."/>
 *              <Keys Name="..." Count="..."/>
 *              ...
 *              <Award Name="..." Count="..."/>
 *              <Award Name="..." Count="..."/>
 *              ...
 *              <Payment Name="..." Count="..."/>
 *              <Payment Name="..." Count="..."/>
 *              ...
 *          </Entry>
 *      </Point>
 *      <Point Id="...">...</Point>
 *      <Point Id="...">...</Point>
 *      ...
 * </Story>
 * количество элементов Jump, Keys, Award, Payment не регламентировано.
 * Name, Answer, Entry должно быть по одному... но не проверяется. Возможно, стоит перевести в аттрибуты.
 *
 * <?xml version="1.0" encoding="utf-8"?>
 * <Story>
 *      <Point Id="..." Name="..." Answer="...">
 *          <Jumps>
 *          </Jumps>
 *          <Keys>
 *          </Keys>
 *          <Award>
 *          </Award>
 *          <Payment>
 *          </Payment>
 *      </Point>
 *
 *          <Jump Name="..."/>
 *          <Jump Name="..."/>
 *          <Jump Name="..."/>
 *          ...
 *          <Entry>
 *              <Keys Name="..." Count="..."/>
 *              <Keys Name="..." Count="..."/>
 *              ...
 *              <Award Name="..." Count="..."/>
 *              <Award Name="..." Count="..."/>
 *              ...
 *              <Payment Name="..." Count="..."/>
 *              <Payment Name="..." Count="..."/>
 *              ...
 *          </Entry>
 *      </Point>
 *      <Point Id="...">...</Point>
 *      <Point Id="...">...</Point>
 *      ...
 * </Story>
 */

class DIALOGPOINTSHARED_EXPORT XmlStoryReader
{
public:

public:
    explicit XmlStoryReader(QIODevice *device);
    explicit XmlStoryReader(const QByteArray &data);

    bool next(); // Сдвигается на одну точку вперёд, если это возможно

    DialogPoint point();
    QString name();

    bool isValid() const;

signals:

public slots:

private:
    QXmlStreamReader m_reader;
    bool m_isValid;
    DialogPoint m_dialogPoint;
private:
    bool startCheck();

    void fillPointData();
    void fillResourcesData();
    DialogPoint::Resource getResource(QStringRef name, bool *ok);
};

#endif // XMLSTORYREADER_H
