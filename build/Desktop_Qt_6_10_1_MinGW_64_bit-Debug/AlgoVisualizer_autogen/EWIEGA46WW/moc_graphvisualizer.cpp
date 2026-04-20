/****************************************************************************
** Meta object code from reading C++ file 'graphvisualizer.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.10.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../graphvisualizer.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'graphvisualizer.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 69
#error "This file was generated using the moc from 6.10.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {
struct qt_meta_tag_ZN15GraphVisualizerE_t {};
} // unnamed namespace

template <> constexpr inline auto GraphVisualizer::qt_create_metaobjectdata<qt_meta_tag_ZN15GraphVisualizerE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "GraphVisualizer",
        "requestEdgeValueInput",
        "",
        "QPoint",
        "pos",
        "edgeIndex",
        "requestAStarNodeInput",
        "clickPos",
        "enableGraphButtons",
        "disableGraphButtons",
        "setTimeElapsed",
        "time",
        "statusUpdated",
        "message",
        "processNextStep",
        "updateTimeElapsed"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'requestEdgeValueInput'
        QtMocHelpers::SignalData<void(const QPoint &, int)>(1, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 3, 4 }, { QMetaType::Int, 5 },
        }}),
        // Signal 'requestAStarNodeInput'
        QtMocHelpers::SignalData<void(const QPoint &)>(6, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 3, 7 },
        }}),
        // Signal 'enableGraphButtons'
        QtMocHelpers::SignalData<void()>(8, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'disableGraphButtons'
        QtMocHelpers::SignalData<void()>(9, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'setTimeElapsed'
        QtMocHelpers::SignalData<void(int)>(10, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 11 },
        }}),
        // Signal 'statusUpdated'
        QtMocHelpers::SignalData<void(const QString &)>(12, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 13 },
        }}),
        // Slot 'processNextStep'
        QtMocHelpers::SlotData<void()>(14, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'updateTimeElapsed'
        QtMocHelpers::SlotData<void()>(15, 2, QMC::AccessPrivate, QMetaType::Void),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<GraphVisualizer, qt_meta_tag_ZN15GraphVisualizerE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject GraphVisualizer::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN15GraphVisualizerE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN15GraphVisualizerE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN15GraphVisualizerE_t>.metaTypes,
    nullptr
} };

void GraphVisualizer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<GraphVisualizer *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->requestEdgeValueInput((*reinterpret_cast<std::add_pointer_t<QPoint>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<int>>(_a[2]))); break;
        case 1: _t->requestAStarNodeInput((*reinterpret_cast<std::add_pointer_t<QPoint>>(_a[1]))); break;
        case 2: _t->enableGraphButtons(); break;
        case 3: _t->disableGraphButtons(); break;
        case 4: _t->setTimeElapsed((*reinterpret_cast<std::add_pointer_t<int>>(_a[1]))); break;
        case 5: _t->statusUpdated((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1]))); break;
        case 6: _t->processNextStep(); break;
        case 7: _t->updateTimeElapsed(); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (GraphVisualizer::*)(const QPoint & , int )>(_a, &GraphVisualizer::requestEdgeValueInput, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (GraphVisualizer::*)(const QPoint & )>(_a, &GraphVisualizer::requestAStarNodeInput, 1))
            return;
        if (QtMocHelpers::indexOfMethod<void (GraphVisualizer::*)()>(_a, &GraphVisualizer::enableGraphButtons, 2))
            return;
        if (QtMocHelpers::indexOfMethod<void (GraphVisualizer::*)()>(_a, &GraphVisualizer::disableGraphButtons, 3))
            return;
        if (QtMocHelpers::indexOfMethod<void (GraphVisualizer::*)(int )>(_a, &GraphVisualizer::setTimeElapsed, 4))
            return;
        if (QtMocHelpers::indexOfMethod<void (GraphVisualizer::*)(const QString & )>(_a, &GraphVisualizer::statusUpdated, 5))
            return;
    }
}

const QMetaObject *GraphVisualizer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *GraphVisualizer::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN15GraphVisualizerE_t>.strings))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int GraphVisualizer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void GraphVisualizer::requestEdgeValueInput(const QPoint & _t1, int _t2)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 0, nullptr, _t1, _t2);
}

// SIGNAL 1
void GraphVisualizer::requestAStarNodeInput(const QPoint & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 1, nullptr, _t1);
}

// SIGNAL 2
void GraphVisualizer::enableGraphButtons()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void GraphVisualizer::disableGraphButtons()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void GraphVisualizer::setTimeElapsed(int _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 4, nullptr, _t1);
}

// SIGNAL 5
void GraphVisualizer::statusUpdated(const QString & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 5, nullptr, _t1);
}
QT_WARNING_POP
