#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>  // exposes an object to QML

#include "todolist.h"
#include "todomodel.h"

// https://www.youtube.com/watch?v=9BcAYDlpuT8
int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    // register model for QML
    qmlRegisterType<ToDoModel>("ToDo", 1, 0, "ToDoModel");
    // it forces ToDoList is a QML type that it can be used as a property of ToDoModel
    // since ToDoList is the back-end type it should not be created in QML
    // this function prints the error message if there will be attempt to instantiate
    // the type in QML
    qmlRegisterUncreatableType<ToDoList>("ToDo", 1, 0, "ToDoList",
        QStringLiteral("ToDoList should not be created in QML"));

    ToDoList toDoList;

    QQmlApplicationEngine engine;
    // the ToDo list is exposed to QML
    // set as a context property
    // it means it is available to any QML files loaded by application
    // run qmake
    engine.rootContext()->setContextProperty(QStringLiteral("toDoList"), &toDoList);
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
