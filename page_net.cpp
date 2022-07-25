#include "page_net.h"
#include "ui_page_net.h"

page_net::page_net(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::page_net)
{
    ui->setupUi(this);
    //一些初始的ui
    iconFont=(new Tool())->getIconFont();
    ui->logo->setFont(iconFont);
    ui->logo->setText(_icon_net);
    ui->refresh->setFont(iconFont);
    ui->refresh->setText(_icon_refresh);
    ui->tem_1->setFont(iconFont);
    ui->tem_1->setText(_icon_s_off);
    ui->zd_1->setFont(iconFont);
    ui->zd_1->setText(_icon_s_off);
    ui->tem_2->setFont(iconFont);
    ui->tem_2->setText(_icon_s_off);
    ui->zd_2->setFont(iconFont);
    ui->zd_2->setText(_icon_s_off);

    for(int i=0;i<4;i++)dev_auto[i]=0;
    ui->spin_1->setSuffix(" ℃");
    ui->spin_1->setMinimum(26);
    ui->spin_1->setMaximum(35);
    ui->spin_2->setSuffix(" ℃");
    ui->spin_2->setMinimum(26);
    ui->spin_2->setMaximum(35);
}

page_net::~page_net()
{
    delete ui;
}

void page_net::setCurrentPort(QSerialPort** port){
    currentport=*port;
    setSerialPortUnit();
}
void page_net::setSerialPortUnit(){
    //刷新存在的串口
    refreshSorts();
    connect(ui->refresh,&QPushButton::clicked,this,&page_net::refreshSorts);
    //设置默认连接参数
    ui->port_data->setCurrentText("8");
    ui->port_stop->setCurrentText("1");
    ui->port_baud->setCurrentText("57600");
    ui->port_parity->setCurrentText("无校验");
    //选中并打开串口
    openPort();
    connect(ui->sure,&QPushButton::clicked,this,&page_net::openPort);
}
void page_net::refreshSorts(){
    //刷新出所有串口
    QStringList portnames;
    foreach(const QSerialPortInfo &info,QSerialPortInfo::availablePorts()){
        portnames<<info.portName();
    }
    ui->ports->clear();
    ui->ports->addItems(portnames);
}

void page_net::openPort(){
    if(currentport==nullptr)return;
    if(currentport->isOpen()){
        currentport->clear();
        currentport->close();
    }
    currentport->setPortName(ui->ports->currentText());//选择当前串口
    if(!currentport->open(QIODevice::ReadWrite)){
//        qDebug()<<"打开失败";
        return;
    }
    //设置波特率和读写方向
    QString baud=ui->port_baud->currentText();
    currentport->setBaudRate(baud.toUInt(),QSerialPort::AllDirections);
    //数据位
    int data=ui->port_data->currentText().toInt();
    QSerialPort::DataBits databit;
    databit=data>=7?(data==8?QSerialPort::Data8:QSerialPort::Data7):(data==6?QSerialPort::Data6:QSerialPort::Data5);
    currentport->setDataBits(databit);
    //停止位
    QString stop=ui->port_stop->currentText();
    QSerialPort::StopBits stopbit=QString::compare(stop,"2")?QSerialPort::OneStop:QSerialPort::TwoStop;
    currentport->setStopBits(stopbit);
    //无校验位
    QString parity=ui->port_parity->currentText();
    QSerialPort::Parity paritybit=QSerialPort::NoParity;
    if(QString::compare(parity,"无校验"))//如果不是无校验
        paritybit=QString::compare(parity,"奇校验")==0?QSerialPort::OddParity:QSerialPort::EvenParity;
    currentport->setParity(paritybit);
    //无流控制
    currentport->setFlowControl(QSerialPort::NoFlowControl);
//    qDebug()<<"打开成功";
    ui->current_port->setText(currentport->portName()+" ["+baud+"-"+ui->port_data->currentText()+"-"+stop+"-"+parity+"]");
}

void page_net::autoTem_1(){
    bool s=dev_auto[0]=!dev_auto[0];
    ui->tem_1->setText(s?_icon_s_on:_icon_s_off);
    //关闭
    if(!s){
        currentport->write("k");
        return;
    }
    int tem=ui->spin_1->value();
    QString t=QChar(tem-26+'a');
    currentport->write(t.toLocal8Bit());
}
void page_net::autozd_1(){
    bool s=dev_auto[1]=!dev_auto[1];
    ui->zd_1->setText(s?_icon_s_on:_icon_s_off);
    if(s)currentport->write("y");
    else currentport->write("z");
}

void page_net::autoTem_2(){
    bool s=dev_auto[2]=!dev_auto[2];
    ui->tem_2->setText(s?_icon_s_on:_icon_s_off);
    //关闭
    if(!s){
        currentport->write("K");
        return;
    }
    int tem=ui->spin_2->value();
    QString t=QChar(tem-26+'A');
    currentport->write(t.toLocal8Bit());
}
void page_net::autozd_2(){
    bool s=dev_auto[3]=!dev_auto[3];
    ui->zd_2->setText(s?_icon_s_on:_icon_s_off);
    if(s)currentport->write("Y");
    else currentport->write("Z");
}
void page_net::setBtn(){
    QPushButton* btn[]={ui->tem_1,ui->tem_2,ui->zd_1,ui->zd_2};
    if(!isLogin){
        for(int i=0;i<4;i++){
            disconnect(btn[i],&QPushButton::clicked,0,0);
            btn[i]->setStyleSheet("color:#c7c7c7");
        }
        return;
    }
    for(int i=0;i<4;i++){
        btn[i]->setStyleSheet("color:#409EFF");
    }
    connect(ui->tem_1,&QPushButton::clicked,this,&page_net::autoTem_1);
    connect(ui->tem_2,&QPushButton::clicked,this,&page_net::autoTem_2);
    connect(ui->zd_1,&QPushButton::clicked,this,&page_net::autozd_1);
    connect(ui->zd_2,&QPushButton::clicked,this,&page_net::autozd_2);
}
