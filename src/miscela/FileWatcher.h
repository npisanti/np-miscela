
#pragma once

#include "ofMain.h"

namespace np{ namespace miscela {
    
class FileWatcher{

public:
    FileWatcher();
    
    void load( std::string path, bool watch=true );

    float interval;

    ofParameterGroup parameters;

protected:
    std::string filepath;

    virtual void reload(){};

private:
    // --- variables for live check ---
    time_t writeTimestamp;
    float timePassed;
    void checkFile(ofEventArgs &args);
};
    
    
}}
