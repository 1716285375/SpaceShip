#include "FontResource.h"

FontResource::FontResource(TTF_Font *font, int fontSize, bool bold, bool italic, const std::string& fontName)
 : m_font(font), m_fontSize(fontSize), m_bold(bold), m_italic(italic), m_fontName(fontName)
{

}

FontResource::~FontResource()
{
    unload();
}

void FontResource::unload()
{
    if (m_font) {
        TTF_CloseFont(m_font);
        m_font = nullptr;
    }
}

TTF_Font *FontResource::getFont() const
{
    if (m_font) {
        return m_font;
    }
    return nullptr;
}
