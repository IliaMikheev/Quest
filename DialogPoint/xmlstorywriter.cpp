#include "xmlstorywriter.h"
#include <QBuffer>

/*! Конструктор для записи истории в файл */
XmlStoryWriter::XmlStoryWriter(QIODevice *device)
{
    m_writer.setDevice(device);
    start();
}

/*! Конструктор для записи истории в бинарный массив */
XmlStoryWriter::XmlStoryWriter(QByteArray *data)
{
    m_buffer.reset(new QBuffer(data));
    m_writer.setDevice(m_buffer.data());
    start();
}

/*! Используется из конструктора после настройки m_writer
 * Создаёт начало документа, главный элемент.
*/
void XmlStoryWriter::start()
{
    m_writer.setAutoFormatting(true);
    m_writer.writeStartDocument();
    m_writer.writeProcessingInstruction("xml", "version=\"1.0\" encoding=\"utf-8\"");
    m_writer.writeStartElement("Story");
    m_isValid = !m_writer.hasError();
    m_isFinished = false;
    //m_writer.writeEndElement();
}

/*! Добавляет точку в историю */
void XmlStoryWriter::append(const DialogPoint &point)
{
    m_writer.writeStartElement("Point");
    m_writer.writeAttribute("Id", QString::number(m_currentId++)); //
    writeSingleAttrUnit("Name", "Text", point.name());
    writeSingleAttrUnit("Answer", "Text", point.answer());
    writeJumpList(point.jumps());
    writeResources(point);
    m_writer.writeEndElement();
    m_isValid = !m_writer.hasError();
}

/*! Добавляет xml элемент с одним аттрибутом */
void XmlStoryWriter::writeSingleAttrUnit(const QString & tag, const QString & attrName, const QString & attrValue)
{
    m_writer.writeStartElement(tag);
    m_writer.writeAttribute(attrName, attrValue);
    m_writer.writeEndElement();
}


/*! Добавляет список переходов в другие точки */
void XmlStoryWriter::writeJumpList(const QStringList & jumps)
{
    foreach (QString jump, jumps) {
        writeSingleAttrUnit("Jump", "Name", jump);
    }
}

/*! Добавляет группу ресурсов точки. Что, если у точки нет ресурсов? */
void XmlStoryWriter::writeResources(const DialogPoint &point)
{
    m_writer.writeStartElement("Entry");    
    writeResourceCathegory(point.entryKeys(), "Key");
    writeResourceCathegory(point.entryPayment(), "Payment");
    writeResourceCathegory(point.entryAward(), "Earn");
    m_writer.writeEndElement();
}

/*! Добавляет ресурсы одной из категорий (ключи для входа в точку, плата за вход в точку, получить за вход в точку) */
void XmlStoryWriter::writeResourceCathegory(const QHash<QString, uint> & entry, const QString &name)
{
    foreach (QString key, entry.keys()) {
        m_writer.writeStartElement(name);
        m_writer.writeAttribute("Name", key);
        m_writer.writeAttribute("Count", QString::number(entry[key]));
        m_writer.writeEndElement();
    }
}

bool XmlStoryWriter::isFinished() const
{
    return m_isFinished;
}

/*! Должен быть вызван для завершения записи истории */
void XmlStoryWriter::finalise()
{
    if (m_isFinished)
        return;
    m_writer.writeEndElement();
    m_writer.writeEndDocument();

    m_isFinished = true;
}

bool XmlStoryWriter::isValid() const
{
    return m_isValid;
}
