#include "page_dev.h"
#include "ui_page_dev.h"

page_dev::page_dev(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::page_dev)
{
    ui->setupUi(this);
    //一些初始的ui
    iconFont=(new Tool())->getIconFont();
    ui->logo->setFont(iconFont);
    ui->logo->setText(_icon_poll);

    db=new database();
    //初始化环境信息
    QString nodes="0,0,0,0,0,0,00";//温度，湿度，照度，粉尘浓度，大气压强，序号，设备状态
    env_info=nodes.split(",");
    env_info2=nodes.split(",");

    views[0]=ui->tem;views[1]=ui->hum;views[2]=ui->fc;views[3]=ui->atm;
    views[4]=ui->tem_2;views[5]=ui->hum_2;views[6]=ui->fc_2;views[7]=ui->atm_2;
    //初始化图表
    initChart();

    //初始化数据
    for(int i=0;i<6;i++){
        QVector<float>*s=new QVector<float>();
        for(int j=0;j<8;j++)s->append(0);
        time.append(QString::number(i));
        time2.append(QString::number(i));
        datas.append(*s);
    }
    QTimer *timer = new QTimer(this);
    connect(timer,&QTimer::timeout,this,&page_dev::updateChart);
    timer->start(freshtime);
    connect(ui->app,&QComboBox::currentTextChanged,this,&page_dev::chooseUnit);
    chooseUnit();
}

page_dev::~page_dev()
{
    delete ui;
}

void page_dev::initChart(){
    float min[]={15,20,5000,99};
    float max[]={45,90,7000,103};//范围
    for(int i=0;i<8;i++){
        chart[i]=new QChart();
        axisX[i]=new QBarCategoryAxis();
        axisY[i]=new QValueAxis();
        // 将图例隐藏
        chart[i]->legend()->hide();
        //横坐标轴
        QStringList categories;
        for(int j=0;j<6;j++)
            categories.append(QString::number(j));
        axisX[i]->setCategories(categories);
        axisY[i]->setRange(min[i%4],max[i%4]);
        views[i]->setChart(chart[i]);
        views[i]->chart()->addAxis(axisX[i], Qt::AlignBottom);
        views[i]->chart()->addAxis(axisY[i], Qt::AlignLeft);
        views[i]->setRenderHint(QPainter::Antialiasing);
    }
}

void page_dev::getData(){
    QString t=QDate::currentDate().toString("yyyy/MM/dd");
    QVector<QVector<QString>>d=db->readData6(t,1);
    QVector<QVector<QString>>d2=db->readData6(t,2);
    for(int i=0;i<d.length();i++){
        time[i]=d[i][1];
        datas[i][0]=d[i][2].toFloat();//tem
        datas[i][1]=d[i][3].toFloat();//hum
        datas[i][2]=d[i][5].toFloat();//fc
        datas[i][3]=d[i][6].toFloat();//atm
    }
    for(int i=0;i<d2.length();i++){
        time2[i]=d2[i][1];
        datas[i][4]=d2[i][2].toFloat();//tem
        datas[i][5]=d2[i][3].toFloat();//hum
        datas[i][6]=d2[i][5].toFloat();//fc
        datas[i][7]=d2[i][6].toFloat();//atm
    }
}
void page_dev::chooseUnit(){
    int n=ui->app->currentText().toInt();
    if(n==1){
        for(int i=0;i<4;i++){
            views[i]->show();
            views[i+4]->hide();
        }
        ui->app_n->setText("环境表1");
    }else{
        for(int i=0;i<4;i++){
            views[i]->hide();
            views[i+4]->show();
        }
        ui->app_n->setText("环境表2");
    }
}
void page_dev::updateChart(){
    if(!isLogin)return;
    QString color[]={"blue","red","green","purple"};
    updateData();
    //曲线绘制
    if(QString::compare(env_info[5],"0")){//1号有效
        for(int i=0;i<4;i++){
            views[i]->chart()->removeAllSeries();
            series[i]=new QLineSeries();
            for(int j=0;j<6;j++){
               series[i]->append(j,datas[j][i]);
            }
            series[i]->setPointsVisible(true);
            series[i]->setColor(color[i%4]);
            series[i]->setPointLabelsFormat("@yPoint");
            //更新坐标轴
            QStringList categories;
            for(int j=0;j<6;j++)
                categories.append(i<4?time[j].right(5):time2[j].right(5));
            axisX[i]->setCategories(categories);

            views[i]->chart()->addSeries(series[i]);
            //线与坐标轴对应起来
            series[i]->attachAxis(axisX[i]);
            series[i]->attachAxis(axisY[i]);
        }
    }
    if(QString::compare(env_info2[5],"0")){//2号有效
        for(int i=4;i<8;i++){
            views[i]->chart()->removeAllSeries();
            series[i]=new QLineSeries();
            for(int j=0;j<6;j++){
               series[i]->append(j,datas[j][i]);
            }
            series[i]->setPointsVisible(true);
            series[i]->setColor(color[i%4]);
            series[i]->setPointLabelsFormat("@yPoint");
            //更新坐标轴
            QStringList categories;
            for(int j=0;j<6;j++)
                categories.append(i<4?time[j].right(5):time2[j].right(5));
            axisX[i]->setCategories(categories);

            views[i]->chart()->addSeries(series[i]);
            //线与坐标轴对应起来
            series[i]->attachAxis(axisX[i]);
            series[i]->attachAxis(axisY[i]);
        }
    }

}

void page_dev::updateData(){
    QVector<float>va={
        env_info[0].toFloat(),env_info[1].toFloat(),env_info[3].toFloat(),env_info[4].toFloat(),
        env_info2[0].toFloat(),env_info2[1].toFloat(),env_info2[3].toFloat(),env_info2[4].toFloat()
    };
    datas.pop_front();
    datas.push_back(va);
    QString t=QTime::currentTime().toString("hh:mm:ss");
    time.pop_front();
    time.push_back(t);
    time2.pop_front();
    time2.push_back(t);
}
