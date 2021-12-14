#ifndef THEME_H
#define THEME_H

#include "texture.h"
#include <QDir>
#include <map>
#include <set>
#include "color.h"
#include <QtXml>

class Theme
{
public:

	typedef std::map<QString, Texture, std::less<QString>> TextureMapType;
	typedef std::set<Color, CompareColor> ColorMapType;
	Theme();

	void save(const QDir &dir) const;
	void load(const QDir &dir);

	void pack(const Theme *model = nullptr);
	void unpack(const Theme *model=nullptr);

	void savePixmaps(const QDir &dir);
	void loadPixmaps(const QDir &dir);

	bool loadColors(const QDir &dir);
	bool saveColors(const QDir &dir) const;
	void fuseColors(const Theme *model);

	const QDir &path() const;
	const QString &name() const;

    bool isInitialized() const;

	bool isOpened() const;
	bool isUnpacked() const;

	void copyTextures(const Theme &other);

	const TextureMapType &textures() const;
	const ColorMapType &colors() const;

private:
	QString	m_name;
	QDir m_path;
	TextureMapType m_textures;
	ColorMapType m_colors;
};

#endif // THEME_H
