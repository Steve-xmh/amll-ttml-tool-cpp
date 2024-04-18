#include "TTMLLyric.h"

#include <qnamespace.h>
#include <qxmlstream.h>

typedef enum ParseStatus {
    None = 0,
    InDiv,
    InP,

    InSpan,
    InTranslationSpan,
    InRomanSpan,

    InBackgroundSpan,
    InSpanInBackgroundSpan,
    InTranslationSpanInBackgroundSpan,
    InRomanSpanInBackgroundSpan,

    InBody,
    InHead,
    InMetadata,
    InTtml,
} ParseStatus;

TTMLLyric::TTMLLyric()
{
}

TTMLLyric::~TTMLLyric()
{
}

void TTMLLyric::clear()
{
}

void TTMLLyric::readFromString(string data)
{
    using namespace std;
    QXmlStreamReader reader(data.c_str());
    ParseStatus status = None;
    while (!reader.atEnd()) {
        switch (reader.readNext()) {
        case QXmlStreamReader::NoToken: {
            break;
        }
        case QXmlStreamReader::StartDocument: {
            break;
        }
        case QXmlStreamReader::EndDocument: {
            break;
        }
        case QXmlStreamReader::StartElement: {
            auto qname = reader.qualifiedName();
            qDebug() << "StartElement:" << qname;
            if (!QString::compare(qname, "tt", Qt::CaseInsensitive)) {
                if (status == None) {
                    status = InTtml;
                } else {
                    throw runtime_error("Unexpected <tt> tag");
                }
            } else if (!QString::compare(qname, "head", Qt::CaseInsensitive)) {
                if (status == InTtml) {
                    status = InHead;
                } else {
                    throw runtime_error("Unexpected <head> tag");
                }
            } else if (!QString::compare(qname, "metadata", Qt::CaseInsensitive)) {
                if (status == InHead) {
                    status = InMetadata;
                } else {
                    throw runtime_error("Unexpected <metadata> tag");
                }
            } else if (!QString::compare(qname, "ttm:agent", Qt::CaseInsensitive)) {
                if (status == InMetadata) {
                    // TODO
                    reader.readElementText(QXmlStreamReader::IncludeChildElements); // Skip
                } else {
                    throw runtime_error("Unexpected <ttm:agent> tag");
                }
            } else if (!QString::compare(qname, "amll:meta", Qt::CaseInsensitive)) {
                if (status == InMetadata) {
                    // TODO
                    reader.readElementText(QXmlStreamReader::IncludeChildElements); // Skip
                } else {
                    throw runtime_error("Unexpected <amll:meta> tag");
                }
            } else if (!QString::compare(qname, "body", Qt::CaseInsensitive)) {
                if (status == InTtml) {
                    status = InBody;
                } else {
                    throw runtime_error("Unexpected <body> tag");
                }
            } else if (!QString::compare(qname, "div", Qt::CaseInsensitive)) {
                if (status == InBody) {
                    status = InDiv;
                } else {
                    throw runtime_error("Unexpected <div> tag");
                }
            } else if (!QString::compare(qname, "p", Qt::CaseInsensitive)) {
                if (status == InDiv) {
                    status = InP;
                } else {
                    throw runtime_error("Unexpected <p> tag");
                }
            } else if (!QString::compare(qname, "span", Qt::CaseInsensitive)) {
                if (status == InP) {
                    reader.readElementText(QXmlStreamReader::IncludeChildElements); // Skip
                    // status = InSpan;
                    // TODO
                } else if (status == InSpan) {
                    // TODO
                } else {
                    throw runtime_error("Unexpected <p> tag");
                }
            }
            break;
        }
        case QXmlStreamReader::EndElement: {
            auto qname = reader.qualifiedName();
            qDebug() << "EndElement:" << qname;
            if (!QString::compare(qname, "tt", Qt::CaseInsensitive)) {
                if (status == InTtml) {
                    status = None;
                } else {
                    throw runtime_error("Unexpected <tt> tag");
                }
            } else if (!QString::compare(qname, "head", Qt::CaseInsensitive)) {
                if (status == InHead) {
                    status = InTtml;
                } else {
                    throw runtime_error("Unexpected <head> tag");
                }
            } else if (!QString::compare(qname, "metadata", Qt::CaseInsensitive)) {
                if (status == InMetadata) {
                    status = InHead;
                } else {
                    throw runtime_error("Unexpected <metadata> tag");
                }
            } else if (!QString::compare(qname, "ttm:agent", Qt::CaseInsensitive)) {
                // TODO
                // Should be skiped
                throw runtime_error("unreachable code");
            } else if (!QString::compare(qname, "amll:meta", Qt::CaseInsensitive)) {
                // TODO
                // Should be skiped
                throw runtime_error("unreachable code");
            } else if (!QString::compare(qname, "body", Qt::CaseInsensitive)) {
                if (status == InBody) {
                    status = InTtml;
                } else {
                    throw runtime_error("Unexpected <body> tag");
                }
            } else if (!QString::compare(qname, "div", Qt::CaseInsensitive)) {
                if (status == InDiv) {
                    status = InBody;
                } else {
                    throw runtime_error("Unexpected <div> tag");
                }
            } else if (!QString::compare(qname, "p", Qt::CaseInsensitive)) {
                if (status == InP) {
                    status = InDiv;
                } else {
                    throw runtime_error("Unexpected <p> tag");
                }
            } else if (!QString::compare(qname, "span", Qt::CaseInsensitive)) {
                // TODO
                // Should be skiped
                throw runtime_error("unreachable code");
            }
            break;
        }
        case QXmlStreamReader::Characters: {
            break;
        }
        case QXmlStreamReader::Comment: {
            break;
        }
        case QXmlStreamReader::DTD: {
            break;
        }
        case QXmlStreamReader::EntityReference: {
            break;
        }
        case QXmlStreamReader::ProcessingInstruction: {
            break;
        }
        case QXmlStreamReader::Invalid: {
            break;
        }
        }
    }
    if (reader.hasError()) {
        throw runtime_error("Failed to parse TTML data");
    }
}
