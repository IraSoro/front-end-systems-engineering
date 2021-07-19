#include "system.h"

#include <QFileDialog>
#include <QCoreApplication>

System::System()
{

}

System::~System()
{
    blocks.clear();
    connection.clear();
}

int System::getSizeBlocks(){
    return blocks.size();
}

int System::getSizeConnections(){
    return connection.size();
}

int System::getSizeBusInBlock(int indexBlock){
   return blocks[indexBlock].getSizeBus();
}

IpBlock System::getBlock(int index){
    return blocks[index];
}

IpBlock System::getLastBlock(){
    return blocks.last();
}

bool System::getMarkConnection(int indexConnection){
    return connection[indexConnection].mark;
}

int System::getXCoordinate(int indexConnection){
    return connection[indexConnection].coordinates.x;
}

int System::getYCoordinate(int indexConnection){
    return connection[indexConnection].coordinates.y;
}

Connection System::getConnection(int index){
    return connection[index];
}

void System::addBlock(IpBlock addingBlock){
    blocks.push_back(addingBlock);
}

void System::addConnection(Connection addingConnection){
    connection.push_back(addingConnection);
}

void System::setMarkConnection(int index, bool settingMark){
    connection[index].mark = settingMark;
}

int System::getTypeBus(int idBlock, int idBus){
    return blocks[idBlock].getTypeBusOnIndex(idBus);
}

int System::getBitnessBus(int idBlock, int idBus){
    return blocks[idBlock].getBitnessBusOnIndex(idBus);
}

bool System::ruleCheckConnection(int idBlockFirst, int idBusFirst, int typeSecondBus, int bitnessSecondBus){
    if (g_busMapping[getTypeBus(idBlockFirst, idBusFirst)][typeSecondBus] == true){
        return true;
    }else if (bitnessSecondBus == getBitnessBus(idBlockFirst, idBusFirst)){
              return true;
          }else{
              return false;
          }
}

void System::writtingToFile(){
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

    QString str3 = QFileDialog::getSaveFileName(nullptr, "Save File","untitled.json","(*.json)");
    QFile fileJson(str3);
    fileJson.open(QIODevice::WriteOnly);
    fileJson.write(QJsonDocument(recordObject).toJson());
    fileJson.close();

    QMessageBox msgBox;
    msgBox.setText("Файл сохранен.");
    msgBox.exec();
}

