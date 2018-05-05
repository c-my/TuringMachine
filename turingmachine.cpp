#include "turingmachine.h"

TuringMachine::TuringMachine(QObject *parent) : QObject(parent)
{
    currentIndex = 1;
    isRunning = true;
}

bool TuringMachine::setGrammar(QString filename)
{
    QFile jsonFile(filename);
    if(!jsonFile.exists())
        return false;
    jsonFile.open(QIODevice::ReadOnly|QIODevice::Text);
    jsonobj = QJsonDocument::fromJson(jsonFile.readAll()).object();
    jsonFile.close();
    if(jsonobj.isEmpty()||!jsonobj.contains("grammar"))
        return false;
    grammar = jsonobj.value("grammar").toObject();
    if(!grammar.contains("states")
            ||!grammar.contains("input")
            ||!grammar.contains("alphabet")
            ||!grammar.contains("blank")
            ||!grammar.contains("transition"))
            return false;
    //获取初始状态
    initialState = grammar.value("states").toObject().value("initial").toString();
    currentState = initialState;

    //获取终止状态
    finialStates.clear();
    QJsonArray array = grammar.value("states").toObject().value("finial").toArray();
    for(auto item: array)
        finialStates.append(item.toString());

    //获取状态集合
    allStates.clear();
    array = grammar.value("states").toObject().value("states").toArray();
    for(auto item: array)
        allStates.append(item.toString());

    //获取空白符
    blank = grammar.value("blank").toString().at(0);

    //获取字符表
    alphabet.clear();
    array = grammar.value("alphabet").toArray();
    for(auto item: array)
        alphabet += (item.toString());

    //获取接受字符
    input.clear();
    array = grammar.value("input").toArray();
    for(auto item: array)
        input += (item.toString());

    //获取转移字符
    transition.clear();
    QStringList keys = grammar.value("transition").toObject().keys();
    for(auto key: keys)
    {
        QJsonObject subobject = grammar.value("transition").toObject().value(key).toObject();
        QStringList subkeys = subobject.keys();
        for(auto subkey: subkeys)
        {
            QJsonArray array = subobject.value(subkey).toArray();
            QString tmp = "δ(" + key +", " + subkey + ") = (";
            for(auto item: array)
                tmp += item.toString()+", ";
            tmp.remove(tmp.length()-2, 2);
            tmp+=")";
            transition.append(tmp);
        }
    }

    setTestStr(jsonobj.value("demo").toString());
    name = jsonobj.value("name").toString();
    return true;
}

void TuringMachine::setTestStr(QString str)
{
    rawStr = str;
    testStr = blank + str + blank;
    isRunning = true;
}

bool TuringMachine::checkByStep()
{
    QJsonValue value = grammar.value("transition").toObject().value(currentState)
            .toObject().value(testStr.at(currentIndex));
    if(!value.isUndefined())
    {
        QString listItem;
        listItem = "δ(" +currentState + ", " + testStr.at(currentIndex) + ") = (";
        currentState = value.toArray()[0].toString();   //更新当前状态
        testStr[currentIndex] = value.toArray()[1].toString()[0]; //更新当前字符
        QString move = value.toArray()[2].toString();
        listItem += currentState +", " + testStr[currentIndex] + ", " + move+")";
        transitionIndex = transition.indexOf(listItem);

        if(move == "L")
            currentIndex = (currentIndex - 1 >= 0) ? (currentIndex - 1) : 0;
        else if(move == "R")
            currentIndex = (currentIndex + 1 < testStr.size()) ?
                        (currentIndex + 1) : testStr.size()-1;
        else if(move == "S")
            currentIndex = currentIndex;
        return true;
    }
    else
        return false;

}

bool TuringMachine::run()
{
    while (isRunning) {
        checkByStep();
    }
    if(finialStates.contains(currentState))
        return true;
    else
        return false;
}

bool TuringMachine::hasGrammar()
{
    return !this->jsonobj.isEmpty();
}

bool TuringMachine::isStopped()
{
    return !isRunning;
}

void TuringMachine::reset()
{
    currentIndex = 1;
    currentState = initialState;
//    transition.clear();
//    input.clear();
//    alphabet.clear();
//    finialStates.clear();
//    allStates.clear();
}
