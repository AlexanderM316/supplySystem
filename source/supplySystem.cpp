// SupplySystem.cpp
#include "supplySystem.h"
#include "warehouse.h"
#include "product.h"

void SupplySystem::addWarehouse(const Warehouse& warehouse) {
    warehouses.append(warehouse);
}

void SupplySystem::removeWarehouse(const QString& warehouseId) {
    // Удаление склада по идентификатору
}

Warehouse* SupplySystem::findWarehouse(const QString& warehouseId) {
    // Поиск и возврат указателя на склад
}

void SupplySystem::addProduct(const Product& product) {
    //products.append(product);
}

void SupplySystem::removeProduct(const QString& productId) {
    // Удаление продукта по идентификатору
}

Product* SupplySystem::findProduct(const QString& productId) {
    // Поиск и возврат указателя на продукт
}

void SupplySystem::writeToXml(QXmlStreamWriter& writer) const {
    writer.writeStartElement("SupplySystem");

        writer.writeStartElement("Warehouses");
        for (const auto& warehouse : warehouses) {
            warehouse.writeToXml(writer);
        }
        writer.writeEndElement(); // Warehouses

        writer.writeStartElement("ServicedProducts");
        for (const auto& product : servicedProducts) {
            product.writeToXml(writer);
        }
        writer.writeEndElement(); // ServicedProducts

        writer.writeEndElement(); // SupplySystem
}

void SupplySystem::readFromXml(QXmlStreamReader& reader) {
}
