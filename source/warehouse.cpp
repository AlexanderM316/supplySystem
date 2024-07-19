#include "warehouse.h"
#include <iostream>

int Warehouse::id_counter = 1;

Warehouse::Warehouse(const QString name):Identifier(QString::number(id_counter++)), name(name){}
Warehouse::~Warehouse() {}

void Warehouse::addPart(const SparePartRecord& part) {
    spareParts.append(part);
}

void Warehouse::setSparePartRecord(const QVector<SparePartRecord>& spareParts) {
    this->spareParts = spareParts;
}

void Warehouse::listSpareParts() const {
        std::cout << "Warehouse: " << name.toStdString() << std::endl;
        for (const auto& part : spareParts) {
            QString db =  ", Name: " + part.sparePart.getName()
                      + ", Mass: " + part.sparePart.getMass()
                      + ", Quantity: " + part.qty
                      + ", Delivery Date: " + part.deliveryDate.toString() ;
                    QString dd = db;
        }

}
QVector<SparePartRecord> Warehouse::getSparePartRecord() const{
       return spareParts;
}

QString Warehouse::getName(){
    return name;
}
void Warehouse::setName(QString n){
    name = n;
}
void Warehouse::writeToXml(QXmlStreamWriter& writer) const {
    writer.writeStartElement("Warehouse");
        writer.writeAttribute("Identifier", getIdentifier());
        writer.writeTextElement("name", name);

        for (const auto& part : spareParts) {
            writer.writeStartElement("SparePartRecord");

            writer.writeTextElement("PartId", part.sparePart.getIdentifier());
            writer.writeTextElement("Name", part.sparePart.getName());
           // writer.writeTextElement("Mass", QString::number(part.sparePart.getMass()));
           // writer.writeTextElement("Lenght", QString::number(part.sparePart.getDimensions()[0]));
           // writer.writeTextElement("Width", QString::number(part.sparePart.getDimensions()[1]));
           // writer.writeTextElement("Hight", QString::number(part.sparePart.getDimensions()[2]));
            writer.writeTextElement("Quantity", QString::number(part.qty));
            writer.writeTextElement("DeliveryDate", part.deliveryDate.toString(Qt::ISODate));

            writer.writeEndElement(); // SparePartRecord
        }

        writer.writeEndElement(); // Warehouse
}

void Warehouse::readFromXml(QXmlStreamReader& reader) {
}
