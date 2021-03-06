source=source/*
header=header/

header=-Iheader -I../libmwshare/header/ -I../sfl -I../libescan/header -I../scan_module/include 

LIBS=/opt/MicroWorld/lib/libmwshare.so.1.0.0 /opt/MicroWorld/lib/libmwact.so.1.0.0 /opt/MicroWorld/lib/libmwsusp.so.1.0.0 /opt/MicroWorld/lib/libmwdmidecode.so  /opt/MicroWorld/lib/libescan.so.3.0.0 /opt/MicroWorld/lib/libssl.so.0.9.8 /opt/MicroWorld/lib/libcurl.so.4 -lcrypto #/opt/MicroWorld/lib/libcrypto.so.4  #/opt/Microworld/lib/libzip.so 



final:
	g++ -DZIP_STD  ${source} ${header} -Wl,-rpath=/opt/Microworld/lib/ ${LIBS} -o escan-backup -lpthread -lsqlite3 #-lzip 
	@echo DONE!
	@echo escan-backup READY!


clean :
	rm  -f escan-backup
	@echo CLEANED!
