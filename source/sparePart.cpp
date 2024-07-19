#include "identifier.h"
#include "sparePart.h"

int SparePart::id_counter = 1;

SparePart::SparePart(const QString& name,double price, double mass, const QVector<double>& dims,SparePartGroup group )
    : Identifier(QString::number(id_counter++)), name(name),price(price), mass(mass), dimensions(dims), group(group) {}

SparePart::SparePart(const QString& name,double price, double mass, const QVector<double>& dims,SparePartGroup *group )
    : Identifier(QString::number(id_counter++)), name(name),price(price), mass(mass), dimensions(dims), group(*group) {}

void SparePart::writeToXml(QXmlStreamWriter& writer) const {
    writer.writeStartElement("SparePart");
       writer.writeAttribute("Identifier", getIdentifier());
       writer.writeTextElement("Name", name);
       writer.writeTextElement("Price", QString::number(price));
       writer.writeTextElement("Mass", QString::number(mass));
       writer.writeTextElement("Dimensions", getFormatedDimensions());
       writer.writeTextElement("Group", group.getName());
       writer.writeEndElement(); // SparePart
}

void SparePart::readFromXml(QXmlStreamReader& reader) {
    // Реализация чтения из XML
}
double SparePart::getMass() const {

    return mass;
}
void SparePart::setMass(double m) {

    mass = m;
}
double SparePart::getPrice() const{

    return price;
}
void SparePart::setPrice(double p){

    price = p;
}
QString SparePart::getName() const{

    return name;
}
void SparePart::setName(QString _name){

    name = _name;
}

const QVector<double>& SparePart::getDimensions() const {

    return dimensions;
}

const QString SparePart::getFormatedDimensions() const{

    return QString::number(dimensions.at(0)) + " x " + QString::number(dimensions.at(1)) + " x " + QString::number(dimensions.at(2));
}
void SparePart::setDimensions(const QVector<double>& d) {

    dimensions = d;
}
SparePartGroup SparePart::getGroup() const{

    return group;
}
void SparePart::setGroup(SparePartGroup g){

    group = g;
}
