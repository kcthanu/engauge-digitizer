#include "CallbackAddPointsInCurvesGraphs.h"
#include "CallbackCheckAddPointAxis.h"
#include "CallbackCheckEditPointAxis.h"
#include "CallbackNextOrdinal.h"
#include "CallbackRemovePointsInCurvesGraphs.h"
#include "Curve.h"
#include "CurvesGraphs.h"
#include "CurveStyles.h"
#include "Document.h"
#include "DocumentSerialize.h"
#include "EngaugeAssert.h"
#include "EnumsToQt.h"
#include <iostream>
#include "Logger.h"
#include "OrdinalGenerator.h"
#include "Point.h"
#include <QByteArray>
#include <QDataStream>
#include <QDebug>
#include <QFile>
#include <QImage>
#include <QtToString.h>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include "SettingsForGraph.h"
#include "Transformation.h"
#include "Version.h"
#include "Xml.h"

const int FOUR_BYTES = 4;

Document::Document (unsigned int numberCoordSystem,
                    const QImage &image) :
  m_coordSystemContext (numberCoordSystem),
  m_name ("untitled")
{
  LOG4CPP_INFO_S ((*mainCat)) << "Document::Document"
                              << " numberCoordSystem=" << numberCoordSystem
                              << " image=" << image.width() << "x" << image.height();

  m_successfulRead = true; // Reading from QImage always succeeds, resulting in empty Document

  m_pixmap.convertFromImage (image);
}

Document::Document (const QString &fileName) :
  m_name (fileName)
{
  LOG4CPP_INFO_S ((*mainCat)) << "Document::Document"
                              << " fileName=" << fileName.toLatin1().data();

  m_successfulRead = true;

  // Grab first few bytes to determine the version number
  QFile *file = new QFile (fileName);
  if (file->open(QIODevice::ReadOnly)) {

    QByteArray bytesStart = file->read (FOUR_BYTES);
    file->close ();

    if (bytesIndicatePreVersion6 (bytesStart)) {

      QFile *file = new QFile (fileName);
      if (file->open (QIODevice::ReadOnly)) {
        QDataStream str (file);

        loadPreVersion6 (str);

      } else {

        m_successfulRead = false;
        m_reasonForUnsuccessfulRead = "Operating system says file is not readable";

      }
    } else {

      QFile *file = new QFile (fileName);
      if (file->open (QIODevice::ReadOnly | QIODevice::Text)) {

        QXmlStreamReader reader (file);

        loadPostVersion5 (reader);

        // Close and deactivate
        file->close ();
        delete file;
        file = 0;

      } else {

        m_successfulRead = false;
        m_reasonForUnsuccessfulRead = "Operating system says file is not readable";
      }
    }
  } else {
    file->close ();
    m_successfulRead = false;
    m_reasonForUnsuccessfulRead = QString ("File '%1' was not found")
                                  .arg (fileName);

  }
}

void Document::addGraphCurveAtEnd (const QString &curveName)
{
  LOG4CPP_INFO_S ((*mainCat)) << "Document::addGraphCurveAtEnd";

  m_coordSystemContext.addGraphCurveAtEnd  (curveName);
}

void Document::addPointAxisWithGeneratedIdentifier (const QPointF &posScreen,
                                                    const QPointF &posGraph,
                                                    QString &identifier,
                                                    double ordinal)
{
  LOG4CPP_INFO_S ((*mainCat)) << "Document::addPointAxisWithGeneratedIdentifier";

  m_coordSystemContext.addPointAxisWithGeneratedIdentifier(posScreen,
                                                           posGraph,
                                                           identifier,
                                                           ordinal);
}

void Document::addPointAxisWithSpecifiedIdentifier (const QPointF &posScreen,
                                                    const QPointF &posGraph,
                                                    const QString &identifier,
                                                    double ordinal)
{
  LOG4CPP_INFO_S ((*mainCat)) << "Document::addPointAxisWithSpecifiedIdentifier";

  m_coordSystemContext.addPointAxisWithSpecifiedIdentifier(posScreen,
                                                           posGraph,
                                                           identifier,
                                                           ordinal);
}

