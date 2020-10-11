#ifndef lightly_helper_h
#define lightly_helper_h

/*************************************************************************
 * Copyright (C) 2014 by Hugo Pereira Da Costa <hugo.pereira@free.fr>    *
 *                                                                       *
 * This program is free software; you can redistribute it and/or modify  *
 * it under the terms of the GNU General Public License as published by  *
 * the Free Software Foundation; either version 2 of the License, or     *
 * (at your option) any later version.                                   *
 *                                                                       *
 * This program is distributed in the hope that it will be useful,       *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 * GNU General Public License for more details.                          *
 *                                                                       *
 * You should have received a copy of the GNU General Public License     *
 * along with this program; if not, write to the                         *
 * Free Software Foundation, Inc.,                                       *
 * 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA .        *
 *************************************************************************/


#include "lightly.h"
#include "lightlyanimationdata.h"
#include "config-lightly.h"

#include <KColorScheme>
#include <KSharedConfig>

#include <QPainterPath>
#include <QIcon>
#include <QWidget>

namespace Lightly
{

    //* lightly style helper class.
    /** contains utility functions used at multiple places in both lightly style and lightly window decoration */
    class Helper
    {
        public:

        //* constructor
        explicit Helper( KSharedConfig::Ptr );

        //* destructor
        virtual ~Helper()
        {}

        //* load configuration
        virtual void loadConfig();

        //* pointer to shared config
        KSharedConfig::Ptr config() const;

        //*@name color utilities
        //@{

        //* add alpha channel multiplier to color
        QColor alphaColor( QColor color, qreal alpha ) const;

        //* mouse over color
        QColor hoverColor( const QPalette& palette ) const
        { return _viewHoverBrush.brush( palette ).color(); }

        //* focus color
        QColor focusColor( const QPalette& palette ) const
        { return _viewFocusBrush.brush( palette ).color(); }

        //* negative text color (used for close button)
        QColor negativeText( const QPalette& palette ) const
        { return _viewNegativeTextBrush.brush( palette ).color(); }

        //* shadow
        QColor shadowColor( const QPalette& palette ) const
        { return alphaColor( palette.color( QPalette::Shadow ), 0.15 ); }

        //* titlebar color
        const QColor& titleBarColor( bool active ) const
        { return active ? _activeTitleBarColor:_inactiveTitleBarColor; }

        //* titlebar text color
        const QColor& titleBarTextColor( bool active ) const
        { return active ? _activeTitleBarTextColor:_inactiveTitleBarTextColor; }

        //* frame outline color, using animations
        QColor frameOutlineColor( const QPalette&, bool mouseOver = false, bool hasFocus = false, qreal opacity = AnimationData::OpacityInvalid, AnimationMode = AnimationNone ) const;


        //* hover outline color, using animations
        QColor hoverOutlineColor( const QPalette& ) const;

        //* focus outline color, using animations
        QColor buttonFocusOutlineColor( const QPalette& ) const;

        //* hover outline color, using animations
        QColor buttonHoverOutlineColor( const QPalette& ) const;

        //* side panel outline color, using animations
        QColor sidePanelOutlineColor( const QPalette&, bool hasFocus = false, qreal opacity = AnimationData::OpacityInvalid, AnimationMode = AnimationNone ) const;

        //* frame background color
        QColor frameBackgroundColor( const QPalette& palette ) const
        { return frameBackgroundColor( palette, palette.currentColorGroup() ); }

        //* frame background color
        QColor frameBackgroundColor( const QPalette&, QPalette::ColorGroup ) const;

        //* arrow outline color
        QColor arrowColor( const QPalette&, QPalette::ColorGroup, QPalette::ColorRole ) const;

        //* arrow outline color
        QColor arrowColor( const QPalette& palette, QPalette::ColorRole role ) const
        { return arrowColor( palette, palette.currentColorGroup(), role ); }

        //* arrow outline color, using animations
        QColor arrowColor( const QPalette&, bool mouseOver, bool hasFocus, qreal opacity = AnimationData::OpacityInvalid, AnimationMode = AnimationNone ) const;

        //* button outline color, using animations
        QColor buttonOutlineColor( const QPalette&, bool mouseOver, bool hasFocus, qreal opacity = AnimationData::OpacityInvalid, AnimationMode = AnimationNone ) const;

        //* button panel color, using animations
        QColor buttonBackgroundColor( const QPalette&, bool mouseOver, bool hasFocus, bool sunken, qreal opacity = AnimationData::OpacityInvalid, AnimationMode = AnimationNone ) const;

        //* tool button color
        QColor toolButtonColor( const QPalette&, bool mouseOver, bool hasFocus, bool sunken, qreal opacity = AnimationData::OpacityInvalid, AnimationMode = AnimationNone ) const;

