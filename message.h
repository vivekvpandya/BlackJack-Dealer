#ifndef MESSAGE_H
#define MESSAGE_H
#include <vector>
#include <QDataStream>
#include "table.h"
#include "card.h"
#include "player.h"


enum class MessageType{
    GetTableDetails,
    TableDetails,
    GameDetails,
    JoinTable,
    LeaveTable,
    Message,
    ChekNickAvailability,
    NickAvailable,
    AddedToTable,
    TableOverFolw,
    NickRegistered,
    Hit,
    Fold,
    Card,
    GameOver
};

QDataStream & operator <<( QDataStream & stream, const MessageType &type);
QDataStream & operator >>(QDataStream & stream, MessageType & types);



class Message
{
public:
    Message();

    MessageType getMessageType() const;
    void setMessageType(const MessageType &mtype);
    Message(MessageType type);
    std::vector<QString> getDataStrings() const;
    void insertDataString(const QString &string);
    std::vector<Table> getTableDetails() const;
    void insertTable(Table table);
    std::vector<Card> getCards() const;
    void insertCard(Card card);
    void insertPlayer(Player player);
    std::vector<Player> getPlayers() const;
    void clearContainers();
    void printEmAll();

private:
    MessageType m_type;
    std::vector<QString> dataStrings;
    std::vector<Table> tables;
    std::vector<Card> cards;
    std::vector<Player> players;

};

QDataStream & operator <<( QDataStream & stream, const Message &message);
QDataStream & operator >>(QDataStream & stream, Message & message);
#endif // MESSAGE_H
