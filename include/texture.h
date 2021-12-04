#ifndef TEXTURE_H
#define TEXTURE_H

#include "pixmap.h"
#include <QDir>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

class Texture
{
public:
	typedef std::map<QString, Pixmap, std::less<QString>> MapType;

	Texture(const QString &id = QString());

	bool save(const QFile &file) const;
	bool load(const QFile &file);

	bool savePixmaps(const QDir &dir) const;
	bool loadPixmaps(const QDir &dir);

	bool saveSpecificPixmaps(const QDir &dir) const;
	bool loadSpecificPixmaps(const QDir &dir);

	void pack();
	void unpack();

	const QString &id() const;

	static void initPathToIdMapFromJson(const QJsonArray &textureJsonArray);

private:

	void unpackSpecific();
	void createAndAppendPixmap(const QJsonObject &objectJson, const QString &id, int index, bool isSpecific, int depth, int specificIndex);

	static std::map<QString, QString, std::less<QString>> ms_pathToIdMap;

	QString m_pathId;
	QImage	m_image;
	MapType m_pixmaps;
};

#endif // TEXTURE_H