#ifndef COGPROCESSOR_H
#define COGPROCESSOR_H

#include <QObject>
#include <memory>


using pixPosVal_t = uint32_t;
const uint32_t MAX_PEAKS_IN_COLUMN = 5;
const uint32_t PEAK_BORDERS_EMPTY_VALUE = 0xFFFFFFFF;
const uint32_t SUBPIX_MULT = 32;
const uint32_t PIX_POS_ERROR_VALUE = 1300*32;



using ImageSharedPointer_t = std::shared_ptr<QImage>;
using peakBorders_t = std::pair<uint32_t, uint32_t>;//start, end
typedef std::vector<std::pair<uint32_t, uint32_t>> peaksBordersInColumn_t;


typedef std::vector<pixPosVal_t> pixPos_t;





class CogProcessor : public QObject
{
    Q_OBJECT

public:
    CogProcessor();


    signals:
    void ready( ImageSharedPointer_t pImg );

public slots:
    void process( QString );

private:
    void makeMaskNBorders(  ImageSharedPointer_t img,
                            ImageSharedPointer_t mask,
                            std::vector<peaksBordersInColumn_t>& peaksBorders ) const;
    void calcCogPos(        ImageSharedPointer_t img,
                            const std::vector<peaksBordersInColumn_t>& peaksBorders,
                            std::vector<pixPos_t>& pixPos ) const ;
    void markFoundPixPos(   ImageSharedPointer_t img,
                            const std::vector<pixPos_t>& pixPos ) const;
};

#endif // COGPROCESSOR_H
