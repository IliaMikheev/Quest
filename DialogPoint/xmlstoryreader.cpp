#include "xmlstoryreader.h"


/*! Конструктор класса, для чтения xml-истории из файла */
XmlStoryReader::XmlStoryReader(QIODevice *device)
{
    m_reader.clear();
    m_reader.setDevice(device);
    m_isValid = startCheck();
}

/*! Конструктор класса, для чтения xml-истории из байтового массива */
XmlStoryReader::XmlStoryReader(const QByteArray &data)
{
    m_reader.clear();
    m_reader.addData(data);
    m_isValid = startCheck();
}

/*!
 * \brief StoryCreator::startCheck
 * Проверяет корректность заголовка Xml файла и переходит на
 * первый Point в xml файле
 *
 * Этот метод должен выполняться сразу после того, как в данный класс
 * будет загружено новое xml - описание истории, т.е. после каждого
 * m_reader.setDevice(src), m_reader.addData();
 * Результатом является
 * 1 - "прокрутка" ридера на первый дочерний элемент - первую точку в истории,
 * т.ч. следующий вызов m_reader.name() вернёт имя первого дочернего атрибута, а
 * m_reader.nextStartElement() вернёт передвинет ридер на второй дочерний элемент
 * первой точки, либо следующую точку
 * 2 - возвращает \return true, если получилосб, иначе false
 */
bool XmlStoryReader::startCheck()
{
    if (!m_reader.readNextStartElement())
        return false;
    if (m_reader.name() != "Story")
        return false;
    return true;
}

/*!
 * \brief StoryCreator::next
 * Сдвигается на одину точку (point) вперед по списку точек,
 * если это возможно и возвращает \return true, иначе \return false
 * позволяет внешнему коду "проходить" по списку точек, потобно тому
 * как это делает класс QSqlQuery с результатом sql-запроса.
 * В начале работы обработки
 **/
bool XmlStoryReader::next()
{

    if (!m_reader.readNextStartElement()){
        return false;
    }
    fillPointData();
    return true;
}

DialogPoint XmlStoryReader::point()
{
    return m_dialogPoint;
}

QString XmlStoryReader::name()
{
    return m_dialogPoint.name();
}

bool XmlStoryReader::isValid() const
{
    return m_isValid;
}

/*!
 * \brief StoryCreator::fillPointData
 * Метод нужен для заполнения данных текущей точки.*
 */
void XmlStoryReader::fillPointData() {
    m_dialogPoint = DialogPoint();

    while (m_reader.readNextStartElement()) {
        const QXmlStreamAttributes &attributes = m_reader.attributes();
        QStringRef name = m_reader.name();
        if (name == "Name")        {
            m_dialogPoint.setName(attributes.value("Text").toString());
        }
        else if (name == "Answer")      {
            m_dialogPoint.setAnswer(attributes.value("Text").toString());
        }
        else if (name == "Jump")        {
            m_dialogPoint.addJump(attributes.value("Name").toString());
        }
        else if (name == "Entry") {
            fillResourcesData();
        }
        else {
           m_reader.skipCurrentElement();
        }
        m_reader.readNext();
    }
}

/*! Заполняет данные о ресурсах в текущей точке.
 *  Вызывается только из fillPointData() в соответствующем месте.
 *  иначе состояние m_reader и m_dialogPoint не будет таким, как ожидается
*/
void XmlStoryReader::fillResourcesData()
{
    while (m_reader.readNextStartElement()) {
        const QXmlStreamAttributes &attributes = m_reader.attributes();
        QStringRef name = m_reader.name();
        bool ok;
        DialogPoint::Resource resource = getResource(name, &ok);

        if(ok) {
            QString attributeName = attributes.value("Name").toString();
            uint count = attributes.value("Count").toUInt();
            m_dialogPoint.addEntry(resource, attributeName, count);
        }
        else {
            m_reader.skipCurrentElement();
        }
        m_reader.readNext();
    }
}

/*! Возвращает тип ресурса согласно его имени, если имя соответствует
 *  хоть одному из типов ресурсов
*/
DialogPoint::Resource XmlStoryReader::getResource(QStringRef name, bool * ok) {
    DialogPoint::Resource resource;
    bool isOk = true;
    if (name == "Key") {
        resource = DialogPoint::Keys;
    }
    else if (name == "Award") {
        resource = DialogPoint::Award;
    }
    else if (name == "Payment") {
        resource = DialogPoint::Payment;
    }
    else {
        resource = DialogPoint::Keys;
        isOk = false;
    }
    *ok = isOk;
    return resource;
}
