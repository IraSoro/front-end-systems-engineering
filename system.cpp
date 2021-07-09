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
            phoneNumbersArray.push_back(addressObjectBus);
            //addressObjectBlock.insert(QString::number(j), addressObjectBus);
        }
        addressObjectBlock.insert("Bus", phoneNumbersArray);
        recordObject.insert(QString::number(i), addressObjectBlock);
    }

//    recordObject.insert("FirstName", QJsonValue::fromVariant("John"));
//    recordObject.insert("LastName", QJsonValue::fromVariant("Doe"));
//    recordObject.insert("Age", QJsonValue::fromVariant(43));

//    QJsonObject addressObject;
//    addressObject.insert("Street", "Downing Street 10");
//    addressObject.insert("City", "London");
//    addressObject.insert("Country", "Great Britain");
//    recordObject.insert("Address", addressObject);

//    QJsonArray phoneNumbersArray;
//    phoneNumbersArray.push_back("+44 1234567");
//    phoneNumbersArray.push_back("+44 2345678");
//    recordObject.insert("Phone Numbers", phoneNumbersArray);


    QFile fileJson("C:/Users/User/Desktop/FrontEndSystemsEngineering/first.json");
    fileJson.open(QIODevice::WriteOnly);
    QVariantMap testMap;
    fileJson.write(QJsonDocument(recordObject).toJson());
    fileJson.close();

    QMessageBox msgBox;
    msgBox.setText("Файл сохранен.");
    msgBox.exec();
}
