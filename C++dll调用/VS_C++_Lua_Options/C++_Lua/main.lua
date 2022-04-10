print("Hello C++ Lua")   
print("Hello C++ Call Lua")

io.write("Please enter your name: ")
name = io.read()
io.write("Hi " .. string.format("%s",name) .. ", enjoy hacking with Lua\r\n");

--来自C++的函数
myHello()