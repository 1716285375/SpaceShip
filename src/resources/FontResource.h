#ifndef FONT_RESOURCE_H
#define FONT_RESOURCE_H

#include "Resource.h"
#include <SDL_ttf.h>

class FontResource : public Resource {
    public:
        FontResource(TTF_Font* font, int fontSize, bool bold = false, bool italic = false, const std::string& fontName = "DefaultFont");
        virtual ~FontResource() override;
        void unload() override;
        TTF_Font* getFont() const;
    private:
        TTF_Font* m_font;
        int m_fontSize;
        bool m_bold;
        bool m_italic;
        std::string m_fontName;

};

#endif // FONT_RESOURCE_H