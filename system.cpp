#include "system.h"

#include <QFileDialog>
#include <QCoreApplication>

System::System()
{

}

System::~System()
{
    deleteSystem();
}

void System::deleteSystem(){
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
    //QJsonObject recordObject;
    QJsonArray recordObject;

    for (int i = 0; i < blocks.size(); i++){
        QJsonObject addressObjectBlock;
        addressObjectBlock.insert("ID block", i);
        addressObjectBlock.insert("Name block", blocks[i].getNameBlock());
        addressObjectBlock.insert("Count bus", blocks[i].getListBuses().size());
        QJsonArray phoneNumbersArray;
        for (int j = 0; j < blocks[i].getListBuses().size(); j++){
            QJsonObject objectBus;
            objectBus.insert("Name bus", blocks[i].getListBuses()[j].getNameBus());
            objectBus.insert("Address base", blocks[i].getListBuses()[j].getStartAddress());
            objectBus.insert("Address end", blocks[i].getListBuses()[j].getFinishAddress());
            objectBus.insert("Type bus", g_typeBus[blocks[i].getListBuses()[j].getTypeBus()]);
            objectBus.insert("Bitness", blocks[i].getListBuses()[j].getBitness());
            objectBus.insert("id bus", j);
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
            objectBus.insert("Connection", arrayConnection);
            phoneNumbersArray.push_back(objectBus);
        }
        addressObjectBlock.insert("Bus", phoneNumbersArray);
        recordObject.push_back(addressObjectBlock);
    }

    QString str = QFileDialog::getSaveFileName(nullptr, "Save File","untitled.json","(*.json)");
    QFile fileJson(str);
    fileJson.open(QIODevice::WriteOnly);
    fileJson.write(QJsonDocument(recordObject).toJson());
    fileJson.close();

    QMessageBox msgBox;
    msgBox.setText("Файл сохранен.");
    msgBox.exec();
}

void System::readFile(){
    deleteSystem();
    int heightDrawing = 20;
    int const step = 20;

    QString filePath = QFileDialog::getOpenFileName(nullptr, "Open file", "", "*.json");
    QFile fileJson(filePath);
    if (fileJson.open(QIODevice::ReadOnly)){
        qDebug()<<"open file";
    }else{
        QMessageBox msgBox;
        msgBox.setText("Ошибка открытия файла.");
        msgBox.exec();
        return;
    }
    QString strFile = fileJson.readAll();
    fileJson.close();

    QJsonParseError error;
    QJsonDocument doc = QJsonDocument::fromJson(strFile.toUtf8(), &error);
    qDebug() << "Error: " << error.errorString() << error.offset << error.error;

    QVector <IpBlock> blocks;
    if (doc.isArray()){
        QJsonArray arrayBlocks = doc.array();
        //qDebug()<<json.size();
        foreach (const QJsonValue & value, arrayBlocks) {
            if (value.isObject()) {
                QJsonObject objBlock = value.toObject();
                QString nameBlock = objBlock["Name block"].toString();
                int countBus = objBlock["Count bus"].toInt();
                Coordinate coordinateBlock;
                coordinateBlock.x = 0;
                coordinateBlock.y = heightDrawing;
                heightDrawing += step * countBus + step;

                QJsonArray arrayBus = objBlock["Bus"].toArray();
                //qDebug()<<"size bus = "<<arrayBus.size();
                QVector <Bus> listBus;
                foreach(const QJsonValue & tempBus, arrayBus){
                    QJsonObject objBus = tempBus.toObject();
                    QString nameBus = objBus["Name bus"].toString();
                    QString startAddress = objBus["Address base"].toString();
                    QString finishAddress = objBus["Address end"].toString();
                    int typeBus = setTypeBus(objBus["Type bus"].toString());
                    int bitness = objBus["Bitness"].toInt();
                    int id = objBus["id bus"].toInt();
                    Bus addingBus(nameBus, typeBus, bitness, id, startAddress, finishAddress);
                    listBus.push_back(addingBus);
                    qDebug()<<"-----------";
                    qDebug()<<nameBus;
                    qDebug()<<typeBus;
                    qDebug()<<bitness;
                    qDebug()<<id;
                    qDebug()<<startAddress;
                    qDebug()<<finishAddress;
                    qDebug()<<"-----------";
                    QJsonArray arrayConnectionInBus = objBlock["Connection"].toArray();
                    foreach (const QJsonValue & tempConnecton, arrayConnectionInBus){
                       QJsonObject objConnection = tempConnecton.toObject();
                       ConnectionBus addingConnection;
                       addingConnection.idBlock = objBus["ID Block"].toInt();
                       addingConnection.idBus = objBus["ID Bus"].toInt();
                       addingBus.addConnection(addingConnection);
                    }

                }
                IpBlock addingBlock(nameBlock, listBus, coordinateBlock);
                blocks.push_back(addingBlock);
            }
        }

    }
}

int System::setTypeBus(QString typeStr){
    for (int i = 0; i < g_typeBus->size(); i++){
        if (typeStr == g_typeBus[i]){
            return i;
        }
    }
}