        //* slider outline color, using animations
        QColor sliderOutlineColor( const QPalette&, bool mouseOver, bool hasFocus, qreal opacity = AnimationData::OpacityInvalid, AnimationMode = AnimationNone ) const;

        //* scrollbar handle color, using animations
        QColor scrollBarHandleColor( const QPalette&, bool mouseOver, bool hasFocus, qreal opacity = AnimationData::OpacityInvalid, AnimationMode = AnimationNone ) const;

        //* checkbox indicator, using animations
        QColor checkBoxIndicatorColor( const QPalette&, bool mouseOver, bool active, qreal opacity = AnimationData::OpacityInvalid, AnimationMode = AnimationNone ) const;

        //* separator color
        QColor separatorColor( const QPalette& ) const;

        //* merge active and inactive palettes based on ratio, for smooth enable state change transition
        QPalette disabledPalette( const QPalette&, qreal ratio ) const;

        //@}

        //*@name rendering utilities
        //@{

        //* debug frame
        void renderDebugFrame( QPainter*, const QRect& ) const;

        //* focus line
        void renderFocusLine( QPainter*, const QRect&, const QColor& ) const;

        //* generic frame
        void renderFrame( QPainter*, const QRect&, const QColor& color, const QPalette& palette, const QColor& outline = QColor(), const bool enabled = true ) const;

        //* side panel frame
        void renderSidePanelFrame( QPainter*, const QRect&, const QColor& outline, Side ) const;

        //* menu frame
        void renderMenuFrame( QPainter*, const QRect&, const QColor& color, const QColor& outline, bool roundCorners = true ) const;
        
        //* shadow for rounded (or not) rectangles
        void renderRectShadow(QPainter*, const QRectF&, QColor color, const int size, const float param1, const float param2, const int xOffset, const int yOffset, const int radius, const bool outline = false, const int outlineStrength = 0 ) const;
        
        QPixmap renderRectShadow( const QPixmap& mask, const QRectF&, QColor color, const int size, const float param1, const float param2, const int xOffset, const int yOffset, const int radius, const bool outline = false, const int outlineStrength = 0 ) const;
        
        //* shadow for ellipses
        void renderEllipseShadow(QPainter*, const QRectF&, QColor color, const int size, const float param1, const float param2, const int xOffset, const int yOffset, const bool outline = false, const int outlineStrength = 0 ) const;
        
        //* button frame
        void renderButtonFrame( QPainter*, const QRect&, const QColor& color, const QPalette& palette, const bool focus, const bool sunken, const bool mouseOver, const bool enabled ) const;

        //* toolbutton frame
        void renderToolButtonFrame( QPainter*, const QRect&, const QColor& color, bool sunken ) const;

        //* toolbutton frame
        void renderToolBoxFrame( QPainter*, const QRect&, int tabWidth, const QColor& color ) const;

        //* tab widget frame
        void renderTabWidgetFrame( QPainter*, const QRect&, const QColor& color, const QColor& outline, Corners ) const;

        //* selection frame
        void renderSelection( QPainter*, const QRect&, const QColor&, const bool rounded = false ) const;

        //* separator
        void renderSeparator( QPainter*, const QRect&, const QColor&, bool vertical = false ) const;

        //* checkbox
        void renderCheckBoxBackground( QPainter*, const QRect&, const QColor& color, bool sunken ) const;
        
        //* line edit
        void renderLineEdit( QPainter*, const QRect&, const QColor& background, const QColor& outline, const bool hasFocus, const bool mouseOver, const bool enabled ) const;
        
        //* group box
        void renderGroupBox( QPainter*, const QRect&, const QColor& color, const bool mouseOver ) const;

        //* checkbox
        void renderCheckBox( QPainter*, const QRect&, const QColor& color, const QColor& background, const QColor& shadow, bool sunken, const bool mouseOver, CheckBoxState state, qreal animation = AnimationData::OpacityInvalid ) const;

        //* radio button
        void renderRadioButtonBackground( QPainter*, const QRect&, const QColor& color, bool sunken ) const;

        //* radio button
        void renderRadioButton( QPainter*, const QRect&, const QColor& color, const QColor& background, const bool mouseOver, bool sunken, RadioButtonState state, qreal animation = AnimationData::OpacityInvalid ) const;

        //* slider groove
        void renderSliderGroove( QPainter*, const QRect&, const QColor& ) const;

        //* slider handle
        void renderSliderHandle( QPainter*, const QRect&, const QColor&, const bool focus, bool sunken ) const;

        //* dial groove
        void renderDialGroove( QPainter*, const QRect&, const QColor&, qreal first, qreal last ) const;

