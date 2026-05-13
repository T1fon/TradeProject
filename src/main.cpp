#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "optionwindow_v.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    qmlRegisterType<OptionWindow_V>("XMlLoader", 1, 0, "OptionWindow_V");
    const QUrl url(u"qrc:/TradeProject/src/Main.qml"_qs);
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
