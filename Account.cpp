#include "Account.h"

bool Account::isAdmin()
{
    return getType() == "admin";
}