void Document::addPointGraphWithGeneratedIdentifier (const QString &curveName,
                                                     const QPointF &posScreen,
                                                     QString &identifier,
                                                     double ordinal)
{
  LOG4CPP_INFO_S ((*mainCat)) << "Document::addPointGraphWithGeneratedIdentifier";

  m_coordSystemContext.addPointGraphWithGeneratedIdentifier(curveName,
                                                            posScreen,
                                                            identifier,
                                                            ordinal);
}

void Document::addPointGraphWithSpecifiedIdentifier (const QString &curveName,
                                                     const QPointF &posScreen,
                                                     const QString &identifier,
                                                     double ordinal)
{
  LOG4CPP_INFO_S ((*mainCat)) << "Document::addPointGraphWithSpecifiedIdentifier";

  m_coordSystemContext.addPointGraphWithSpecifiedIdentifier(curveName,
                                                            posScreen,
                                                            identifier,
                                                            ordinal);
}

void Document::addPointsInCurvesGraphs (CurvesGraphs &curvesGraphs)
{
  LOG4CPP_INFO_S ((*mainCat)) << "Document::addPointsInCurvesGraphs";

  m_coordSystemContext.addPointsInCurvesGraphs(curvesGraphs);
}

bool Document::bytesIndicatePreVersion6 (const QByteArray &bytes) const
{
  LOG4CPP_INFO_S ((*mainCat)) << "Document::bytesIndicatePreVersion6";

  QByteArray preVersion6MagicNumber;
  preVersion6MagicNumber.resize (FOUR_BYTES);
  preVersion6MagicNumber[0] = 0x00;
  preVersion6MagicNumber[1] = 0x00;
  preVersion6MagicNumber[2] = 0xCA;
  preVersion6MagicNumber[3] = 0xFE;

  return (bytes == preVersion6MagicNumber);
}

void Document::checkAddPointAxis (const QPointF &posScreen,
                                  const QPointF &posGraph,
                                  bool &isError,
                                  QString &errorMessage)
{
  LOG4CPP_INFO_S ((*mainCat)) << "Document::checkAddPointAxis";

  m_coordSystemContext.checkAddPointAxis(posScreen,
                                         posGraph,
                                         isError,
                                         errorMessage);
}

void Document::checkEditPointAxis (const QString &pointIdentifier,
                                   const QPointF &posScreen,
                                   const QPointF &posGraph,
                                   bool &isError,
                                   QString &errorMessage)
{
  LOG4CPP_INFO_S ((*mainCat)) << "Document::checkEditPointAxis";

  m_coordSystemContext.checkEditPointAxis(pointIdentifier,
                                          posScreen,
                                          posGraph,
                                          isError,
                                          errorMessage);
}

const CoordSystem &Document::coordSystem() const
{
  LOG4CPP_INFO_S ((*mainCat)) << "Document::coordSystem";

  return m_coordSystemContext.coordSystem();
}

unsigned int Document::coordSystemCount () const
{
  LOG4CPP_INFO_S ((*mainCat)) << "Document::coordSystemCount";

  return m_coordSystemContext.coordSystemCount();
}

CoordSystemIndex Document::coordSystemIndex() const
{
  LOG4CPP_INFO_S ((*mainCat)) << "Document::coordSystemIndex";

  return m_coordSystemContext.coordSystemIndex();
}

const Curve &Document::curveAxes () const
{
  LOG4CPP_INFO_S ((*mainCat)) << "Document::curveAxes";

  return m_coordSystemContext.curveAxes();
}

Curve *Document::curveForCurveName (const QString &curveName)
{
  LOG4CPP_INFO_S ((*mainCat)) << "Document::curveForCurveName";

  return m_coordSystemContext.curveForCurveName(curveName);
}

const Curve *Document::curveForCurveName (const QString &curveName) const
{
  LOG4CPP_INFO_S ((*mainCat)) << "Document::curveForCurveName";

  return m_coordSystemContext.curveForCurveName (curveName);
}

const CurvesGraphs &Document::curvesGraphs () const
{
  LOG4CPP_INFO_S ((*mainCat)) << "Document::curvesGraphs";

  return m_coordSystemContext.curvesGraphs();
}

