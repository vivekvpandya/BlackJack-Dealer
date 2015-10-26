#include "message.h"

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
std::vector<Peer> Message::getPeerVector() const{
    return peerVector;
}

void Message::insertDataString(const QString &string){

    dataStrings.push_back(string);
}

void Message::insertPeerObj(const Peer &peer){

    peerVector.push_back(peer);
}

std::vector<Table> Message::getTableVector() const{
    return tableVector;
}
void Message::insertTableObj(const Table &table){
    tableVector.push_back(table);
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
    std::vector<Peer> peerObjects = message.getPeerVector();
    int peerVectorSize = peerObjects.size();
    stream << peerVectorSize;
    std::vector<Table> tableVector = message.getTableVector();
    int tableVectorSize = tableVector.size();
    stream << tableVectorSize;
    for( QString obj : dataStrings ){
        
        stream << obj;
    }

    for(Peer peer :  peerObjects){
        stream<<peer;

    }
    for(Table table: tableVector){
        stream << table;
    }
    return stream;
}

QDataStream &  operator >>(QDataStream & stream, Message &message){
    MessageType mtype;
    QString stringObj;
    Peer peerObj;
    Table tableObj;
    int dataStringsSize;
    int peerVectorSize;
    int tableVectorSize;

    stream >> mtype;
    stream >> dataStringsSize;
    stream >> peerVectorSize;
    stream >> tableVectorSize;
    message.setMessageType(mtype);

    for(int i=0;i<dataStringsSize;i++){
        stream>>stringObj;
        message.insertDataString(stringObj);
    }
    for(int i=0;i<peerVectorSize; i++){
        stream>>peerObj;
        message.insertPeerObj(peerObj);
    }
    for(int i=0;i<tableVectorSize; i++){
        stream >> tableObj;
        message.insertTableObj(tableObj);
    }
    return stream;
}

