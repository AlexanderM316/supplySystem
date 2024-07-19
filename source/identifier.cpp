#include "identifier.h"

Identifier::Identifier(const QString& id)
    : Id(id) {}

Identifier::~Identifier() {
    // Деструктор
}
// Геттеры и сеттеры
QString Identifier::getIdentifier() const {
    return Id;
}

void Identifier::setIdentifier(const QString& id) {
    Id = id;
}

QString Identifier::getName() const {
    return name;
}

void Identifier::setName(const QString& name) {
    this->name = name;
}
