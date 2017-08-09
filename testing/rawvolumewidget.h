#ifndef RAWVOLUMEWIDGET_H
#define RAWVOLUMEWIDGET_H

#include <QWidget>
#include<QDialog>
#include<QSlider>
#include<QPushButton>
#include<QGridLayout>
#include<QVBoxLayout>
#include<QHBoxLayout>
#include<QLabel>
#include<QGroupBox>
#include<QGridLayout>
#include<QLineEdit>
#include<QDialogButtonBox>
#include<QLineEdit>
#include<QSpinBox>
#include<QComboBox>
#include"glm/vec3.hpp"
#include"glm/matrix.hpp"
#include"glm/vec2.hpp"
class RawVolumeWidget :public QDialog // read raw data;
    {

        Q_OBJECT
    public:
        RawVolumeWidget(QWidget* parent, const QString& filename, std::string& objectModel, std::string& format, int& numFrames,
            glm::ivec3& dim, glm::vec3& spacing, int& headerSkip, bool& bigEndian, int fixedZDim = -1);
        ~RawVolumeWidget();

    protected:
        void resizeEvent(QResizeEvent *);

    private:
        QPushButton* submit_;
        QComboBox* datatypeComboBox_;
        QComboBox* objectModelComboBox_;
        QSpinBox* numTimeFramesSpin_;
        QSpinBox* headerSkipSpin_;
        QComboBox* endiannessCombo_;
        QSpinBox* xDimension_;
        QSpinBox* yDimension_;
        QSpinBox* zDimension_;
        QDoubleSpinBox* xSpacing_;
        QDoubleSpinBox* ySpacing_;
        QDoubleSpinBox* zSpacing_;

        std::string& objectModel_;
        std::string& format_;
        int& numFrames_;
        glm::ivec3& dim_;
        glm::vec3& spacing_;
        //glm::mat4& trafoMat_;
        //glm::mat4  tranfoMat; // what is this for?
        //QWidget* trafoMatWidget_;
        int& headerSkip_;
        bool& bigEndian_;

        private slots:
        void updateValues();
};



#endif // RAWVOLUMEWIDGET_H
