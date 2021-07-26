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
    tempConnection.clear();
    heightDrawingReadFile = 0;
    heightBlockForDrawing = startHeightBlockForDrawing;
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
    int const step = 20;
    heightBlockForDrawing += step * addingBlock.getSizeBus() + step;
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
    QJsonArray recordObject;

    for (int i = 0; i < blocks.size(); i++){
        QJsonObject objectBlock;
        objectBlock.insert("ID block", i);
        objectBlock.insert("Name block", blocks[i].getNameBlock());
        objectBlock.insert("Count bus", blocks[i].getListBuses().size());
        QJsonArray arrayListBus;
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
            objectBus.insert("Connection", arrayConnection);
            arrayListBus.push_back(objectBus);
        }
        objectBlock.insert("Bus", arrayListBus);
        recordObject.push_back(objectBlock);
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
    int heightDrawing = startHeightBlockForDrawing;
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

    if (doc.isArray()){
        QJsonArray arrayBlocks = doc.array();
        foreach (const QJsonValue & value, arrayBlocks) {
            if (value.isObject()) {
                QJsonObject objBlock = value.toObject();
                QString nameBlock = objBlock["Name block"].toString();
                int IdBlock = objBlock["ID block"].toInt();
                int countBus = objBlock["Count bus"].toInt();
                Coordinate coordinateBlock;
                coordinateBlock.x = 0;
                coordinateBlock.y = heightDrawing;
                heightDrawing += step * countBus + step;

                QJsonArray arrayBus = objBlock["Bus"].toArray();
                QVector <Bus> listBus;
                foreach(const QJsonValue & tempBus, arrayBus){
                    QJsonObject objBus = tempBus.toObject();
                    QString nameBus = objBus["Name bus"].toString();
                    QString startAddress = objBus["Address base"].toString();
                    QString finishAddress = objBus["Address end"].toString();
                    int typeBus = setTypeBus(objBus["Type bus"].toString());
                    int bitness = objBus["Bitness"].toInt();
                    int id = objBus["id bus"].toInt();
                    ConnectionBus startBus;
                    startBus.idBus = id;
                    startBus.idBlock = IdBlock;
                    Bus addingBus(nameBus, typeBus, bitness, id, startAddress, finishAddress);
                    QJsonArray arrayConnectionInBus = objBus["Connection"].toArray();
                    foreach (const QJsonValue & tempConnecton, arrayConnectionInBus){
                       QJsonObject objConnection = tempConnecton.toObject();
                       ConnectionBus finishBus;
                       finishBus.idBlock = objConnection["ID Block"].toInt();
                       finishBus.idBus = objConnection["ID Bus"].toInt();
                       Connection addingTempConnect;
                       addingTempConnect.connectionBusStart = startBus;
                       addingTempConnect.connectionBusFinish = finishBus;
                       this->tempConnection.push_back(addingTempConnect);
                    }

                    int sizeBlock = blocks.size();
                    if (sizeBlock > 0){
                        for (int i = 0; i < sizeBlock; i++){
                            int sizeListBus = blocks[i].getSizeBus();
                            for (int j = 0; j < sizeListBus; j++){
                                if (ruleCheckConnection(i, j, typeBus, bitness)){
                                    ConnectionBus tempConnection;
                                    tempConnection.idBus = j;
                                    tempConnection.idBlock = i;
                                    addingBus.addConnection(tempConnection);
                                }
                            }
                        }
                    }


                    listBus.push_back(addingBus);

                }
                IpBlock addingBlock(nameBlock, listBus, coordinateBlock);
                blocks.push_back(addingBlock);
            }
        }

    }
    heightDrawingReadFile = heightDrawing;

    return;
}

int System::getHeightBlockForDrawing(){
    return heightBlockForDrawing;
}

void System::updateHeightBlockForDrawing(){
    try
    {
        if (tempConnection.size() == 0){
            throw "You cannot use System::getHeightDrawingReadFile function";
        }
        heightBlockForDrawing = heightDrawingReadFile;
    }
    catch (const char* exception)
    {
        std::cerr << "Error: " << exception << '\n';
    }

}

void System::markToFile(){
    if (tempConnection.size() == 0){
        return;
    }
    for (int i = 0; i < connection.size(); i++){
        for (int j = 0; j < tempConnection.size(); j++){
            if (connection[i].connectionBusStart.idBus == tempConnection[j].connectionBusStart.idBus &&
                connection[i].connectionBusStart.idBlock == tempConnection[j].connectionBusStart.idBlock &&
                connection[i].connectionBusFinish.idBus == tempConnection[j].connectionBusFinish.idBus &&
                connection[i].connectionBusFinish.idBlock == tempConnection[j].connectionBusFinish.idBlock){

                connection[i].mark = true;
            }

        }
    }
}

void System::outputSystem(){
    for (int i = 0; i < blocks.size(); i++){
        qDebug()<<"Block "<<i;
        qDebug()<<"Name block"<<blocks[i].getNameBlock();
        qDebug()<<"Count bus"<<blocks[i].getSizeBus();
        qDebug()<<"Bus:";
        for (int j = 0; j < blocks[i].getSizeBus(); j++){
            qDebug()<<" [";
            qDebug()<<"     ID bus"<<blocks[i].getBusOnIndex(j).getId();
            qDebug()<<"     Name bus"<<blocks[i].getBusOnIndex(j).getNameBus();
            qDebug()<<"     Connection:";
            qDebug()<<"         [";
            for (int k = 0; k < blocks[i].getSizeConnectionInBus(j); k++){
                qDebug()<<"         ID con"<<k;
                qDebug()<<"          ID Block"<<blocks[i].getBusOnIndex(j).getConnectionOnIndex(k).idBlock;
                qDebug()<<"          ID Bus"<<blocks[i].getBusOnIndex(j).getConnectionOnIndex(k).idBus;
            }
            qDebug()<<"         ]";
            qDebug()<<" ]";
        }
    }
}

int System::setTypeBus(QString typeStr){
    for (int i = 0; i < g_typeBus->size(); i++){
        if (typeStr == g_typeBus[i]){
            return i;
        }
    }
    return -1;
}

QVector <ConnectionBus> System::installAllConnection(int indexTypeAddingBus, int bitnessAddingBus){
    QVector <ConnectionBus> connect;

    int sizeBlock = getSizeBlocks();
    if (sizeBlock > 0){
        for (int i = 0; i < sizeBlock; i++){
            int sizeListBus = getSizeBusInBlock(i);
            for (int j = 0; j < sizeListBus; j++){
                if (ruleCheckConnection(i, j, indexTypeAddingBus, bitnessAddingBus)){
                    ConnectionBus connection;
                    connection.idBus = j;
                    connection.idBlock = i;
                    connect.push_back(connection);
                }
            }
        }
    }
    return connect;
}

