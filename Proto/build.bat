for %%i in (.\proto_format\*) do (
	protoc.exe -I=.\proto_format --cpp_out=..\Common\include\proto %%i
)