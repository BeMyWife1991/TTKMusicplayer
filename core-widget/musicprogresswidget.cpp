#include "musicprogresswidget.h"
#include "musicbgthememanager.h"
#include "musicuiobject.h"

#include <QPainter>
#include <QLabel>
#include <QToolButton>
#include <QProgressBar>

MusicProgressWidget::MusicProgressWidget(QWidget *parent)
    : QProgressDialog(parent)
{
    setModal(true);
    setWindowFlags( Qt::Window | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    setWindowModality(Qt::ApplicationModal);
    setAttribute(Qt::WA_TranslucentBackground, true);
    setCancelButton(NULL);
    setLabel(NULL);
    setFixedSize(400, 155);

    initWidget();
}

MusicProgressWidget::~MusicProgressWidget()
{
    delete m_background;
    delete m_textLabel;
    delete m_progressBar;
}

void MusicProgressWidget::initWidget()
{
    m_background = new QLabel(this);
    m_background->setGeometry(20, 20, 360, 115);
    QWidget *backgroundMask = new QWidget(this);
    backgroundMask->setGeometry(20, 45, 360, 90);
    backgroundMask->setStyleSheet("background:rgba(255,255,255,200);");

    QLabel *topTitleName = new QLabel(this);
    topTitleName->setText(tr("Progress Bar"));
    topTitleName->setGeometry(30, 20, 221, 25);
    topTitleName->setStyleSheet("color:#FFFFFF;font-weight:bold;");

    QToolButton *topTitleCloseButton = new QToolButton(this);
    topTitleCloseButton->setGeometry(360, 22, 20, 20);
    topTitleCloseButton->setIcon(QIcon(":/share/searchclosed"));
    topTitleCloseButton->setStyleSheet(MusicUIObject::MToolButtonStyle03);
    topTitleCloseButton->setEnabled(false);

    m_progressBar = new QProgressBar(this);
    setBar(m_progressBar);
    m_progressBar->setStyleSheet(MusicUIObject::MProgressBar01);

    m_textLabel = new QLabel(this);
    m_textLabel->setAlignment(Qt::AlignCenter);
    m_textLabel->setGeometry(40, 50, 320, 25);
}

void MusicProgressWidget::setTitle(const QString &name)
{
    m_textLabel->setText(name);
}

void MusicProgressWidget::resizeEvent(QResizeEvent *)
{
    m_progressBar->setGeometry(40, 85, 320, 25);
}

void MusicProgressWidget::paintEvent(QPaintEvent *event)
{
    QDialog::paintEvent(event);
    QPainter painter(this);

    painter.drawPixmap(0, 0, WIDTH_S, HEIGHT_S, QPixmap(":/shadow/corner1"));
    painter.drawPixmap(width() - WIDTH_S, 0, WIDTH_S, HEIGHT_S, QPixmap(":/shadow/corner2"));
    painter.drawPixmap(0, height() - HEIGHT_S, WIDTH_S, HEIGHT_S, QPixmap(":/shadow/corner3"));
    painter.drawPixmap(width() - WIDTH_S, height() - HEIGHT_S, WIDTH_S, HEIGHT_S, QPixmap(":/shadow/corner4"));

    painter.drawPixmap(0, WIDTH_S, HEIGHT_S, height() - 2*WIDTH_S,
                       QPixmap(":/shadow/left").scaled(WIDTH_S, height() - 2*HEIGHT_S));
    painter.drawPixmap(width() - WIDTH_S, WIDTH_S, HEIGHT_S, height() - 2*HEIGHT_S,
                       QPixmap(":/shadow/right").scaled(WIDTH_S, height() - 2*HEIGHT_S));
    painter.drawPixmap(HEIGHT_S, 0, width() - 2*WIDTH_S, HEIGHT_S,
                       QPixmap(":/shadow/top").scaled(width() - 2*WIDTH_S, HEIGHT_S));
    painter.drawPixmap(WIDTH_S, height() - HEIGHT_S, width() - 2*WIDTH_S, HEIGHT_S,
                       QPixmap(":/shadow/bottom").scaled(width() - 2*WIDTH_S, HEIGHT_S));
}

void MusicProgressWidget::show()
{
    QPixmap pix(M_BG_MANAGER->getMBackground());
    m_background->setPixmap(pix.scaled( size() ));
    QProgressDialog::show();
}
