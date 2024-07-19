#ifndef IDENTIFIER_H
#define IDENTIFIER_H

#include <QString>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>

class Identifier {
protected:
    QString Id;
    QString name;

public:
    Identifier(const QString& id);
    Identifier() {}
    virtual ~Identifier();

    // Виртуальные методы для сериализации и десериализации
    virtual void writeToXml(QXmlStreamWriter& writer) const = 0;
    virtual void readFromXml(QXmlStreamReader& reader) = 0;

     // Геттеры и сеттеры
    QString getIdentifier() const;
    void setIdentifier(const QString& id);

    QString getName() const;
    void setName(const QString& name);
};
#endif // IDENTIFIER_H