QStringList Document::curvesGraphsNames() const
{
  LOG4CPP_INFO_S ((*mainCat)) << "Document::curvesGraphsNames";

  return m_coordSystemContext.curvesGraphsNames();
}

int Document::curvesGraphsNumPoints(const QString &curveName) const
{
  LOG4CPP_INFO_S ((*mainCat)) << "Document::curvesGraphsNumPoints";

  return m_coordSystemContext.curvesGraphsNumPoints(curveName);
}

void Document::editPointAxis (const QPointF &posGraph,
                              const QString &identifier)
{
  LOG4CPP_INFO_S ((*mainCat)) << "Document::editPointAxis";

  m_coordSystemContext.editPointAxis(posGraph,
                                     identifier);
}

void Document::generateEmptyPixmap(const QXmlStreamAttributes &attributes)
{
  LOG4CPP_INFO_S ((*mainCat)) << "Document::generateEmptyPixmap";

  int width = 800, height = 500; // Defaults

  if (attributes.hasAttribute (DOCUMENT_SERIALIZE_IMAGE_WIDTH) &&
      attributes.hasAttribute (DOCUMENT_SERIALIZE_IMAGE_HEIGHT)) {

    width = attributes.value (DOCUMENT_SERIALIZE_IMAGE_WIDTH).toInt();
    height = attributes.value (DOCUMENT_SERIALIZE_IMAGE_HEIGHT).toInt();

  }

  m_pixmap = QPixmap (width, height);
}

void Document::iterateThroughCurvePointsAxes (const Functor2wRet<const QString &, const Point &, CallbackSearchReturn> &ftorWithCallback)
{
  LOG4CPP_INFO_S ((*mainCat)) << "Document::iterateThroughCurvePointsAxes";

  m_coordSystemContext.iterateThroughCurvePointsAxes(ftorWithCallback);
}

void Document::iterateThroughCurvePointsAxes (const Functor2wRet<const QString &, const Point &, CallbackSearchReturn> &ftorWithCallback) const
{
  LOG4CPP_INFO_S ((*mainCat)) << "Document::iterateThroughCurvePointsAxes";

  m_coordSystemContext.iterateThroughCurvePointsAxes(ftorWithCallback);
}

void Document::iterateThroughCurveSegments (const QString &curveName,
                                            const Functor2wRet<const Point &, const Point &, CallbackSearchReturn> &ftorWithCallback) const
{
  LOG4CPP_INFO_S ((*mainCat)) << "Document::iterateThroughCurveSegments";

  m_coordSystemContext.iterateThroughCurveSegments(curveName,
                                                   ftorWithCallback);
}

void Document::iterateThroughCurvesPointsGraphs (const Functor2wRet<const QString &, const Point &, CallbackSearchReturn> &ftorWithCallback)
{
  LOG4CPP_INFO_S ((*mainCat)) << "Document::iterateThroughCurvesPointsGraphs";

  m_coordSystemContext.iterateThroughCurvesPointsGraphs(ftorWithCallback);
}

void Document::iterateThroughCurvesPointsGraphs (const Functor2wRet<const QString &, const Point &, CallbackSearchReturn> &ftorWithCallback) const
{
  LOG4CPP_INFO_S ((*mainCat)) << "Document::iterateThroughCurvesPointsGraphs";

  m_coordSystemContext.iterateThroughCurvesPointsGraphs(ftorWithCallback);
}

void Document::loadImage(QXmlStreamReader &reader)
{
  LOG4CPP_INFO_S ((*mainCat)) << "Document::loadImage";

  loadNextFromReader(reader); // Read to CDATA
  if (reader.isCDATA ()) {

    // Get base64 array
    QByteArray array64 = reader.text().toString().toUtf8();

    // Decoded array
    QByteArray array;
    array = QByteArray::fromBase64(array64);

    // Read decoded array into image
    QDataStream str (&array, QIODevice::ReadOnly);
    QImage img = m_pixmap.toImage ();
    str >> img;
    m_pixmap = QPixmap::fromImage (img);

    // Read until end of this subtree
    while ((reader.tokenType() != QXmlStreamReader::EndElement) ||
           (reader.name() != DOCUMENT_SERIALIZE_IMAGE)){
      loadNextFromReader(reader);
    }

  } else {

    // This point can be reached if:
    // 1) File is broken
    // 2) Bad character is in text, and NetworkClient::cleanXml did not do its job
    reader.raiseError ("Cannot read image data");
  }
}

