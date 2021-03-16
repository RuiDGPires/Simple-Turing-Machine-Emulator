#ifndef  __CAPP_H__
#define __CAPP_H__

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

class cApp : public wxApp{
    public:
        cApp();
        ~cApp();
};

#endif