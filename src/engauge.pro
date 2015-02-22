TEMPLATE    = app
CONFIG      = qt warn_on thread debug
OBJECTS_DIR = .objs
MOC_DIR = .moc
RCC_DIR = .rcc

HEADERS  += \
    include/BackgroundImage.h \
    Callback/CallbackAddPointsInCurvesGraphs.h \
    Callback/CallbackAxesCheckerFromAxesPoints.h \
    Callback/CallbackAxisPointsAbstract.h \
    Callback/CallbackCheckAddPointAxis.h \
    Callback/CallbackCheckEditPointAxis.h \
    Callback/CallbackRemovePointsInCurvesGraphs.h \
    Callback/CallbackSceneUpdateAfterCommand.h \
    Callback/CallbackSearchReturn.h \
    Callback/CallbackUpdateTransform.h \
    Checker/Checker.h \
    Checker/CheckerMode.h \
    Cmd/CmdAbstract.h \
    Cmd/CmdAddPointAxis.h \
    Cmd/CmdAddPointGraph.h \
    Cmd/CmdCopy.h \
    Cmd/CmdCut.h \
    Cmd/CmdDelete.h \
    Cmd/CmdEditPointAxis.h \
    Cmd/CmdFactory.h \
    Cmd/CmdMediator.h \
    Cmd/CmdMoveBy.h \
    Cmd/CmdPaste.h \
    Cmd/CmdSettingsAxesChecker.h \
    Cmd/CmdSettingsCoords.h \
    Cmd/CmdSettingsCurveProperties.h \
    Cmd/CmdSettingsCurves.h \
    Cmd/CmdSettingsExport.h \
    Cmd/CmdSettingsFilter.h \
    Cmd/CmdSettingsGridRemoval.h \
    Cmd/CmdSettingsPointMatch.h \
    Cmd/CmdSettingsSegments.h \
    include/ColorPalette.h \
    Coord/CoordScale.h \
    Coord/CoordsType.h \
    Coord/CoordThetaUnits.h \
    Correlation/Correlation.h \
    Curve/Curve.h \
    Curve/CurveConnectAs.h \
    Curve/CurveConstants.h \
    Curve/CurveFilter.h \
    Curve/CurveNameList.h \
    Curve/CurveNameListEntry.h \
    Curve/CurveSettingsInt.h \
    Curve/CurvesGraphs.h \
    Curve/CurveStyles.h \
    include/DataKey.h \
    DigitizeState/DigitizeStateAbstractBase.h \
    DigitizeState/DigitizeStateAxis.h \
    DigitizeState/DigitizeStateContext.h \
    DigitizeState/DigitizeStateColorPicker.h \
    DigitizeState/DigitizeStateCurve.h \
    DigitizeState/DigitizeStateEmpty.h \
    DigitizeState/DigitizeStatePointMatch.h \
    DigitizeState/DigitizeStateScale.h \
    DigitizeState/DigitizeStateSegment.h \
    DigitizeState/DigitizeStateSelect.h \
    Dlg/DlgAbout.h \
    Dlg/DlgEditPoint.h \
    Dlg/DlgFilterCommand.h \
    Dlg/DlgFilterThread.h \
    Dlg/DlgFilterWorker.h \
    Dlg/DlgSettingsAbstractBase.h \
    Dlg/DlgSettingsAxesChecker.h \
    Dlg/DlgSettingsCoords.h \
    Dlg/DlgSettingsCurves.h \
    Dlg/DlgSettingsCurveProperties.h \
    Dlg/DlgSettingsExport.h \
    Dlg/DlgSettingsFilter.h \
    Dlg/DlgSettingsGridRemoval.h \
    Dlg/DlgSettingsPointMatch.h \
    Dlg/DlgSettingsSegments.h \
    Dlg/DlgSpinBoxDouble.h \
    Dlg/DlgSpinBoxInt.h \
    Document/Document.h \
    Document/DocumentModelAbstractBase.h \
    Document/DocumentModelAxesChecker.h \
    Document/DocumentModelCoords.h \
    Document/DocumentModelExport.h \
    Document/DocumentModelFilter.h \
    Document/DocumentModelGridRemoval.h \
    Document/DocumentModelPointMatch.h \
    Document/DocumentModelSegments.h \
    Document/DocumentSerialize.h \
    include/EngaugeAssert.h \
    util/EnumsToQt.h \
    Export/ExportLayoutFunctions.h \
    Export/ExportPointsSelectionFunctions.h \
    Export/ExportPointsSelectionRelations.h \
    Export/ExportDelimiter.h \
    Export/ExportHeader.h \
    Export/ExportToClipboard.h \
    Export/ExportToFile.h \
    Filter/Filter.h \
    Filter/FilterColorEntry.h \
    Filter/FilterHistogram.h \
    Filter/FilterMode.h \
    Callback/functor.h \
    Graphics/GraphicsItemType.h \
    Graphics/GraphicsLine.h \
    Graphics/GraphicsLinesForCurve.h \
    Graphics/GraphicsLinesForCurves.h \
    Graphics/GraphicsPoint.h \
    Graphics/GraphicsPointAbstractBase.h \
    Graphics/GraphicsPointEllipse.h \
    Graphics/GraphicsPointFactory.h \
    Graphics/GraphicsPointPolygon.h \
    Graphics/GraphicsScene.h \
    Graphics/GraphicsView.h \
    Grid/GridClassifier.h \
    Grid/GridCoordDisable.h \
    Line/LineIdentifierToGraphicsItem.h \
    Line/LineStyle.h \
    Line/LineStyles.h \
    Load/LoadImageFromUrl.h \
    Logger/Logger.h \
    Logger/LoggerUpload.h \
    main/MainWindow.h \
    Mime/MimePoints.h \
    util/mmsubs.h \
    Point/Point.h \
    Point/PointIdentifiers.h \
    Point/PointIdentifierToGraphicsPoint.h \
    Point/PointShape.h \
    Point/PointStyle.h \
    Point/PointStyles.h \
    util/QtToString.h \
    Segment/Segment.h \
    Segment/SegmentFactory.h \
    Segment/SegmentLine.h \
    Settings/Settings.h \
    StatusBar/StatusBar.h \
    StatusBar/StatusBarMode.h \
    Transformation/Transformation.h \
    Transformation/TransformationStateAbstractBase.h \
    Transformation/TransformationStateContext.h \
    Transformation/TransformationStateDefined.h \
    Transformation/TransformationStateUndefined.h \
    include/VersionNumber.h \
    View/ViewPointStyle.h \
    View/ViewPreview.h \
    View/ViewProfile.h \
    View/ViewProfileDivider.h \
    View/ViewProfileParameters.h \
    View/ViewProfileScale.h \
    View/ViewSegmentFilter.h \
    util/Xml.h \
    include/ZoomFactor.h

