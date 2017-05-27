#include "datescaledraw.h"

DateScaleDraw::DateScaleDraw( const QTime &base ):
    baseTime( base )
{
    setLabelRotation( -45.0 );
}
QwtText DateScaleDraw::label( double v ) const
{
    int year = v / 10000;
    int month = (v - year * 10000) / 100;
    int day = v - year * 10000 - month * 100;
    qDebug() << day;
    char* result = new char[256];
    sprintf(result, "%d.%d.%d", day, month, year);
    return (QwtText) result;
}
