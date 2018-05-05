#ifndef TURINGMACHINE_H
#define TURINGMACHINE_H

#include <QObject>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QVector>
#include <QDebug>

class TuringMachine : public QObject
{
    Q_OBJECT
public:
    TuringMachine(QObject *parent = nullptr);
    bool setGrammar(QString filename);
    void setTestStr(QString str);
    QString getTestStr() { return testStr; }
    QString getRawStr() { return rawStr; }
    QString getName() { return name; }
    QString getInitialState() { return initialState; }
    QChar   getBlank() { return blank; }
    QStringList getFinialStates() { return finialStates; }
    QStringList getAllStates() { return allStates; }
    QString     getAlphabet() { return alphabet; }
    QString     getInput()  { return input; }
    int     getCurrentIndex() { return currentIndex; }
    QStringList getTransition() { return transition; }
    int     getTransitionIndex() { return transitionIndex; }
    QString getCurrentState() { return currentState; }
    bool checkByStep();
    bool run();
    bool hasGrammar();
    bool isStopped();
    void reset();

private:
    QJsonObject jsonobj;
    QJsonObject grammar;
    QString     name;
    QString     rawStr, testStr;
    QChar       blank;  //空白符
    QString     currentState;   //当前状态
    int         currentIndex;   //当前字符索引号
    int         transitionIndex;
    QString     initialState;
    QStringList finialStates;
    QStringList allStates;
    QString     input;
    QString     alphabet;
    QStringList transition;
    bool        isRunning;
};

#endif // TURINGMACHINE_H
