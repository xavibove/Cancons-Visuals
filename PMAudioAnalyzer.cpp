//
//  PMAudioAnalyzer.cpp
//  PMConcertParaules
//
//  Created by Miquel Àngel Soler on 21/10/15.
//
//

#include "PMAudioAnalyzer.hpp"

void PMAudioAnalyzer::init(
        float _minPitchFreq, float _maxPitchFreq,
        float _energyThreshold,
        bool _useSilence, float _silenceThreshold, unsigned int _silenceQueueLength,
        float _onsetsThreshold, float _onsetsAlpha,
        float _smoothingDelta, int _ascDescAnalysisSize)
{
    minPitchMidiNote = _minPitchFreq;
    maxPitchMidiNote = _maxPitchFreq;

    energyThreshold = _energyThreshold;

    useSilence = _useSilence;
    silenceThreshold = useSilence ? _silenceThreshold : 0;
    silenceQueueLength = _silenceQueueLength;

    onsetsThreshold = _onsetsThreshold;
    onsetsAlpha = _onsetsAlpha;

    smoothingDelta = _smoothingDelta;
    
    ascDescAnalysisSize = _ascDescAnalysisSize;
}

PMDeviceAudioAnalyzer *PMAudioAnalyzer::addDeviceAudioAnalyzer(
        unsigned int audioInputIndex,
        int deviceID, int inChannels, int outChannels, int sampleRate, int bufferSize,
        PMDAA_ChannelMode channelMode, unsigned int channelNumber)
{
    PMDeviceAudioAnalyzer *deviceAudioAnalyzer = new PMDeviceAudioAnalyzer(deviceID, inChannels, outChannels, sampleRate, bufferSize);
    deviceAudioAnalyzer->setup(audioInputIndex, channelMode, channelNumber,
            minPitchMidiNote, maxPitchMidiNote,
            energyThreshold,
            useSilence, silenceThreshold, silenceQueueLength,
            onsetsThreshold, onsetsAlpha,
            smoothingDelta, ascDescAnalysisSize);

    deviceAudioAnalyzers.push_back(deviceAudioAnalyzer);

    return deviceAudioAnalyzer;
}

vector<PMDeviceAudioAnalyzer *> *PMAudioAnalyzer::getAudioAnalyzers()
{
    return &deviceAudioAnalyzers;
}

void PMAudioAnalyzer::start()
{
    for (int i=0; i< deviceAudioAnalyzers.size(); i++)
        deviceAudioAnalyzers[i]->start();
}

void PMAudioAnalyzer::stop()
{
    for (int i=0; i< deviceAudioAnalyzers.size(); i++)
        deviceAudioAnalyzers[i]->stop();
}

void PMAudioAnalyzer::clear()
{
    stop();

    // Delete all device audio analyzers
    for (int i=0; i<deviceAudioAnalyzers.size(); i++)
        deviceAudioAnalyzers[i]->clear();

    // Erase all device audio analyzers from vector
//    for (int i=0; i<deviceAudioAnalyzers.size(); ++i)
//        delete deviceAudioAnalyzers[i];
    deviceAudioAnalyzers.clear();
}

vector<ofSoundDevice> PMAudioAnalyzer::getInputDevices()
{
    ofSoundStream soundStream;

    vector<ofSoundDevice> allDevices = soundStream.getDeviceList();

#ifdef OF_DEBUG
    soundStream.printDeviceList();
#endif

    vector<ofSoundDevice> inputDevices;
    for (int i=0; i< allDevices.size(); ++i)
        if (allDevices[i].inputChannels > 0)
            inputDevices.push_back(allDevices[i]);

    return inputDevices;
}
