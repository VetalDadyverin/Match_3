#!/bin/bash
BUILD_DIRECTORY=build

if [[ ! -d "$BUILD_DIRECTORY" ]]
then
    mkdir $BUILD_DIRECTORY
fi

cd $BUILD_DIRECTORY
qmake ../Match_3_model_plugin
make 
cp qmldir ./Match_3_model_plugin
qmake ../Match_3_qml
make
./Match_3_qml
