/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the QtQuick module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 3 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL3 included in the
** packaging of this file. Please review the following information to
** ensure the GNU Lesser General Public License version 3 requirements
** will be met: https://www.gnu.org/licenses/lgpl-3.0.html.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 2.0 or (at your option) the GNU General
** Public license version 3 or any later version approved by the KDE Free
** Qt Foundation. The licenses are as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL2 and LICENSE.GPL3
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-2.0.html and
** https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef QSGCONTEXT_H
#define QSGCONTEXT_H

//
//  W A R N I N G
//  -------------
//
// This file is not part of the Qt API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.
//

#include <QtCore/QObject>
#include <QtCore/qabstractanimation.h>
#include <QtCore/QMutex>

#include <QtGui/QImage>
#include <QtGui/QSurfaceFormat>

#include <private/qtquickglobal_p.h>
#include <private/qrawfont_p.h>

#include <QtQuick/qsgnode.h>

QT_BEGIN_NAMESPACE

class QSGContextPrivate;
class QSGRectangleNode;
class QSGImageNode;
class QSGPainterNode;
class QSGGlyphNode;
class QSGNinePatchNode;
class QSGRenderer;
class QSGDistanceFieldGlyphCache;
class QQuickWindow;
class QSGTexture;
class QSGMaterial;
class QSGRenderLoop;
class QSGLayer;
class QQuickTextureFactory;
class QSGDistanceFieldGlyphCacheManager;
class QSGContext;
class QQuickPaintedItem;
class QSGRendererInterface;
class QSGShaderEffectNode;
class QSGGuiThreadShaderEffectManager;

Q_DECLARE_LOGGING_CATEGORY(QSG_LOG_TIME_RENDERLOOP)
Q_DECLARE_LOGGING_CATEGORY(QSG_LOG_TIME_COMPILATION)
Q_DECLARE_LOGGING_CATEGORY(QSG_LOG_TIME_TEXTURE)
Q_DECLARE_LOGGING_CATEGORY(QSG_LOG_TIME_GLYPH)
Q_DECLARE_LOGGING_CATEGORY(QSG_LOG_TIME_RENDERER)

Q_DECLARE_LOGGING_CATEGORY(QSG_LOG_INFO)
Q_DECLARE_LOGGING_CATEGORY(QSG_LOG_RENDERLOOP)

class Q_QUICK_PRIVATE_EXPORT QSGRenderContext : public QObject
{
    Q_OBJECT
public:
    enum CreateTextureFlags {
        CreateTexture_Alpha       = 0x1,
        CreateTexture_Atlas       = 0x2,
        CreateTexture_Mipmap      = 0x4
    };

    QSGRenderContext(QSGContext *context);
    virtual ~QSGRenderContext();

    QSGContext *sceneGraphContext() const { return m_sg; }
    virtual bool isValid() const { return true; }

    virtual void initialize(void *context);
    virtual void invalidate();
    virtual void renderNextFrame(QSGRenderer *renderer, uint fboId) = 0;
    virtual void endSync();

    virtual QSGDistanceFieldGlyphCache *distanceFieldGlyphCache(const QRawFont &font);
    QSGTexture *textureForFactory(QQuickTextureFactory *factory, QQuickWindow *window);

    virtual QSGTexture *createTexture(const QImage &image, uint flags = CreateTexture_Alpha) const = 0;
    virtual QSGRenderer *createRenderer() = 0;

    void registerFontengineForCleanup(QFontEngine *engine);

Q_SIGNALS:
    void initialized();
    void invalidated();

public Q_SLOTS:
    void textureFactoryDestroyed(QObject *o);

protected:
    QSGContext *m_sg;

    QMutex m_mutex;
    QHash<QQuickTextureFactory *, QSGTexture *> m_textures;
    QSet<QSGTexture *> m_texturesToDelete;
    QSGDistanceFieldGlyphCacheManager *m_distanceFieldCacheManager;

    QSet<QFontEngine *> m_fontEnginesToClean;
};


class Q_QUICK_PRIVATE_EXPORT QSGContext : public QObject
{
    Q_OBJECT

public:
    enum AntialiasingMethod {
        UndecidedAntialiasing,
        VertexAntialiasing,
        MsaaAntialiasing
    };

    explicit QSGContext(QObject *parent = 0);
    virtual ~QSGContext();

    virtual void renderContextInitialized(QSGRenderContext *renderContext);
    virtual void renderContextInvalidated(QSGRenderContext *renderContext);
    virtual QSGRenderContext *createRenderContext() = 0;

    QSGRectangleNode *createRectangleNode(const QRectF &rect, const QColor &c);
    virtual QSGRectangleNode *createRectangleNode() = 0;
    virtual QSGImageNode *createImageNode() = 0;
    virtual QSGPainterNode *createPainterNode(QQuickPaintedItem *item) = 0;
    virtual QSGGlyphNode *createGlyphNode(QSGRenderContext *rc, bool preferNativeGlyphNode) = 0;
    virtual QSGNinePatchNode *createNinePatchNode() = 0;
    virtual QSGLayer *createLayer(QSGRenderContext *renderContext) = 0;
    virtual QSGGuiThreadShaderEffectManager *createGuiThreadShaderEffectManager();
    virtual QSGShaderEffectNode *createShaderEffectNode(QSGRenderContext *renderContext,
                                                        QSGGuiThreadShaderEffectManager *mgr);
    virtual QAnimationDriver *createAnimationDriver(QObject *parent);

    virtual QSize minimumFBOSize() const;
    virtual QSurfaceFormat defaultSurfaceFormat() const = 0;

    virtual QSGRendererInterface *rendererInterface(QSGRenderContext *renderContext);

    static QSGContext *createDefaultContext();
    static QQuickTextureFactory *createTextureFactoryFromImage(const QImage &image);
    static QSGRenderLoop *createWindowManager();
};

QT_END_NAMESPACE

#endif // QSGCONTEXT_H
