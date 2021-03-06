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
	typedef std::multimap<QString, Pixmap, std::less<QString>> MapType;

	Texture(const QString &id = QString());
	Texture(const Texture &other);

	bool save(const QFile &file) const;
	bool load(const QFile &file);

	bool savePixmaps(const QDir &dir) const;
	bool loadPixmaps(const QDir &dir);

	bool saveSpecificPixmaps(const QDir &dir) const;
	bool loadSpecificPixmaps(const QDir &dir);

	void pack(const Texture *other = nullptr, Texture *tagger=nullptr, bool usePixmaps=false);
	void unpack(const Texture *model = nullptr);

	const QString &pathId() const;
	const QImage &image() const;
	QImage &image();

	static void initPathToIdMapFromJson(const QJsonArray &textureJsonArray);
	bool isUnpacked() const;
	const MapType &pixmaps() const;

	Texture &operator=(const Texture &other);

private:

	void unpackSpecific(const Texture *model);
	void createAndAppendPixmap(const QJsonObject &objectJson, const QString &id,
							   int index, bool isSpecific, int depth, int specificIndex,
							   const Texture *model=nullptr);

	void pack(const MapType &pixmaps, Texture * const tagger=nullptr);

	static std::map<QString, QString, std::less<QString>> ms_pathToIdMap;

	QString m_pathId;
	QImage	m_image;
	MapType m_pixmaps;
};

#endif // TEXTURE_H
