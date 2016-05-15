
PEMSysps.dll: dlldata.obj PEMSys_p.obj PEMSys_i.obj
	link /dll /out:PEMSysps.dll /def:PEMSysps.def /entry:DllMain dlldata.obj PEMSys_p.obj PEMSys_i.obj \
		kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib \
.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0500 /DREGISTER_PROXY_DLL \
		$<
# _WIN32_WINNT=0x0500 is for Win2000, change it to 0x0400 for NT4 or Win95 with DCOM

clean:
	@del PEMSysps.dll
	@del PEMSysps.lib
	@del PEMSysps.exp
	@del dlldata.obj
	@del PEMSys_p.obj
	@del PEMSys_i.obj