void Document::loadPostVersion5 (QXmlStreamReader &reader)
{
  LOG4CPP_INFO_S ((*mainCat)) << "Document::loadPostVersion5";

  // If this is purely a serialized Document then we process every node under the root. However, if this is an error report file
  // then we need to skip the non-Document stuff. The common solution is to skip nodes outside the Document subtree using this flag
  bool inDocumentSubtree = false;

  // Import from xml. Loop to end of data or error condition occurs, whichever is first
  while (!reader.atEnd() &&
         !reader.hasError()) {
    QXmlStreamReader::TokenType tokenType = loadNextFromReader(reader);

    // Special processing of DOCUMENT_SERIALIZE_IMAGE outside DOCUMENT_SERIALIZE_DOCUMENT, for an error report file
    if ((reader.name() == DOCUMENT_SERIALIZE_IMAGE) &&
        (tokenType == QXmlStreamReader::StartElement)) {

      generateEmptyPixmap (reader.attributes());
    }

    // Branching to skip non-Document nodes, with the exception of any DOCUMENT_SERIALIZE_IMAGE outside DOCUMENT_SERIALIZE_DOCUMENT
    if ((reader.name() == DOCUMENT_SERIALIZE_DOCUMENT) &&
        (tokenType == QXmlStreamReader::StartElement)) {

      inDocumentSubtree = true;

    } else if ((reader.name() == DOCUMENT_SERIALIZE_DOCUMENT) &&
               (tokenType == QXmlStreamReader::EndElement)) {

      // Exit out of loop immediately
      break;
    }

    if (inDocumentSubtree) {

      // Iterate to next StartElement
      if (tokenType == QXmlStreamReader::StartElement) {

        // This is a StartElement, so process it
        QString tag = reader.name().toString();
//        if (tag == DOCUMENT_SERIALIZE_AXES_CHECKER){
//          m_modelAxesChecker.loadXml (reader);
//        } else if (tag == DOCUMENT_SERIALIZE_COORDS) {
//          m_modelCoords.loadXml (reader);
//        } else if (tag == DOCUMENT_SERIALIZE_CURVE) {
//          m_curveAxes = new Curve (reader);
//        } else if (tag == DOCUMENT_SERIALIZE_CURVES_GRAPHS) {
//          m_curvesGraphs.loadXml (reader);
//        } else if (tag == DOCUMENT_SERIALIZE_DIGITIZE_CURVE) {
//          m_modelDigitizeCurve.loadXml (reader);
//        } else if (tag == DOCUMENT_SERIALIZE_DOCUMENT) {
//          // Do nothing. This is the root node
//        } else if (tag == DOCUMENT_SERIALIZE_EXPORT) {
//          m_modelExport.loadXml (reader);
//        } else if (tag == DOCUMENT_SERIALIZE_GENERAL || tag == DOCUMENT_SERIALIZE_COMMON) {
//          m_modelGeneral.loadXml (reader);
//        } else if (tag == DOCUMENT_SERIALIZE_GRID_REMOVAL) {
//          m_modelGridRemoval.loadXml (reader);
//        } else if (tag == DOCUMENT_SERIALIZE_IMAGE) {
//          // A standard Document file has DOCUMENT_SERIALIZE_IMAGE inside DOCUMENT_SERIALIZE_DOCUMENT, versus an error report file
//          loadImage(reader);
//        } else if (tag == DOCUMENT_SERIALIZE_POINT_MATCH) {
//          m_modelPointMatch.loadXml (reader);
//        } else if (tag == DOCUMENT_SERIALIZE_SEGMENTS) {
//         m_modelSegments.loadXml (reader);
//        } else {
//          m_successfulRead = false;
//          m_reasonForUnsuccessfulRead = QString ("Unexpected xml token '%1' encountered").arg (tag);
//          break;
//        }
      }
    }
  }
  if (reader.hasError ()) {

    m_successfulRead = false;
    m_reasonForUnsuccessfulRead = reader.errorString();
  }

  // There are already one axes curve and at least one graph curve so we do not need to add any more graph curves
}

