#ifndef SPAREPARTRECORD_H
#define SPAREPARTRECORD_H
#include <QDate>
#include "sparePart.h"

struct SparePartRecord{
    SparePart sparePart;
    int qty;
    QDate deliveryDate;
public:
    SparePartRecord() {}
    SparePartRecord(const SparePart& sparePart, int qty, const QDate& deliveryDate)
        : sparePart(sparePart), qty(qty), deliveryDate(deliveryDate) {}
    SparePartRecord(const SparePart* sparePart, int qty, const QDate& deliveryDate)
        : sparePart(*sparePart), qty(qty), deliveryDate(deliveryDate) {};
    void writeToXml(QXmlStreamWriter& writer) const {
           writer.writeTextElement("PartName", sparePart.getName());
           writer.writeTextElement("Quantity", QString::number(qty));
           writer.writeTextElement("DeliveryDate", deliveryDate.toString("dd.MM.yyyy"));
    };
};
#endif // SPAREPARTRECORD_H
