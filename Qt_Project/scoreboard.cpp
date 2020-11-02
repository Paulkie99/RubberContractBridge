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
    parentWidget()->show();
}

void ScoreBoard::updateScores(QJsonObject NSscores [50],QJsonObject EWscores [50],int Counterz)
{
    //QJsonObject tel = NSscores[0];
   // qDebug()<<tel["overtricks"];
    int loops = 0;
    int EWtotal=0;
    int NStotal = 0;
    int NS100=0;
    int EW100=0;
    int GNum=0;
    while(loops!=Counterz)
    {
         ui->txtNSlog->append("overtricks:"+(QString::number(NSscores[loops]["overtricks"].toInt())));
         ui->txtNSlog->append("undertricks:"+QString::number(NSscores[loops]["undertricks"].toInt()));
         ui->txtNSlog->append("honors:"+QString::number(NSscores[loops]["honors"].toInt()));
//         ui->txtNSlog->append("vulnerable:"+QString::number(NSscores[loops]["vulnerable"].toInt()));
//         ui->txtNSlog->append("double:"+QString::number(NSscores[loops]["double"].toInt()));
//         ui->txtNSlog->append("redouble:"+QString::number(NSscores[loops]["redouble"].toInt()));
         ui->txtNSlog->append("slam:"+QString::number(NSscores[loops]["slam"].toInt()));
         ui->txtNSlog->append("unfinished:"+QString::number(NSscores[loops]["unfinished"].toInt()));
         ui->txtNSlog->append("trickScore:"+QString::number(NSscores[loops]["trickScore"].toInt()));
         ui->txtNSlog->append("---------------------------------------");
         ui->txtNSlog->append("");


         ui->txtEWlog->append("overtricks:"+(QString::number(EWscores[loops]["overtricks"].toInt())));
         ui->txtEWlog->append("undertricks:"+QString::number(EWscores[loops]["undertricks"].toInt()));
         ui->txtEWlog->append("honors:"+QString::number(EWscores[loops]["honors"].toInt()));
//         ui->txtEWlog->append("vulnerable:"+QString::number(EWscores[loops]["vulnerable"].toInt()));
//         ui->txtEWlog->append("double:"+QString::number(EWscores[loops]["double"].toInt()));
//         ui->txtEWlog->append("redouble:"+QString::number(EWscores[loops]["redouble"].toInt()));
         ui->txtEWlog->append("slam:"+QString::number(EWscores[loops]["slam"].toInt()));
         ui->txtEWlog->append("unfinished:"+QString::number(EWscores[loops]["unfinished"].toInt()));
         ui->txtEWlog->append("trickScore:"+QString::number(EWscores[loops]["trickScore"].toInt()));
         ui->txtEWlog->append("----------------------------------------");
         ui->txtEWlog->append("");

         //NS bonus points
         if(NSscores[loops]["overtricks"].toInt() > 0)
         {
             ui->txtNSBonus->append(QString::number(NSscores[loops]["overtricks"].toInt()));
               NStotal=NStotal+NSscores[loops]["overtricks"].toInt();

         }
         if(NSscores[loops]["undertricks"].toInt() >0)
         {
             ui->txtNSBonus->append(QString::number(NSscores[loops]["undertricks"].toInt()));
               NStotal=NStotal+NSscores[loops]["undertricks"].toInt();
         }
         if(NSscores[loops]["honors"].toInt() >0)
         {
             ui->txtNSBonus->append(QString::number(NSscores[loops]["honors"].toInt()));
               NStotal=NStotal+NSscores[loops]["honors"].toInt();
         }
         if(NSscores[loops]["vulnerable"].toInt() >0)
         {
             ui->txtNSBonus->append(QString::number(NSscores[loops]["vulnerable"].toInt()));
//               NStotal=NStotal+NSscores[loops]["vulnerable"].toInt();
         }
         if(NSscores[loops]["double"].toInt() >0)
         {
             ui->txtNSBonus->append(QString::number(NSscores[loops]["double"].toInt()));
//               NStotal=NStotal+NSscores[loops]["double"].toInt();
         }
         if(NSscores[loops]["redouble"].toInt() >0)
         {
             ui->txtNSBonus->append(QString::number(NSscores[loops]["redouble"].toInt()));
//               NStotal=NStotal+NSscores[loops]["redouble"].toInt();

         }
         if(NSscores[loops]["slam"].toInt() >0)
         {
             ui->txtNSBonus->append(QString::number(NSscores[loops]["slam"].toInt()));
               NStotal=NStotal+NSscores[loops]["slam"].toInt();
         }
         if(NSscores[loops]["unfinished"].toInt() >0)
         {
             ui->txtNSBonus->append(QString::number(NSscores[loops]["unfinished"].toInt()));
               NStotal=NStotal+NSscores[loops]["unfinished"].toInt();
         }
         if(NSscores[loops]["insult"].toInt() >0)
         {
             ui->txtNSBonus->append(QString::number(NSscores[loops]["insult"].toInt()));
               NStotal=NStotal+NSscores[loops]["insult"].toInt();
         }
         if(NSscores[loops]["rubberbonus"].toInt() >0)
         {
             ui->txtNSBonus->append(QString::number(NSscores[loops]["rubberbonus"].toInt()));
               NStotal=NStotal+NSscores[loops]["rubberbonus"].toInt();
         }
         if(NSscores[loops]["trickScore"].toInt() >0)
         {
             NStotal=NStotal+NSscores[loops]["trickScore"].toInt();

             NS100 = NS100+NSscores[loops]["trickScore"].toInt();
             if(GNum==0)
             {
                ui->txtNSG1->append(QString::number(NSscores[loops]["trickScore"].toInt())) ;
             }else if(GNum==1)
             {
                 ui->txtNSG2->append(QString::number(NSscores[loops]["trickScore"].toInt())) ;
             }else
             {
               ui->txtNSG3->append(QString::number(NSscores[loops]["trickScore"].toInt())) ;
             }
         }



         //EW bonus points
         if(EWscores[loops]["overtricks"].toInt() >0)
         {
             ui->txtEWBonus->append(QString::number(EWscores[loops]["overtricks"].toInt()));
               EWtotal=EWtotal+EWscores[loops]["overtricks"].toInt();
         }
         if(EWscores[loops]["undertricks"].toInt() >0)
         {
             ui->txtEWBonus->append(QString::number(EWscores[loops]["undertricks"].toInt()));
               EWtotal=EWtotal+EWscores[loops]["undertricks"].toInt();
         }
         if(EWscores[loops]["honors"].toInt() >0)
         {
             ui->txtEWBonus->append(QString::number(EWscores[loops]["honors"].toInt()));
               EWtotal=EWtotal+EWscores[loops]["honors"].toInt();
         }
         if(EWscores[loops]["vulnerable"].toInt() >0)
         {
             ui->txtEWBonus->append(QString::number(EWscores[loops]["vulnerable"].toInt()));
//               EWtotal=EWtotal+EWscores[loops]["vulnerable"].toInt();
         }
         if(EWscores[loops]["double"].toInt() >0)
         {
             ui->txtEWBonus->append(QString::number(EWscores[loops]["double"].toInt()));
//               EWtotal=EWtotal+EWscores[loops]["double"].toInt();
         }
         if(EWscores[loops]["redouble"].toInt() >0)
         {
             ui->txtEWBonus->append(QString::number(EWscores[loops]["redouble"].toInt()));
//               EWtotal=EWtotal+EWscores[loops]["redouble"].toInt();

         }
         if(EWscores[loops]["slam"].toInt() >0)
         {
             ui->txtEWBonus->append(QString::number(EWscores[loops]["slam"].toInt()));
               EWtotal=EWtotal+EWscores[loops]["slam"].toInt();
         }
         if(EWscores[loops]["unfinished"].toInt() >0)
         {
             ui->txtEWBonus->append(QString::number(EWscores[loops]["unfinished"].toInt()));
               EWtotal=EWtotal+EWscores[loops]["unfinished"].toInt();
         }
         if(EWscores[loops]["insult"].toInt() >0)
         {
             ui->txtEWBonus->append(QString::number(EWscores[loops]["insult"].toInt()));
               EWtotal=EWtotal+EWscores[loops]["insult"].toInt();
         }
         if(EWscores[loops]["rubberbonus"].toInt() >0)
         {
             ui->txtEWBonus->append(QString::number(EWscores[loops]["rubberbonus"].toInt()));
               EWtotal=EWtotal+EWscores[loops]["rubberbonus"].toInt();
         }
         if(EWscores[loops]["trickScore"].toInt() >0)
         {
             EWtotal=EWtotal+EWscores[loops]["trickScore"].toInt();
             EW100 = EW100+EWscores[loops]["trickScore"].toInt();
             if(GNum==0)
             {
                ui->txtEWG1->append(QString::number(EWscores[loops]["trickScore"].toInt())) ;
             }else if(GNum==1)
             {
                 ui->txtEWG2->append(QString::number(EWscores[loops]["trickScore"].toInt())) ;
             }else
             {
               ui->txtEWG3->append(QString::number(EWscores[loops]["trickScore"].toInt())) ;
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
        loops++;
    }
     //QJsonObject NSscores = scoresToDisplay["NSscores"].toObject();
    // QJsonObject EWscores = scoresToDisplay["EWscores"].toObject();

     //code to update gui
     //int NSScores2 = scoresToDisplay["NSscores"].toObject()["overtricks"].toInt();
    // ui->txtWeAbove1->setText(QString::number(NSScores2));
    // ui->txtWeAbove1->append("hello");
}

