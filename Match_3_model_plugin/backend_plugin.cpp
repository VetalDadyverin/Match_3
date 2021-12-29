#include "backend_plugin.h"
#include "mylistmodel.h"
#include <qqml.h>

void Match3Plugin::registerTypes(const char *uri){
    qmlRegisterType<MyListModel>(uri, 1, 0, "MyListModel");
}

