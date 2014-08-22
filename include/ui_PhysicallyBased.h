/********************************************************************************
** Form generated from reading UI file 'PhysicallyBased.ui'
**
** Created by: Qt User Interface Compiler version 4.8.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PHYSICALLYBASED_H
#define UI_PHYSICALLYBASED_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDockWidget>
#include <QtGui/QFrame>
#include <QtGui/QHeaderView>
#include <QtGui/QPushButton>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PhysBDock
{
public:
    QWidget *dockWidgetContents;
    QPushButton *physBButton;
    QFrame *line;
    QFrame *line_2;

    void setupUi(QDockWidget *PhysBDock)
    {
        if (PhysBDock->objectName().isEmpty())
            PhysBDock->setObjectName(QString::fromUtf8("PhysBDock"));
        PhysBDock->resize(892, 200);
        PhysBDock->setMinimumSize(QSize(199, 200));
        PhysBDock->setFeatures(QDockWidget::NoDockWidgetFeatures);
        dockWidgetContents = new QWidget();
        dockWidgetContents->setObjectName(QString::fromUtf8("dockWidgetContents"));
        physBButton = new QPushButton(dockWidgetContents);
        physBButton->setObjectName(QString::fromUtf8("physBButton"));
        physBButton->setGeometry(QRect(640, 100, 241, 60));
        physBButton->setMinimumSize(QSize(175, 60));
        QFont font;
        font.setPointSize(12);
        font.setBold(true);
        font.setWeight(75);
        physBButton->setFont(font);
        line = new QFrame(dockWidgetContents);
        line->setObjectName(QString::fromUtf8("line"));
        line->setGeometry(QRect(270, 10, 20, 161));
        line->setFrameShape(QFrame::VLine);
        line->setFrameShadow(QFrame::Sunken);
        line_2 = new QFrame(dockWidgetContents);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        line_2->setGeometry(QRect(620, 10, 20, 161));
        line_2->setFrameShape(QFrame::VLine);
        line_2->setFrameShadow(QFrame::Sunken);
        PhysBDock->setWidget(dockWidgetContents);

        retranslateUi(PhysBDock);

        QMetaObject::connectSlotsByName(PhysBDock);
    } // setupUi

    void retranslateUi(QDockWidget *PhysBDock)
    {
        PhysBDock->setWindowTitle(QApplication::translate("PhysBDock", "Physically Based Modeling", 0, QApplication::UnicodeUTF8));
        physBButton->setText(QApplication::translate("PhysBDock", "Physically Based Modeling", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class PhysBDock: public Ui_PhysBDock {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PHYSICALLYBASED_H