void Document::loadPreVersion6 (QDataStream &str)
{
  LOG4CPP_INFO_S ((*mainCat)) << "Document::loadPreVersion6";

  qint32 int32;
  double dbl, versionDouble, radius = 0.0;
  QString st;

//  str >> int32; // Magic number
//  str >> versionDouble;
//  str >> st; // Version string
//  str >> int32; // Background
//  str >> m_pixmap;
//  str >> m_name;
//  str >> st; // CurveCmbText selection
//  str >> st; // MeasureCmbText selection
//  str >> int32;
//  m_modelCoords.setCoordsType((CoordsType) int32);
//  if (versionDouble >= 3) {
//    str >> (double &) radius;
//  }
//  m_modelCoords.setOriginRadius(radius);
//  str >> int32;
//  m_modelCoords.setCoordUnitsRadius(COORD_UNITS_NON_POLAR_THETA_NUMBER);
//  m_modelCoords.setCoordUnitsTheta((CoordUnitsPolarTheta) int32);
//  str >> int32;
//  m_modelCoords.setCoordScaleXTheta((CoordScale) int32);
//  str >> int32;
//  m_modelCoords.setCoordScaleYRadius((CoordScale) int32);
//
//  str >> int32;
//  m_modelExport.setDelimiter((ExportDelimiter) int32);
//  str >> int32;
//  m_modelExport.setLayoutFunctions((ExportLayoutFunctions) int32);
//  str >> int32;
//  m_modelExport.setPointsSelectionFunctions((ExportPointsSelectionFunctions) int32);
//  m_modelExport.setPointsIntervalUnitsRelations((ExportPointsIntervalUnits) int32);
//  str >> int32;
//  m_modelExport.setHeader((ExportHeader) int32);
//  if (versionDouble >= 5.2) {
//    str >> st; // X label
//    if (m_modelCoords.coordsType() == COORDS_TYPE_CARTESIAN) {
//      m_modelExport.setXLabel(st);
//    }
//    str >> st; // Theta label
//    if (m_modelCoords.coordsType() == COORDS_TYPE_POLAR) {
//      m_modelExport.setXLabel(st);
//    }
//  }
//
//  // Stable flag in m_modelGridRemoval is set below after points are read in
//  str >> int32; // Remove thin lines parallel to axes
//  str >> dbl; // Thin thickness
//  str >> int32;
//  m_modelGridRemoval.setRemoveDefinedGridLines(int32);
//  str >> int32; // Initialized
//  str >> int32;
//  m_modelGridRemoval.setCountX(int32);
//  str >> int32;
//  m_modelGridRemoval.setCountY(int32);
//  str >> int32;
//  m_modelGridRemoval.setGridCoordDisableX((GridCoordDisable) int32);
//  str >> int32;
//  m_modelGridRemoval.setGridCoordDisableY((GridCoordDisable) int32);
//  str >> dbl;
//  m_modelGridRemoval.setStartX(dbl);
//  str >> dbl;
//  m_modelGridRemoval.setStartY(dbl);
//  str >> dbl;
//  m_modelGridRemoval.setStepX(dbl);
//  str >> dbl;
//  m_modelGridRemoval.setStepY(dbl);
//  str >> dbl;
//  m_modelGridRemoval.setStopX(dbl);
//  str >> dbl;
//  m_modelGridRemoval.setStopY(dbl);
//  str >> dbl;
//  m_modelGridRemoval.setCloseDistance(dbl);
//  str >> int32; // Boolean remove color flag
//  if (versionDouble >= 5) {
//    QColor color;
//    str >> color;
//  } else {
//    str >> int32; // Rgb color
//  }
//  str >> int32; // Foreground threshold low
//  str >> int32; // Foreground threshold high
//  str >> dbl; // Gap separation
//
//  str >> int32; // Grid display is initialized flag
//  str >> int32; // X count
//  str >> int32; // Y count
//  str >> int32; // X parameter
//  str >> int32; // Y parameter
//  str >> dbl; // X start
//  str >> dbl; // Y start
//  str >> dbl; // X step
//  str >> dbl; // Y step
//  str >> dbl; // X stop
//  str >> dbl; // Y stop
//
//  str >> int32;
//  m_modelSegments.setMinLength(int32);
//  str >> int32;
//  m_modelSegments.setPointSeparation(int32);
//  str >> int32;
//  m_modelSegments.setLineWidth(int32);
//  str >> int32;
//  m_modelSegments.setLineColor((ColorPalette) int32);
//
//  str >> int32; // Point separation
//  str >> int32;
//  m_modelPointMatch.setMaxPointSize(int32);
//  str >> int32;
//  m_modelPointMatch.setPaletteColorAccepted((ColorPalette) int32);
//  str >> int32;
//  m_modelPointMatch.setPaletteColorRejected((ColorPalette) int32);
//  if (versionDouble < 4) {
//    m_modelPointMatch.setPaletteColorCandidate(COLOR_PALETTE_BLUE);
//  } else {
//    str >> int32;
//    m_modelPointMatch.setPaletteColorCandidate((ColorPalette) int32);
//  }
//
//  str >> int32; // Discretize method
//  str >> int32; // Intensity threshold low
//  str >> int32; // Intensity threshold high
//  str >> int32; // Foreground threshold low
//  str >> int32; // Foreground threshold high
//  str >> int32; // Hue threshold low
//  str >> int32; // Hue threshold high
//  str >> int32; // Saturation threshold low
//  str >> int32; // Saturation threshold high
//  str >> int32; // Value threshold low
//  str >> int32; // Value threshold high
//
//  m_curveAxes = new Curve (str);
//  Curve curveScale (str); // Scales are dropped on the floor
//  m_curvesGraphs.loadPreVersion6 (str);
//
//  // Information from curves and points can affect some data structures that were (mostly) set earlier
//  if (m_curveAxes->numPoints () > 2) {
//    m_modelGridRemoval.setStable();
//  }
}

