/*!
 * \file src/Console.cpp
 * \brief Console 'overlay'
 *
 * \author xythobuz
 */

#include <iostream>

#include "global.h"
#include "Font.h"
#include "OpenRaider.h"
#include "utils/strings.h"
#include "utils/time.h"
#include "Window.h"
#include "Console.h"

#define INPUT_BUFFER_SIZE 255

Console::Console() {
    mVisible = false;
    mInputBuffer = new char[INPUT_BUFFER_SIZE + 1];
    mInputBuffer[INPUT_BUFFER_SIZE] = '\0';
    mInputBufferPointer = 0;
    mPartialInput = NULL;
    mHistoryPointer = 0;
    mUnfinishedInput = NULL;
    mLineOffset = 0;
}

Console::~Console() {
    delete [] mInputBuffer;
    mInputBuffer = NULL;

    delete [] mPartialInput;
    mPartialInput = NULL;

    delete [] mUnfinishedInput;
    mUnfinishedInput = NULL;

    while (mHistory.size() > 0) {
        delete [] mHistory.back();
        mHistory.pop_back();
    }

    while (mCommandHistory.size() > 0) {
        delete [] mCommandHistory.back();
        mCommandHistory.pop_back();
    }
}

void Console::setVisible(bool visible) {
    mVisible = visible;
    getWindow().setTextInput(mVisible);
}

bool Console::isVisible() {
    return mVisible;
}

void Console::print(const char *s, ...) {
    va_list args;
    va_start(args, s);
    char *tmp = bufferString(s, args);
    va_end(args);

    if (tmp != NULL) {
        mHistory.push_back(tmp);
#ifdef DEBUG
        std::cout << tmp << std::endl;
#endif
    }
}

#define LINE_GEOMETRY(window) unsigned int firstLine = 35; \
        unsigned int lastLine = (window.getHeight() / 2) - 55; \
        unsigned int inputLine = (window.getHeight() / 2) - 30; \
        unsigned int lineSteps = 20; \
        unsigned int lineCount = (lastLine - firstLine + lineSteps) / lineSteps; \
        while (((lineCount * lineSteps) + firstLine) < inputLine) { \
            lineSteps++; \
            lineCount = (lastLine - firstLine + lineSteps) / lineSteps; \
        }

void Console::display() {
    if (mVisible) {
        // Calculate line drawing geometry
        // Depends on window height, so recalculate every time
        LINE_GEOMETRY(getWindow());

        // Draw half-transparent *overlay*
        glColor4f(0.0f, 0.0f, 0.0f, 0.75f);
        glDisable(GL_TEXTURE_2D);
        glRecti(0, 0, getWindow().getWidth(), getWindow().getHeight() / 2);
        glEnable(GL_TEXTURE_2D);

        int scrollIndicator;
        if (mHistory.size() > lineCount) {
            scrollIndicator = (mHistory.size() - lineCount - mLineOffset) * 100 / (mHistory.size() - lineCount);
        } else {
            scrollIndicator = 100;
        }

        getFont().drawText(10, 10, 0.70f, OR_BLUE,
                "%s uptime %lus scroll %d%%", VERSION, systemTimerGet() / 1000, scrollIndicator);

        // Draw output log
        int end = lineCount;
        int drawOffset = 0;
        int historyOffset = 0;
        if (mHistory.size() < lineCount) {
            end = mHistory.size();
            drawOffset = lineCount - mHistory.size();
        } else if (lineCount < mHistory.size()) {
            historyOffset = mHistory.size() - lineCount;
        }
        for (int i = 0; i < end; i++) {
            getFont().drawText(10, ((i + drawOffset) * lineSteps) + firstLine,
                    0.75f, OR_BLUE, "%s", mHistory[i + historyOffset - mLineOffset]);
        }

        // Draw current input
        if ((mInputBufferPointer > 0) && (mInputBuffer[0] != '\0')) {
            getFont().drawText(10, inputLine, 0.75f, OR_BLUE, "> %s", mInputBuffer);
        } else {
            getFont().drawText(10, inputLine, 0.75f, OR_BLUE, ">");
        }

        //! \todo display the current mPartialInput. The UTF-8 segfaults SDL-TTF, somehow?
    }
}

