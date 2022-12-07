#ifndef BLL_POLYCHAT_H
#define BLL_POLYCHAT_H

#include "db_localdata.h"

#include <QNetworkInterface>
#include <QRandomGenerator>

namespace BLL
{

/** Get IP address local PC, fomat like `192.168.XX.XX`
 * @brief getIPAddress
 * @return [QHostAddress] IP Address local PC
 */
static QHostAddress getIPAddress()
{
    QHostAddress ipAddress;
    QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();
    for (int i = 0; i < ipAddressesList.size(); ++i)
    {
        if (ipAddressesList.at(i) != QHostAddress::LocalHost
            && ipAddressesList.at(i).toIPv4Address())
        {
            ipAddress = ipAddressesList.at(i);
            break;
        }
    }

    if (ipAddress.toString().isEmpty())
        ipAddress = QHostAddress(QHostAddress::LocalHost);

    return ipAddress;
}


/**
 * @brief initLocalUser
 * @param name
 * @param groupNumber
 * @return true
 */
static bool initLocalUser(QString name, QString groupNumber)
{
    DB::localUserName           = name;
    DB::localUserGroupNumber    = groupNumber;
    DB::localIpAddress          = getIPAddress();

    return true;
}

static QString      getLocalUserName()
{
    return DB::localUserName;
}

static void      setLocalUserName(QString localUserName)
{
    DB::localUserName = localUserName;
}

static QString      getLocalUserGroupNumber()
{
    return DB::localUserGroupNumber;
}
static void      setLocalUserGroupNumber(QString localUserGroupNumber)
{
    DB::localUserGroupNumber = localUserGroupNumber;
}


static QHostAddress getLocalIpAddress()
{
    return DB::localIpAddress;
}
static void setLocalIpAddress(QHostAddress localIpAddress)
{
    DB::localIpAddress = localIpAddress;
}

static qint16 getPortChatList()
{
    return DB::PORT_CHAT_LIST;
}

/** Show ChatList Widget
 * @brief initAndShowChatList
 */
static void initAndShowChatList(QWidget* parent)
{
    DB::chatList = new ChatList(parent, DB::localUserName, DB::localUserGroupNumber, DB::localIpAddress);
    DB::chatList->show();
}


/** 查找一个名称的群聊是否已经存在
 * @brief isChatExist
 * @param name
 * @return 存在返回 true
 */
static bool isChatExist(const QString name)
{
    for (auto i : DB::vChat)
    {
        if (name == i->name) return true;
    }

    return false;
}


/** 查找一个端口号是否被占用
 * @brief isPortExist
 * @param port
 * @return
 */
static bool isPortExist(const qint16 port)
{
    if (DB::vChat.isEmpty()) return false;
    for (auto i : DB::vChat)
    {
        if (port == i->port || port == DB::PORT_CHAT_LIST) return true;
    }

    return false;
}

/** 获取一个不重复的随机端口号
 * @brief getRandomPort
 * @return
 */
static qint16 getRandomPort()
{

    while (true)
    {
        qint16 port = QRandomGenerator::global()->bounded(DB::PORT_MIN, DB::PORT_MAX);
        if (!isPortExist(port)) return port;
    }

    qDebug() << 2;

}


/** 创建并插入新的聊天窗口信息
 * @brief getAndInsertNewChat
 * @param name
 * @param port
 * @param isOpen
 * @return
 */
static Chat* getAndInsertNewChat(QString name, qint16 port, bool isOpen = true)
{
    Chat* chat = new Chat(name, port, isOpen);
    DB::vChat.push_back(chat);
    return chat;
}


static QVector<Chat*> getVectorChatList()
{
    return DB::vChat;
}


}

#endif // BLL_POLYCHAT_H