DocumentModelAxesChecker Document::modelAxesChecker() const
{
  LOG4CPP_INFO_S ((*mainCat)) << "Document::modelAxesChecker";

  return m_coordSystemContext.modelAxesChecker();
}

DocumentModelColorFilter Document::modelColorFilter() const
{
  LOG4CPP_INFO_S ((*mainCat)) << "Document::modelColorFilter";

  return m_coordSystemContext.modelColorFilter();
}

DocumentModelCoords Document::modelCoords() const
{
  LOG4CPP_INFO_S ((*mainCat)) << "Document::modelCoords";

  return m_coordSystemContext.modelCoords();
}

CurveStyles Document::modelCurveStyles() const
{
  LOG4CPP_INFO_S ((*mainCat)) << "Document::modelCurveStyles";

  return m_coordSystemContext.modelCurveStyles();
}

DocumentModelDigitizeCurve Document::modelDigitizeCurve() const
{
  LOG4CPP_INFO_S ((*mainCat)) << "Document::modelDigitizeCurve";

  return m_coordSystemContext.modelDigitizeCurve();
}

DocumentModelExportFormat Document::modelExport() const
{
  LOG4CPP_INFO_S ((*mainCat)) << "Document::modelExport";

  return m_coordSystemContext.modelExport();
}

DocumentModelGeneral Document::modelGeneral() const
{
  LOG4CPP_INFO_S ((*mainCat)) << "Document::modelGeneral";

  return m_coordSystemContext.modelGeneral();
}

DocumentModelGridRemoval Document::modelGridRemoval() const
{
  LOG4CPP_INFO_S ((*mainCat)) << "Document::modelGridRemoval";

  return m_coordSystemContext.modelGridRemoval();
}

DocumentModelPointMatch Document::modelPointMatch() const
{
  LOG4CPP_INFO_S ((*mainCat)) << "Document::modelPointMatch";

  return m_coordSystemContext.modelPointMatch();
}

