#include "cogprocessor.h"
#include <QImageReader>
#include <QDebug>



CogProcessor::CogProcessor()
{

}

void CogProcessor::process( QString imgPath ){
    QImageReader qimr( imgPath );


    auto img = std::make_shared<QImage>( 1600,1200, QImage::Format_Mono );
    auto mask = std::make_shared<QImage>( 1600,1200, QImage::Format_RGB888 );

    qimr.read(img.get());

    std::vector<peaksBordersInColumn_t> peaksBorders;

    makeMaskNBorders( img, mask, peaksBorders);

    std::vector<pixPos_t> pixPos;
    calcCogPos( img, peaksBorders, pixPos );

    markFoundPixPos( mask, pixPos );

    emit ready( mask );

}

void CogProcessor::makeMaskNBorders(    ImageSharedPointer_t img,
                                        ImageSharedPointer_t mask,
                                        std::vector<peaksBordersInColumn_t>& peaksBorders ) const{

    auto width = img->width();
    auto height = img->height();



    for(auto i = 0; i < width; i++){//columns iteration
        size_t peakCnt = 0;
        peaksBordersInColumn_t borders = {
                                            {PEAK_BORDERS_EMPTY_VALUE, PEAK_BORDERS_EMPTY_VALUE},//0
                                            {PEAK_BORDERS_EMPTY_VALUE, PEAK_BORDERS_EMPTY_VALUE},//1
                                            {PEAK_BORDERS_EMPTY_VALUE, PEAK_BORDERS_EMPTY_VALUE},//2
                                            {PEAK_BORDERS_EMPTY_VALUE, PEAK_BORDERS_EMPTY_VALUE},//3
                                            {PEAK_BORDERS_EMPTY_VALUE, PEAK_BORDERS_EMPTY_VALUE},//4
                                         };

        for(auto j = 0; j < height; j++){//in column iteration
            QRgb pixColor = img->pixel(i,j);

            if( qGray( pixColor ) > 0){
                mask->setPixelColor( i, j, QColor(255,255,255).rgb() );
                borders[peakCnt].first = (borders[peakCnt].first == PEAK_BORDERS_EMPTY_VALUE) ? j : borders[peakCnt].first;
            }else{
                mask->setPixelColor( i, j, QColor(0,0,0).rgb() );

                if(borders[peakCnt].first != PEAK_BORDERS_EMPTY_VALUE && borders[peakCnt].second == PEAK_BORDERS_EMPTY_VALUE){
                    borders[peakCnt].second = j;
                }
                if( borders[peakCnt].first != PEAK_BORDERS_EMPTY_VALUE && peakCnt < (MAX_PEAKS_IN_COLUMN-1)){
                    peakCnt++;
                }
            }
        }
        peaksBorders.emplace_back(borders);
        if(peakCnt > 0 && false)
            qDebug() << "Col: " << i << ", PeakCnt : " << peakCnt << ", " << borders;

    }
}

void CogProcessor::calcCogPos( ImageSharedPointer_t img,
                               const std::vector<peaksBordersInColumn_t>& peaksBorders,
                               std::vector<pixPos_t>& pixPos ) const {


    for(auto columnNum = 0; columnNum < peaksBorders.size(); columnNum++){
        pixPos_t columnPixPos = {
                                    PIX_POS_ERROR_VALUE,
                                    PIX_POS_ERROR_VALUE,
                                    PIX_POS_ERROR_VALUE,
                                    PIX_POS_ERROR_VALUE,
                                    PIX_POS_ERROR_VALUE
                                };
        for(auto peaksNum = 0; peaksNum < peaksBorders[columnNum].size(); peaksNum++){
            pixPosVal_t cogSum = 0;
            pixPosVal_t cogWSum = 0;
            pixPosVal_t cogPos = PIX_POS_ERROR_VALUE;

            if( peaksBorders[columnNum][peaksNum].first != PEAK_BORDERS_EMPTY_VALUE &&
                    peaksBorders[columnNum][peaksNum].second != PEAK_BORDERS_EMPTY_VALUE){

                for (auto pixNum = peaksBorders[columnNum][peaksNum].first; pixNum < peaksBorders[columnNum][peaksNum].second; pixNum++) {
                    cogSum += qGray(img->pixel( columnNum, pixNum ));
                    cogWSum += qGray(img->pixel( columnNum, pixNum )) * pixNum * SUBPIX_MULT;

                }
                cogPos = cogWSum / cogSum;
            }

            columnPixPos[peaksNum] = cogPos;


        }
        pixPos.push_back( columnPixPos );
    }

}

void CogProcessor::markFoundPixPos(   ImageSharedPointer_t img,
                                      const std::vector<pixPos_t>& pixPos ) const{
    for(auto colNum  = 0; colNum < pixPos.size(); colNum++){
        for(auto pos : pixPos[colNum]){
            if(pos != PIX_POS_ERROR_VALUE){
                img->setPixelColor( colNum, pos/SUBPIX_MULT, QColor(255,0,0).rgb() );
            }

        }
    }
}