SOURCES += \
    Callback/CallbackAddPointsInCurvesGraphs.cpp \
    Callback/CallbackAxesCheckerFromAxesPoints.cpp \
    Callback/CallbackAxisPointsAbstract.cpp \
    Callback/CallbackCheckAddPointAxis.cpp \
    Callback/CallbackCheckEditPointAxis.cpp \
    Callback/CallbackRemovePointsInCurvesGraphs.cpp \
    Callback/CallbackSceneUpdateAfterCommand.cpp \
    Callback/CallbackUpdateTransform.cpp \
    Checker/Checker.cpp \
    Cmd/CmdAbstract.cpp \
    Cmd/CmdAddPointAxis.cpp \
    Cmd/CmdAddPointGraph.cpp \
    Cmd/CmdCopy.cpp \
    Cmd/CmdCut.cpp \
    Cmd/CmdDelete.cpp \
    Cmd/CmdEditPointAxis.cpp \
    Cmd/CmdFactory.cpp \
    Cmd/CmdMediator.cpp \
    Cmd/CmdMoveBy.cpp \
    Cmd/CmdPaste.cpp \
    Cmd/CmdSettingsAxesChecker.cpp \
    Cmd/CmdSettingsCoords.cpp \
    Cmd/CmdSettingsCurveProperties.cpp \
    Cmd/CmdSettingsCurves.cpp \
    Cmd/CmdSettingsExport.cpp \
    Cmd/CmdSettingsFilter.cpp \
    Cmd/CmdSettingsGridRemoval.cpp \
    Cmd/CmdSettingsPointMatch.cpp \
    Cmd/CmdSettingsSegments.cpp \
    Correlation/Correlation.cpp \
    Curve/Curve.cpp \
    Curve/CurveFilter.cpp \
    Curve/CurveNameList.cpp \
    Curve/CurveNameListEntry.cpp \
    Curve/CurveSettingsInt.cpp \
    Curve/CurvesGraphs.cpp \
    Curve/CurveStyles.cpp \
    DigitizeState/DigitizeStateAbstractBase.cpp \
    DigitizeState/DigitizeStateAxis.cpp \
    DigitizeState/DigitizeStateColorPicker.cpp \
    DigitizeState/DigitizeStateContext.cpp \
    DigitizeState/DigitizeStateCurve.cpp \
    DigitizeState/DigitizeStateEmpty.cpp \
    DigitizeState/DigitizeStatePointMatch.cpp \
    DigitizeState/DigitizeStateScale.cpp \
    DigitizeState/DigitizeStateSegment.cpp \
    DigitizeState/DigitizeStateSelect.cpp \
    Dlg/DlgAbout.cpp \
    Dlg/DlgEditPoint.cpp \
    Dlg/DlgFilterCommand.cpp \
    Dlg/DlgFilterThread.cpp \
    Dlg/DlgFilterWorker.cpp \
    Dlg/DlgSettingsAbstractBase.cpp \
    Dlg/DlgSettingsAxesChecker.cpp \
    Dlg/DlgSettingsCoords.cpp \
    Dlg/DlgSettingsCurves.cpp \
    Dlg/DlgSettingsCurveProperties.cpp \
    Dlg/DlgSettingsExport.cpp \
    Dlg/DlgSettingsFilter.cpp \
    Dlg/DlgSettingsGridRemoval.cpp \
    Dlg/DlgSettingsPointMatch.cpp \
    Dlg/DlgSettingsSegments.cpp \
    Dlg/DlgSpinBoxDouble.cpp \
    Dlg/DlgSpinBoxInt.cpp \
    Document/Document.cpp \
    Document/DocumentModelAbstractBase.cpp \
    Document/DocumentModelAxesChecker.cpp \
    Document/DocumentModelCoords.cpp \
    Document/DocumentModelExport.cpp \
    Document/DocumentModelFilter.cpp \
    Document/DocumentModelGridRemoval.cpp \
    Document/DocumentModelPointMatch.cpp \
    Document/DocumentModelSegments.cpp \
    Document/DocumentSerialize.cpp \
    util/EnumsToQt.cpp \
    Export/ExportToClipboard.cpp \
    Export/ExportToFile.cpp \
    Filter/Filter.cpp \
    Filter/FilterHistogram.cpp \
    Graphics/GraphicsLine.cpp \
    Graphics/GraphicsLinesForCurve.cpp \
    Graphics/GraphicsLinesForCurves.cpp \
    Graphics/GraphicsPoint.cpp \
    Graphics/GraphicsPointAbstractBase.cpp \
    Graphics/GraphicsPointEllipse.cpp \
    Graphics/GraphicsPointFactory.cpp \
    Graphics/GraphicsPointPolygon.cpp \
    Graphics/GraphicsScene.cpp \
    Graphics/GraphicsView.cpp \
    Grid/GridClassifier.cpp \
    Line/LineStyle.cpp \
    Load/LoadImageFromUrl.cpp \
    Logger/Logger.cpp \
    Logger/LoggerUpload.cpp \
    main/MainWindow.cpp \
    Mime/MimePoints.cpp \
    util/mmsubs.cpp \
    Point/Point.cpp \
    Point/PointIdentifiers.cpp \
    Point/PointStyle.cpp \
    util/QtToString.cpp \
    Segment/Segment.cpp \
    Segment/SegmentFactory.cpp \
    Segment/SegmentLine.cpp \
    Settings/Settings.cpp \
    StatusBar/StatusBar.cpp \
    Transformation/Transformation.cpp \
    Transformation/TransformationStateAbstractBase.cpp \
    Transformation/TransformationStateContext.cpp \
    Transformation/TransformationStateDefined.cpp \
    Transformation/TransformationStateUndefined.cpp \
    View/ViewPointStyle.cpp \
    View/ViewPreview.cpp \
    View/ViewProfile.cpp \
    View/ViewProfileDivider.cpp \
    View/ViewProfileParameters.cpp \
    View/ViewProfileScale.cpp \
    View/ViewSegmentFilter.cpp \
    util/Xml.cpp

# Main entry point for non-test
SOURCES += main/main.cpp

TARGET = ../bin/engauge

QT += core gui network printsupport widgets xml

LIBS += -llog4cpp -lfftw3
INCLUDEPATH += Callback \
               Checker \
               Cmd \
               Coord \
               Correlation \
               Curve \
               DigitizeState \
               Dlg \
               Document \
               Export \
               Filter \
               Graphics \
               Grid \
               img \
               include \
               Line \
               Load \
               Logger \
               main \
               Mime \
               Plot \
               Point \
               Settings \
               StatusBar \
               Transformation \
               util \
               View

RESOURCES += \
    engauge.qrc