DocumentModelSegments Document::modelSegments() const
{
  LOG4CPP_INFO_S ((*mainCat)) << "Document::modelSegments";

  return m_coordSystemContext.modelSegments();
}

void Document::movePoint (const QString &pointIdentifier,
                          const QPointF &deltaScreen)
{
  m_coordSystemContext.movePoint (pointIdentifier,
                     deltaScreen);
}

int Document::nextOrdinalForCurve (const QString &curveName) const
{
  LOG4CPP_INFO_S ((*mainCat)) << "Document::nextOrdinalForCurve";

  return m_coordSystemContext.nextOrdinalForCurve(curveName);
}

QPixmap Document::pixmap () const
{                               
  return m_pixmap;
}

QPointF Document::positionGraph (const QString &pointIdentifier) const
{
  return m_coordSystemContext.positionGraph(pointIdentifier);
}

QPointF Document::positionScreen (const QString &pointIdentifier) const
{                          
  return m_coordSystemContext.positionScreen(pointIdentifier);
}

void Document::print () const
{                                 
  QString text;
  QTextStream str (&text);

  printStream ("",
               str);
  std::cerr << text.toLatin1().data();
}

void Document::printStream (QString indentation,
                            QTextStream &str) const
{
  str << indentation << "Document\n";

  indentation += INDENTATION_DELTA;

  str << indentation << "name=" << m_name << "\n";
  str << indentation << "pixmap=" << m_pixmap.width() << "x" <<  m_pixmap.height() << "\n";

  m_coordSystemContext.printStream(indentation,
                      str);
}

QString Document::reasonForUnsuccessfulRead () const
{
  ENGAUGE_ASSERT (!m_successfulRead);

  return m_reasonForUnsuccessfulRead;
}

void Document::removePointAxis (const QString &identifier)
{
  LOG4CPP_INFO_S ((*mainCat)) << "Document::removePointAxis";

  m_coordSystemContext.removePointAxis(identifier);
}

void Document::removePointGraph (const QString &identifier)
{
  LOG4CPP_INFO_S ((*mainCat)) << "Document::removePointGraph";

  m_coordSystemContext.removePointGraph(identifier);
}

void Document::removePointsInCurvesGraphs (CurvesGraphs &curvesGraphs)
{
  LOG4CPP_INFO_S ((*mainCat)) << "Document::removePointsInCurvesGraphs";

  m_coordSystemContext.removePointsInCurvesGraphs(curvesGraphs);
}

void Document::saveXml (QXmlStreamWriter &writer) const
{
  writer.writeStartElement(DOCUMENT_SERIALIZE_DOCUMENT);

  // Version number is tacked onto DOCUMENT_SERIALIZE_DOCUMENT since the alternative  (creating a new start element)
  // causes the code to complain during loading
  writer.writeAttribute(DOCUMENT_SERIALIZE_APPLICATION_VERSION_NUMBER, VERSION_NUMBER);

  // Serialize the Document image. That binary data is encoded as base64
  QByteArray array;
  QDataStream str (&array, QIODevice::WriteOnly);
  QImage img = m_pixmap.toImage ();
  str << img;
  writer.writeStartElement(DOCUMENT_SERIALIZE_IMAGE);

  // Image width and height are explicitly inserted for error reports, since the CDATA is removed
  // but we still want the image size for reconstructing the error(s)
  writer.writeAttribute(DOCUMENT_SERIALIZE_IMAGE_WIDTH, QString::number (img.width()));
  writer.writeAttribute(DOCUMENT_SERIALIZE_IMAGE_HEIGHT, QString::number (img.height()));

  writer.writeCDATA (array.toBase64 ());
  m_coordSystemContext.saveXml (writer);
  writer.writeEndElement();
}

void Document::setCoordSystemIndex(CoordSystemIndex coordSystemIndex)
{
  LOG4CPP_INFO_S ((*mainCat)) << "Document::setCoordSystemIndex";

  m_coordSystemContext.setCoordSystemIndex (coordSystemIndex);
}

void Document::setCurvesGraphs (const CurvesGraphs &curvesGraphs)
{
  LOG4CPP_INFO_S ((*mainCat)) << "Document::setCurvesGraphs";

  m_coordSystemContext.setCurvesGraphs(curvesGraphs);
}

