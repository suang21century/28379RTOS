# invoke SourceDir generated makefile for app.p28FP
app.p28FP: .libraries,app.p28FP
.libraries,app.p28FP: package/cfg/app_p28FP.xdl
	$(MAKE) -f D:\project\TiRTOS\28379test/src/makefile.libs

clean::
	$(MAKE) -f D:\project\TiRTOS\28379test/src/makefile.libs clean

