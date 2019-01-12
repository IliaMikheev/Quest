#ifndef XMLSTORYWRITER_H
#define XMLSTORYWRITER_H

#include "dialogpoint_global.h"
#include <QObject>
#include <QString>
#include <QXmlStreamReader>
#include <QIODevice>
#include <QByteArray>
#include <QBuffer>
#include "dialogpoint.h"

/*!
 * \brief Класс предназначен для формирования xml файла
 * или байтового массива с описанием истории. *
 * xml должен иметь следущую структуру
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
 *
 * точки добавляются по одной.
 */


class DIALOGPOINTSHARED_EXPORT XmlStoryWriter
{    
public:    
    explicit XmlStoryWriter(QIODevice *device);
    explicit XmlStoryWriter(QByteArray *data);

    void append(const DialogPoint & point);
    void finalise();

    bool isValid() const; //??? имеет ли смысл?

    bool isFinished() const;

private:
    void start();
     void writeJumpList(const QStringList &jumps);
     void writeResources(const DialogPoint &point);
     void writeResourceCathegory(const QHash<QString, uint> &entry, const QString &name);
     void writeSingleAttrUnit(const QString &tag, const QString &attrName, const QString &attrValue);

     QXmlStreamWriter m_writer;
     QScopedPointer<QBuffer> m_buffer;
     int m_currentId;
     bool m_isValid;
     bool m_isFinished;


};

#endif // XMLSTORYWRITER_H
