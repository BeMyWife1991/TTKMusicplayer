#ifndef MUSICEQUALIZERDIALOG_H
#define MUSICEQUALIZERDIALOG_H

/* =================================================
 * This file is part of the Music Player project
 * Copyright (c) 2014 - 2015 Greedysky Studio
 * All rights reserved!
 * Redistribution and use of the source code or any derivative
 * works are strictly forbiden.
   =================================================*/

#include <QDialog>
#include <QMouseEvent>
#include "musicobject.h"
#include "musicmovedialogabstract.h"

namespace Ui {
class MusicEqualizerDialog;
}

class MUSIC_WIDGET_EXPORT MusicEqualizerDialog : public MusicMoveDialogAbstract
{
    Q_OBJECT
public:
    explicit MusicEqualizerDialog(QWidget *parent = 0);
    ~MusicEqualizerDialog();

signals:
    void setEqEffect(const MIntList &effect);
    void setEnaleEffect(bool enable);
    void setSpEqEffect(MusicObject::SpecialEQ eq);
    void resetEqEffect();

public slots:
    void setEqEnable();
    void resetEq();
    void verticalSliderChanged(int index);
    void eqChoiceIndexChanged(int index);
    void setMixedEffect(int index);
    void setEqualizerEffect(int index);
    virtual int exec();

protected:
    void init();
    void setControlEnable(bool enable) const;
    void readEqInformation();
    void writeEqInformation() const;
    void initEqualizeValue();
    void emitParameter();

    Ui::MusicEqualizerDialog *ui;
    bool m_eable;
    bool m_eqChoiceSelected;
    MIntList m_equalizeValue;

};

#endif // MUSICEQUALIZERDIALOG_H