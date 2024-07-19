#ifndef PRODUCT_H
#define PRODUCT_H

#include "identifier.h"
#include "sparePartRecord.h"


class Product : public Identifier {
private:
    QString name;
    QVector<SparePartRecord> spareParts;
    static int id_counter;

public:
    Product(const QString& name);

    ~Product();

    QString getName() const;
    void setName(const QString& value);

    void addPart(const SparePartRecord& part);
    QVector<SparePartRecord> getSparePartRecord() const;
    void setSparePartRecord(const QVector<SparePartRecord>& spareParts);

    // Метод для записи данных в XML
   void writeToXml(QXmlStreamWriter& writer) const;

    // Метод для чтения данных из XML
   void readFromXml(QXmlStreamReader& reader);
};
#endif // PRODUCT_H
