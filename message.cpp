#include "message.h"
#include "table.h"
#include "card.h"
#include <QDebug>

Message::Message()
{

}

Message::Message(MessageType type){

    m_type = type;
}

void Message::setMessageType(const MessageType &mtype){
    m_type = mtype;
}

MessageType Message::getMessageType() const {
    return m_type;
}

std::vector<QString> Message::getDataStrings() const{
    return dataStrings;
}

void Message::insertDataString(const QString &string){

    dataStrings.push_back(string);
}

std::vector<Table> Message::getTableDetails() const{
    return tables;
}

void Message::insertTable(Table table){
    tables.push_back(table);
}

std::vector<Card> Message::getCards() const{
    return cards;
}

void Message::insertCard(Card card){
    cards.push_back(card);
}

QDataStream & operator <<( QDataStream & stream, const MessageType &type){

    return stream <<(int) type;
}
QDataStream & operator >>(QDataStream & stream, MessageType & type){

    int enumVal;
    stream >> enumVal;
    type = MessageType(enumVal);
    return stream;
}

QDataStream & operator <<(QDataStream & stream, const Message &message){

    stream << message.getMessageType();
    std::vector<QString> dataStrings = message.getDataStrings();
    int dataStringsSize = dataStrings.size();
    stream << dataStringsSize;
    std::vector<Table> tables = message.getTableDetails();
    int numberoOftables = tables.size();
    stream << numberoOftables;
    std::vector<Card> cards = message.getCards();
    int numberOfCards = cards.size();
    stream << numberOfCards;
    for(QString str : dataStrings)
    {
        stream << str;
    }
    for(Table table: tables)
     {
                  stream << table;
    }
    for(Card card: cards)
        {
                  stream << card;
    }
    return stream;
}

QDataStream &  operator >>(QDataStream & stream, Message &message){
    MessageType mtype;
    QString stringObj;
    Table tableObj;
    Card cardObj = Card();
    int dataStringsSize;
    int numberOfTables;
    int numberOfCards;
    stream >> mtype;
    stream >> dataStringsSize;
    stream >> numberOfTables;
    stream >> numberOfCards;
    message.setMessageType(mtype);
    for(int i=0;i<dataStringsSize;i++)
    {
        stream>>stringObj;
        message.insertDataString(stringObj);
    }
    for(int i=0; i<numberOfTables; i++)
    {
        stream >> tableObj;
        message.insertTable(tableObj);
    }
    for(int i=0; i<numberOfCards; i++)
    {
        stream >> cardObj;
        message.insertCard(cardObj);
    }
    return stream;
}

