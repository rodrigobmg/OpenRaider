/*!
 * \file include/SoundNull.h
 * \brief This is the null audio manager Header
 *
 * \author xythobuz
 */

#ifndef _SOUND_NULL_H_
#define _SOUND_NULL_H_

#include "Sound.h"

/*!
 * \brief This is the null audio manager
 */
class SoundNull : public Sound {
public:

    /*!
     * \brief Constructs an object of SoundNull
     */
    SoundNull();

    /*!
     * \brief Deconstructs an object of SoundNull
     */
    virtual ~SoundNull();

    /*!
     * \brief Initialize sound system
     * \returns 0 on success or < 0 error flags
     */
    virtual int initialize();

    virtual void setEnabled(bool on);

    /*!
     * \brief Set the volume
     * \param vol new source gain
     */
    virtual void setVolume(float vol);

    /*!
     * \brief Get number of registered sources
     * \returns number of registered sources
     */
    virtual int registeredSources();

    /*!
     * \brief Remove all loaded sounds
     */
    virtual void clear();

    /*!
     * \brief Move listener and repositions them
     * \param pos New position for listener
     * \param angle New orientation for listener
     */
    virtual void listenAt(float pos[3], float angle[3]);

    /*!
     * \brief Move sound source to position
     * \param source valid source id
     * \param pos new position for source
     */
    virtual void sourceAt(int source, float pos[3]);

    /*!
     * \brief Load wav file from disk
     * \param filename not NULL!
     * \param source not NULL! Returns new source ID or -1 on error.
     * \param flags set options. Use SoundFlags enum bitwise OR-ed
     * \returns 0 for no error or < 0 error flag
     */
    virtual int addFile(const char *filename, int *source, unsigned int flags);

    /*!
     * \brief Load wav file from buffer
     * \param wav not NULL! Is a valid waveform buffer!
     * \param length length of wav buffer
     * \param source not NULL! Returns new source ID or -1 on error.
     * \param flags set options. Use SoundFlags enum bitwise OR-ed
     * \returns 0 for no error or < 0 error flag
     */
    virtual int addWave(unsigned char *wav, unsigned int length, int *source, unsigned int flags);

    /*!
     * \brief Play sound source
     * \param source sound source to play
     */
    virtual void play(int source);

    /*!
     * \brief Stop playing sound source
     * \param source sound source to stop
     */
    virtual void stop(int source);
};

#endif
