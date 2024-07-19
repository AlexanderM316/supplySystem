#ifndef SPAREPARTGROUP_H
#define SPAREPARTGROUP_H
#include <QString>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include "identifier.h"

class SparePartGroup : public Identifier {

    QString name;
    static int id_counter;

public:
    // Конструктор по умолчанию
    SparePartGroup() {}
    // Конструктор
    SparePartGroup(const QString& name);

    // Метод для записи данных в XML
    void writeToXml(QXmlStreamWriter& writer) const;

    // Метод для чтения данных из XML
    void readFromXml(QXmlStreamReader& reader);

    // Геттеры и сеттеры

    QString getName() const;
    void setName(const QString& name);

};
#endif // SPAREPARTGROUP_H
