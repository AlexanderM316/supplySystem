#include "sparePartGroup.h"

int SparePartGroup::id_counter =1;

SparePartGroup::SparePartGroup(const QString& name)
    : Identifier(QString::number(id_counter++)), name(name) {}
    // Метод для записи данных в XML
void SparePartGroup::writeToXml(QXmlStreamWriter& writer) const {
        writer.writeStartElement("SparePartGroup");
        writer.writeAttribute("Identifier", getIdentifier());
        writer.writeTextElement("Name", name);
        writer.writeEndElement(); // SparePartGroup
}

    // Метод для чтения данных из XML
void SparePartGroup::readFromXml(QXmlStreamReader& reader) {

}

    // Геттеры и сеттеры
QString SparePartGroup::getName() const {

    return name;
}
void SparePartGroup::setName(const QString& name) {

    this->name = name;
}
