// Copyright (C) 2021 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#include "QtGUI/include/app.h"

int main(int argc, char *argv[])
{
    app app(argc, argv);
	auto r = app.run();
	return r;
}
