#include "product.h"
#include "identifier.h"

int Product::id_counter = 1;

Product::Product( const QString& name)
    : Identifier(QString::number(id_counter++)), name(name) {}

Product::~Product() {}

QString Product::getName() const {
    return name;
}

void Product::setName(const QString& value) {
    name = value;
}
void Product::addPart(const SparePartRecord& part){
    spareParts.append(part);
}

void Product::setSparePartRecord(const QVector<SparePartRecord>& spareParts) {
    this->spareParts = spareParts;
}
QVector<SparePartRecord> Product::getSparePartRecord() const{
    return spareParts;
}
void Product::writeToXml(QXmlStreamWriter& writer) const {
        writer.writeStartElement("Product");
        writer.writeAttribute("Identifier",getIdentifier());
        writer.writeTextElement("Name", name);
        writer.writeStartElement("SpareParts");

        for (const SparePartRecord& part : spareParts) {
            writer.writeStartElement("SparePartRecord");
            part.writeToXml(writer);
            writer.writeEndElement(); // SparePartRecord
        }

        writer.writeEndElement(); // SpareParts
        writer.writeEndElement(); // Product
}

void Product::readFromXml(QXmlStreamReader& reader) {

}
