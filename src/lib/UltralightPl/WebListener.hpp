#pragma once

#include <iostream>       
#include <Ultralight/Ultralight.h>
#include <AppCore/AppCore.h>

class LocalLoadListener : public ultralight::LoadListener 
{
public:
    explicit LocalLoadListener(bool* flag) : loaded_(flag) {}

    void OnFinishLoading(
        ultralight::View* view,
        uint64_t frame_id,
        bool main_frame,
        const ultralight::String& url
    ) override 
    {
        if (main_frame) {
            std::cout << "[Ultralight] loaded " << url.utf8().data() << "\n";
            if (loaded_) {
                *loaded_ = true;
            }
        }
    }

    void OnFailLoading(
        ultralight::View* view,
        uint64_t frame_id,
        bool main_frame,
        const ultralight::String& url,
        const ultralight::String& desc,
        const ultralight::String& error_domain,
        int error_code
    ) override 
    {
        if (main_frame) {
            std::cerr << "[Ultralight] load failed " 
                      << url.utf8().data() << " " 
                      << desc.utf8().data() << "\n";
            if (loaded_) {
                *loaded_ = false;
            }
        }
    }

private:
    bool* loaded_ = nullptr;
};
