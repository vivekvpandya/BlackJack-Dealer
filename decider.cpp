#include "decider.h"
#include <QHash>
#include "player.h"
#include <QDebug>
Decider::Decider(QObject *parent) : QObject(parent)
{

}

std::vector<QString> Decider::gameDecider(Table *table){
    std::vector<QString> winners;
    std::vector<Card> temp;
    QHash<QString,int> values;
    for(std::list< Player >::iterator it=table->playerListBegin();it!=table->playerListEnd();it++){
        temp = ((*it).getCardHand());
        Player player = *it;
        int value=0;
        for(std::vector<Card>::iterator itcard=temp.begin();itcard!=temp.end();itcard++){
            value+=(*itcard).getValue();
        }
           values.insert(player.getName(),value);
    }
    int ans=0,index=0;
    foreach(QString playerName, values.keys()){
        if(values[playerName]<=21 && values[playerName]>ans){
            ans=values[playerName];
        }
    }
    foreach(QString playerName, values.keys()){
       int sum  = values[playerName];
       if(sum  == ans)
       {    qDebug() << playerName << "winner";
           winners.push_back(playerName);
       }
    }

    return winners;
}
