#ifndef SHINE_H
#define SHINE_H

#include <QString>
#include <QVector>

/*!
 * \brief множество типов шин
 */
enum class TypeBus {AVALON = 0, AXI, APB, WISHBONE,     MAX_BUS = 4};
const QString g_typeBus[4] = {"AVALON", "AXI", "APB", "WISHBONE"};                                      ///<типы шин
const bool g_busMapping[static_cast<int>(TypeBus::MAX_BUS)][static_cast<int>(TypeBus::MAX_BUS)] = {     ///<правила для формирования связей между шинами
    {true, false, false, false},
    {false, true, false, false},
    {false, false, true, false},
    {false, false, false, true}
};
/*!
 * \brief структура, в которой хранится идентификатор шины и идентификатор блока, в котором она находится
 * \details нужна для формирования связей - показывает с каким элементом данная шина может соединиться
 */
struct ConnectionBus{
    int idBlock = -1;
    int idBus = -1;
};
/*!
 * \brief класс описывающий шину
 */
class Bus
{
private:
    QString nameBus = "";
    QString startAddress = "";
    QString finishAddress = "";
    int typeBus = 0;
    int bitness = 0;
    int id = -1;
    QVector <ConnectionBus> connectionOnID;

public:    
    Bus();
    ~Bus();
    Bus(QString nameBus, int typeBus, int bitness, int id, QString startAddress, QString finishAddress);
    /*!
     * \brief возвращает название шина
     * \return строку с названием шины
     */
    QString getNameBus();

    /*!
     * \brief возвращает начальный адрес шины
     * \return строку с адрессом начальной шины
     */
    QString getStartAddress();

    /*!
     * \brief возвращает конечный адрес шины
     * \return строка с конечным адрессом шины
     */
    QString getFinishAddress();

    /*!
     * \brief возвращает тип шины
     * \return число - идентификатор типа шин
     */
    int getTypeBus();

    /*!
     * \brief возвращает разрядность шины
     * \return число - разрядность
     */
    int getBitness();

    /*!
     * \brief возвращает идентификатор шины
     * \return число - идентификатор шины
     */
    int getId();

    /*!
     * \brief возвращает все возможные соединения данной шины с другими шинами
     * \return вектор из объектов типа ConnectionBus
     */
    QVector <ConnectionBus> getConnectionOnID();

    /*!
     * \brief возвращает один элемент типа Connection(соединение данной шины с одной другой шиной)
     * \param index индекс элемента, который нужно получить
     * \return один элемент из вектора connection
     */
    ConnectionBus getConnectionOnIndex(int index);

    /*!
     * \brief добавляет новое возможное соединение шины в вектор имеющихся
     * \param connection элемент типа ConnectionBus
     */
    void addConnection(ConnectionBus connection);
};



#endif // SHINE_H
