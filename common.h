#ifndef COMMON_H
#define COMMON_H
#include <memory>
#include <QThread>
#include <QImage>
#include <QQueue>
#include <QDebug>


using ImageSharedPointer_t = std::shared_ptr<QImage>;
Q_DECLARE_METATYPE( ImageSharedPointer_t );


using ImgQueue_t = QQueue<ImageSharedPointer_t>;
using ImgQueueSharedPointer_t = std::shared_ptr<ImgQueue_t>;


#endif // COMMON_H
