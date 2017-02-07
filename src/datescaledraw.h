#ifndef DATESCALEDRAW_H
#define DATESCALEDRAW_H
#include "QTime.h"

class DateScaleDraw
{
public:
    DateScaleDraw( const QTime &base ):
        baseTime( base );
    virtual QwtText label( double v ) const;

private:
    QTime baseTime;
};

#endif // DATESCALEDRAW_H
