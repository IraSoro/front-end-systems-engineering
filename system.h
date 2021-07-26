#ifndef SYSTEM_H
#define SYSTEM_H

#include "iostream"

#include <QVector>
#include <QDebug>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QFile>
#include <QMessageBox>

#include "ipblock.h"


struct Connection{
    Coordinate coordinates;
    ConnectionBus connectionBusStart;
    ConnectionBus connectionBusFinish;
    bool mark = 0;
};

class System
{
public:
    System();
    ~System();
    /*!
     * \brief записывает систему в json-файл и сохраняет файл
     */
    void writtingToFile();

    /*!
     * \brief возвращает количество блоков в системе
     * \return целое число - количество блоков в системе
     */
    int getSizeBlocks();

    /*!
     * \brief возвращает количество связей в системе
     * \return целое число - количество связей в системе
     */
    int getSizeConnections();

    /*!
     * \brief возвращает количество шин в одном блоке
     * \param indexBlock - индекс блока
     * \return целое число - количество шин в блоке
     */
    int getSizeBusInBlock(int indexBlock);

    /*!
     * \brief добавление блока в систему
     * \param addingBlock элемент типа IpBlock
     */
    void addBlock(IpBlock addingBlock);

    /*!
     * \brief добавление связи в систему
     * \param addingBlock элемент типа Connection
     */
    void addConnection(Connection addingConnection);

    /*!
     * \brief устанавливает метку связи: связана или разъединена
     * \param index индекс связи
     * \param settingMark true или false - в зависимости от того, сделать ли связь помеченной или нет
     */
    void setMarkConnection(int index, bool settingMark);

    /*!
     * \brief возврат блока системы по индексу
     * \param индекс блока
     * \return элемент типа IpBlock
     */
    IpBlock getBlock(int index);

    /*!
     * \brief возврат связи по индексу
     * \param index индекс связи
     * \return возврат элемента типа Connection
     */
    Connection getConnection(int index);

    /*!
     * \brief получение информации о том, отмечена ли связь
     * \param индекс связи
     * \return true - если помечена, false - если нет
     */
    bool getMarkConnection(int indexConnection);

    /*!
     * \brief получение x-координаты выбранного соединения
     * \param indexConnection индекст связи
     * \return целое число - x-координата
     */
    int getXCoordinate(int indexConnection);

    /*!
     * \brief получение y-координаты выбранного соединения
     * \param indexConnection индекст связи
     * \return целое число - y-координата
     */
    int getYCoordinate(int indexConnection);

    /*!
     * \brief проверка, по правилам которым определяется, могут ли быть соединены шины
     * \param idBlockFirst индекс блока предполагаемого элемента
     * \param idBusFirst индекс шины в блоке предполагаемого элемента
     * \param typeSecondBus тип шины с которой может быть соединен предполагаемый элемент
     * \param bitnessSecondBus разрядность шины с которой может быть соединен предполагаемый элемент
     * \return true - могут,false - нет
     */
    bool ruleCheckConnection(int idBlockFirst, int idBusFirst, int typeSecondBus, int bitnessSecondBus);
    /*!
     * \brief удаление системы
     */
    void deleteSystem();

    /*!
     * \brief парсер выбранного json-файла
     */
    void readFile();

    /*!
     * \brief возврат индекса типа шины по названию шины
     * \param название типа шины
     * \return индекс типа шины
     */
    int setTypeBus(QString typeStr);

    /*!
     * \brief вывод системы в консоль
     */
    void outputSystem();

    /*!
     * \brief проходит вектор connection и помечает параметр mark = true в тех элементов, которые в файле указаны как соединенные
     */
    void markToFile();
    void updateHeightBlockForDrawing();
    int getHeightBlockForDrawing();

private:    
    QVector <IpBlock> blocks;
    QVector <Connection> connection;
    QVector <Connection> tempConnection;

    int heightBlockForDrawing = 20;
    int heightDrawingReadFile = 0;

    int getTypeBus(int idBlock, int idBus);
    int getBitnessBus(int idBlock, int idBus);

};

#endif // SYSTEM_H
