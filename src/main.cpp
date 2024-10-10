#include <iostream>

#include <surfacemeshprocessing.h>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QSurfaceFormat format;
    format.setSamples(16);
    QSurfaceFormat::setDefaultFormat(format);
    SurfaceMeshProcessing mainWin;
    mainWin.move(100, 100);
    mainWin.show();
    return app.exec();
}
