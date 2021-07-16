#include "system.h"

System::System()
{

}

System::~System()
{
    blocks.clear();
    coordinateConnection.clear();
    connection.clear();
}

void System::WrittingToFile(){
    QJsonObject recordObject;

    for (int i = 0; i < blocks.size(); i++){
        QJsonObject addressObjectBlock;
        addressObjectBlock.insert("Name block", blocks[i].getNameBlock());
        addressObjectBlock.insert("Count bus", blocks[i].getListBuses().size());
        QJsonArray phoneNumbersArray;
        for (int j = 0; j < blocks[i].getListBuses().size(); j++){
            QJsonObject addressObjectBus;
            addressObjectBus.insert("Name bus", blocks[i].getListBuses()[j].getNameBus());
            addressObjectBus.insert("Type bus", g_typeBus[blocks[i].getListBuses()[j].getTypeBus()]);
            addressObjectBus.insert("Bitness", blocks[i].getListBuses()[j].getBitness());
            addressObjectBus.insert("id bus", j);
            QJsonArray arrayConnection;
            for (Connection temp: connection){
                if (temp.connectionBusStart.idBus == j && temp.connectionBusStart.idBlock == i && temp.mark == 1){
                    QJsonObject connectObject;
                    connectObject.insert("ID Block", temp.connectionBusFinish.idBlock);
                    connectObject.insert("ID Bus", temp.connectionBusFinish.idBus);
                    arrayConnection.push_back(connectObject);
                }
            }
            for (Connection temp: connection){
                if (temp.connectionBusFinish.idBus == j && temp.connectionBusFinish.idBlock == i && temp.mark == 1){
                    QJsonObject connectObject;
                    connectObject.insert("ID Block", temp.connectionBusStart.idBlock);
                    connectObject.insert("ID Bus", temp.connectionBusStart.idBus);
                    arrayConnection.push_back(connectObject);
                }
            }
            addressObjectBus.insert("Connection", arrayConnection);
            phoneNumbersArray.push_back(addressObjectBus);
        }
        addressObjectBlock.insert("Bus", phoneNumbersArray);
        recordObject.insert(QString::number(i), addressObjectBlock);
    }


    QFile fileJson("C:/Users/User/Desktop/FrontEndSystemsEngineering/first.json");
    fileJson.open(QIODevice::WriteOnly);
    QVariantMap testMap;
    fileJson.write(QJsonDocument(recordObject).toJson());
    fileJson.close();

    QMessageBox msgBox;
    msgBox.setText("Файл сохранен.");
    msgBox.exec();
}

