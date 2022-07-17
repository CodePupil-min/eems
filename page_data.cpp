#include "page_data.h"
#include "ui_page_data.h"

page_data::page_data(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::page_data)
{
    ui->setupUi(this);
    //一些初始的ui
    iconFont=(new Tool())->getIconFont();
    ui->logo->setFont(iconFont);
    ui->logo->setText(_icon_data);

    db=new database();
    //当前日期
    ui->date->setDate(QDate::currentDate());
    //刷新数据
    QTimer *timer = new QTimer(this);
    connect(timer,&QTimer::timeout,this,&page_data::updateRecord);
    timer->start(savetime);
    ui->save->setText("*保存间隔："+QString::number(savetime/1000)+"s");
    connect(ui->inquire,&QPushButton::clicked,this,&page_data::updateRecord);
    connect(ui->app,&QComboBox::currentTextChanged,this,&page_data::updateRecord);
    connect(ui->remove,&QPushButton::clicked,this,&page_data::removeRecord);

}

page_data::~page_data()
{
    delete ui;
}
void page_data::updateRecord(){
    if(!isLogin)return;
    int n=ui->app->currentText().toInt();
    ui->app_n->setText("（环境表-"+QString::number(n)+"）");
    data=db->readData(ui->date->text(),n);
    content=new QStandardItemModel();
    //添加表头
    int col_num=7;
    content->setColumnCount(col_num+1);
    content->setHeaderData(0,Qt::Horizontal,QStringLiteral("序号"));   //设置表头内容
    content->setHeaderData(1,Qt::Horizontal,QStringLiteral("日期"));   //设置表头内容
    content->setHeaderData(2,Qt::Horizontal,QStringLiteral("时间"));   //设置表头内容
    content->setHeaderData(3,Qt::Horizontal,QStringLiteral("温度(℃)"));   //设置表头内容
    content->setHeaderData(4,Qt::Horizontal,QStringLiteral("湿度(%PH)"));   //设置表头内容
    content->setHeaderData(5,Qt::Horizontal,QStringLiteral("光照等级"));   //设置表头内容
    content->setHeaderData(6,Qt::Horizontal,QStringLiteral("粉尘浓度(pcs/283ml)"));   //设置表头内容
    content->setHeaderData(7,Qt::Horizontal,QStringLiteral("大气压强(pa)"));   //设置表头内容
    ui->datatable->setModel(content);    //挂载表格模型
    ui->datatable->horizontalHeader()->setDefaultAlignment(Qt::AlignCenter);        //表头信息显示居中
    ui->datatable->verticalHeader()->hide();    //隐藏默认显示的行头
    ui->datatable->horizontalHeader()->setSectionResizeMode(0,QHeaderView::Fixed);  //设定第一列表头列宽不可变
    ui->datatable->setColumnWidth(0,40);       //设定表格第1列宽度
    ui->datatable->horizontalHeader()->setSectionResizeMode(1,QHeaderView::Fixed);  //设定第二列表头列宽不可变
    ui->datatable->setColumnWidth(0,80);       //设定表格第2列宽度
    ui->datatable->horizontalHeader()->setSectionResizeMode(2,QHeaderView::Fixed);  //设定第三列表头列宽不可变
    ui->datatable->setColumnWidth(0,80);       //设定表格第3列宽度
    for(int i=3;i<col_num+1;i++){
        ui->datatable->horizontalHeader()->setSectionResizeMode(i,QHeaderView::Stretch);//设定后面列表头弹性拉伸
    }
    for(int i=0;i<data.size();i++){
        QStandardItem *item0 = new QStandardItem(tr("%1").arg(i+1));
        content->setItem(i,0,item0);                                //表格第i行，第1列添加一项内容
        content->item(i,0)->setTextAlignment(Qt::AlignCenter);      //设置表格内容居中
        for(int j=0;j<col_num;j++){
            QStandardItem *item = new QStandardItem(data.at(i)[j]);
            content->setItem(i,j+1,item);                                //表格第i行，第3列添加一项内容
            content->item(i,j+1)->setTextAlignment(Qt::AlignCenter);           //设置表格内容居中
        }
    }
}
void page_data::removeRecord(){
    QString date=ui->date->text();
    int n=ui->app->currentText().toInt();
    confirm *c=new confirm(this);
    if(!c->reveal("删除环境表"+ui->app->currentText()+"\n“"+date+"”的全部数据",_icon_trash)){delete c;return;}
    db->removeDay(date,n);
    updateRecord();
}
