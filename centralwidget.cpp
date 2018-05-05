#include "centralwidget.h"

CentralWidget::CentralWidget(QWidget *parent) : QWidget(parent)
{
    machine = new TuringMachine(this);

//    nameEdit = new QLineEdit(this);
//    nameEdit->setReadOnly(true);
    autoCheckTimer = new QTimer(this);
    connect(autoCheckTimer, QTimer::timeout, this, [this](){
        checkByStep->click();
    });

    teststrEdit = new QLineEdit(this);

    allStatesEdit = new QLineEdit(this);
    allStatesEdit->setReadOnly(true);
    inputEdit = new QLineEdit(this);
    inputEdit->setReadOnly(true);
    alphabetEdit = new QLineEdit(this);
    alphabetEdit->setReadOnly(true);
    initialStateEdit = new QLineEdit(this);
    initialStateEdit->setReadOnly(true);
    blankEdit = new QLineEdit(this);
    blankEdit->setReadOnly(true);
    finialStatesEdit = new QLineEdit(this);
    finialStatesEdit->setReadOnly(true);

    listWidget = new QListWidget(this);

    importButton = new QPushButton(tr("导入配置"), this);
    connect(importButton, QPushButton::clicked, this, importJson);
    checkByStep = new QPushButton(tr("单步检查"), this);
    checkByStep->setDisabled(true);
    connect(checkByStep, QPushButton::clicked, this, stepCheck);
    autoCheckButton = new QPushButton(tr("自动模式"), this);
    autoCheckButton->setDisabled(true);
    connect(autoCheckButton, QPushButton::clicked, this, autoCheck);
    loadButton = new QPushButton(tr("装载纸带"), this);
    loadButton->setDisabled(true);
    connect(loadButton, QPushButton::clicked, this, loadTape);
    resetButton = new QPushButton(tr("重置"), this);
    connect(resetButton, QPushButton::clicked, this, [this](){
        machine->reset();
        loadButton->setEnabled(true);
        autoCheckButton->setDisabled(true);
        checkByStep->setDisabled(true);
        checkByStep->setChecked(false);
    });

    tape = new PaperTape();
    scene = new QGraphicsScene(this);
    scene->setSceneRect(-250, -65, 500, 130);
    scene->addItem(tape);
    scene->addLine(0,0,0,40,QPen(Qt::red));
    view = new QGraphicsView(scene ,this);


    formlayout = new QFormLayout();
//    formlayout->setSpacing(10);
//    formlayout->setFieldGrowthPolicy(QFormLayout::FieldsStayAtSizeHint);
//    formlayout->addRow(tr("Name"), nameEdit);
    formlayout->addRow(tr("状态集合"), allStatesEdit);
    formlayout->addRow(tr("输入字符"), inputEdit);
    formlayout->addRow(tr("字符表"), alphabetEdit);
    formlayout->addRow(tr("初始状态"), initialStateEdit);
    formlayout->addRow(tr("空白符"), blankEdit);
    formlayout->addRow(tr("终止状态"), finialStatesEdit);
    formlayout->addRow(tr("Test string"), teststrEdit);
//    formlayout->addRow(loadButton);
//    formlayout->addRow(checkByStep);

    vsublayout = new QVBoxLayout();
    vsublayout->addWidget(importButton);
    vsublayout->addWidget(resetButton);
    vsublayout->addWidget(loadButton);
    vsublayout->addWidget(autoCheckButton);
    vsublayout->addWidget(checkByStep);

    hlayout = new QHBoxLayout();
    hlayout->addLayout(formlayout);
    hlayout->addWidget(listWidget);
    hlayout->addLayout(vsublayout);
//    hlayout->addWidget(importButton);


    mainlayout = new QVBoxLayout(this);
    mainlayout->addLayout(hlayout);
    mainlayout->addWidget(view);

    setLayout(mainlayout);
}

CentralWidget::~CentralWidget()
{
    delete machine;
    delete tape;
}

void CentralWidget::importJson()
{
    QString filename = QFileDialog::getOpenFileName(this, tr("import json"),
                                                    ".",tr("json(*.json)"));
    if(filename.isEmpty())
        return;
    if(!machine->setGrammar(filename))
    {
        setStatus("请检查文件格式");
        return;
    };
    setStatus(tr("导入成功"));
    if(machine->hasGrammar())
    {
        loadButton->setEnabled(true);
//        checkByStep->setEnabled(true);
    }
    else
        loadButton->setDisabled(false);
//    nameEdit->setText(machine->getName());
    allStatesEdit->setText(machine->getAllStates().join(", "));
    alphabetEdit->setText(machine->getAlphabet().split("", QString::SkipEmptyParts).join(", "));
    inputEdit->setText(machine->getInput().split("", QString::SkipEmptyParts).join(", "));
    initialStateEdit->setText(machine->getInitialState());
    blankEdit->setText(machine->getBlank());
    finialStatesEdit->setText(machine->getFinialStates().join(", "));
    listWidget->clear();
    listWidget->addItems(machine->getTransition());

    if(teststrEdit->text().isEmpty())
    {
        teststrEdit->setText(machine->getRawStr());
    }
    tape->adjustPos();
}

void CentralWidget::loadTape()
{
    machine->setTestStr(teststrEdit->text());
    machine->reset();
    tape->setStr(machine->getTestStr());
    tape->standBy(1);
    checkByStep->setEnabled(true);
    autoCheckButton->setEnabled(true);
    machineReady = true;
}

void CentralWidget::stepCheck()
{
    machineReady = machine->checkByStep();
    if(machineReady)
    {
        loadButton->setDisabled(true);
        tape->standBy(machine->getCurrentIndex());
        tape->setStr(machine->getTestStr());
        listWidget->setCurrentRow(machine->getTransitionIndex());
    }
    else
    {
        loadButton->setEnabled(true);
        autoCheckButton->setDisabled(true);
        checkByStep->setDisabled(true);
        checkByStep->setChecked(false);
        autoCheckTimer->stop();
        if(machine->getFinialStates().contains(machine->getCurrentState()))
        {
            emit setStatus("Correct!");
        }
        else
        {
            emit setStatus("Not OK!");
        }
    }
}

void CentralWidget::autoCheck()
{
    autoCheckTimer->start(300);
}
