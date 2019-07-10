include ./../../common-web.mk

SRC += Fourses.cpp gen_export/gen_dsp/genlib.cpp gen_export/gen_dsp.cpp

#WAM_SRC += 

WAM_CFLAGS += -DGENLIB_USE_FLOAT32 -Igen_export -Igen_export/gen_dsp

WEB_CFLAGS += -DIGRAPHICS_NANOVG -DIGRAPHICS_GLES2 -Igen_export -Igen_export/gen_dsp

WAM_LDFLAGS += -s EXPORT_NAME="'AudioWorkletGlobalScope.WAM.Fourses'" -O2 -s ASSERTIONS=0

WEB_LDFLAGS += -O2 -s ASSERTIONS=0

WEB_LDFLAGS += $(NANOVG_LDFLAGS)
