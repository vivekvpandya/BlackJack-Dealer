#include "message.h"
#include "table.h"
#include "card.h"
#include <QDebug>

Message::Message()
{

}

Message::Message(MessageType type){

    m_type = type;
    dataStrings.clear();
    tables.clear();
    cards.clear();
    players.clear();
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

void Message::insertPlayer(Player player)
{
    players.push_back(player);
}

std::vector<Player> Message::getPlayers() const
{
    return players;
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

    std::vector<Player> playersVector = message.getPlayers();
    int numberOfPlayers = playersVector.size();

    stream << numberOfPlayers;

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

    for(Player player : playersVector)
    {
        stream << player;
    }
    return stream;
}

QDataStream &  operator >>(QDataStream & stream, Message &message){
    MessageType mtype;
    QString stringObj;
    Table tableObj;
    Player playerObj;
    Card cardObj = Card();
    int dataStringsSize;
    int numberOfTables;
    int numberOfCards;
    int numberOfPlayers;
    stream >> mtype;

    stream >> dataStringsSize;

    stream >> numberOfTables;

    stream >> numberOfCards;
    stream >> numberOfPlayers;

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
    for(int j = 0; j < numberOfPlayers; j++ )
    {
        stream >> playerObj;
        message.insertPlayer(playerObj);
    }

    return stream;
}

void Message::clearContainers()
{
    dataStrings.clear();
    tables.clear();
    cards.clear();
    players.clear();
}


void Message::printEmAll()
{
    qDebug() << "MessageType : " <<(int)m_type;
    for(QString dataString: dataStrings)
    {
        qDebug() << "DataString : "<<dataString;
    }
    for(Card card : cards)
    {
        qDebug() << "Card : " <<card.getValue() << " " << card.getSuit();
    }
    for(Player player : players)
    {
        qDebug() << "Player : "<<player.getName();
        qDebug() << "Player isFold : "<<player.isFold();
        qDebug() << "Player cards : ";
        for(Card card : player.getCardHand())
        {
            qDebug() << " \t Card : "<<card.getRank() << " " << card.getSuit();
        }
    }
}
