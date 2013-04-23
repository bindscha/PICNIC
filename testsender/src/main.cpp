// Copyright (C) 2010 EPFL
// All rights reserved. EPFL internal use only.
//
// Author:
// Laurent Bindschaedler <laurent.bindschaedler@epfl.ch>

#include <QCoreApplication>
#include "testsender.h"

// Main program for the sender test

int main(int argc, char **argv) {
    QCoreApplication a(argc,argv);
    TestSender example;
    return a.exec();
}

