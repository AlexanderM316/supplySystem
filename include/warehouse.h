#ifndef WAREHOUSE_H
#define WAREHOUSE_H

#include <QDate>
#include "identifier.h"
#include "sparePartRecord.h"

class Warehouse : public Identifier {
private:
    QString identifier;
    QString name;
    QVector<SparePartRecord> spareParts;
    static int id_counter;

public:
    Warehouse(const QString name);
    ~Warehouse();
    void addPart(const SparePartRecord& part);
    QVector<SparePartRecord> getSparePartRecord() const;
    void setSparePartRecord(const QVector<SparePartRecord>& spareParts);
    int getSparePartQty(const QString& partId);
    void listSpareParts() const;
    QString getName();
    void setName(QString n);
    void writeToXml(QXmlStreamWriter& writer) const override;
    void readFromXml(QXmlStreamReader& reader) override;
};
#endif // WAREHOUSE_H
