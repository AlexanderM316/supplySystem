#ifndef SUPPLYSYSTEM_H
#define SUPPLYSYSTEM_H

#include "identifier.h"
#include "warehouse.h"
#include "product.h"
#include "sparePart.h"

class SupplySystem : public Identifier {
private:
    QList<Warehouse> warehouses;
    QList<Product> servicedProducts;

public:
    SupplySystem(const QString& id)
        : Identifier(id){}//, warehouses(whs), servicedProducts(prods) {}
    void addWarehouse(const Warehouse& warehouse);
    void removeWarehouse(const QString& warehouseId);
    Warehouse* findWarehouse(const QString& warehouseId);

    void addProduct(const Product& product);
    void removeProduct(const QString& productId);
    Product* findProduct(const QString& productId);

    // Методы для сериализации и десериализации
    void writeToXml(QXmlStreamWriter& writer) const;
    void readFromXml(QXmlStreamReader& reader);
};
#endif // SUPPLYSYSTEM_H
