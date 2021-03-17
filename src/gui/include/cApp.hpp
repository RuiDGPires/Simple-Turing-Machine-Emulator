#ifndef __CAPP_H__
#define __CAPP_H__

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#include "cMain.hpp"

class cApp : public wxApp{
    private:
        cMain *frame1 = nullptr;
    public:
        cApp();
        ~cApp();
    virtual bool OnInit();
};

#endif