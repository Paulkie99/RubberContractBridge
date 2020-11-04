#include "scoreboard.h"
#include "ui_scoreboard.h"
#include "gamescreen.h"
#include <iostream>
ScoreBoard::ScoreBoard(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ScoreBoard)
{
    ui->setupUi(this);

    // Disable resizing of window
    //ui->tableWidgetScore->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    //ui->tableWidgetScore->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    // Set window title
    QWidget::setWindowTitle("Scoreboard");
}

ScoreBoard::~ScoreBoard()
{
    delete ui;
}

void ScoreBoard::on_ScoreBoard_finished(int result)
{
    Q_UNUSED(result);
    parentWidget()->show();
}

void ScoreBoard::updateScores(QJsonObject NSscores,QJsonObject EWscores)
{
    //QJsonObject tel = NSscores[0];
   // qDebug()<<tel["overtricks"];
         ui->txtNSlog->append("overtricks:"+(QString::number(NSscores["overtricks"].toInt())));
         ui->txtNSlog->append("undertricks:"+QString::number(NSscores["undertricks"].toInt()));
         ui->txtNSlog->append("honors:"+QString::number(NSscores["honors"].toInt()));
         ui->txtNSlog->append("vulnerable:"+QString::number(NSscores["vulnerable"].toInt()));
         ui->txtNSlog->append("double:"+QString::number(NSscores["double"].toInt()));
         ui->txtNSlog->append("redouble:"+QString::number(NSscores["redouble"].toInt()));
         ui->txtNSlog->append("slam:"+QString::number(NSscores["slam"].toInt()));
         ui->txtNSlog->append("unfinished:"+QString::number(NSscores["unfinished"].toInt()));
         ui->txtNSlog->append("trickScore:"+QString::number(NSscores["trickScore"].toInt()));
         ui->txtNSlog->append("insult:"+QString::number(NSscores["insult"].toInt()));
         ui->txtNSlog->append("rubberbonus:"+QString::number(NSscores["rubberbonus"].toInt()));
         ui->txtNSlog->append("---------------------------------------");
         ui->txtNSlog->append("");


         ui->txtEWlog->append("overtricks:"+(QString::number(EWscores["overtricks"].toInt())));
         ui->txtEWlog->append("undertricks:"+QString::number(EWscores["undertricks"].toInt()));
         ui->txtEWlog->append("honors:"+QString::number(EWscores["honors"].toInt()));
         ui->txtEWlog->append("vulnerable:"+QString::number(EWscores["vulnerable"].toInt()));
         ui->txtEWlog->append("double:"+QString::number(EWscores["double"].toInt()));
         ui->txtEWlog->append("redouble:"+QString::number(EWscores["redouble"].toInt()));
         ui->txtEWlog->append("slam:"+QString::number(EWscores["slam"].toInt()));
         ui->txtEWlog->append("unfinished:"+QString::number(EWscores["unfinished"].toInt()));
         ui->txtEWlog->append("trickScore:"+QString::number(EWscores["trickScore"].toInt()));
         ui->txtEWlog->append("insult:"+QString::number(EWscores["insult"].toInt()));
         ui->txtEWlog->append("rubberbonus:"+QString::number(EWscores["rubberbonus"].toInt()));
         ui->txtEWlog->append("----------------------------------------");
         ui->txtEWlog->append("");

         //NS bonus points
         if(NSscores["overtricks"].toInt() > 0)
         {
             ui->txtNSBonus->append(QString::number(NSscores["overtricks"].toInt()));
               NStotal=NStotal+NSscores["overtricks"].toInt();

         }
         if(NSscores["undertricks"].toInt() >0)
         {
             ui->txtNSBonus->append(QString::number(NSscores["undertricks"].toInt()));
               NStotal=NStotal+NSscores["undertricks"].toInt();
         }
         if(NSscores["honors"].toInt() >0)
         {
             ui->txtNSBonus->append(QString::number(NSscores["honors"].toInt()));
               NStotal=NStotal+NSscores["honors"].toInt();
         }
         if(NSscores["vulnerable"].toInt() >0)
         {
//             ui->txtNSBonus->append(QString::number(NSscores["vulnerable"].toInt()));
//               NStotal=NStotal+NSscores["vulnerable"].toInt();
         }
         if(NSscores["double"].toInt() >0)
         {
//             ui->txtNSBonus->append(QString::number(NSscores["double"].toInt()));
//               NStotal=NStotal+NSscores["double"].toInt();
         }
         if(NSscores["redouble"].toInt() >0)
         {
//             ui->txtNSBonus->append(QString::number(NSscores["redouble"].toInt()));
//               NStotal=NStotal+NSscores["redouble"].toInt();

         }
         if(NSscores["slam"].toInt() >0)
         {
             ui->txtNSBonus->append(QString::number(NSscores["slam"].toInt()));
               NStotal=NStotal+NSscores["slam"].toInt();
         }
         if(NSscores["unfinished"].toInt() >0)
         {
             ui->txtNSBonus->append(QString::number(NSscores["unfinished"].toInt()));
               NStotal=NStotal+NSscores["unfinished"].toInt();
         }
         if(NSscores["insult"].toInt() >0)
         {
             ui->txtNSBonus->append(QString::number(NSscores["insult"].toInt()));
               NStotal=NStotal+NSscores["insult"].toInt();
         }
         if(NSscores["rubberbonus"].toInt() >0)
         {
             ui->txtNSBonus->append(QString::number(NSscores["rubberbonus"].toInt()));
               NStotal=NStotal+NSscores["rubberbonus"].toInt();
         }
         if(NSscores["trickScore"].toInt() >0)
         {
             NStotal=NStotal+NSscores["trickScore"].toInt();

             NS100 = NS100+NSscores["trickScore"].toInt();
             if(GNum==0)
             {
                ui->txtNSG1->append(QString::number(NSscores["trickScore"].toInt())) ;
             }else if(GNum==1)
             {
                 ui->txtNSG2->append(QString::number(NSscores["trickScore"].toInt())) ;
             }else
             {
               ui->txtNSG3->append(QString::number(NSscores["trickScore"].toInt())) ;
             }
         }



         //EW bonus points
         if(EWscores["overtricks"].toInt() >0)
         {
             ui->txtEWBonus->append(QString::number(EWscores["overtricks"].toInt()));
               EWtotal=EWtotal+EWscores["overtricks"].toInt();
         }
         if(EWscores["undertricks"].toInt() >0)
         {
             ui->txtEWBonus->append(QString::number(EWscores["undertricks"].toInt()));
               EWtotal=EWtotal+EWscores["undertricks"].toInt();
         }
         if(EWscores["honors"].toInt() >0)
         {
             ui->txtEWBonus->append(QString::number(EWscores["honors"].toInt()));
               EWtotal=EWtotal+EWscores["honors"].toInt();
         }
         if(EWscores["vulnerable"].toInt() >0)
         {
//             ui->txtEWBonus->append(QString::number(EWscores["vulnerable"].toInt()));
//               EWtotal=EWtotal+EWscores["vulnerable"].toInt();
         }
         if(EWscores["double"].toInt() >0)
         {
//             ui->txtEWBonus->append(QString::number(EWscores["double"].toInt()));
//               EWtotal=EWtotal+EWscores["double"].toInt();
         }
         if(EWscores["redouble"].toInt() >0)
         {
//             ui->txtEWBonus->append(QString::number(EWscores["redouble"].toInt()));
//               EWtotal=EWtotal+EWscores["redouble"].toInt();

         }
         if(EWscores["slam"].toInt() >0)
         {
             ui->txtEWBonus->append(QString::number(EWscores["slam"].toInt()));
               EWtotal=EWtotal+EWscores["slam"].toInt();
         }
         if(EWscores["unfinished"].toInt() >0)
         {
             ui->txtEWBonus->append(QString::number(EWscores["unfinished"].toInt()));
               EWtotal=EWtotal+EWscores["unfinished"].toInt();
         }
         if(EWscores["insult"].toInt() >0)
         {
             ui->txtEWBonus->append(QString::number(EWscores["insult"].toInt()));
               EWtotal=EWtotal+EWscores["insult"].toInt();
         }
         if(EWscores["rubberbonus"].toInt() >0)
         {
             ui->txtEWBonus->append(QString::number(EWscores["rubberbonus"].toInt()));
               EWtotal=EWtotal+EWscores["rubberbonus"].toInt();
         }
         if(EWscores["trickScore"].toInt() >0)
         {
             EWtotal=EWtotal+EWscores["trickScore"].toInt();
             EW100 = EW100+EWscores["trickScore"].toInt();
             if(GNum==0)
             {
                ui->txtEWG1->append(QString::number(EWscores["trickScore"].toInt())) ;
             }else if(GNum==1)
             {
                 ui->txtEWG2->append(QString::number(EWscores["trickScore"].toInt())) ;
             }else
             {
               ui->txtEWG3->append(QString::number(EWscores["trickScore"].toInt())) ;
             }
         }


        if((EW100>=100)||(NS100>=100))
        {
            GNum++;
            EW100=0;
            NS100=0;
        }
        ui->EWTotal->setText( "Total: "+QString::number(EWtotal));
        ui->NSTotal->setText("Total: "+QString::number(NStotal));
     //QJsonObject NSscores = scoresToDisplay["NSscores"].toObject();
    // QJsonObject EWscores = scoresToDisplay["EWscores"].toObject();

     //code to update gui
     //int NSScores2 = scoresToDisplay["NSscores"].toObject()["overtricks"].toInt();
    // ui->txtWeAbove1->setText(QString::number(NSScores2));
    // ui->txtWeAbove1->append("hello");
}

