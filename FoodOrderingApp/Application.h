#ifndef APPLICATION_H
#define APPLICATION_H

#include <QtWidgets>

class Application: public QApplication
{
public:
    using QApplication::QApplication;
    bool notify(QObject *receiver, QEvent *e) override
    {
        if(receiver->isWindowType()){
            if(e->type() == QEvent::Show){
                qDebug()<< receiver << "show";
            }
            else if (e->type() == QEvent::Close) {
                qDebug()<< receiver << "close";
            }
        }
        return QApplication::notify(receiver, e);
    }
};



#endif // APPLICATION_H