        //* dial groove
        void renderDialContents( QPainter*, const QRect&, const QColor&, qreal first, qreal second ) const;

        //* progress bar groove
        void renderProgressBarGroove( QPainter*, const QRect&, const QColor& ) const;

        //* progress bar contents
        void renderProgressBarContents( QPainter* painter, const QRect& rect, const QColor& color ) const
        { return renderProgressBarGroove( painter, rect, color ); }

        //* progress bar contents (animated)
        void renderProgressBarBusyContents( QPainter* painter, const QRect& rect, const QColor& first, const QColor& second, bool horizontal, bool reverse, int progress  ) const;

        //* scrollbar groove
        void renderScrollBarGroove( QPainter* painter, const QRect& rect, const QColor& color ) const
        { return renderScrollBarHandle( painter, rect, color ); }

        //* scrollbar handle
        void renderScrollBarHandle( QPainter*, const QRect&, const QColor& ) const;

        //* toolbar handle
        void renderToolBarHandle( QPainter* painter, const QRect& rect, const QColor& color ) const
        { return renderProgressBarGroove( painter, rect, color ); }

        //* separator between scrollbar and contents
        void renderScrollBarBorder( QPainter*, const QRect&, const QColor& ) const;

        //* tabbar tab
        void renderTabBarTab( QPainter*, const QRect&, const QColor& color, const QColor& outline, Corners ) const;

        //* generic arrow
        void renderArrow( QPainter*, const QRect&, const QColor&, ArrowOrientation ) const;

        //* generic button (for mdi decorations, tabs and dock widgets)
        void renderDecorationButton( QPainter*, const QRect&, const QColor&, ButtonType, bool inverted ) const;

        //* generic shadow for rounded rectangles
        void renderRoundedRectShadow ( QPainter*, const QRectF&, const QColor&, qreal radius = Metrics::Frame_FrameRadius - 0.5 ) const;
        
        //* generic shadow for ellipses
        void renderEllipseShadow( QPainter*, const QRectF&, const QColor& ) const;
        
        //@}

        //*@name compositing utilities
        //@{

        //* true if style was compiled for and is running on X11
        static bool isX11();

        //* true if running on platform Wayland
        static bool isWayland();

        //* returns true if compositing is active
        bool compositingActive() const;

        //* returns true if a given widget supports alpha channel
        bool hasAlphaChannel( const QWidget* ) const;
        
        //* returns true if the window should have an alpha channel
        bool shouldWindowHaveAlpha( const QPalette&, bool isDolphin ) const;
        
        //* returns true if a given palette has dark colors 
        bool isDarkTheme( const QPalette& palette) const
        { return qGray( palette.color( QPalette::Window ).rgb() ) > 110 ? false : true; }
        

        //@}

        //* return device pixel ratio for a given pixmap
        virtual qreal devicePixelRatio( const QPixmap& ) const;

        //* frame radius
        constexpr qreal frameRadius( const int penWidth = PenWidth::NoPen, const qreal bias = 0 ) const
        { return qMax( Metrics::Frame_FrameRadius - (0.5 * penWidth) + bias, 0.0 ); }
        
        //* frame radius with new pen width
        constexpr qreal frameRadiusForNewPenWidth( const qreal oldRadius, const int penWidth ) const
        { return qMax( oldRadius - (0.5 * penWidth), 0.0 ); }
        
        //* return a QRectF with the appropriate size for a rectangle with a pen stroke
        QRectF strokedRect( const QRectF &rect, const int penWidth = PenWidth::Frame ) const;
        
        //* return a QRectF with the appropriate size for a rectangle with a pen stroke
        QRectF strokedRect( const QRect &rect, const int penWidth = PenWidth::Frame ) const;
        
        QPixmap coloredIcon(const QIcon &icon, const QPalette& palette, const QSize &size,
                            QIcon::Mode mode = QIcon::Normal, QIcon::State state = QIcon::Off);

        //protected:

        //* return rounded path in a given rect, with only selected corners rounded, and for a given radius
        QPainterPath roundedPath( const QRectF&, Corners, qreal ) const;

        private:

        //* configuration
        KSharedConfig::Ptr _config;

        //*@name brushes
        //@{
        KStatefulBrush _viewFocusBrush;
        KStatefulBrush _viewHoverBrush;
        KStatefulBrush _viewNegativeTextBrush;
        //@}

        //*@name windeco colors
        //@{
        QColor _activeTitleBarColor;
        QColor _activeTitleBarTextColor;
        QColor _inactiveTitleBarColor;
        QColor _inactiveTitleBarTextColor;
        //@}

    };

}

#endif
