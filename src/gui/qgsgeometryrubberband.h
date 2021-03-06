/***************************************************************************
                         qgsgeometryrubberband.h
                         -----------------------
    begin                : December 2014
    copyright            : (C) 2014 by Marco Hugentobler
    email                : marco at sourcepole dot ch
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef QGSGEOMETRYRUBBERBAND_H
#define QGSGEOMETRYRUBBERBAND_H

#include "qgsmapcanvasitem.h"
#include <QBrush>
#include <QPen>
#include "qgis_gui.h"


class QgsAbstractGeometry;
class QgsPointV2;
struct QgsVertexId;

/** \ingroup gui
 * A rubberband class for QgsAbstractGeometry (considering curved geometries)*/
class GUI_EXPORT QgsGeometryRubberBand: public QgsMapCanvasItem
{
  public:
    enum IconType
    {

      /**
      * No icon is used
      */
      ICON_NONE,

      /**
       * A cross is used to highlight points (+)
       */
      ICON_CROSS,

      /**
       * A cross is used to highlight points (x)
       */
      ICON_X,

      /**
       * A box is used to highlight points (□)
       */
      ICON_BOX,

      /**
       * A circle is used to highlight points (○)
       */
      ICON_CIRCLE,

      /**
       * A full box is used to highlight points (■)
       */
      ICON_FULL_BOX
    };

    QgsGeometryRubberBand( QgsMapCanvas* mapCanvas, QgsWkbTypes::GeometryType geomType = QgsWkbTypes::LineGeometry );
    ~QgsGeometryRubberBand();

    //! Sets geometry (takes ownership). Geometry is expected to be in map coordinates
    void setGeometry( QgsAbstractGeometry* geom );
    //! Returns a pointer to the geometry
    const QgsAbstractGeometry* geometry() { return mGeometry; }
    //! Moves vertex to new position (in map coordinates)
    void moveVertex( QgsVertexId id, const QgsPointV2& newPos );
    //! Sets fill color for vertex markers
    void setFillColor( const QColor& c );
    //! Sets outline color for vertex markers
    void setOutlineColor( const QColor& c );
    //! Sets outline width
    void setOutlineWidth( int width );
    //! Sets pen style
    void setLineStyle( Qt::PenStyle penStyle );
    //! Sets brush style
    void setBrushStyle( Qt::BrushStyle brushStyle );
    //! Sets vertex marker icon type
    void setIconType( IconType iconType ) { mIconType = iconType; }

  protected:
    virtual void paint( QPainter* painter ) override;

  private:
    QgsAbstractGeometry* mGeometry = nullptr;
    QBrush mBrush;
    QPen mPen;
    int mIconSize;
    IconType mIconType;
    QgsWkbTypes::GeometryType mGeometryType;

    void drawVertex( QPainter* p, double x, double y );
    QgsRectangle rubberBandRectangle() const;
};

#endif // QGSGEOMETRYRUBBERBAND_H
