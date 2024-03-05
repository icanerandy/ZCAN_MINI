#ifndef CANVIEWOPTION_DIALOG_H
#define CANVIEWOPTION_DIALOG_H

#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

#include <QDialog>
#include "canframe_tablemodel.h"

namespace Ui {
class CanViewOptionDialog;
}

class CanViewOptionDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CanViewOptionDialog(QWidget *parent = 0);
    ~CanViewOptionDialog();

signals:
    void sig_visibleCol_changed(const QList<uint> visible_columns);

private:
    Ui::CanViewOptionDialog * const ui;
};

#endif // CANVIEWOPTION_DIALOG_H
