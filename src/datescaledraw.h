#ifndef DATESCALEDRAW_H
#define DATESCALEDRAW_H
#include "QTime"
#include "qwt_text.h"
#include "qwt_scale_draw.h"

class DateScaleDraw : public QwtScaleDraw
{
public:
    DateScaleDraw( const QTime &base );
    virtual QwtText label( double v ) const;

private:
    QTime baseTime;
};



#endif // DATESCALEDRAW_H
