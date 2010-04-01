/////////////////////////////////////////////////////////////////////////////
// Name:        wx/msw/statbmp.h
// Purpose:     wxStaticBitmap class for wxMSW
// Author:      Julian Smart
// Modified by:
// Created:     01/02/97
// RCS-ID:      $Id: statbmp.h 58757 2009-02-08 11:45:59Z VZ $
// Copyright:   (c) Julian Smart
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////

#ifndef _WX_STATBMP_H_
#define _WX_STATBMP_H_

#include "wx/control.h"
#include "wx/icon.h"
#include "wx/bitmap.h"

extern WXDLLIMPEXP_DATA_CORE(const char) wxStaticBitmapNameStr[];

// a control showing an icon or a bitmap
class WXDLLIMPEXP_CORE wxStaticBitmap : public wxStaticBitmapBase
{
public:
    wxStaticBitmap() { Init(); }

    wxStaticBitmap(wxWindow *parent,
                   wxWindowID id,
                   const wxGDIImage& label,
                   const wxPoint& pos = wxDefaultPosition,
                   const wxSize& size = wxDefaultSize,
                   long style = 0,
                   const wxString& name = wxStaticBitmapNameStr)
    {
        Init();

        Create(parent, id, label, pos, size, style, name);
    }

    bool Create(wxWindow *parent,
                wxWindowID id,
                const wxGDIImage& label,
                const wxPoint& pos = wxDefaultPosition,
                const wxSize& size = wxDefaultSize,
                long style = 0,
                const wxString& name = wxStaticBitmapNameStr);

    virtual ~wxStaticBitmap() { Free(); }

    virtual void SetIcon(const wxIcon& icon) { SetImage(&icon); }
    virtual void SetBitmap(const wxBitmap& bitmap) { SetImage(&bitmap); }
    virtual wxBitmap GetBitmap() const;
    virtual wxIcon GetIcon() const;

    virtual WXDWORD MSWGetStyle(long style, WXDWORD *exstyle) const;

    // returns true if the platform should explicitly apply a theme border
    virtual bool CanApplyThemeBorder() const { return false; }

protected:
    virtual wxSize DoGetBestSize() const;

    // ctor/dtor helpers
    void Init() { m_isIcon = true; m_image = NULL; m_currentHandle = 0; }
    void Free();

    // true if icon/bitmap is valid
    bool ImageIsOk() const;

    void SetImage(const wxGDIImage* image);
    void SetImageNoCopy( wxGDIImage* image );

#ifndef __WXWINCE__
    // draw the bitmap ourselves here if the OS can't do it correctly (if it
    // can we leave it to it)
    void DoPaintManually(wxPaintEvent& event);
#endif // !__WXWINCE__


    // we can have either an icon or a bitmap
    bool m_isIcon;
    wxGDIImage *m_image;

    // handle used in last call to STM_SETIMAGE
    WXHANDLE m_currentHandle;

private:
    DECLARE_DYNAMIC_CLASS(wxStaticBitmap)
    wxDECLARE_NO_COPY_CLASS(wxStaticBitmap);
};

#endif
    // _WX_STATBMP_H_