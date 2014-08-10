/*!
 * \file src/Menu.cpp
 * \brief Menu 'overlay'
 *
 * \author xythobuz
 */

#include <cctype>
#include <cstring>

#include "global.h"
#include "Console.h"
#include "OpenRaider.h"
#include "utils/strings.h"
#include "TombRaider.h"
#include "Window.h"
#include "Menu.h"

// TODO
// Going up to / leads to the current working directory

Menu::Menu() {
    mVisible = false;
    mCursor = 0;
    mMin = 0;
    mapFolder = nullptr;

    mainText.text = bufferString("%s", VERSION);
    mainText.color[0] = BLUE[0];
    mainText.color[1] = BLUE[1];
    mainText.color[2] = BLUE[2];
    mainText.color[3] = BLUE[3];
    mainText.scale = 1.2f;
    mainText.y = 10;
    mainText.w = 0;
    mainText.h = 0;
}

Menu::~Menu() {
    delete [] mainText.text;
    mainText.text = nullptr;

    delete mapFolder;
    mapFolder = nullptr;
}

int Menu::initialize() {
    return initialize(Folder(getOpenRaider().mPakDir));
}

int Menu::initialize(Folder folder) {
    if (mapFolder != nullptr)
        delete mapFolder;
    mapFolder = new Folder(folder);
    mMin = mCursor = 0;

    mapFolder->executeRemoveFiles([](File &f) {
        // Filter files based on file name
        if ((f.getName().compare(f.getName().length() - 4, 4, ".phd") != 0)
            && (f.getName().compare(f.getName().length() - 4, 4, ".tr2") != 0)
            && (f.getName().compare(f.getName().length() - 4, 4, ".tr4") != 0)
            && (f.getName().compare(f.getName().length() - 4, 4, ".trc") != 0)) {
            return true; // delete file from list
        }

        // Check maps for validity
        int error = TombRaider::checkMime(f.getPath().c_str());
        if (error != 0) {
            getConsole().print("Error: pak file '%s' %s",
                    f.getName().c_str(), (error == -1) ? "not found" : "invalid");
            return true; // delete file from list
        }

        return false; // keep file on list
    });

    if ((mapFolder->fileCount() + mapFolder->folderCount()) > 0)
        mCursor = 1; // Don't select ".." by default

    return 0;
}

void Menu::setVisible(bool visible) {
    mVisible = visible;
}

bool Menu::isVisible() {
    return mVisible;
}

void Menu::display() {
    if (!mVisible)
        return;

    // Draw half-transparent *overlay*
    glColor4f(0.0f, 0.0f, 0.0f, 0.75f);
    glDisable(GL_TEXTURE_2D);
    glRecti(0, 0, (GLint)getWindow().getWidth(), (GLint)getWindow().getHeight());
    glEnable(GL_TEXTURE_2D);

    // Draw heading text, using FontString so we can get the
    // width of the drawn text to center it
    mainText.x = (getWindow().getWidth() / 2) - ((unsigned int)(mainText.w / 2));
    getFont().writeString(mainText);

    // Estimate displayable number of items
    int items = (getWindow().getHeight() - 60) / 25;

    // Print list of "..", folders, files
    for (long i = mMin; (i < (mMin + items))
                && (i < (mapFolder->folderCount() + mapFolder->fileCount() + 1)); i++) {
        if (i == 0) {
            getFont().drawText(25, 50, 0.75f, (mCursor == i) ? RED : BLUE, "..");
        } else {
            getFont().drawText(25, (unsigned int)(50 + (25 * (i - mMin))), 0.75f,
                (mCursor == i) ? RED : BLUE, "%s",
                ((i - 1) < mapFolder->folderCount()) ?
                    (mapFolder->getFolder(i - 1).getName() + "/").c_str()
                    : mapFolder->getFile(i - 1 - mapFolder->folderCount()).getName().c_str());
        }
    }
}

void Menu::play() {
    if (mCursor == 0) {
        if (initialize(mapFolder->getParent().getPath()) != 0) {
            //! \todo Display something if an error occurs
        }
    } else if ((mCursor - 1) < mapFolder->folderCount()) {
        if (initialize(mapFolder->getFolder(mCursor - 1).getPath()) != 0) {
            //! \todo Display something if an error occurs
        }
    } else {
        char *tmp = bufferString("load %s",
                mapFolder->getFile((unsigned long)mCursor - 1 - mapFolder->folderCount()).getPath().c_str());
        if (getOpenRaider().command(tmp) == 0) {
            setVisible(false);
        } else {
            //! \todo Display something if an error occurs
        }
        delete [] tmp;
    }
}

void Menu::handleKeyboard(KeyboardButton key, bool pressed) {
    if (!pressed)
        return;

    assert(mapFolder != nullptr);
    int items = (getWindow().getHeight() - 60) / 25;

    if (key == upKey) {
        if (mCursor > 0)
            mCursor--;
        else
            mCursor = (long)(mapFolder->folderCount() + mapFolder->fileCount());
    } else if (key == downKey) {
        if (mCursor < (long)(mapFolder->folderCount() + mapFolder->fileCount()))
            mCursor++;
        else
            mCursor = 0;
    } else if (key == enterKey) {
        play();
    }

    if (mCursor > (mMin + items - 1)) {
        mMin = mCursor - items + 1;
    } else if (mCursor < mMin) {
        mMin = mCursor;
    }
}

void Menu::handleMouseClick(unsigned int x, unsigned int y, KeyboardButton button, bool released) {
    int items = (getWindow().getHeight() - 60) / 25;

    if (released || (button != leftmouseKey))
        return;

    if ((y >= 50) && (y <= (unsigned int)(50 + (25 * items)))) {
        y -= 50;
        if (mCursor == (mMin + (y / 25)))
            play();
        else
            mCursor = mMin + (y / 25);
    }
}

void Menu::handleMouseScroll(int xrel, int yrel) {
    assert((xrel != 0) || (yrel != 0));
    assert(mapFolder != nullptr);
    int items = (getWindow().getHeight() - 60) / 25;

    if ((mapFolder->folderCount() + mapFolder->fileCount() + 1) > items) {
        if (yrel < 0) {
            if (mMin < (mapFolder->folderCount() + mapFolder->fileCount() + 1 - items))
                mMin++;
        } else if (yrel > 0) {
            if (mMin > 0)
                mMin--;
        }

        if (mCursor < mMin) {
            mCursor = mMin;
        } else if (mCursor > (mMin + items - 1)) {
            mCursor = mMin + items - 1;
        }
    }
}

