#include "system.h"

System::System()
{

}

System::~System()
{

}

void System::WrittingToFile(){
    QJsonObject recordObject;

    for (int i = 0; i < Blocks.size(); i++){
        QJsonObject addressObjectBlock;
        addressObjectBlock.insert("Name block", Blocks[i].NameBlock);
        addressObjectBlock.insert("Count bus", Blocks[i].ListShines.size());
        QJsonArray phoneNumbersArray;
        for (int j = 0; j < Blocks[i].ListShines.size(); j++){
            QJsonObject addressObjectBus;
            addressObjectBus.insert("Name bus", Blocks[i].ListShines[j].NameShine);
            addressObjectBus.insert("Type bus", Blocks[i].ListShines[j].TypeShine);
            addressObjectBus.insert("Bitness", Blocks[i].ListShines[j].Bitness);
            addressObjectBus.insert("id bus", j);
            QJsonArray arrayConnection;
            for (Connection temp: connection){
                if (temp.connectionBusStart.IdBus == j && temp.connectionBusStart.IdBlock == i && temp.mark == 1){
                    QJsonObject connectObject;
                    connectObject.insert("ID Block", temp.connectionBusFinish.IdBlock);
                    connectObject.insert("ID Bus", temp.connectionBusFinish.IdBus);
                    arrayConnection.push_back(connectObject);
                }
            }
            for (Connection temp: connection){
                if (temp.connectionBusFinish.IdBus == j && temp.connectionBusFinish.IdBlock == i && temp.mark == 1){
                    QJsonObject connectObject;
                    connectObject.insert("ID Block", temp.connectionBusStart.IdBlock);
                    connectObject.insert("ID Bus", temp.connectionBusStart.IdBus);
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

//void System::FindConnectoun(){

//}