void Console::handleKeyboard(KeyboardButton key, bool pressed) {
    if (pressed && (key == enterKey)) {
        // Execute entered command
        if ((mInputBufferPointer > 0) && (mInputBuffer[0] != '\0')) {
            print("> %s", mInputBuffer);
            mCommandHistory.push_back(bufferString("%s", mInputBuffer));
            int error = getOpenRaider().command(mInputBuffer);
            if (error != 0) {
                print("Error Code: %d", error);
            }
        } else {
            print("> ");
        }

        // Clear partial and input buffer
        mInputBufferPointer = 0;
        mInputBuffer[0] = '\0';
        if (mPartialInput != NULL) {
            delete [] mPartialInput;
            mPartialInput = NULL;
        }

        mHistoryPointer = 0;
    }

    //! \fixme only deleting the last byte is not valid for non-ASCII UTF-8 strings
    if (pressed && (key == backspaceKey)) {
        if (mInputBufferPointer > 0) {
            mInputBufferPointer--;
            mInputBuffer[mInputBufferPointer] = '\0';
        }
    }

    if (pressed && ((key == upKey) || (key == downKey))) {
        moveInHistory(key == upKey);
    }
}

void Console::moveInHistory(bool up) {
    if (mCommandHistory.size() == 0)
        return;

    if (up) {
        if (mHistoryPointer < mCommandHistory.size()) {
            mHistoryPointer++;
            if (mHistoryPointer == 1) {
                mUnfinishedInput = bufferString("%s", mInputBuffer);
            }
        } else {
            return;
        }
    } else {
        if (mHistoryPointer > 0)
            mHistoryPointer--;
        else
            return;
    }

    if ((mHistoryPointer > 0) && (mHistoryPointer <= mCommandHistory.size())) {
        strcpy(mInputBuffer, mCommandHistory[mCommandHistory.size() - mHistoryPointer]);
        mInputBufferPointer = strlen(mInputBuffer);
    } else {
        if (mUnfinishedInput != NULL) {
            strcpy(mInputBuffer, mUnfinishedInput);
            mInputBufferPointer = strlen(mInputBuffer);
            delete [] mUnfinishedInput;
            mUnfinishedInput = NULL;
        } else {
            mInputBuffer[0] = '\0';
            mInputBufferPointer = 0;
        }
    }
}

void Console::handleText(char *text, bool notFinished) {
    // Always scroll to bottom when text input is received
    mLineOffset = 0;

    if (!notFinished) {
        // Finished entering character
        // delete previous partial character, if present
        if (mPartialInput != NULL) {
            delete [] mPartialInput;
        }

        //! \fixme Temporary hack filtering the console activation key
        if (text[0] == '`')
            return;

        // Append new input to buffer
        size_t length = strlen(text);
        if (length > 0) {
            if (((INPUT_BUFFER_SIZE - mInputBufferPointer) < length)) {
                print("Console input buffer overflowed! (> %d)", INPUT_BUFFER_SIZE);
                return;
            }
            strcpy((mInputBuffer + mInputBufferPointer), text);
            mInputBufferPointer += length;
            mInputBuffer[mInputBufferPointer] = '\0';
        }
    } else {
        // Partial character received
        mPartialInput = bufferString("%s", text);
    }
}

void Console::handleMouseScroll(int xrel, int yrel) {
    assert((xrel != 0) || (yrel != 0));
    LINE_GEOMETRY(getWindow());

    if (mHistory.size() > lineCount) {
        if (yrel > 0) {
            if (mLineOffset < (mHistory.size() - lineCount)) {
                mLineOffset++;
            }
        } else if (yrel < 0) {
            if (mLineOffset > 0) {
                mLineOffset--;
            }
        }
    }
}

