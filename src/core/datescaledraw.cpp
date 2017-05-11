#include "datescaledraw.h"

DateScaleDraw::DateScaleDraw( const QTime &base ):
    baseTime( base )
{
    setLabelRotation( -45.0 );
}
QwtText DateScaleDraw::label( double v ) const
{
    return (QwtText) "12.12";
}