void Document::setCurvesGraphs (CoordSystemIndex coordSystemIndex,
                                const CurvesGraphs &curvesGraphs)
{
  LOG4CPP_INFO_S ((*mainCat)) << "Document::setCurvesGraphs";

  m_coordSystemContext.setCurvesGraphs(coordSystemIndex,
                                       curvesGraphs);
}

void Document::setModelAxesChecker(const DocumentModelAxesChecker &modelAxesChecker)
{
  LOG4CPP_INFO_S ((*mainCat)) << "Document::setModelAxesChecker";

  m_coordSystemContext.setModelAxesChecker(modelAxesChecker);
}

void Document::setModelColorFilter(const DocumentModelColorFilter &modelColorFilter)
{
  LOG4CPP_INFO_S ((*mainCat)) << "Document::setModelColorFilter";

  // Save the CurveFilter for each Curve
  ColorFilterSettingsList::const_iterator itr;
  for (itr = modelColorFilter.colorFilterSettingsList().constBegin ();
       itr != modelColorFilter.colorFilterSettingsList().constEnd();
       itr++) {

    QString curveName = itr.key();
    const ColorFilterSettings &colorFilterSettings = itr.value();

    Curve *curve = curveForCurveName (curveName);
    curve->setColorFilterSettings (colorFilterSettings);
  }
}

void Document::setModelCoords (const DocumentModelCoords &modelCoords)
{
  LOG4CPP_INFO_S ((*mainCat)) << "Document::setModelCoords";

  m_coordSystemContext.setModelCoords(modelCoords);
}

void Document::setModelCurveStyles(const CurveStyles &modelCurveStyles)
{
  LOG4CPP_INFO_S ((*mainCat)) << "Document::setModelCurveStyles";

  // Save the LineStyle and PointStyle for each Curve
  QStringList curveNames = modelCurveStyles.curveNames();
  QStringList::iterator itr;
  for (itr = curveNames.begin(); itr != curveNames.end(); itr++) {

    QString curveName = *itr;
    const CurveStyle &curveStyle = modelCurveStyles.curveStyle (curveName);

    Curve *curve = curveForCurveName (curveName);
    curve->setCurveStyle (curveStyle);
  }
}

void Document::setModelDigitizeCurve (const DocumentModelDigitizeCurve &modelDigitizeCurve)
{
  LOG4CPP_INFO_S ((*mainCat)) << "Document::setModelDigitizeCurve";

  m_coordSystemContext.setModelDigitizeCurve(modelDigitizeCurve);
}

void Document::setModelExport(const DocumentModelExportFormat &modelExport)
{
  LOG4CPP_INFO_S ((*mainCat)) << "Document::setModelExport";

  m_coordSystemContext.setModelExport (modelExport);
}

void Document::setModelGeneral (const DocumentModelGeneral &modelGeneral)
{
  LOG4CPP_INFO_S ((*mainCat)) << "Document::setModelGeneral";

  m_coordSystemContext.setModelGeneral(modelGeneral);
}

void Document::setModelGridRemoval(const DocumentModelGridRemoval &modelGridRemoval)
{
  LOG4CPP_INFO_S ((*mainCat)) << "Document::setModelGridRemoval";

  m_coordSystemContext.setModelGridRemoval(modelGridRemoval);
}

void Document::setModelPointMatch(const DocumentModelPointMatch &modelPointMatch)
{
  LOG4CPP_INFO_S ((*mainCat)) << "Document::setModelPointMatch";

  m_coordSystemContext.setModelPointMatch(modelPointMatch);
}

void Document::setModelSegments(const DocumentModelSegments &modelSegments)
{
  LOG4CPP_INFO_S ((*mainCat)) << "Document::setModelSegments";

  setModelSegments (modelSegments);
}

bool Document::successfulRead () const
{                                 
  return m_successfulRead;
}

void Document::updatePointOrdinals (const Transformation &transformation)
{
  LOG4CPP_INFO_S ((*mainCat)) << "Document::updatePointOrdinals";

  m_coordSystemContext.updatePointOrdinals(transformation);
}
