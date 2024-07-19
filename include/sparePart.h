#ifndef SPAREPART_H
#define SPAREPART_H

#include "identifier.h"
#include "sparePartGroup.h"
#include <qvector.h>

class SparePart : public Identifier {
private:
    double mass;
    QString name;
    double price;
    SparePartGroup group;
    QVector<double> dimensions;
    static int id_counter;

public:
    SparePart() : mass(0.0) {}
    SparePart(const QString& name,double price, double mass, const QVector<double>& dims,SparePartGroup group );
    SparePart(const QString& name,double price, double mass, const QVector<double>& dims,SparePartGroup *group );
    double getMass() const;
    void setMass(double m);

    QString getName() const;
    void setName(QString name);

    double getPrice() const;
    void setPrice(double price);

    const QVector<double>& getDimensions() const;
    const QString getFormatedDimensions() const;
    void setDimensions(const QVector<double>& d);

    SparePartGroup getGroup() const;
    void setGroup(SparePartGroup g);

    void writeToXml(QXmlStreamWriter& writer) const override;
    void readFromXml(QXmlStreamReader& reader) override;

};

#endif // SPAREPART_H


