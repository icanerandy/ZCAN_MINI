#ifndef PLOT_DOCKWIDGET_H
#define PLOT_DOCKWIDGET_H

#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

#include <QObject>
#include <QMap>
#include <QDockWidget>
#include <QMouseEvent>
#include <QDialog>
#include <cmath>
#include "Eigen/Core"
#include "Eigen/Dense"
#include "zlgcan.h"
#include "Vector/DBC.h"
#include "qcustomplot.h"
#include "lineplot.h"
#include "linereplot.h"
#include "deviationplot.h"
#include "deviationreplot.h"
#include "distribution_dialog.h"

#include "xlsxdocument.h"
#include "xlsxchartsheet.h"
#include "xlsxcellrange.h"
#include "xlsxchart.h"
#include "xlsxrichstring.h"
#include "xlsxworkbook.h"

#include <GL/freeglut.h>


namespace Ui {
class SpeedViewDockWidget;
}

class SpeedViewDockWidget : public QDockWidget
{
    Q_OBJECT

public:
    explicit SpeedViewDockWidget(QWidget *parent = 0);
    ~SpeedViewDockWidget();

private:
    void init_ui();
    void bind_signals();
    void init_plot(QCustomPlot* const plot);
    void add_graphs(QCustomPlot* const plot, int graph_count);
    void init_thread();
    void destroy_thread();
    double cal_max_error(std::vector<double>& tmp_vec1, std::vector<double>& tmp_vec2);
    double cal_mean_error(std::vector<double>& tmp_vec1, std::vector<double>& tmp_vec2);
    double cal_correlation_coefficient(std::vector<double> &tmp_vec1, std::vector<double> &tmp_vec2);
    double cal_RMSE(std::vector<double> &tmp_vec1, std::vector<double> &tmp_vec2);

public slots:
    void slot_paint_enable(QList<QPair<uint32_t, Vector::DBC::Signal>> sig_lst);
    void slot_selectionChanged();
    void slot_btnPaint_clicked(bool paint_enable);
    void slot_clearData();
    void slot_disSigVal_changed(double value);
    void slot_btnShowDis();
    bool slot_btnSavePic_clicked();
    void slot_btnSaveExcel_clicked();

private:
    Ui::SpeedViewDockWidget* const ui;
    DistributionDialog* distribution_dialog_;

    QList< QPair<uint32_t, Vector::DBC::Signal> > sig_lst_;

    SignalParser* signal_parser_;
    LinePlot* line_plot_;
    LineReplot* line_replot_;
    DeviationPlot* deviation_plot_;
    DeviationReplot* deviation_replot_;

    QThread* signal_parser_thread_;
    QThread* line_plot_thread_;
    QThread* line_replot_thread_;
    QThread* deviation_plot_thread_;
    QThread* deviation_replot_thread_;

    double default_deviation_value_;
};

#endif // PLOT_DOCKWIDGET_H
