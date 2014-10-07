/*!
 * \file src/commands/CommandSet.cpp
 * \brief Set command
 *
 * \author xythobuz
 */

#include "global.h"
#include "Camera.h"
#include "Font.h"
#include "Log.h"
#include "RunTime.h"
#include "Sound.h"
#include "Window.h"
#include "utils/strings.h"
#include "commands/CommandSet.h"

std::string CommandSet::name() {
    return "set";
}

std::string CommandSet::brief() {
    return "set a parameter";
}

void CommandSet::printHelp() {
    getLog() << "set-Command Usage:" << Log::endl;
    getLog() << "  set VAR VAL" << Log::endl;
    getLog() << "Available Variables:" << Log::endl;
    getLog() << "  basedir    STRING" << Log::endl;
    getLog() << "  pakdir     STRING" << Log::endl;
    getLog() << "  audiodir   STRING" << Log::endl;
    getLog() << "  datadir    STRING" << Log::endl;
    getLog() << "  font       STRING" << Log::endl;
    getLog() << "  size       INT INT" << Log::endl;
    getLog() << "  fullscreen BOOL" << Log::endl;
    getLog() << "  audio      BOOL" << Log::endl;
    getLog() << "  volume     BOOL" << Log::endl;
    getLog() << "  mouse_x    FLOAT" << Log::endl;
    getLog() << "  mouse_y    FLOAT" << Log::endl;
    getLog() << "  fps        BOOL" << Log::endl;
    getLog() << "Enclose STRINGs with \"\"!" << Log::endl;
}

namespace {
    std::string expandNames(std::string s) {
        // Remove quotes
        if ((s.length() >= 3) &&
                (((s[0] == '"') && (s[s.length() - 1] == '"'))
                || ((s[0] == '\'') && (s[s.length() - 1] == '\'')))) {
            s.erase(0, 1);
            s.erase(s.length() - 1, 1);
        }

        // Expand Names
        s = findAndReplace(s, "$(pakdir)", getRunTime().getPakDir());
        s = findAndReplace(s, "$(audiodir)", getRunTime().getAudioDir());
        s = findAndReplace(s, "$(datadir)", getRunTime().getDataDir());
        s = findAndReplace(s, "$(basedir)", getRunTime().getBaseDir());

        // Full path
        s = expandHomeDirectory(s);

        return s;
    }
}

int CommandSet::execute(std::istream& args) {
    std::string var;
    args >> var;

    if (var.compare("size") == 0) {
        unsigned int w = DEFAULT_WIDTH, h = DEFAULT_HEIGHT;
        if (!(args >> w >> h)) {
            getLog() << "set-size-Error: Invalid value(s)" << Log::endl;
            return -2;
        }
        getWindow().setSize(w, h);
    } else if (var.compare("fullscreen") == 0) {
        bool fullscreen = false;
        if (!(args >> fullscreen)) {
            getLog() << "set-fullscreen-Error: Invalid value" << Log::endl;
            return -3;
        }
        getWindow().setFullscreen(fullscreen);
    } else if (var.compare("audio") == 0) {
        bool audio = false;
        if (!(args >> audio)) {
            getLog() << "set-audio-Error: Invalid value" << Log::endl;
            return -4;
        }
        getSound().setEnabled(audio);
    } else if (var.compare("volume") == 0) {
        float vol = 1.0f;
        if (!(args >> vol)) {
            getLog() << "set-volume-Error: Invalid value" << Log::endl;
            return -5;
        }
        getSound().setVolume(vol);
    } else if (var.compare("mouse_x") == 0) {
        float sense = 1.0f;
        if (!(args >> sense)) {
            getLog() << "set-mouse_x-Error: Invalid value" << Log::endl;
            return -6;
        }
        getCamera().setSensitivityX(OR_DEG_TO_RAD(sense));
    } else if (var.compare("mouse_y") == 0) {
        float sense = 1.0f;
        if (!(args >> sense)) {
            getLog() << "set-mouse_y-Error: Invalid value" << Log::endl;
            return -7;
        }
        getCamera().setSensitivityY(OR_DEG_TO_RAD(sense));
    } else if (var.compare("fps") == 0) {
        bool fps = false;
        if (!(args >> fps)) {
            getLog() << "set-fps-Error: Invalid value" << Log::endl;
            return -8;
        }
        getRunTime().setFPS(fps);
    } else if (var.compare("basedir") == 0) {
        std::string temp;
        args >> temp;
        getRunTime().setBaseDir(expandNames(temp));
    } else if (var.compare("pakdir") == 0) {
        std::string temp;
        args >> temp;
        getRunTime().setPakDir(expandNames(temp));
    } else if (var.compare("audiodir") == 0) {
        std::string temp;
        args >> temp;
        getRunTime().setAudioDir(expandNames(temp));
    } else if (var.compare("datadir") == 0) {
        std::string temp;
        args >> temp;
        getRunTime().setDataDir(expandNames(temp));
    } else if (var.compare("font") == 0) {
        std::string temp;
        args >> temp;
        getFont().setFont(expandNames(temp).c_str());
    } else {
        getLog() << "set-Error: Unknown variable (" << var.c_str() << ")" << Log::endl;
        return -1;
    }

    return 0;
}
