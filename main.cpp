#define CAMERA 1

#if CAMERA == 1

#include <QApplication>
#include <QFile>
#include <camera.h>
// #include <database.hpp>
#include <iostream>
int main(int argc, char *argv[]) {
    std::cout << "oiiiii" << std::endl;
    QApplication app(argc, argv);
    std::cout << "po" << std::endl;

    Camera camera;
    camera.show();
    QFile styleSheetFile("./resources/stylesheet.qss");
    styleSheetFile.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(styleSheetFile.readAll());
    app.setStyleSheet(styleSheet);
    return app.exec();
};

#elif CAMERA == 0

#include <iostream>
#include <mail.hpp>

int main() {
    Mail m;
    m.mail("moreiramachadoneto@gmail.com");
    std::cout << "Hello world!" << std::endl;
    return 0;
}

#endif
