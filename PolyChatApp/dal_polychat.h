#ifndef DAL_POLYCHAT_H
#define DAL_POLYCHAT_H

#include "bll_polychat.h"

namespace DAL
{


/** Check info and init
 * @brief initLocalUser
 * @param name
 * @param groupNumber
 * @return false in name or group have error,
 *          if not init local user and return true
 */
bool initLocalUser(const QString name, const QString groupNumber)
{
    if (name.isEmpty() || groupNumber.isEmpty())
    {
        return false;
    }

    BLL::initLocalUser(name, groupNumber);
    return true;
}

/** Show ChatList Widget
 * @brief initAndShowChatList
 */
void initAndShowChatList(QWidget* parent)
{
    BLL::initAndShowChatList(parent);
}

}

#endif // DAL_POLYCHAT_H
