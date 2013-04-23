// Copyright (C) 2010 EPFL
// All rights reserved. EPFL internal use only.
//
// Author:
// Laurent Bindschaedler <laurent.bindschaedler@epfl.ch>

#include <QCoreApplication>
#include "testreceiver.h"

// Main program for the receiver test

int main(int argc, char **argv) {
    QCoreApplication a(argc,argv);
    TestReceiver example;
    return a.exec();
}

